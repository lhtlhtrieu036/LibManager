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
void inMotQuyenSach(Book thisBook) {
	cout << "ISBN: " << thisBook.ISBN << endl;
	cout << "Ten sach: " << thisBook.book_Name << endl;
	cout << "Ten tac gia: " << thisBook.book_Author << endl;
	cout << "Nam xuat ban: " << thisBook.book_published_year << endl;
	cout << "Nha xuat ban: " << thisBook.book_publisher << endl;
	cout << "The loai: " << thisBook.book_type << endl;
	cout << "Gia sach: " << thisBook.price << endl;
	cout << "So luong: " << thisBook.count << endl;
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

void freeBookList(bookList*& dsSach) {
	while (dsSach->firstBook != NULL)
		deleteSachDauList(dsSach);
	free(dsSach);
}





