#pragma once

#include"include.h"

struct theDocGia {
    int maDocGia;
    char ho_Ten[NAME_MAX];
    char so_CMND[CMND_MAX];
    char ngay_Sinh[BIRTH_DAY];
    int gioiTinh;
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

nodeDocGia* searchForDocGiaByCMND(const char*, danhSachDocGia*);

void searchForDocGiaByHoTen(const char*, danhSachDocGia*);

void deleteDocGiaDau(danhSachDocGia*&);

void freeDanhSachDocGia(danhSachDocGia*&);

void xemDanhSachDocGia(nodeDocGia*);

void inDocGia(theDocGia);