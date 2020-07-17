#include <fstream>
#include <algorithm>
#include "hashtable.h"
using namespace std;

hashtable::hashtable()  {
	for(int i=0;i<11;++i) {
		data.push_back(make_pair<string,int>("NULL",-1));
	}
	load=0;
	indexy=0;
	next_size.push_back(11); //value of sizes for resizing
	next_size.push_back(23); 
	next_size.push_back(41); 
	next_size.push_back(83);
	next_size.push_back(163); 
	next_size.push_back(331); 
	next_size.push_back(641);
	next_size.push_back(1283); 
	next_size.push_back(2579); 
	next_size.push_back(5147);
	next_size.push_back(10243); 
	next_size.push_back(20483); 
	next_size.push_back(40961);
}

void hashtable::add(const string& word) {
	string lword=word;
	std::transform(lword.begin(), lword.end(), lword.begin(), ::tolower);
	int ind= hash(lword);
	unsigned int i=0;
	while(i<data.size()) {
		if(data[(ind+i*i)%data.size()].second==-1) {//if empty bucket found
			data[(ind+i*i)%data.size()]=make_pair<string, int>(lword, 1);
			++load;
			break;
		}
		else if(data[(ind+i*i)%data.size()].first==lword) {//if word is found, increment freq
			data[(ind+i*i)%data.size()]=make_pair<string, int>(lword, 1+data[(ind+i*i)%data.size()].second);
			break;
		}
		else //keep probing
			++i;
	}
	if(data.size()<=2*load)//if resize required
		resize();
}

int hashtable::hash(const string& word) {
	string hashword=word;
	int hashval[14]={0};
	int position =13;
	while(true) {
		long long key=0;
		long long place=1;
		for(int i=1;i<=8;i++) {
			int h_size=hashword.size();
			if(h_size-i<0) {
				break;
			}
			else  {
				key+= (long long)hashword[h_size-i]*(long long)place;
				place*=(long long)128;
			}//creating 128 bit number from 8 chars

		}
		for(int g=0;g<4;g++) {//converting that into base 40961
			hashval[position]=key%((long long)40961);
			key=key/((long long)40961);
			--position;
		}
		if(hashword.size()>8) {//repeat proccess for next 8 char's
			int s=hashword.size();
			hashword.resize(s-8);
		}
		else
			break;
	}
	long long hv=0;//get psuedorandom number
	hv=((long long)(34394 * hashval[0]) + (long long)(36706 * hashval[1]) + (long long)(38074 * hashval[2]) 
		+ (long long)(16351 * hashval[3]) + (long long)(2623 * hashval[4]) + (long long)(10174 * hashval[5]) 
		+ (long long)(22339 * hashval[6]) + (long long)(27779 * hashval[7]) + (long long)(36642 * hashval[8]) 
		+ (long long)(19250 * hashval[9]) + (long long)(36216 * hashval[10]) + (long long)(33514 * hashval[11]) 
		+ (long long)(24019 * hashval[12]) + (long long)(5552 * hashval[13]));
	int d_size=data.size();
	int result= hv%((long long)d_size);
	return result;
}

void hashtable::reportAll (std::ostream& output) {
	for(unsigned int i=0;i<data.size();++i)  {
		if(data[i].second!=-1) {
			output<<data[i].first<<" "<<data[i].second<<endl;
		}
	}
}




 void hashtable::resize() {
 	if(indexy+1==next_size.size()) {
 		return;
 	}
 	++indexy;
 	vector<std::pair<std::string,int> > temp;
 	for(unsigned int i=0;i<data.size();++i){//take out all elements in old hashtable
 		if(data[i].second!=-1)
 			temp.push_back(data[i]);
 	}
 	data.clear();//reset 

 	for(int b=0;b<next_size[indexy];++b)
 		data.push_back(make_pair<string,int>("NULL",-1));

 	for(unsigned int i=0;i<temp.size();++i) {//re add the elements
 		int dex=hash(temp[i].first);
 		unsigned int prob=0;
 		while(prob<data.size()) {//probe to find the appropriate spot
 			if(data[(dex+prob*prob)%data.size()].second==-1) {
				data[(dex+prob*prob)%data.size()]=make_pair<string, int>(temp[i].first, temp[i].second);
				break;
			}
		
			else 
				++prob;

 		}

 	}
 } 	
