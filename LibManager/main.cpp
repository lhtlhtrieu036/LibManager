#include "include.h"
#include "account.h"


int main() {
	cout << "Library Manager";
	ifstream p("danh_sach.csv");
	user_info a;
	user_info* A;
	int n;
	A = new user_info[50];
	read_Mang_User(p, A, n);
	cout << " MSSV,Ho Ten,DTB" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << " " << A[i].ID << ", " << A[i].ho_Ten << ", " << A[i].tinh_Trang << ", " << A[i].ngay_Sinh << endl;
	};
	delete[]A; A = NULL;

	
	return 0;
}