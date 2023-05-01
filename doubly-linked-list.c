/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 if necessary */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 0; // 정상 종료를 표시하기 위해 0으로 변경
}


int initialize(headNode** h) {
	if(!h) // h에 리스트가 이미 들어있는 경우
	{
		freeList(h); // 프리를 진행
	}
	*h = (headNode*)malloc(sizeof(headNode)); // h에 새로운 헤더 동적할당 (이때, h를 바꾸주어야 하므로, 이중 포인터로 받은 것임)
	(*h)->first = NULL; // 첫번째 노드가 현재는 없으므로, NULL로 초기화
	return 1;
}

int freeList(headNode* h){
	listNode prev = h->first;
	listNode* ptr = prev; // 노드들을 가르킬 listNode 포인터 변수 ptr, prev을 만든다. prev는 ptr을 따라가며, 실질적으로 초기화를 진행할 노드를 가리킨다.
	while(prev) // prev == ptr이 NULL을 가르킬 때까지(모든 노드를 다 free할 때까지) 반복한다
	{
		ptr = ptr->rlink; // ptr을 다음 노드로 이동시킨다
		free(prev); // prev, 즉 ptr의 이전 노드를 free한다
		prev = ptr; // prev를 다음 노드로 이동시킨다
	}
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* ptr = h->first;
	if(!ptr) // 첫번째 노드에 삽입하게 되는 경우
	{
		insertFirst(h, key);
		return 0;
	}
	while(!ptr->rlink) // ptr이 마지막 끝 노드의 이전 노드를 가르킬 때까지 반복한다
	{
		ptr = ptr->rlink;
	}
	ptr->rlink = (listNode*)malloc(sizeof(listNode)); // ptr의 오른쪽, 즉 마지막 위치에 새로운 노드를 동적할당 한다
	ptr->rlink->key = key; // 해당 새 노드에 key값을 대입한다
	ptr->rlink->llink = ptr; // 해당 새 노드의 왼쪽 링크에 이전 노드인 ptr을 연결시킨다
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	
	listNode* newnode = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 동적할당
	newnode->key = key; // 해당 새 노드에 key값을 대입한다
	newnode->rlink = h->first; // 해당 새 노드의 rlink에 원래의 첫번째 노드의 주소를 연결한다 (빈 리스트 상태였을 경우, NULL)
	// newnode->llink = h; /////////////////////////////////// 해당 부분 관련해서는 영상 참고해야 할 듯
	newnode->rlink->llink = newnode; // 새 노드의 다음 노드의 llink를 newnode로 재조정
	h->first = newnode; // 헤더의 first를 newnode로 재조정

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* temp = h->first; // 지울 노드인 첫 노드를 temp로 가르킨다
	h->first = temp->rlink; // 헤더의 first를 첫 노드의 다음 노드로 바꾼다
	// temp->rlink->llink =  ///////////////////////// 해당 부분 관련해서는 영상 참고해야 할 듯 // 첫 노드의 다음 노드의 llink를 변경.
	free(temp); // temp를 free한다
	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 1;
}


