//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//


#include <fstream>
#include <limits>
#include <math.h>
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
#ifndef MARMOSET_TESTING
struct Student{
	int studentID;
	int grade;
};

struct Dataset{
	int numStudents;
	Student* students;
};

struct Rejects{
	int numRejects;
	int* rejects;
};

struct Mode{
	int numModes;
	int* modes;
};

struct Statistics{
	int   minimum;
	float average;
	int   maximum;
	float popStdDev;
	float smplStdDev;
	Mode  mode;
	int   histogram[10];
};
#endif


int readCSV(const char filename[], const int minAcceptableID, const int maxAcceptableID, Dataset& data, Rejects& rejects);
int computeStatistics(Dataset& data, Statistics& stats);
int writeCSV(const char filename[], const Statistics& stats);
bool stringToInt(const char input[], int& value);
bool stringToIntHelper(const char input[], int& value, int& digit_now_operating);
bool statistics(const float dataset[], const int size, float& min, float& avg, float& max,float& popSD, float& smplSD);
bool sort(int dataset[], const int size);
void merge(int* dataset, const int left, const int right);
void msort(int* dataset, const int left, const int mid, const int right);
float minimum(const float dataset[], const int size);
float average(const float dataset[], const int size);
float maximum(const float dataset[], const int size);
float popStdDev(const float dataset[], const int size);
float smplStdDev(const float dataset[], const int size);
int mode(const int dataset[], const int size, int mode[]);
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
			default:
				break;
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

bool sort(int dataset[], const int size){
	merge(dataset, 0, size-1);
	return true;
}

void merge(int* dataset, int left, int right){
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

bool statistics(const float dataset[], const int size, float& min, float& avg, float& max, float& popSD, float& smplSD) {
	if (size<=0) return -1;
	else{ 
		min=minimum(dataset, size);

		avg=average(dataset, size);
 
		max=maximum(dataset, size);
 
		popSD=popStdDev(dataset, size);

		smplSD=smplStdDev(dataset, size);
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
	

int readCSV(const char filename[], const int minAcceptableID, const int maxAcceptableID, Dataset& data, Rejects& rejects){
	if(minAcceptableID > maxAcceptableID) return -1;
	const int maxLineLength = 100;
	int filename_index = 0;
	while(filename[filename_index] != 0 && filename[filename_index] != 46){
		filename_index++;
	}
	data.students = new Student[maxLineLength];
	char* new_filename = new char[filename_index+5];
	
	filename_index = 0;
	bool flag = false;
	//read filename into a new filename
	while(filename[filename_index] != 0 ){
		new_filename[filename_index] = filename[filename_index];
		filename_index++;
	}
	new_filename[filename_index] = 0;
	filename_index = 0;
	//modify the extension of filename
	while(new_filename[filename_index] != 46 && new_filename[filename_index] !=0){
		filename_index++;
	}
	if(new_filename[filename_index] == 46){
		if(new_filename[filename_index] == 46 && new_filename[filename_index+1] == 99 && new_filename[filename_index+2] == 115 && new_filename[filename_index+3] == 118 ){
			flag = true;
		}
		else return -1;
	}	
	
	if(!flag){
		new_filename[filename_index] = 46;
		new_filename[filename_index+1] = 99;
		new_filename[filename_index+2] = 115;
		new_filename[filename_index+3] = 118;
		new_filename[filename_index+4] = 0;
	}	
	filename_index = 0;
	
	
	char line[maxLineLength];
	ifstream file;
	file.open(new_filename);
	if(!file.is_open()) return -1;
	
	bool done = false;
	int fileLineNumber = 0;
	int Accepted_ID = 0;
	int student_grade = 0;
	char* pass_in_value = new char[10];
	int pass_in_value_index = 0;
	int number_of_rejection = 0;
	int number_of_success = 0;
	int line_index = 0;
	data.numStudents = 0;
	
	int maxNumErrors = 10;
	rejects.rejects = new int[maxNumErrors];
	
	while(!done){
		int count = 0;
		bool ws_count1 = false;
		bool ws_count2 = false;
		bool ws_count3 = false;
		fileLineNumber++;
		if(file.getline(line, maxLineLength)){
		}
		else if(file.eof()){
			rejects.numRejects = number_of_rejection;
			if(number_of_rejection >= maxNumErrors) return -1;
			return number_of_rejection;
		}	
		else return -1;
		
		if(line[line_index] == 0){ 
			rejects.rejects[number_of_rejection] = fileLineNumber;
			number_of_rejection++;
			continue;
		}
		
		while(line[line_index] == 32 || line[line_index] == 9){
			line_index++;
		}	//loop through charcters until there is no white space or tab. Note: ASCII: space: 32; horizontal tab: 9
		
		do{
			if(line[line_index] == 32 || line[line_index] == 9){
				while(line[line_index] != 44){
					if(line[line_index]>=48 && line[line_index]<=57){
						rejects.rejects[number_of_rejection] = fileLineNumber;
						number_of_rejection++;
						student_grade = 0;
						Accepted_ID = 0;
						line_index = 0;
						pass_in_value_index = 0;
						ws_count1 = true;
					}
				if(ws_count1 == true){
					ws_count2 = true;
					break;
				}	
				line_index++;	
				}
				if(ws_count2 == true){
					ws_count3 = true;
					break;
				}	
			}
			else{	
			pass_in_value[pass_in_value_index] = line[line_index];
			line_index++;
			pass_in_value_index++;
			}
		}while(/* line[line_index] != 32 && line[line_index] != 9 &&  */line[line_index] != 44);	//make up the array to pass into StringToInt(STI) function
		
		if(ws_count3 == true) continue;
		
		pass_in_value[pass_in_value_index] = 0;
		
		if(!stringToInt(pass_in_value, Accepted_ID)){
			rejects.rejects[number_of_rejection] = fileLineNumber;
			number_of_rejection++;
			student_grade = 0;
			Accepted_ID = 0;
			line_index = 0;
			pass_in_value_index = 0;
			continue;
		}	//call the STI function, check the input validity 				
		pass_in_value_index = 0;	//one good deal leads to another
			
		
		while(line[line_index] == 32 || line[line_index] == 9 || line[line_index] == 44){
			if(line[line_index] == 44) count+=1;
			line_index++;
		}	//loop through charcters, passing space, tab, and that comma
		
		if(count >= 2){
			rejects.rejects[number_of_rejection] = fileLineNumber;
			number_of_rejection++;
			student_grade = 0;
			Accepted_ID = 0;
			line_index = 0;	
			pass_in_value_index = 0;
			continue;
		}	
		
		do{
			if(line[line_index] == 32 || line[line_index] == 9){
				while(line[line_index] != 44){
					if(line[line_index]>=48 && line[line_index]<=57){
						rejects.rejects[number_of_rejection] = fileLineNumber;
						number_of_rejection++;
						student_grade = 0;
						Accepted_ID = 0;
						line_index = 0;
						pass_in_value_index = 0;
						ws_count1 = true;
					}
				if(ws_count1 == true){
					ws_count2 = true;
					break;
				}	
				line_index++;	
				}
				if(ws_count2 == true){
					ws_count3 = true;
					break;
				}	
			}
			else{	
			pass_in_value[pass_in_value_index] = line[line_index];
			line_index++;
			pass_in_value_index++;
			}
		}while(/* line[line_index] != 32 && line[line_index] != 9 &&  */line[line_index] != 0);	//make up the array to pass into StringToInt(STI) function
		
		if(ws_count3 == true) continue;
		
		pass_in_value[pass_in_value_index] = 0;
			
		if(!stringToInt(pass_in_value, student_grade)){
			rejects.rejects[number_of_rejection] = fileLineNumber;
			number_of_rejection++;
			student_grade = 0;
			Accepted_ID = 0;
			line_index = 0;	
			pass_in_value_index = 0;
			continue;
		}	//call the STI function, check the input validity
		pass_in_value_index = 0;	//one good deal leads to another
		
		
		
		while(line[line_index] != 0){
			line_index++;
		}	//loop through charcters, until the end of that line	
		

		if(Accepted_ID < minAcceptableID || Accepted_ID > maxAcceptableID || student_grade < 0 || student_grade > 100){
			if(number_of_rejection == maxNumErrors) return -1;
			rejects.rejects[number_of_rejection] = fileLineNumber;
			number_of_rejection++;
		}	//check whether ID and grade are in the range. If not, throw line_index to rejects	
		else{
			data.students[number_of_success].grade = student_grade; 
			student_grade = 0;
			data.numStudents+=1;
			data.students[number_of_success].studentID = Accepted_ID;
			Accepted_ID = 0;
			number_of_success++;
		}
		line_index = 0;	
	}
	file.close();
	return 0;
}

int computeStatistics(Dataset& data, Statistics& stats){
	stats.mode.modes = new int[data.numStudents];
	float minimum = 0;
	float maximum = 0;
	float average = 0;
	float popStdDev = 0;
	float smplStdDev = 0;
	int* grade_list_int = new int[data.numStudents];
	float* grade_list_float = new float[data.numStudents];
	for(int i=0; i<data.numStudents; i++){
		grade_list_int[i] = data.students[i].grade;
		grade_list_float[i] = data.students[i].grade;
	}
	
	if(!statistics(grade_list_float, data.numStudents, minimum, average, maximum, popStdDev, smplStdDev)) return -1;
	stats.mode.numModes = mode(grade_list_int, data.numStudents, stats.mode.modes);
	
	stats.minimum = minimum;
	stats.maximum = maximum;
	stats.average = average;
	stats.popStdDev = popStdDev;
	stats.smplStdDev = smplStdDev;
	
	for(int i=0; i<10; i++){
		stats.histogram[i] = 0;
	}
	int relevant_grade = 0;
	for(int i=0; i<data.numStudents; i++){
		relevant_grade = data.students[i].grade/10;
		switch(relevant_grade){
		case 0:
			stats.histogram[0] += 1;
			break;
		case 1:
			stats.histogram[1] += 1;
			break;
		case 2:
			stats.histogram[2] += 1;
			break;
		case 3:
			stats.histogram[3] += 1;
			break;
		case 4:
			stats.histogram[4] += 1;
			break;
		case 5:
			stats.histogram[5] += 1;
			break;
		case 6:
			stats.histogram[6] += 1;
			break;
		case 7:
			stats.histogram[7] += 1;
			break;
		case 8:
			stats.histogram[8] += 1;
			break;
		case 9:
			stats.histogram[9] += 1;
			break;
		case 10:
			stats.histogram[9] += 1;	//specially for grade 100
			break;
		default:;	
		}
	}	
	return 0;
}

int writeCSV(const char filename[], const Statistics& stats){
	int filename_index = 0;
	int filename_length = 0;
	int dot = 0;
	bool flag = true;
	while(filename[filename_index] != 0 ){
		filename_index++;
	}
	filename_length = filename_index;
	char* new_filename = new char[filename_length+5];

	
	for(filename_index=0; filename_index < filename_length; filename_index++){
		new_filename[filename_index] = filename[filename_index];
	}
	new_filename[filename_index] = 0;	
	filename_index = 0;
	
	while(new_filename[filename_index] !=0 && flag == true){
		if(new_filename[filename_index] == 46){
			dot=filename_index;
			flag = false;
		}	
		filename_index++;
	}
	if(dot != 0){
		if(new_filename[dot] == 46 && new_filename[dot+1] == 99 && new_filename[dot+2] == 115 && new_filename[dot+3] == 118 ){
			new_filename[dot] = 46;
			new_filename[dot+1] = 115;
			new_filename[dot+2] = 116;
			new_filename[dot+3] = 97;
			new_filename[dot+4] = 116;
			new_filename[dot+5] = 0;
		}
		else return -1;
	}
	else{
		new_filename[filename_index] = 46;
		new_filename[filename_index+1] = 115;
		new_filename[filename_index+2] = 116;
		new_filename[filename_index+3] = 97;
		new_filename[filename_index+4] = 116;
		new_filename[filename_index+5] = 0;
	}
	
	filename_index = 0;
	ofstream file(new_filename);
	if(!file.is_open()) return -1;
	
	file << "Minimum: " << stats.minimum << endl;
	file << "Average: " << stats.average << endl;
	file << "Maximum: " << stats.maximum << endl;
	file << "Population Standard Deviation: " << stats.popStdDev << endl;
	file << "Sample Standard Deviation: " << stats.smplStdDev <<endl;
	file << "Modes: ";
	for(int i=0; i<stats.mode.numModes; i++){
		file << stats.mode.modes[i];
		if(i != stats.mode.numModes -1) file << ", ";
	}	
	file << endl;
	file << "Histogram: " << endl;
	file << "[0-9]: " << stats.histogram[0] << endl;
	file << "[10-19]: " << stats.histogram[1] << endl;
	file << "[20-29]: " << stats.histogram[2] << endl;
	file << "[30-39]: " << stats.histogram[3] << endl;
	file << "[40-49]: " << stats.histogram[4] << endl;
	file << "[50-59]: " << stats.histogram[5] << endl;
	file << "[60-69]: " << stats.histogram[6] << endl;
	file << "[70-79]: " << stats.histogram[7] << endl;
	file << "[80-89]: " << stats.histogram[8] << endl;
	file << "[90-100]: " << stats.histogram[9] << endl;
	file.close();
	return 0;
	
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
	int minAcceptableID = 1000;
	int maxAcceptableID = 10000;

	Dataset data = {0};
	Rejects rejects = {0};
	Statistics stats = {0};

	std::cout << std::endl << "Implement some more appropriate tests in main()" << std::endl << std::endl;

	if(readCSV(argv[1], minAcceptableID, maxAcceptableID, data, rejects) < 0)
	{
		std::cout << ".csv file could not be read" << std::endl;
	}
	
	if (computeStatistics(data, stats) < 0)
	{
		std::cout << "Stats could not be computed" << std::endl;
	}

	if (writeCSV(argv[1], stats) < 0)
	{
		std::cout << ".stat file could not be written" << std::endl;
	}

	std::cout << "Average: " << stats.average << std::endl;
	std::cout << "Minimum: " << stats.minimum << std::endl;
	std::cout << "Maximum: " << stats.maximum << std::endl;
	std::cout << "Population standard deviation: " << stats.popStdDev << std::endl;
	std::cout << "Sample standard deviation: " << stats.smplStdDev << std::endl;
	
	
	for (unsigned char i = 0; i < stats.mode.numModes; i++)
	{
		std::cout << "Mode: " << stats.mode.modes[i] << std::endl;
	}

	for (unsigned char i = 0; i < 10; i++)
	{
		std::cout << "Histogram bin [" << (i*10) << ", " << ((((i+1)*10) - 1) + i/9) << "]: " << stats.histogram[i] << std::endl;
	}
	std::cout << rejects.rejects[0] <<endl;
	std::cout << rejects.numRejects << endl;
	return 0;
}

#endif
