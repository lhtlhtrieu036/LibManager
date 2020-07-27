#include "include.h"

bookList* createBookList() {
    bookList* newBookList = (bookList*)malloc(sizeof(bookList));
    newBookList->firstBook = NULL;
    newBookList->lastBook = NULL;
    newBookList->bookCount = 0;
    return newBookList;
}

bookNode* createBookNode(Book newBook) {
    bookNode* newBookNode = (bookNode*)malloc(sizeof(bookNode));
    newBookNode->bookInfo = newBook;
    newBookNode->nextBook = NULL;
    newBookNode->prevBook = NULL;
    return newBookNode;
}
bookList* getDanhSachSachList() {
    FILE* f = fopen(BOOKLIST_FILE, "rb+");
    if (f == NULL) return NULL;

    fseek(f, 0, SEEK_SET);
    bookList* newBookList = createBookList();

    // Doc tong so sach.
    fread(&newBookList->bookCount, sizeof(int), 1, f);

    // Doc tung node.
    for (int i = 1; i <= newBookList->bookCount; ++i) {
        Book newBook;
        fread(&newBook, sizeof(Book), 1, f);

        bookNode* newBookNode = createBookNode(newBook);

        if (newBookList->firstBook == NULL) {
            newBookList->firstBook = newBookNode;
            newBookList->lastBook = newBookNode;
        } else {
            newBookList->lastBook->nextBook = newBookNode;
            newBookNode->prevBook = newBookList->lastBook;
            newBookList->lastBook = newBookNode;
        }
    }
    fclose(f);

    return newBookList;
}
bookNode* searchBookByISBN(const char* ISBN, bookList* dsSach) {
    bookNode* thisBookNode = dsSach->firstBook;
    while (thisBookNode != NULL) {
        if (strcmp(thisBookNode->bookInfo.ISBN, ISBN) == 0)
            return thisBookNode;
        thisBookNode = thisBookNode->nextBook;
    }
    return NULL;
}

void searchBookByName(const char* bookName, bookList* dsSach) {
    bookNode* thisBookNode = dsSach->firstBook;
    bool foundBook = false;

    while (thisBookNode != NULL) {
        if (_stricmp(bookName, thisBookNode->bookInfo.book_Name) == 0) {
            inMotQuyenSach(thisBookNode->bookInfo);
            foundBook = true;
        }
        thisBookNode = thisBookNode->nextBook;
    }

    if (!foundBook) cout << "Khong tim thay sach co ten " << bookName << endl;
}

bool validateBookInfo(Book newBook) {
    return strlen(newBook.ISBN) <= ISBN_MAX &&
        strlen(newBook.book_Name) <= BOOK_NAME_MAX &&
        strlen(newBook.book_Author) <= NAME_MAX &&
        strlen(newBook.book_published_year) <= BOOK_PUBLISHED_MAX &&
        strlen(newBook.book_publisher) <= BOOK_PUBLISHER_MAX &&
        newBook.countTotal >= 0 &&
        newBook.price >= 0;
}

int addBookFromCSV(FILE* csvFile, bookList*& dsSach) {
    if (csvFile == NULL) return 0;

    char buffer[1024];

    // So thu tu cot.
    int index = 0;

    // So thu tu dong.
    int lineNumber = 1;

    // So dong da them.
    int added = 0;

    while (fgets(buffer, 1024, csvFile)) {
        Book newBook;
        char* cell = strtok(buffer, ",");

        while (cell) {
            if (index == 0) strcpy(newBook.ISBN, cell);
            if (index == 1) strcpy(newBook.book_Name, cell);
            if (index == 2) strcpy(newBook.book_Author, cell);
            if (index == 3) strcpy(newBook.book_published_year, cell);
            if (index == 4) strcpy(newBook.book_publisher, cell);
            if (index == 5) strcpy(newBook.book_type, cell);
            if (index == 6) newBook.price = atoi(cell);
            if (index == 7) {
                if (cell[strlen(cell) - 1] == '\n') cell[strlen(cell) - 1] = '\0';
                newBook.countTotal = atoi(cell);
            }
            ++index;

            cell = strtok(NULL, ",");

            if (index == 8) {
                if (validateBookInfo(newBook)) {
                    // Neu sach da ton tai, cong don sach.
                    // (Sach ton tai bang ISBN)
                    bookNode* bookNodeExisted = searchBookByISBN(newBook.ISBN, dsSach);
                    if (bookNodeExisted != NULL) bookNodeExisted->bookInfo.countTotal += newBook.countTotal;
                    else {
                        newBook.countBorrowed = 0;
                        bookNode* newBookNode = createBookNode(newBook);
                        
                        // Chen book node vao cuoi list.
                        if (dsSach->firstBook == NULL) {
                            dsSach->firstBook = newBookNode;
                            dsSach->lastBook = newBookNode;
                        } else {
                            dsSach->lastBook->nextBook = newBookNode;
                            newBookNode->prevBook = dsSach->lastBook;
                            dsSach->lastBook = newBookNode;
                        }

                        // Den day moi dem so luong quyen sach.
                        ++dsSach->bookCount;
                    }

                    // Dem tong so sach da them.
                    ++added;
                }
                else {
                    cout << "Da co loi xay ra o dong so " << lineNumber << endl;
                    cout << "Nguyen nhan co the vao cac loi sau:" << endl;
                    cout << "- Do dai cac thong tin khong phu hop." << endl;
                    cout << "- Loi nhap lieu tu file .csv" << endl;
                }

                // Reset so cot ve 0.
                index = 0;

                // Dem so dong.
                ++lineNumber;
            }
        }
    }

    return added;
}

void inMotQuyenSach(Book thisBook) {
    cout << "ISBN: " << thisBook.ISBN << endl;
    cout << "Ten sach: " << thisBook.book_Name << endl;
    cout << "Ten tac gia: " << thisBook.book_Author << endl;
    cout << "Nam xuat ban: " << thisBook.book_published_year << endl;
    cout << "Nha xuat ban: " << thisBook.book_publisher << endl;
    cout << "The loai: " << thisBook.book_type << endl;
    cout << "Gia sach: " << thisBook.price << endl;
    cout << "Tong so quyen sach: " << thisBook.countTotal << endl;
    cout << "Tong so quyen da cho muon: " << thisBook.countBorrowed << endl;
    cout << "Tong so quyen hien co: " << thisBook.countTotal - thisBook.countBorrowed << endl;
    cout << "=====" << endl;
}

void inBookList(bookNode* thisBook) {
    if (thisBook != NULL) {
        inMotQuyenSach(thisBook->bookInfo);
        inBookList(thisBook->nextBook);
    }
}

bookNode* isBookExist(char* ISBN, bookList list) {
    bookNode* thisBook = list.firstBook;

    while (thisBook != NULL) {
        if (strcmp(ISBN, thisBook->bookInfo.ISBN) == 0)
            return thisBook;
        thisBook = thisBook->nextBook;
    }

    return NULL;
}

bool deleteBook(const char* ISBN, bookList*& dsSach) {
    bookNode* thisBook = searchBookByISBN(ISBN, dsSach);
    if (thisBook != NULL) {
        if (confirmationBox()) {
            if (thisBook == dsSach->firstBook)
                deleteSachDauList(dsSach);
            else if (thisBook == dsSach->lastBook)
                deleteSachCuoiList(dsSach);
            else
                deleteSachGiuaList(thisBook);

            --dsSach->bookCount;
            return true;
        }
    }

    return false;
}

void deleteSachDauList(bookList*& dsSach) {
    bookNode* thisBook = dsSach->firstBook;

    if (thisBook->nextBook == NULL)
        dsSach->firstBook = NULL;
    else {
        dsSach->firstBook = thisBook->nextBook;
        thisBook->nextBook->prevBook = NULL;
    }

    free(thisBook);
}

void deleteSachCuoiList(bookList*& dsSach) {
    bookNode* thisBook = dsSach->lastBook;
    if (thisBook->prevBook == NULL)
        dsSach->lastBook = NULL;
    else {
        dsSach->lastBook = thisBook->prevBook;
        thisBook->prevBook->nextBook = NULL;
    }

    free(thisBook);
}

void deleteSachGiuaList(bookNode*& thisBook) {
    thisBook->nextBook->prevBook = thisBook->prevBook;
    thisBook->prevBook->nextBook = thisBook->nextBook;

    free(thisBook);
}

void freeBookList(bookList*& dsSach) {
    while (dsSach->firstBook != NULL)
        deleteSachDauList(dsSach);
    free(dsSach);
}

/*
void enterBookInfo(bookList& a)
{
    Book newBook;
    cout << " NHAP CAC THONG TIN SAU CUA SACH: " << endl;
    char tempISBN[ISBN_MAX];
    cout << " ISBN: "; cin >> tempISBN;

    //
    // Sua lai sau.
    //

    //if (isBookExist(tempISBN, a) != NULL) {
    //	// Them so luong
    //}
    //else {
    //	//
    //}

    for (bookNode* p = a.firstBook; p != NULL; p = p->nextBook)
    {
        if (strcmp(tempISBN, p->bookInfo.ISBN) == 0)
        {
            cout << " Nhap so luong sach muon nhap vao thu vien: ";
            int tempCount; cin >> tempCount;
            p->bookInfo.count = p->bookInfo.count + tempCount; return;
        }
    };
    strcpy(newBook.ISBN, tempISBN);
    cout << " Ten sach: "; cin >> newBook.book_Name;
    cout << " Ten tac gia: "; cin >> newBook.book_Author;
    cout << " Nam xuat ban: "; cin >> newBook.book_published_year;
    cout << " Nha xuat ban: "; cin >> newBook.book_publisher;
    cout << " The loai: "; cin >> newBook.book_type;
    cout << " Gia sach: "; cin >> newBook.price;
    cout << " So luong sach nhap vao thu vien: "; cin >> newBook.count;
    cout << " --------------------------------------";
    bookNode* p;
    p = createBookNode(newBook);
    if (a.firstBook == NULL)
    {
        a.firstBook = p;
        a.lastBook = p;
        a.bookCount++;
    }
    else
    {
        p->nextBook = a.firstBook;
        p->nextBook->prevBook = p;
        a.firstBook = p;
        a.bookCount++;
    };
};

void add_book_to_list(bookList& a, bookNode* newbook)
{
    if (a.firstBook == NULL)
    {
        a.firstBook = newbook;
        a.lastBook = newbook;
        //a.bookCount++;
    }
    else
    {
        newbook->nextBook = a.firstBook;
        newbook->nextBook->prevBook = newbook;
        a.firstBook = newbook;
        //a.bookCount++;
    };
}

void deleteOneBook(bookList& a)
{
    if (a.lastBook == NULL)
    {
        return;
    }
    else
    {
        bookNode* q;
        q = a.lastBook;
        a.lastBook = q->prevBook;
        q->prevBook->nextBook = NULL;
        delete q; q = NULL;
        a.bookCount--;
    }
};

void delete_ALL_book(bookList& a)
{
    while (a.firstBook != NULL)
    {
        deleteOneBook(a);
        a.firstBook = NULL;
        a.lastBook = NULL;
    };
};

void cout_Book_List(bookList a)
{
    cout << " TRONG THU VIEN HIEN CO " << a.bookCount << " SACH KHAC NHAU!" << endl;
    for (bookNode* p = a.firstBook; p != NULL; p = p->nextBook)
    {
        cout << " Sach: " << p->bookInfo.book_Name << " hien dang co " << p->bookInfo.count << " quyen!" << endl;
        cout << " --------------------------------------------------------------" << endl;
    }
};

void getBookList(bookList& a)
{
    FILE* f = fopen(BOOKLIST_FILE, "rb+");
    if (f == NULL) { cout << " CO LOI VOI FILE BOOK.DAT!" << endl; return; };

    //lay tong so cuon sach hien co (cac sach giong nhau duoc tinh la 1)
    fseek(f, 0, SEEK_SET);
    fread(&a.bookCount, sizeof(int), 1, f);

    //lay danh sach cac sach vao book list
    for (int i = 0; i < a.bookCount; ++i)
    {
        Book* newBook = new Book;
        fread(newBook, sizeof(Book), 1, f);

        bookNode* newBookNode = createBookNode(*newBook);
        add_book_to_list(a, newBookNode);

    };
    fclose(f);
};

void write_bookList_to_DAT(bookList list)
{
    FILE* f = fopen(BOOKLIST_FILE, "wb+");
    if (f == NULL) {
        cout << " CO LOI VOI FILE BOOK.DAT!" << endl;
        return;
    }

    fwrite(&list.bookCount, sizeof(int), 1, f);
    bookNode* book = list.firstBook;
    while (book != NULL) {
        fwrite(&book->bookInfo, sizeof(Book), 1, f);
        book = book->nextBook;
    };
    cout << "CCCCCC" << endl;
    fclose(f);
}
*/