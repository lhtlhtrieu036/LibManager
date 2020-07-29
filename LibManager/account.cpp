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
accountList* getAccountList() {
    FILE* f = fopen(ACCOUNT_FILE, "rb+");
    if (f == NULL) return NULL;

    // Tao mot account list moi.
    accountList* newAccountList = (accountList*)malloc(sizeof(accountList));
    newAccountList->head = NULL;
    newAccountList->tail = NULL;

    // Lay tong so account.
    fseek(f, 0, SEEK_SET);
    fread(&newAccountList->totalAccount, sizeof(int), 1, f);

    // Doc cac account vao list
    for (int i = 1; i <= newAccountList->totalAccount; ++i) {
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

// Ham lay thong tin nguoi dung tu ID.
userInfoNode* getUserFromID(int ID, userInfoList* list) {
    userInfoNode* thisUser = list->head;
    
    while (thisUser != NULL) {
        if (thisUser->info->ID == ID) return thisUser;
        thisUser = thisUser->nextUser;
    }

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

    if (confirmationBox()) {
        // Doi mat khau va yeu cau nguoi dung dang nhap lai.
        // tuy nhien, action dang xuat se xu ly trong controller ngoai main.
        strcpy(user->pass_word, newPassword);
        cout << "Da doi mat khau thanh cong, vui long dang nhap lai." << endl;

        return true;
    }
    return false;
}

//
// Ham doi CMND nguoi dung.
//
bool editUserCMND(user_info*& user_session_info) {
    char soCMND[CMND_MAX]; 
    
    cin.ignore();
    cin >> soCMND;

    if (strlen(soCMND) >= CMND_MIN && strlen(soCMND) <= CMND_MAX) {
        if (confirmationBox()) {
            strcpy(user_session_info->so_CMND, soCMND);
            return true;
        }
    }

    return false;
}

//
// Ham doi ten nguoi dung.
//
bool editUserHoTen(user_info*& user_session_info) {
    char hoTen[NAME_MAX]; 
    
    cin.ignore();
    cin.getline(hoTen, NAME_MAX);

    if (strlen(hoTen) >= NAME_MIN && strlen(hoTen) <= NAME_MAX) {
        if (confirmationBox()) {
            strcpy(user_session_info->ho_Ten, hoTen);
            return true;
        }
    }

    return false;
}

//
// Ham doi dia chi nguoi dung.
//
bool editUserDiaChi(user_info*& user_session_info) {
    char diaChi[ADDRESS_MAX];

    cin.ignore();
    cin.getline(diaChi, ADDRESS_MAX);

    if (strlen(diaChi) >= ADDRESS_MIN && strlen(diaChi) <= ADDRESS_MAX) {
        if (confirmationBox()) {
            strcpy(user_session_info->dia_Chi, diaChi);
            return true;
        }
    }
    
    return false;
}

//
// Ham doi gioi tinh nguoi dung.
//
bool editUserGioiTinh(user_info*& user_session_info) {
    char gioiTinh[SEX];

    cin.ignore();
    cin >> gioiTinh;

    if (confirmationBox()) {
        strcpy(user_session_info->gioi_Tinh, gioiTinh);

        return true;
    }
    return false;
}

//
// Ham doi ngay sinh nguoi dung.
//
bool editUserNgaySinh(user_info*& user_session_info) {
    char ngaySinh[BIRTH_DAY];

    cin.ignore();
    cin >> ngaySinh;

    // Neu ngay thang khong hop le, bao loi.
    if (!dateCheck(chuyenDoiNgay(ngaySinh))) return false;

    if (confirmationBox()) {
        strcpy(user_session_info->ngay_Sinh, ngaySinh);

        return true;
    }

    return false;
}

//
// Ham them nguoi dung vao danh sach.
//
bool addUser(accountList*& userList, userInfoList*& infoList) {
    char username[USERNAME_MAX_SIZE];
    char password[PASSWORD_MAX_SIZE];

    cout << "Tai khoan moi: "; cin >> username;
    cout << "Mat khau moi: "; cin >> password;

    if (strlen(username) >= USERNAME_MIN_SIZE && strlen(username) <= USERNAME_MAX_SIZE &&
        strlen(password) >= PASSWORD_MIN_SIZE && strlen(password) <= PASSWORD_MAX_SIZE) {
        if (!confirmationBox()) return false;

        // Tao mot tai khoan moi.
        account* newAccount = (account*)malloc(sizeof(account));
        newAccount->ID = ++userList->totalAccount;
        strcpy(newAccount->user_name, username);
        strcpy(newAccount->pass_word, password);

        // Tao info nguoi dung, info se la he thong cho.
        // Info nguoi dung se do nguoi dung tu thay doi.
        user_info* newInfo = (user_info*)malloc(sizeof(user_info));
        newInfo->ID = newAccount->ID;
        strcpy(newInfo->ho_Ten, "Nguyen Van A");
        strcpy(newInfo->dia_Chi, "Viet Nam");
        strcpy(newInfo->ngay_Sinh, "01012001");
        strcpy(newInfo->so_CMND, "000000000");
        strcpy(newInfo->gioi_Tinh, "nam");
        newInfo->permissions = USER_CVIEN;

        // Tao node va gan vao duoi moi list.
        accountNode* newAccountNode = createAccountNode(newAccount);
        userInfoNode* newInfoNode = createInfoNode(newInfo);

        // Gan account vao duoi list account.
        newAccountNode->prevAccount = userList->tail;
        userList->tail->nextAccount = newAccountNode;
        userList->tail = newAccountNode;

        // Gan info vao duoi list info.
        newInfoNode->prevUser = infoList->tail;
        infoList->tail->nextUser = newInfoNode;
        infoList->tail = newInfoNode;

        return true;
    }

    return false;
}

//
// Ham phan quyen cho user.
//
bool permissionUser(userInfoList*& infoList) {
    int userID, newPermission;
    cout << "ID nguoi dung can phan quyen: "; cin >> userID;
    cout << "== Cac quyen hien co: ==" << endl;
    cout << USER_QUANLY << ". Quan ly." << endl;
    cout << USER_CVIEN << ". Chuyen vien." << endl;
    cout << "Quyen moi cua nguoi dung: "; cin >> newPermission;

    userInfoNode* userNode = getUserFromID(userID, infoList);

    // Neu user khong ton tai, tra ve false.
    if (userNode == NULL) 
        return false;

    // Neu user la admin, tra ve false.
    if (isAdmin(userNode->info)) 
        return false;

    // Neu phan quyen la, tra ve false.
    if (newPermission != USER_QUANLY && newPermission != USER_CVIEN)
        return false;

    
    if (!confirmationBox()) return false;

    // Phan quyen cho nguoi dung.
    userNode->info->permissions = newPermission;

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

void writeCredentialsBackToFile(accountList* users) {
    FILE* f = fopen(ACCOUNT_FILE, "wb+");
    fseek(f, 0, SEEK_SET);

    // Ghi tong so user.
    fwrite(&users->totalAccount, sizeof(int), 1, f);

    // Ghi credentials tung user.
    accountNode* thisNode = users->head;
    while (thisNode != NULL) {
        fwrite(thisNode->credentials, sizeof(account), 1, f);
        thisNode = thisNode->nextAccount;
    }
    fclose(f);
}

void writeInfoBackToFile(userInfoList* infos) {
    FILE* f = fopen(USER_INFO_FILE, "wb+");
    fseek(f, 0, SEEK_SET);

    // Ghi info tung user.
    userInfoNode* thisUserInfo = infos->head;
    while (thisUserInfo != NULL) {
        fwrite(thisUserInfo->info, sizeof(user_info), 1, f);
        thisUserInfo = thisUserInfo->nextUser;
    }
    fclose(f);
}
