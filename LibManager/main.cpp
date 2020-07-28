#include "include.h"

// Ham nap danh sach nguoi dung & danh sach thong tin nguoi dung
// tu file vao linked list.
void Initialise(accountList*& users, 
                userInfoList*& infos, 
                danhSachDocGia*& dsDocGia, 
                bookList*& dsSach) {
    users = getAccountList();
    infos = getUserInfoList(users->totalAccount);
    dsDocGia = getDanhSachDocGiaList();
    dsSach = getDanhSachSachList();

    if (users == NULL || infos == NULL || dsDocGia == NULL || dsSach == NULL) {
        cout << "Co van de xay ra voi file du lieu. Vui long tai lai chuong trinh.\n";
        exit(0);
    }
}

// Ham ghi cac list vao file tuong ung.
void writeAllLists(accountList* users, userInfoList* infos, danhSachDocGia* dsDocGia, bookList* dsSach) {
    // Ghi danh sach users tro lai file.
    writeCredentialsBackToFile(users);

    // Ghi info users tro lai file.
    writeInfoBackToFile(infos);

    // Ghi doc gia tro lai file.
    writeDocGiaBackToFile(dsDocGia);

    // Ghi sach tro lai file.
    writeBookBackToFile(dsSach);
}

// Ham ket thuc chuong trinh: luu lai cac thay doi va free cac list.
void Terminate(accountList*& users, userInfoList*& infos, danhSachDocGia*& dsDocGia, bookList*& dsSach) {
    //
    // Ghi lai cac thay doi vao file.
    //
    writeAllLists(users, infos, dsDocGia, dsSach);

    //
    // Xoa cac danh sach.
    //
    freeAccountList(users);
    freeUserInfoList(infos);
    freeDanhSachDocGia(dsDocGia);
    freeBookList(dsSach);
}

int main(int argc, char** argv) {
    //
    // De bat dau, dau tien load tat ca user va info vao mot danh sach.
    // phuc vu muc dich dang nhap.
    //
    
    accountList* users = NULL;
    userInfoList* infos = NULL;
    danhSachDocGia* dsDocGia = NULL;
    bookList* dsSach = NULL;

    Initialise(users, infos, dsDocGia, dsSach);

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
    // (That ra cai nay la dang nhap bang command line).
    if (argc != 3) {
        cout << "Vui long nhap tai khoan / mat khau." << endl;
        stop_executing = true;
    } 
    else {
        // Dang nhap va load user account session.
        user_session_account = logUserIn(argv[1], argv[2], users);
        if (user_session_account == NULL) {
            cout << "Tai khoan / Mat khau khong chinh xac." << endl;
            stop_executing = true;
        }
        else {
            // Lay user_session_info.
            user_session_info = getUserInfo(infos, user_session_account);

            // Neu user inative, bao loi va dang xuat.
            if (!isActive(user_session_info)) {
                cout << "Tai khoan cua ban da bi deactivate. Vui long lien he admin de duoc giai quyet." << endl;
                logUserOut(user_session_account, user_session_info);
                stop_executing = true;
            }
        }
    }

    // Vong lap giu cho chuong trinh luon chay.
    // (Thoat bang cach set bien stop_executing = true, nhu da lam ben tren
    // de bat mot so loi.)
    do {
        // Thoat hoan toan chuong trinh.
        if (stop_executing) {
            Terminate(users, infos, dsDocGia, dsSach);
            break;
        }

        system("cls");

        // Da dang nhap thanh cong.
        int command_code = -1;
        while (user_session_account != NULL && user_session_info != NULL) {
            // Xoa man hinh.
            system("cls");

            // Load menu co ban.
            generalMenu();

            // Neu la admin, load menu nang cao cho admin.
            if (isAdmin(user_session_info))
                adminMenu();

            // Load menu quan ly doc gia.
            quanLyDocGia(user_session_info);

            // Load menu quan ly sach.
            quanLySach(user_session_info);

            // Load menu quan ly Muon - Tra Sach
            muonTraSach();

            // Load menu thong ke co ban.
            thongKeCoBan(user_session_info);

            cout << "=====" << endl;
            cout << "Nhap lenh ban muon thuc hien (so dung truoc moi menu): " << endl;
            if (!(cin >> command_code)) {
                cin.clear(); // xoa loi
                cin.ignore(); // xoa noi dung trong stream
                continue;
            }

            system("cls");

            switch (command_code) {
                // Bat su kien doi mat khau.
                case CHANGE_PASSWORD_COMMAND_CODE: {
                    if (changeUserPassword(user_session_account)) {
                        logUserOut(user_session_account, user_session_info);
                        stop_executing = true;
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

                // Bat su kien dang xuat va thoat.
                case LOGOUT_COMMAND_CODE: {
                    if (isLoggedIn(user_session_account, user_session_info))
                        logUserOut(user_session_account, user_session_info);
                    cout << "Da dang xuat, dang thoat chuong trinh.." << endl;
                    stop_executing = true;
                    break;
                }

                // Bat su kien them user.
                case MENU_THEM_USER_COMMAND_CODE: {
                    if (isAdmin(user_session_info)) {
                        if (addUser(users, infos)) {
                            cout << "Da tao tai khoan moi thanh cong." << endl;
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
                    cout << "Danh sach nay co " << dsDocGia->totalDocGia << " doc gia." << endl;
                    break;
                }

                // Bat su kien them doc gia tu file .csv
                case THEM_DOC_GIA_CSV_COMMAND_CODE: {
                    cout << "Nhap file .csv chua thong tin cac doc gia: ";
                    char fileName[1024]; cin >> fileName;

                    if (isCSV(fileName)) {
                        FILE* f = fopen(fileName, "r+");

                        if (f != NULL)
                            if (confirmationBox()) {
                                int totalAdded = themDocGiaTuCSV(f, dsDocGia);
                                cout << "Da them thanh cong " << totalAdded << " doc gia." << endl;
                            } else cout << "Lenh nhap doc gia da bi huy." << endl;
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

                        if (deleteDocGia(ID, dsDocGia)) {
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

                    searchForDocGiaByHoTen(hoTen, dsDocGia);

                    break;
                }

                // Bat su kien xem danh sach sach trong thu vien.
                case XEM_SACH_COMMAND_CODE: {
                    if (!isChuyenVien(user_session_info)) {
                        inBookList(dsSach->firstBook);
                        cout << "Co tong so " << dsSach->bookCount << " cuon sach trong thu vien." << endl;
                    } else cout << "Ban khong co quyen thuc hien lenh nay." << endl;
                    break;
                }

                // Bat su kien nhap sach tu file .csv
                case THEM_SACH_CSV_COMMAND_CODE: {
                    if (!isChuyenVien(user_session_info)) {
                        cout << "Nhap file .csv chua sach: " << endl;
                        char fileName[1024]; cin >> fileName;

                        if (isCSV(fileName)) {
                            FILE* f = fopen(fileName, "r+");

                            if (f != NULL)
                                if (confirmationBox()) {
                                    int totalAdded = addBookFromCSV(f, dsSach);
                                    cout << "Da them thanh cong " << totalAdded << " line." << endl;
                                } else cout << "Lenh nhap sach da bi huy." << endl;
                            else cout << "File khong ton tai." << endl;
                        } else cout << "File ban vua nhap khong phai la file .csv" << endl;
                    } else cout << "Ban khong co quyen thuc hien lenh nay." << endl;

                    break;
                }

                // Bat su kien doi thong tin sach.
                case DOI_THONG_TIN_SACH_COMMAND_CODE: {
                    if (!isChuyenVien(user_session_info)) {
                        cout << "Nhap ISBN cua sach can doi thong tin: ";
                        char ISBN[ISBN_MAX]; cin >> ISBN;

                        bookNode* thisBook = searchBookByISBN(ISBN, dsSach);
                        if (thisBook != NULL) {
                            // Hien menu chinh sua thong tin sach.
                            editInfoBook();

                            catchEditInfoBook(thisBook, dsSach);
                        } else cout << "Sach co ISBN " << ISBN << " khong ton tai." << endl;
                    } else cout << "Ban khong co quyen thuc hien lenh nay." << endl;

                    break;
                }

                // Bat su kien xoa thong tin sach.
                case XOA_SACH_COMMAND_CODE: {
                    if (!isChuyenVien(user_session_info)) {
                        cout << "Nhap ISBN cua quyen sach can xoa: " << endl;
                        char ISBN[ISBN_MAX]; cin >> ISBN;

                        if (deleteBook(ISBN, dsSach))
                            cout << "Da xoa sach ISBN " << ISBN << " thanh cong." << endl;
                        else {
                            cout << "Xoa sach khong thanh cong vi mot trong so cac ly do sau:" << endl;
                            cout << "- Sach co ISBN khong ton tai." << endl;
                            cout << "- Lenh xoa sach da bi huy." << endl;
                        }
                    } else cout << "Ban khong co quyen thuc hien lenh nay." << endl;

                    break;
                }

                // Bat su kien tim sach theo ISBN
                case TIM_SACH_THEO_ISBN_COMMAND_CODE: {
                    cout << "Nhap ISBN cua sach: " << endl;
                    char ISBN[ISBN_MAX]; cin >> ISBN;

                    bookNode* resultBook = searchBookByISBN(ISBN, dsSach);
                    if (resultBook != NULL)
                        inMotQuyenSach(resultBook->bookInfo);
                    else cout << "Khong tim thay sach co ISBN " << ISBN << endl;
                    break;
                }

                // Bat su kien tim sach theo ten.
                case TIM_SACH_THEO_TEN_COMAND_CODE: {
                    cout << "Nhap ten sach can tim: " << endl;
                    char tenSach[BOOK_NAME_MAX]; cin.ignore();
                    cin.getline(tenSach, BOOK_NAME_MAX);

                    searchBookByName(tenSach, dsSach);           

                    break;
                }

                // Bat su kien thong ke so luong sach.
                case THONG_KE_SO_LUONG_SACH_COMMAND_CODE: {
                    if (!isChuyenVien(user_session_info)) {
                        cout << "Trong thu vien hien co " << dsSach->bookCount << " quyen sach." << endl;
                        cout << "De xem chi tiet tung quyen sach, dung lenh " << XEM_SACH_COMMAND_CODE << endl;
                        cout << "De tra cuu thong tin sach theo ISBN, dung lenh " << TIM_SACH_THEO_ISBN_COMMAND_CODE << endl;
                        cout << "De tra cuu thong tin sach theo ten sach, dung lenh " << TIM_SACH_THEO_TEN_COMAND_CODE << endl;
                    } else cout << "Ban khong co quyen thuc hien lenh nay." << endl;
                    
                    break;
                }

                // Bat su kien thong ke so luong sach theo the loai.
                case THONG_KE_SACH_THEO_THE_LOAI_COMMAND_CODE: {
                    if (!isChuyenVien(user_session_info)) {
                        cout << "Thong ke sach theo the loai: " << endl;
                        thongKeSachTheoTheLoai(dsSach);
                    } else cout << "Ban khong co quyen thuc hien lenh nay." << endl;
                    break;
                }

                // Bat su kien thong ke so luong doc gia.
                case THONG_KE_SO_LUONG_DOC_GIA_COMMAND_CODE:
                    if (!isChuyenVien(user_session_info)) {
                        cout << "Thong ke so luong doc gia:" << endl;
                        cout << "Tong so luong doc gia: " << dsDocGia->totalDocGia << endl;
                    }
                    else cout << "Ban khong co quyen thuc hien chuc nang nay." << endl;
                    break;

                // Bat su kien thong ke doc gia theo gioi tinh.
                case THONG_KE_DOC_GIA_GIOI_TINH_COMMAND_CODE: {
                    if (!isChuyenVien(user_session_info)) thongKeTheoGioiTinh(dsDocGia);
                    else cout << "Ban khong co quyen thuc hien chuc nang nay." << endl;
                    
                    break;
                }

                default:
                    cout << "Khong tim thay lenh " << command_code << endl;
            }
            system("pause");

            // Luu thong tin lai sau moi lan cap nhat.
            writeAllLists(users, infos, dsDocGia, dsSach);
        }
    } while (true);
    
    return 0;
}