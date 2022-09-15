#ifndef _SYSTEM_H_
#define _SYSTEM_H_

/*
*		Filename: system.h
*		Cpp Functions:
*				Main Function Definition Statement and Implementation
*			of Tourism Resource Management System.
*		Author: Jie0355
*
*/

/* Macro Definition */
#include "list.h"
#define ACCOUNT_MAXLEN 25 // maximum length of account names and passwords
#define INFO_MAXLEN 500 // maximum length of attraction information

/* Function Declaration */
/*
*		<START>:
*			The beginning part is used for the initialization of the
*		entire resource management system and entering the administrator
*		or user system, and is also used for the operation management
*		of the administrator or user system.
*
*/
void LinkStartou();
void GetAdminInput();
void GetUserInput();
char CheckInput(int l, int r, char ll, char rl);
void PrintAdminMenu();
void PrintUserMenu();
/*
*		<LOGIN SYSTEM>:
*			You can log in or register an account in this system, and
*		at the same time determine whether the user is an administrator
*		or a normal user.
*
*/
void LoginSystem();
void LoginAccount();
void RegisterAccount();
void GetLoginInput();
int IsRegistered(char *userName);
void PrintLoginMenu();
void PrintAccountType();
/* ----------------------------------- admin part ----------------------------------- */
/*
*		<ADD SYSTEM>:
*			The attraction information augmentation system is used to
*		read import information from a file or cache.
*
*/
void AddSystem();
void GetAddInput();
void LoadDataFromFile();
void AddByTyping();
void PrintAddMenu();
/*
*		<DELETE SYSTEM>:
*			The scenic spot information deletion system deletes the
*		scenic spot from the linked list and the local file by locating
*		the scenic spot number.
*
*/
void DeleteSystem();
void GetDeleteInput();
void DeleteScenicInfo();
int LocateFileLine(char k[10]);
void PrintDeleteMenu();
/*
*		<EDIT SYSTEM>:
*			The scenic spot information editing system modifies all
*		its sub-contents through the scenic spot number.
*
*/
void EditSystem();
void GetEditInput();
void EditInfo();
void GetEditOpInput(LinkList &L, ElemType e);
void PrintEditMenu();
void PrintEditInfoAndOps(ElemType e);
/*
*		<QUERY SYSTEM>:
*			The scenic spot information query system can obtain the
*		brief information of all scenic spots, and at the same time,
*		it can not only search for other information corresponding
*		to the scenic spot number, but also make all scenic spots
*		sort and output according to the specified keywords.
*
*/
void QuerySystem();
void GetQueryInput();
void LookupKthInfo();
void FilterInfo();
void PrintQueryMenu();
void PrintFilterMenu();
/* ----------------------------------- user part ------------------------------------ */
/*
*		<BUY SYSTEM>:
*			Attraction ticket purchase system can purchase tickets
*		for corresponding attractions.
*
*/
void BuySystem();
void GetBuyInput();
void BuyTicket();
void PrintBuyMenu();
/*
*		<REFUND SYSTEM>:
*			The attraction ticket return system can return the ticket
*		through the given order number.
*
*/
void RefundSystem();
void GetRefundInput();
void RefundTicket();
int LocateOrderLine(char k[10]);
void PrintRefundMenu();
/*
*		<ORDER QUERY SYSTEM>:
*			The ticket purchase information query system can query
*		all historical order information in the system through the
*		given order number, buyer's name and attraction number.
*
*/
void QueryTicketSystem();
void GetQueryTicketInput();
void QueryTicketOrderNum();
void QueryTicketName();
void QueryTicketNO();
void PrintQueryTicketMenu();

bool _isNum(char x);
bool _isAlpha(char x);
// Generate random order number
int RandTicketOrderNum(void);

/* welcome talks and quit talks */
void Welcome();
void Exittks();

#endif
