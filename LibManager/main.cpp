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
    
    // Bat nguoi dung dang nhap bang moi gia.
    do {
        system("cls");
        do {
            user_session_account = logUserIn(users);
            if (user_session_account == NULL) {
                cout << "Sai tai khoan / mat khau. Xin thu lai!" << endl;
            }
            else {
                user_session_info = getUserInfo(infos, user_session_account);

                // Neu nguoi dung khong con active, thong bao va dang xuat.
                if (!isActive(user_session_info)) {
                    cout << "Tai khoan cua ban da bi block. Vui long lien he admin de duoc giai quyet. Xin cam on." << endl;
                    logUserOut(user_session_account, user_session_info);
                    break;
                }

                cout << "Dang nhap thanh cong. Dang chuyen ban den menu nguoi dung phu hop..." << endl;
            }
            system("pause");
            system("cls");
        } while (user_session_account == NULL || user_session_info == NULL);

        // Da dang nhap thanh cong.
        int command_code = -1;
        while (user_session_account != NULL && user_session_info != NULL) {
            if (isAdmin(user_session_info)) {
                adminMenu();
                // Bat su kien admin menu.
            }

            else if (isQuanLy(user_session_info)) {
                quanlyMenu();
                // Bat su kien quan ly menu.
            }

            else {
                chuyenvienMenu();
                // Bat su kien chuyen vien menu.
            }

            cout << "Nhap lenh ban muon thuc hien: " << endl;
            cin >> command_code;

            // Bat su kien dang nhap thanh cong va thoat.
            if (command_code == LOGOUT_COMMAND_CODE) {
                logUserOut(user_session_account, user_session_info);
                cout << "Dang xuat thanh cong." << endl;
                system("pause");
                break;
            }

            // Bat su kien dang nhap thanh cong, dang xuat va thoat hoan toan.
            if (command_code == EXIT_COMMAND_CODE) {
                if (isLoggedIn(user_session_account, user_session_info))
                    logUserOut(user_session_account, user_session_info);
                cout << "Da dang xuat, dang thoat chuong trinh.." << endl;
                system("pause");
                exit(0);
            }
        }
    } while (true);
    
    
    return 0;
}