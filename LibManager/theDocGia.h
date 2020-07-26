#pragma once

#include"include.h"

#define DOCGIA_FILE "docgia.dat"
#define NAM 1
#define NU  0

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

nodeDocGia* searchForDocGiaByCMND(const char*, danhSachDocGia*);

void searchForDocGiaByHoTen(const char*, danhSachDocGia*);

void themDocGiaTuCSV(FILE*, danhSachDocGia*&, int&);

void deleteDocGiaDau(danhSachDocGia*&);

void freeDanhSachDocGia(danhSachDocGia*&);

void xemDanhSachDocGia(nodeDocGia*);

void thongKeTheoGioiTinh(danhSachDocGia*, int);

void inDocGia(theDocGia);