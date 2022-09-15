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
			printf(" >> ���벻�Ϸ���������Ϸ�����[%d-%d]...\n", l, r);
			scanf("%s", optmp);
		}
	} else {
		while (!(_isNum(*optmp) || _isAlpha(*optmp))) {
			printf(" >> ���벻�Ϸ���������Ϸ�����[%d-%d]/[%c-%c]...\n", l, r, ll, rl); 
			scanf("%s", optmp);
		}
	}
	return *optmp;
}
void PrintAdminMenu() {
	printf(" --------------------------------------------\n");
	printf(" |                ����Աϵͳ                |\n");
	printf(" --------------------------------------------\n");
	printf(" |                                          |\n");
	printf(" |      [1].���Ӿ���      [A].���µ�¼      |\n");
	printf(" |      [2].ɾ������      [/].�˳�ϵͳ      |\n");
	printf(" |      [3].�༭����                        |\n");
	printf(" |      [4].��ѯ����                        |\n");
	printf(" --------------------------------------------\n\n");
}
void PrintUserMenu() {
	printf(" ------------------------------------------------\n");
	printf(" |                   �û�ϵͳ                   |\n");
	printf(" ------------------------------------------------\n");
	printf(" |                                              |\n");
	printf(" |      [1].���򾰵���Ʊ      [A].���µ�¼      |\n");
	printf(" |      [2].�˻ؾ�����Ʊ      [/].�˳�ϵͳ      |\n");
	printf(" |      [3].��ѯ��Ʊ��Ϣ                        |\n");
	printf(" |      [4].��ѯ������Ϣ                        |\n");
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
		printf(" |      ��½ϵͳ->��¼����      |\n");
		printf(" --------------------------------\n\n");
		printf(" >> �������˻�����");
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
		printf(" >> ���������룺");
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
			printf(" >> �û���Ϣ�ļ�'account.dat'��ʧ��...\n");
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
					printf("\n ����¼�ɹ���\n\n");
					//memset(LoginUserName, '\0', sizeof(LoginUserName));
					//strcpy(LoginUserName, userName);
					ID = tmpAccountInfo[fstPtr] - '0';
					PrintAccountType();
					flagLogin = 1;
					break;
				}
				else {
					printf("\n ����¼ʧ�ܣ��������\n");
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
		printf(" >> �û���Ϣ�ļ�'account.dat'��ʧ��...\n");
		return;
	}
	while (1) {
		i = 0;
		system("cls");
		printf(" --------------------------------------\n");
		printf(" |         ��½ϵͳ->ע�����         |\n");
		printf(" --------------------------------------\n");
		printf(" |   [!] �˺�������С�ڵ��ڶ�ʮ�ַ�   |\n"); 
		printf(" |   [!] ���볤��С�ڵ��ڶ�ʮ�ַ�     |\n"); 
		printf(" |   [!] ���������ĸ���������       |\n"); 
		printf(" --------------------------------------\n\n");
		printf(" >> �������˻�����");
		while (1) {
			if (i == ACCOUNT_MAXLEN) break;
			userName[i ++] = getch();
			if (userName[i - 1] == '\r') break;
			printf("%c", userName[i - 1]);
		}
		userName[i - 1] = '\0';
		putchar('\n');
		if (i == ACCOUNT_MAXLEN) {
			printf("\n �����û�����ʧ�ܡ�\n");
			printf(" >> �˻��������������������˻���...\n\n");
			system("pause");
			continue;
		}
		if (!IsRegistered(userName)) {
			printf("\n �����û������ɹ���\n\n");
			break;
		} else {
			printf("\n �����û�����ʧ�ܡ�\n");
			printf(" >> �˻����ѱ�ע�ᣡ�����������˻���...\n\n");
			system("pause");
		}
	}
	putchar('\n');
	system("cls");
	while (1) {
		while (1) {
			int other = 0;
			i = 0;
			printf(" >> ����������:");
			while (1) {
				if (i == ACCOUNT_MAXLEN) break; 
				fstPassword[i ++] = getch();
				if (fstPassword[i - 1] == '\r') break;
				printf("%c", fstPassword[i - 1]);
			}
			fstPassword[i - 1] = '\0';
			putchar('\n');
			if (i == ACCOUNT_MAXLEN) {
				printf(" >> �����������������������...\n\n");
				system("pause");
				continue;
			}
			for (int i = 0; fstPassword[i]; i ++) {
				if (!(_isAlpha(fstPassword[i]) || _isNum(fstPassword[i]))) {
					printf(" >> ����ֻ�ܰ������ֺ���ĸ��\n");
					other = 1;
					break;
				}
			}
			if (!other) break;
		}
		i = 0;
		printf("\n >> ���ٴ��������룺");
		while (1) {
			secPassword[i ++] = getch();
			if (secPassword[i - 1] == '\r') break;
			printf("%c", secPassword[i - 1]);
		}
		secPassword[i - 1] = '\0';
		putchar('\n');
		if (!strcmp(fstPassword, secPassword)) {
			printf("\n ��ע��ɹ���\n\n");
			char tmpStr[2 * ACCOUNT_MAXLEN + 5] = "(";
			strcat(tmpStr, userName);
			strcat(tmpStr, ",");
			strcat(tmpStr, fstPassword);
			strcat(tmpStr, ",0)");
			fprintf(fp, "%s\n", tmpStr);
			break;
		} else {
			printf("\n ��ע��ʧ�ܡ�\n");
			printf(" >> �������벻һ��\n\n");
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
		printf(" >> �û���Ϣ�ļ�'account.dat'��ʧ��...\n");
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
	printf(" |        ��¼ϵͳ      |\n");
	printf(" ------------------------\n");
	printf(" |                      |\n");
	printf(" |    [1].��¼�˺�      |\n");
	printf(" |    [2].ע���˺�      |\n");
	printf(" |    [/].�˳�ϵͳ      |\n");
	printf(" |                      |\n");
	printf(" ------------------------\n\n");
}
void PrintAccountType() {
	if (ID) {
		printf(" ------------------------------\n");
		printf(" |      �˺����ͣ�����Ա      |\n");
		printf(" ------------------------------\n");
	} else {
		printf(" ----------------------------\n");
		printf(" |      �˺����ͣ��û�      |\n");
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
	printf(" >> ϵͳ����������...\n");
	if ((fp = fopen("scenic.dat", "rb")) == NULL) {
		printf(" >> ������Ϣ�ļ�'scenic.dat'��ʧ��...\n");
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
	printf(" >> ���ݵ���ɹ���\n");
}
void AddByTyping() {
	char tmpStr[INFO_MAXLEN] = "(";
	ElemType tmpInfo;
	/*enter*/
	printf(" ---------------------------------\n");
	printf(" |           �½�����            |\n");
	printf(" ---------------------------------\n");
	printf(" |   [!] ��ų���С�ڵ���8�ַ�   |\n");
	printf(" |   [!] ����Ʊ��������Ϊ����    |\n");
	printf(" ---------------------------------\n\n");
	printf(" >> �����ţ�");
	scanf("%s", tmpInfo.no);
	getchar();
	printf(" >> �������ƣ�");
	scanf("%s", tmpInfo.name);
	getchar();
	printf(" >> ����ȼ���");
	scanf("%s", tmpInfo.level);
	getchar();
	printf(" >> ����Ʊ�ۣ�");
	scanf("%s", tmpInfo.fare);
	getchar();
	printf(" >> �������ͣ�");
	scanf("%s", tmpInfo.type);
	getchar();
	printf(" >> �������绰��");
	scanf("%s", tmpInfo.tel);
	getchar();
	printf(" >> �����ַ��");
	scanf("%s", tmpInfo.address);
	/*add to node*/
	AddNodeToHead(ScenicList, tmpInfo);
	/*save to file*/
	FILE *fp;
	if ((fp = fopen("scenic.dat", "ab")) == NULL) {
		printf(" >> ������Ϣ�ļ�'scenic.dat'��ʧ��...\n");
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
	printf("\n�������½��ɹ���\n");
}
void PrintAddMenu() {
	printf(" ------------------------------------\n");
	printf(" |         ������Ϣ����ϵͳ         |\n");
	printf(" ------------------------------------\n");
	printf(" |        [1].���ļ���ʽ����        |\n");
	printf(" |        [2].��������ʽ����        |\n");
	printf(" |        [/].�˳���ǰϵͳ          |\n");
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
	printf(" >> ������ɾ������ı�ţ�");
	scanf("%s", deleteNO);
	if (!DeleteTheKTNode(ScenicList, deleteNO))
		printf(" >> �ɹ�ɾ�����Ϊ%s�ľ��㣡\n\n", deleteNO);
	else printf(" >> δ���ҵ����Ϊ%s�ľ���...\n\n", deleteNO);
	/* delete the k-th spot from file */
	i = LocateFileLine(deleteNO);
	if (i == -1) {
		printf(" >> δ���ҵ����Ϊ%s�ľ���...\n\n", deleteNO);
		return;
	}
	char tmpStr[INFO_MAXLEN];
	FILE *fp, *tmpfp;
	if ((fp = fopen("scenic.dat", "rb")) == NULL) {
		printf(" >> ������Ϣ�ļ�'scenic.dat'��ʧ��...\n");
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
		printf(" >> ������Ϣ��ʱ�ļ�'temp.dat'��ʧ��...\n");
    	return;
	}
	fp = fopen("scenic.dat", "wb");
	fclose(fp);
	if ((fp = fopen("scenic.dat", "ab")) == NULL) {
		printf(" >> ������Ϣ�ļ�'scenic.dat'��ʧ��...\n");
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
		printf(" >> ������Ϣ�ļ�'scenic.dat'��ʧ��...\n");
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
	printf(" |      ������Ϣɾ��ϵͳ      |\n");
	printf(" ------------------------------\n");
	printf(" |    [1]ɾ��ָ��������Ϣ     |\n");
	printf(" |    [/]�˳�ϵͳ             |\n");
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
	printf("\n >> ������༭�ľ����ţ�");
	scanf("%s", editNO);
	if (!GetTheNOkNode(ScenicList, editNO, te)) {
		printf(" >> �ɹ���ѯ�����Ϊ%s�ľ���...\n\n", editNO);
		PrintEditInfoAndOps(te);
		GetEditOpInput(ScenicList, te);
	} else printf(" >> δ���ҵ����Ϊ%s�ľ���...\n\n", editNO);
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
				printf(" >> ������Ϣ�ļ�'scenic.dat'��ʧ��...\n");
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
				printf(" >> δ���ҵ����Ϊ%s�ľ���...\n", e.no);
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
					printf(" >> �������޸ĺ�ľ�������...\n");
					printf(" %s -> ", info.name);
					scanf("%s", tmpInfo);
					strcpy(info.name, tmpInfo);
					break;
				case '2':
					printf(" >> �������޸ĺ�ľ���ȼ�...\n");
					printf(" %s -> ", info.level);
					scanf("%s", tmpInfo);
					strcpy(info.level, tmpInfo);
					break;
				case '3':
					printf(" >> �������޸ĺ�ľ���Ʊ��...\n");
					printf(" %s -> ", info.fare);
					scanf("%s", tmpInfo);
					strcpy(info.fare, tmpInfo);
					break;
				case '4':
					printf(" >> �������޸ĺ�ľ�������...\n");
					printf(" %s -> ", info.type);
					scanf("%s", tmpInfo);
					strcpy(info.type, tmpInfo);
					break;
				case '5':
					printf(" >> �������޸ĺ�ľ���绰...\n");
					printf(" %s -> ", info.tel);
					scanf("%s", tmpInfo);
					strcpy(info.tel, tmpInfo);
					break;
				case '6':
					printf(" >> �������޸ĺ�ľ����ַ...\n");
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
				printf(" >> ������Ϣ�ļ�'scenic.dat'��ʧ��...\n");
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
				printf(" >> ������Ϣ��ʱ�ļ�'temp.dat'��ʧ��...\n");
				return; 
			}
			fp = fopen("scenic.dat", "wb");
			fclose(fp);
			if ((fp = fopen("scenic.dat", "ab")) == NULL) {
				printf(" >> ������Ϣ�ļ�'scenic.dat'��ʧ��...\n");
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
	printf(" |      ������Ϣ�༭ϵͳ      |\n");
	printf(" ------------------------------\n");
	printf(" |    [1]��ʼ��Ϣ�༭ģʽ     |\n");
	printf(" |    [/]�˳�ϵͳ             |\n");
	printf(" ------------------------------\n\n");
}
void PrintEditInfoAndOps(ElemType e) {
	printf(" --------------------------------------------------\n");
	printf(" |���      |����               |�ȼ�             |\n");
	printf(" |%-08s  |%-19s|%-17s|\n", e.no, e.name, e.level);
	printf(" |Ʊ��      |����               |�绰             |\n");
	printf(" |%-08s  |%-19s|%-17s|\n", e.fare, e.type, e.tel);
	printf(" |��ַ:%-43s|\n", e.address);
	printf(" --------------------------------------------------\n");
	printf(" |      [1].����      [4].����      [/].�˳�      |\n");
	printf(" |      [2].�ȼ�      [5].�绰                    |\n");
	printf(" |      [3].Ʊ��      [6].��ַ                    |\n");
	printf(" --------------------------------------------------\n\n");
	printf(" >> ��������༭��Ϣ�ı�ţ�\n");
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
	printf(" >> ������鿴�ľ����ţ�");
	scanf("%s", queryNO);
	if (!GetTheNOkNode(ScenicList, queryNO, te)) {
		printf(" >> �ɹ���ѯ�����Ϊ%s�ľ���...\n\n", queryNO);
		PrintEditInfoAndOps(te);
	} else printf(" >> δ���ҵ����Ϊ%s�ľ���...\n\n", queryNO);
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
	printf(" |         ������Ϣ��ѯϵͳ          |\n");
	printf(" -------------------------------------\n");
	printf(" |      [1]�鿴���о�����Ϣ(��)      |\n");
	printf(" |      [2]�鿴ĳ�������ϸ��Ϣ      |\n");
	printf(" |      [3]����ɸѡ������Ϣ(��)      |\n");
	printf(" |      [/]�˳�ϵͳ                  |\n"); 
	printf(" -------------------------------------\n\n");
}
void PrintFilterMenu() {
	printf(" ---------------------------\n");
	printf(" |     ɸѡ�ؼ���ѡ��      |\n");
	printf(" ---------------------------\n");
	printf(" |      [1]���(����)      |\n");
	printf(" |      [2]�ȼ�(����)      |\n");
	printf(" |      [3]Ʊ��(����)      |\n");
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
	printf(" >> �������ο�������");
	scanf("%s", name);
	getchar();
	printf(" >> �������ο����֤�ţ�");
	scanf("%s", id);
	getchar();
	printf(" >> ������������ľ���Ʊ��Ӧ�ľ����ţ�");
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
		if (!strcmp(te.fare, "���")) printf(" >> ����ɹ�������0Ԫ...\n");
		else printf(" >> ����ɹ�������%sԪ...\n", te.fare);
		printf(" >> ���Ķ�����Ϊ��%s\n\n", orderNumber);
		FILE *fp;
		if ((fp = fopen("ticket.dat", "ab")) == NULL) {
			printf(" >> �û���Ʊ��Ϣ�ļ�'ticket.dat'��ʧ��...\n");
			return;
		}
		fprintf(fp, "%s\n", tmpStr);
		fclose(fp);
	} else printf(" >> ���Ϊ%s�ľ��㲻����...����ʧ��...\n\n", ticketNO);
}
void PrintBuyMenu() {
	printf(" ---------------------------\n");
	printf(" |      �û���Ʊϵͳ       |\n");
	printf(" ---------------------------\n");
	printf(" |   [1]��ʼѡ��������Ʊ   |\n");
	printf(" |   [/]�˳�ϵͳ           |\n");
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
	printf(" >> �����붩���ţ�");
	scanf("%s", orderNum);
	i = LocateOrderLine(orderNum);
	if (i == -1) {
		printf(" >> δ���ҵ����Ϊ%s�Ķ���...\n\n", orderNum);
		return;
	}
	else {
		printf(" >> �ɹ��ҵ����Ϊ%s�Ķ���...\n\n", orderNum);
		printf(" >> ȷ���Ƿ���Ʊ��������Y/N��");
		scanf("%s", chos);
		if (*chos == 'N') return;
	}
	char tmpStr[50];
	FILE *fp, *tmpfp = fopen("temp.dat", "wb");
	if ((fp = fopen("ticket.dat", "rb")) == NULL) {
		printf(" >> �û���Ʊ��Ϣ�ļ�'ticket.dat'��ʧ��...\n");
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
		printf(" >> ��Ʊ��Ϣ��ʱ�ļ�'temp.dat'��ʧ��...\n");
    	return;
	}
	fp = fopen("ticket.dat", "wb");
	fclose(fp);
	if ((fp = fopen("ticket.dat", "ab")) == NULL) {
		printf(" >> �û���Ʊ��Ϣ�ļ�'ticket.dat'��ʧ��...\n");
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
		printf(" >> �û���Ʊ��Ϣ�ļ�'ticket.dat'��ʧ��...\n");
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
	printf(" |      �û���Ʊϵͳ       |\n");
	printf(" ---------------------------\n");
	printf(" |   [1]��ʼ�˻ؾ�����Ʊ   |\n");
	printf(" |   [/]�˳�ϵͳ           |\n");
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
	printf(" >> ���������ѯ�Ķ����ţ�");
	scanf("%s", queryOrderNum);
	if ((fp = fopen("ticket.dat", "rb")) == NULL) {
		printf(" >> �û���Ʊ��Ϣ�ļ�'ticket.dat'��ʧ��...\n");
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
			printf("|����                |������      |\n");
			printf("|%-18s  |%-10s  |\n", name, orderNumber);
			printf("|���֤��            |������    |\n");
			printf("|%-20s|%-10s  |\n", id, ticketNO);
			printf("-----------------------------------\n\n");
		}
	}
	if (!flagFind) printf(" >> δ���ҵ�������Ϊ'%s'�������Ϣ...\n", queryOrderNum);
}
void QueryTicketName() {
	FILE *fp;
	int flagFind = 0;
	int fstPtr, slwPtr;
	char tmpStr[50];
	char name[15], id[20];
	char ticketNO[10], orderNumber[10];
	char queryName[15];
	printf(" >> ���������ѯ��������");
	scanf("%s", queryName);
	if ((fp = fopen("ticket.dat", "rb")) == NULL) {
		printf(" >> �û���Ʊ��Ϣ�ļ�'ticket.dat'��ʧ��...\n");
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
			printf("|����                |������      |\n");
			printf("|%-18s  |%-10s  |\n", name, orderNumber);
			printf("|���֤��            |������    |\n");
			printf("|%-20s|%-10s  |\n", id, ticketNO);
			printf("-----------------------------------\n\n");
		}
	}
	if (!flagFind) printf(" >> δ���ҵ�����Ϊ'%s'�������Ϣ...\n", queryName);
}
void QueryTicketNO() {
	FILE *fp;
	int flagFind = 0;
	int fstPtr, slwPtr;
	char tmpStr[50];
	char name[15], id[20];
	char ticketNO[10], orderNumber[10];
	char queryNO[15];
	printf(" >> ���������ѯ�ľ����ţ�");
	scanf("%s", queryNO);
	if ((fp = fopen("ticket.dat", "rb")) == NULL) {
		printf(" >> �û���Ʊ��Ϣ�ļ�'ticket.dat'��ʧ��...\n");
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
			printf("|����                |������      |\n");
			printf("|%-18s  |%-10s  |\n", name, orderNumber);
			printf("|���֤��            |������    |\n");
			printf("|%-20s|%-10s  |\n", id, ticketNO);
			printf("-----------------------------------\n\n");
		}
	}
	if (!flagFind) printf(" >> δ���ҵ�������Ϊ'%s'�������Ϣ...\n", queryNO);
}
void PrintQueryTicketMenu() {
	printf(" ---------------------------\n");
	printf(" |      �û���ѯϵͳ       |\n");
	printf(" ---------------------------\n");
	printf(" |     [1]�����Ų�ѯ       |\n");
	printf(" |     [2]�û�����ѯ       |\n");
	printf(" |     [3]�����ѯ         |\n");
	printf(" |     [/]�˳�ϵͳ         |\n");
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
	system("title ������Դ����ϵͳ By Jie0355"); 
	//system("color 0A");
	printf(" -------------------------------------------------------------\n");
	printf(" |                  ��ӭʹ��������Դ����ϵͳ                 |\n");
	printf(" |                       ���� : Jie0355                      |\n");
	printf(" |                   ����ʱ�� : 2022.06.06                   |\n");
	printf(" |                      Version : 1.0.0                      |\n");
	printf(" -------------------------------------------------------------\n");
	Sleep(1000); system("cls");
	printf("                            ����������\n");
	printf("                                    ��\n");
	printf("                                    ��\n");
	printf("                            ����������\n");
	printf("                                    ��\n");
	printf("                                    ��\n");
	printf("                            ����������\n");
	Sleep(1000); system("cls");
	printf("                            ����������\n");
	printf("                                    ��\n");
	printf("                                    ��\n");
	printf("                            ����������\n");
	printf("                            ��       \n");
	printf("                            ��       \n");
	printf("                            ����������\n");
	Sleep(1000); system("cls");
	printf("                              ����\n");
	printf("                                ��\n");
	printf("                                ��\n");
	printf("                                ��\n");
	printf("                                ��\n");
	printf("                                ��\n");
	printf("                              ������\n");
	Sleep(1000); system("cls");
}
void Exittks() {
	printf("                            ����������\n");
	printf("                                    ��\n");
	printf("                                    ��\n");
	printf("                            ����������\n");
	printf("                                    ��\n");
	printf("                                    ��\n");
	printf("                            ����������\n");
	Sleep(1000); system("cls");
	printf("                            ����������\n");
	printf("                                    ��\n");
	printf("                                    ��\n");
	printf("                            ����������\n");
	printf("                            ��       \n");
	printf("                            ��       \n");
	printf("                            ����������\n");
	Sleep(1000); system("cls");
	printf("                              ����\n");
	printf("                                ��\n");
	printf("                                ��\n");
	printf("                                ��\n");
	printf("                                ��\n");
	printf("                                ��\n");
	printf("                              ������\n");
	Sleep(1000); system("cls");
	printf(" ----------------------------------------\n");
	printf(" |       �ɹ��˳�������Դ����ϵͳ       |\n");
	printf(" |      *^_^*�ڴ������´�ʹ��*^_^*      |\n");
	printf(" |            ���� : Jie0355            |\n");
	printf(" |     ��ϵ��ʽ : 1955864881@qq.com     |\n");
	printf(" ----------------------------------------\n");
}
