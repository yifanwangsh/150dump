//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <math.h>
#include <float.h>
#include<limits>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING

#include <iostream>

using namespace std;

bool statistics(const float dataset[], const int size,
                float& min, float& avg, float& max,
	        float& popSD, float& smplSD, float& mdn);

float minimum(const float dataset[], const int size);
float average(const float dataset[], const int size);
float maximum(const float dataset[], const int size);
float popStdDev(const float dataset[], const int size);
float smplStdDev(const float dataset[], const int size);
float median(const float dataset[], const int size);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  

bool statistics(const float dataset[], const int size,
	   float& min, float& avg, float& max,
	   float& popSD, float& smplSD, float& mdn) {
	
	
	
	
	if (size<=0) return 0;
	
	else{ 
		min=minimum(dataset, size);

		avg=average(dataset, size);
 
		max=maximum(dataset, size);
 
		popSD=popStdDev(dataset, size);

		smplSD=smplStdDev(dataset, size);

		mdn=median(dataset, size);
	}	
	
	return 1;
		   
  
}

float minimum(const float dataset[], const int size){
	int j=0;
	int k=0;
	float b=0;
	int i=0;
	float a[size];
	
	for(i=1;i<=size;i++){
		a[i-1]=dataset[i-1];
	}	
	for(j=0; j<=size-1; j++){
		for(k=j; k<=size-1; k++){
			if(a[k]<=a[j]){
				b=a[k];
				a[k]=a[j];
				a[j]=b;
			}	
		}
	}	
	return a[0];	
}

float average(const float dataset[], const int size) {
	int j=0;
	float AVG=0;
	for(j=0; j<=size-1; j++){
		AVG+=dataset[j]/size;
	}
	return AVG;
}

float maximum(const float dataset[], const int size) {
	int j=0;
	int k=0;
	float b=0;
	int i=0;
	float a[size];
	
	for(i=1;i<=size;i++){
		a[i-1]=dataset[i-1];
	}	
	for(j=0; j<=size-1; j++){
		for(k=j; k<=size-1; k++){
			if(a[k]<=a[j]){
				b=a[k];
				a[k]=a[j];
				a[j]=b;
			}	
		}
	}	
	return a[size-1];
}

float smplStdDev(const float dataset[], const int size) {
	int j=0;
	float w_=0;
	int i=0;
	float a[size];
	float AVG =average(dataset,size);
	
	for(i=0;i<=size-1;i++){
		a[i]=dataset[i];
	}	
	
	for(j=0; j<=size-1; j++){
		w_+=(a[j]-AVG)*(a[j]-AVG);
	}
	
	
	if(size!=1) return sqrt(w_/(size-1));	
	else return std::numeric_limits<float>::infinity();
}
	
float popStdDev(const float dataset[], const int size) {
	int j=0;
	float w_=0;
	int i=0;
	float a[size];
	float AVG =average(dataset,size);
	
	for(i=0;i<=size-1;i++){
		a[i]=dataset[i];
	}	
	
	for(j=0; j<=size-1; j++){
		w_+=(a[j]-AVG)*(a[j]-AVG);
	}

	return sqrt(w_/size);
}



float median(const float dataset[], const int size) {
	int j=0;
	int k=0;
	float b=0;
	int i=0;
	float a[size];
	
	for (i=0;i<=size-1; i++){
		
		a[i]=dataset[i];
		
	}	
	
	for(j=0; j<=size-1; j++){
		for(k=j; k<=size-1; k++){
			if(a[k]<=a[j]){
				b=a[k];
				a[k]=a[j];
				a[j]=b;
			}	
		}
	}
	
	if (size%2==1) return a[(size-1)/2];
	else return (a[size/2-1]+a[size/2])/2;
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

int main(const int argc, const char* const argv[]) {
  int size = argc-1;
  float dataset[size];
  float min;
  float avg;
  float max;
  float popStDev;
  float smplStDev;
  float medians;
  
  for(int i=0; i<=size-1;i++){
	  dataset[i]=atof(argv[i+1]);
  }  

  
  if (statistics(dataset, size, min, avg, max, popStDev, smplStDev, medians)) {
    cout << "Minimum: " << min << endl;
	cout << "Average: " << avg << endl;
	cout << "Median:  " << medians << endl;
	cout << "Maximum: " << max << endl;
	cout << "Population Standard Deviation: " << popStDev << endl;
	cout << "Sample Standard Deviation:     " << smplStDev << endl;
  }
  else
    cout << "Error: unable to compute statistics" << endl;

  return 0;
}

#endif
