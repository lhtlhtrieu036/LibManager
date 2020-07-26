#include "include.h"


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
void Initialise(accountList*& users, userInfoList*& infos, danhSachDocGia*& dsDocGia, int& totalAccounts, int& totalDocGia) {
    users = getAccountList(totalAccounts);
    infos = getUserInfoList(totalAccounts);
    dsDocGia = getDanhSachDocGiaList(totalDocGia);

    if (users == NULL || infos == NULL || dsDocGia == NULL) {
        cout << "Co van de xay ra voi file du lieu. Vui long tai lai chuong trinh.\n";
        exit(0);
    }
}

// Ham ghi cac danh sach tro lai file sau khi ket thuc.
void Terminate(accountList*& users, userInfoList*& infos, danhSachDocGia*& dsDocGia, int totalAccounts, int totalDocGia) {
    // Ghi danh sach users tro lai file.
    FILE* f = fopen(ACCOUNT_FILE, "wb+");
    fseek(f, 0, SEEK_SET);
    
    // Ghi tong so user.
    fwrite(&totalAccounts, sizeof(int), 1, f);

    // Ghi credentials tung user.
    accountNode* thisNode = users->head;
    while (thisNode != NULL) {
        fwrite(thisNode->credentials, sizeof(account), 1, f);
        thisNode = thisNode->nextAccount;
    }
    fclose(f);

    // Ghi info users tro lai file.
    f = fopen(USER_INFO_FILE, "wb+");

    // Ghi info tung user.
    userInfoNode* thisUserInfo = infos->head;
    while (thisUserInfo != NULL) {
        fwrite(thisUserInfo->info, sizeof(user_info), 1, f);
        thisUserInfo = thisUserInfo->nextUser;
    }
    fclose(f);

    // Ghi doc gia tro lai file.
    f = fopen(DOCGIA_FILE, "wb+");

    // Ghi tong so doc gia.
    fwrite(&totalDocGia, sizeof(int), 1, f);

    // Ghi tung doc gia.
    nodeDocGia* docGia = dsDocGia->docGiaDau;
    while (docGia != NULL) {
        fwrite(&docGia->thongTinDocGia, sizeof(theDocGia), 1, f);
        docGia = docGia->docGiaTiepTheo;
    }
    fclose(f);

    //
    // Xoa cac danh sach.
    //
    freeAccountList(users);
    freeUserInfoList(infos);
    freeDanhSachDocGia(dsDocGia);
}

int main() {
    //
    // Thong tin demo
    //
    cout << "(Demo only): Tai khoan admin: admin/admin@fit.hcmus" << endl;
    cout << "(Demo only): Tai khoan quan ly: lttan/lttan@bqpvietnam" << endl;
    cout << "(Demo only): Tai khoan chuyen vien: thquan/quan@hcmus" << endl;
    system("pause");

    //
    // De bat dau, dau tien load tat ca user va info vao mot danh sach.
    // phuc vu muc dich dang nhap.
    //
    
    int totalAccounts = 0, totalDocGia = 0;
    accountList* users = NULL;
    userInfoList* infos = NULL;
    danhSachDocGia* dsDocGia = NULL;


    Initialise(users, infos, dsDocGia, totalAccounts, totalDocGia);

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
    bool stop_executing = false;
    
    // Bat nguoi dung dang nhap bang moi gia.
    do {
        // Thoat hoan toan chuong trinh.
        if (stop_executing) {
            Terminate(users, infos, dsDocGia, totalAccounts, totalDocGia);
            break;
        }

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
            // Xoa man hinh.
            system("cls");

            // Load menu co ban.
            generalMenu();

            // Neu la admin, load menu nang cao cho admin.
            if (isAdmin(user_session_info)) {
                adminMenu();
            }

            // Load menu quan ly doc gia.
            quanLyDocGia(user_session_info);

            thongKeCoBan(user_session_info);

            cout << "=====" << endl;
            cout << "Nhap lenh ban muon thuc hien (so dung truoc moi menu): " << endl;
            if (!(cin >> command_code)) {
                cin.clear(); // xoa loi
                cin.ignore(); // xoa noi dung trong stream
                continue;
            }

            switch (command_code) {
                // Bat su kien doi mat khau.
                case CHANGE_PASSWORD_COMMAND_CODE: {
                    if (changeUserPassword(user_session_account)) {
                        logUserOut(user_session_account, user_session_info);
                        break;
                    }
                    break;
                }

                // Bat su kien doi thong tin.
                case CHANGE_INFO_COMMAND_CODE: {
                    editInfoMenu();
                    catchEditInfoMenu(user_session_account, user_session_info);
                    break;
                }

                // Bat su kien dang xuat.
                case LOGOUT_COMMAND_CODE: {
                    logUserOut(user_session_account, user_session_info);
                    cout << "Dang xuat thanh cong. De thoat hoan toan, hay dang nhap lai va dung lenh " << EXIT_COMMAND_CODE << endl;
                    break;
                }

                // Bat su kien dang xuat va thoat.
                case EXIT_COMMAND_CODE: {
                    if (isLoggedIn(user_session_account, user_session_info))
                        logUserOut(user_session_account, user_session_info);
                    cout << "Da dang xuat, dang thoat chuong trinh.." << endl;
                    stop_executing = true;
                    break;
                }

                // Bat su kien them user.
                case MENU_THEM_USER_COMMAND_CODE: {
                    if (isAdmin(user_session_info)) {
                        if (addUser(totalAccounts, users, infos)) {
                            cout << "Da tao tai khoan moi thanh cong." << endl;
                            cout << "Moi thay doi se duoc luu sau khi dang xuat va thoat khoi chuong trinh bang lenh " << EXIT_COMMAND_CODE << endl;

                            cout << "Thong tin tai khoan moi duoc tao: " << endl;
                            cout << "ID: " << infos->tail->info->ID << endl;
                            cout << "Tai khoan: " << users->tail->credentials->user_name << endl;
                            cout << "Mat khau: " << users->tail->credentials->pass_word << endl;
                        }
                        else cout << "Do dai mot trong so cac thong tin khong hop le." << endl;
                    }
                    else cout << "Ban khong co quyen thuc hien lenh nay." << endl;
                    break;
                }

                // Bat su kien phan quyen user (admin)
                case MENU_PHAN_QUYEN_USER_COMMAND_CODE: {
                    if (isAdmin(user_session_info)) {
                        if (permissionUser(infos)) {
                            cout << "Da phan quyen thanh cong." << endl;
                            cout << "Moi thay doi se duoc luu sau khi dang xuat va thoat khoi chuong trinh bang lenh " << EXIT_COMMAND_CODE << endl;
                        }
                        else {
                            cout << "Khong the phan quyen cho user nay vi mot trong so cac ly do sau:" << endl;
                            cout << "- khong ton tai quyen duoc phan cong." << endl;
                            cout << "- nguoi dung duoc phan quyen khong ton tai." << endl;
                            cout << "- phan quyen cho admin." << endl;
                            cout << "- lenh phan quyen bi huy." << endl;
                        }
                    }
                    else cout << "Ban khong co quyen thuc hien lenh nay." << endl;
                    break;
                }
                
                // Bat su kien xem doc gia
                case XEM_DOC_GIA_COMMAND_CODE: {
                    cout << "== Danh sach doc gia ==" << endl;
                    xemDanhSachDocGia(dsDocGia->docGiaDau);
                    cout << "==        END        ==" << endl;
                    cout << "Danh sach nay co " << totalDocGia << " doc gia." << endl;
                    break;
                }

                // Bat su kien them doc gia tu file .csv
                case THEM_DOC_GIA_CSV_COMMAND_CODE: {
                    cout << "Nhap file .csv chua thong tin cac doc gia: ";
                    char fileName[1024]; cin >> fileName;

                    if (isCSV(fileName)) {
                        FILE* f = fopen(fileName, "r+");

                        if (f != NULL) {
                            int totalAdded = themDocGiaTuCSV(f, dsDocGia, totalDocGia);
                            cout << "Da them thanh cong " << totalAdded << " doc gia." << endl;
                        }
                        else cout << "File khong ton tai." << endl;
                    }
                    else cout << "File ban vua nhap khong phai la file .csv" << endl;

                    break;
                }
                
                // Bat su kien doi thong tin doc gia.
                case DOI_THONG_TIN_DOC_GIA_COMMAND_CODE: {
                    cout << "Nhap ID doc gia can thay doi thong tin: " << endl;
                    int idDocGia;
                    if (!(cin >> idDocGia)) {
                        cin.clear();
                        cin.ignore();
                        break;
                    }

                    // Tim doc gia co ID.
                    nodeDocGia* docGia = searchForDocGiaByID(idDocGia, dsDocGia);

                    if (docGia != NULL) {
                        // Hien menu
                        editInfoDocGia();

                        // Bat su kien.
                        catchEditInfoDocGia(docGia, dsDocGia);
                    }
                    else cout << "Doc gia khong ton tai." << endl;
                    break;
                }

                // Bat su kien xoa doc gia
                case XOA_DOC_GIA_COMMAND_CODE: {
                    if (!isChuyenVien(user_session_info)) {
                        cout << "Nhap ID cua doc gia can xoa: " << endl;
                        int ID; cin >> ID;

                        if (deleteDocGia(ID, dsDocGia, totalDocGia)) {
                            cout << "Da xoa doc gia thanh cong." << endl;
                        } else {
                            cout << "Xoa doc gia khong thanh cong vi mot trong cac ly do sau: " << endl;
                            cout << "- Doc gia khong ton tai." << endl;
                            cout << "- Lenh xoa bi huy." << endl;
                        }
                    } else cout << "Ban khong co quyen thuc hien lenh nay." << endl;
                    break;
                }

                // Bat su kien tim doc gia co CMND
                case TIM_DOC_GIA_CMND_COMMAND_CODE: {
                    cout << "Nhap CMND cua doc gia can tim:" << endl;
                    char CMND[CMND_MAX]; cin >> CMND;

                    nodeDocGia* docGia = searchForDocGiaByCMND(CMND, dsDocGia);
                    if (docGia == NULL) cout << "Khong tim thay doc gia co CMND " << CMND << endl;
                    else inDocGia(docGia->thongTinDocGia);

                    break;
                }

                // Bat su kien tim doc gia co ho ten.
                case TIM_DOC_GIA_HO_TEN_COMMAND_CODE: {
                    cout << "Nhap ho ten cua doc gia can tim:" << endl;
                    char hoTen[NAME_MAX];
                    cin.ignore(); cin.getline(hoTen, NAME_MAX);

                    searchForDocGiaByHoTen(_strlwr(hoTen), dsDocGia);

                    break;
                }

                // Bat su kien thong ke so luong doc gia.
                case THONG_KE_SO_LUONG_DOC_GIA_COMMAND_CODE:
                    if (!isChuyenVien(user_session_info)) {
                        cout << "Thong ke so luong doc gia:" << endl;
                        cout << "Tong so luong doc gia: " << totalDocGia << endl;
                    }
                    else cout << "Ban khong co quyen thuc hien chuc nang nay." << endl;
                    break;

                // Bat su kien thong ke doc gia theo gioi tinh.
                case THONG_KE_DOC_GIA_GIOI_TINH_COMMAND_CODE: {
                    if (!isChuyenVien(user_session_info)) thongKeTheoGioiTinh(dsDocGia, totalDocGia);
                    else cout << "Ban khong co quyen thuc hien chuc nang nay." << endl;
                    
                    break;
                }

                default:
                    cout << "Khong tim thay lenh " << command_code << endl;
            }
            system("pause");
        }
    } while (true);
    
    
    return 0;
}