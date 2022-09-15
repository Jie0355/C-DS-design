#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "system.h"

/* Definition of global variables */
int ID = -1; // identity sign: 1 -> administrator and 0 -> user
int flagLogin, flagExit;
char LoginUserName[25];
LinkList ScenicList;
/* Function Realization  */
void LinkStartou() {
	if (ScenicList == NULL) LinkListInit(ScenicList);
	while (1) {
		if (ID == -1) LoginSystem();
		switch (ID) {
			/* administrator */
		case 1:
			while (1) {
				PrintAdminMenu();
				GetAdminInput();
				system("pause");
				system("cls");
			}
			/* user */
		case 0:
			LoadDataFromFile();
			while (1) {
				PrintUserMenu();
				GetUserInput();
				system("pause");
				system("cls");
			}
		}
	}
}
void GetAdminInput() {
	char chos;
	chos = CheckInput(1, 4, 'A', 'A');
	switch(chos) {
	case '1':
		/* add scenic information to the linked list */
		AddSystem();
		break;
	case '2':
		/* delete scenic information from the list */
		DeleteSystem();
		break;
	case '3':
		/* edit the no.k scenic spot's information */
		EditSystem();
		break;
	case '4':
		/* query the no.k scenic spot's information and sort it */
		QuerySystem();
		break;
	case 'A':
		/* login again or switch another account */
		system("cls");
		LoginSystem();
		LinkStartou();
		break;
	case '/':
		/* exit system */ 
		Exittks();
		exit(0); 
		break;
	}
}
void GetUserInput() {
	char chos;
	chos = CheckInput(1, 4, 'A', 'A');
	switch(chos) {
	case '1':
		/* buy ticket */
		BuySystem();
		break;
	case '2':
		/* refund ticket */
		RefundSystem();
		break;
	case '3':
		/* query 'user - ticket' information */
		QueryTicketSystem();
		break;
	case '4':
		/* query no.k scenic spot's information and sort it */
		QuerySystem();
		break;
	case 'A':
		/* login again or switch another account */
		system("cls");
		LoginSystem();
		LinkStartou();
		break;
	case '/':
		/* exit system */
		Exittks();
		exit(0);
		break;
	}
}
char CheckInput(int l, int r, char ll, char rl) {
	char optmp[2];
	printf(" >> ");
	scanf("%s", optmp);
	if (*optmp == '/') return '/';
	if (ll == '/' && rl == '/') {
		while (!_isNum(*optmp)) {
			printf(" >> 输入不合法！请输入合法操作[%d-%d]...\n", l, r);
			scanf("%s", optmp);
		}
	} else {
		while (!(_isNum(*optmp) || _isAlpha(*optmp))) {
			printf(" >> 输入不合法！请输入合法操作[%d-%d]/[%c-%c]...\n", l, r, ll, rl); 
			scanf("%s", optmp);
		}
	}
	return *optmp;
}
void PrintAdminMenu() {
	printf(" --------------------------------------------\n");
	printf(" |                管理员系统                |\n");
	printf(" --------------------------------------------\n");
	printf(" |                                          |\n");
	printf(" |      [1].增加景点      [A].重新登录      |\n");
	printf(" |      [2].删除景点      [/].退出系统      |\n");
	printf(" |      [3].编辑景点                        |\n");
	printf(" |      [4].查询景点                        |\n");
	printf(" --------------------------------------------\n\n");
}
void PrintUserMenu() {
	printf(" ------------------------------------------------\n");
	printf(" |                   用户系统                   |\n");
	printf(" ------------------------------------------------\n");
	printf(" |                                              |\n");
	printf(" |      [1].购买景点门票      [A].重新登录      |\n");
	printf(" |      [2].退回景点门票      [/].退出系统      |\n");
	printf(" |      [3].查询购票信息                        |\n");
	printf(" |      [4].查询景点信息                        |\n");
	printf(" ------------------------------------------------\n\n");
}
void LoginSystem() {
	flagLogin = 0;
	while (1) {
		if (flagLogin == 1) break;
		PrintLoginMenu();
		GetLoginInput();
		system("pause");
		system("cls");
	}
}
void LoginAccount() {
	int i;
	char userName[ACCOUNT_MAXLEN], password[ACCOUNT_MAXLEN];
	while (1) {
		system("cls");
		printf(" --------------------------------\n");
		printf(" |      登陆系统->登录界面      |\n");
		printf(" --------------------------------\n\n");
		printf(" >> 请输入账户名：");
		i = 0;
		while (1) {
			if (i == ACCOUNT_MAXLEN) {
				break;
			}
			userName[i ++] = getch();
			if (userName[i - 1] == '\r') break;
			printf("%c", userName[i - 1]);
		}
		userName[i - 1] = '\0';
		putchar('\n');
		printf(" >> 请输入密码：");
		i = 0;
		while (1) {
			if (i == ACCOUNT_MAXLEN) {
				break;
			}
			password[i ++] = getch();
			if (password[i - 1] == '\r') break;
			printf("%c", password[i - 1]);
		}
		password[i - 1] = '\0';
		putchar('\n');
		int flagPassword = 0;
		int fstPtr, slwPtr;
		char tmpAccountInfo[2 * ACCOUNT_MAXLEN + 5];
		char tmpUserName[ACCOUNT_MAXLEN], tmpPassword[ACCOUNT_MAXLEN];
		FILE *fp;
		if ((fp = fopen("account.dat", "rb")) == NULL) {
			printf(" >> 用户信息文件'account.dat'打开失败...\n");
			return;
		}
		while (fgets(tmpAccountInfo, 2 * ACCOUNT_MAXLEN + 5, fp) && tmpAccountInfo[0] != 10) {
			fstPtr = 1;
			memset(tmpUserName, '\0', sizeof(tmpUserName));
			for (slwPtr = 0; tmpAccountInfo[fstPtr] != ','; fstPtr ++)
				tmpUserName[slwPtr ++] = tmpAccountInfo[fstPtr];
			fstPtr ++;
			tmpUserName[slwPtr] = '\0';
			if (!strcmp(tmpUserName, userName)) {
				for (slwPtr = 0; tmpAccountInfo[fstPtr] != ','; fstPtr ++)
					tmpPassword[slwPtr ++] = tmpAccountInfo[fstPtr];
				fstPtr ++;
				tmpPassword[slwPtr] = '\0';
				if (!strcmp(tmpPassword, password)) {
					printf("\n 【登录成功】\n\n");
					//memset(LoginUserName, '\0', sizeof(LoginUserName));
					//strcpy(LoginUserName, userName);
					ID = tmpAccountInfo[fstPtr] - '0';
					PrintAccountType();
					flagLogin = 1;
					break;
				}
				else {
					printf("\n 【登录失败：密码错误】\n");
					break;
				}
			}
		}
		fclose(fp);
		if (flagLogin == 1) break;
	}
}
void RegisterAccount() {
	int i;
	char userName[ACCOUNT_MAXLEN];
	char fstPassword[ACCOUNT_MAXLEN], secPassword[ACCOUNT_MAXLEN];
	FILE *fp;
	if ((fp = fopen("account.dat", "ab")) == NULL) {
		printf(" >> 用户信息文件'account.dat'打开失败...\n");
		return;
	}
	while (1) {
		i = 0;
		system("cls");
		printf(" --------------------------------------\n");
		printf(" |         登陆系统->注册界面         |\n");
		printf(" --------------------------------------\n");
		printf(" |   [!] 账号名长度小于等于二十字符   |\n"); 
		printf(" |   [!] 密码长度小于等于二十字符     |\n"); 
		printf(" |   [!] 密码仅有字母及数字组成       |\n"); 
		printf(" --------------------------------------\n\n");
		printf(" >> 请输入账户名：");
		while (1) {
			if (i == ACCOUNT_MAXLEN) break;
			userName[i ++] = getch();
			if (userName[i - 1] == '\r') break;
			printf("%c", userName[i - 1]);
		}
		userName[i - 1] = '\0';
		putchar('\n');
		if (i == ACCOUNT_MAXLEN) {
			printf("\n 【新用户创建失败】\n");
			printf(" >> 账户名过长！请重新输入账户名...\n\n");
			system("pause");
			continue;
		}
		if (!IsRegistered(userName)) {
			printf("\n 【新用户创建成功】\n\n");
			break;
		} else {
			printf("\n 【新用户创建失败】\n");
			printf(" >> 账户名已被注册！请重新输入账户名...\n\n");
			system("pause");
		}
	}
	putchar('\n');
	system("cls");
	while (1) {
		while (1) {
			int other = 0;
			i = 0;
			printf(" >> 请输入密码:");
			while (1) {
				if (i == ACCOUNT_MAXLEN) break; 
				fstPassword[i ++] = getch();
				if (fstPassword[i - 1] == '\r') break;
				printf("%c", fstPassword[i - 1]);
			}
			fstPassword[i - 1] = '\0';
			putchar('\n');
			if (i == ACCOUNT_MAXLEN) {
				printf(" >> 密码过长！请重新输入密码...\n\n");
				system("pause");
				continue;
			}
			for (int i = 0; fstPassword[i]; i ++) {
				if (!(_isAlpha(fstPassword[i]) || _isNum(fstPassword[i]))) {
					printf(" >> 密码只能包含数字和字母！\n");
					other = 1;
					break;
				}
			}
			if (!other) break;
		}
		i = 0;
		printf("\n >> 请再次输入密码：");
		while (1) {
			secPassword[i ++] = getch();
			if (secPassword[i - 1] == '\r') break;
			printf("%c", secPassword[i - 1]);
		}
		secPassword[i - 1] = '\0';
		putchar('\n');
		if (!strcmp(fstPassword, secPassword)) {
			printf("\n 【注册成功】\n\n");
			char tmpStr[2 * ACCOUNT_MAXLEN + 5] = "(";
			strcat(tmpStr, userName);
			strcat(tmpStr, ",");
			strcat(tmpStr, fstPassword);
			strcat(tmpStr, ",0)");
			fprintf(fp, "%s\n", tmpStr);
			break;
		} else {
			printf("\n 【注册失败】\n");
			printf(" >> 两次密码不一致\n\n");
		}
	}
	fclose(fp);
}
void GetLoginInput() {
	char chos;
	chos = CheckInput(1, 2, '/', '/');
	switch (chos) {
	case '1':
		/* login account */
		LoginAccount();
		break;
	case '2':
		/* register a new account */
		RegisterAccount();
		break;
	case '/':
		/* exit the login system */
		Exittks();
		exit(0);
		break;
	}
}
int IsRegistered(char userName[ACCOUNT_MAXLEN]) {
	FILE *fp;
	int flagRegistered = 0;
	int fstPtr, slwPtr;
	char tmpAccountInfo[2 * ACCOUNT_MAXLEN + 5], tmpUserName[ACCOUNT_MAXLEN];
	if ((fp = fopen("account.dat", "rb")) == NULL) {
		printf(" >> 用户信息文件'account.dat'打开失败...\n");
		return _ERROR_;
	}
	while (fgets(tmpAccountInfo, 2 * ACCOUNT_MAXLEN + 5, fp) && tmpAccountInfo[0] != 10) {
		fstPtr = 1;
		memset(tmpUserName, '\0', sizeof(tmpUserName));
		for (slwPtr = 0; tmpAccountInfo[fstPtr] != ','; fstPtr ++)
			tmpUserName[slwPtr ++] = tmpAccountInfo[fstPtr];
		tmpUserName[slwPtr] = '\0';
		if (!strcmp(tmpUserName, userName)) flagRegistered = 1;
	}
	fclose(fp);
	if (!flagRegistered) return 0;
	else return 1;
}
void PrintLoginMenu() {
	printf(" ------------------------\n");
	printf(" |        登录系统      |\n");
	printf(" ------------------------\n");
	printf(" |                      |\n");
	printf(" |    [1].登录账号      |\n");
	printf(" |    [2].注册账号      |\n");
	printf(" |    [/].退出系统      |\n");
	printf(" |                      |\n");
	printf(" ------------------------\n\n");
}
void PrintAccountType() {
	if (ID) {
		printf(" ------------------------------\n");
		printf(" |      账号类型：管理员      |\n");
		printf(" ------------------------------\n");
	} else {
		printf(" ----------------------------\n");
		printf(" |      账号类型：用户      |\n");
		printf(" ----------------------------\n");
	}
}
void AddSystem() {
	flagExit = 0;
	while (1) {
		if (flagExit == 1) break;
		PrintAddMenu();
		GetAddInput();
		system("pause");
		system("cls");
	}
}
void GetAddInput() {
	char chos;
	chos = CheckInput(1, 2, '/', '/');
	switch(chos) {
	case '1':
		/* load data from the local file and add it to the linked list */
		LoadDataFromFile();
		break;
	case '2':
		/*
		*	enter a new scenic spot's info then
		*	add it to the linked list and save it to the local file
		*/
		AddByTyping();
		break;
	case '/':
		/* exit the add system */
		flagExit = 1;
		break;
	}
}
void LoadDataFromFile() {
	int cnt = 0;
	int fstPtr, slwPtr;
	char tmpStr[INFO_MAXLEN];
	ElemType tmpInfo[1005];
	FILE *fp;
	printf(" >> 系统导入数据中...\n");
	if ((fp = fopen("scenic.dat", "rb")) == NULL) {
		printf(" >> 景点信息文件'scenic.dat'打开失败...\n");
		return;
	}
	while(fgets(tmpStr, INFO_MAXLEN, fp) && tmpStr[0] != 10) {
		fstPtr = 1;
		for (slwPtr = 0;tmpStr[fstPtr] != ','; fstPtr ++)
			tmpInfo[cnt].no[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		tmpInfo[cnt].no[slwPtr] = '\0';
		for (slwPtr = 0;tmpStr[fstPtr] != ','; fstPtr ++)
			tmpInfo[cnt].name[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		tmpInfo[cnt].name[slwPtr] = '\0';
		for (slwPtr = 0;tmpStr[fstPtr] != ','; fstPtr ++)
			tmpInfo[cnt].level[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		tmpInfo[cnt].level[slwPtr] = '\0';
		for (slwPtr = 0;tmpStr[fstPtr] != ','; fstPtr ++)
			tmpInfo[cnt].fare[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		tmpInfo[cnt].fare[slwPtr] = '\0';
		for (slwPtr = 0;tmpStr[fstPtr] != ','; fstPtr ++)
			tmpInfo[cnt].type[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		tmpInfo[cnt].type[slwPtr] = '\0';
		for (slwPtr = 0;tmpStr[fstPtr] != ','; fstPtr ++)
			tmpInfo[cnt].address[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		tmpInfo[cnt].address[slwPtr] = '\0';
		for (slwPtr = 0;tmpStr[fstPtr] != ')'; fstPtr ++)
			tmpInfo[cnt].tel[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		tmpInfo[cnt].tel[slwPtr] = '\0';
		AddNodeToHead(ScenicList, tmpInfo[cnt]);
		cnt ++;
	}
	printf(" >> 数据导入成功！\n");
}
void AddByTyping() {
	char tmpStr[INFO_MAXLEN] = "(";
	ElemType tmpInfo;
	/*enter*/
	printf(" ---------------------------------\n");
	printf(" |           新建景点            |\n");
	printf(" ---------------------------------\n");
	printf(" |   [!] 编号长度小于等于8字符   |\n");
	printf(" |   [!] 景点票价请输入为整数    |\n");
	printf(" ---------------------------------\n\n");
	printf(" >> 景点编号：");
	scanf("%s", tmpInfo.no);
	getchar();
	printf(" >> 景点名称：");
	scanf("%s", tmpInfo.name);
	getchar();
	printf(" >> 景点等级：");
	scanf("%s", tmpInfo.level);
	getchar();
	printf(" >> 景点票价：");
	scanf("%s", tmpInfo.fare);
	getchar();
	printf(" >> 景点类型：");
	scanf("%s", tmpInfo.type);
	getchar();
	printf(" >> 景点服务电话：");
	scanf("%s", tmpInfo.tel);
	getchar();
	printf(" >> 景点地址：");
	scanf("%s", tmpInfo.address);
	/*add to node*/
	AddNodeToHead(ScenicList, tmpInfo);
	/*save to file*/
	FILE *fp;
	if ((fp = fopen("scenic.dat", "ab")) == NULL) {
		printf(" >> 景点信息文件'scenic.dat'打开失败...\n");
		return;
	}
	strcat(tmpStr, tmpInfo.no);
	strcat(tmpStr, ",");
	strcat(tmpStr, tmpInfo.name);
	strcat(tmpStr, ",");
	strcat(tmpStr, tmpInfo.level);
	strcat(tmpStr, ",");
	strcat(tmpStr, tmpInfo.fare);
	strcat(tmpStr, ",");
	strcat(tmpStr, tmpInfo.type);
	strcat(tmpStr, ",");
	strcat(tmpStr, tmpInfo.tel);
	strcat(tmpStr, ",");
	strcat(tmpStr, tmpInfo.address);
	strcat(tmpStr, ")");
	fprintf(fp, "%s\n", tmpStr);
	fclose(fp);
	printf("\n【景点新建成功】\n");
}
void PrintAddMenu() {
	printf(" ------------------------------------\n");
	printf(" |         景点信息增加系统         |\n");
	printf(" ------------------------------------\n");
	printf(" |        [1].以文件形式导入        |\n");
	printf(" |        [2].以输入形式增加        |\n");
	printf(" |        [/].退出当前系统          |\n");
	printf(" ------------------------------------\n\n");
}

void DeleteSystem() {
	flagExit = 0;
	while (1) {
		if (flagExit == 1) break;
		PrintDeleteMenu();
		GetDeleteInput();
		system("pause");
		system("cls");
	}
}
void GetDeleteInput() {
	char chos;
	chos = CheckInput(1, 1, '/', '/');
	switch (chos) {
	case '1':
		/* start delete info */
		DeleteScenicInfo();
		break;
	case '/':
		/* exit the delete system */
		flagExit = 1;
		break;
	}
}
void DeleteScenicInfo() {
	int i, j = 0;
	char deleteNO[10];
	PrintTheList(ScenicList);
	printf(" >> 请输入删除景点的编号：");
	scanf("%s", deleteNO);
	if (!DeleteTheKTNode(ScenicList, deleteNO))
		printf(" >> 成功删除编号为%s的景点！\n\n", deleteNO);
	else printf(" >> 未能找到编号为%s的景点...\n\n", deleteNO);
	/* delete the k-th spot from file */
	i = LocateFileLine(deleteNO);
	if (i == -1) {
		printf(" >> 未能找到编号为%s的景点...\n\n", deleteNO);
		return;
	}
	char tmpStr[INFO_MAXLEN];
	FILE *fp, *tmpfp;
	if ((fp = fopen("scenic.dat", "rb")) == NULL) {
		printf(" >> 景点信息文件'scenic.dat'打开失败...\n");
    	return; 
	}
	tmpfp = fopen("temp.dat", "wb");
	while (fgets(tmpStr, INFO_MAXLEN, fp) && tmpStr[0] != 10) {
		j ++;
		if (j == i) continue;
		else fprintf(tmpfp, "%s", tmpStr);
	}
	fclose(fp);
	fclose(tmpfp);
	if ((tmpfp = fopen("temp.dat", "rb")) == NULL) {
		printf(" >> 景点信息临时文件'temp.dat'打开失败...\n");
    	return;
	}
	fp = fopen("scenic.dat", "wb");
	fclose(fp);
	if ((fp = fopen("scenic.dat", "ab")) == NULL) {
		printf(" >> 景点信息文件'scenic.dat'打开失败...\n");
    	return;
	}
	while (fgets(tmpStr, INFO_MAXLEN, tmpfp) && tmpStr[0] != 10)
		fprintf(fp, "%s", tmpStr);
	fclose(fp);
	fclose(tmpfp);
	system("ERASE temp.dat");
}
int LocateFileLine(char k[10]) {
	int fstPtr, slwPtr, i = 0;
	char tmpStr[INFO_MAXLEN], tmpNO[10];
	FILE *fp;
	if ((fp = fopen("scenic.dat", "rb")) == NULL) {
		printf(" >> 景点信息文件'scenic.dat'打开失败...\n");
		return -1;
	}
	while(fgets(tmpStr, INFO_MAXLEN, fp) && tmpStr[0] != 10) {
		i ++;
		fstPtr = 1;
		memset(tmpNO, '\0', sizeof(tmpNO));
		for (slwPtr = 0;tmpStr[fstPtr] != ','; fstPtr ++)
			tmpNO[slwPtr ++] = tmpStr[fstPtr];
		tmpNO[slwPtr] = '\0';
		if (!strcmp(tmpNO, k)) return i;
	}
	return -1;
}
void PrintDeleteMenu() {
	printf(" ------------------------------\n");
	printf(" |      景点信息删除系统      |\n");
	printf(" ------------------------------\n");
	printf(" |    [1]删除指定景点信息     |\n");
	printf(" |    [/]退出系统             |\n");
	printf(" ------------------------------\n\n");
}
void EditSystem() {
	flagExit = 0;
	while (1) {
		if (flagExit == 1) break;
		PrintEditMenu();
		GetEditInput();
		system("pause");
		system("cls");
	}
}
void GetEditInput() {
	char chos;
	chos = CheckInput(1, 1, '/', '/');
	switch (chos) {
	case '1':
		/* start edit info */
		EditInfo();
		break;
	case '/':
		/* exit the edit system */
		flagExit = 1;
		break;
	}
}
void EditInfo() {
	char editNO[10];
	ElemType te;
	PrintTheList(ScenicList);
	printf("\n >> 请输入编辑的景点编号：");
	scanf("%s", editNO);
	if (!GetTheNOkNode(ScenicList, editNO, te)) {
		printf(" >> 成功查询到编号为%s的景点...\n\n", editNO);
		PrintEditInfoAndOps(te);
		GetEditOpInput(ScenicList, te);
	} else printf(" >> 未能找到编号为%s的景点...\n\n", editNO);
}
void GetEditOpInput(LinkList &L, ElemType e) {
	LinkList p = L;
	while (p->next) {
		p = p->next;
		if (!strcmp(p->data.no, e.no)) {
			int fstPtr, slwPtr;
			int flagFind = 0, i = 0, j = 0, len = 0;
			char tmpStr[INFO_MAXLEN], tmpNO[10];
			FILE *fp;
			if ((fp = fopen("scenic.dat", "rb")) == NULL) {
				printf(" >> 景点信息文件'scenic.dat'打开失败...\n");
				return;
			}
			/* locate the no.k-th scenic and save it temporarily */
			while(fgets(tmpStr, INFO_MAXLEN, fp) && tmpStr[0] != 10) {
				i ++;
				fstPtr = 1;
				memset(tmpNO, '\0', sizeof(tmpNO));
				for (slwPtr = 0;tmpStr[fstPtr] != ','; fstPtr ++)
					tmpNO[slwPtr ++] = tmpStr[fstPtr];
				fstPtr ++;
				tmpNO[slwPtr] = '\0';
				if (!strcmp(tmpNO, e.no)) {
					flagFind = 1;
					break;
				}
			}
			fclose(fp);
			if (!flagFind) {
				printf(" >> 未能找到编号为%s的景点...\n", e.no);
				return;
			}
			/* split the whole message 'tmpStr' into several parts*/
			ElemType info;
			strcpy(info.no, tmpNO);
			for (slwPtr = 0;tmpStr[fstPtr] != ','; fstPtr ++)
				info.name[slwPtr ++] = tmpStr[fstPtr];
			fstPtr ++;
			info.name[slwPtr] = '\0';
			for (slwPtr = 0;tmpStr[fstPtr] != ','; fstPtr ++)
				info.level[slwPtr ++] = tmpStr[fstPtr];
			fstPtr ++;
			info.level[slwPtr] = '\0';
			for (slwPtr = 0;tmpStr[fstPtr] != ','; fstPtr ++)
				info.fare[slwPtr ++] = tmpStr[fstPtr];
			fstPtr ++;
			info.fare[slwPtr] = '\0';
			for (slwPtr = 0;tmpStr[fstPtr] != ','; fstPtr ++)
				info.type[slwPtr ++] = tmpStr[fstPtr];
			fstPtr ++;
			info.type[slwPtr] = '\0';
			for (slwPtr = 0;tmpStr[fstPtr] != ','; fstPtr ++)
				info.address[slwPtr ++] = tmpStr[fstPtr];
			fstPtr ++;
			info.address[slwPtr] = '\0';
			for (slwPtr = 0;tmpStr[fstPtr] != ')'; fstPtr ++)
				info.tel[slwPtr ++] = tmpStr[fstPtr];
			fstPtr ++;
			info.tel[slwPtr] = '\0';
			/* edit info */
			flagExit = 0;
			char tmpInfo[300], chos;
			while (1) {
				system("cls");
				PrintEditInfoAndOps(info);
				if (flagExit == 1) break;
				chos = CheckInput(1, 6, '/', '/');
				switch(chos) {
					memset(tmpInfo, '\0', sizeof(tmpInfo));
				case '1':
					printf(" >> 请输入修改后的景点名称...\n");
					printf(" %s -> ", info.name);
					scanf("%s", tmpInfo);
					strcpy(info.name, tmpInfo);
					break;
				case '2':
					printf(" >> 请输入修改后的景点等级...\n");
					printf(" %s -> ", info.level);
					scanf("%s", tmpInfo);
					strcpy(info.level, tmpInfo);
					break;
				case '3':
					printf(" >> 请输入修改后的景点票价...\n");
					printf(" %s -> ", info.fare);
					scanf("%s", tmpInfo);
					strcpy(info.fare, tmpInfo);
					break;
				case '4':
					printf(" >> 请输入修改后的景点类型...\n");
					printf(" %s -> ", info.type);
					scanf("%s", tmpInfo);
					strcpy(info.type, tmpInfo);
					break;
				case '5':
					printf(" >> 请输入修改后的景点电话...\n");
					printf(" %s -> ", info.tel);
					scanf("%s", tmpInfo);
					strcpy(info.tel, tmpInfo);
					break;
				case '6':
					printf(" >> 请输入修改后的景点地址...\n");
					printf(" %s -> ", info.address);
					scanf("%s", tmpInfo);
					strcpy(info.address, tmpInfo);
					break;
				case '/':
					flagExit = 1;
					break;
				}
			}
			/* bring information that was split back together */
			char replaceStr[INFO_MAXLEN]; 
			memset(tmpStr, '\0', sizeof(tmpStr));
			tmpStr[0] = '(';
			strcat(tmpStr, info.no);
			strcat(tmpStr, ",");
			strcat(tmpStr, info.name);
			strcat(tmpStr, ",");
			strcat(tmpStr, info.level);
			strcat(tmpStr, ",");
			strcat(tmpStr, info.fare);
			strcat(tmpStr, ",");
			strcat(tmpStr, info.type);
			strcat(tmpStr, ",");
			strcat(tmpStr, info.address);
			strcat(tmpStr, ",");
			strcat(tmpStr, info.tel);
			strcat(tmpStr, ")");
			strcpy(replaceStr, tmpStr);
			memset(tmpStr, '\0', sizeof(tmpStr));
			/* edited info replace the former info in the same place in file */
			FILE *tmpfp;
			if ((fp = fopen("scenic.dat", "rb")) == NULL) {
				printf(" >> 景点信息文件'scenic.dat'打开失败...\n");
				return; 
			}
			tmpfp = fopen("temp.dat", "wb");
			while (fgets(tmpStr, INFO_MAXLEN, fp) && tmpStr[0] != 10) {
				j ++;
				if (j == i) fprintf(tmpfp, "%s\n", replaceStr);
				else fprintf(tmpfp, "%s", tmpStr);
			}
			fclose(fp);
			fclose(tmpfp);
			if ((tmpfp = fopen("temp.dat", "rb")) == NULL) {
				printf(" >> 景点信息临时文件'temp.dat'打开失败...\n");
				return; 
			}
			fp = fopen("scenic.dat", "wb");
			fclose(fp);
			if ((fp = fopen("scenic.dat", "ab")) == NULL) {
				printf(" >> 景点信息文件'scenic.dat'打开失败...\n");
				return; 
			}
			while (fgets(tmpStr, INFO_MAXLEN, tmpfp) && tmpStr[0] != 10)
				fprintf(fp, "%s", tmpStr);
			fclose(fp);
			fclose(tmpfp);
			system("ERASE temp.dat");
		}
	}
}
void PrintEditMenu() {
	printf(" ------------------------------\n");
	printf(" |      景点信息编辑系统      |\n");
	printf(" ------------------------------\n");
	printf(" |    [1]开始信息编辑模式     |\n");
	printf(" |    [/]退出系统             |\n");
	printf(" ------------------------------\n\n");
}
void PrintEditInfoAndOps(ElemType e) {
	printf(" --------------------------------------------------\n");
	printf(" |编号      |名称               |等级             |\n");
	printf(" |%-08s  |%-19s|%-17s|\n", e.no, e.name, e.level);
	printf(" |票价      |类型               |电话             |\n");
	printf(" |%-08s  |%-19s|%-17s|\n", e.fare, e.type, e.tel);
	printf(" |地址:%-43s|\n", e.address);
	printf(" --------------------------------------------------\n");
	printf(" |      [1].名称      [4].类型      [/].退出      |\n");
	printf(" |      [2].等级      [5].电话                    |\n");
	printf(" |      [3].票价      [6].地址                    |\n");
	printf(" --------------------------------------------------\n\n");
	printf(" >> 请输入待编辑信息的编号！\n");
}
void QuerySystem() {
	flagExit = 0;
	while (1) {
		if (flagExit == 1) break;
		PrintQueryMenu();
		GetQueryInput();
		system("pause");
		system("cls");
	}
}
void GetQueryInput() {
	char chos;
	chos = CheckInput(1, 3, '/', '/');
	switch (chos) {
	case '1':
		/* print the whole scenic spot's info */
		PrintTheList(ScenicList);
		break;
	case '2':
		/* lookup the no.k scenic spot's info in the list */
		LookupKthInfo();
		break;
	case '3':
		/* 
		*	filter the scenic spot's info:
		*	1.no	2.level	3.fare
		*/
		FilterInfo();
		break;
	case '/':
		/* exit the query system */
		flagExit = 1;
		break;
	}
}
void LookupKthInfo() {
	char queryNO[10];
	ElemType te;
	system("cls");
	PrintTheList(ScenicList);
	printf(" >> 请输入查看的景点编号：");
	scanf("%s", queryNO);
	if (!GetTheNOkNode(ScenicList, queryNO, te)) {
		printf(" >> 成功查询到编号为%s的景点...\n\n", queryNO);
		PrintEditInfoAndOps(te);
	} else printf(" >> 未能找到编号为%s的景点...\n\n", queryNO);
}
void FilterInfo() {
	char chos;
	system("cls");
	PrintFilterMenu();
	chos = CheckInput(1, 3, '/', '/');
	switch (chos) {
	case '1':
		/* sort scenic spot's information in ascending 'no' order */
		SortTheList(ScenicList, 1);
		PrintTheList(ScenicList);
		break;
	case '2':
		/* sort scenic spot's information in descending 'level' order */
		SortTheList(ScenicList, 2);
		PrintTheList(ScenicList);
		break;
	case '3':
		/* sort scenic spot's information in ascending 'fare' order */
		SortTheList(ScenicList, 3);
		PrintTheList(ScenicList);
		break;
	}
}
void PrintQueryMenu() {
	printf(" -------------------------------------\n");
	printf(" |         景点信息查询系统          |\n");
	printf(" -------------------------------------\n");
	printf(" |      [1]查看所有景点信息(简)      |\n");
	printf(" |      [2]查看某景点的详细信息      |\n");
	printf(" |      [3]条件筛选景点信息(简)      |\n");
	printf(" |      [/]退出系统                  |\n"); 
	printf(" -------------------------------------\n\n");
}
void PrintFilterMenu() {
	printf(" ---------------------------\n");
	printf(" |     筛选关键字选择      |\n");
	printf(" ---------------------------\n");
	printf(" |      [1]编号(升序)      |\n");
	printf(" |      [2]等级(降序)      |\n");
	printf(" |      [3]票价(升序)      |\n");
	printf(" ---------------------------\n\n");
}
void BuySystem() {
	flagExit = 0;
	while (1) {
		if (flagExit == 1) break;
		PrintBuyMenu();
		GetBuyInput();
		system("pause");
		system("cls");
	}
}
void GetBuyInput() {
	char chos;
	chos = CheckInput(1, 1, '/', '/');
	switch (chos) {
	case '1':
		/* start buy ticket */
		BuyTicket();
		break;
	case '/':
		/* exit the ticket buy system */
		flagExit = 1;
		break;
	}
}
void BuyTicket() {
	char name[15], id[20];
	char ticketNO[10], orderNumber[10];
	char tmpStr[50] = "(";
	ElemType te;
	PrintTicketInfo(ScenicList);
	/* enter ticktet buyer's info */
	printf(" >> 请输入游客姓名：");
	scanf("%s", name);
	getchar();
	printf(" >> 请输入游客身份证号：");
	scanf("%s", id);
	getchar();
	printf(" >> 请输入所购买的景点票相应的景点编号：");
	scanf("%s", ticketNO);
	if (!GetTheNOkNode(ScenicList, ticketNO, te)) {
		int n;
		n = RandTicketOrderNum(); // generate random order number
		for (int i = 7; i >= 0; i --) {
			orderNumber[i] = (n % 10) + '0';
			n /= 10;
		}
		/* save it to file */
		orderNumber[8] = '\0';
		strcat(tmpStr, orderNumber);
		strcat(tmpStr, ",");
		strcat(tmpStr, name);
		strcat(tmpStr, ",");
		strcat(tmpStr, id);
		strcat(tmpStr, ",");
		strcat(tmpStr, ticketNO);
		strcat(tmpStr, ")");
		if (!strcmp(te.fare, "免费")) printf(" >> 购买成功！花费0元...\n");
		else printf(" >> 购买成功！花费%s元...\n", te.fare);
		printf(" >> 您的订单号为：%s\n\n", orderNumber);
		FILE *fp;
		if ((fp = fopen("ticket.dat", "ab")) == NULL) {
			printf(" >> 用户购票信息文件'ticket.dat'打开失败...\n");
			return;
		}
		fprintf(fp, "%s\n", tmpStr);
		fclose(fp);
	} else printf(" >> 编号为%s的景点不存在...购买失败...\n\n", ticketNO);
}
void PrintBuyMenu() {
	printf(" ---------------------------\n");
	printf(" |      用户购票系统       |\n");
	printf(" ---------------------------\n");
	printf(" |   [1]开始选购景点门票   |\n");
	printf(" |   [/]退出系统           |\n");
	printf(" ---------------------------\n\n");
}
void RefundSystem() {
	flagExit = 0;
	while (1) {
		if (flagExit == 1) break;
		PrintRefundMenu();
		GetRefundInput();
		system("pause");
		system("cls");
	}
}
void GetRefundInput() {
	char chos;
	chos = CheckInput(1, 1, '/', '/');
	switch (chos) {
	case '1':
		/* start ticket refund */
		RefundTicket();
		break;
	case '/':
		/* exit the ticktet refund system */
		flagExit = 1;
		break;
	}
}
void RefundTicket() {
	int i, j = 0; 
	char orderNum[10], chos[2];
	printf(" >> 请输入订单号：");
	scanf("%s", orderNum);
	i = LocateOrderLine(orderNum);
	if (i == -1) {
		printf(" >> 未能找到编号为%s的订单...\n\n", orderNum);
		return;
	}
	else {
		printf(" >> 成功找到编号为%s的订单...\n\n", orderNum);
		printf(" >> 确认是否退票？请输入Y/N：");
		scanf("%s", chos);
		if (*chos == 'N') return;
	}
	char tmpStr[50];
	FILE *fp, *tmpfp = fopen("temp.dat", "wb");
	if ((fp = fopen("ticket.dat", "rb")) == NULL) {
		printf(" >> 用户购票信息文件'ticket.dat'打开失败...\n");
    	return; 
	}
	while (fgets(tmpStr, 50, fp) && tmpStr[0] != 10) {
		j ++;
		if (j == i) continue;
		else fprintf(tmpfp, "%s", tmpStr);
	}
	fclose(fp);
	fclose(tmpfp);
	if ((tmpfp = fopen("temp.dat", "rb")) == NULL) {
		printf(" >> 购票信息临时文件'temp.dat'打开失败...\n");
    	return;
	}
	fp = fopen("ticket.dat", "wb");
	fclose(fp);
	if ((fp = fopen("ticket.dat", "ab")) == NULL) {
		printf(" >> 用户购票信息文件'ticket.dat'打开失败...\n");
    	return;
	}
	while (fgets(tmpStr, 50, tmpfp) && tmpStr[0] != 10) {
		fprintf(fp, "%s", tmpStr);
	}
	fclose(fp);
	fclose(tmpfp);
	system("ERASE temp.dat");
}
int LocateOrderLine(char k[10]) {
	int fstPtr, slwPtr, i = 0;
	char tmpStr[50], tmpNO[10];
	FILE *fp;
	if ((fp = fopen("ticket.dat", "rb")) == NULL) {
		printf(" >> 用户购票信息文件'ticket.dat'打开失败...\n");
		return -1;
	}
	while(fgets(tmpStr, 50, fp) && tmpStr[0] != 10) {
		i ++;
		fstPtr = 1;
		memset(tmpNO, '\0', sizeof(tmpNO));
		for (slwPtr = 0;tmpStr[fstPtr] != ','; fstPtr ++)
			tmpNO[slwPtr ++] = tmpStr[fstPtr];
		tmpNO[slwPtr] = '\0';
		if (!strcmp(tmpNO, k)) return i;
	}
	return -1;
}
void PrintRefundMenu() {
	printf(" ---------------------------\n");
	printf(" |      用户退票系统       |\n");
	printf(" ---------------------------\n");
	printf(" |   [1]开始退回景点门票   |\n");
	printf(" |   [/]退出系统           |\n");
	printf(" ---------------------------\n\n");
}
void QueryTicketSystem() {
	flagExit = 0;
	while (1) {
		if (flagExit == 1) break;
		PrintQueryTicketMenu();
		GetQueryTicketInput();
		system("pause");
		system("cls");
	}
}
void GetQueryTicketInput() {
	char chos;
	chos = CheckInput(1, 1, '/', '/');
	switch (chos) {
	case '1':
		/* query the user info with ticket order number */
		QueryTicketOrderNum();
		break;
	case '2':
		/* query the user info with buyer's name */
		QueryTicketName();
		break;
	case '3':
		/* query the order info with scenic spot's no */
		QueryTicketNO();
		break;
	case '/':
		/* exit the query order system */
		flagExit = 1;
		break;
	}
}
void QueryTicketOrderNum() {
	FILE *fp;
	int flagFind = 0;
	int fstPtr, slwPtr;
	char tmpStr[50];
	char name[15], id[20];
	char ticketNO[10], orderNumber[10];
	char queryOrderNum[10];
	printf(" >> 请输入待查询的订单号：");
	scanf("%s", queryOrderNum);
	if ((fp = fopen("ticket.dat", "rb")) == NULL) {
		printf(" >> 用户购票信息文件'ticket.dat'打开失败...\n");
		return;
	}
	while(fgets(tmpStr, 50, fp) && tmpStr[0] != 10) {
		fstPtr = 1;
		memset(name, '\0', sizeof(name));
		memset(id, '\0', sizeof(id));
		memset(ticketNO, '\0', sizeof(ticketNO));
		memset(orderNumber, '\0', sizeof(orderNumber));
		for (slwPtr = 0; tmpStr[fstPtr] != ','; fstPtr ++)
			orderNumber[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		orderNumber[slwPtr] = '\0';
		for (slwPtr = 0; tmpStr[fstPtr] != ','; fstPtr ++)
			name[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		name[slwPtr] = '\0';
		for (slwPtr = 0; tmpStr[fstPtr] != ','; fstPtr ++)
			id[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		id[slwPtr] = '\0';
		for (slwPtr = 0; tmpStr[fstPtr] != ')'; fstPtr ++)
			ticketNO[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		ticketNO[slwPtr] = '\0';
		if (!strcmp(queryOrderNum, orderNumber)) {
			flagFind = 1;
			printf("-----------------------------------\n");
			printf("|姓名                |订单号      |\n");
			printf("|%-18s  |%-10s  |\n", name, orderNumber);
			printf("|身份证号            |景点编号    |\n");
			printf("|%-20s|%-10s  |\n", id, ticketNO);
			printf("-----------------------------------\n\n");
		}
	}
	if (!flagFind) printf(" >> 未查找到订单号为'%s'的相关信息...\n", queryOrderNum);
}
void QueryTicketName() {
	FILE *fp;
	int flagFind = 0;
	int fstPtr, slwPtr;
	char tmpStr[50];
	char name[15], id[20];
	char ticketNO[10], orderNumber[10];
	char queryName[15];
	printf(" >> 请输入待查询的姓名：");
	scanf("%s", queryName);
	if ((fp = fopen("ticket.dat", "rb")) == NULL) {
		printf(" >> 用户购票信息文件'ticket.dat'打开失败...\n");
		return;
	}
	while(fgets(tmpStr, 50, fp) && tmpStr[0] != 10) {
		fstPtr = 1;
		memset(name, '\0', sizeof(name));
		memset(id, '\0', sizeof(id));
		memset(ticketNO, '\0', sizeof(ticketNO));
		memset(orderNumber, '\0', sizeof(orderNumber));
		for (slwPtr = 0; tmpStr[fstPtr] != ','; fstPtr ++)
			orderNumber[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		orderNumber[slwPtr] = '\0';
		for (slwPtr = 0; tmpStr[fstPtr] != ','; fstPtr ++)
			name[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		name[slwPtr] = '\0';
		for (slwPtr = 0; tmpStr[fstPtr] != ','; fstPtr ++)
			id[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		id[slwPtr] = '\0';
		for (slwPtr = 0; tmpStr[fstPtr] != ')'; fstPtr ++)
			ticketNO[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		ticketNO[slwPtr] = '\0';
		if (!strcmp(queryName, name)) {
			flagFind = 1;
			printf("-----------------------------------\n");
			printf("|姓名                |订单号      |\n");
			printf("|%-18s  |%-10s  |\n", name, orderNumber);
			printf("|身份证号            |景点编号    |\n");
			printf("|%-20s|%-10s  |\n", id, ticketNO);
			printf("-----------------------------------\n\n");
		}
	}
	if (!flagFind) printf(" >> 未查找到姓名为'%s'的相关信息...\n", queryName);
}
void QueryTicketNO() {
	FILE *fp;
	int flagFind = 0;
	int fstPtr, slwPtr;
	char tmpStr[50];
	char name[15], id[20];
	char ticketNO[10], orderNumber[10];
	char queryNO[15];
	printf(" >> 请输入待查询的景点编号：");
	scanf("%s", queryNO);
	if ((fp = fopen("ticket.dat", "rb")) == NULL) {
		printf(" >> 用户购票信息文件'ticket.dat'打开失败...\n");
		return;
	}
	while(fgets(tmpStr, 50, fp) && tmpStr[0] != 10) {
		fstPtr = 1;
		memset(name, '\0', sizeof(name));
		memset(id, '\0', sizeof(id));
		memset(ticketNO, '\0', sizeof(ticketNO));
		memset(orderNumber, '\0', sizeof(orderNumber));
		for (slwPtr = 0; tmpStr[fstPtr] != ','; fstPtr ++)
			orderNumber[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		orderNumber[slwPtr] = '\0';
		for (slwPtr = 0; tmpStr[fstPtr] != ','; fstPtr ++)
			name[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		name[slwPtr] = '\0';
		for (slwPtr = 0; tmpStr[fstPtr] != ','; fstPtr ++)
			id[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		id[slwPtr] = '\0';
		for (slwPtr = 0; tmpStr[fstPtr] != ')'; fstPtr ++)
			ticketNO[slwPtr ++] = tmpStr[fstPtr];
		fstPtr ++;
		ticketNO[slwPtr] = '\0';
		if (!strcmp(queryNO, ticketNO)) {
			flagFind = 1;
			printf("-----------------------------------\n");
			printf("|姓名                |订单号      |\n");
			printf("|%-18s  |%-10s  |\n", name, orderNumber);
			printf("|身份证号            |景点编号    |\n");
			printf("|%-20s|%-10s  |\n", id, ticketNO);
			printf("-----------------------------------\n\n");
		}
	}
	if (!flagFind) printf(" >> 未查找到景点编号为'%s'的相关信息...\n", queryNO);
}
void PrintQueryTicketMenu() {
	printf(" ---------------------------\n");
	printf(" |      用户查询系统       |\n");
	printf(" ---------------------------\n");
	printf(" |     [1]订单号查询       |\n");
	printf(" |     [2]用户名查询       |\n");
	printf(" |     [3]景点查询         |\n");
	printf(" |     [/]退出系统         |\n");
	printf(" ---------------------------\n\n");
}
bool _isNum(char x) {
	if (x >= '0' && x <= '9') return true;
	return false;
}
bool _isAlpha(char x) {
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z')) return true;
	return false;
}
int RandTicketOrderNum() {
	srand((unsigned)time(NULL));
	int n = 10000000 + rand() % 90000000; // 10000000 ~ 99999999
	return n;
}
void Welcome() {
	system("title 旅游资源管理系统 By Jie0355"); 
	//system("color 0A");
	printf(" -------------------------------------------------------------\n");
	printf(" |                  欢迎使用旅游资源管理系统                 |\n");
	printf(" |                       作者 : Jie0355                      |\n");
	printf(" |                   更新时间 : 2022.06.06                   |\n");
	printf(" |                      Version : 1.0.0                      |\n");
	printf(" -------------------------------------------------------------\n");
	Sleep(1000); system("cls");
	printf("                            ■■■■■\n");
	printf("                                    ■\n");
	printf("                                    ■\n");
	printf("                            ■■■■■\n");
	printf("                                    ■\n");
	printf("                                    ■\n");
	printf("                            ■■■■■\n");
	Sleep(1000); system("cls");
	printf("                            ■■■■■\n");
	printf("                                    ■\n");
	printf("                                    ■\n");
	printf("                            ■■■■■\n");
	printf("                            ■       \n");
	printf("                            ■       \n");
	printf("                            ■■■■■\n");
	Sleep(1000); system("cls");
	printf("                              ■■\n");
	printf("                                ■\n");
	printf("                                ■\n");
	printf("                                ■\n");
	printf("                                ■\n");
	printf("                                ■\n");
	printf("                              ■■■\n");
	Sleep(1000); system("cls");
}
void Exittks() {
	printf("                            ■■■■■\n");
	printf("                                    ■\n");
	printf("                                    ■\n");
	printf("                            ■■■■■\n");
	printf("                                    ■\n");
	printf("                                    ■\n");
	printf("                            ■■■■■\n");
	Sleep(1000); system("cls");
	printf("                            ■■■■■\n");
	printf("                                    ■\n");
	printf("                                    ■\n");
	printf("                            ■■■■■\n");
	printf("                            ■       \n");
	printf("                            ■       \n");
	printf("                            ■■■■■\n");
	Sleep(1000); system("cls");
	printf("                              ■■\n");
	printf("                                ■\n");
	printf("                                ■\n");
	printf("                                ■\n");
	printf("                                ■\n");
	printf("                                ■\n");
	printf("                              ■■■\n");
	Sleep(1000); system("cls");
	printf(" ----------------------------------------\n");
	printf(" |       成功退出旅游资源管理系统       |\n");
	printf(" |      *^_^*期待您的下次使用*^_^*      |\n");
	printf(" |            作者 : Jie0355            |\n");
	printf(" |     联系方式 : 1955864881@qq.com     |\n");
	printf(" ----------------------------------------\n");
}
