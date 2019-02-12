

// OSMAN BOZOĞLU 220201048



#include <stdio.h>
#include <stdlib.h> 
#include<time.h> 
#include <stdbool.h>

/* Struct for list nodes */
struct lst_node_s {
	int data;
	struct lst_node_s* next;
};

/* Struct for task nodes */
struct tsk_node_s {
	int task_num; //starting from 0
	int task_type; // insert:0, delete:1, search:2
	int value;
	struct tsk_node_s* next;
};


/* List operations */
int Insert(int value);
int Search(int value);
int Delete(int value);
void print_task();

/* Task queue functions */
void Task_queue(int n); //generate n random tasks for the task queue
void Task_enqueue(int task_num, int task_type, int value); //insert a new task into task queue
int Task_dequeue(); //take a task from task queue

struct tsk_node_s *head_tsk = NULL; //define head of the task nodes
struct lst_node_s *head_lst = NULL; //define head of the list nodes


int main(int argc, char const *argv[])
{
	head_tsk = (struct tsk_node_s*)malloc(sizeof(struct tsk_node_s)); // head of the task queue allocation
	head_lst = (struct lst_node_s*)malloc(sizeof(struct lst_node_s)); // first node of the linked list
	int n = atoi(argv[1]); // n is number of how many task will be created. it takes from Command line
	Task_queue(n); // generates tasks
	Task_dequeue(); // 
	return 0;
}


bool is_contain(int type, int value){ // just checks there is no duplicated item in the task queue
	struct tsk_node_s *temp; 
	temp = head_tsk->next;
	while(temp != NULL){
		if(temp->task_type == type && temp->value == value)
			return true;
		temp = temp->next;
	}

	return false;
} 

void Task_enqueue(int task_num, int task_type, int value) {			//insert a new task into task queue

	struct tsk_node_s *new_task = (struct tsk_node_s*)malloc(sizeof(struct tsk_node_s)); // creating new task
	new_task->task_num = task_num; // assign task num
	new_task->task_type = task_type; // assign task type
	new_task->value = value; //assign value
	new_task->next = NULL; // assing next pointer

	if (head_tsk->next == NULL) // if head->next equals null, that mean is task list is empty
	{
		head_tsk->next = new_task; // assigning the first element
	}
	else{
		struct tsk_node_s *tmp;	
		tmp = head_tsk->next; // tmp is the first element
		while(tmp->next != NULL)
			tmp = tmp->next;	
		tmp->next = new_task; // add new task to last item
		
	}
}


void Task_queue(int n){
	srand(time(0));
	int task_num = 0;
	for (int i = 0; i < n; ++i)
	{
		int task_type = rand() %3; // select random task between 0 to 2
		int value = rand() %50; // select the random value between 0 to 49
		Task_enqueue(task_num,task_type,value); // creating task
		task_num++;
	}
}

int Search(int value){
	struct lst_node_s *temp; 
	temp = head_lst->next; // temp is the first of the list
	while(temp != NULL){
		if (temp->data == value){ // if temp->data is equals the given value, the search function returns 1 
			return 1;
		}
			
		temp = temp->next;
	}
	return 0; // if the value is not found, search function returns 0
}

int Insert(int value){
	if(Search(value))
		return 0;
	struct lst_node_s *new_task = (struct lst_node_s*)malloc(sizeof(struct lst_node_s)); // creating new task
	new_task->data = value;
	if (head_lst->next == NULL) // if head->next equals null, that mean is task list is empty
	{
		head_lst->next = new_task;
		new_task->next = NULL;
	}
	else{
		struct lst_node_s *tmp, *prev;	
		tmp = head_lst->next;
		prev = head_lst;
		while(tmp->data < value && tmp->next != NULL){ // finds location of the given value in linked list
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp->next == NULL && tmp->data < value) // If the value is the biggest from the list element, this adds  it to the last.
		{
			tmp->next = new_task;
			new_task->next = NULL;
			return 1;
		}
		new_task->next = tmp;
		prev->next = new_task;
	}
	return 1;
}



int Delete(int value){

	if (!Search(value)) // checks the given value is in list or not. If not, delete function returns 0
		return 0;
		
	struct lst_node_s *prev, *temp; // struct definitions
	temp = head_lst->next;
	prev = head_lst;
	while(temp != NULL){
		if (temp->data == value)
		{
			prev->next = temp->next;
			free(temp); 
			return 1;
		}
		prev = temp;
		temp = temp->next;
	}
}

void print_final_list(){ // prints the final list
		struct lst_node_s *tmp;	
		tmp = head_lst->next;
		printf("Final List :\n");
		while(tmp != NULL){
			printf("%d\t", tmp->data);
			tmp = tmp->next;
		}
		printf("\n");
}

/*
Task_dequeue 
It calls the Insert function if the task type 0. Then prints the result and the task removed from the task queue.
It calls the Insert function if the task type 0. Then prints the result and the task removed from the task queue.
It calls the Insert function if the task type 0. Then prints the result and the task removed from the task queue.
*/

int Task_dequeue(){
	struct tsk_node_s *tmp;
	head_tsk = head_tsk->next;
	while(head_tsk != NULL){
		switch(head_tsk->task_type){
			case 0:
				printf("task %d insert %d :",head_tsk->task_num,head_tsk->value);
				if(Insert(head_tsk->value))
					printf("%d is inserted\n", head_tsk->value);
				else
					printf("%d can not be inserted\n", head_tsk->value);
				break;
			case 1:
				printf("task %d delete %d :",head_tsk->task_num,head_tsk->value);
				if(Delete(head_tsk->value))
					printf("%d is deleted\n", head_tsk->value);
				else
					printf("%d can not be deleted\n", head_tsk->value);
				break;
			case 2:
				printf("task %d search %d :",head_tsk->task_num,head_tsk->value);
				if(Search(head_tsk->value))
					printf("%d is found\n", head_tsk->value);
				else
					printf("%d is not found\n", head_tsk->value);
				break;
			default: break;

		}
		tmp = head_tsk;
		head_tsk = head_tsk->next;
		free(tmp); // deleting the task
	}
	free(head_tsk);
	print_final_list();
	return 1;

}
