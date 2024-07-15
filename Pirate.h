#ifndef WET1MIVNE_PIRATE_H
#define WET1MIVNE_PIRATE_H

#include <memory>

#include "Deque.h"

class Ship;

class Pirate {
   private:
    int pirate_id;
    int treasure;
    std::weak_ptr<Ship> ship;
    DequeNode<int>* pointer;

   public:
    Pirate(int& pirate_id, int& treasure, DequeNode<int>* list_ptr,
           std::weak_ptr<Ship> ship_ptr)
        : pirate_id(pirate_id),
          treasure(treasure),
          ship(ship_ptr),
          pointer(list_ptr){};

    int getId() { return pirate_id; }

    std::weak_ptr<Ship> getShip(){
        return ship;
    }

    DequeNode<int>* getPirateListPointer(){
        return pointer;
    }

    void setPirateListPointer(DequeNode<int>* pointer){
        this->pointer = pointer;
    }

    int getTreasure(){
        return treasure;
    }


    void addCoins(int coins){
        treasure += coins;
    }

};

#endif