#include <fstream>
#include "splaytree.h"
#include "hashtable.h"
using namespace std;


int main (int argc, char* argv[]) {
	if(argc<3) {
		cout<<"incorrect numver of arguments"<<endl;
		return -1;
	}
	if(argv[1][0]-'0'!=4&&argv[1][0]-'0'!=5) {
		return -1;
	}	
	ifstream infile;
	infile.open(argv[2]);
	if(infile.fail()) {
		cout<<"file not found";
		return -1;
	}
	string word;
	splaytree mysplay;
	hashtable myhash;
	clock_t start;
    double duration;

    start = clock();
    
	if(argv[1][0]-'0'==4){
		while(infile>>word) 
			mysplay.add(word);
		std::ofstream outfile;
		outfile.open("splayoutput.txt");
		mysplay.reportAll(outfile);
	}
	else {
		while(infile>>word) 
			myhash.add(word);
		std::ofstream outfile;
		outfile.open("hashoutput.txt");
		myhash.reportAll(outfile);	
	}

	duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
	if(argv[1][0]-'0'==4)
    std::cout << "splay run time:";
    else
    std::cout << "hash run time:";
    std::cout<<duration << endl;
	

}
