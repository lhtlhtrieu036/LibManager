#pragma once
#ifndef MENU_H
#define MENU_H
#endif // !MENU_H

#define EXIT_COMMAND_CODE    3817 // E - X - I - T
#define LOGOUT_COMMAND_CODE  6969 // nonsense, se set gia tri khac trong tuong lai
#define CHANGE_PASSWORD_COMMAND_CODE 9455 // P - A - S -S.
#define CHANGE_INFO_COMMAND_CODE 1024 // nonsense, se set gia tri khac trong tuong lai.

// COMMAND CODE for Doc gia
#define XEM_DOC_GIA_COMMAND_CODE 2100
#define TIM_DOC_GIA_CMND_COMMAND_CODE 2500
#define TIM_DOC_GIA_HO_TEN_COMMAND_CODE 2600


// COMMAND CODE for Thong ke
#define THONG_KE_SO_LUONG_DOC_GIA_COMMAND_CODE 6300
#define THONG_KE_DOC_GIA_GIOI_TINH_COMMAND_CODE 6400

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

#define MENU_THEM_USER_COMMAND_CODE 8
#define MENU_PHAN_QUYEN_USER_COMMAND_CODE 9

// Chua dang nhap
void nonLoggedInMenu();

// Menu co ban.
void generalMenu();

// Menu thay doi thong tin nguoi dung.
void editInfoMenu();

// Menu cho admin.
void adminMenu();

// Menu quan ly doc gia.
void quanLyDocGia();

// Menu thong ke co ban.
void thongKeCoBan(user_info*);

// Xu ly cho cac menu
void catchEditInfoMenu(account*&, user_info*&);

// Ham xac nhan hanh dong cua nguoi dung.
bool confirmationBox();