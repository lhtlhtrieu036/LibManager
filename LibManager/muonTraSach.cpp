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
        fread(&newBookTicket, sizeof(borrowBookTicket), 1, f);

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

bool validateMuonSach(borrowBookTicket ticket, danhSachDocGia* dsDocGia, bookList* dsSach) {
    nodeDocGia* docGia = searchForDocGiaByID(ticket.maDocGia, dsDocGia);
    if (docGia == NULL) {
        cout << "Doc gia khong ton tai." << endl;
        return false;
    }
    
    if (!theConHan(docGia->thongTinDocGia)) {
        cout << "The doc gia da het han." << endl;
        return false;
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
        if (thongTinSach == NULL || bookLeft(thongTinSach->bookInfo) == 0) {
            hasErrorInBooks = true;
            break;
        }
    }

    releaseHashMap(dsSachDaDuocDem);

    if (hasErrorInBooks) {
        cout << "Mot trong so cac quyen sach khong ton tai / khong du so luong cho muon." << endl;
        return false;
    }

    return true;
}

bool lapPhieuMuonSach(borrowBookTicketList*& bookTicketList, danhSachDocGia* dsDocGia, bookList*& dsSach) {
    borrowBookTicket newBorrowTicket;
    cout << "Nhap ID (Ma Doc gia): "; 
    
    if (!(cin >> newBorrowTicket.maDocGia)) {
        cin.clear();
        cin.ignore();
        cout << "ID khong hop le." << endl;
        return false;
    }

    cout << "Nhap so luong sach can muon: " << endl;

    if (!(cin >> newBorrowTicket.totalMuon)) {
        cin.clear();
        cin.ignore();
        cout << "So sach muon khong hop le." << endl;
        return false;
    }

    if (newBorrowTicket.totalMuon <= 0 || newBorrowTicket.totalMuon > MAX_BORROW) {
        cout << "So sach muon khong hop le." << endl;
        return false;
    }
    
    for (int i = 0; i < newBorrowTicket.totalMuon; ++i) {
        cout << "Nhap ISBN quyen sach thu " << i + 1 << " can muon: " << endl;
        char tempISBN[ISBN_MAX]; cin >> tempISBN;
        newBorrowTicket.listISBN[i] = _strdup(tempISBN);
    }

    if (validateMuonSach(newBorrowTicket, dsDocGia, dsSach)) {
        
    }

    return false;
}

void writeBorrowTicketToFile(borrowBookTicketList* borrowTicketList) {
    FILE* f = fopen(BORROW_TICKET_FILE, "wb+");

    fwrite(&borrowTicketList->totalTickets, sizeof(borrowTicketList->totalTickets), 1, f);

    borrowBookTicketNode* bookTicketNode = borrowTicketList->firstTicket;
    while (bookTicketNode != NULL) {
        fwrite(&bookTicketNode->bookTicketData, sizeof(bookTicketNode->bookTicketData), 1, f);
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