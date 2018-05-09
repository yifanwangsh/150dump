//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <limits>
#include <math.h>
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
							 
bool hitTargetGivenAngle (const float h, const float m, const float theta, 
              const float d, const float step, const float k,
              const float t, const float b, const float w, float& v);
float bisectionHelper (const float h, const float m, const float theta, 
					   const float d, const float t, const float step, const float k, const float b, 
					   const float w, const float left, const float right,
					   const float precision, const float minIntervalSize,
					   int iterated_time);
float bisection(const float h, const float m, const float theta, 
				const float d, const float t, const float step, const float k, const float b, 
				const float w, const float left, const float right,
				const float precision, const float minIntervalSize);
float hitTargetGivenAngleHelper (const float h, const float m, const float theta, 
							const float d, const float t, const float step, const float k, const float b, 
							const float w, float v);
bool hitTargetGivenAngleCheck(const float h, const float m, const float theta, 
							const float d, const float t, const float step, const float k, const float b, 
							const float w, float v);							
//////////////////////////////////////////////////////////////
//
// Your code here ...
//  

bool hitTargetGivenAngle (const float h, const float m, const float theta, 
							const float d, const float step, const float k,
              const float t, const float b, const float w, float& v) {
	if(m <= 0 || step <= 0 || h < 0 || b < 0 || w < 0 || d < 0 || k < 0 || theta >= 90) return false;
	
	float theta_radius = theta * M_PI /180;
	v = bisection(h,m,theta_radius,d,t,step,k,b,w,10,100,0.01,0.01);
	if(hitTargetGivenAngleCheck(h,m,theta_radius,d,t,step,k,b,w,v))  return true;
	else return false;
}

float bisectionHelper (const float h, const float m, const float theta, 
					   const float d, const float t, const float step, const float k, const float b, 
					   const float w, const float left, const float right,
					   const float precision, const float minIntervalSize,
					   int iterated_time){
	if(precision <= 0 || minIntervalSize <= 0) return std::numeric_limits<float>::quiet_NaN();
	
	//cout << "# iteration: " << iterated_time << endl;
	
	float check = hitTargetGivenAngleHelper(h,m,theta,d,t,step,k,b,w,left);
	float check2 = hitTargetGivenAngleHelper(h,m,theta,d,t,step,k,b,w,right);
	
	/* if( (isNaN(hitTargetGivenAngleHelper(h,m,theta,d,t,step,k,b,w,left))) || 
		(isNaN(hitTargetGivenAngleHelper(h,m,theta,d,t,step,k,b,w,right))) ) {
			return NaN;
		} */
	
	
	
	if (isNaN(check) || isNaN(check2))
		return NaN;
	
	float midpoint = (right + left)/2.0;
	
	int iterating=iterated_time+ 1;
	if(iterating >=100) return midpoint;
	//limit the calling of function
	
	if(left > right){
		return std::numeric_limits<float>::quiet_NaN();
	}	
	/*
	if(hitTargetGivenAngleHelper(h,m,theta,d,t,step,k,b,w,left) * hitTargetGivenAngleHelper(h,m,theta,d,t,step,k,b,w,right) > 0){
		return std::numeric_limits<float>::quiet_NaN();
	} 
*/	
	//whether it is calculable

	if(hitTargetGivenAngleHelper(h,m,theta,d,t,step,k,b,w,left) == 0) return left;
	check = hitTargetGivenAngleHelper(h,m,theta,d,t,step,k,b,w,left);
	if(hitTargetGivenAngleHelper(h,m,theta,d,t,step,k,b,w,right) == 0) return right;
	check2 = hitTargetGivenAngleHelper(h,m,theta,d,t,step,k,b,w,left);
	
	if(right - left < minIntervalSize ||(-precision <= hitTargetGivenAngleHelper(h,m,theta,d,t,step,k,b,w,midpoint))&&(hitTargetGivenAngleHelper(h,m,theta,d,t,step,k,b,w,midpoint) <= precision)){
		return midpoint;
	}
	
	
	if(hitTargetGivenAngleHelper(h,m,theta,d,t,step,k,b,w,midpoint)*hitTargetGivenAngleHelper(h,m,theta,d,t,step,k,b,w,right) < 0){
		return bisectionHelper(h,m,theta,d,t,step,k,b,w,midpoint, right, precision, minIntervalSize, iterating);
	}

	else{
		return bisectionHelper(h,m,theta,d,t,step,k,b,w,left, midpoint, precision,minIntervalSize, iterating);
	}
	
}	
	

float bisection(const float h, const float m, const float theta, 
				const float d, const float t, const float step, const float k, const float b, 
				const float w, const float left, const float right,
				const float precision, const float minIntervalSize) {
	int iteration = 0;		
	return bisectionHelper(h,m,theta,d,t,step,k,b,w,left, right, precision, minIntervalSize, iteration);
}


float hitTargetGivenAngleHelper (const float h, const float m, const float theta, 
							const float d, const float t, const float step, const float k, const float b, 
							const float w, float v) {
	// Your code here...
	float horizontal_acceleration = v*cos(theta);
	float vertical_acceleration = v*sin(theta);
	float destX = 0;
	float destY = h;
	float velocity_theta = theta;
	float horizontal_velocity = v*cos(theta);
	float vertical_velocity = v*sin(theta);
	float instant_velocity = 0;
	int counter = 0;
	while(destX < d && counter <= 10000){
		velocity_theta = atan(vertical_velocity/horizontal_velocity);
		instant_velocity = sqrt(horizontal_velocity*horizontal_velocity+vertical_velocity*vertical_velocity);
		
		horizontal_acceleration = -(k*instant_velocity*instant_velocity/m)*cos(velocity_theta);
		vertical_acceleration = -(k*instant_velocity*instant_velocity/m)*sin(velocity_theta) - 9.8;
		
		destX+=horizontal_velocity*step;
		destY+=vertical_velocity*step;
		
		horizontal_velocity+=horizontal_acceleration*step;
		vertical_velocity+=vertical_acceleration*step;
		counter++;
	}

	return destY - t;
}

bool hitTargetGivenAngleCheck (const float h, const float m, const float theta, 
							const float d, const float t, const float step, const float k, const float b, 
							const float w, float v) {
	float horizontal_acceleration = v*cos(theta);
	float vertical_acceleration = v*sin(theta);
	float destX = 0;
	float destY = h;
	float velocity_theta = theta;
	float horizontal_velocity = v*cos(theta);
	float vertical_velocity = v*sin(theta);
	float instant_velocity = 0;

	while(destX < d){
		velocity_theta = atan(vertical_velocity/horizontal_velocity);
		instant_velocity = sqrt(horizontal_velocity*horizontal_velocity+vertical_velocity*vertical_velocity);
		
		horizontal_acceleration = -(k*instant_velocity*instant_velocity/m)*cos(velocity_theta);
		vertical_acceleration = -(k*instant_velocity*instant_velocity/m)*sin(velocity_theta) - 9.8;
		
		destX+=horizontal_velocity*step;
		destY+=vertical_velocity*step;
		
		horizontal_velocity+=horizontal_acceleration*step;
		vertical_velocity+=vertical_acceleration*step;
		if(destY <= -1 && (destX < b || destX > b+w)) return false;
		if(destX >= b && destY <= t-1) return false;
		
	}
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
  float step = 0.01;
  float k = 0.00856;
  float theta = 45; // Angle in degrees;
  float v = 25;	

  cout << endl << "Given angle: " << theta << endl;
  cout << "Target at (" << d << "," << t << ")" << endl;
  if (hitTargetGivenAngle (h, m, theta, d, step, k, t, b, w, v)) {
    cout << "required initial velocity: " << v << endl << endl;
  }
  else {
    cout << "cannot calculate the velocity" << endl << endl;
  }
    
  return 0;
}
#endif
