#include"include.h"

// Ham tao mot account node.
accountNode* createAccountNode(account* newAccount) {
    accountNode* newAccountNode = (accountNode*)malloc(sizeof(accountNode));

    newAccountNode->credentials = newAccount;
    newAccountNode->nextAccount = NULL;
    newAccountNode->prevAccount = NULL;

    return newAccountNode;
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
        accountNode* newAccountNode = createAccountNode(newAccount);

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

    return newInfoList;
}

// Ham lay thong tin tai khoan cua nguoi dung.
// aka nap thong tin user tu list vao session.
user_info* getUserInfo(userInfoList* infoList, account* credentials) {
    userInfoNode* thisUserInfo = infoList->head;
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

// Ham doi mat khau cua nguoi dung.
bool changeUserPassword(account* user) {
    char currentPassword[PASSWORD_MAX_SIZE], newPassword[PASSWORD_MAX_SIZE], renewPassword[PASSWORD_MAX_SIZE];
    cout << "Nhap mat khau hien tai cua ban: " << endl; 
    cin >> currentPassword;
    cout << "Nhap mat khau moi cua ban (min = " << PASSWORD_MIN_SIZE << ", max = " << PASSWORD_MAX_SIZE << " ky tu): " << endl;
    cin >> newPassword;
    cout << "Nhap lai mat khau moi cua ban: " << endl;
    cin >> renewPassword;

    // 2 mat khau khong trung nhau.
    if (strcmp(currentPassword, user->pass_word) != 0) {
        cout << "Mat khau hien tai khong trung khop. Xin thu lai." << endl;
        return false;
    }

    // Mat khau moi hoac nhap lai mat khau moi khong dung.
    if (strcmp(newPassword, renewPassword) != 0) {
        cout << "Ban nhap sai mat khau moi, xin vui long thu lai." << endl;
        return false;
    }

    // Kiem tra do dai mat khau.
    // Phan nay nen duoc viet vao 1 file validation, nhung de viet sau.
    if (strlen(newPassword) > PASSWORD_MAX_SIZE || strlen(newPassword) < PASSWORD_MIN_SIZE) {
        cout << "Do dai mat khau khong phu hop, xin hay thu lai." << endl;
        return false;
    }
    
    // Doi mat khau va yeu cau nguoi dung dang nhap lai.
    // tuy nhien, action dang xuat se xu ly trong controller ngoai main.
    strcpy(user->pass_word, newPassword);
    cout << "Da doi mat khau thanh cong, vui long dang nhap lai." << endl;

    return true;
}

//
// Ham xoa phan tu dau cua list.
//
void freeAccountNode(accountList*& users) {
    accountNode* newHead = users->head->nextAccount;

    // Node cuoi cung cua list
    if (newHead == NULL) {
        free(users->head);
        users->head = NULL;
        users->tail = NULL;
    }
    else {
        newHead->prevAccount = NULL;
        free(users->head);
        users->head = newHead;
    }
}

//
// Ham xoa toan bo danh sach lien ket luu users.
//
void freeAccountList(accountList*& users) {
    while (users->head != NULL) freeAccountNode(users);
    free(users);
}

//
// Ham xoa user info o dau list.
//
void freeUserInfoNode(userInfoList*& infos) {
    userInfoNode* newHead = infos->head->nextUser;

    // Node cuoi cung cua list.
    if (newHead == NULL) {
        free(infos->head);
        infos->head = NULL;
        infos->tail = NULL;
    }
    else {
        newHead->prevUser = NULL;
        free(infos->head);
        infos->head = newHead;
    }
}

//
// Ham xoa toan bo list user info.
//
void freeUserInfoList(userInfoList*& infos) {
    while (infos->head != NULL) freeUserInfoNode(infos);
    free(infos);
}