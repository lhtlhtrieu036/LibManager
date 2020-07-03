#pragma once
#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H
#endif

#include"include.h"

// Ham tao mot account node.
// Ham nay duoc viet rieng, vi co the duoc tai su dung
// trong qua trinh tao account moi.
accountNode* createAccountNode(account*);

// Ham lay list account tu file.
accountList* getAccountList(int&);

// Ham tao mot info node.
// Ham nay duoc viet rieng, vi co the duoc tai su dung
// trong qua trinh tao account moi.
userInfoNode* createInfoNode(user_info*);

// Ham lay list user info tu 1 file.
userInfoList* getUserInfoList(int);

// Ham dang nhap - tra ve con tro den user.
account* logUserIn(accountList*, char*, char*);

// Ham lay thong tin tai khoan - con tro den thong tin tai khoan.
user_info* getUserInfo(account*);

// Ham kiem tra user co phai admin hay khong.
int isAdmin(user_info*);

// Ham kiem tra user co phai quan ly hay khong.
int isQuanLy(user_info*);

// Ham kiem tra user con active hay bi block.
int isActive(user_info*);