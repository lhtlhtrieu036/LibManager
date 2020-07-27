#pragma once

#include"include.h"

#define DOCGIA_FILE "docgia.dat"
#define DOCGIA_NAM 1
#define DOCGIA_NU  0

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
    nodeDocGia* docGiaDau;
    nodeDocGia* docGiaCuoi;
};

danhSachDocGia* createDanhSachDocGia();

nodeDocGia* createDocGiaNode(theDocGia);

danhSachDocGia* getDanhSachDocGiaList(int&);

bool isNam(theDocGia);

bool isCSV(char const*);

bool validateDocGiaInfo(theDocGia, danhSachDocGia*);

bool editTenDocGia(nodeDocGia*&);

bool editCMNDDocGia(nodeDocGia*&, danhSachDocGia*&);

bool editNgaySinhDocGia(nodeDocGia*&);

bool editEmailDocGia(nodeDocGia*&);

bool editDiaChiDocGia(nodeDocGia*&);

bool editGioiTinhDocGia(nodeDocGia*&);

bool deleteDocGia(int ID, danhSachDocGia*&, int&);

nodeDocGia* searchForDocGiaByCMND(const char*, danhSachDocGia*);

nodeDocGia* searchForDocGiaByID(int, danhSachDocGia*);

void searchForDocGiaByHoTen(const char*, danhSachDocGia*);

int themDocGiaTuCSV(FILE*, danhSachDocGia*&, int&);

int getMaxID(danhSachDocGia*);

void deleteDocGiaDau(danhSachDocGia*&);

void deleteDocGiaCuoi(danhSachDocGia*&);

void deleteDocGiaGiua(nodeDocGia*&);

void freeDanhSachDocGia(danhSachDocGia*&);

void xemDanhSachDocGia(nodeDocGia*);

void thongKeTheoGioiTinh(danhSachDocGia*, int);

void inDocGia(theDocGia);