 /**
 * bst.h
 *  Implements a(n unbalanced) BST storing Key,Value pairs
 */
#ifndef BST_H
#define BST_H
#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/* -----------------------------------------------------
 * Regular Binary Tree Nodes
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
  class Node {
 public:
  Node (const KeyType & k, const ValueType & v, Node<KeyType, ValueType> *p)
    : _item(k, v)
   // the default is to create new nodes as leaves
    { _parent = p; _left = _right = NULL; }
  
  virtual ~Node()
  { }
  
  std::pair<const KeyType, ValueType> const & getItem () const
    { return _item; }
  
  std::pair<const KeyType, ValueType> & getItem ()
    { return _item; }
  
  const KeyType & getKey () const
  { return _item.first; }
  
  const ValueType & getValue () const
  { return _item.second; }
  
  /* the next three functions are virtual because for AVL-Trees,
     we'll want to use AVL nodes, and for those, the
     getParent, getLeft, and getRight functions should return 
     AVL nodes, not just ordinary nodes.
     That's an advantage of using getters/setters rather than a struct. */
  
  virtual Node<KeyType, ValueType> *getParent () const
    { return _parent; }
  
  virtual Node<KeyType, ValueType> *getLeft () const
    { return _left; }
  
  virtual Node<KeyType, ValueType> *getRight () const
    { return _right; }
  
  
  void setParent (Node<KeyType, ValueType> *p)
  { _parent = p; }
  
  void setLeft (Node<KeyType, ValueType> *l)
  { _left = l; }
  
  void setRight (Node<KeyType, ValueType> *r)
  { _right = r; }
  
  void setValue (const ValueType &v)
  { _item.second = v; }
  
 protected:
  std::pair<const KeyType, ValueType> _item;
  Node <KeyType, ValueType> *_left, *_right, *_parent;
};

/* -----------------------------------------------------
 * Regular Binary Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class BinarySearchTree {
 protected:
  // Main data member of the class
  Node<KeyType, ValueType> *root;

 public:
  /**
   * Constructor
   */
  BinarySearchTree () { root = NULL; }

  /**
   * Destructor
   */
  ~BinarySearchTree () { deleteAll (root); }

  /**
   * Prints the entire tree structure in a nice format 
   *  
   * It will denote subtrees in [] brackets.
   *  This could be helpful if you want to debug your functions. 
   */  
  void print () const
  { 
    printRoot (root);
    std::cout << "\n";
  }
    



  /**
   * An In-Order iterator
   *  !!! You must implement this !!!
   */
  class iterator {
  public:
    /**
     * Initialize the internal members of the iterator
     */
    iterator(Node<KeyType,ValueType>* ptr, BinarySearchTree<KeyType, ValueType>* tr): tree(tr) 
    {curr=ptr;}//constructor, i added a ptr to the iterator's avl/bs tree
    
    std::pair<const KeyType,ValueType>& operator*()
      { return curr->getItem();  }
    
    std::pair<const KeyType,ValueType>* operator->() 
      { return &(curr->getItem()); }
    
    /**
     * Checks if 'this' iterator's internals have the same value
     *  as 'rhs'
     */
    bool operator==(const iterator& rhs) const
    {return (curr==rhs.curr&&tree==rhs.tree);}
    /**
     * Checks if 'this' iterator's internals have a different value
     *  as 'rhs'
     */
    bool operator!=(const iterator& rhs) const
    {return !operator==(rhs);}
    /**
     * Advances the iterator's location using an in-order sequencing
     */
    iterator& operator++()
    {
		if(!curr)
			return (*this);
			
		Node<KeyType, ValueType>* start=curr;
		if(!start->getRight()) {
			Node<KeyType, ValueType>* parnode=start->getParent();
			while(parnode) {
				if(parnode->getLeft()==start)
					break;
				else
					start=parnode;
					parnode=parnode->getParent();
			}
			 curr=parnode;
			
		}
		else {
			start=start->getRight();
			while(start->getLeft())
				start=start->getLeft();
			curr=start;	
		}
		return (*this);
     
     }

     
    
  protected:
      void plushelper( Node<KeyType, ValueType>* node, bool& found) {//find next node is sequence
          if(!node)
              return;
          plushelper(node->getLeft(), found);

          if(curr==node&&!found)
              found=true;
           else if(found) {
              curr=node;
              found=false;
           }

          plushelper(node->getRight(), found);
      }
    Node<KeyType, ValueType>* curr;
    const BinarySearchTree<KeyType, ValueType>* tree;
    //you are welcome to add any necessary variables and helper functions here.

  };
  
  /**
   * Returns an iterator to the "smallest" item in the tree
   */
  iterator begin() 
  {
    iterator begin(get_smallest(root), this);
    return begin;
  } 

  /**
   * Returns an iterator whose value means INVALID
   */
  iterator end() {
      iterator end(0, this);
      return end;
  }
  
 protected:
  /**
   * Helper function to find a node with given key, k and 
   * return a pointer to it or NULL if no item with that key
   * exists
   */
   Node<KeyType, ValueType>* get_smallest(Node<KeyType, ValueType>* n) {
    if(!root)
      return 0;
    if(!n->getLeft())
      return n;
    else
      return get_smallest(n->getLeft());
   }

  Node<KeyType, ValueType>* internalFind(const KeyType& k) const 
  {
    Node<KeyType, ValueType> *curr = root;
    while (curr) {
      if (curr->getKey() == k) {
	return curr;
      } else if (k < curr->getKey()) {
	curr = curr->getLeft();
      } else {
	curr = curr->getRight();
      }
    }
    return NULL;
  }
  
  /**
   * Helper function to print the tree's contents
   */
  void printRoot (Node<KeyType, ValueType> *r) const
  {
    if (r != NULL)
      {
	std::cout << "[";
	printRoot (r->getLeft());
	std::cout << " (" << r->getKey() << ", " << r->getValue() << ") ";
	printRoot (r->getRight());
	std::cerr << "]";
      }
  }
  
  /**
   * Helper function to delete all the items
   */
  void deleteAll (Node<KeyType, ValueType> *r)
  {
    if (r != NULL)
      {
	deleteAll (r->getLeft());
	deleteAll (r->getRight());
	delete r;
      }
  }
};



#endif
