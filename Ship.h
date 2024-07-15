#ifndef WET1MIVNE_SHIP_H
#define WET1MIVNE_SHIP_H

#include <iostream>
#include <memory>

#include "AVLTree.h"
#include "Deque.h"
#include "Pirate.h"

class Ship {
   private:
    int ship_id;
    int cannon_num;
    int pirate_num;
    int treasure_offset;

    AVLTree<Pirate> treasure_tree;
    Deque<int> pirates_queue;

   public:
    Ship(int id, int cannons)
        : ship_id(id), cannon_num(cannons), pirate_num(0), treasure_offset(0) {}

    DequeNode<int>* add_pirate_id(int pirate_id) {
        return pirates_queue.push_back(pirate_id);
    }
    void add_pirate(std::shared_ptr<Pirate> pirate) {
        pirate->addCoins(-treasure_offset);
        treasure_tree.insert(pirate->getId(), pirate, true);
        pirate_num++;
    }

    void remove_pirate(int pirate_id, DequeNode<int>* pointer) {
        treasure_tree.remove(pirate_id, true);
        pirates_queue.erase(pointer);
        pirate_num--;
    }

    int treason() {
        try {
            int pirate_id = pirates_queue.front();
            return pirate_id;
        } catch (const std::out_of_range& e) {
            return 0;
        }
    }

    int getTreasureOffset() { return treasure_offset; }

    void addTreasureOffset(int change) { treasure_offset += change; }

    int getPirateNum() { return pirate_num; }

    int getCannons() { return cannon_num; }

    void updatePirateMaxTreasure(int pirateId) {
        treasure_tree.updateMaxFromChangedNode(pirateId);
    }

    int getRichestPirate() { return treasure_tree.getMaxTreasureId(); }
};

template <>
inline void AVLTree<Pirate>::updateMaxTreasureId(AVLNode<Pirate>* node) {
    if (!node) return;

    Pirate p = *(node->value);
    int p_treasure = p.getTreasure();
    int p_id = p.getId();

    int leftMax = node->left ? node->left->max_treasure : p_treasure;
    int rightMax = node->right ? node->right->max_treasure : p_treasure;

    int leftId = node->left ? node->left->max_treasure_id : -1;
    int rightId = node->right ? node->right->max_treasure_id : -1;

    int children_max = max(leftMax, rightMax);
    int children_id = (children_max == leftMax) ? leftId : rightId;

    if (leftMax == rightMax && leftId != rightId) {
        children_id = max(leftId, rightId);
    }

    if (p_treasure > children_max ||
        (p_treasure == children_max && p_id > children_id)) {
        node->max_treasure = p_treasure;
        node->max_treasure_id = p_id;
    } else {
        node->max_treasure = children_max;
        node->max_treasure_id = children_id;
    }
}

template <>
inline void AVLTree<Pirate>::updateMaxFromChangedNode(int pirateId) {
    AVLNode<Pirate>* node = find(root, pirateId);
    while (node) {
        updateMaxTreasureId(node);
        node = node->parent;
    }
}

template <>
inline int AVLTree<Pirate>::getMaxTreasureId() {
    return root->max_treasure_id;
}

#endif
