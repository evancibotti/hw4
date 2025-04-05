#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{
}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{
}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateright(AVLNode<Key,Value>* right);
    void rotateleft(AVLNode<Key,Value>* left);
    void insertfix(AVLNode<Key,Value>* node);
    void removefix(AVLNode<Key,Value>* node);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    // if the tree is empty it needs to be inserted as the root_
    if(this->root_ == nullptr){
      this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
      // you can then return because you are done
      return;
    }

    // create pointers to the node you are currently on and the prev one
    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_);
    AVLNode<Key, Value>* prev = nullptr;

    // traverse until you reach the the node or bottom
    while(current != nullptr){

      // check if the its already inside each time to just overwrite
      if(current->getKey() == new_item.first){
        current->setValue(new_item.second);
        // able to return nothing else to be done
        return;
        
      } else {
        // if not store your current as prev so you can move down
        prev = current;

        // figure out which way to go like in the other file
        if(current->getKey() < new_item.first){
          current = current->getRight();
        } else if(current->getKey() > new_item.first){
          current = current->getLeft();
        }
      }
    }

  // now that you have found the leaf location to insert create the node to 
  // be inserted and make its parent the previous node
  AVLNode<Key, Value>* insert = new AVLNode<Key, Value>(new_item.first, new_item.second, prev);

  // figure out which child to set it to for the parent
  if(prev->getKey() < new_item.first){
    prev->setRight(insert);
  } else if(prev->getKey() > new_item.first){
    prev->setLeft(insert);
  }

  // then finally call the helper function to fix the the tree
  insertfix(insert);
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    // find and save the node that we are trying to remove from the tree
    // using the key
    // can use inherited function if you static cast and use this pointer
    AVLNode<Key, Value>* removal = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));

    // create another pointer to store the predecessor of the removal if it
    // has two children
    AVLNode<Key, Value>* pred = nullptr;

    // create another 2 pointers to store its child and parent for later
    AVLNode<Key, Value>* child = nullptr;
    AVLNode<Key, Value>* parent = nullptr;


    // can just stop if the key provided isnt in the tree
    if(removal == nullptr){
      return;
    }

    // check if it has two children
    if(removal->getRight() != nullptr && removal->getLeft() != nullptr){
      // store its predecessor and swap them if so
      // have to static cast and use this to use old functions
      pred = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::predecessor(removal));
      this->nodeSwap(removal, pred);
    }

    // store the removals parent now because it could have just changed
    parent = removal->getParent();

    // store its child if it has one
    if(removal->getLeft() != nullptr){
      child = removal->getLeft();
    } else if(removal->getRight() != nullptr){
      child = removal->getRight();
    }
    // create a variable to store the change in balance
    // depending on what side the child is on
    int8_t balchange = 0;

    // set its child as root if theres no parent
    // or set the parents child to it if so
    if(parent == nullptr){
      this->root_ = child;
    } else if (parent != nullptr){
      // figure out which child it is
      if(parent->getLeft() == removal){
        parent->setLeft(child);
        // change balchange accordingly
        balchange = 1;
      } else if(parent->getRight() == removal){
        parent->setRight(child);
        // change balchange accordingly
        balchange = -1;
      }
    }
    // now update the childs parent if needed
    if(child != nullptr){
      child->setParent(parent);
    }

    // finally delete the node
    delete removal;

    // fix balance and call helper if needed 
    if(parent != nullptr){
      parent->updateBalance(balchange);
      //
      removefix(parent);
    }
}

// helper for rotating right
template<class Key, class Value>
void AVLTree<Key, Value>:: rotateright(AVLNode<Key,Value>* right){
    // TODO
    // store the 4 nodes to be used so that there can be no issues with
    // the order of operations and nothing is lost
    AVLNode<Key, Value>* oroot = right;
    AVLNode<Key, Value>* nroot = right->getLeft();
    AVLNode<Key, Value>* parent = right->getParent();
    AVLNode<Key, Value>* rchild = nroot->getRight();

    // Connect the new root to the old parent if there is one
    if(parent != nullptr){
      nroot->setParent(parent);
      if(parent->getLeft() == oroot){
        parent->setLeft(nroot);
      } else {
        parent->setRight(nroot);
      }
    } else {
      // set the root equal to the new one if it was previosly
      this->root_ = nroot;
      // set its parent to null
      nroot->setParent(nullptr);
    }

    // Switch the location of the new root and old root
    nroot->setRight(oroot);
    oroot->setParent(nroot);

    // Connect the new roots right child to the old ones left if there is one
    oroot->setLeft(rchild);
    if(rchild != nullptr){
      rchild->setParent(oroot);
    }
}

// helper for rotating left
template<class Key, class Value>
void AVLTree<Key, Value>:: rotateleft(AVLNode<Key,Value>* left){
    // TODO
    // store the 4 nodes to be used so that there can be no issues with
    // the order of operations and nothing is lost
    AVLNode<Key, Value>* oroot = left;
    AVLNode<Key, Value>* nroot = left->getRight();
    AVLNode<Key, Value>* parent = left->getParent();
    AVLNode<Key, Value>* lchild = nroot->getLeft();

    // Connect the new root to the old parent if there is one
    if(parent != nullptr){
      nroot->setParent(parent);
      if(parent->getLeft() == oroot){
        parent->setLeft(nroot);
      } else {
        parent->setRight(nroot);
      }
    } else {
      // set the root equal to the new one if it was previosly
      this->root_ = nroot;
      // set its parent to nullptr
      nroot->setParent(nullptr);
    }

    // Switch the location of the new root and old root
    nroot->setLeft(oroot);
    oroot->setParent(nroot);

    // Connect the new roots left child to the old ones right if there is one
    oroot->setRight(lchild);
    if(lchild != nullptr){
      lchild->setParent(oroot);
    }
}

// helper for fixing the balance after inserting
template<class Key, class Value>
void AVLTree<Key, Value>:: insertfix(AVLNode<Key,Value>* node){
    // TODO
    // REMEMBER BALANCE IS L-R
    // get its parent and the while loop of traversal will go until
    // this parent is nullptr (the current node is the root)
    AVLNode<Key, Value>* parent = node->getParent();

    // also save a copy of the insertion so it can be edited
    AVLNode<Key, Value>* current = node;

    while(parent != nullptr){
      // branch for which side it was added to (start with right)
      if(parent->getRight() == current){

        // parents balance increases by 1
        parent->updateBalance(1);

        // check if its fully balanced so you can stop early because the child only helped
        if(parent->getBalance() == 0){
          break;
        }

        // check if its fully unbalanced and fix if so
        // (can't be possible on first iteration)
        else if(parent->getBalance() == 2){

          // branch for if it needs double or single (double first) 
          if(current->getBalance() == -1){

            // current = right and child = left so store its child and balance
            AVLNode<Key, Value>* child = current->getLeft();
            int8_t childbal = child->getBalance();

            // rotate the child right and parent left
            rotateright(current);
            rotateleft(parent);

            // update the balances depending on its original
            if(childbal == 0){
              child->setBalance(0);
              current->setBalance(0);
              parent->setBalance(0);
            } else if(childbal == -1){
              child->setBalance(0);
              current->setBalance(1);
              parent->setBalance(0);
            } else if(childbal == 1){
              child->setBalance(0);
              current->setBalance(0);
              parent->setBalance(-1);
            }
          } 

          // branch for if it needs double or single (single second)
          else if(current->getBalance() == 1){
            // save child to change balances later
            AVLNode<Key, Value>* child = current->getRight();

            // current = right and child = right so just rotate left with parent
            rotateleft(parent);

            // now change balances to 0 because it is a triangle
            child->setBalance(0);
            current->setBalance(0);
            parent->setBalance(0);
          }

          // now break because both cases where it was unbalanced we fixed it
          break;
        }
        
      // branch for which side it was added to (finish with left)
      } else if(parent->getLeft() == current){

        // parents balance decreases by 1
        parent->updateBalance(-1);

        // check if its fully balanced so you can stop early because the child only helped
        if(parent->getBalance() == 0){
          break;
        }

        // check if its fully unbalanced and fix if so
        // (can't happen till second iteration)
        else if(parent->getBalance() == -2){

          // branch for if it needs double or single (double first) 
          if(current->getBalance() == 1){

            // current = left and child = right so store its child and balance
            AVLNode<Key, Value>* child = current->getRight();
            int8_t childbal = child->getBalance();

            // rotate the child left and parent right
            rotateleft(current);
            rotateright(parent);

            // update the balances depending on its original
            if(childbal == 0){
              child->setBalance(0);
              current->setBalance(0);
              parent->setBalance(0);
            } else if(childbal == -1){
              child->setBalance(0);
              current->setBalance(0);
              parent->setBalance(1);
            } else if(childbal == 1){
              child->setBalance(0);
              current->setBalance(-1);
              parent->setBalance(0);
            }
          } 

          // branch for if it needs double or single (single second)
          else if(current->getBalance() == -1){
            // save child to change balances later
            AVLNode<Key, Value>* child = current->getLeft();

            // current = left and child = left so just rotate right with parent
            rotateright(parent);

            // now change balances to 0 because it is a triangle
            child->setBalance(0);
            current->setBalance(0);
            parent->setBalance(0);
          }

          // now break because both cases where it was unbalanced we fixed it
          break;
        }
      }

      // update for traversal
      current = parent;
      parent = parent->getParent();
    }
}

// helper for fixing the balance after removing
template<class Key, class Value>
void AVLTree<Key, Value>:: removefix(AVLNode<Key,Value>* node){
    // TODO
    // REMEMBER BALANCE IS L-R
    // Save a copy of the parent so it can be edited
    AVLNode<Key, Value>* current = node;
    AVLNode<Key, Value>* parent = nullptr;

    // get its parent and the while loop of traversal will go until
    // this parent is nullptr (the current node is the root)
    if(current != nullptr && current->getParent() != nullptr){
      parent = current->getParent();
    } else {
      return;
    }

    while(parent != nullptr){
      // branch for which side was removed (start with right)
      if(parent->getRight() == current){
        // update the balance of the parent accordingly
        parent->updateBalance(-1);

        // if parent has a balance of 0 can't change anything
        // but still need to move up so don't check

        // check if the new balance is now -1 
        //(would've been balanced so just lost 1 child and no height changed)
        if(parent->getBalance() == -1){
          break;

        }

        // now check if new balance is 2 where you need to rotate
        if(parent->getBalance() == -2){
            // we now know the child is on the left so store it
            AVLNode<Key, Value>* child = parent->getLeft();

            // branch for if child is balanced
            if(child->getBalance() == 0){
              // left child and both children 
              rotateright(parent);
              // adjust balances
              child->setBalance(1);
              parent->setBalance(-1);
              // break here because height doesn't increase or decrease
              break;
            }

            // branch for if child has left child
            else if(child->getBalance() == -1){
             // left child and left child 
              rotateright(parent);
              // adjust balances
              child->setBalance(0);
              parent->setBalance(0);
              // don't break because height decreased
            }

            // branch for if child has right child
            else if(child->getBalance() == 1){
              // left child and right child so store its child and balance
              AVLNode<Key, Value>* gchild = child->getRight();
              int8_t gchildbal = gchild->getBalance();

              // rotate the gchild left and child right
              rotateleft(child);
              rotateright(parent);

              // update the balances depending on its original
              if(gchildbal == 0){
                child->setBalance(0);
                gchild->setBalance(0);
                parent->setBalance(0);
              }   else if(gchildbal == -1){
                child->setBalance(0);
                gchild->setBalance(0);
                parent->setBalance(1);
              } else if(gchildbal == 1){
                child->setBalance(-1);
                gchild->setBalance(0);
                parent->setBalance(0);
              }
              // don't break because height decreased
            }
        }
      // branch for which side was removed (end with left)
      } else if(parent->getLeft() == current){
        // update the balance of the parent accordingly
        parent->updateBalance(1);

        // if parent has a balance of 0 can't change anything
        // but still need to move up so don't check

        // check if the new balance is now 1 
        //(would've been balanced so just lost 1 child and no height changed)
        if(parent->getBalance() == 1){
          break;

        }
        // now check if new balance is 2 where you need to rotate
        if(parent->getBalance() == 2){
            // we now know the child is on the right so store it
            AVLNode<Key, Value>* child = parent->getRight();

           // branch for if child is balanced
            if(child->getBalance() == 0){
              // right child and both children 
             rotateleft(parent);
              // adjust balances
              child->setBalance(-1);
              parent->setBalance(1);
              // break here because height doesn't increase or decrease
              break;
            }

            // branch for if child has right child
            else if(child->getBalance() == 1){
              // right child and right child 
              rotateleft(parent);
              // adjust balances
              child->setBalance(0);
              parent->setBalance(0);
              // don't break because height decreased
            }

            // branch for if child has left child
            else if(child->getBalance() == -1){
              // right child and left child so store its child and balance
              AVLNode<Key, Value>* gchild = child->getLeft();
              int8_t gchildbal = gchild->getBalance();

              // rotate the child right and parent left
              rotateright(child);
              rotateleft(parent);

              // update the balances depending on its original
              if(gchildbal == 0){
                child->setBalance(0);
                gchild->setBalance(0);
                parent->setBalance(0);
              } else if(gchildbal == -1){
                child->setBalance(1);
                gchild->setBalance(0);
                parent->setBalance(0);
              } else if(gchildbal == 1){
                child->setBalance(0);
                gchild->setBalance(0);
                parent->setBalance(-1);
              }
              // don't break because height decreased
           }
        }
      }
      // finally update for traversal
        current = parent;
        parent = parent->getParent();
    }
}



template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
