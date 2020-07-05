#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

// Account file.
#define ACCOUNT_FILE   "users.dat"
#define USER_INFO_FILE "infos.dat"

// Username & password
#define USERNAME_MAX_SIZE 30
#define USERNAME_MIN_SIZE 1
#define PASSWORD_MAX_SIZE 30
#define PASSWORD_MIN_SIZE 8

// Phan quyen nguoi dung
#define USER_ADMIN  1
#define USER_QUANLY 2
#define USER_CVIEN  3

// Thong tin nguoi dung
#define NAME_MAX 30
#define BIRTH_DAY 12
#define CMND 10
#define ADDRESS 50
#define SEX 4

// Cau truc cua mot tai khoan gom ID, username va password.
struct account 
{

    int ID;
    char user_name[USERNAME_MAX_SIZE];
    char pass_word[PASSWORD_MAX_SIZE];

};

// O day ta se bieu dien danh sach tai khoan
// duoi dang danh sach lien ket kep.
struct accountNode {
    account* credentials;
    accountNode* nextAccount;
    accountNode* prevAccount;
};

struct accountList {
    accountNode* head;
    accountNode* tail;
};

// Cau truc thong tin cua mot user.
struct user_info
{
    int ID;
    int permissions;
    char ho_Ten[NAME_MAX];
    char ngay_Sinh[BIRTH_DAY];
    char so_CMND[CMND];
    char dia_Chi[ADDRESS];
    char gioi_Tinh[SEX];
    bool tinh_Trang;
};

// Ta cung bieu dien danh sach thong tin tai khoan
// duoi dang danh sach lien ket kep.
struct userInfoNode {
    user_info* info;
    userInfoNode* nextUser;
    userInfoNode* prevUser;
};

struct userInfoList {
    userInfoNode* head;
    userInfoNode* tail;
};
#endif


// Ham tao mot account node.
// Ham nay duoc viet rieng, vi co the duoc tai su dung
// trong qua trinh tao account moi.
accountNode* createAccountNode(account* newAccount);

// Ham lay list account tu file.
accountList* getAccountList(int&);

// Ham tao mot info node.
// Ham nay duoc viet rieng, vi co the duoc tai su dung
// trong qua trinh tao account moi.
userInfoNode* createInfoNode(user_info*);

// Ham lay list user info tu 1 file.
userInfoList* getUserInfoList(int);

// Ham lay thong tin tai khoan - con tro den thong tin tai khoan.
// aka nap user tu list vao session.
user_info* getUserInfo(userInfoList*, account*);

//
// Ham giai phong list user (khi thoat chuong trinh)
//
void freeAccountNode(accountList*&);
void freeAccountList(accountList*&);

//
// Ham giai phong list user info (khi thoat chuong trinh)
//
void freeUserInfoNode(userInfoList*&);
void freeUserInfoList(userInfoList*&);