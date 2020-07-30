#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include "include.h"

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
#define NAME_MIN 10
#define BIRTH_DAY 11
#define CMND_MIN 9
#define CMND_MAX 10
#define EMAIL_MIN 10
#define EMAIL_MAX 30
#define ADDRESS_MIN 10
#define ADDRESS_MAX 50
#define SEX 4

// Cau truc cua mot tai khoan gom ID, username va password.
struct account {
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
    int totalAccount;
    accountNode* head;
    accountNode* tail;
};

// Cau truc thong tin cua mot user.
struct user_info {
    int ID;
    int permissions;
    char ho_Ten[NAME_MAX];
    char ngay_Sinh[BIRTH_DAY];
    char so_CMND[CMND_MAX];
    char dia_Chi[ADDRESS_MAX];
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

//void read_user_data(ifstream& p, user_info& a);
//void read_Mang_User(ifstream& p, user_info* a, int& n);

// Ham tao mot account node.
// Ham nay duoc viet rieng, vi co the duoc tai su dung
// trong qua trinh tao account moi.
accountNode* createAccountNode(account* newAccount);

// Ham lay list account tu file.
accountList* getAccountList();

// Ham tao mot info node.
// Ham nay duoc viet rieng, vi co the duoc tai su dung
// trong qua trinh tao account moi.
userInfoNode* createInfoNode(user_info*);

// Ham lay list user info tu 1 file.
userInfoList* getUserInfoList(int);

// Ham lay thong tin tai khoan - con tro den thong tin tai khoan.
// aka nap user tu list vao session.
user_info* getUserInfo(userInfoList*, account*);

// Ham lay thong tin tu ID.
userInfoNode* getUserFromID(int, userInfoList*);

// Ham doi CMND user.
bool editUserCMND(user_info*&);

// Ham doi ho ten user.
bool editUserHoTen(user_info*&);

// Ham doi dia chi user.
bool editUserDiaChi(user_info*&);

// Ham doi gioi tinh user.
bool editUserGioiTinh(user_info*&);

// Ham doi ngay sinh user.
bool editUserNgaySinh(user_info*&);

// Ham doi password user.
bool changeUserPassword(account*);

// Ham them user.
bool addUser(accountList*&, userInfoList*&);

// Ham phan quyen user.
bool permissionUser(userInfoList*&);

// Ham bo kich hoat tai khoan user.
bool deactivateUser(int, userInfoList*&);

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

//
// Ham in thong tin user.
//
void printAccountsInfo(accountList*, userInfoList*);

//
// Ham ghi tai khoan tro lai file.
//
void writeCredentialsBackToFile(accountList*);

//
// Ham ghi info nguoi dung tro lai file.
//
void writeInfoBackToFile(userInfoList*);