#include"include.h"

// LUU Y:
// File ACCOUNT_FILE phai co dang nhu sau:

// n - Tong so user
// user1username
// user1password
// user2username
// user2password
// ..
// usernusername
// usernpassword

// Ham nap danh sach nguoi dung & danh sach thong tin nguoi dung
// tu file vao linked list.
void Initialise(accountList*& users, userInfoList*& infos, int& totalAccounts) {
	users = getAccountList(totalAccounts);
	infos = getUserInfoList(totalAccounts);

	if (users == NULL || infos == NULL) {
		cout << "Co van de xay ra voi file du lieu. Vui long tai lai chuong trinh.\n";
		exit(0);
	}
}

int main() {
	//
	// De bat dau, dau tien load tat ca user va info vao mot danh sach.
	// phuc vu muc dich dang nhap.
	//
	
	int totalAccounts;
	accountList* users = NULL;
	userInfoList* infos = NULL;


	Initialise(users, infos, totalAccounts);

	//
	// Sau do cac bien sau se luu session (phien dang nhap) cua nguoi dung:
	//
	// user_session_account luu account credentials,
	// su dung khi can thay doi password.
	//
	// user_session_info luu info nguoi dung,
	// dung de tra cuu permission, thong tin cung nhu thay doi thong tin.
	//
	// Den day neu can kiem tra dang nhap: truy van xem truong
	// user_session_info = NULL => chua dang nhap, nguoc lai la da dang nhap/
	//

	account* user_session_account = NULL;
	user_info* user_session_info = NULL;





	printf("%s", users->tail->credentials->pass_word);
	return 0;
}