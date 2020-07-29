#include"include.h"

borrowBookTicketList* createTicketList() {
    borrowBookTicketList* newTicketList = (borrowBookTicketList*)malloc(sizeof(borrowBookTicketList));
    newTicketList->totalTickets = 0;
    newTicketList->firstTicket = NULL;
    newTicketList->lastTicket = NULL;
    return newTicketList;
}

borrowBookTicketNode* createTicketNode(borrowBookTicket ticketData) {
    borrowBookTicketNode* newTicketNode = (borrowBookTicketNode*)malloc(sizeof(borrowBookTicketNode));
    newTicketNode->nextTicketNode = NULL;
    newTicketNode->prevTicketNode = NULL;
    newTicketNode->bookTicketData = ticketData;
    return newTicketNode;
}

borrowBookTicketNode* findBookTicketNodeByDocGia(borrowBookTicketList* ticketList, int idDocGia) {
    borrowBookTicketNode* thisTicket = ticketList->firstTicket;
    while (thisTicket != NULL) {
        if (thisTicket->bookTicketData.maDocGia == idDocGia)
            return thisTicket;
        thisTicket = thisTicket->nextTicketNode;
    }
    return NULL;
}

borrowBookTicketList* getDanhSachPhieuMuonSach() {
    FILE* f = fopen(BORROW_TICKET_FILE, "rb+");
    if (f == NULL) return NULL;

    borrowBookTicketList* newTicketList = createTicketList();

    // Doc tong so phieu.
    fseek(f, 0, SEEK_SET);
    fread(&newTicketList->totalTickets, sizeof(newTicketList->totalTickets), 1, f);

    // Doc tung phieu vao node.
    for (int i = 1; i <= newTicketList->totalTickets; ++i) {
        borrowBookTicket newBookTicket;
        fread(&newBookTicket.maDocGia, sizeof(newBookTicket.maDocGia), 1, f);
        fread(&newBookTicket.totalMuon, sizeof(newBookTicket.totalMuon), 1, f);
        
        for (int i = 0; i < newBookTicket.totalMuon; ++i) {
            newBookTicket.listISBN[i] = (char*)malloc(ISBN_MAX);
            fread(newBookTicket.listISBN[i], ISBN_MAX, 1, f);
        }

        fread(&newBookTicket.borrowDate, sizeof(newBookTicket.borrowDate), 1, f);
        fread(&newBookTicket.returnDate, sizeof(newBookTicket.returnDate), 1, f);
        fread(&newBookTicket.actualReturnDate, sizeof(newBookTicket.actualReturnDate), 1, f);
        fread(&newBookTicket.returned, sizeof(newBookTicket.returned), 1, f);

        borrowBookTicketNode* newTicketNode = createTicketNode(newBookTicket);

        if (newTicketList->firstTicket == NULL) {
            newTicketList->firstTicket = newTicketNode;
            newTicketList->lastTicket = newTicketNode;
        } 
        else {
            newTicketList->lastTicket->nextTicketNode = newTicketNode;
            newTicketNode->prevTicketNode = newTicketList->lastTicket;
            newTicketList->lastTicket = newTicketNode;
        }
    }

    fclose(f);

    return newTicketList;
}

hashMap* validateMuonSach(borrowBookTicket ticket, borrowBookTicketList* ticketList, danhSachDocGia* dsDocGia, bookList* dsSach) {
    nodeDocGia* docGia = searchForDocGiaByID(ticket.maDocGia, dsDocGia);

    if (docGia == NULL) {
        cout << "Doc gia khong ton tai." << endl;
        return NULL;
    }
    
    if (!theConHan(docGia->thongTinDocGia)) {
        cout << "The doc gia da het han." << endl;
        return NULL;
    }

    // Chuyen danh sach ISBN thanh hashmap de dem moi ISBN rieng biet 1 lan.
    hashMap* dsSachDaDuocDem = taoDanhSachDemISBN(ticket);

    // Kiem tra xem co loi trong ISBN hay khong.
    bool hasErrorInBooks = false;
    hashNode* sachTrongHashMap = dsSachDaDuocDem->firstNode;
    while (sachTrongHashMap != NULL) {
        bookNode* thongTinSach = searchBookByISBN(sachTrongHashMap->hash, dsSach);
        borrowBookTicketNode* borrowedByDocGia = findBookTicketNodeByDocGia(ticketList, ticket.maDocGia);
        if (thongTinSach == NULL || 
            borrowedByDocGia != NULL ||
            bookLeft(thongTinSach->bookInfo) == 0 ||
            bookLeft(thongTinSach->bookInfo) < sachTrongHashMap->count) {
            hasErrorInBooks = true;
            break;
        }
        
        sachTrongHashMap = sachTrongHashMap->nextNode;
    }

    if (hasErrorInBooks) {
        cout << "Mot trong so cac quyen sach khong ton tai / khong du so luong cho muon." << endl;
        return NULL;
    }

    return dsSachDaDuocDem;
}

bool phieuChuaTra(borrowBookTicket thisBookTicket) {
    return !thisBookTicket.returned;
}

bool lapPhieuMuonSach(borrowBookTicketList*& bookTicketList, danhSachDocGia* dsDocGia, bookList*& dsSach) {
    borrowBookTicket newBorrowTicket;

    // Nhap doc gia.
    cout << "Nhap ID Doc gia (Ma Doc gia): "; 
    
    if (!(cin >> newBorrowTicket.maDocGia)) {
        cin.clear();
        cin.ignore();
        cout << "ID khong hop le." << endl;
        return false;
    }

    // Nhap so luong sach
    cout << "Nhap so luong sach can muon: " << endl;

    if (!(cin >> newBorrowTicket.totalMuon)) {
        cin.clear();
        cin.ignore();
        cout << "So sach muon khong hop le." << endl;
        return false;
    }

    // Validate luong sach.
    if (newBorrowTicket.totalMuon <= 0 || newBorrowTicket.totalMuon > MAX_BORROW) {
        cout << "So sach muon khong hop le." << endl;
        return false;
    }
    
    // Lay ISBN cua tung quyen sach muon.   
    for (int i = 0; i < newBorrowTicket.totalMuon; ++i) {
        cout << "Nhap ISBN quyen sach thu " << i + 1 << " can muon: " << endl;
        char tempISBN[ISBN_MAX]; cin >> tempISBN;
        newBorrowTicket.listISBN[i] = (char*)malloc(ISBN_MAX);
        strcpy(newBorrowTicket.listISBN[i], tempISBN);
    }

    // So ngay muon sach.
    cout << "Nhap so ngay can muon: " << endl;
    int soNgay; cin >> soNgay;

    // Validate so ngay muon.
    if (soNgay <= 0 || soNgay > 7) {
        cout << "So ngay muon khong hop le." << endl;
        return false;
    }

    hashMap* dsSachDaDem = validateMuonSach(newBorrowTicket, bookTicketList, dsDocGia, dsSach);

    if (dsSachDaDem != NULL) {
        //
        // Neu da validate thanh cong, tien hanh chen thoi gian.
        // va trang thai da tra.
        //
        
        // Trang thai da tra.
        newBorrowTicket.returned = false;

        // Khoi tao thoi gian hien tai.
        time_t currentTime = time(NULL);
        newBorrowTicket.borrowDate = currentTime;
        newBorrowTicket.actualReturnDate = currentTime;

        // Doi now sang struct.
        tm* nowInStruct = gmtime(&currentTime);

        // Cong them so ngay muon.
        nowInStruct->tm_mday += soNgay;

        // Doi now nguoc lai thanh time_t
        time_t returnDate = mktime(nowInStruct);
        newBorrowTicket.returnDate = returnDate;

        // Viet so luong sach muon vao list Sach.
        hashNode* thisNode = dsSachDaDem->firstNode;
        while (thisNode != NULL) {
            // Cap nhat so luong sach cho muon.
            bookNode* thisBook = searchBookByISBN(thisNode->hash, dsSach);
            thisBook->bookInfo.countBorrowed += thisNode->count;

            thisNode = thisNode->nextNode;
        }
        
        borrowBookTicketNode* newBorrowNode = createTicketNode(newBorrowTicket);

        // Chen node vao duoi list.
        if (bookTicketList->firstTicket == NULL) {
            bookTicketList->firstTicket = newBorrowNode;
            bookTicketList->lastTicket = newBorrowNode;
        } else {
            bookTicketList->lastTicket->nextTicketNode = newBorrowNode;
            newBorrowNode->prevTicketNode = bookTicketList->lastTicket;
            bookTicketList->lastTicket = newBorrowNode;
        }
        
        // Tang so phieu trong list.
        ++bookTicketList->totalTickets;

        releaseHashMap(dsSachDaDem);

        printBorrowTicket(newBorrowNode->bookTicketData);

        return true;
    }

    return false;
}

bool lapPhieuTraSach(borrowBookTicketList*& bookTicketList, danhSachDocGia* dsDocGia, bookList*& dsSach) {
    cout << "Nhap ID doc gia: ";
    int docGiaID;

    if (!(cin >> docGiaID)) {
        cin.clear();
        cin.ignore();
        return false;
    }

    // Check xem doc gia co ton tai hay khong.
    nodeDocGia* docGia = searchForDocGiaByID(docGiaID, dsDocGia);

    if (docGia == NULL) {
        cout << "Doc gia khong ton tai." << endl;
        return false;
    }

    // Tim phieu muon hien co cua doc gia.
    borrowBookTicketNode* activeBorrow = findBookTicketNodeByDocGia(bookTicketList, docGia->thongTinDocGia.maDocGia);

    // Doc gia hien khong co phieu muon sach nao dang active.
    if (activeBorrow == NULL || !phieuChuaTra(activeBorrow->bookTicketData)) {
        cout << "Ban khong co phieu muon sach nao." << endl;
        return false;
    }

    // Lay thoi gian hien tai.
    time_t currentTime = time(NULL);

    cout << "Ban dang co 1 phieu muon sach chua tra:" << endl;
    printBorrowTicket(activeBorrow->bookTicketData);

    //
    // Den day doc gia dang co 1 phieu muon sach.
    // Van de dat ra la so sach doc gia tra co bang voi so sach doc gia muon hay khong.
    // De giai quyet dieu do, nhan vien phai nhap ISBN va so luong quyen de kiem tra.
    //

    // Load tat ca cac sach user da muon vao mot hashmap.
    hashMap* dsSachMuon = taoDanhSachDemISBN(activeBorrow->bookTicketData);

    // Tao mot hashmap moi de dem so sach tra.
    hashMap* dsSachTra = createHashMap();

    // Lay so luong tung node tra.
    hashNode* dsSachMuonNode = dsSachMuon->firstNode;
    while (dsSachMuonNode != NULL) {
        int soLuongTra = -1;
        do {
            cout << "ISBN: " << dsSachMuonNode->hash << endl;
            cout << "Nhap so luong quyen tra: "; cin >> soLuongTra;

            if (soLuongTra < 0 || soLuongTra > dsSachMuonNode->count)
                cout << "So luong quyen tra khong hop le, xin vui long nhap lai." << endl;
        } while (soLuongTra < 0 || soLuongTra > dsSachMuonNode->count);

        // Push so luong tra vao hash dsSachTra
        pushToHashMap(dsSachTra, dsSachMuonNode->hash);
        dsSachTra->lastNode->count = soLuongTra;

        dsSachMuonNode = dsSachMuonNode->nextNode;
    }

    // Tinh toan so luong sach them nguoc lai vao database
    hashNode* dsSachTraNode = dsSachTra->firstNode;
    dsSachMuonNode = dsSachMuon->firstNode;

    int lostCost = 0;

    while (dsSachTraNode != NULL) {
        bookNode* thisBookNode = searchBookByISBN(dsSachTraNode->hash, dsSach);

        // Truong hop sach da bi xoa khoi database, ta bo qua.
        if (thisBookNode != NULL) {
            if (dsSachTraNode->count < dsSachMuonNode->count) lostCost += thisBookNode->bookInfo.price * 2 * (dsSachMuonNode->count - dsSachTraNode->count);

            // Tong so sach muon -= so sach da ghi trong phieu muon.
            // ta khong quan tam so luong tra la bao nhieu.
            thisBookNode->bookInfo.countBorrowed -= dsSachMuonNode->count;

            // Tong so sach += so sach muon - so sach tra.
            // tuc la neu tra thieu thi tru trong tong so sach.
            thisBookNode->bookInfo.countTotal -= dsSachMuonNode->count - dsSachTraNode->count;
        }
        
        dsSachTraNode = dsSachTraNode->nextNode;
        dsSachMuonNode = dsSachMuonNode->nextNode;
    }

    // Cap nhat trang thai phieu.
    activeBorrow->bookTicketData.returned = true;
    activeBorrow->bookTicketData.actualReturnDate = currentTime;

    // Tinh tong so tien phat qua han.
    int outdateCost = 0;
    if (currentTime - activeBorrow->bookTicketData.returnDate > 0)
        outdateCost = ((double)(currentTime - activeBorrow->bookTicketData.returnDate) / 3600 * 24) * 5000;

    // In thong tin thu tien.
    system("cls");
    printBorrowTicket(activeBorrow->bookTicketData);
    cout << "Ngay tra: " << ctime(&currentTime) << endl;
    cout << "Tong tien qua han: " << outdateCost << endl;
    cout << "Tong tien phat mat sach: " << lostCost << endl;
    cout << "Tong tien can thu: " << outdateCost + lostCost << endl;

    releaseHashMap(dsSachMuon);
    releaseHashMap(dsSachTra);

    // Xoa node cho ranh.
    deleteBookTicketNode(bookTicketList, activeBorrow);

    return true;
}

borrowBookTicketNode* findBorrowBookTicket(borrowBookTicketList* borrowList, int docGiaID) {
    borrowBookTicketNode* borrowNode = borrowList->firstTicket;

    while (borrowNode != NULL) {
        if (borrowNode->bookTicketData.maDocGia == docGiaID &&
            phieuChuaTra(borrowNode->bookTicketData))
            return borrowNode;
        borrowNode = borrowNode->nextTicketNode;
    }

    return NULL;
}

hashMap* taoDanhSachDemISBN(borrowBookTicket borrowTicket) {
    hashMap* dsSachMuon = createHashMap();
    for (int i = 0; i < borrowTicket.totalMuon; ++i) {
        hashNode* sachTrongHashMap = findInHashMap(dsSachMuon, borrowTicket.listISBN[i]);

        if (sachTrongHashMap != NULL) ++sachTrongHashMap->count;
        else pushToHashMap(dsSachMuon, borrowTicket.listISBN[i]);
    }

    return dsSachMuon;
}

void printBorrowTicket(borrowBookTicket borrowTicket) {
    printf("======\n");
    printf("Thong tin phieu muon sach:\n");
    printf("Ma doc gia: %d\n", borrowTicket.maDocGia);
    printf("Tong so quyen sach da muon: %d\n", borrowTicket.totalMuon);
    printf("Danh sach sach da muon:\n");
    
    // Tao va load danh sach sach da muon.
    hashMap* dsSach = taoDanhSachDemISBN(borrowTicket);
    hashNode* thisNode = dsSach->firstNode;
    while (thisNode != NULL) {
        printf("ISBN: %s - So luong muon: %d\n", thisNode->hash, thisNode->count);
        thisNode = thisNode->nextNode;
    }

    releaseHashMap(dsSach);

    printf("Ngay muon: %s\n", ctime(&borrowTicket.borrowDate));
    printf("Ngay tra du kien: %s\n", ctime(&borrowTicket.returnDate));
    printf("Trang thai: %s tra\n", (phieuChuaTra(borrowTicket) ? "chua" : "da"));
    printf("======\n");
}

void writeBorrowTicketToFile(borrowBookTicketList* borrowTicketList) {
    FILE* f = fopen(BORROW_TICKET_FILE, "wb+");

    fwrite(&borrowTicketList->totalTickets, sizeof(borrowTicketList->totalTickets), 1, f);

    borrowBookTicketNode* bookTicketNode = borrowTicketList->firstTicket;
    while (bookTicketNode != NULL) {
        //
        // Doi voi list string, chung ta se khong ghi binh thuong ma phai ghi tung dong.
        //
        fwrite(&bookTicketNode->bookTicketData.maDocGia, sizeof(bookTicketNode->bookTicketData.maDocGia), 1, f);
        fwrite(&bookTicketNode->bookTicketData.totalMuon, sizeof(bookTicketNode->bookTicketData.totalMuon), 1, f);
        for (int i = 0; i < bookTicketNode->bookTicketData.totalMuon; ++i)
            fwrite(bookTicketNode->bookTicketData.listISBN[i], ISBN_MAX, 1, f);
        fwrite(&bookTicketNode->bookTicketData.borrowDate, sizeof(bookTicketNode->bookTicketData.borrowDate), 1, f);
        fwrite(&bookTicketNode->bookTicketData.returnDate, sizeof(bookTicketNode->bookTicketData.returnDate), 1, f);
        fwrite(&bookTicketNode->bookTicketData.actualReturnDate, sizeof(bookTicketNode->bookTicketData.actualReturnDate), 1, f);
        fwrite(&bookTicketNode->bookTicketData.returned, sizeof(bookTicketNode->bookTicketData.returned), 1, f);

        bookTicketNode = bookTicketNode->nextTicketNode;
    }

    fclose(f);
}

void deleteBookTicketListFirstNode(borrowBookTicketList*& bookTicketList) {
    borrowBookTicketNode* firstTicketNode = bookTicketList->firstTicket;
    if (firstTicketNode->nextTicketNode == NULL)
        bookTicketList->firstTicket = NULL;
    else bookTicketList->firstTicket = firstTicketNode->nextTicketNode;

    free(firstTicketNode);
}

void deleteBookTicketListLastNode(borrowBookTicketList*& bookTicketList) {
    borrowBookTicketNode* lastTicketNode = bookTicketList->lastTicket;
    if (lastTicketNode->prevTicketNode == NULL)
        bookTicketList->lastTicket = NULL;
    else bookTicketList->lastTicket = lastTicketNode->prevTicketNode;

    free(lastTicketNode);
}

void deleteBookTicketMidNode(borrowBookTicketNode*& bookTicketNode) {
    bookTicketNode->nextTicketNode->prevTicketNode = bookTicketNode->prevTicketNode;
    bookTicketNode->prevTicketNode->nextTicketNode = bookTicketNode->nextTicketNode;

    free(bookTicketNode);
}

void deleteBookTicketNode(borrowBookTicketList*& bookTicketList, borrowBookTicketNode*& bookTicketNode) {
    if (bookTicketNode == bookTicketList->firstTicket)
        deleteBookTicketListFirstNode(bookTicketList);
    else if (bookTicketNode == bookTicketList->lastTicket)
        deleteBookTicketListLastNode(bookTicketList);
    else deleteBookTicketMidNode(bookTicketNode);

    --bookTicketList->totalTickets;
}

void freeBookTicketList(borrowBookTicketList*& bookTicketList) {
    while (bookTicketList->firstTicket != NULL) deleteBookTicketListFirstNode(bookTicketList);
    free(bookTicketList);
}

int thongKeSachChoMuon(bookList* dsSach) {
    bookNode* thisNode = dsSach->firstBook;
    int totalSachChoMuon = 0;
    while (thisNode != NULL) {
        totalSachChoMuon += thisNode->bookInfo.countBorrowed;
        thisNode = thisNode->nextBook;
    }
    return totalSachChoMuon;
}

int thongKeDocGiaTreHan(borrowBookTicketList* borrowList) {
    int totalTreHan = 0;
    time_t currentTime = time(NULL);
    borrowBookTicketNode* borrowTicket = borrowList->firstTicket;

    while (borrowTicket != NULL) {
        if (currentTime - borrowTicket->bookTicketData.returnDate > 0)
            ++totalTreHan;
        borrowTicket = borrowTicket->nextTicketNode;
    }

    return totalTreHan;
}

