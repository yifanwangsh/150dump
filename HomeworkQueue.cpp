//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//
#include<sys/time.h>
#include<limits.h>
//////////////////////////////////////////////////////////////
//
// local #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
#endif

//////////////////////////////////////////////////////////////
//
// struct definitions 
//
#ifndef MARMOSET_TESTING

enum COURSE {CHE102, MATH115, MATH117, ECE105, ECE150, ECE190, Null};

struct Assignment 
{
	COURSE course; // CHE102, MATH117, etc.
	int assnNum; // Assignment Number
	int dueMonth; // Month due (1-12)
	int dueDay; // Day due (1-31)
	char* description; // Assignment description
};

struct HomeworkQueue
{
	Assignment* assn;
	HomeworkQueue* nextInQueue;
};

#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
//

bool enqueue(HomeworkQueue*& queue, const Assignment& assignment);
const Assignment* dequeue(HomeworkQueue*& queue);
int daysTillDue(const HomeworkQueue* q, const COURSE course);
const Assignment* dueIn(const HomeworkQueue* q, const int numDays);
bool isEarlier(const Assignment &a1, const Assignment &a2);
//////////////////////////////////////////////////////////////
//
// Function definitions. PLEASE USE HELPER FUNCTIONS
//

bool enqueue(HomeworkQueue*& queue, const Assignment& assignment)
{
	HomeworkQueue* current = queue;
	HomeworkQueue* new_assignment = new HomeworkQueue;
	Assignment new_assignment;
	new_assignment -> assn = assignment;
	new_assignment -> nextInQueue = NULL;
	//declare variables; current takes the head initially; new_assignment holds assignment parameter information 
	
	while(current -> nextInQueue != NULL){//Loop in the linked list
		if(current -> nextInQueue -> assn -> dueMonth > assignment.dueMonth){//The work is due earlier
			new_assignment -> nextInQueue = current -> nextInQueue;
			current -> nextInQueue = new_assignment;//add 
			return true;
		}
		else if(current -> nextInQueue -> assn -> dueMonth == assignment.dueMonth){
			if(current -> nextInQueue -> assn -> dueDay > assignment.dueDay){//first come, first serve
				new_assignment -> nextInQueue = current -> nextInQueue;
				current -> nextInQueue = new_assignment;
				return true;
			}
		}
		current = current -> nextInQueue;
	}
	current -> nextInQueue = new_assignment;
	return true;
	return false;
}

const Assignment* dequeue(HomeworkQueue*& queue)
{
	Assignmet to_be_done = queue -> assn;
	HomeworkQueue* to_kill = new HomeworkQueue;
	
	to_kill -> nextInQueue = queue;
	queue = queue -> nextInQueue;
	delete to_kill;
	return to_be_done;
	return NULL;
	
}
int daysTillDue(const HomeworkQueue* q, const COURSE course)
{
	HomeworkQueue current = q;
	struct timeval tv;
	struct timezone tz;
	struct tm *tm;
	while(current -> nextInQueue != NULL){
		if(current -> assn -> course == course){
			if(!gettimeofday(&tv, NULL)) return -1;
			time_t current_time = tv.tv_sec;
			tm now = localtime(&current_time);
			return_value = 30*(now -> tm_mon - current -> assn -> dueMonth) + (now -> tm_mday - current -> assn -> dueDay);
			return return_value;
		}
	}
	return INT_MAX;
	
}
const Assignment* dueIn(const HomeworkQueue* q, const int numDays)
{
	HomeworkQueue* current = q;
	struct timeval tv;
	struct timezone tz;
	struct tm *tm;
	if(!gettimeofday(&tv, NULL)) return -1;
	time_t current_time = tv.tv_sec;
	tm now = localtime(&current_time);
	int days_due = 0;
	int to_be_returned_index = 0;
	Assignment* to_be_returned = new Assignment[10];
	Assignment last_assignment;
	last_assignment.course = Null;
	
	int numDays_index = 0;
	
	while(current -> nextInQueue != NULL){
		days_due = (current -> assn -> dueMonth - now -> tm_mon)*30 + (current -> assn -> dueDay - now -> tm_mday);
		if(days_due <= numDays){
			to_be_returned[to_be_returned_index] = current -> assn;
			numDays_index++;
		}
		current = current -> nextInQueue;
	}
	to_be_returned[to_be_returned_index] = last_assignment; 
	return to_be_returned;
	
}
bool isEarlier(const Assignment &a1, const Assignment &a2){
	if(a1.dueMonth < a2.dueMonth){
		return true;
	}
	else if(a1.dueMonth == a2.dueMonth){
		if(a1.dueDay < a2.dueDay){
			return true;
		}
		else return false;
	}
	else return false;
}	

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
//

#ifndef MARMOSET_TESTING

int main(const int argc, const char* const argv[]) {
  		// Some test driver code here ....
	std::cout << std::endl << "Implement some more appropriate tests in main()" << std::endl << std::endl;

	HomeworkQueue* p_queue = new HomeworkQueue;
	p_queue->nextInQueue = NULL;
	p_queue->assn = NULL;

	char sampleDescription[] = "Sequential Execution";
	Assignment assn1 = 
	{
		.course = ECE150,
		.assnNum = 0,
		.dueMonth = 9,
		.dueDay = 15,
		.description = sampleDescription
	};
	Assignment assn2 = 
	{
		.course = ECE105,
		.assnNum = 1,
		.dueMonth = 11,
		.dueDay = 15,
		.description = sampleDescription
	};
	Assignment assn3 = 
	{
		.course = CHE102,
		.assnNum = 2,
		.dueMonth = 11,
		.dueDay = 17,
		.description = sampleDescription
	};
	Assignment assn4 = 
	{
		.course = ECE190,
		.assnNum = 3,
		.dueMonth = 11,
		.dueDay = 16,
		.description = sampleDescription
	};
	Assignment assn5 = 
	{
		.course = MATH115,
		.assnNum = 4,
		.dueMonth = 10,
		.dueDay = 21,
		.description = sampleDescription
	};
	Assignment assn6 = 
	{
		.course = ECE117,
		.assnNum = 5,
		.dueMonth = 10,
		.dueDay = 30,
		.description = sampleDescription
	};
	bool enqueueSuccess = enqueue(p_queue, assn1) && enqueue(p_queue, assn2)&& enqueue(p_queue, assn3)&& enqueue(p_queue, assn4)&& enqueue(p_queue, assn5)&& enqueue(p_queue, assn6);
	
	if(enqueueSuccess){
		std::cout << "assn1 enqueued successfully" << std::endl << std::endl;
	}
	else{
		std::cout << "enqueue() failed" << std::endl << std::endl; 
	}

	const Assignment* p_firstAssignmentInQueue = dequeue(p_queue);
	
	if (p_firstAssignmentInQueue)
	{
		std::cout << "Dequeue successful..." << std::endl;
		std::cout << "Course: " << p_firstAssignmentInQueue->course << std::endl;
		std::cout << "Assignment #: " << p_firstAssignmentInQueue->assnNum << std::endl;
		std::cout << "Day due: " << p_firstAssignmentInQueue->dueDay << std::endl;
		std::cout << "Month due: " << p_firstAssignmentInQueue->dueMonth << std::endl;
		std::cout << "Description: " << p_firstAssignmentInQueue->description << std::endl;
	}
	else
	{
		std::cout << "dequeue() failed" << std::endl;
	}

	delete p_queue;

	return 0;
}

#endif
