#include"include.h"

// Ham dang nhap, tra ve con tro den tai khoan cua user.
account* logUserIn(accountList* list) {
    char username[USERNAME_MAX_SIZE], password[PASSWORD_MAX_SIZE];
    cout << "== Dang nhap vao tai khoan ==" << endl;
    cout << "Tai khoan: "; cin >> username;
    cout << "Mat khau : "; cin >> password;

    accountNode* accountInDB = list->head;
    while (accountInDB != NULL) {
        // Lay thong tin tu 1 node.
        account* credentials = accountInDB->credentials;

        // Kiem tra neu thong tin dang nhap trung khop
        // thi tra ve node do.
        if (strcmp(credentials->user_name, username) == 0 &&
            strcmp(credentials->pass_word, password) == 0)
            return accountInDB->credentials;

        // Kiem tra sang node tiep theo.
        accountInDB = accountInDB->nextAccount;
    }

    // Khong co tai khoan nao khop voi thong tin dang nhap,
    // tra ve NULL.
    return NULL;
}

// Ham dang xuat khoi he thong.
void logUserOut(account*& user_session_account, user_info*& user_session_info) {
    // That ra dang xuat khoi he thong rat don gian:
    // Luu moi thong tin cua user vao node tro lai,
    // roi set cho cac bien session = NULL.
    //
    // Node se duoc ghi tro lai file truoc khi thoat hoan toan chuong trinh.

    // Vi chua co thao tac thay doi thong tin
    // nen chi unset cac bien session.
    user_session_account = NULL;
    user_session_info = NULL;
}

// Ham kiem tra xem nguoi dung dang nhap hay chua
bool isLoggedIn(account* user, user_info* info) {
    return user != NULL && info != NULL;
}

// Ham kiem tra user co phai admin hay khong.
bool isAdmin(user_info* userInfo) {
    return userInfo->permissions == USER_ADMIN;
}

// Ham kiem tra user co phai quan ly hay khong.
bool isQuanLy(user_info* userInfo) {
    return userInfo->permissions == USER_QUANLY;
}

// Ham kiem tra tai khoan con active hay khong.
bool isActive(user_info* userInfo) {
    return userInfo->tinh_Trang;
}