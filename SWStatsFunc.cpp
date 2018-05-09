//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include<math.h>
//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING

#include <iostream>

using namespace std;

int SWStats(const float dataset[], const int size,
	    const int currentSample, const int windowSize,
	    float& min, float& avg, float& max,
	    float& smplSD, float& mdn);

int SWMinimum(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& minimum);
int SWAverage(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& average);
int SWMaximum(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& maximum);
int SWSmplStdDev(const float dataset[], const int size,
		 const int currentSample, const int windowSize,
		 float& smplStdDev);
int SWMedian(const float dataset[], const int size,
	     const int currentSample, const int windowSize,
	     float& median);
#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
	

int SWStats(const float dataset[], const int size,
	    const int currentSample, const int windowSize,
	    float& min, float& avg, float& max,
	    float& smplSD, float& mdn) {
			
			
	if(SWMinimum(dataset, size, currentSample, windowSize, min)==-1||
		SWAverage(dataset, size, currentSample, windowSize, avg)==-1||
		SWMaximum(dataset, size, currentSample, windowSize, max)==-1||
		SWSmplStdDev(dataset, size, currentSample, windowSize, smplSD)==-1||
		SWMedian(dataset, size, currentSample, windowSize, mdn)==-1)
		return -1;
	
	if(SWMinimum(dataset, size, currentSample, windowSize, min)==0||
		SWAverage(dataset, size, currentSample, windowSize, avg)==0||
		SWMaximum(dataset, size, currentSample, windowSize, max)==0||
		SWSmplStdDev(dataset, size, currentSample, windowSize, smplSD)==0||
		SWMedian(dataset, size, currentSample, windowSize, mdn)==0)
		return 1;

	return 0;	

}




int SWMinimum(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& minimum) {
	float a[windowSize];
	
	int j=currentSample;
	int k=0;
	for(int i=1; i<=windowSize; i++){
		a[k]=dataset[j];
		j--;
		k++;
		if (j<0) j++;
	}
	
	float temp=0;
	for (int i=0; i<=windowSize-1; i++){
		for (int j=i; j<=windowSize-1; j++){
			if(a[j]<=a[i]){
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
	
	
	minimum=a[0];
	
	
	if(size<=0||currentSample<0||windowSize<=0) return -1;
	if(windowSize>=size || windowSize==1) return 0;
	else return 1; 
}




int SWAverage(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& average) {
	average=0;
	int j=currentSample;
	for(int i=1; i<=windowSize; i++){
		average+=dataset[j]/windowSize;
		j--;
		if (j<0) j++;
	}
	
	if(size<=0||currentSample<0||windowSize<=0) return -1;
	if(windowSize>=size || windowSize==1) return 0;
	else return 1; 
}




int SWMaximum(const float dataset[], const int size,
	      const int currentSample, const int windowSize,
	      float& maximum) {
	float a[windowSize];
	int j=currentSample;
	int k=0;
	for(int i=1; i<=windowSize; i++){
		a[k]=dataset[j];
		j--;
		k++;
		if (j<0) j++;
	}
	
	float temp=0;
	for (int i=0; i<=windowSize-1; i++){
		for (int j=i; j<=windowSize-1; j++){
			if(a[j]<=a[i]){
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
	
    
	maximum=a[windowSize-1];
	
	
	if(size<=0||currentSample<0||windowSize<=0) return -1;
	if(windowSize>=size || windowSize==1) return 0;
	else return 1; 	
}




int SWSmplStdDev(const float dataset[], const int size,
		 const int currentSample, const int windowSize,
		 float& smplStdDev) {
	/* int j=currentSample;
	float average=0;
	if(currentSample-windowSize+1>0){
		for(int i=1; i<=windowSize; i++){
			average+=dataset[j]/windowSize;
			j--;
		}
	
		float smpl=0;
		j=currentSample;
		for(int i=1; i<=windowSize; i++){
			smpl=(dataset[j]-average)*(dataset[j]-average);
			j--;
			if (j<0) j++;
		}
		smplStdDev=sqrt(smpl/(windowSize-1));
	}
	
	else{
		for(int j=currentSample; j>=0; j--){
			average+=dataset[j]/(currentSample+1);
		}
		
		float smpl=0;
		
		for(int j=currentSample; j>=0; j--){
			smpl+=(dataset[j]-average)*(dataset[j]-average);
		}
		
		smplStdDev=sqrt(smpl/(currentSample+1));
		
	} */
	
	int j=currentSample;
	float average=0;
	for(int i=1; i<=windowSize; i++){
		average+=dataset[j]/windowSize;
		j--;
		if (j<0) j++;
	}
	
	float smpl=0;
	j=currentSample;
	for(int i=1; i<=windowSize; i++){
		smpl+=(dataset[j]-average)*(dataset[j]-average);
		j--;
		if (j<0) j++;
	}
	
	smplStdDev=sqrt(smpl/(windowSize-1));
	
	if(size<=0||currentSample<0||windowSize<=0) return -1;
	if(windowSize>=size || windowSize==1) return 0;
	else return 1; 
}




int SWMedian(const float dataset[], const int size,
	     const int currentSample, const int windowSize,
	     float& median) {
	/* float a[windowSize];
	int j=currentSample;
	int k=0;
	for(int i=1; i<=windowSize; i++){
		a[k]=dataset[j];
		j--;
		k++;
		if (j<0) j++;
	} 
	
	float temp=0;
	for (int i=0; i<=windowSize-1; i++){
		for (int j=i; j<=windowSize-1; j++){
			if(a[j]<=a[i]){
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
	if(currentSample-windowSize+1>0){
		if(windowSize%2==1) median=a[(windowSize-1)/2];
		else median=(a[windowSize/2]+a[windowSize/2-1])/2;
	}
	else{
		if(currentSample%2==1) median=(a[(currentSample+1)/2]+a[(currentSample-1)/2])/2;
		else median=a[currentSample/2];
	} */
	
	float a[windowSize];
	int j=currentSample;
	int k=0;
	for(int i=1; i<=windowSize; i++){
		a[k]=dataset[j];
		j--;
		k++;
		if (j<0) j++;
	} 
	
	float temp=0;
	for (int i=0; i<=windowSize-1; i++){
		for (int j=i; j<=windowSize-1; j++){
			if(a[j]<=a[i]){
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
	if(currentSample!=0){
		if(windowSize%2==1) median=a[(windowSize-1)/2];
		else median=(a[windowSize/2]+a[windowSize/2-1])/2;
	}
	else median=a[0];
	if(size<=0||currentSample<0||windowSize<=0) return -1;
	if(windowSize>=size || windowSize==1) return 0;
	else return 1; 
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
  int size = atoi(argv[1]);
  float dataset[argc-2];
  for(int k=0; k<=argc-2; k++){
	 dataset[k]=atof(argv[k+2]); 
  }
  
  int windowSize = 4;
  int currentSample = 0;
  float min;
  float avg;
  float max;
  float smplSD;
  float median;

  cout << "Sample \t Minimum \t Average \t Median \t Maximum \t Sample Standard Deviation" << endl;

  while (currentSample < size) {
    int retCode = SWStats(dataset, size, currentSample, windowSize, min, avg, max, smplSD, median);
    if (retCode >= 0) {
      cout << currentSample << "\t " << min << "\t " << avg << "\t " << median << "\t " << max << "\t " << smplSD << endl;
      if (retCode > 0)
	cerr << "Warning: something weird happened, but we computed stats anyway ... YMMV" << endl;
    }
    else {
      cerr << "Error: unable to compute sliding-window statistics; exiting" << endl;
      return(-1);
    }
    ++currentSample;
  }
  return 0;
}

#endif
