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
// Important: do not include your struct, class into MARMOSET_TESTING!!!

//////////////////////////////////////////////////////////////
//
// struct definitions 
//

enum TaskType{LAUNDRY, DISHES, MAKE_BED, VACUUM, MOP_FLOOR, MOW_LAWN};

struct Task 
{
	TaskType type; // Laundry, dishes, etc.
	int taskID;
	char* description;
};

//////////////////////////////////////////////////////////////
//
// Class definitions, do not remove.
//

class TaskQueue{
public:
	//it maybe a good idea to have a constructor
	bool enqueue(const Task& task){ 
	// you can either implement your function here or below in the function definitions
		if(task.description[0] == 0) return false;
	
		Queue* new_queue = new Queue;
		Task* task_copy = new Task;
		task_copy->type = task.type;
		task_copy->taskID = task.taskID;
		task_copy->description = task.description;
	
		new_queue -> task = task_copy;
		new_queue -> nextInQueue = NULL;
		if(queue == NULL){
			queue = new Queue;
			queue -> task = NULL;
			queue -> nextInQueue = NULL;
		}	
		if(queue -> task == NULL){
			queue -> task = task_copy;
			return true;
		}
		Queue* curr = queue;
		if(task_copy->taskID == curr->task->taskID && task_copy->type == curr -> task -> type) return false;
		while(curr -> nextInQueue != NULL){
			curr = curr -> nextInQueue;
		}

		curr -> nextInQueue = new_queue;
		return true;
	}
	
	const Task* dequeue(){
		if(queue == NULL) return NULL;
		Queue* to_be_completed = queue;
		Task* return_task = to_be_completed -> task;
	
	
		queue = queue -> nextInQueue;
		delete to_be_completed;
		return return_task;
	}
	
	/* TaskQueue operator=(const TaskQueue &source){
		if(this == &source) return *this;
		Queue* tmp = new Queue;
		tmp = this->queue;
		
		while(tmp){
			this->queue = this->queue->nextInQueue;
			delete tmp;
			tmp = this->queue;
		}
		
		Queue* tail = new Queue;
		tail = this->queue;
		Task* temp = source.dequeue();
		while(temp){
			tail->task = temp;
			temp = source.dequeue();
			tail = this->queue->nextInQueue;
		}
		return *this;
	}	 */
	
	TaskQueue(){
		queue = new Queue;
		queue->task = NULL;
		queue->nextInQueue = NULL;
	}
	
	~TaskQueue(){
		queue = new Queue;
		queue->task = NULL;
		queue->nextInQueue = NULL;
	}	
private:
	// you decide what goes here 
	struct Queue{
		Task* task;
		Queue* nextInQueue;
		};
	Queue* queue;	
};


//////////////////////////////////////////////////////////////
//
// Function definitions. PLEASE USE HELPER FUNCTIONS
//


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

	TaskQueue p_queue;

	bool enqueueSuccess = true;
	int enqueue_time = 12;
	for(int i=0;i<enqueue_time; i++){
		//enqueueSuccess = enqueueSuccess && enqueue(p_queue, task[i]);
		success[i] = p_queue.enqueue(task[i]);
		cout << success[i] << endl;
	}
	
	/* if(enqueueSuccess){
		cout << "tasks enqueued successfully" << endl << endl;
	}
	else
		cout << "enqueue() failed" << endl << endl;  */
	
	TaskQueue anotherQueue = p_queue;
	cout << anotherQueue.dequeue()->taskID << endl;
	
	const Task* p_firstTaskInQueue;
	int deque_time = 6;
	for(int i=1;i<=deque_time; i++){
		p_firstTaskInQueue = p_queue.dequeue();
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
	
	return 0;
}
#endif

