#include"include.h"

// Ham tao mot danh sach doc gia (doubly-linked-list).
danhSachDocGia* createDanhSachDocGia() {
    danhSachDocGia* newList = (danhSachDocGia*)malloc(sizeof(danhSachDocGia));
    newList->docGiaDau = NULL;
    newList->docGiaCuoi = NULL;
    return newList;
}

// Ham tao mot node doc gia.
nodeDocGia* createDocGiaNode(theDocGia thongTinDocGia) {
    nodeDocGia* newNode = (nodeDocGia*)malloc(sizeof(nodeDocGia));
    newNode->docGiaPhiaTruoc = NULL;
    newNode->docGiaTiepTheo = NULL;
    newNode->thongTinDocGia = thongTinDocGia;
    return newNode;
}

// Ham doc danh sach doc gia vao mot doubly-linked-list.
danhSachDocGia* getDanhSachDocGiaList(int& totalDocGia) {
    FILE* f = fopen(DOCGIA_FILE, "rb+");

    if (f == NULL) return NULL;

    fseek(f, 0, SEEK_SET);
    fread(&totalDocGia, sizeof(totalDocGia), 1, f);
    
    danhSachDocGia* newList = createDanhSachDocGia();
    for (int i = 1; i <= totalDocGia; ++i) {
        theDocGia* newTheDocGia = (theDocGia*)malloc(sizeof(theDocGia));
        fread(newTheDocGia, sizeof(theDocGia), 1, f);
        nodeDocGia* newTheDocGiaNode = createDocGiaNode(*newTheDocGia);
        if (i == 1) {
            newList->docGiaDau = newTheDocGiaNode;
            newList->docGiaCuoi = newTheDocGiaNode;
        }
        else {
            newList->docGiaCuoi->docGiaTiepTheo = newTheDocGiaNode;
            newTheDocGiaNode->docGiaPhiaTruoc = newList->docGiaCuoi;
            newList->docGiaCuoi = newTheDocGiaNode;
        }
    }

    return newList;
}

nodeDocGia* searchForDocGiaByCMND(const char* CMND, danhSachDocGia* list) {
    nodeDocGia* thisNode = list->docGiaDau;
    while (thisNode != NULL) {
        if (strcmp(thisNode->thongTinDocGia.so_CMND, CMND) == 0)
            return thisNode;
    }
    return NULL;
}

void searchForDocGiaByHoTen(const char* HoTen, danhSachDocGia* list) {
    nodeDocGia* thisNode = list->docGiaDau;
    bool foundDocGia = false;
    while (thisNode != NULL) {
        if (strcmp(thisNode->thongTinDocGia.ho_Ten, HoTen) == 0) {
            inDocGia(thisNode->thongTinDocGia);
            foundDocGia = true;
        }
    }

    if (!foundDocGia) cout << "Khong tim thay doc gia co ten " << HoTen << endl;
}

void xemDanhSachDocGia(nodeDocGia* docGia) {
    if (docGia != NULL) {
        theDocGia thongTin = docGia->thongTinDocGia;
        inDocGia(thongTin);

        xemDanhSachDocGia(docGia->docGiaTiepTheo);
    }
}

void inDocGia(theDocGia thongTin) {
    printf("ID: %d\n", thongTin.maDocGia);
    printf("Ho ten: %s\n", thongTin.ho_Ten);
    printf("Gioi tinh: %s\n", (thongTin.gioiTinh == NAM) ? "NAM" : "NU");
    printf("CMND: %s\n", thongTin.so_CMND);
    printf("Ngay sinh: %s\n", thongTin.ngay_Sinh);
    cout << "Dia chi: " << thongTin.diaChi << endl;
    printf("Ngay lap the: %s\n", ctime(&thongTin.ngayLapThe));
    printf("Ngay het han: %s\n", ctime(&thongTin.ngayHetHan));
}

void deleteDocGiaDau(danhSachDocGia*& list) {
    nodeDocGia* headNode = list->docGiaDau;

    if (headNode->docGiaTiepTheo == NULL)
        list->docGiaDau = NULL;
    else list->docGiaDau = headNode->docGiaTiepTheo;

    free(headNode);
}

void freeDanhSachDocGia(danhSachDocGia*& list) {
    while (list->docGiaDau != NULL)
        deleteDocGiaDau(list);
    free(list);
}