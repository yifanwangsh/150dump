//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <float>
#include <math.h>
#include <fstream>
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
// Class declaration; modify but do not remove
							 
class StudentGrades 
{
public:
    // Supported statistics
    int   minimum();
    float average();
    int   maximum();
    float popStdDev();
    float smplStdDev();
    int   numModes();
    int   mode(const int modeNumber);
    int   histogram(const int bucketNumber);

    // Populating the data and writing out results
    int  readCSV(const char filename[]);
    int  writeStats(const char filename[]);
    
    // Some supporting functions
    bool validStudentIDs(const int minAcceptableID, const int maxAcceptableID);
    int  numRejects();
    int  reject(const int rejectNumber);

    // Constructor and Destructor
    StudentGrades();
    ~StudentGrades();

private:
	int minAcceptableID;
	int maxAcceptableID;
	
	struct Student{
	int studentID;
	int grade;
	};
	
	struct Dataset{
	int numStudents;
	Student* students;
	};
	
	int numRejects;
	int* rejects;
	int maxNumErrors;
	int numModes;
	int* modes;
	int   minimum;
	float average;
	int   maximum;
	float popStdDev;
	float smplStdDev;
	int   histogram[10];
	int modeNumber;
	
	Dataset dataset;
	

    // It is up to you what you store here
};


//////////////////////////////////////////////////////////////
//
// Your code here ...
//  

int StudentGrades::minimum()
{
	int j=0;
	int k=0;
	float b=0;
	int i=0;
	float a[dataset.numStudents];
	
	for(i=1;i<=dataset.numStudents;i++){
		a[i-1]=dataset.students[i-1];
	}	
	for(j=0; j<=dataset.numStudents-1; j++){
		for(k=j; k<=dataset.numStudents-1; k++){
			if(a[k]<=a[j]){
				b=a[k];
				a[k]=a[j];
				a[j]=b;
			}	
		}
	}	
	return a[0];	
}

float StudentGrades::average()
{
    int j=0;
	float AVG=0;
	for(j=0; j<=dataset.numStudents-1; j++){
		AVG+=dataset.students[j]/dataset.numStudents;
	}
	return AVG;
}

int StudentGrades::maximum()
{
   int j=0;
	int k=0;
	float b=0;
	int i=0;
	float a[dataset.numStudents];
	
	for(i=1;i<=dataset.numStudents;i++){
		a[i-1]=dataset.students[i-1];
	}	
	for(j=0; j<=dataset.numStudents-1; j++){
		for(k=j; k<=dataset.numStudents-1; k++){
			if(a[k]<=a[j]){
				b=a[k];
				a[k]=a[j];
				a[j]=b;
			}	
		}
	}	
	return a[dataset.numStudents-1];
}

float StudentGrades::popStdDev()
{
    int j=0;
	float w_=0;
	int i=0;
	float a[dataset.numStudents];
	float AVG = average();
	
	for(i=0;i<=dataset.numStudents-1;i++){
		a[i]=dataset.students[i];
	}	
	
	for(j=0; j<=dataset.numStudents-1; j++){
		w_+=(a[j]-AVG)*(a[j]-AVG);
	}

	return sqrt(w_/dataset.numStudents);
}

float StudentGrades::smplStdDev()
{
    int j=0;
	float w_=0;
	int i=0;
	float a[dataset.numStudents];
	float AVG =average();
	
	for(i=0;i<=dataset.numStudents-1;i++){
		a[i]=dataset.students[i];
	}	
	
	for(j=0; j<=dataset.numStudents-1; j++){
		w_+=(a[j]-AVG)*(a[j]-AVG);
	}
	
	
	if(dataset.numStudents!=1) return sqrt(w_/(dataset.numStudents-1));	
	else return std::numeric_limits<float>::infinity();
}

int StudentGrades::numModes()
{
	int pass_data[dataset.numStudents];
	for(int i=0; i<=dataset.numStudents-1; i++){
		pass_data[i] = dataset[i];
	}
	
	sort(pass_data, dataset.numStudents);
	
	int number_count = 0;
	int count = 1;
	int temp_count = 1;
	int j = -1;
	pass_data[dataset.numStudents] = std::numeric_limits<float>::quiet_NaN();
	for(int i=0; i<=dataset.numStudents-1; i++){
		if(pass_data[i] == pass_data[i+1]){
			temp_count+=1;
		}
		else{
			if(temp_count > count){
				count = temp_count;
				modes[0] = pass_data[i];
				j = 0;
				number_count = 1;
			}
			else if(temp_count == count){
				j++;
				modes[j] = pass_data[i];
				number_count+=1;
			}	
			temp_count = 1;
		}
	}
	
	return number_count; 
}

int StudentGrades::mode(const int modeNumber)
{
	if(modeNumber > numModes) return -1;
	else return modes[modeNumber-1];
}

int StudentGrades::histogram(const int bucketNumber)
{
	if(bucketNumber < 1 || bucketNumber > 10) return -1;
	else return histogram[bucketNumber-1];
}

int StudentGrades::readCSV(const char filename[])
{
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
	
	while(!done){
		int count = 0;
		bool ws_count1 = false;
		bool ws_count2 = false;
		bool ws_count3 = false;
		fileLineNumber++;
		if(file.getline(line, maxLineLength)){
		}
		else if(file.eof()){
			numRejects = number_of_rejection;
			if(number_of_rejection >= maxNumErrors) return -1;
			return number_of_rejection;
		}	
		else return -1;
		
		if(line[line_index] == 0){ 
			rejects[number_of_rejection] = fileLineNumber;
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
						rejects[number_of_rejection] = fileLineNumber;
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
			rejects[number_of_rejection] = fileLineNumber;
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
			rejects[number_of_rejection] = fileLineNumber;
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
						rejects[number_of_rejection] = fileLineNumber;
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
			rejects[number_of_rejection] = fileLineNumber;
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
			rejects[number_of_rejection] = fileLineNumber;
			number_of_rejection++;
		}	//check whether ID and grade are in the range. If not, throw line_index to rejects	
		else{
			dataset.students[number_of_success].grade = student_grade; 
			student_grade = 0;
			dataset.numStudents+=1;
			dataset.students[number_of_success].studentID = Accepted_ID;
			Accepted_ID = 0;
			number_of_success++;
		}
		line_index = 0;	
	}

	file.close();
	return 0;
}

int StudentGrades::writeStats(const char filename[])
{
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
	
	file << "Minimum: " << minimum() << endl;
	file << "Average: " << average() << endl;
	file << "Maximum: " << maximum() << endl;
	file << "Population Standard Deviation: " << popStdDev() << endl;
	file << "Sample Standard Deviation: " << smplStdDev() <<endl;
	file << "Modes: ";
	for(int i=0; i<numModes; i++){
		file << modes[i];
		if(i != numModes -1) file << ", ";
	}	
	file << endl;
	file << "Histogram: " << endl;
	file << "[0-9]: " << histogram[0] << endl;
	file << "[10-19]: " << histogram[1] << endl;
	file << "[20-29]: " << histogram[2] << endl;
	file << "[30-39]: " << histogram[3] << endl;
	file << "[40-49]: " << histogram[4] << endl;
	file << "[50-59]: " << histogram[5] << endl;
	file << "[60-69]: " << histogram[6] << endl;
	file << "[70-79]: " << histogram[7] << endl;
	file << "[80-89]: " << histogram[8] << endl;
	file << "[90-100]: " << histogram[9] << endl;
	file.close();
	return 0;
}

bool StudentGrades::validStudentIDs(const int minAcceptableID, const int maxAcceptableID)
{
    minAcceptableID = minAcceptableID;
	maxAcceptableID = maxAcceptableID;
	return true;
}

int StudentGrades::numRejects()
{
    return numRejects;
}

int StudentGrades::reject(const int rejectNumber)
{
    if(rejectNumber > numRejects
}

StudentGrades::StudentGrades()
{
	minAcceptableID = 0;
	maxAcceptableID = 100;
	numRejects = 0;
	maxNumErrors = 10;
	rejects = new int[maxNumErrors];
	numModes = 0;
	modes = new int[100];
	
	for(int i=0; i<10; i++){
		histogram[i] = 0;
	}	
	
	modeNumber = 0;
	dataset.numStudents = 0;
	dataset.students = new Student[100];
}

StudentGrades::~StudentGrades()
{
    //Please clean up
	delete rejects;
	delete modes;
	delete dataset.students;
}
		

#ifndef MARMOSET_TESTING
int main(const int argc, const char* const args[]) 
{

    StudentGrades grades;
    //formatting
    cout << endl;

    if (!grades.readCSV(args[1]))
    {
        cout << "CSV read success" << endl;

    } 
    else
    {
        cout << "CSV read fail" << endl;
    }

    cout << "Min: " << grades.minimum() << endl;
    cout << "Max: " << grades.maximum() << endl;

    if (!grades.writeStats(args[1]))
    {
        cout << "Stats write success" << endl;

    } 
    else
    {
        cout << "Stats write fail" << endl;
    }
    //formatting
    cout << endl;

    return 0;

  
}
#endif
