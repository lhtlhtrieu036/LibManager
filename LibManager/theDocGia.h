#pragma once

#include"include.h"

#define DOCGIA_FILE "docgia.dat"
#define DOCGIA_NAM 1
#define DOCGIA_NU  0

struct ngayThangNam {
	int ngay;
	int thang;
	int nam;
};

struct theDocGia {
    int maDocGia;
    char ho_Ten[NAME_MAX];
    char so_CMND[CMND_MAX];
    char ngay_Sinh[BIRTH_DAY];
    int gioiTinh; // 1 : nam, 0 : nu
    char email[EMAIL_MAX];
    char diaChi[ADDRESS_MAX];
    // Them ngay lap the
    time_t ngayLapThe;
    // Them ngay het han
    time_t ngayHetHan;
};

struct nodeDocGia {
    theDocGia thongTinDocGia;
    nodeDocGia* docGiaTiepTheo;
    nodeDocGia* docGiaPhiaTruoc;
};

struct danhSachDocGia {
    int totalDocGia;
    nodeDocGia* docGiaDau;
    nodeDocGia* docGiaCuoi;
};

danhSachDocGia* createDanhSachDocGia();

nodeDocGia* createDocGiaNode(theDocGia);

danhSachDocGia* getDanhSachDocGiaList();

bool isNam(theDocGia);

bool isCSV(char const*);

bool validateDocGiaInfo(theDocGia, danhSachDocGia*);

bool editTenDocGia(nodeDocGia*&);

bool editCMNDDocGia(nodeDocGia*&, danhSachDocGia*&);

bool editNgaySinhDocGia(nodeDocGia*&);

bool editEmailDocGia(nodeDocGia*&);

bool editDiaChiDocGia(nodeDocGia*&);

bool editGioiTinhDocGia(nodeDocGia*&);

bool deleteDocGia(int, danhSachDocGia*&);

nodeDocGia* searchForDocGiaByCMND(const char*, danhSachDocGia*);

nodeDocGia* searchForDocGiaByID(int, danhSachDocGia*);

void searchForDocGiaByHoTen(const char*, danhSachDocGia*);

int themDocGiaTuCSV(FILE*, danhSachDocGia*&);

int getMaxID(danhSachDocGia*);

void deleteDocGiaDau(danhSachDocGia*&);

void deleteDocGiaCuoi(danhSachDocGia*&);

void deleteDocGiaGiua(nodeDocGia*&);

void freeDanhSachDocGia(danhSachDocGia*&);

void xemDanhSachDocGia(nodeDocGia*);

void thongKeTheoGioiTinh(danhSachDocGia*);

void inDocGia(theDocGia);

bool dateCheck(ngayThangNam);

ngayThangNam chuyenDoiNgay(char*);