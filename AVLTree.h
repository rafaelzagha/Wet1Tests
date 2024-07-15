#ifndef WET1MIVNE_AVLTREE_H
#define WET1MIVNE_AVLTREE_H

#include <math.h>

#include <iostream>
#include <memory>

#include "Pirate.h"

template <typename T>
struct AVLNode {
    int key;
    int max_treasure_id;
    int max_treasure;
    std::shared_ptr<T> value;
    AVLNode<T>* left;
    AVLNode<T>* right;
    AVLNode<T>* parent;
    int height;

    AVLNode(int k, std::shared_ptr<T> val)
        : key(k),
          max_treasure_id(0),
          max_treasure(0),
          value(val),
          left(nullptr),
          right(nullptr),
          parent(nullptr),
          height(1){};
};

template <typename T>
class AVLTree {
   private:
    AVLNode<T>* root;

    void deleteTree(AVLNode<T>* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    int getHeight(AVLNode<T>* node) { return node ? node->height : 0; }

    int getBalanceFactor(AVLNode<T>* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    int max(int a, int b) { return a >= b ? a : b; }

    void updateHeight(AVLNode<T>* node) {
        if (node) {
            node->height =
                1 + max(getHeight(node->left), getHeight(node->right));
        }
    }

    AVLNode<T>* rotateRight(AVLNode<T>* y, bool& updateMax) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;

        x->right = y;
        y->left = T2;

        if (T2) T2->parent = y;
        x->parent = y->parent;
        y->parent = x;

        updateHeight(y);
        updateHeight(x);

        if (updateMax) {
            updateMaxTreasureId(y);
            updateMaxTreasureId(x);
        }

        return x;
    }

    AVLNode<T>* rotateLeft(AVLNode<T>* x, bool& updateMax) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;

        y->left = x;
        x->right = T2;

        if (T2) T2->parent = x;
        y->parent = x->parent;
        x->parent = y;

        updateHeight(x);
        updateHeight(y);
        if (updateMax) {
            updateMaxTreasureId(x);
            updateMaxTreasureId(y);
        }

        return y;
    }

    AVLNode<T>* insert(AVLNode<T>* node, int key, std::shared_ptr<T> value,
                       bool& inserted, bool updateMax) {
        if (!node) {
            inserted = true;
            node = new AVLNode<T>(key, value);

        } else {
            if (key < node->key) {
                node->left =
                    insert(node->left, key, value, inserted, updateMax);
                if (node->left) {
                    node->left->parent = node;
                }
            } else if (key > node->key) {
                node->right =
                    insert(node->right, key, value, inserted, updateMax);
                if (node->right) {
                    node->right->parent = node;
                }
            } else {
                inserted = false;
                return node;
            }

            updateHeight(node);

            int balance = getBalanceFactor(node);

            if (balance > 1 && key < node->left->key) {
                return rotateRight(node, updateMax);
            } else if (balance < -1 && key > node->right->key) {
                return rotateLeft(node, updateMax);
            } else if (balance > 1 && key > node->left->key) {
                node->left = rotateLeft(node->left, updateMax);
                return rotateRight(node, updateMax);
            } else if (balance < -1 && key < node->right->key) {
                node->right = rotateRight(node->right, updateMax);
                return rotateLeft(node, updateMax);
            }
        }

        if (updateMax) {
            updateMaxTreasureId(node);
        }

        return node;
    }

    AVLNode<T>* minValueNode(AVLNode<T>* node) {
        AVLNode<T>* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    AVLNode<T>* remove(AVLNode<T>* root, int key,  updateMax) {
        if (!root) {
            return root;
        }

        if (key < root->key) {
            root->left = remove(root->left, key, updateMax);
            if (root->left) {
                root->left->parent = root;
            }
        } else if (key > root->key) {
            root->right = remove(root->right, key, updateMax);
            if (root->right) {
                root->right->parent = root;
            }
        } else {
            if (!root->left || !root->right) {
                AVLNode<T>* temp = root->left ? root->left : root->right;

                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }

                if (temp) {
                    if (temp->left) {
                        temp->left->parent = temp->parent;
                    }
                    if (temp->right) {
                        temp->right->parent = temp->parent;
                    }
                }

                delete temp;
            } else {
                AVLNode<T>* temp = minValueNode(root->right);

                root->key = temp->key;
                root->value = temp->value;

                root->right = remove(root->right, temp->key, updateMax);
                if (root->right) {
                    root->right->parent = root;
                }
            }
        }

        if (!root) {
            return root;
        }

        updateHeight(root);

        int balance = getBalanceFactor(root);

        if (balance > 1 && getBalanceFactor(root->left) >= 0) {
            return rotateRight(root, updateMax);
        }

        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left, updateMax);
            return rotateRight(root, updateMax);
        }

        if (balance < -1 && getBalanceFactor(root->right) <= 0) {
            return rotateLeft(root, updateMax);
        }

        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right, updateMax);
            return rotateLeft(root, updateMax);
        }

        if (updateMax) {
            updateMaxTreasureId(root);
        }
        return root;
    }

    AVLNode<T>* find(AVLNode<T>* node, int key) {
        if (!node || node->key == key) {
            return node;
        }
        if (key < node->key) {
            return find(node->left, key);
        } else {
            return find(node->right, key);
        }
    }

   public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() { deleteTree(root); }

    bool insert(int key, std::shared_ptr<T> value, bool updateMax) {
        bool inserted = false;
        root = insert(root, key, value, inserted, updateMax);
        return inserted;
    }

    void remove(int key, bool updateMax) {
        root = remove(root, key, updateMax);
    }

    std::shared_ptr<T> find(int key) {
        AVLNode<T>* node = find(root, key);
        return node ? node->value : nullptr;
    }

    void updateMaxTreasureId(AVLNode<T>* node) { return; }

    void updateMaxFromChangedNode(int pirateId) { return; }

    int getMaxTreasureId() { return 0; }

    void printTree(AVLNode<T>* node, int space) const {
        if (!node) return;

        const int COUNT = 5;
        space += COUNT;

        printTree(node->right, space);

        std::cout << std::endl;
        for (int i = COUNT; i < space; ++i) {
            std::cout << " ";
        }
        std::cout << node->key << "\n";

        printTree(node->left, space);
    }

    void print() const {
        if (!root) {
            std::cout << "Tree is empty.\n";
            return;
        }
        printTree(root, 0);
    }
};
template <>
void AVLTree<Pirate>::updateMaxTreasureId(AVLNode<Pirate>* node);

template <>
void AVLTree<Pirate>::updateMaxFromChangedNode(int pirateId);

template <>
int AVLTree<Pirate>::getMaxTreasureId();

#endif  // WET1MIVNE_AVLTREE_H
