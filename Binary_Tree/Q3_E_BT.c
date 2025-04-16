///////////////////////////////////////////////////////

#include <stdio.h>  // 표준 입출력 함수를 위한 헤더 파일
#include <stdlib.h> // 동적 메모리 할당(malloc, free)을 위한 헤더 파일

//////////////////////////////////////////////////////////////////////////////////
typedef struct _btnode
{
    int item;              // 노드의 데이터 값
    struct _btnode *left;  // 왼쪽 자식 노드를 가리키는 포인터
    struct _btnode *right; // 오른쪽 자식 노드를 가리키는 포인터
} BTNode;   // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode
{
    BTNode *btnode;         // 이진 트리 노드를 가리키는 포인터
    struct _stackNode *next; // 다음 스택 노드를 가리키는 포인터
} StackNode;

typedef struct _stack
{
    StackNode *top;         // 스택의 맨 위 노드를 가리키는 포인터
} Stack;

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int countOneChildNodes(BTNode *node);  // 정확히 하나의 자식을 가진 노드 수를 계산하는 함수

BTNode *createBTNode(int item);        // 새로운 이진 트리 노드를 생성하는 함수

BTNode *createTree();                  // 이진 트리를 생성하는 함수
void push(Stack *stack, BTNode *node); // 스택에 노드를 추가하는 함수
BTNode* pop(Stack *stack);             // 스택에서 노드를 꺼내는 함수

void printTree(BTNode *node);          // 이진 트리를 중위 순회로 출력하는 함수
void removeAll(BTNode **node);         // 이진 트리의 모든 노드를 제거하는 함수

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    char e;              // 문자 입력을 처리하기 위한 변수
    int c, s;            // 사용자 선택 및 결과값 저장 변수
    BTNode *root;        // 이진 트리의 루트 노드

    c = 1;               // 초기 메뉴 선택값
    root = NULL;         // 루트 노드 초기화


    printf("1: Create a binary tree.\n");
    printf("2: Count the number of nodes that have exactly one child node.\n");
    printf("0: Quit;\n");

    while(c != 0)        // 사용자가 0을 선택할 때까지 반복
    {
        printf("Please input your choice(1/2/0): ");
        if(scanf("%d",&c) > 0)  // 정수 입력이 성공했을 경우
        {
            switch(c)
            {
            case 1:  // 이진 트리 생성
                removeAll(&root);     // 기존 트리 제거
                root = createTree();  // 새 트리 생성
                printf("The resulting binary tree is: ");
                printTree(root);      // 생성된 트리 출력
                printf("\n");
                break;
            case 2:  // 하나의 자식을 가진 노드 개수 계산
                s = countOneChildNodes(root);  // 노드 개수 계산
                printf("The number of nodes that have exactly one child node is: %d.\n", s);
                removeAll(&root);     // 트리 제거
                break;
            case 0:  // 프로그램 종료
                removeAll(&root);     // 트리 제거
                break;
            default: // 잘못된 선택
                printf("Choice unknown;\n");
                break;
            }
        }
        else  // 정수 입력이 실패했을 경우
        {
            scanf("%c",&e);  // 버퍼에서 문자 제거
        }

    }
    return 0;  // 프로그램 정상 종료
}

//////////////////////////////////////////////////////////////////////////////////

// 정확히 하나의 자식을 가진 노드의 개수를 계산하는 함수
int countOneChildNodes(BTNode *node)
{
    // 기본 케이스: 노드가 NULL인 경우 0 반환
    if (node == NULL)
        return 0;
    
    // 현재 노드의 자식 상태 확인
    int hasLeftChild = (node->left != NULL);   // 왼쪽 자식 유무 (1 또는 0)
    int hasRightChild = (node->right != NULL); // 오른쪽 자식 유무 (1 또는 0)
    
    // 왼쪽과 오른쪽 서브트리에서 하나의 자식을 가진 노드 개수를 재귀적으로 계산
    int leftCount = countOneChildNodes(node->left);
    int rightCount = countOneChildNodes(node->right);
    
    // 현재 노드가 정확히 하나의 자식만 가지고 있는지 확인
    if ((hasLeftChild && !hasRightChild) || (!hasLeftChild && hasRightChild)) {
        // 현재 노드가 하나의 자식만 가지고 있으면, 왼쪽과 오른쪽 서브트리의 카운트에 1을 더함
        return leftCount + rightCount + 1;
    } else {
        // 현재 노드가 자식이 없거나 두 개의 자식을 가지고 있으면, 왼쪽과 오른쪽 서브트리의 카운트만 반환
        return leftCount + rightCount;
    }
}

///////////////////////////////////////////////////////////////////////////////////

// 새로운 이진 트리 노드를 생성하는 함수
BTNode *createBTNode(int item)
{
    BTNode *newNode = malloc(sizeof(BTNode));  // 메모리 할당
    newNode->item = item;     // 노드의 데이터 값 설정
    newNode->left = NULL;     // 왼쪽 자식 포인터 초기화
    newNode->right = NULL;    // 오른쪽 자식 포인터 초기화
    return newNode;           // 생성된 노드 반환
}

//////////////////////////////////////////////////////////////////////////////////

// 사용자 입력으로 이진 트리를 생성하는 함수
BTNode *createTree()
{
    Stack stack;            // 노드 처리를 위한 스택
    BTNode *root, *temp;    // 루트 노드와 임시 노드 포인터
    char s;                 // 문자 입력을 처리하기 위한 변수
    int item;               // 노드의 데이터 값

    stack.top = NULL;       // 스택 초기화
    root = NULL;            // 루트 노드 초기화
    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if(scanf("%d",&item) > 0)  // 정수 입력이 성공했을 경우
    {
        root = createBTNode(item);  // 루트 노드 생성
        push(&stack, root);        // 스택에 루트 노드 추가
    }
    else  // 정수 입력이 실패했을 경우(알파벳 등)
    {
        scanf("%c",&s);  // 버퍼에서 문자 제거
    }

    // 스택이 빌 때까지 노드 생성 계속
    while((temp = pop(&stack)) != NULL)
    {
        // 현재 노드의 왼쪽 자식 처리
        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if(scanf("%d",&item) > 0)  // 정수 입력이 성공했을 경우
        {
            temp->left = createBTNode(item);  // 왼쪽 자식 노드 생성
        }
        else  // 정수 입력이 실패했을 경우(알파벳 등)
        {
            scanf("%c",&s);  // 버퍼에서 문자 제거
            // NULL로 남김 (왼쪽 자식 없음)
        }

        // 현재 노드의 오른쪽 자식 처리
        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if(scanf("%d",&item) > 0)  // 정수 입력이 성공했을 경우
        {
            temp->right = createBTNode(item);  // 오른쪽 자식 노드 생성
        }
        else  // 정수 입력이 실패했을 경우(알파벳 등)
        {
            scanf("%c",&s);  // 버퍼에서 문자 제거
            // NULL로 남김 (오른쪽 자식 없음)
        }

        // 생성된 자식 노드들을 스택에 추가 (나중에 처리하기 위해)
        // 노드 처리 순서를 위해 오른쪽 자식을 먼저 스택에 추가
        if(temp->right != NULL)
            push(&stack, temp->right);
        if(temp->left != NULL)
            push(&stack, temp->left);
    }
    return root;  // 생성된 트리의 루트 반환
}

// 스택에 노드를 추가하는 함수(푸시)
void push(Stack *stack, BTNode *node)
{
    StackNode *temp;  // 새 스택 노드를 위한 포인터

    temp = malloc(sizeof(StackNode));  // 스택 노드에 메모리 할당
    if(temp == NULL)  // 메모리 할당 실패 시
        return;
    temp->btnode = node;  // 이진 트리 노드 연결
    if(stack->top == NULL)  // 스택이 비어있는 경우
    {
        stack->top = temp;   // 새 노드를 스택 맨 위로 설정
        temp->next = NULL;   // 다음 노드는 없음
    }
    else  // 스택에 노드가 있는 경우
    {
        temp->next = stack->top;  // 새 노드의 다음을 현재 스택 맨 위로 설정
        stack->top = temp;        // 스택 맨 위를 새 노드로 업데이트
    }
}

// 스택에서 노드를 꺼내는 함수(팝)
BTNode* pop(Stack *stack)
{
    StackNode *temp, *top;  // 스택 노드를 위한 포인터
    BTNode *ptr;            // 반환할 이진 트리 노드
    ptr = NULL;             // 초기값으로 NULL 설정

    top = stack->top;       // 현재 스택 맨 위 노드
    if(top != NULL)         // 스택이 비어있지 않은 경우
    {
        temp = top->next;   // 다음 노드 저장
        ptr = top->btnode;  // 이진 트리 노드 추출

        stack->top = temp;  // 스택 맨 위를 다음 노드로 업데이트
        free(top);          // 스택에서 제거된 노드의 메모리 해제
        top = NULL;         // 포인터 정리
    }
    return ptr;  // 추출한 이진 트리 노드 반환(또는 NULL)
}

// 이진 트리를 중위 순회로 출력하는 함수(왼쪽 서브트리 -> 루트 -> 오른쪽 서브트리)
void printTree(BTNode *node)
{
    if(node == NULL) return;  // 빈 노드면 함수 종료

    printTree(node->left);    // 왼쪽 서브트리 먼저 출력
    printf("%d ", node->item); // 현재 노드의 데이터 출력
    printTree(node->right);   // 오른쪽 서브트리 마지막에 출력
}

// 이진 트리의 모든 노드를 재귀적으로 제거하는 함수(후위 순회)
void removeAll(BTNode **node)
{
    if(*node != NULL)  // 노드가 존재하는 경우
    {
        removeAll(&((*node)->left));  // 먼저 왼쪽 서브트리의 모든 노드 제거
        removeAll(&((*node)->right)); // 그 다음 오른쪽 서브트리의 모든 노드 제거
        free(*node);                  // 현재 노드의 메모리 해제 
        *node = NULL;                 // 포인터를 NULL로 설정하여 참조 오류 방지
    }
}