#pragma once

#include"include.h"

#define BOOKLIST_FILE "bookList.dat"

#define ISBN_MAX 15
#define BOOK_NAME_MAX 100
#define BOOK_PUBLISHED_MAX 5
#define BOOK_PUBLISHER_MAX 50
#define BOOK_TYPE_MAX 50

struct Book {
    char ISBN[ISBN_MAX];
    char book_Name[BOOK_NAME_MAX];
    char book_Author[NAME_MAX];
    char book_published_year[BOOK_PUBLISHED_MAX];
    char book_publisher[BOOK_PUBLISHER_MAX];
    char book_type[BOOK_TYPE_MAX];
    int price;
    int countTotal;
    int countBorrowed;
};

struct bookNode {
    Book bookInfo;
    bookNode* nextBook;
    bookNode* prevBook;
};

struct bookList {
    bookNode* firstBook;
    bookNode* lastBook;
    int bookCount;
};
 
bookList* createBookList();
bookNode* createBookNode(Book);
bookList* getDanhSachSachList();
bookNode* searchBookByISBN(const char*, bookList*);
bool validateBookInfo(Book);
bool deleteBook(const char*, bookList*&);
int addBookFromCSV(FILE*, bookList*&);
int bookLeft(Book);
void searchBookByName(const char*, bookList*);
void inMotQuyenSach(Book);
void inBookList(bookNode*);
void deleteSachDauList(bookList*&);
void deleteSachCuoiList(bookList*&);
void deleteSachGiuaList(bookNode*&);
void freeBookList(bookList*&);
void writeBookBackToFile(bookList*);
void thongKeSachTheoTheLoai(bookList*);
bool editBookName(bookNode*&);
bool editAuthorName(bookNode*&);
bool editPublisherName(bookNode*&);
bool editPublishedYear(bookNode*&);
bool editBookType(bookNode*&);
bool editBookPrice(bookNode*&);