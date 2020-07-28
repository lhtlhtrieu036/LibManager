#include"include.h"

// Ham tao mot danh sach doc gia (doubly-linked-list).
danhSachDocGia* createDanhSachDocGia() {
    danhSachDocGia* newList = (danhSachDocGia*)malloc(sizeof(danhSachDocGia));
    newList->docGiaDau = NULL;
    newList->docGiaCuoi = NULL;
    newList->totalDocGia = 0;
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
danhSachDocGia* getDanhSachDocGiaList() {
    FILE* f = fopen(DOCGIA_FILE, "rb+");

    if (f == NULL) return NULL;

    danhSachDocGia* newList = createDanhSachDocGia();

    fseek(f, 0, SEEK_SET);
    fread(&newList->totalDocGia, sizeof(int), 1, f);
    
    
    for (int i = 1; i <= newList->totalDocGia; ++i) {
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

bool isNam(theDocGia docGia) {
    return docGia.gioiTinh == 1;
}

bool isCSV(char const* fileName) {
    return fileName[strlen(fileName) - 1] == 'v' &&
        fileName[strlen(fileName) - 2] == 's' &&
        fileName[strlen(fileName) - 3] == 'c';
}

bool validateDocGiaInfo(theDocGia newDocGia, danhSachDocGia* listDocGia) {
    return strlen(newDocGia.ho_Ten) <= NAME_MAX && strlen(newDocGia.ho_Ten) >= NAME_MIN &&
        strlen(newDocGia.so_CMND) <= CMND_MAX && strlen(newDocGia.so_CMND) >= CMND_MIN &&
        strlen(newDocGia.email) <= EMAIL_MAX && strlen(newDocGia.email) >= EMAIL_MIN &&
        strlen(newDocGia.diaChi) <= ADDRESS_MAX && strlen(newDocGia.diaChi) >= ADDRESS_MIN &&
        searchForDocGiaByCMND(newDocGia.so_CMND, listDocGia) == NULL;
}

bool editTenDocGia(nodeDocGia*& docGia) {
    char newName[NAME_MAX];
    cin.ignore();
    cin.getline(newName, NAME_MAX);

    if (strlen(newName) >= NAME_MIN && strlen(newName) <= NAME_MAX) {
        if (confirmationBox()) {
            strcpy(docGia->thongTinDocGia.ho_Ten, newName);
            return true;
        }
    }

    return false;
}

bool editCMNDDocGia(nodeDocGia*& docGia, danhSachDocGia*& dsDocGia) {
    char CMND[CMND_MAX];
    cin.ignore();
    cin >> CMND;

    if (strlen(CMND) <= CMND_MAX && strlen(CMND) >= CMND_MIN &&
        searchForDocGiaByCMND(CMND, dsDocGia) == NULL) {
        if (confirmationBox()) {
            strcpy(docGia->thongTinDocGia.so_CMND, CMND);
            return true;
        }
    }

    return false;
}

bool editNgaySinhDocGia(nodeDocGia*& docGia) {
    char ngaySinh[BIRTH_DAY];
    cin.ignore();
    cin >> ngaySinh;

    if (confirmationBox()) {
        strcpy(docGia->thongTinDocGia.ngay_Sinh, ngaySinh);
        return true;
    }

    return false;
}

bool editEmailDocGia(nodeDocGia*& docGia) {
    char email[EMAIL_MAX];
    cin.ignore();
    cin >> email;

    if (strlen(email) <= EMAIL_MAX && strlen(email) >= EMAIL_MIN) {
        if (confirmationBox()) {
            strcpy(docGia->thongTinDocGia.email, email);
            return true;
        }
    }

    return false;
}

bool editDiaChiDocGia(nodeDocGia*& docGia) {
    char diaChi[ADDRESS_MAX];
    cin.ignore();
    cin.getline(diaChi, ADDRESS_MAX);

    if (strlen(diaChi) <= ADDRESS_MAX && strlen(diaChi) >= ADDRESS_MIN) {
        if (confirmationBox()) {
            strcpy(docGia->thongTinDocGia.diaChi, diaChi);
            return true;
        }
    }

    return false;
}

bool editGioiTinhDocGia(nodeDocGia*& docGia) {
    int gioiTinh;
    cin >> gioiTinh;

    if (gioiTinh == 0 || gioiTinh == 1) {
        if (confirmationBox()) {
            docGia->thongTinDocGia.gioiTinh = gioiTinh;
            return true;
        }
    }

    return false;
}

bool deleteDocGia(int ID, danhSachDocGia*& dsDocGia) {
    nodeDocGia* docGia = searchForDocGiaByID(ID, dsDocGia);

    if (docGia != NULL) {
        if (confirmationBox()) {
            if (docGia == dsDocGia->docGiaDau)
                deleteDocGiaDau(dsDocGia);
            else if (docGia == dsDocGia->docGiaCuoi)
                deleteDocGiaCuoi(dsDocGia);
            else
                deleteDocGiaGiua(docGia);

            --dsDocGia->totalDocGia;
            return true;
        }        
    }

    return false;
}

int themDocGiaTuCSV(FILE* csvFile, danhSachDocGia*& list) {
    if (csvFile == NULL) return 0;

    char buffer[1024];
    
    // So cot.
    int index = 0;

    // So dong.
    int lineNumber = 1;

    // So Doc gia da them.
    int added = 0;
    
    while (fgets(buffer, 1024, csvFile)) {
        theDocGia newDocGia;
        // Doc 1 dong.
        char* cell = strtok(buffer, ",");
        while (cell) {
            //
            // Van de dat ra o day la tao mot Doc gia moi truoc,
            // sau do moi validate du lieu.
            //
            if (index == 0) strcpy(newDocGia.ho_Ten, cell);
            if (index == 1) strcpy(newDocGia.so_CMND, cell);
            if (index == 2) strcpy(newDocGia.ngay_Sinh, cell);
            if (index == 3) newDocGia.gioiTinh = (strcmp(cell, "1") == 0) ? 1 : 0;
            if (index == 4) strcpy(newDocGia.email, cell);
            if (index == 5) {
                // Loai bo ky tu xuong dong.
                if (cell[strlen(cell) - 1] == '\n') cell[strlen(cell) - 1] = '\0';
                strcpy(newDocGia.diaChi, cell);
            }
            // Tang so cot len.
            ++index;

            cell = strtok(NULL, ",");

            if (index == 6) {
                if (validateDocGiaInfo(newDocGia, list)) {
                    time_t now = time(NULL);

                    // Chen ma doc gia va ngay lap the.
                    newDocGia.maDocGia = getMaxID(list) + 1;
                    newDocGia.ngayLapThe = now;

                    // Ngay het han la 2 nam ke tu ngay lap the.
                    // Convert now thanh time struct.
                    tm* timeStruct = gmtime(&now);

                    // Them 2 nam
                    timeStruct->tm_year += 2;

                    // Convert lai ve time_t
                    now = mktime(timeStruct);

                    // Gan cho newDocGia.
                    newDocGia.ngayHetHan = now;

                    // Tao node doc gia moi.
                    nodeDocGia* newNodeDocGia = createDocGiaNode(newDocGia);

                    //
                    // O day ta khong can confirm box,
                    // vi khi user nhap vao file .csv la user da thuc su muon thuc hien hanh dong.
                    // Ngoai ra, neu co sai sot thi van co the chinh sua tu phia chuyen vien va xoa tu phia quan ly,
                    // neu trung thi da co bao loi.
                    //

                    if (list->docGiaCuoi == NULL) {
                        // List chua co ai.
                        list->docGiaCuoi = newNodeDocGia;
                        list->docGiaDau = newNodeDocGia;
                    }
                    else {
                        // Chen node doc gia vao cuoi list.
                        list->docGiaCuoi->docGiaTiepTheo = newNodeDocGia;
                        newNodeDocGia->docGiaPhiaTruoc = list->docGiaCuoi;
                        list->docGiaCuoi = newNodeDocGia;
                    }

                    cout << "Da them doc gia " << newNodeDocGia->thongTinDocGia.ho_Ten << endl;
                    ++added;
                    ++list->totalDocGia;
                }
                else {
                    cout << "Da co loi xay ra o dong so " << lineNumber << endl;
                    cout << "Nguyen nhan co the vao cac loi sau:" << endl;
                    cout << "- CMND da duoc su dung cho mot doc gia khac." << endl;
                    cout << "- Do dai cac thong tin khong phu hop." << endl;
                    cout << "- Loi nhap lieu tu file .csv" << endl;
                    cout << "=====" << endl;
                }

                index = 0;
                ++lineNumber;
            }
        }
    }

    return added;
}

int getMaxID(danhSachDocGia* dsDocGia) {
    int maxID = 0;
    nodeDocGia* docGia = dsDocGia->docGiaDau;
    while (docGia != NULL) {
        maxID = max(maxID, docGia->thongTinDocGia.maDocGia);
        docGia = docGia->docGiaTiepTheo;
    }
    return maxID;
}

nodeDocGia* searchForDocGiaByCMND(const char* CMND, danhSachDocGia* list) {
    nodeDocGia* thisNode = list->docGiaDau;
    while (thisNode != NULL) {
        if (strcmp(thisNode->thongTinDocGia.so_CMND, CMND) == 0)
            return thisNode;
        thisNode = thisNode->docGiaTiepTheo;
    }

    return NULL;
}

nodeDocGia* searchForDocGiaByID(int ID, danhSachDocGia* list) {
    nodeDocGia* thisNode = list->docGiaDau;
    while (thisNode != NULL) {
        if (thisNode->thongTinDocGia.maDocGia == ID) 
            return thisNode;
        thisNode = thisNode->docGiaTiepTheo;
    }

    return NULL;
}

void searchForDocGiaByHoTen(const char* HoTen, danhSachDocGia* list) {
    nodeDocGia* thisNode = list->docGiaDau;
    bool foundDocGia = false;
    while (thisNode != NULL) {
        if (_stricmp(thisNode->thongTinDocGia.ho_Ten, HoTen) == 0) {
            inDocGia(thisNode->thongTinDocGia);
            foundDocGia = true;

            // Khong break vi co the co nhieu doc gia trung ten.
            // chi co flag danh dau xem co tim thay hay khong.
        }
        thisNode = thisNode->docGiaTiepTheo;
    }

    if (!foundDocGia) cout << "Khong tim thay doc gia co ten " << HoTen << endl;
}

void xemDanhSachDocGia(nodeDocGia* docGia) {
    if (docGia != NULL) {
        theDocGia thongTin = docGia->thongTinDocGia;
        inDocGia(thongTin);

        if (docGia->docGiaTiepTheo != NULL)
            xemDanhSachDocGia(docGia->docGiaTiepTheo);
    }
    else cout << "Hien tai khong co doc gia nao trong danh sach." << endl;
}

void thongKeTheoGioiTinh(danhSachDocGia* dsDocGia) {
    nodeDocGia* thisNode = dsDocGia->docGiaDau;
    int docGiaNam = 0;

    while (thisNode != NULL) {
        if (isNam(thisNode->thongTinDocGia)) ++docGiaNam;
        thisNode = thisNode->docGiaTiepTheo;
    }

    cout << "Thong ke theo gioi tinh:" << endl;
    cout << "Co tong cong " << dsDocGia->totalDocGia << " doc gia, trong do: " << endl;
    cout << docGiaNam << " nguoi la NAM." << endl;
    cout << dsDocGia->totalDocGia - docGiaNam << " nguoi la NU." << endl;
}

void inDocGia(theDocGia thongTin) {
    printf("ID: %d\n", thongTin.maDocGia);
    printf("Ho ten: %s\n", thongTin.ho_Ten);
    printf("Email: %s\n", thongTin.email);
    printf("Gioi tinh: %s\n", (isNam(thongTin)) ? "NAM" : "NU");
    printf("CMND: %s\n", thongTin.so_CMND);
    printf("Ngay sinh: %s\n", thongTin.ngay_Sinh);
    printf("Dia chi: %s\n", thongTin.diaChi);
    printf("Ngay lap the: %s\n", ctime(&thongTin.ngayLapThe));
    printf("Ngay het han: %s\n", ctime(&thongTin.ngayHetHan));
    printf("=====\n");
}

void deleteDocGiaDau(danhSachDocGia*& list) {
    nodeDocGia* headNode = list->docGiaDau;

    if (headNode->docGiaTiepTheo != NULL) {
        headNode->docGiaTiepTheo->docGiaPhiaTruoc = NULL;
        list->docGiaDau = headNode->docGiaTiepTheo;
    } else list->docGiaDau = NULL;
        

    free(headNode);
}

void deleteDocGiaCuoi(danhSachDocGia*& list) {
    nodeDocGia* tailNode = list->docGiaCuoi;

    tailNode->docGiaPhiaTruoc->docGiaTiepTheo = NULL;
    list->docGiaCuoi = tailNode->docGiaPhiaTruoc;

    free(tailNode);
}

void deleteDocGiaGiua(nodeDocGia*& node) {
    node->docGiaPhiaTruoc->docGiaTiepTheo = node->docGiaTiepTheo;
    node->docGiaTiepTheo->docGiaPhiaTruoc = node->docGiaPhiaTruoc;
    
    free(node);
}

void freeDanhSachDocGia(danhSachDocGia*& list) {
    while (list->docGiaDau != NULL)
        deleteDocGiaDau(list);
    
    free(list);
}

void writeDocGiaBackToFile(danhSachDocGia* dsDocGia) {
    FILE* f = fopen(DOCGIA_FILE, "wb+");

    // Ghi tong so doc gia.
    fwrite(&dsDocGia->totalDocGia, sizeof(int), 1, f);

    // Ghi tung doc gia.
    nodeDocGia* docGia = dsDocGia->docGiaDau;
    while (docGia != NULL) {
        fwrite(&docGia->thongTinDocGia, sizeof(theDocGia), 1, f);
        docGia = docGia->docGiaTiepTheo;
    }
    fclose(f);
}
