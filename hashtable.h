#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Map.h"
#include <vector>


class hashtable : public Map
{
public:
	hashtable();
	void add(const std::string& word);
	void reportAll(std::ostream& output);

private:
	int hash(const std::string& word);
	void resize();
	std::vector<std::pair<std::string,int> > data;
	unsigned int load;
	unsigned int indexy;
	std::vector <int> next_size;
};

#endif
