//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <math.h>
//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY);

//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY) {
  // Your code here ...
	float theta_radium = theta * M_PI /180;
	if(v<0 || h<0) return false;
	//if(theta > 90) return false;
	if(b*w < 0) return false;
	//if(d<b || d>(b+w)) return false;
	if(theta == 90){
		destX = 0;
		destY = h;
		return true;
	}

	if(v == 0){
		destX = 0;
		destY = h;
		return true;
	}	
	
	if(theta < 90 && theta > 0){
		float time1 = b/(v*cos(theta_radium));
		float time2 = (b+w)/(v*cos(theta_radium));
		float time = (v*sin(theta_radium)+sqrt((v*sin(theta_radium))*(v*sin(theta_radium))+19.6*h))/9.8;
		float time_on_mass = (v*sin(theta_radium)+sqrt((v*sin(theta_radium))*(v*sin(theta_radium))+19.6*(h-t)))/9.8;
	
		if((h + v*sin(theta_radium)*time1 - 4.9*time1*time1) < t && (h + v*sin(theta_radium)*time1 - 4.9*time1*time1) >= 0){
			destX = b;
			destY = h + v*sin(theta_radium)*time1 - 4.9*time1*time1;
		}
		else if((h + v*sin(theta_radium)*time1 - 4.9*time1*time1) < 0){
			destY = 0;
			destX = v*cos(theta_radium)*time;
		}
		else{
			if((h + v*sin(theta_radium)*time2 - 4.9*time2*time2) < t){
				destX = v*cos(theta_radium)*time_on_mass;
				destY = t;
			}
			else{
				destX = v*cos(theta_radium)*time;
				destY = 0;
			}
		}		
		return true;	
	}
	else if(theta > 90 && theta < 180){
		destY = 0;
		
		float time = (v*sin(theta_radium)+sqrt((v*sin(theta_radium))*(v*sin(theta_radium))+19.6*h))/9.8;
		destX = v*cos(theta_radium)*time;
		return true;
	}
	else return false;
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

  float h = 50;
  float v = 18.4;
  float m = 50;
  float theta = 127.61;        // Angle in degrees; will need to be converted by function
  float d = 100;
  float t = 30;
  float b = 30;
  float w = 50;

  float hitsAtX;
  float hitsAtY;

  if (projectileDestination(h,v,m,theta,d,t,b,w,hitsAtX,hitsAtY))
    cout << "Projectile hit at (" << hitsAtX << ", " << hitsAtY << ")" <<endl;
  else
    cout << "Unable to calculate where projectile hits." << endl;
  return 0;
}

#endif
