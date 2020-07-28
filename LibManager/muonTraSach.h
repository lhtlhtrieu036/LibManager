#pragma once
#include"include.h"

// File luu danh sach sach muon.
#define BORROW_TICKET_FILE "borrow.dat"

// So sach duoc muon toi da.
#define MAX_BORROW 5

struct borrowBookTicket {
    int maDocGia;
    int totalMuon;
    char* listISBN[MAX_BORROW];
    time_t borrowDate;
    time_t returnDate;
    time_t actualReturnDate;
};

struct borrowBookTicketNode {
    borrowBookTicket bookTicketData;
    borrowBookTicketNode* nextTicketNode;
    borrowBookTicketNode* prevTicketNode;
};

struct borrowBookTicketList {
    int totalTickets;
    borrowBookTicketNode* firstTicket;
    borrowBookTicketNode* lastTicket;
};

// Ham tao danh sach phieu muon sach.
borrowBookTicketList* createTicketList();

// Ham tao node phieu muon sach.
borrowBookTicketNode* createTicketNode(borrowBookTicket);

// Ham load phieu muon sach tu file vao list.
borrowBookTicketList* getDanhSachPhieuMuonSach();

bool validateMuonSach(borrowBookTicket);

// Ham lap phieu muon sach.
bool lapPhieuMuonSach(danhSachDocGia*, bookList*);

// Ham viet phieu muon sach tu list vao file.
void writeBorrowTicketToFile(borrowBookTicketList*);

// Ham xoa node dau tien cua list phieu.
void deleteBookTicketListFirstNode(borrowBookTicketList*&);

// Ham xoa node cuoi cua list phieu.
void deleteBookTicketListLastNode(borrowBookTicketList*&);

// Ham xoa node giua cua list phieu.
void deleteBookTicketMidNode(borrowBookTicketNode*&);

// Ham giai phong list phieu.
void freeBookTicketList(borrowBookTicketList*&);
