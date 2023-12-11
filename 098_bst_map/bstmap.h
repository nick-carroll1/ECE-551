#ifndef __BST_MAP_H__
#define __BST_MAP_H__

#include <set>
#include <stack>

#include "map.h"

class Missing_Key : public std::invalid_argument {
  virtual const char * what() const throw() { return "Key not found in Map"; }

 public:
  Missing_Key() : invalid_argument("Key not found in Map") {}
};

template<typename K, typename V>
class BstMap : public Map<K, V> {
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(const K & newKey, const V & newValue) :
        key(newKey), value(newValue), left(NULL), right(NULL) {}
    Node(const Node & rhs) : key(rhs.key), value(rhs.value), left(NULL), right(NULL) {
      if (rhs.left != NULL) {
        left = new Node(*rhs.left);
      }
      if (rhs.right != NULL) {
        right = new Node(*rhs.right);
      }
    }
    Node & operator=(const Node & rhs) {
      if (this != &rhs) {
        key = rhs.key;
        value = rhs.value;
        if (rhs.left != NULL) {
          if (left != NULL) {
            deleteHelper(left);
          }
          left = new Node(*rhs.left);
        }
        if (rhs.right != NULL) {
          if (left != NULL) {
            deleteHelper(left);
          }
          right = new Node(*rhs.right);
        }
      }
      return *this;
    }
    void deleteHelper(Node * currentNode) {
      if (currentNode->left != NULL) {
        deleteHelper(currentNode->left);
      }
      if (currentNode->right != NULL) {
        deleteHelper(currentNode->right);
      }
      delete currentNode;
    }
    ~Node() {}
  };

 private:
  Node * root;

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs) : root(NULL) {
    if (rhs.root != NULL) {
      root = new Node(*rhs.root);
    }
  }
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      if (root != NULL) {
        deleteHelper(root);
      }
      if (rhs.root != NULL) {
        root = new Node(*rhs.root);
      }
      else {
        root = rhs.root;
      }
    }
    return *this;
  }
  void addHelper(const K & key, const V & value, Node * currentNode) {
    if (key == currentNode->key) {
      currentNode->value = value;
    }
    else {
      if (key > currentNode->key) {
        if (currentNode->right == NULL) {
          currentNode->right = new Node(key, value);
        }
        else {
          addHelper(key, value, currentNode->right);
        }
      }
      else {
        if (currentNode->left == NULL) {
          currentNode->left = new Node(key, value);
        }
        else {
          addHelper(key, value, currentNode->left);
        }
      }
    }
  }
  virtual void add(const K & key, const V & value) {
    if (root == NULL) {
      root = new Node(key, value);
    }
    else {
      addHelper(key, value, root);
    }
  }
  virtual const V & lookupHelper(const K & key, const Node * currentNode) const
      throw(std::invalid_argument) {
    if (key == currentNode->key) {
      return currentNode->value;
    }
    else {
      if (key > currentNode->key) {
        if (currentNode->right == NULL) {
          throw Missing_Key();
        }
        else {
          return lookupHelper(key, currentNode->right);
        }
      }
      else {
        if (currentNode->left == NULL) {
          throw Missing_Key();
        }
        else {
          return lookupHelper(key, currentNode->left);
        }
      }
    }
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    if (root != NULL) {
      return lookupHelper(key, root);
    }
    else {
      throw Missing_Key();
    }
  }

  void removeHelper(const K & key, Node * currentNode, Node ** parentPointer) {
    if (currentNode->key == key) {
      Node * temp = currentNode;
      Node * closestParent;
      if (currentNode->right != NULL) {
        closestParent = findClosest(currentNode->right, currentNode);
        if (closestParent != temp) {
          *parentPointer = closestParent->left;
          closestParent->left = closestParent->left->right;
          (*parentPointer)->right = temp->right;
          (*parentPointer)->left = temp->left;
        }
        else {
          *parentPointer = temp->right;
          (*parentPointer)->left = temp->left;
        }
        delete temp;
      }
      else {
        *parentPointer = currentNode->left;
        delete temp;
      }
    }
    else {
      if (key > currentNode->key) {
        if (currentNode->right != NULL) {
          removeHelper(key, currentNode->right, &currentNode->right);
        }
      }
      else {
        if (currentNode->left != NULL) {
          removeHelper(key, currentNode->left, &currentNode->left);
        }
      }
    }
  }

  Node * findClosest(Node * currentNode, Node * parentNode) {
    if (currentNode->left != NULL) {
      return findClosest(currentNode->left, currentNode);
    }
    else {
      return parentNode;
    }
  }

  virtual void remove(const K & key) {
    if (root != NULL) {
      removeHelper(key, root, &root);
    }
  }

  void deleteHelper(Node * currentNode) {
    if (currentNode->left != NULL) {
      deleteHelper(currentNode->left);
    }
    if (currentNode->right != NULL) {
      deleteHelper(currentNode->right);
    }
    delete currentNode;
  }

  virtual ~BstMap<K, V>() {
    if (root != NULL) {
      deleteHelper(root);
    }
  }
};
#endif
