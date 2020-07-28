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

        //fread(&newBookTicket, sizeof(borrowBookTicket), 1, f);

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

hashMap* validateMuonSach(borrowBookTicket ticket, danhSachDocGia* dsDocGia, bookList* dsSach) {
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
    hashMap* dsSachDaDuocDem = createHashMap();
    for (int i = 0; i < ticket.totalMuon; ++i) {
        hashNode* sachTrongHashMap = findInHashMap(dsSachDaDuocDem, ticket.listISBN[i]);
        if (sachTrongHashMap != NULL) ++sachTrongHashMap->count;
        else pushToHashMap(dsSachDaDuocDem, ticket.listISBN[i]);
    }

    // Kiem tra xem co loi trong ISBN hay khong.
    bool hasErrorInBooks = false;
    hashNode* sachTrongHashMap = dsSachDaDuocDem->firstNode;
    while (sachTrongHashMap != NULL) {
        bookNode* thongTinSach = searchBookByISBN(sachTrongHashMap->hash, dsSach);
        if (thongTinSach == NULL || 
            bookLeft(thongTinSach->bookInfo) == 0 ||
            bookLeft(thongTinSach->bookInfo) - sachTrongHashMap->count < 0) {
            hasErrorInBooks = true;
            break;
        }
        sachTrongHashMap = sachTrongHashMap->nextNode;
    }

    //releaseHashMap(dsSachDaDuocDem);

    if (hasErrorInBooks) {
        cout << "Mot trong so cac quyen sach khong ton tai / khong du so luong cho muon." << endl;
        return NULL;
    }

    return dsSachDaDuocDem;
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

    hashMap* dsSachDaDem = validateMuonSach(newBorrowTicket, dsDocGia, dsSach);

    if (dsSachDaDem != NULL) {
        //
        // Neu da validate thanh cong, tien hanh chen thoi gian.
        //
        time_t currentTime = time(NULL);
        newBorrowTicket.borrowDate = currentTime;
        newBorrowTicket.actualReturnDate = currentTime;

        // Doi now sang struct.
        tm* nowInStruct = gmtime(&currentTime);

        // Cong them so ngay muon.
        nowInStruct->tm_yday += soNgay;

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

        return true;
    }

    return false;
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

void freeBookTicketList(borrowBookTicketList*& bookTicketList) {
    while (bookTicketList->firstTicket != NULL) deleteBookTicketListFirstNode(bookTicketList);
    free(bookTicketList);
}