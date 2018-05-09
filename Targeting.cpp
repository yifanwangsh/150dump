//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <math.h>
#include <limits>
//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//


#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

#define NaN std::numeric_limits<float>::quiet_NaN() 
#define isNaN(X) (X != X) // NaN is the only float that is not equal to itself

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove

bool hitTargetGivenVelocity (const float h, const float v, const float m,
							 const float d, const float t, const float b, 
							 const float w, float& theta);
							 
bool hitTargetGivenAngle (const float h, const float m, const float theta, 
							const float d, const float t, const float b, 
							const float w, float& v);

//////////////////////////////////////////////////////////////
//
// Your code here ...
// 
 

bool hitTargetGivenVelocity (const float h, const float v, const float m,
							 const float d, const float t, const float b, 
							 const float w, float& theta) {
	// Your code here...
	theta = 0;
	if(v <= 0 || h < 0 || b < 0 || w < 0 || d < 0) return false;
	if(t >= 0){
		theta = atan((d + d/v*sqrt(v*v + 19.6*h-19.6*t - 9.8*9.8*d*d/v/v))/(9.8*d*d/v/v));
		if(isNaN(theta)) return false;
		theta = theta*180/M_PI;
		return true;
	}
	else{
		theta = atan((d + d/v*sqrt(v*v + 19.6*h-19.6*t - 9.8*9.8*d*d/v/v))/(9.8*d*d/v/v));
		if(isNaN(theta)) return false;
		if(b*tan(theta)-4.9*b*b/(v*cos(theta))/(v*cos(theta))+h <= 0) return false;
		else{
			theta = theta*180/M_PI;
			return true;
		}		
	}	
}

bool hitTargetGivenAngle (const float h, const float m, const float theta, 
							const float d, const float t, const float b, 
							const float w, float& v) {
	// Your code here...
	v = 0;
	if(theta > 90  || h < 0 || b < 0 || w < 0 || d < 0) return false;
	float  theta_radium = theta*M_PI/180;
	v = sqrt((4.9*d*d)/(cos(theta_radium)*cos(theta_radium)*(h-t+d*tan(theta_radium))));
	return true;
}		


#ifndef MARMOSET_TESTING
int main() {
	
  // Some test driver code here ....
  
  float h = 50;
  float d = 60;
  float b = 40;
  float t = 0;
  float w = 30;
  float m = 0.5;

  float theta = 68.81; // Angle in degrees;
  float v = 0 ;	

  cout << "Given angle: " << theta << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;
  if (hitTargetGivenAngle (h, m, theta, d, t, b, w, v)) {
    cout << "required initial velocity: " << v << endl << endl;
  }
  else {
    cout << "cannot calculate the velocity\n\n";
  }
	v = 41.8 ;	
  cout << "Given initial velocity: " << v << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;
  if (hitTargetGivenVelocity (h, v, m, d, t, b, w, theta)) {
    cout << "required angle8 " << theta << endl << endl;
  }
  else {
    cout << "cannot calculate the angle\n\n";  
  }
    
  return 0;
}
#endif
