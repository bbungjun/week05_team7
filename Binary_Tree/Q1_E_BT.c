#include <stdio.h>  // 표준 입출력 라이브러리 포함
#include <stdlib.h> // 메모리 할당을 위한 malloc, free 함수 포함

// 이진 트리 노드 구조체 정의
typedef struct _btnode{
    int item;               // 노드의 값
    struct _btnode *left;   // 왼쪽 자식 노드 포인터
    struct _btnode *right;  // 오른쪽 자식 노드 포인터
} BTNode;   // You should not change the definition of BTNode

// 스택 노드 구조체 정의 - 트리 생성 시 사용
typedef struct _stackNode{
    BTNode *btnode;         // 이진 트리 노드 포인터
    struct _stackNode *next; // 다음 스택 노드 포인터
}StackNode;

// 스택 구조체 정의
typedef struct _stack{
    StackNode *top;         // 스택의 최상위 노드 포인터
}Stack;

///////////////////////// function prototypes ////////////////////////////////////

// 함수 프로토타입 선언
int identical(BTNode *tree1, BTNode *tree2); // 두 트리의 구조적 동일성 검사 함수

BTNode* createBTNode(int item);  // 새 이진 트리 노드 생성 함수

BTNode* createTree();            // 이진 트리 생성 함수
void push(Stack *stk, BTNode *node); // 스택에 노드 추가 함수
BTNode* pop(Stack *stk);         // 스택에서 노드 제거 함수

void printTree(BTNode *node);    // 트리 출력 함수
void removeAll(BTNode **node);   // 트리 전체 메모리 해제 함수

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    int c, s;          // 사용자 선택 및 결과 저장 변수
    char e;            // 문자 입력을 위한 변수
    BTNode *root1, *root2; // 두 이진 트리의 루트 노드

    root1 = NULL;      // 첫 번째 트리 초기화
    root2 = NULL;      // 두 번째 트리 초기화
    c = 1;             // 메뉴 선택 초기값

    // 메뉴 출력
    printf("1: Create a binary tree1.\n");
    printf("2: Create a binary tree2.\n");
    printf("3: Check whether two trees are structurally identical.\n");
    printf("0: Quit;\n");

    // 사용자가 0을 입력할 때까지 메뉴 반복
    while(c != 0){
        printf("Please input your choice(1/2/3/0): ");
        if(scanf("%d", &c) > 0) // 숫자 입력 성공 시
        {
            switch(c)
            {
            case 1: // 첫 번째 트리 생성
                removeAll(&root1); // 기존 트리 제거
                printf("Creating tree1:\n");
                root1 = createTree(); // 새 트리 생성
                printf("The resulting tree1 is: ");
                printTree(root1); // 생성된 트리 출력
                printf("\n");
                break;
            case 2: // 두 번째 트리 생성
                removeAll(&root2); // 기존 트리 제거
                printf("Creating tree2:\n");
                root2 = createTree(); // 새 트리 생성
                printf("The resulting tree2 is: ");
                printTree(root2); // 생성된 트리 출력
                printf("\n");
                break;
            case 3: // 두 트리의 구조적 동일성 검사
                s = identical(root1, root2); // 구조적 동일성 함수 호출
                if(s){
                    printf("Both trees are structurally identical.\n");
                }
                else{
                    printf("Both trees are different.\n");
                }
                removeAll(&root1); // 첫 번째 트리 메모리 해제
                removeAll(&root2); // 두 번째 트리 메모리 해제
                break;
            case 0: // 프로그램 종료 선택
                removeAll(&root1); // 첫 번째 트리 메모리 해제
                removeAll(&root2); // 두 번째 트리 메모리 해제
                break;
            default: // 잘못된 메뉴 선택
                printf("Choice unknown;\n");
                break;
            }
        }
        else // 숫자가 아닌 입력 처리
        {
            scanf("%c",&e);
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

// 두 이진 트리가 구조적으로 동일한지 확인하는 함수
int identical(BTNode *tree1, BTNode *tree2)
{
    // 두 트리가 모두 비어있는 경우(NULL) - 구조적으로 동일함
    if (tree1 == NULL && tree2 == NULL)
        return 1;
    
    // 한 트리만 비어있는 경우 - 구조적으로 다름
    if (tree1 == NULL || tree2 == NULL)
        return 0;
    
    // 현재 노드의 값이 다른 경우 - 구조적으로 다름
    if (tree1->item != tree2->item)
        return 0;
    
    // 현재 노드의 값이 같으면 왼쪽과 오른쪽 서브트리를 재귀적으로 검사
    // 양쪽 서브트리가 모두 동일해야 전체가 동일함
    return identical(tree1->left, tree2->left) && identical(tree1->right, tree2->right);
}

/////////////////////////////////////////////////////////////////////////////////

// 새 이진 트리 노드 생성 함수
BTNode *createBTNode(int item){
    BTNode *newNode = malloc(sizeof(BTNode)); // 메모리 할당
    newNode->item = item;     // 노드 값 설정
    newNode->left = NULL;     // 왼쪽 자식 초기화
    newNode->right = NULL;    // 오른쪽 자식 초기화
    return newNode;           // 생성된 노드 반환
}

//////////////////////////////////////////////////////////////////////////////////

// 이진 트리 생성 함수
BTNode *createTree()
{
    Stack stk;               // 스택 선언
    BTNode *root, *temp;     // 루트 노드와 임시 노드 포인터
    char s;                  // 문자 입력을 위한 변수
    int item;                // 노드 값

    stk.top = NULL;          // 스택 초기화
    root = NULL;             // 루트 노드 초기화

    // 사용자 안내 메시지
    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if(scanf("%d",&item) > 0) // 정수 입력 성공 시
    {
        root = createBTNode(item); // 루트 노드 생성
        push(&stk, root);         // 스택에 루트 노드 추가
    }
    else // 정수가 아닌 입력 처리
    {
        scanf("%c",&s);
    }

    // 스택이 빌 때까지 반복하며 트리 구성
    while((temp = pop(&stk)) != NULL)
    {
        // 왼쪽 자식 노드 처리
        printf("Enter an integer value for the Left child of %d: ", temp->item);
        if(scanf("%d",&item) > 0) // 정수 입력 성공 시
        {
            temp->left = createBTNode(item); // 왼쪽 자식 노드 생성
        }
        else // 정수가 아닌 입력 처리
        {
            scanf("%c",&s);
        }

        // 오른쪽 자식 노드 처리
        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if(scanf("%d",&item) > 0) // 정수 입력 성공 시
        {
            temp->right = createBTNode(item); // 오른쪽 자식 노드 생성
        }
        else // 정수가 아닌 입력 처리
        {
            scanf("%c",&s);
        }

        // 자식 노드들을 스택에 추가 (순서가 중요: 오른쪽 먼저, 왼쪽 나중에)
        if(temp->right != NULL)
            push(&stk, temp->right);
        if(temp->left != NULL)
            push(&stk, temp->left);
    }
    return root; // 생성된 트리의 루트 반환
}

// 스택에 노드 추가 함수
void push(Stack *stk, BTNode *node){
    StackNode *temp;

    temp = malloc(sizeof(StackNode)); // 새 스택 노드 메모리 할당
    if(temp == NULL)        // 메모리 할당 실패 시
        return;
    temp->btnode = node;    // 이진 트리 노드 연결
    
    if(stk->top == NULL){   // 스택이 비어있을 때
        stk->top = temp;    // 첫 노드 설정
        temp->next = NULL;  // 다음 노드는 없음
    }
    else{                   // 스택에 노드가 있을 때
        temp->next = stk->top; // 기존 top을 다음 노드로 설정
        stk->top = temp;     // 새 노드를 top으로 설정
    }
}

// 스택에서 노드 제거 함수
BTNode* pop(Stack *stk){
    StackNode *temp, *top;  // 임시 노드 포인터
    BTNode *ptr;            // 반환할 이진 트리 노드
    ptr = NULL;             // 초기값 설정

    top = stk->top;         // 현재 스택 최상단 노드
    if(top != NULL){        // 스택이 비어있지 않을 때
        temp = top->next;   // 다음 노드 저장
        ptr = top->btnode;  // 반환할 이진 트리 노드 저장

        stk->top = temp;    // 스택 최상단 갱신
        free(top);          // 메모리 해제
        top = NULL;         // 포인터 초기화
    }
    return ptr;             // 이진 트리 노드 반환
}

// 트리 중위 순회 출력 함수 (왼쪽-루트-오른쪽)
void printTree(BTNode *node){
    if(node == NULL) return; // 빈 노드면 종료

    printTree(node->left);   // 왼쪽 서브트리 먼저 출력
    printf("%d ", node->item); // 현재 노드 값 출력
    printTree(node->right);  // 오른쪽 서브트리 출력
}

// 트리 전체 메모리 해제 함수 (후위 순회: 왼쪽-오른쪽-루트)
void removeAll(BTNode **node){
    if(*node != NULL){
        removeAll(&((*node)->left));  // 왼쪽 서브트리 메모리 해제
        removeAll(&((*node)->right)); // 오른쪽 서브트리 메모리 해제
        free(*node);                  // 현재 노드 메모리 해제
        *node = NULL;                 // 포인터 초기화
    }
}