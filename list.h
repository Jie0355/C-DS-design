#ifndef _LIST_H_
#define _LIST_H_

/*
*		Filename: list.h
*		Cpp Description:
*				Definition and declaration of linked list and its functions.
*		Author: Jie0355
*
*/

/* Macro Definitions & Structures */
#define _ERROR_ -1;
typedef struct elem {
	char no[10], name[25], level[10];
	char fare[10], type[25];
	char tel[20], address[300];
}ElemType;
typedef struct Node {
	ElemType data;
	struct Node *next;
}*LinkList;

/* Function Declaration */
int LinkListInit(LinkList &L);
void LinkListDestory(LinkList &L);
/* return true if the linked list is empty, or return false */
bool isLinkListEmpty(LinkList L);
/*
*	sort the linked list in three pattern when the mode is:
*		1.ascending 'no' order
*		2.descending 'level' order
*		3.ascending 'fare' order
*
*/
void SortTheList(LinkList &L, int mode);
int AddNodeToHead(LinkList &L, ElemType e);
/* delete the no.k node */
int DeleteTheKTNode(LinkList &L, char k[10]);
/* locate the k-th node and assign its info to e */
int GetTheNOkNode(LinkList L, char k[10], ElemType &e);
void PrintTheList(LinkList L);
void PrintTicketInfo(LinkList L);

#endif
