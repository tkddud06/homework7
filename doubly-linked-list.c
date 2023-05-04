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

/* �ʿ��� ������� �߰� if necessary */

typedef struct Node { // ������ũ�帮��Ʈ�� ��带 ��Ÿ���� ����ü
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head { // ������ũ�帮��Ʈ�� ��� ������ �� ����ü
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ���� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
        - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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

	do{ // �Է¹޴� ���ڿ� ����, �� ��ɵ��� �����ϰ�, q�� ������ �����Ѵ�.
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		printf("[--------------  [�ֻ�]  	[2022041062]  --------------]\n");
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

	return 0; // ���� ���Ḧ ǥ���ϱ� ���� 0���� ����
}


int initialize(headNode** h) {
	if(*h != NULL) // h�� ����Ʈ�� �̹� ����ִ� ���
	{
		freeList(*h); // ������ ����
	}
	*h = (headNode*)malloc(sizeof(headNode)); // h�� ���ο� ��� �����Ҵ� (�̶�, h�� �ٲ��־�� �ϹǷ�, ���� �����ͷ� ���� ����)
	(*h)->first = NULL; // ù��° ��尡 ����� �����Ƿ�, NULL�� �ʱ�ȭ
	return 1;
}

int freeList(headNode* h){
	listNode* prev = h->first;
	listNode* ptr = prev; // ������ ����ų listNode ������ ���� ptr, prev�� �����. prev�� ptr�� ���󰡸�, ���������� �ʱ�ȭ�� ������ ��带 ����Ų��.
	while(prev) // prev == ptr�� NULL�� ����ų ������(��� ��带 �� free�� ������) �ݺ��Ѵ�
	{
		ptr = ptr->rlink; // ptr�� ���� ���� �̵���Ų��
		free(prev); // prev, �� ptr�� ���� ��带 free�Ѵ�
		prev = ptr; // prev�� ���� ���� �̵���Ų��
	}
	free(h); // ���������� h�� free�Ѵ�
	return 0;
}


void printList(headNode* h) { // ������ũ�帮��Ʈ�� ����Ѵ�
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) { // ��ü�� ���鼭 ���
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i); // ������ ����
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* ptr = h->first;
	if(!ptr) // ù��° ��忡 �����ϰ� �Ǵ� ��� (�� ����Ʈ�� ���)
	{
		insertFirst(h, key);
		return 0;
	}
	while(ptr->rlink != NULL) // ptr�� ������ ��带 ����ų ������ �ݺ��Ѵ�
	{
		ptr = ptr->rlink;
	}
	ptr->rlink = (listNode*)malloc(sizeof(listNode)); // ptr�� ������, �� ������ ��ġ�� ���ο� ��带 �����Ҵ� �Ѵ�
	ptr->rlink->key = key; // �ش� �� ��忡 key���� �����Ѵ�
	ptr->rlink->llink = ptr; // �ش� �� ����� ���� ��ũ�� ���� ����� ptr�� �����Ų��
	ptr->rlink->rlink = NULL; // �ش� �� ����� ������ ��ũ�� NULL�� �����Ѵ�
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	listNode* temp = h->first; // ���� ��带 ����Ű�� �� temp�� �����
	if(!temp) // �� ����Ʈ�� ���
	{
		printf("nothing to delete.\n");
		return 1;
	}
	while(temp->rlink != NULL) // temp�� ������ ��带 ����ų ������ �ݺ��Ѵ�
	{
		temp = temp->rlink;
	}
	if(temp == h->first) // ���� ��尡 ù��° ����� ���
	{
		deleteFirst(h);
		return 0;
	}

	temp->llink->rlink = NULL; // ������ ����� ���� ����� rlink�� NULL�� �����
	free(temp); // temp�� free�Ѵ�
	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	
	listNode* newnode = (listNode*)malloc(sizeof(listNode)); // ���ο� ��� �����Ҵ�
	newnode->key = key; // �ش� �� ��忡 key���� �����Ѵ�
	newnode->rlink = h->first; // �ش� �� ����� rlink�� ������ ù��° ����� �ּҸ� �����Ѵ� (�� ����Ʈ ���¿��� ���, NULL)
	newnode->llink = NULL;
	if(newnode->rlink) // ���� ���� ù��° ��尡 �־��ٸ� (�� ����Ʈ�� �ƴϿ��ٸ�)
	{
	newnode->rlink->llink = newnode; // �� ����� ���� ����� llink�� newnode�� ������
	}
	h->first = newnode; // ����� first�� newnode�� ������

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	listNode* temp = h->first; // ���� ����� ù ��带 temp�� ����Ų��
	if(!temp) // �� ����Ʈ�� ���
	{
		printf("nothing to delete.\n");
		return 1;
	}
	h->first = temp->rlink; // ����� first�� ù ����� ���� ���� �ٲ۴�
	temp->rlink->llink = NULL; // ���� ����� ���� ���, �� ���ܵ� ù��° ����� llink�� NULL�� �����Ѵ�
	free(temp); // temp�� free�Ѵ�
	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	listNode* ptr = h->first;
	listNode* prev = NULL; // �ٲ� ��带 ����ų ptr, �ٲ� ����� ���� ��带 ����ų prev ����
	if(ptr == NULL) // �� ����Ʈ�� ���
	{
		printf("nothing to invert...\n");
		return 1;
	}
	
	while(ptr != NULL) // ������ ����� ������ �ݺ�
	{
		ptr->llink = ptr->rlink; // llink�� rlink�� �ٲ�
		ptr->rlink = prev; // �̸� �����ص� prev�� ���� rlink�� �ٲ� (�ش� �۾��� ����, rlink�� llink�� ���� �ٲ�� ��)
		prev = ptr; // prev�� ���� ptr ��ġ�� �̵�
		ptr = ptr->llink; // ptr�� ���� ��� ��ġ�� �̵�
	}
	h->first = prev; // ����������, h�� first�� ������
	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	listNode* ptr = h->first;
	listNode* temp; // ����Ʈ�� ������ ����ų ptr�� insert ������ ���� temp ����
	if(!ptr || ptr->key > key) // ù��° ��忡 �����ϰ� �Ǵ� ��� (�� ����Ʈ�� ��� Ȥ�� ù��° ����� Ű���� �Է¹��� Ű�� ���� ���)
	{
		insertFirst(h, key);
		return 0;
	}
	while(ptr->rlink != NULL && ptr->rlink->key <= key) // ptr�� ���� ��尡 �������� �ƴϰ�, �ش� ���� ����� Ű�� �Է¹��� key���� �۰ų� ������ �ݺ�(Ŀ���� ����)
	{
		ptr = ptr->rlink;
	}
	temp = ptr->rlink; // ���� ptr�� ���� ��带 temp�� �ӽ÷� ����
	ptr->rlink = (listNode*)malloc(sizeof(listNode)); // ptr�� ������, ptr ���� ����� ���̿� ���ο� ��带 �����Ҵ� �Ѵ�
	ptr->rlink->key = key; // �ش� �� ��忡 key���� �����Ѵ�
	ptr->rlink->llink = ptr; // �ش� �� ����� ���� ��ũ�� ���� ����� ptr�� �����Ų��
	ptr->rlink->rlink = temp; // �ش� �� ����� ������ ��ũ�� temp�� �����Ѵ�
	if(temp != NULL) // �߰��� ����� ������ ��尡 NULL�� �ƴ϶�� (�߰��� ��尡 ������ ��尡 �ƴ϶�, ������ ���̿� �ִ� ���)
	{
		temp->llink = ptr->rlink; // �߰��� ����� ������ ����� llink�� �߰��� ���� �̾���
	}
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	listNode* ptr = h->first;
	if(!ptr) // �� ����Ʈ�� ���
	{
		printf("nothing to delete.\n");
		return 1;
	}
	
	if (ptr->key == key) // ù��° ��带 ������ �ϴ� ���
	{
		deleteFirst(h);
		return 0;
	}
	while(ptr != NULL && ptr->key != key) // ptr�� ����Ű�� ��尡 �������� �ƴϰ�, �ش� ����� Ű�� �Է¹��� Ű�϶����� �ݺ�
	{
		ptr = ptr->rlink;
	}
	if(ptr == NULL) // ������ �������� ��ã�Ҵٸ�
	{
		printf("cannot find the node for key = %d\n", key);
		return 1;
	}
	// ã�� ���
	ptr->llink->rlink = ptr->rlink; // ���� ����� ���� ����� rlink�� ���� ����� ������ ���� �̾���

	if(ptr->rlink != NULL) // ���� ����� ������ ��尡 NULL�� �ƴ϶�� (���� ��尡 ������ ��尡 �ƴ϶�, ������ ���̿� �ִ� ���)
	{
		ptr->rlink->llink = ptr->llink; // ���� ����� ������ ����� llink�� ���� ����� ���� ���� �̾���
	}
	free(ptr); // ptr free
	return 0;
}


