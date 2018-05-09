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
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

int range(const int dataset[], const int size);
int mode(const int dataset[], const int size, int mode[]);
bool sort(int dataset[], const int size);
void merge(int* dataset, const int left, const int right);
void msort(int* dataset, const int left, const int mid, const int right);
//////////////////////////////////////////////////////////////
//
// Your code here ...
//  Return -1 if there there are any problems with the dataset.
//
#define isNaN(X) (X != X) 
int range(const int dataset[], const int size){
	int pass_data[size];
	
	if(size <= 0 ) return -1;
	
	for(int i=0; i<=size-1; i++){
		pass_data[i] = dataset[i];
	}
	
	if(sort(pass_data, size)){
		return pass_data[size-1]-pass_data[0];
	}
}


int mode(const int dataset[], const int size, int mode[]){
	int pass_data[size];
	for(int i=0; i<=size-1; i++){
		pass_data[i] = dataset[i];
	}
	
	sort(pass_data, size);
	
	int number_count = 0;
	int count = 1;
	int temp_count = 1;
	int j = -1;
	pass_data[size] = std::numeric_limits<float>::quiet_NaN();
	for(int i=0; i<=size-1; i++){
		if(pass_data[i] == pass_data[i+1]){
			temp_count+=1;
		}
		else{
			if(temp_count > count){
				count = temp_count;
				mode[0] = pass_data[i];
				j = 0;
				number_count = 1;
			}
			else if(temp_count == count){
				j++;
				mode[j] = pass_data[i];
				number_count+=1;
			}	
			temp_count = 1;
		}
	}
	
	
	
	
	return number_count;
}


bool sort(int dataset[], const int size){
	merge(dataset, 0, size-1);
	return true;
}

void merge(int* dataset, int left, int right){
	if(left >= right) return;
	
	int mid = (left+right)/2;
	
	merge(dataset, left, mid);
	merge(dataset, mid+1, right);
	msort(dataset, left, mid, right);
	
}

void msort(int* dataset, int left, int mid, int right){
	if(left >= mid || mid+1 >= right) return;
 	
	int left_index = left;
	int mid_index = mid+1;
	int merge_index = 0;
	int* merge_dataset = new int[right-left+1];
	
	while(left_index <= mid && mid_index <= right){
		if(dataset[left_index] < dataset[mid_index]){
			merge_dataset[merge_index] = dataset[left_index];
			left_index++;
			merge_index++;
		}
		else{
			merge_dataset[merge_index] = dataset[mid_index];
			mid_index++;
			merge_index++;
		}
	}

	while(left_index<= mid){
		merge_dataset[merge_index] = dataset[left_index];
		left_index++;
		merge_index++;
	}

	while(mid_index <= right){
		merge_dataset[merge_index] = dataset[mid_index];
		mid_index++;
		merge_index++;
	}

	for(int i=0; i< right-left+1; i++){
		dataset[i+left] = merge_dataset[i];
	}	
}		
/* void merge(int* dataset, int left, int right){
	if(left >= right) return;
	
	int mid = (left + right)/2;
	merge(dataset, left, mid);
	merge(dataset, mid+1, right);
	msort(dataset, left, mid, right);
}

void msort(int* dataset,const int left,const int mid,const int right){
	if(left >mid || mid > right) return;
	
	int left_index = left;
	int right_index = right;
	int mid_index = mid+1;
	int mergedata_index = 0;
	int mergedata[right-left+1];
	
	
	while(left_index <= mid && mid_index <= right){
		if(dataset[left_index] <= dataset[mid_index]){
			mergedata[mergedata_index] = dataset[left_index];
			left_index++;
		}
		else{
			mergedata[mergedata_index] = dataset[mid_index];
			mid_index++;
		}
		mergedata_index++;
	}
	
	while(left_index <= mid){
		mergedata[mergedata_index] = dataset[left_index];
		left_index++;
		mergedata_index++;
	}

	while(mid_index <= right){
		mergedata[mergedata_index] = dataset[mid_index];
		mid_index++;
		mergedata_index++;
	}
	
	left_index = left;
	for(int i=0;i<=mergedata_index-1;i++){
		dataset[left_index + i] = mergedata[i];
	}
}  */


/* void merge(int* dataset, int left, int right){
	if(left >= right) return;
	
	int mid = (left + right)/2;
	
	merge(dataset, left, mid);
	merge(dataset, mid+1, right);
	msort(dataset, left, mid, right);
}

void msort(int* dataset, int left, int mid, int right){
	if(left > mid || mid > right) return;
	
	int left_index = left;
	int mid_index = mid+1;
	int right_index = right;
	int sortsize = right - left + 1;
	int sorted[sortsize];
	int sorting_index = 0;
	
	while(left_index <= mid && mid_index <= right_index){
		if(dataset[left_index] <= dataset[mid_index]){
			sorted[sorting_index] = dataset[left_index];
			left_index++;
		}
		else{
			sorted[sorting_index] = dataset[mid_index];
			mid_index++;
		}
		
		sorting_index++;
	}
	
	
	while(mid_index <= right_index){
		sorted[sorting_index] = dataset[mid_index];
		sorting_index++;
		mid_index++;
	}		
	
	while(left_index <= mid){
		sorted[sorting_index] = dataset[left_index];
		sorting_index++;
		left_index++;
	}
	
	
	for(int j=0; j<=sortsize-1; j++){
		dataset[j+left] = sorted[j];
	}	
}	
	 */
//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING

int main(const int argc, const char* const argv[]) {
  
  // Some test driver code here ....
  int data[argc-1];
  int size = argc-1;
  //change this to however many modes you expect to find
  int* modeArray;
  
  for(int i=0; i<=argc-2; i++){
	  data[i] = atoi(argv[i+1]);
  }  
  int rng = range(data, size);
  int modes = mode(data, size, modeArray);
  cout << "range: " << rng << " number of Modes: " << modes << " Modes are this: ";
   for(int i = 0; i<modes;i++){
  	cout<< modeArray[i];
  	if(i<modes-1){
  		cout << ", ";
  	}
  }
  cout<<endl;    
  return 0;
}

#endif
