
//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <limits>
#include <limits.h>
#include <float.h>
//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;


// Sample function for which you need to find the root

float f(const float x) {
  return 1-x*x;//3.2*x*x*x - 2.1*x - 23.0;
}

#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//
#define isNaN(X) (X != X) 
float bisectionHelper(const float left, const float right,
		      const float precision, const float minIntervalSize,
		      int iterated_time );
float bisection(const float left, const float right,
		const float precision, const float minIntervalSize);
//#endif

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

float bisectionHelper (const float left, const float right,
		      const float precision, const float minIntervalSize,
		      int iterated_time){
	if(precision <= 0 || minIntervalSize <= 0) return std::numeric_limits<float>::quiet_NaN();
	
	if(isNaN(f(left))|| isNaN(f(right))) return std::numeric_limits<float>::quiet_NaN();
	
	float midpoint = (right + left)/2.0;
	
	int iterating=iterated_time+ 1;
	if(iterating >=10000) return midpoint;
	//limit the calling of function
	
	if(left > right){
		return std::numeric_limits<float>::quiet_NaN();
	}	
	
	if(f(left) * f(right) > 0){
		return std::numeric_limits<float>::quiet_NaN();
	}  
	//whether it is calculable

	if(f(left) == 0) return left;
	
	if(f(right) == 0) return right;
	
	if( right - left < minIntervalSize ||(-precision <= f(midpoint))&&(f(midpoint) <= precision)){
		return midpoint;
	}
	
	
	if(f(midpoint)*f(right) < 0){
		return bisectionHelper(midpoint, right, precision, minIntervalSize, iterating);
	}
	else{
		return bisectionHelper(left, midpoint, precision,minIntervalSize, iterating);
	}
	
}	
	

float bisection(const float left, const float right,
		const float precision, const float minIntervalSize) {
	int iteration = 0;		
	return bisectionHelper(left, right, precision, minIntervalSize, iteration);
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

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
  
  // Some test driver code here ....
  float left = atof(argv[1]);
  float right = atof(argv[2]);
  float precision = atof(argv[3]);
  float minIntervalSize = atof(argv[4]);
  cout << bisection(left, right, precision, minIntervalSize) << endl;

  return 0;
}

#endif
