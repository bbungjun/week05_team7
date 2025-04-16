//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode* removeNodeFromTree(BSTNode *root, int value);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("3: Delete key from the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 3:
			printf("Input an integer that you want to remove from the Binary Search Tree: ");
			scanf("%d", &i);
			removeNodeFromTree(root, i);
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS2(BSTNode *root)
{
	/* add your code here */
	if (root == NULL) return;
	Stack stack; // 후위 순회 출력용 스택
	stack.top = NULL;
	Stack roots; // 루트 관리용 스택
	roots.top = NULL;

	BSTNode *cur;
	push(&roots, root);

	while(!isEmpty(&roots)) {
		cur = pop(&roots);
		push(&stack, cur); // 루트-오른쪽 자식-왼쪽 자식 순으로 stack에 push됨
		if (cur->left != NULL) push(&roots, cur->left);
		if (cur->right != NULL) push(&roots, cur->right); // 오른쪽 자식을 왼쪽 자식보다 먼저 roots에서 pop해서 결과적으로 stack에서는 왼쪽 자식보다 나중에 pop됨
	}

	while(!isEmpty(&stack)) {
		cur = pop(&stack); // 왼쪽 자식-오른쪽 자식-루트 순으로 pop됨
		printf("%d ", cur->item);
	}

	return;
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root. Make recursive function. */
BSTNode* removeNodeFromTree(BSTNode *root, int value)
{
	/* add your code here */
	if (root == NULL) return NULL;
    
    if (value < root->item) root->left = removeNodeFromTree(root->left, value);
    else if (value > root->item) root->right = removeNodeFromTree(root->right, value);
    else {
        // Case 1. 리프 노드를 제거하는 경우
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL; // 부모의 왼쪽/오른쪽 포인터를 NULL로 한다.
        }
        // Case 2. 자식이 1개 있는 노드를 제거하는 경우
        else if (root->left != NULL && root->right == NULL) {
            BSTNode *tmp = root->left;
            free(root);
            return tmp; // 부모의 왼쪽/오른쪽 포인터를 삭제할 노드의 (왼쪽) 자식으로 업데이트한다.
        }
        else if (root->left == NULL && root->right != NULL) {
            BSTNode *tmp = root->right;
            free(root);
            return tmp; // 부모의 왼쪽/오른쪽 포인터를 삭제할 노드의 (오른쪽) 자식으로 업데이트한다.
        }
        // Case 3. 자식이 2개 있는 노드를 제거하는 경우
        else {
            BSTNode* predecessor = root->left;
            while (predecessor->right != NULL) predecessor = predecessor->right; // 삭제할 노드의 선임자(작은 값들중 최대값)를 찾는다.
            root->item = predecessor->item; // 선임자의 노드의 데이터를 삭제할 노드의 위치에 복사한다.
            root->left = removeNodeFromTree(root->left, predecessor->item); // 옮긴 노드를 삭제한다.
			// 옮긴 노드에 자식이 없으면 Case 1, 자식이 1개만 있으면 Case 2에 따라 노드를 삭제한다.
        }
    }
    return root;
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
