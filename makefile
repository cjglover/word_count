all: zipf

zipf: 
	g++ -g -Wall hashtable.cpp splaytree.cpp zipf.cpp -o zipf
	
clean:
	-rm zipf
