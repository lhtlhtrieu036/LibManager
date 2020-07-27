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
#define THEM_DOC_GIA_CSV_COMMAND_CODE 2200
#define DOI_THONG_TIN_DOC_GIA_COMMAND_CODE 2300
#define XOA_DOC_GIA_COMMAND_CODE 2400
#define TIM_DOC_GIA_CMND_COMMAND_CODE 2500
#define TIM_DOC_GIA_HO_TEN_COMMAND_CODE 2600

// COMMAND CODE for Sach
#define XEM_SACH_COMMAND_CODE 3100
#define THEM_SACH_CSV_COMMAND_CODE 3200
#define DOI_THONG_TIN_SACH_COMMAND_CODE 3300
#define XOA_SACH_COMMAND_CODE 3400
#define TIM_SACH_THEO_ISBN_COMMAND_CODE 3500
#define TIM_SACH_THEO_TEN_COMAND_CODE 3600

// COMMAND CODE for Thong ke
#define THONG_KE_SO_LUONG_SACH_COMMAND_CODE 6100
#define THONG_KE_SACH_THEO_THE_LOAI_COMMAND_CODE 6200
#define THONG_KE_SO_LUONG_DOC_GIA_COMMAND_CODE 6300
#define THONG_KE_DOC_GIA_GIOI_TINH_COMMAND_CODE 6400
#define THONG_KE_SACH_DANG_MUON 6500
#define THONG_KE_DOC_GIA_TRE_HAN 6600

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

// Command menu thay doi thong tin doc gia
// Tuong tu menu ben tren, khong so trung.
#define MENU_DOI_TEN_DOC_GIA_COMMAND_CODE 1
#define MENU_DOI_CMND_DOC_GIA_COMMAND_CODE 2
#define MENU_DOI_NGAY_SINH_DOC_GIA_COMMAND_CODE 3
#define MENU_DOI_GIOI_TINH_DOC_GIA_COMMAND_CODE 4
#define MENU_DOI_EMAIL_DOC_GIA_COMMAND_CODE 5
#define MENU_DOI_DIA_CHI_DOC_GIA_COMMAND_CODE 6

// Command menu them user va phan quyen.
// (Menu danh rieng cho admin)
#define MENU_THEM_USER_COMMAND_CODE 8
#define MENU_PHAN_QUYEN_USER_COMMAND_CODE 9

// Menu co ban.
void generalMenu();

// Menu thay doi thong tin nguoi dung.
void editInfoMenu();

// Menu cho admin.
void adminMenu();

// Menu quan ly doc gia.
void quanLyDocGia(user_info*);

// Menu quan ly sach.
void quanLySach(user_info*);

// Menu thay doi thong tin doc gia.
void editInfoDocGia();

// Menu thong ke co ban.
void thongKeCoBan(user_info*);

// Xu ly cho cac menu thay doi thong tin nguoi dung.
void catchEditInfoMenu(account*&, user_info*&);

// Xu ly cho menu thay doi thong tin doc gia.
void catchEditInfoDocGia(nodeDocGia*&, danhSachDocGia*&);

// Ham xac nhan hanh dong cua nguoi dung.
bool confirmationBox();