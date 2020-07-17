#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include "Map.h"
#include "bst.h"

class splaytree : public Map, public BinarySearchTree <std::string, int>
{
public:	
	splaytree();
	void add(const std::string& word);
	void reportAll(std::ostream& output);
private:
	void insert (const std::pair<const std::string, int>& new_item);
	void splayinsert (const std::pair<const std::string, int>& new_item, Node<std::string,int>* node);
	void splay (Node<std::string,int>* node);
	void r_splay(Node<std::string,int>* node);
	void l_splay(Node<std::string,int>* node);
	void rl_splay(Node<std::string,int>* node);
	void lr_splay(Node<std::string,int>* node);
	void rootr_splay(Node<std::string,int>* node);
	void rootl_splay(Node<std::string,int>* node);
	
};

#endif
