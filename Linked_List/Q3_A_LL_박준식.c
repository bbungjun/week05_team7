//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void moveOddItemsToBack(LinkedList *ll) 
{
	/* add your code here */
	if (ll == NULL)
		return;
	ListNode *cur = ll->head;
	ListNode *prev = NULL;
	ListNode *oddH = NULL;
	ListNode *oddT = NULL;

	while (cur != NULL) {
		if (cur->item % 2 == 1) {
			ListNode *tmp = cur;
			if (prev == NULL) {
				ll->head = cur->next;
				cur = ll->head;
			} else {
				prev->next = cur->next;
				cur = prev->next;
			}
			tmp->next = NULL;
			if (oddH == NULL) {
				oddH = tmp;
				oddT = tmp; // 없으면 1 3 5에서 에러남
			} else {
				oddT->next = tmp;
				oddT = tmp;
			}
			ll->size--;
		} else {
			prev = cur;
			cur = cur->next;
		}
	}

	if (prev == NULL) { // 모두 홀수인 경우
		ll->head = oddH;
	} else {
		prev->next = oddH;
	}

	ListNode *odd = oddH;
	while (odd != NULL) {
		ll->size++;
		odd = odd->next;
	}
}

	// ListNode *cur;
	// if (ll == NULL)
	// 	return;
	// cur = ll->head;
	// LinkedList lo;
	// lo.head = NULL;
	// lo.size = 0;
	// int idx = 0;
	// int odx = 0;
	// while (cur->next != NULL) {
	// 	if (cur->item % 2 == 1) {
	// 		int val = cur->item;
	// 		if (idx == 0) {
	// 			cur = ll->head->next;
	// 			free(ll->head);
	// 			ll->head = cur;
	// 			ll->size--;
	// 		} else {
	// 			ListNode *pre;
	// 			if ((pre = findNode(ll, idx-1)) != NULL){
	// 				cur = pre->next;
	// 				pre->next = cur->next;
	// 				free(cur);
	// 				ll->size--;
	// 			}
	// 		}
	// 		insertNode(&lo, odx, val);
	// 		odx++;
	// 	} else {
	// 		cur = cur->next;
	// 		idx++;
	// 	}
	// }
	// cur->next = lo.head;
	// ll->size++;
	// ll->size += lo.size;
	// printList(&lo);
	// ListNode *curo = lo.head;
	// while (curo->next != NULL) {
	// 	cur->next = curo;
	// 	curo = curo->next;
	// 	cur = cur->next;
	// 	ll->size++;
	// }


///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
