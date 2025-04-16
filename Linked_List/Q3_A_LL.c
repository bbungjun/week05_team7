//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

// 연결 리스트의 노드를 표현하는 구조체
typedef struct _listnode
{
	int item;            // 노드에 저장되는 데이터 값
	struct _listnode *next;  // 다음 노드를 가리키는 포인터
} ListNode;			// You should not change the definition of ListNode

// 연결 리스트 자체를 표현하는 구조체
typedef struct _linkedlist
{
	int size;            // 연결 리스트의 크기(노드 개수)
	ListNode *head;      // 연결 리스트의 첫 번째 노드를 가리키는 포인터
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// 홀수 항목을 리스트의 뒤로 이동시키는 함수
void moveOddItemsToBack(LinkedList *ll);

// 리스트의 모든 항목을 출력하는 함수
void printList(LinkedList *ll);
// 리스트의 모든 항목을 제거하는 함수
void removeAllItems(LinkedList *ll);
// 특정 인덱스의 노드를 찾는 함수
ListNode * findNode(LinkedList *ll, int index);
// 특정 인덱스에 노드를 삽입하는 함수
int insertNode(LinkedList *ll, int index, int value);
// 특정 인덱스의 노드를 제거하는 함수
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;      // 연결 리스트의 헤드를 NULL로 초기화
	ll.size = 0;         // 연결 리스트의 크기를 0으로 초기화


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	// 사용자 입력에 따라 작업 수행하는 메인 루프
	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			// 사용자로부터 정수를 입력받아 리스트에 추가
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);  // 리스트의 끝에 노드 삽입
			printf("The resulting linked list is: ");
			printList(&ll);  // 결과 리스트 출력
			break;
		case 2:
			// 홀수 항목을 리스트 뒤로 이동
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
			printList(&ll);  // 결과 리스트 출력
			removeAllItems(&ll);  // 모든 항목 제거
			break;
		case 0:
			// 프로그램 종료 전 메모리 정리
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
	// 리스트가 비어있거나 노드가 하나뿐이면 이동할 필요 없음
	if (ll == NULL || ll->head == NULL || ll->head->next == NULL)
		return;
	
	ListNode *evenHead = NULL;    // 짝수 노드들의 첫 번째 노드
	ListNode *evenTail = NULL;    // 짝수 노드들의 마지막 노드
	ListNode *oddHead = NULL;     // 홀수 노드들의 첫 번째 노드
	ListNode *oddTail = NULL;     // 홀수 노드들의 마지막 노드
	ListNode *current = ll->head; // 현재 처리 중인 노드
	
	// 리스트를 순회하며 홀수/짝수 노드 분리
	while (current != NULL) {
		ListNode *next = current->next; // 다음 노드 저장
		current->next = NULL;          // 현재 노드 연결 끊기
		
		if (current->item % 2 == 0) {  // 짝수인 경우
			if (evenHead == NULL) {    // 첫 짝수 노드인 경우
				evenHead = current;
				evenTail = current;
			} else {                   // 이미 짝수 노드가 있는 경우
				evenTail->next = current;
				evenTail = current;
			}
		} else {                       // 홀수인 경우
			if (oddHead == NULL) {     // 첫 홀수 노드인 경우
				oddHead = current;
				oddTail = current;
			} else {                   // 이미 홀수 노드가 있는 경우
				oddTail->next = current;
				oddTail = current;
			}
		}
		
		current = next;  // 다음 노드로 이동
	}
	
	// 짝수 노드나 홀수 노드가 없는 경우 처리
	if (evenHead == NULL) {
		ll->head = oddHead;  // 짝수 노드가 없으면 홀수 노드만 있음
		return;
	}
	if (oddHead == NULL) {
		ll->head = evenHead;  // 홀수 노드가 없으면 짝수 노드만 있음
		return;
	}
	
	// 짝수 노드 뒤에 홀수 노드 연결
	evenTail->next = oddHead;
	ll->head = evenHead;  // 리스트의 헤드를 짝수 노드의 시작으로 설정
}

///////////////////////////////////////////////////////////////////////////////////

// 리스트의 모든 항목을 출력하는 함수
void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;  // 첫 번째 노드부터 시작

	if (cur == NULL)
		printf("Empty");  // 리스트가 비어있는 경우
	while (cur != NULL)
	{
		printf("%d ", cur->item);  // 현재 노드의 값 출력
		cur = cur->next;  // 다음 노드로 이동
	}
	printf("\n");
}

// 리스트의 모든 항목을 제거하고 메모리 해제하는 함수
void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;  // 다음 노드 임시 저장
		free(cur);        // 현재 노드 메모리 해제
		cur = tmp;        // 다음 노드로 이동
	}
	ll->head = NULL;  // 헤드를 NULL로 설정
	ll->size = 0;     // 크기를 0으로 초기화
}

// 특정 인덱스의 노드를 찾는 함수
ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	// 예외 처리: 유효하지 않은 인덱스
	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	// 예외 처리: 빈 리스트이거나 인덱스가 음수
	if (temp == NULL || index < 0)
		return NULL;

	// 해당 인덱스까지 이동
	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;  // 찾은 노드 반환
}

// 특정 인덱스에 노드를 삽입하는 함수
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	// 예외 처리: 유효하지 않은 인덱스
	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// 빈 리스트이거나 첫 번째 위치에 삽입하는 경우
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));  // 새 노드 생성
		ll->head->item = value;               // 값 설정
		ll->head->next = cur;                 // 연결 설정
		ll->size++;                           // 크기 증가
		return 0;
	}

	// 목표 위치 이전의 노드를 찾고 새 노드 삽입
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));  // 새 노드 생성
		pre->next->item = value;               // 값 설정
		pre->next->next = cur;                 // 연결 설정
		ll->size++;                            // 크기 증가
		return 0;
	}

	return -1;  // 삽입 실패
}

// 특정 인덱스의 노드를 제거하는 함수
int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// 예외 처리: 유효하지 않은 인덱스
	// 제거할 수 있는 가장 높은 인덱스는 size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// 첫 번째 노드를 제거하는 경우
	if (index == 0){
		cur = ll->head->next;      // 두 번째 노드
		free(ll->head);            // 첫 번째 노드 메모리 해제
		ll->head = cur;            // 헤드를 두 번째 노드로 설정
		ll->size--;                // 크기 감소

		return 0;
	}

	// 목표 위치 이전의 노드를 찾고 목표 노드 제거
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;           // 제거할 노드
		pre->next = cur->next;     // 연결 재설정
		free(cur);                 // 노드 메모리 해제
		ll->size--;                // 크기 감소
		return 0;
	}

	return -1;  // 제거 실패
}