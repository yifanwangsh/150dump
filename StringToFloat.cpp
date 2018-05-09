//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
// You are allowed float.h

#include<limits>
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

bool stringToFloat(const char input[], float& value);
bool stringToFloatHelper(const char input[], float& value, int& digit_now_operating, int& decimal_place_now_operating, int& flag);
bool stringToInt(const char input[], int& value);
bool stringToIntHelper(const char input[], int& value, int& digit_now_operating);
bool e_string(const char input[], int& value);
//////////////////////////////////////////////////////////////
//
// Your code here ...
bool stringToInt(const char input[], int& value) {
  // Your code here ...
	int digit_now_operating = 0;
	value = 0;
	if(input[digit_now_operating] == 43 || input[digit_now_operating] == 45) digit_now_operating+=1;
	
	return stringToIntHelper(input, value, digit_now_operating);
}

bool stringToIntHelper(const char input[], int& value, int& digit_now_operating){
	if(input[digit_now_operating] >= 48 && input[digit_now_operating] <= 57){
		switch(input[digit_now_operating]){
			case 48:
				value+=0;
				if(value < 0) return false;
				break;
			case 49:
				value+=1;
				if(value < 0) return false;
				break;
			case 50:
				value+=2;
				if(value < 0) return false;
				break;
			case 51:
				value+=3;
				if(value < 0) return false;
				break;
			case 52:
				value+=4;
				if(value < 0) return false;
				break;
			case 53:
				value+=5;
				if(value < 0) return false;
				break;
			case 54:
				value+=6;
				if(value < 0) return false;
				break;
			case 55:
				value+=7;
				if(value < 0) return false;
				break;
			case 56:
				value+=8;
				if(value < 0){
					if(input[0] != 45) return false;
				}	
				break;
			case 57:
				value+=9;
				if(value < 0) return false;
				break;
			default:;
		}
	}
	else{
		return false;
	}
	if(input[digit_now_operating+1] == 0){
		if(input[0] == 43) value*= 1;
		if(input[0] == 45) value*= -1;
		return true;
	}	
	else{
		value*=10;
		if(value < 0) return false;
		digit_now_operating+=1;
		return stringToIntHelper(input, value, digit_now_operating);
	}	
  
}

bool e_string(const char input[], float& value){
	int digit_now_operating = 0;
	while(input[digit_now_operating] != 101 && input[digit_now_operating] != 69){ 
		digit_now_operating++;
	}	
	digit_now_operating++;
	char* e_string = new char[10];
	int e_index = 0;
	int e_value = 0;
	while(input[digit_now_operating] != 0){
		e_string[e_index] = input[digit_now_operating];
		e_index++;
		digit_now_operating++;
	}
	e_string[e_index] = 0;
	if(stringToInt(e_string, e_value)){
		if(e_value> 0){
			for(int i=1; i<=e_value; i++){
				value*=10;
			}
			if(input[0] == 43) value*= 1;
			if(input[0] == 45) value*= -1;
			return true;
		}
		else if(e_value<0){
			for(int i=1; i<=-e_value; i++){
				value=value/10;
			}
			if(input[0] == 43) value*= 1;
			if(input[0] == 45) value*= -1;
			return true;
		}	
	}	
	else{
		return false;
	}
}	


bool stringToFloat(const char input[], float& value){
	int digit_now_operating = 0;
	value = 0;
	int flag = 1;
	int decimal_place_now_operating = 0;
	if(input[digit_now_operating] == 43 || input[digit_now_operating] == 45) digit_now_operating+=1;
	if(input[digit_now_operating] == 46){
		digit_now_operating++;
		flag = 0;
		decimal_place_now_operating++;
	}	
	
	return stringToFloatHelper(input, value, digit_now_operating, decimal_place_now_operating, flag);
}


bool stringToFloatHelper(const char input[], float& value, int& digit_now_operating, int& decimal_place_now_operating, int& flag){
	float decimal_value = 0;
	
	switch(flag){
		case 1:
		switch(input[digit_now_operating]){
			case 48:
				value+=0;
				break;
			case 49:
				value+=1;
				break;
			case 50:
				value+=2;
				break;
			case 51:
				value+=3;
				break;
			case 52:
				value+=4;
				break;
			case 53:
				value+=5;
				break;
			case 54:
				value+=6;
				break;
			case 55:
				value+=7;
				break;
			case 56:
				value+=8;
				break;
			case 57:
				value+=9;
				break;
			default:
				return false;
		}
		if(input[digit_now_operating + 1] == 46){
			flag = 0;
			digit_now_operating+=2;
			decimal_place_now_operating++;
			return stringToFloatHelper(input, value, digit_now_operating, decimal_place_now_operating, flag);
		}
		break;
		
		case 0:
			switch(input[digit_now_operating]){
			case 48:
				decimal_value+=0;
				break;
			case 49:
				decimal_value+=1;
				break;
			case 50:
				decimal_value+=2;
				break;
			case 51:
				decimal_value+=3;
				break;
			case 52:
				decimal_value+=4;
				break;
			case 53:
				decimal_value+=5;
				break;
			case 54:
				decimal_value+=6;
				break;
			case 55:
				decimal_value+=7;
				break;
			case 56:
				decimal_value+=8;
				break;
			case 57:
				decimal_value+=9;
				break;
			default:
				return false;
			}
		for(int i=1; i<=decimal_place_now_operating; i++){
			decimal_value = decimal_value / 10;
		}
		value+= decimal_value;
		decimal_place_now_operating++;
		if(input[digit_now_operating + 1] == 101 || input[digit_now_operating + 1] == 69) return e_string(input, value);
		break;
		default: return false;
	}
	
	
	if(input[digit_now_operating+1] == 0){
		if(input[0] == 43) value*= 1;
		if(input[0] == 45) value*= -1;
		return true;
	}	
	else{
		if(flag == 1) value*=10; 
		digit_now_operating+=1;
		return stringToFloatHelper(input, value, digit_now_operating, decimal_place_now_operating, flag);
	}	
	
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
  
  // Some test driver code here ....
  float argv1;

  if (argc < 2) {
    cerr << "Error: Usage: " << argv[0] << " <float>" << endl;
    return -1;
  }

  if (stringToFloat(argv[1],argv1)) 
    cout << "argv[1] is a float with value: " << argv1 <<endl;
  else
    cout << "argv[1] is not a float. argv[1]: " <<argv[1] << endl;
  return 0;
}

#endif
