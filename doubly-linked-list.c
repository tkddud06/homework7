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

typedef struct Node { // 더블리링크드리스트의 노드를 나타내는 구조체
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head { // 더블리링크드리스트의 헤더 역할을 할 구조체
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

	do{ // 입력받는 문자에 따라, 각 기능들을 수행하고, q를 받으면 종료한다.
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		printf("[--------------  [최상영]  	[2022041062]  --------------]\n");
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
	if(*h != NULL) // h에 리스트가 이미 들어있는 경우
	{
		freeList(*h); // 프리를 진행
	}
	*h = (headNode*)malloc(sizeof(headNode)); // h에 새로운 헤더 동적할당 (이때, h를 바꾸주어야 하므로, 이중 포인터로 받은 것임)
	(*h)->first = NULL; // 첫번째 노드가 현재는 없으므로, NULL로 초기화
	return 1;
}

int freeList(headNode* h){
	listNode* prev = h->first;
	listNode* ptr = prev; // 노드들을 가르킬 listNode 포인터 변수 ptr, prev을 만든다. prev는 ptr을 따라가며, 실질적으로 초기화를 진행할 노드를 가리킨다.
	while(prev) // prev == ptr이 NULL을 가르킬 때까지(모든 노드를 다 free할 때까지) 반복한다
	{
		ptr = ptr->rlink; // ptr을 다음 노드로 이동시킨다
		free(prev); // prev, 즉 ptr의 이전 노드를 free한다
		prev = ptr; // prev를 다음 노드로 이동시킨다
	}
	free(h); // 마지막으로 h를 free한다
	return 0;
}


void printList(headNode* h) { // 더블리링크드리스트를 출력한다
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) { // 전체를 돌면서 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i); // 원소의 개수
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* ptr = h->first;
	if(!ptr) // 첫번째 노드에 삽입하게 되는 경우 (빈 리스트인 경우)
	{
		insertFirst(h, key);
		return 0;
	}
	while(ptr->rlink != NULL) // ptr이 마지막 노드를 가르킬 때까지 반복한다
	{
		ptr = ptr->rlink;
	}
	ptr->rlink = (listNode*)malloc(sizeof(listNode)); // ptr의 오른쪽, 즉 마지막 위치에 새로운 노드를 동적할당 한다
	ptr->rlink->key = key; // 해당 새 노드에 key값을 대입한다
	ptr->rlink->llink = ptr; // 해당 새 노드의 왼쪽 링크에 이전 노드인 ptr을 연결시킨다
	ptr->rlink->rlink = NULL; // 해당 새 노드의 오른쪽 링크는 NULL로 지정한다
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* temp = h->first; // 지울 노드를 가리키게 될 temp를 만든다
	if(!temp) // 빈 리스트인 경우
	{
		printf("nothing to delete.\n");
		return 1;
	}
	while(temp->rlink != NULL) // temp가 마지막 노드를 가르킬 때까지 반복한다
	{
		temp = temp->rlink;
	}
	if(temp == h->first) // 지울 노드가 첫번째 노드일 경우
	{
		deleteFirst(h);
		return 0;
	}

	temp->llink->rlink = NULL; // 마지막 노드의 이전 노드의 rlink를 NULL로 만든다
	free(temp); // temp를 free한다
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	
	listNode* newnode = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 동적할당
	newnode->key = key; // 해당 새 노드에 key값을 대입한다
	newnode->rlink = h->first; // 해당 새 노드의 rlink에 원래의 첫번째 노드의 주소를 연결한다 (빈 리스트 상태였을 경우, NULL)
	newnode->llink = NULL;
	if(newnode->rlink) // 만약 원래 첫번째 노드가 있었다면 (빈 리스트가 아니였다면)
	{
	newnode->rlink->llink = newnode; // 새 노드의 다음 노드의 llink를 newnode로 재조정
	}
	h->first = newnode; // 헤더의 first를 newnode로 재조정

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* temp = h->first; // 지울 노드인 첫 노드를 temp로 가르킨다
	if(!temp) // 빈 리스트인 경우
	{
		printf("nothing to delete.\n");
		return 1;
	}
	h->first = temp->rlink; // 헤더의 first를 첫 노드의 다음 노드로 바꾼다
	temp->rlink->llink = NULL; // 지울 노드의 다음 노드, 즉 남겨둘 첫번째 노드의 llink는 NULL로 조정한다
	free(temp); // temp를 free한다
	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* ptr = h->first;
	listNode* prev = NULL; // 바꿀 노드를 가리킬 ptr, 바꿀 노드의 이전 노드를 가리킬 prev 생성
	if(ptr == NULL) // 빈 리스트인 경우
	{
		printf("nothing to invert...\n");
		return 1;
	}
	
	while(ptr != NULL) // 마지막 노드일 때까지 반복
	{
		ptr->llink = ptr->rlink; // llink를 rlink로 바꿈
		ptr->rlink = prev; // 미리 저장해둔 prev를 통해 rlink도 바꿈 (해당 작업을 통해, rlink와 llink가 서로 바뀌게 됨)
		prev = ptr; // prev를 현재 ptr 위치로 이동
		ptr = ptr->llink; // ptr은 다음 노드 위치로 이동
	}
	h->first = prev; // 마지막으로, h의 first를 재조정
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* ptr = h->first;
	listNode* temp; // 리스트의 노드들을 가르킬 ptr과 insert 과정을 도울 temp 생성
	if(!ptr || ptr->key > key) // 첫번째 노드에 삽입하게 되는 경우 (빈 리스트인 경우 혹은 첫번째 노드의 키보다 입력받은 키가 작은 경우)
	{
		insertFirst(h, key);
		return 0;
	}
	while(ptr->rlink != NULL && ptr->rlink->key <= key) // ptr의 다음 노드가 마지막이 아니고, 해당 다음 노드의 키가 입력받은 key보다 작거나 같으면 반복(커지면 정지)
	{
		ptr = ptr->rlink;
	}
	temp = ptr->rlink; // 원래 ptr의 다음 노드를 temp에 임시로 저장
	ptr->rlink = (listNode*)malloc(sizeof(listNode)); // ptr의 오른쪽, ptr 다음 노드의 사이에 새로운 노드를 동적할당 한다
	ptr->rlink->key = key; // 해당 새 노드에 key값을 대입한다
	ptr->rlink->llink = ptr; // 해당 새 노드의 왼쪽 링크에 이전 노드인 ptr을 연결시킨다
	ptr->rlink->rlink = temp; // 해당 새 노드의 오른쪽 링크는 temp로 지정한다
	if(temp != NULL) // 추가할 노드의 오른쪽 노드가 NULL이 아니라면 (추가할 노드가 마지막 노드가 아니라, 노드들의 사이에 있는 경우)
	{
		temp->llink = ptr->rlink; // 추가할 노드의 오른쪽 노드의 llink를 추가할 노드로 이어줌
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* ptr = h->first;
	if(!ptr) // 빈 리스트인 경우
	{
		printf("nothing to delete.\n");
		return 1;
	}
	
	if (ptr->key == key) // 첫번째 노드를 지워야 하는 경우
	{
		deleteFirst(h);
		return 0;
	}
	while(ptr != NULL && ptr->key != key) // ptr이 가리키는 노드가 마지막이 아니고, 해당 노드의 키가 입력받은 키일때까지 반복
	{
		ptr = ptr->rlink;
	}
	if(ptr == NULL) // 끝까지 돌았지만 못찾았다면
	{
		printf("cannot find the node for key = %d\n", key);
		return 1;
	}
	// 찾은 경우
	ptr->llink->rlink = ptr->rlink; // 지울 노드의 왼쪽 노드의 rlink를 지울 노드의 오른쪽 노드로 이어줌

	if(ptr->rlink != NULL) // 지울 노드의 오른쪽 노드가 NULL이 아니라면 (지울 노드가 마지막 노드가 아니라, 노드들의 사이에 있는 경우)
	{
		ptr->rlink->llink = ptr->llink; // 지울 노드의 오른쪽 노드의 llink를 지울 노드의 왼쪽 노드로 이어줌
	}
	free(ptr); // ptr free
	return 0;
}


