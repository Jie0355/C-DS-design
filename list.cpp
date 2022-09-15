#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "list.h"

/* Function Realization  */
int LinkListInit(LinkList &L) {
	L = (LinkList)malloc(sizeof(struct Node));
	if (L == NULL) return _ERROR_;
	L->next = NULL;
	return 0;
}
void LinkListDestory(LinkList &L) {
	LinkList tmpNode;
	while (L) {
		tmpNode = L->next;
		L = L->next;
		free(tmpNode);
	}
}
bool isLinkListEmpty(LinkList L) {
	if (L->next == NULL) return true;
	else return false;
}
void SortTheList(LinkList &L, int mode) {
	long long tmpCurr, tmpNext;
	ElemType temp;
	LinkList currPtr, nextPtr;
	LinkList headPtr = L->next, tailPtr = NULL;
	if (L == NULL || L->next == NULL) return;
	while (headPtr != tailPtr) {
		currPtr = headPtr;
		nextPtr = currPtr->next;
		while (currPtr->next != tailPtr) {
			if (mode == 1) {
				tmpCurr = 0, tmpNext = 0;
				for (int i = 0; i < strlen(currPtr->data.no); i ++)
					tmpCurr = tmpCurr * 10 + (currPtr->data.no[i] - '0');
				for (int i = 0; i < strlen(nextPtr->data.no); i ++)
					tmpNext = tmpNext * 10 + (nextPtr->data.no[i] - '0');
				if (tmpCurr > tmpNext) {
					temp = currPtr->data;
					currPtr->data = nextPtr->data;
					nextPtr->data = temp;
				}
			}
			else if (mode == 2 && strlen(currPtr->data.level) < strlen(nextPtr->data.level)) {
				temp = currPtr->data;
				currPtr->data = nextPtr->data;
				nextPtr->data = temp;
			}
			else if (mode == 3) {
				tmpCurr = 0, tmpNext = 0;
				for (int i = 0; i < strlen(currPtr->data.fare); i ++)
					tmpCurr = tmpCurr * 10 + (currPtr->data.fare[i] - '0');
				for (int i = 0; i < strlen(nextPtr->data.fare); i ++)
					tmpNext = tmpNext * 10 + (nextPtr->data.fare[i] - '0');
				if (tmpCurr > tmpNext) {
					temp = currPtr->data;
					currPtr->data = nextPtr->data;
					nextPtr->data = temp;
				}
			}
			currPtr = nextPtr;
			nextPtr = nextPtr->next;
		}
		tailPtr = currPtr;
	}
}
int AddNodeToHead(LinkList &L, ElemType e) {
	LinkList addNode;
	addNode = (LinkList)malloc(sizeof(struct Node));
	if (addNode == NULL) return _ERROR_;
	addNode->data = e;
	addNode->next = L->next;
	L->next = addNode;
	return 0;
}
int DeleteTheKTNode(LinkList &L, char k[10]) {
	LinkList p, ptr;
	p = L; ptr = p->next;
	while (ptr) {
		if (!strcmp(ptr->data.no, k)) {
			p->next = ptr->next;
			free(ptr);
			return 0;
		} else p = ptr;
		ptr = p->next;
	}
	return _ERROR_;
}
int GetTheNOkNode(LinkList L, char k[10], ElemType &e) {
	while (L->next) {
		L = L->next;
		if (!strcmp(L->data.no, k)) {
			e = L->data;
			return 0;
		}
	}
	return _ERROR_;
}
void PrintTheList(LinkList L) {
	if (isLinkListEmpty(L)) {
		printf(" >> 景点信息为空！请尝试新建景点信息或从文件中读入...\n\n");
		return;
	}
	printf("\n ------------------------------------------------\n");
	printf(" |                 景点信息(略)                 |\n");
	printf(" ------------------------------------------------\n");
	printf(" |编号      |名称            |等级   |票价(￥)  |\n");
	while (L->next) {
		L = L->next;
		printf(" |%-08s  |%-16s|%-5s  |%-8s  |\n", L->data.no, L->data.name, L->data.level, L->data.fare);
	}
	printf(" ------------------------------------------------\n\n");
}
void PrintTicketInfo(LinkList L) {
	if (isLinkListEmpty(L)) {
		printf(" >> 景点信息为空！请尝试新建景点信息或从文件中读入...\n\n");
		return;
	}
	printf("\n ----------------------------------------\n");
	printf(" |           景点信息[购票处]           |\n");
	printf(" ----------------------------------------\n");
	printf(" |编号      |名称            |票价(￥)  |\n");
	while (L->next) {
		L = L->next;
		printf(" |%-08s  |%-16s|%-08s  |\n", L->data.no, L->data.name, L->data.fare);
	}
	printf(" ----------------------------------------\n\n");
}
