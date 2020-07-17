#include "splaytree.h"
#include <algorithm>
#include <stdexcept>
using namespace std;

splaytree::splaytree() {}

void splaytree::add(const std::string& word) {
	string lword=word;
	std::transform(lword.begin(), lword.end(), lword.begin(), ::tolower);
	this->splaytree::insert(make_pair<string, int>(lword,1));	
	
}

void splaytree::reportAll(std::ostream& output) {

	BinarySearchTree::iterator it= this->begin();
	for(;it!=this->end();++it) {
		output<<(*it).first<<" "<<(*it).second<<endl;
	}
	
}


void splaytree::insert (const std::pair<const string, int>& new_item) {

      if(!this->root){//if the tree is empty
          this->root=new Node<string,int>(new_item.first, new_item.second, 0);
          this->root->setParent(0);
      }
       else
        splayinsert(new_item, this->root);
  }



void splaytree::splayinsert (const std::pair<const string, int>& new_item, Node<string,int>* node) {


	  if(node->getItem().first==new_item.first) {
	  		node->setValue(node->getValue()+1);
	  		splay(node);
	  }

      else if(node->getItem().first>new_item.first) {//run down tree to find place to insert
          if(!node->getLeft()) {
            Node<string, int>* newnode= new Node<string,int>(new_item.first,new_item.second, node);
            node->setLeft(newnode);//if we find location, insert node and

            splay(newnode);//rebalance
          }
          else {
            splayinsert(new_item, node->getLeft());//or else keep looking for insert location
          }
      }    
      else {
        if(!node->getRight()) {
            Node<string, int>* newnode= new Node<string,int>(new_item.first,new_item.second, node);
            node->setRight(newnode);

            splay(newnode);
          }
          else {
            splayinsert(new_item, node->getRight());
          }

      }

  }

void splaytree::splay(Node<string,int>* node) {
	

	while(node->getParent()) {
		
		Node<string,int>* parnode=node->getParent();
		

		if(parnode->getParent()) {
			if(node==parnode->getRight()&&parnode->getParent()->getRight()==parnode)
				r_splay(node);
			else if(node==parnode->getLeft()&&parnode->getParent()->getLeft()==parnode)
				l_splay(node);
			else if(node==parnode->getLeft()&&parnode->getParent()->getRight()==parnode)
				rl_splay(node);
			else
				lr_splay(node);

		}
		else {
			if(node==parnode->getRight())
				rootr_splay(node);
			else if(node==parnode->getLeft())
				rootl_splay(node);
		}


	}

}  


void splaytree::r_splay(Node<string,int>* node) {
		


		Node<string,int>* parnode=node->getParent();
		Node<string,int>* ancestor=parnode->getParent();
		ancestor->setRight(parnode->getLeft());
		if(ancestor->getRight())
			ancestor->getRight()->setParent(ancestor);
		parnode->setRight(node->getLeft());
		if(node->getLeft())
			node->getLeft()->setParent(parnode);
		node->setLeft(parnode);
		parnode->setParent(node);
		node->setParent(ancestor->getParent());
		parnode->setLeft(ancestor);
		ancestor->setParent(parnode);
		if(node->getParent()){
			if(ancestor==node->getParent()->getLeft())
				node->getParent()->setLeft(node);
			else
				node->getParent()->setRight(node);

		}
		else
			this->root=node;


		


}

void splaytree::l_splay(Node<string,int>* node) {
	

		Node<string,int>* parnode=node->getParent();
		Node<string,int>* ancestor=parnode->getParent();
		ancestor->setLeft(parnode->getRight());
		if(ancestor->getLeft())
			ancestor->getLeft()->setParent(ancestor);
		parnode->setLeft(node->getRight());
		if(node->getRight())
			node->getRight()->setParent(parnode);
		node->setRight(parnode);
		parnode->setParent(node);
		node->setParent(ancestor->getParent());
		parnode->setRight(ancestor);
		ancestor->setParent(parnode);

		if(node->getParent()){
			if(ancestor==node->getParent()->getLeft())
				node->getParent()->setLeft(node);
			else
				node->getParent()->setRight(node);
		}

		else
			this->root=node;


		
		
}

void splaytree::rl_splay(Node<string,int>* node)  {
	

	Node<string,int>* parnode=node->getParent();
	Node<string,int>* ancestor=parnode->getParent();
	ancestor->setRight(node->getLeft());
	if(node->getLeft())
		node->getLeft()->setParent(ancestor);
	parnode->setLeft(node->getRight());
	if(node->getRight())
		node->getRight()->setParent(parnode);
	node->setParent(ancestor->getParent());
	node->setLeft(ancestor);
	ancestor->setParent(node);
	node->setRight(parnode);
	parnode->setParent(node);
	if(node->getParent()){
		if(ancestor==node->getParent()->getLeft())
			node->getParent()->setLeft(node);
		else
			node->getParent()->setRight(node);

	}
	else
		this->root=node;






}

void splaytree::lr_splay(Node<string,int>* node)  {
	
	Node<string,int>* parnode=node->getParent();
	Node<string,int>* ancestor=parnode->getParent();
	ancestor->setLeft(node->getRight());
	if(node->getRight())
		node->getRight()->setParent(ancestor);
	parnode->setRight(node->getLeft());
	if(node->getLeft())
		node->getLeft()->setParent(parnode);
	node->setParent(ancestor->getParent());
	node->setLeft(parnode);
	parnode->setParent(node);
	node->setRight(ancestor);
	ancestor->setParent(node);
	if(node->getParent()){
		if(ancestor==node->getParent()->getLeft())
			node->getParent()->setLeft(node);
		else
			node->getParent()->setRight(node);

	}
	else
		this->root=node;





}

void splaytree::rootr_splay(Node<string,int>* node) {
	

	Node<string,int>* parnode=node->getParent();
	parnode->setRight(node->getLeft());
	if(node->getLeft())
		node->getLeft()->setParent(parnode);
	node->setLeft(parnode);
	parnode->setParent(node);
	node->setParent(0);
	this->root=node;






}

void splaytree::rootl_splay(Node<string,int>* node) {
	

	Node<string,int>* parnode=node->getParent();
	parnode->setLeft(node->getRight());
	if(node->getRight())
		node->getRight()->setParent(parnode);
	node->setRight(parnode);
	parnode->setParent(node);
	node->setParent(0);
	this->root=node;








}



