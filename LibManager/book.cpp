#include "include.h"

bookNode* creatBookNode(Book newBook)
{
	bookNode* p = new bookNode;
	
		p->bookInfo = newBook;
		p->nextBook = NULL;
		p->prevBook = NULL;

		return p;
};

void enterBookInfo(bookList& a)
{
	Book newBook;
	cout << " NHAP CAC THONG TIN SAU CUA SACH: " << endl;
	char tempISBN[ISBN_MAX];
	cout << " ISBN: "; cin >> tempISBN;
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
	p = creatBookNode(newBook);
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
}





