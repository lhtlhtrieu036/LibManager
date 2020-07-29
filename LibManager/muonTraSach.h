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
    bool returned;
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

// Ham validate thong tin muon sach.
hashMap* validateMuonSach(borrowBookTicket, borrowBookTicketList*, danhSachDocGia*, bookList*);

// Ham kiem tra phieu da tra hay chua.
bool phieuChuaTra(borrowBookTicket);

// Ham lap phieu muon sach.
bool lapPhieuMuonSach(borrowBookTicketList*&, danhSachDocGia*, bookList*&);

// Ham lap phieu tra sach.
bool lapPhieuTraSach(borrowBookTicketList*&, danhSachDocGia*, bookList*&);

//
// Ham tim phieu muon sach cua mot nguoi dung.
// Vi moi nguoi dung chi duoc muon 1 lan va phai tra sach truoc khi muon tiep,
// nen ham nay chi tra ve 1 ticketNode duy nhat.
//
borrowBookTicketNode* findBorrowBookTicket(borrowBookTicketList*, int);

// Ham tra ve mot hashmap la ISBN va so luong muon cua ISBN do.
hashMap* taoDanhSachDemISBN(borrowBookTicket);

// Ham in thong tin phieu muon sach.
void printBorrowTicket(borrowBookTicket);

// Ham viet phieu muon sach tu list vao file.
void writeBorrowTicketToFile(borrowBookTicketList*);

// Ham xoa node dau tien cua list phieu.
void deleteBookTicketListFirstNode(borrowBookTicketList*&);

// Ham xoa node cuoi cua list phieu.
void deleteBookTicketListLastNode(borrowBookTicketList*&);

// Ham xoa node giua cua list phieu.
void deleteBookTicketMidNode(borrowBookTicketNode*&);

// Ham xoa mot node bat ky cua list phieu.
void deleteBookTicketNode(borrowBookTicketList*&, borrowBookTicketNode*&);

// Ham giai phong list phieu.
void freeBookTicketList(borrowBookTicketList*&);

// Ham dem so luong quyen sach da cho muon.
int thongKeSachChoMuon(bookList*);

// Ham dem so luong doc gia tre han.
int thongKeDocGiaTreHan(borrowBookTicketList*);
