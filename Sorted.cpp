//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <limits>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
#include<stdlib.h>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// #defines, enum, and function declarations; do not remove
//

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself
#define NaN std::numeric_limits<float>::quiet_NaN() // (comes from <limits>)

enum sortType { ASCENDING, DESCENDING, UNKNOWN, UNSORTED };

bool isSorted(const float data[], const int currentDataItem, const sortType typeOfSort);
bool sorted(const float data[]);

//////////////////////////////////////////////////////////////
//
// Your code here ...
// 
//

bool isSorted(const float data[], const int currentDataItem, const sortType typeOfSort) {
	if (isNaN(data[currentDataItem + 1]) ){
		return true;
	}	
	switch(typeOfSort){
	case ASCENDING:
		if(data[currentDataItem+1] >= data[currentDataItem]){
			return isSorted(data, currentDataItem+1, ASCENDING);
		}
		else return false;
		
	case DESCENDING:
		if(data[currentDataItem+1] <= data[currentDataItem]){
			return isSorted(data, currentDataItem+1, DESCENDING);
		}
		else return false;
	}

		
}

bool sorted(const float data[]) {
	int i=0;
	do{
		if(data[i+1] > data[i]){
			return isSorted(data,i+1,ASCENDING);
		}
		if(data[i+1] < data[i]){
			return isSorted(data,i+1,DESCENDING);
		}
		i++;
		if(isNaN(data[i+1]) ) return 1;
	}while(1==1);	
}
	
//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING

int main(const int argc, const char* const argv[]){
	float data[argc];
	for(int i=0;i<=argc-2; i++){
		data[i] = atof(argv[i+1]);
	}  
  
	data[argc-1] = NaN;
	/* bool a = NaN > data[0];
	cout << a << endl; */
	if(sorted(data))
		cout << "Data is sorted" << endl;
	else
		cout << "Data is not sorted" << endl;
	return 0;
}

#endif

