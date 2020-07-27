#pragma once
#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H
#endif

#include"include.h"

// Ham dang nhap - tra ve con tro den user.
account* logUserIn(const char*, const char*, accountList*);

// Ham dang xuat khoi he thong.
void logUserOut(account*&, user_info*&);

// Ham kiem tra nguoi dung da dang nhap chua.
bool isLoggedIn(account*, user_info*);

// Ham kiem tra user co phai admin hay khong.
bool isAdmin(user_info*);

// Ham kiem tra user co phai quan ly hay khong.
bool isQuanLy(user_info*);

// Ham kiem tra user co phai chuyen vien hay khong.
bool isChuyenVien(user_info*);

// Ham kiem tra user con active hay bi block.
bool isActive(user_info*);