#include "pirates24b1.h"

#include <memory>

#include "AVLTree.h"
#include "Pirate.h"
#include "Ship.h"
#include "wet1util.h"

Ocean::Ocean() {}

Ocean::~Ocean() {}


StatusType Ocean::add_ship(int shipId, int cannons) {
    if (cannons < 0 || shipId <= 0) return StatusType::INVALID_INPUT;
    try {
        std::shared_ptr<Ship> new_ship(new Ship(shipId, cannons));
        bool result = ships.insert(shipId, new_ship, false);
        return result ? StatusType::SUCCESS : StatusType::FAILURE;

    } catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Ocean::remove_ship(int shipId) {
    if (shipId <= 0) return StatusType::INVALID_INPUT;

    std::shared_ptr<Ship> ship = ships.find(shipId);
    if (ship == nullptr || ship->getPirateNum() > 0) {
        return StatusType::FAILURE;
    }
    ships.remove(shipId, false);

    return StatusType::SUCCESS;
}

StatusType Ocean::add_pirate(int pirateId, int shipId, int treasure) {
    if (pirateId <= 0 || shipId <= 0) return StatusType::INVALID_INPUT;

    std::shared_ptr<Ship> ship = ships.find(shipId);
    std::shared_ptr<Pirate> pirate = pirates.find(pirateId);
    // adjust max_treasure_id in tree for all

    if (ship != nullptr && pirate == nullptr) {
        DequeNode<int>* node_pointer = ship->add_pirate_id(pirateId);
        std::weak_ptr<Ship> weak_ship(ship);
        try {
            pirate = std::shared_ptr<Pirate>(
                new Pirate(pirateId, treasure, node_pointer,
                           weak_ship));  
            pirates.insert(pirateId, pirate, false);
            ship->add_pirate(pirate);
            return StatusType::SUCCESS;
        } catch (const std::bad_alloc& e) {
            return StatusType::ALLOCATION_ERROR;
        }
    }

    return StatusType::FAILURE;
}

StatusType Ocean::remove_pirate(int pirateId) {
    if (pirateId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Pirate> pirate = pirates.find(pirateId);
    if (pirate == nullptr) {
        return StatusType::FAILURE;
    }

    if (std::shared_ptr<Ship> ship = pirate->getShip().lock()) {
        ship->remove_pirate(pirateId, pirate->getPirateListPointer());
    }

    pirates.remove(pirateId, false);

    return StatusType::SUCCESS;
}

StatusType Ocean::treason(int sourceShipId, int destShipId) {
    if (sourceShipId <= 0 || destShipId <= 0 || sourceShipId == destShipId) {
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Ship> src_ship = ships.find(sourceShipId);
    std::shared_ptr<Ship> dest_ship = ships.find(destShipId);
    if (src_ship != nullptr && dest_ship != nullptr) {
        int pirate_id = src_ship->treason();
        if (pirate_id <= 0) {
            return StatusType::FAILURE;
        }
        std::shared_ptr<Pirate> pirate = pirates.find(pirate_id);
        int coins = pirate->getTreasure() + src_ship->getTreasureOffset();

        StatusType res = remove_pirate(pirate_id);

        if (res != StatusType::SUCCESS) {
            return res;
        }

        add_pirate(pirate_id, destShipId, coins);

        return StatusType::SUCCESS;
    }

    return StatusType::FAILURE;
}

StatusType Ocean::update_pirate_treasure(int pirateId, int change) {
    if (pirateId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Pirate> pirate = pirates.find(pirateId);
    if (pirate == nullptr) {
        return StatusType::FAILURE;
    }
    pirate->addCoins(change);
    if (std::shared_ptr<Ship> ship = pirate->getShip().lock()) {
        ship->updatePirateMaxTreasure(pirate->getId());
    }

    return StatusType::SUCCESS;
}

output_t<int> Ocean::get_treasure(int pirateId) {
    if (pirateId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Pirate> pirate = pirates.find(pirateId);
    if (pirate == nullptr) {
        return StatusType::FAILURE;
    }
    if (std::shared_ptr<Ship> ship = pirate->getShip().lock()) {
        output_t<int> result(pirate->getTreasure() +
                             ship->getTreasureOffset());
        return result;
    }

    return 0;
}

output_t<int> Ocean::get_cannons(int shipId) {
    if (shipId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Ship> ship = ships.find(shipId);
    if (ship == nullptr) {
        return StatusType::FAILURE;
    }
    output_t<int> result(ship->getCannons());

    return result;
}

output_t<int> Ocean::get_richest_pirate(int shipId) {
    if (shipId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Ship> ship = ships.find(shipId);
    if (ship == nullptr || ship->getPirateNum() == 0) {
        return StatusType::FAILURE;
    }
    output_t<int> result(ship->getRichestPirate());
    return result;
}

int min(int a, int b) { return a <= b ? a : b; }

StatusType Ocean::ships_battle(int shipId1, int shipId2) {
    if (shipId1 <= 0 || shipId2 <= 0 || shipId1 == shipId2) {
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Ship> ship1 = ships.find(shipId1);
    std::shared_ptr<Ship> ship2 = ships.find(shipId2);

    if (!ship1 || !ship2) {
        return StatusType::FAILURE;
    }
    int p1 = min(ship1->getCannons(), ship1->getPirateNum());
    int p2 = min(ship2->getCannons(), ship2->getPirateNum());

    if (p1 > p2) {
        ship1->addTreasureOffset(ship2->getPirateNum());
        ship2->addTreasureOffset(-ship1->getPirateNum());
    } else if (p1 < p2) {
        ship2->addTreasureOffset(ship1->getPirateNum());
        ship1->addTreasureOffset(-ship2->getPirateNum());
    }
    return StatusType::SUCCESS;
}

