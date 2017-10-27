#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

list_t list_create()
{
	list_t list = malloc(sizeof(list_t));
	list->head = NULL;
	list->tail = NULL;
	list->length = 0;
	printf("\n List created.");
	return list;
}

// Travrese the list and delete all nodes?
void list_delete(list_t list)
{
	printf("Deleting list. \n");
	struct node *current = list->head; // Points to the head of the list, used to traverse the list
	struct node *next = malloc(sizeof(struct node)); // Used to keep track of the next nodes

	while(current != NULL){
		next = current->next;
		free(current);
		current = next;
	}
	list->head = NULL; // The list is empty
	printf("\n List deleted.");
}

void list_insert(list_t list, int index, int data){ // Something wrong here

	struct node *current = list->head; // Points to the head of the list, used to traverse the list
	struct node *newNode = malloc(sizeof(struct node)); // Node to be inserted
	int counter = 0;

	while(current != NULL){
		printf("Counter: %i\n", counter);
		if(counter == index){
			printf("QQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n");
			if(index == 0){
				printf("test FFFFFFFFFFFFFFFFFFF\n");
				list->head->prev = newNode;
				newNode->next = list->head;
				list->head = newNode;
				newNode->prev = NULL; 
			}else if(index == list->length){
				printf("testAAAAAAAAAAAAAAAAAA\n");
				newNode->prev = list->tail;
				list->tail->next = newNode;
				list->tail = newNode;
				newNode->next = NULL;
			}else{
				printf("test12323521513453542435\n");
				current->prev->next = newNode; // ..?
				newNode->next = current;
				newNode->prev = current->prev;
				current->prev = newNode;
			}
		(list->length)--;
		printf("Inserted data at index %d\n", index);

		}
	newNode->data = data;
	current = current->next;
	counter = counter + 1;
	}

	//counter = counter + 1;
}

void list_append(list_t list, int data)
{
	printf("Appending the list. \n");
	struct node *newNode = malloc(sizeof(struct node));
	if(list->length == 0) {
		list->head = newNode;
		list->tail = newNode;
		list->tail->next = NULL; // newNode->next = NULL;
		list->head->prev = NULL; // newNode->prev = NULL; //tempNode = tempNode->next; tempNode->next == NULL
		printf("AAAAAAAAAAAAAAA \n");
	}
	else{
		//struct node *tempNode = list->tail;
		//list->tail = newNode;
		//tempNode->next = newNode;
		//newNode->next = NULL;
		//newNode->prev = tempNode;
		newNode->prev = list->tail;
		list->tail->next = newNode;
		printf("QQQQQQQQQQQQQQQQQ\n");
	}
	newNode->data = data;
	newNode->next = NULL;
	list->tail = newNode;
	printf("List appended. \n");
	(list->length)++;
}

/*void list_append(list_t list, int data){
	printf("Appending the list\n");
	struct node* new_node = malloc(sizeof(struct node));
	list->tail->next = new_node;
	(list->length)++;
	new_node->data = data;
	new_node->prev = list->tail;
	list->tail = new_node;
}*/

/*void list_append(list_t list, int data)
{
	printf("Appending the list. \n");
	struct node *current = list->head; // Used to traverse the list
	while(current->next != NULL){
		printf("SSSSSSSSSSSSSSSSS\n");
		current = current->next;
	}
	// Add the new data:
	current->next = malloc(sizeof(struct node));
	current->next->data = data;
	current->next->next = NULL;
	printf("List appended. \n");
}*/


void list_print(list_t list)
{
	struct node *current = list->head;

	while(current != NULL){
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

long list_sum(list_t list)
{
	struct node *current = list->head; // Points to the head of the list, used to traverse the list
	long sum = 0;

	while(current != NULL){
		sum = sum + current->data;
		current = current->next;
	}
	return sum;
}

int list_get(list_t list, int index) // Get the data from an node?
{
	// Traverse the list, return tempNode->data ..? // Does data have to be an int?
	struct node *current = list->head; // Points to the head of the list, used to traverse the list
	int counter = 0;

	while(current != NULL){
		if(counter == index){
			return current->data;
		}
		current = current->next;
		counter = counter + 1;
	}
	return 0;
}

int list_extract(list_t list, int index){

	struct node *current = list->head;
	int retval;
	int counter = 0;
	printf("Extracting node. \n");

	while(current != NULL){
		if(counter == index){
			if(counter == 0){
				list->head = list->head->next;
				if(list->length != 1){ // ..?
					list->head->prev = NULL;
				}
				retval = current->data;
				free(current);
			}else if(counter == list->length){
				list->tail = list->tail->prev;
				retval = current->data;
				free(current);
			}else{
				printf("QQQQQQQQQQQQQQQQQ \n");
				current->prev->next = current->next; // ..?
				current->next->prev = current->prev;
				retval = current->data;
				free(current);
			}
			return retval;
		}
		current = current->next;
		counter = counter + 1;
		(list->length)--;
	}
	return 0;
}