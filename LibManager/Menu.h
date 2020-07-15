#pragma once
#ifndef MENU_H
#define MENU_H
#endif // !MENU_H

#define EXIT_COMMAND_CODE    3817 // E - X - I - T
#define LOGOUT_COMMAND_CODE  6969 // nonsense, se set gia tri khac trong tuong lai
#define CHANGE_PASSWORD_COMMAND_CODE 9455 // P - A - S -S.
#define CHANGE_INFO_COMMAND_CODE 1024 // nonsense, se set gia tri khac trong tuong lai.

// Command menu thay doi thong tin nguoi dung.
// Menu thong tin co the nhan trung gia tri voi menu ben tren,
// nhung xu ly 2 cai nay rieng nen khong xung dot.
#define MENU_DOI_TEN_COMMAND_CODE 1
#define MENU_DOI_NGAY_SINH_COMMAND_CODE 2
#define MENU_DOI_CMND_COMMAND_CODE 3
#define MENU_DOI_DIA_CHI_COMMAND_CODE 4
#define MENU_DOI_GIOI_TINH_COMMAND_CODE 5
#define MENU_THOAT_DOI_COMMAND_CODE 6
#define MENU_XEM_THONG_TIN_COMMAND_CODE 7

// Chua dang nhap
void nonLoggedInMenu();

// Menu co ban.
void generalMenu();

// Menu thay doi thong tin nguoi dung.
void editInfoMenu();

// Menu cho admin.
void adminMenu();

// Menu cho quan ly.
void quanlyMenu();

// Menu cho chuyen vien.
void chuyenvienMenu();


// Xu ly cho cac menu
void catchEditInfoMenu(account*&, user_info*&);