/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
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

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
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
	headNode* headnode = NULL;

	do {
		printf("[----- [고승현] [2016039086] -----]\n");
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

		switch (command) {
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

	} while (command != 'q' && command != 'Q');

	return 1;
}

/*이중 포인터를 매개변수로 받는 경우 포인터에 저장된 
주소를 변경하겠다라는 의미이고 해당 함수에서 headNode구조체를 생성하고
해당 구조체의 주소를 이중포인터로 연결을 해줘야 해당 함수가 종료되더라고
연결관계가 유지 된다*/
int initialize(headNode** h) {
	headNode* temp = NULL;
	if (*h != NULL)
		freeList(*h);
	else {
		temp = (headNode*)malloc(sizeof(headNode));
		temp->first = NULL;
		*h = temp;
	}
	return 1;
}
/*select포인터 변수를 통해 모든 노드를 free해주고
마지막에는 headNode구조체도 해제해준다*/
int freeList(headNode* h) {
	listNode* select = h->first;
	listNode* prev = NULL;
	while (select != NULL) {
		prev = select;
		select = select->rlink;
		free(prev);
	}
	free(h);
	return 0;
}

/*출력*/
void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 마지막에 노드하나를 추가
 * 매개변수로 받은 값에 알맞게 노드를 생성하고 초기 값들을 할당하고
 * 반복문을 통해 마지막 노드를 찾고 연결해준다
 */
int insertLast(headNode* h, int key) {
	listNode* select = h->first;
	listNode* temp = (listNode*)malloc(sizeof(listNode));
	temp->key = key;
	temp->rlink = NULL;
	temp->llink = NULL;
	while (select->rlink != NULL) {
		select = select->rlink;
	}
	select->rlink = temp;
	temp->llink = select;
	temp->rlink = NULL;
	return 0;
}



/**
 * list의 마지막 노드 삭제
 * 노드가 하나만 존재하는 경우 바로 해제해주고 
 * 그 외에는 마지막까지 이동해서 해당 노드를 해제한다
 */
int deleteLast(headNode* h) {
	listNode* select = h->first;
	if (select->rlink == NULL) {
		free(select);
		h->first = NULL;
		return 0;
	}
	while (select->rlink != NULL) {
		select = select->rlink;
	}
	select->llink->rlink = NULL;
	free(select);

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 * 노드가 하나도 없는경우 바로 추가해주고
 * 그외의 경우는 노드간 연결, headNode구조체와의 연결을 
 * 실시한 후에 종료한다
 */
int insertFirst(headNode* h, int key) {
	listNode* temp;
	if (h->first == NULL) {
		temp = (listNode*)malloc(sizeof(listNode));
		temp->key = key;
		temp->rlink = NULL;
		temp->llink = NULL;
		h->first = temp;
	}
	else {
		temp = (listNode*)malloc(sizeof(listNode));
		temp->key = key;
		temp->rlink = NULL;
		temp->llink = NULL;
		h->first->llink = temp;
		temp->rlink = h->first;
		h->first = temp;
	}
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 * 노드가 하나뿐인경우 바로 해제하고
 * 그외의 경우는 노드를 제거하고 headNode구조체와
 * 다음노드의 연결을 만들어주고 종료한다
 */
int deleteFirst(headNode* h) {
	listNode* select = h->first;
	if (select->rlink == NULL) {
		free(select);
		h->first = NULL;
		return 0;
	}
	h->first = select->rlink;
	select->rlink->llink = NULL;
	free(select);
	return 0;
}



/*
 * 리스트의 링크를 역순으로 재 배치
 * 각 노드의 llink와 rlink의 연결을 바꾸어준다
 * 그리고 headNode->first를 마지막노드와 연결해준다
 */
int invertList(headNode* h) {
	listNode* select = h->first;
	listNode* temp;
	listNode* preview = NULL;
	for (; select; select = select->llink) {
		temp = select->llink;
		select->llink = select->rlink;
		select->rlink = temp;
		preview = select;
	}
	h->first = preview;
	return 0;
}




/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
노드가 하나도 없는 경우 바로 연결해주고 노드가 하나 뿐인 경우 조건에 맞으면
insertFirst함수를 호출하고 그외에는 비교해서 노드를 넣어준다 */
int insertNode(headNode* h, int key) {
	listNode* temp;
	listNode* preview = NULL;
	listNode* select = h->first;
	if (h == NULL)
		return 0;

	temp = (listNode*)malloc(sizeof(listNode));
	temp->key = key;
	temp->llink = NULL;
	temp->rlink = NULL;
	if (select == NULL) {
		h->first = temp;
		return 0;
	}
	if (temp->key <= select->key) {
		insertFirst(h, temp->key);
		free(temp);
		return 0;
	}

	for (; select; select = select->rlink) {
		if (key <= select->key) {
			preview->rlink = temp;
			temp->llink = preview;
			select->llink = temp;
			temp->rlink = select;
			break;
		}
		preview = select;
	}
	if (select == NULL) {
		preview->rlink = temp;
		temp->llink = preview;
		temp->rlink = NULL;
	}
	return 0;
}


/*
 * list에서 key에 대한 노드 삭제
입력받은 key값과 일치하면 첫번쨰 노드의 경우는 deleteFirst함수로 제거하고
그외의 경우는 조건문과 일치하면 삭제를 한다
 */
int deleteNode(headNode* h, int key) {
	listNode* select = h->first;
	if (select == NULL)
		return 0;
	if (select->key == key) {
		deleteFirst(h);
		return 0;
	}
	for (; select; select = select->rlink) {
		if (select->key == key) {
			select->llink->rlink = select->rlink;
			select->rlink->llink = select->llink;
			free(select);
			break;
		}
	}
	return 1;


}
