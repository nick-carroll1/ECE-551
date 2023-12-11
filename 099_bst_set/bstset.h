#ifndef __BST_SET_H__
#define __BST_SET_H__

#include <set>
#include <stack>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
  class Node {
   public:
    T key;
    Node * left;
    Node * right;
    Node(const T & newKey) : key(newKey), left(NULL), right(NULL) {}
    Node(const Node & rhs) : key(rhs.key), left(NULL), right(NULL) {
      if (rhs.left != NULL) {
        left = new Node(*rhs.left);
      }
      if (rhs.right != NULL) {
        right = new Node(*rhs.right);
      }
    }
    Node & operator=(const Node & rhs) {
      if (this != &rhs) {
        key = rhs.value;
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
  BstSet() : root(NULL) {}
  BstSet(const BstSet & rhs) : root(NULL) {
    if (rhs.root != NULL) {
      root = new Node(*rhs.root);
    }
  }
  BstSet & operator=(const BstSet & rhs) {
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
  void addHelper(const T & key, Node * currentNode) {
    if (key > currentNode->key) {
      if (currentNode->right == NULL) {
        currentNode->right = new Node(key);
      }
      else {
        addHelper(key, currentNode->right);
      }
    }
    else {
      if (currentNode->left == NULL) {
        currentNode->left = new Node(key);
      }
      else {
        addHelper(key, currentNode->left);
      }
    }
  }
  virtual void add(const T & key) {
    if (root == NULL) {
      root = new Node(key);
    }
    else {
      addHelper(key, root);
    }
  }
  virtual bool containsHelper(const T & key, const Node * currentNode) const {
    if (key == currentNode->key) {
      return true;
    }
    else {
      if (key > currentNode->key) {
        if (currentNode->right == NULL) {
          return false;
        }
        else {
          return containsHelper(key, currentNode->right);
        }
      }
      else {
        if (currentNode->left == NULL) {
          return false;
        }
        else {
          return containsHelper(key, currentNode->left);
        }
      }
    }
  }

  virtual bool contains(const T & key) const {
    if (root != NULL) {
      return containsHelper(key, root);
    }
    else {
      return false;
    }
  }

  void removeHelper(const T & key, Node * currentNode, Node ** parentPointer) {
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

  virtual void remove(const T & key) {
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

  virtual ~BstSet<T>() {
    if (root != NULL) {
      deleteHelper(root);
    }
  }
};
#endif
