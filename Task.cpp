//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
using namespace std;
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

enum TaskType{LAUNDRY, DISHES, MAKE_BED, VACUUM, MOP_FLOOR, MOW_LAWN};

struct Task 
{
	TaskType type; // Laundry, dishes, etc.
	int taskID;
	char* description;
};

struct TaskQueue
{
	Task* task;
	TaskQueue* nextInQueue;
};

#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
//

bool enqueue(TaskQueue*& queue, const Task& task);
const Task* dequeue(TaskQueue*& queue);

//////////////////////////////////////////////////////////////
//
// Function definitions. PLEASE USE HELPER FUNCTIONS
//

bool enqueue(TaskQueue*& queue, const Task& task)
{
	if(task.description[0] == 0) return false;
	
	TaskQueue* new_queue = new TaskQueue;
	Task* task_copy = new Task;
	task_copy->type = task.type;
	task_copy->taskID = task.taskID;
	task_copy->description = task.description;
	
	new_queue -> task = task_copy;
	new_queue -> nextInQueue = NULL;
	if(queue == NULL){
		queue = new TaskQueue;
		queue -> task = NULL;
		queue -> nextInQueue = NULL;
	}	
	if(queue -> task == NULL){
		queue -> task = task_copy;
		return true;
	}
	TaskQueue* curr = queue;
	if(task_copy->taskID == curr->task->taskID && task_copy->type == curr -> task -> type) return false;
	while(curr -> nextInQueue != NULL){
		curr = curr -> nextInQueue;
	}

	curr -> nextInQueue = new_queue;
	return true;
}

const Task* dequeue(TaskQueue*& queue)
{
	if(queue == NULL) return NULL;
	TaskQueue* to_be_completed = queue;
	Task* return_task = to_be_completed -> task;
	
	
	queue = queue -> nextInQueue;
	delete to_be_completed;
	return return_task;
}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
//
#ifndef MARMOSET_TESTING

int main(){
	// Some test driver code here ....
	cout << endl << "Implement some more appropriate tests in main()" << endl << endl;
	
	char sampleDescription[] = "sample description";
	bool success[12];
	
	Task* task = new Task[12];
	task[0] =
	{
		.type = LAUNDRY,
		.taskID = 1,
		.description = sampleDescription
	};
	task[1] = 
	{
		.type = LAUNDRY,
		.taskID = 2,
		.description = sampleDescription
	};
	task[2] = 
	{
		.type = MAKE_BED,
		.taskID = 3,
		.description = sampleDescription
	};
	task[3] = 
	{
		.type = MOP_FLOOR,
		.taskID = 4,
		.description = sampleDescription
	};
	task[4] = 
	{
		.type = MOW_LAWN,
		.taskID = 5,
		.description = sampleDescription
	};
	task[5] = 
	{
		.type = VACUUM,
		.taskID = 6,
		.description = sampleDescription
	};
	task[6] = 
	{
		.type = LAUNDRY,
		.taskID = 7,
		.description = sampleDescription
	};
	task[7] = 
	{
		.type = DISHES,
		.taskID = 8,
		.description = sampleDescription
	};
	task[8] = 
	{
		.type = MOP_FLOOR,
		.taskID = 9,
		.description = sampleDescription
	};
	task[9] = 
	{
		.type = VACUUM,
		.taskID = 12,
		.description = sampleDescription
	};
	task[10] = 
	{
		.type = MOW_LAWN,
		.taskID = 13,
		.description = sampleDescription
	};
	task[11] = 
	{
		.type = MOP_FLOOR,
		.taskID = 14,
		.description = sampleDescription
	};

	TaskQueue* p_queue = new TaskQueue;
	p_queue->task = NULL;
	p_queue->nextInQueue = NULL;

	bool enqueueSuccess = true;
	int enqueue_time = 12;
	for(int i=0;i<enqueue_time; i++){
		//enqueueSuccess = enqueueSuccess && enqueue(p_queue, task[i]);
		success[i] = enqueue(p_queue, task[i]);
		cout << success[i] << endl;
	}
	
	/* if(enqueueSuccess){
		cout << "tasks enqueued successfully" << endl << endl;
	}
	else
		cout << "enqueue() failed" << endl << endl;  */
	
	const Task* p_firstTaskInQueue;
	int deque_time = 6;
	for(int i=1;i<=deque_time; i++){
		p_firstTaskInQueue = dequeue(p_queue);
	}
	
	if (p_firstTaskInQueue)
	{
		cout << "Dequeue successful..." << endl;
		cout << "Type: " << p_firstTaskInQueue->type << endl;
		cout << "Task ID: " << p_firstTaskInQueue->taskID << endl;
		cout << "Description: " << p_firstTaskInQueue->description << endl;
	}
	else
		cout << "dequeue() failed" << endl;

	delete p_queue;  
	
	return 0;
}
#endif

