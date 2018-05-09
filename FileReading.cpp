//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//


#include <fstream>

using namespace std;
//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>

#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
// Replace "..." in bisectionHelper() with any parameter(s)
// you need to ensure termination when precision and
// minIntervalSize are too tightly specified.
//

int histogram(const char filename[], int histogram[10], 
              const int minAcceptableID, const int maxAcceptableID,
              int*& rejects);
bool stringToInt(const char input[], int& value);
bool stringToIntHelper(const char input[], int& value, int& digit_now_operating);
//////////////////////////////////////////////////////////////
//
// Your code here ...
//  
// Return -1 if you cannot compute the histogram for any
// reason;
// Return 0 if the histogram is correct and there are no
// rejections;
// Return the number of rejects if there are rejected
// records from the file
//
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

int histogram(const char filename[], int histogram[10], 
              const int minAcceptableID, const int maxAcceptableID,
              int*& rejects) {
  // Your code here ...
	if(minAcceptableID > maxAcceptableID) return -1;
	
	if(histogram == NULL) return -1;
	
	const int maxLineLength = 100;
	char line[maxLineLength];
	ifstream data;
	data.open(filename);
	if(!data.is_open()) return -1;
	 
	bool done = false;
	int fileLineNumber = 0;
	int Accepted_ID = 0;
	int grade = 0;
	char* pass_in_value = new char[10];
	int pass_in_value_index = 0;
	int number_of_rejection = 0;
	int relevant_grade = 0;
	int line_index = 0;
	
	for(int i=0; i<10; i++){
		histogram[i] = 0;
	}
	int maxNumErrors = 10;
	rejects = new int[maxNumErrors];
	
	
	while(!done){
		fileLineNumber++;
		if(data.getline(line, maxLineLength)){
		}
		else if(data.eof()){
			return number_of_rejection;
		}	
		else return -1;
		//for whatever above: declare variables and load file
		
		if(line[line_index] == 0) continue;
		
		while(line[line_index] == 32 || line[line_index] == 9){
		line_index++;
		}	//loop through charcters until there is no white space or tab. Note: ASCII: space: 32; horizontal tab: 9
		
		
		do{
			pass_in_value[pass_in_value_index] = line[line_index];
			line_index++;
			pass_in_value_index++;
		}while(line[line_index] != 32 && line[line_index] != 9 && line[line_index] != 44);	//make up the array to pass into StringToInt(STI) function
		pass_in_value[pass_in_value_index] = 0;
			
		if(!stringToInt(pass_in_value, Accepted_ID)) return -1;		//call the STI function, check the input validity 				
		pass_in_value_index = 0;	//one good deal leads to another
			
		
		while(line[line_index] == 32 || line[line_index] == 9 || line[line_index] == 44){
		line_index++;
		}	//loop through charcters, passing space, tab, and that comma
		
		
		do{
			pass_in_value[pass_in_value_index] = line[line_index];
			line_index++;
			pass_in_value_index++;
		}while(line[line_index] != 32 && line[line_index] != 9 && line[line_index] != '\0');	//make up the array to pass into StringToInt(STI) function
		pass_in_value[pass_in_value_index] = 0;
			
		if(!stringToInt(pass_in_value, grade)) return -1;	//call the STI function, check the input validity
		pass_in_value_index = 0;	//one good deal leads to another
		
			
		while(line[line_index] != 0){
			line_index++;
		}	//loop through charcters, until the end of that line	
		//rejects = new int[10];
		if(Accepted_ID < minAcceptableID || Accepted_ID > maxAcceptableID || grade < 0 || grade > 100){
			if(number_of_rejection > maxNumErrors) return -1;
			rejects[number_of_rejection] = fileLineNumber;
			number_of_rejection++;
		}	//check whether ID and grade are in the range. If not, throw line_index to rejects	
		else{	//create the histogram
			relevant_grade = grade/10;	//group by grade;
			switch(relevant_grade){
				case 0:
					histogram[0] += 1;
					break;
				case 1:
					histogram[1] += 1;
					break;
				case 2:
					histogram[2] += 1;
					break;
				case 3:
					histogram[3] += 1;
					break;
				case 4:
					histogram[4] += 1;
					break;
				case 5:
					histogram[5] += 1;
					break;
				case 6:
					histogram[6] += 1;
					break;
				case 7:
					histogram[7] += 1;
					break;
				case 8:
					histogram[8] += 1;
					break;
				case 9:
					histogram[9] += 1;
					break;
				case 10:
					histogram[9] += 1;	//specially for grade 100
					break;
				default:;	
			}
		}
		Accepted_ID = 0;	//for next line
		grade = 0;	//reset
		line_index = 0;	
	}
	delete[] pass_in_value;	
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
  if (argc < 2) {
	cerr << "Error: insufficient input" << endl;
	return -1;
  }
  const int numBuckets = 10;
  const int bucketRange = 100/numBuckets;
  int* buckets = new int[10];
  int* rejectedRecords;
  rejectedRecords = NULL;
  int retCode = histogram(argv[1], buckets, 22200000, 22299999, rejectedRecords);
  if (retCode < 0) {
      cout << "Unable to compute histogram." << endl;
  }
  else {
    for (int i = 0; i < numBuckets; ++i)
      if (i != numBuckets-1)
	cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)-1) << "]: " << buckets[i] << endl;
      else
	cout << "Number [" << i*bucketRange << "," << (((i+1)*bucketRange)) << "]: " << buckets[i] << endl;
    if (retCode > 0) {
      cout << "Number of rejected records: " << retCode << endl;
      cout << "Rejected records are:";
      for (int i = 0; i < retCode; ++i){
	  cout << " " << rejectedRecords[i];
      cout << endl;
	  }
      delete[] rejectedRecords;
    }
  }

  return 0;
}

#endif
