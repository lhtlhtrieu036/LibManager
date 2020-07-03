#include"include.h"

// Ham tao mot account node.
accountNode* createAccountNode(account* newAccount) {
	accountNode* newAccountNode = (accountNode*)malloc(sizeof(accountNode));
	
	newAccountNode->credentials = newAccount;
	newAccountNode->nextAccount = NULL;
	newAccountNode->prevAccount = NULL;
	
	return accountNode;
}

// Ham lay list account tu file.
accountList* getAccountList(int& totalAccount) {
	FILE* f = fopen(ACCOUNT_FILE, "rb+");
	if (f == NULL) return NULL;

	// Tao mot account list moi.
	accountList* newAccountList = (accountList*)malloc(sizeof(accountList));
	newAccountList->head = NULL;
	newAccountList->tail = NULL;

	// Lay tong so account.
	fseek(f, 0, SEEK_SET);
	fread(&totalAccount, sizeof(int), 1, f);

	// Doc cac account vao list
	for (int i = 1; i <= totalAccount; ++i) {
		account* newAccount = (account*)malloc(sizeof(account));
		fread(newAccount, sizeof(account), 1, f);

		// Tao mot node moi
		// (Dang le buoc nay nen duoc viet vao 1 ham rieng).
		accountNode* newAccountNode = createAccountNode(account);

		// Them account vao duoi cua list.
		// Neu list dang rong thi head = tail = newNode.
		if (newAccountList->head == NULL) {
			newAccountList->head = newAccountNode;
			newAccountList->tail = newAccountNode;
		}
		else {
			newAccountList->tail->nextAccount = newAccountNode;
			newAccountNode->prevAccount = newAccountList->tail;
			newAccountList->tail = newAccountNode;
		}
	}

	fclose(f);

	// Tra ve danh sach vua tao.
	return newAccountList;
}

// Ham tao mot info node.
userInfoNode* createInfoNode(user_info* userInfo) {
	userInfoNode* newInfoNode = (userInfoNode*)malloc(sizeof(userInfoNode));
	
	newInfoNode->info = userInfo;
	newInfoNode->nextUser = NULL;
	newInfoNode->prevUser = NULL;
	
	return newInfoNode;
}

userInfoList* getUserInfoList(int totalAccount) {
	FILE* f = fopen(USER_INFO_FILE, "rb+");
	if (f == NULL) return NULL;

	// Tao mot danh sach thong tin user moi.
	userInfoList* newInfoList = (userInfoList*)malloc(sizeof(userInfoList));
	newInfoList->head = NULL;
	newInfoList->tail = NULL;

	fseek(f, 0, SEEK_SET);

	// Doc tung block info vao cac node roi noi vao list.
	for (int i = 1; i <= totalAccount; ++i) {
		user_info* newInfo = (user_info*)malloc(sizeof(user_info));
		fread(newInfo, sizeof(user_info), 1, f);

		userInfoNode* newInfoNode = createInfoNode(newInfo);

		// Them info vao duoi list,
		// neu list rong thi head = tail = newInfoNode.
		if (newInfoList->head == NULL) {
			newInfoList->head = newInfoNode;
			newInfoList->tail = newInfoNode;
		}
		else {
			newInfoList->tail->nextUser = newInfoNode;
			newInfoNode->prevUser = newInfoList->tail;
			newInfoList->tail = newInfoNode;
		}
	}

	fclose(f);

	return userInfoList;
}

// Ham dang nhap, tra ve con tro den tai khoan cua user.
account* logUserIn(accountList* database, char* username, char* password) {
	accountNode* accountInDB = database->head;
	while (accountInDB != NULL) {
		// Lay thong tin tu 1 node.
		account* credentials = accountInDB->credentials;

		// Kiem tra neu thong tin dang nhap trung khop
		// thi tra ve node do.
		if (strcmp(credentials->user_name, username) == 0 &&
			strcmp(credentials->pass_word, password) == 0)
			return accountInDB;

		// Kiem tra sang node tiep theo.
		accountInDB = accountInDB->nextAccount;
	}

	// Khong co tai khoan nao khop voi thong tin dang nhap,
	// tra ve NULL.
	return NULL;
}

// Ham lay thong tin tai khoan cua nguoi dung.
user_info* getUserInfo(userInfoList* infoList, account* credentials) {
	userInfoNode* thisUserInfo = userInfoList->head;
	while (thisUserInfo != NULL) {
		// Lay thong tin cua 1 node.
		user_info* info = thisUserInfo->info;

		// Neu ID cua node do trung voi ID cua nguoi dung da dang nhap,
		// tra ve node thong tin.
		if (info->ID == credentials->ID) return info;

		// Kiem tra sang node tiep theo.
		thisUserInfo = thisUserInfo->nextUser;
	}

	// Truong hop user dang nhap ma khong co info rat kho xay ra,
	// nhung van phai tra ve NULL de bao loi.
	return NULL;
}

// Ham kiem tra user co phai admin hay khong.
int isAdmin(user_info* userInfo) {
	return userInfo->permissions == USER_ADMIN;
}

// Ham kiem tra user co phai quan ly hay khong.
int isQuanLy(user_info* userInfo) {
	return userInfo->permissions == USER_QUANLY;
}

// Ham kiem tra tai khoan con active hay khong.
int isActive(user_info* userInfo) {
	return userInfo->tinh_Trang;
}