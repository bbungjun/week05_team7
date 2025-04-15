//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

// ListNode 구조체 정의 - 연결 리스트의 노드를 표현
typedef struct _listnode
{
	int item;                  // 노드에 저장되는 정수 값
	struct _listnode *next;    // 다음 노드를 가리키는 포인터
} ListNode;	// ListNode 구조체 정의는 변경하지 않아야 함

// LinkedList 구조체 정의 - 연결 리스트 자체를 표현
typedef struct _linkedlist
{
	int size;                  // 연결 리스트의 크기(노드 수)
	ListNode *head;            // 첫 번째 노드를 가리키는 포인터
} LinkedList;	// LinkedList 구조체 정의는 변경하지 않아야 함


// Queue 구조체 정의 - 연결 리스트를 기반으로 한 큐 구현
typedef struct _queue
{
	LinkedList ll;             // 큐는 연결 리스트로 구현됨
} Queue;  // Queue 구조체 정의는 변경하지 않아야 함

///////////////////////// 함수 프로토타입 선언 ////////////////////////////////////

// 이 함수들의 프로토타입은 변경하지 않아야 함
void createQueueFromLinkedList(LinkedList *ll, Queue *q);    // 연결 리스트로부터 큐를 생성하는 함수
void removeOddValues(Queue *q);                              // 큐에서 홀수 값을 제거하는 함수

void enqueue(Queue *q, int item);                            // 큐에 항목을 추가하는 함수
int dequeue(Queue *q);                                       // 큐에서 항목을 제거하고 반환하는 함수
int isEmptyQueue(Queue *q);                                  // 큐가 비어있는지 확인하는 함수
void removeAllItemsFromQueue(Queue *q);                      // 큐의 모든 항목을 제거하는 함수

void printList(LinkedList *ll);                              // 연결 리스트를 출력하는 함수
ListNode * findNode(LinkedList *ll, int index);              // 인덱스로 노드를 찾는 함수
int insertNode(LinkedList *ll, int index, int value);        // 특정 위치에 노드를 삽입하는 함수
int removeNode(LinkedList *ll, int index);                   // 특정 위치의 노드를 제거하는 함수
void removeAllItems(LinkedList *ll);                         // 모든 노드를 제거하는 함수

//////////////////////////// main() 함수 //////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	Queue q;

	c = 1;

	// 연결 리스트를 빈 연결 리스트로 초기화
	ll.head = NULL;
	ll.size = 0;

	// 큐를 빈 큐로 초기화
	q.ll.head = NULL;
	q.ll.size = 0;

    // 메뉴 출력
	printf("1: Insert an integer into the linked list:\n");
	printf("2: Create the queue from the linked list:\n");
	printf("3: Remove odd numbers from the queue:\n");
	printf("0: Quit:\n");

    // 메뉴 선택에 따른 작업 처리
	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the List: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);      // 사용자 입력 값을 연결 리스트 끝에 추가
			printf("The resulting linked list is: ");
			printList(&ll);                    // 현재 연결 리스트 출력
			break;
		case 2:
			createQueueFromLinkedList(&ll, &q); // 연결 리스트로부터 큐 생성 함수 호출
			printf("The resulting queue is: ");
			printList(&(q.ll));                // 생성된 큐의 내용 출력
			break;
		case 3:
			removeOddValues(&q);               // 큐에서 홀수 값 제거 함수 호출
			printf("The resulting queue after removing odd integers is: ");
			printList(&(q.ll));                // 홀수 제거 후 큐의 내용 출력
			removeAllItemsFromQueue(&q);       // 큐의 모든 항목 제거
			removeAllItems(&ll);               // 연결 리스트의 모든 항목 제거
			break;
		case 0:
			removeAllItemsFromQueue(&q);       // 종료 전 큐의 모든 항목 제거
			removeAllItems(&ll);               // 종료 전 연결 리스트의 모든 항목 제거
			break;
		default:
			printf("Choice unknown;\n");        // 잘못된 선택 처리
			break;
		}
	}

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////

// createQueueFromLinkedList 함수: 연결 리스트에서 큐를 생성하는 함수
// 연결 리스트의 모든 정수를 순서대로 큐에 추가함(첫 번째 노드부터 마지막 노드까지)
void createQueueFromLinkedList(LinkedList *ll, Queue *q)
{
    // 연결 리스트나 큐가 NULL인지 확인
    if (ll == NULL || q == NULL)
        return;
    
    // 큐가 비어있지 않다면 기존 큐의 모든 항목을 제거
    removeAllItemsFromQueue(q);
    
    // 연결 리스트의 첫 번째 노드부터 순회 시작
    ListNode *cur = ll->head;
    
    // 연결 리스트의 모든 노드를 순회
    while (cur != NULL)
    {
        // 현재 노드의 값을 큐에 추가
        enqueue(q, cur->item);
        
        // 다음 노드로 이동
        cur = cur->next;
    }
    
    // 이제 연결 리스트의 모든 항목이 큐에 추가되었음
}

// removeOddValues 함수: 큐에서 홀수 값을 제거하는 함수
// 큐의 모든 요소를 확인하여 짝수만 유지함
void removeOddValues(Queue *q)
{
    // 큐가 NULL인지 확인
    if (q == NULL)
        return;
    
    // 큐가 비어있는지 확인
    if (isEmptyQueue(q))
        return;
    
    // 짝수 값만 보관할 임시 큐 생성
    Queue tempQ;
    tempQ.ll.head = NULL;
    tempQ.ll.size = 0;
    
    // 큐에서 꺼낸 값을 저장할 변수
    int item;
    
    // 원래 큐의 모든 요소 처리
    while (!isEmptyQueue(q))
    {
        // 원래 큐의 맨 앞 요소 제거
        item = dequeue(q);
        
        // 값이 짝수인지 확인(홀수가 아닌지)
        if (item % 2 == 0)
        {
            // 짝수라면 임시 큐에 추가
            enqueue(&tempQ, item);
        }
    }
    
    // 이제 임시 큐의 모든 짝수 값을 원래 큐로 다시 추가
    while (!isEmptyQueue(&tempQ))
    {
        // 임시 큐에서 항목을 제거하고 원래 큐에 추가
        item = dequeue(&tempQ);
        enqueue(q, item);
    }
    
    // 이제 원래 큐에는 짝수 값만 남아 있음
}

//////////////////////////////////////////////////////////////////////////////////

// enqueue 함수: 큐에 항목을 추가하는 함수
// 큐의 맨 뒤에 새 항목을 추가함
void enqueue(Queue *q, int item) {
	insertNode(&(q->ll), q->ll.size, item);  // 큐의 연결 리스트 끝에 노드 삽입
}

// dequeue 함수: 큐에서 항목을 제거하고 반환하는 함수
// 큐의 맨 앞 항목을 제거하고 그 값을 반환함
int dequeue(Queue *q) {
	int item;

	if (!isEmptyQueue(q)) {                 // 큐가 비어있지 않은 경우
		item = ((q->ll).head)->item;        // 맨 앞 노드의 값을 가져옴
		removeNode(&(q->ll), 0);            // 맨 앞 노드를 제거
		return item;                         // 제거된 값을 반환
	}
	return -1;                              // 큐가 비어있으면 -1 반환
}

// isEmptyQueue 함수: 큐가 비어있는지 확인하는 함수
// 큐가 비어있으면 1, 그렇지 않으면 0을 반환
int isEmptyQueue(Queue *q) {
	if ((q->ll).size == 0)                  // 큐의 크기가 0인지 확인
		return 1;                            // 큐가 비어있음
	return 0;                               // 큐가 비어있지 않음
}

// removeAllItemsFromQueue 함수: 큐의 모든 항목을 제거하는 함수
// 큐의 모든 항목을 하나씩 dequeue하여 제거함
void removeAllItemsFromQueue(Queue *q)
{
	int count, i;
	if (q == NULL)                          // 큐가 NULL인지 확인
		return;
	count = q->ll.size;                     // 현재 큐의 크기 저장

	for (i = 0; i < count; i++)             // 큐의 모든 항목을 반복하여 제거
		dequeue(q);
}


// printList 함수: 연결 리스트의 모든 항목을 출력하는 함수
void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)                         // 연결 리스트가 NULL인지 확인
		return;
	cur = ll->head;                         // 첫 번째 노드부터 시작
	if (cur == NULL)                        // 연결 리스트가 비어있는 경우
		printf("Empty");
	while (cur != NULL)                     // 모든 노드를 방문하며 값 출력
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


// removeAllItems 함수: 연결 리스트의 모든 항목을 제거하는 함수
void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;               // 첫 번째 노드부터 시작
	ListNode *tmp;

	while (cur != NULL){                    // 모든 노드를 방문하며 메모리 해제
		tmp = cur->next;
		free(cur);                          // 현재 노드의 메모리 해제
		cur = tmp;                          // 다음 노드로 이동
	}
	ll->head = NULL;                        // 연결 리스트 초기화
	ll->size = 0;
}


// findNode 함수: 연결 리스트에서 특정 인덱스의 노드를 찾는 함수
ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)  // 유효하지 않은 인덱스 확인
		return NULL;

	temp = ll->head;                        // 첫 번째 노드부터 시작

	if (temp == NULL || index < 0)          // 연결 리스트가 비어있거나 인덱스가 음수인 경우
		return NULL;

	while (index > 0){                      // 인덱스 위치까지 이동
		temp = temp->next;
		if (temp == NULL)                   // 노드가 없는 경우
			return NULL;
		index--;
	}

	return temp;                            // 찾은 노드 반환
}

// insertNode 함수: 연결 리스트의 특정 위치에 새 노드를 삽입하는 함수
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)  // 유효하지 않은 인덱스 확인
		return -1;

	// 빈 리스트이거나 첫 번째 위치에 삽입하는 경우, 헤드 포인터 업데이트 필요
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));  // 새 노드를 위한 메모리 할당
		if (ll->head == NULL)
		{
			exit(0);                          // 메모리 할당 실패 시 종료
		}
		ll->head->item = value;               // 새 노드에 값 할당
		ll->head->next = cur;                 // 새 노드를 기존 리스트에 연결
		ll->size++;                           // 리스트 크기 증가
		return 0;
	}


	// 삽입 위치 이전과 현재 위치의 노드를 찾음
	// 새 노드를 생성하고 리스트에 연결
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));  // 새 노드를 위한 메모리 할당
		if (pre->next == NULL)
		{
			exit(0);                           // 메모리 할당 실패 시 종료
		}
		pre->next->item = value;               // 새 노드에 값 할당
		pre->next->next = cur;                 // 새 노드를 리스트에 연결
		ll->size++;                            // 리스트 크기 증가
		return 0;
	}

	return -1;                                // 삽입 실패
}


// removeNode 함수: 연결 리스트의 특정 위치의 노드를 제거하는 함수
int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// 제거할 수 있는 가장 높은 인덱스는 size-1
	if (ll == NULL || index < 0 || index >= ll->size)  // 유효하지 않은 인덱스 확인
		return -1;

	// 첫 번째 노드를 제거하는 경우, 헤드 포인터 업데이트 필요
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);                       // 첫 번째 노드의 메모리 해제
		ll->head = cur;                       // 헤드 포인터를 두 번째 노드로 업데이트
		ll->size--;                           // 리스트 크기 감소
		return 0;
	}

	// 타겟 위치 이전과 이후 노드를 찾음
	// 타겟 노드의 메모리를 해제하고 리스트 재연결
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)                // 타겟 노드가 없는 경우
			return -1;

		cur = pre->next;
		pre->next = cur->next;               // 이전 노드를 다음 노드에 연결
		free(cur);                           // 타겟 노드의 메모리 해제
		ll->size--;                          // 리스트 크기 감소
		return 0;
	}

	return -1;                               // 제거 실패
}