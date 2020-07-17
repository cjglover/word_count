#ifndef _MAP_H
#define _MAP_H

#include <string>
#include <iostream>

/**
* Christian Glover
* CSCI 104: Spring 2016
* Homework 8 Map interface
*/

/**
* An abstract base class for implementing a Map data structure. Two public functions
* are used to add an element and report the elements in the map. The two Map types
* that need to be implemented for this assignment are a Splay Tree and a Hashtable. 
*
*/
class Map
{
public:
	/**
	* Adds a word to the map. If this is the first time the word
	* has been encountered, it is added with a count of 1. Otherwise,
	* the count for the word is incremented by 1.
	*/
	virtual void add(const std::string& word) = 0;

	/**
	* Reports the contents of the map. Each pair of <word, count> is
	* printed to a new line of the stream. The count should be separated from the 
	* word by a space.
	*/
	virtual void reportAll(std::ostream& output) = 0;

};

#endif