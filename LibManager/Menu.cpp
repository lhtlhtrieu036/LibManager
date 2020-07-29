#include"include.h"

// Menu xu ly sua doi thong tin.
void editInfoMenu() {
    cout << "== Thay doi thong tin ==" << endl;
    cout << MENU_XEM_THONG_TIN_COMMAND_CODE << ". Xem thong tin." << endl;
    cout << MENU_DOI_TEN_COMMAND_CODE << ". Doi ho va ten nguoi dung." << endl;
    cout << MENU_DOI_NGAY_SINH_COMMAND_CODE << ". Doi ngay sinh." << endl;
    cout << MENU_DOI_CMND_COMMAND_CODE << ". Doi CMND." << endl;
    cout << MENU_DOI_DIA_CHI_COMMAND_CODE << ". Doi dia chi." << endl;
    cout << MENU_DOI_GIOI_TINH_COMMAND_CODE << ". Chuyen gioi." << endl; // thay doi sau.
    cout << "Nhap lenh: " << endl;
}

// Menu chung cho cac loai tai khoan.
void generalMenu() {
    cout << "== Cac chuc nang co ban ==" << endl;
    cout << CHANGE_PASSWORD_COMMAND_CODE << ". Thay doi mat khau tai khoan." << endl;
    cout << CHANGE_INFO_COMMAND_CODE << ". Thay doi thong tin tai khoan." << endl;
    cout << LOGOUT_COMMAND_CODE << ". Dang xuat khoi tai khoan." << endl;
}

// Menu cho admin
void adminMenu() {
    cout << "== Cac chuc nang nang cao cho admin ==" << endl;
    cout << MENU_THEM_USER_COMMAND_CODE << ". Tao nguoi dung moi." << endl;
    cout << MENU_PHAN_QUYEN_USER_COMMAND_CODE << ". Phan quyen cho nguoi dung." << endl;
}

void quanLyDocGia(user_info* user_session_info) {
    cout << "== Quan ly doc gia == " << endl;
    cout << XEM_DOC_GIA_COMMAND_CODE << ". Xem danh sach doc gia." << endl;
    cout << THEM_DOC_GIA_CSV_COMMAND_CODE << ". Them doc gia tu file .csv." << endl;
    cout << DOI_THONG_TIN_DOC_GIA_COMMAND_CODE << ". Doi thong tin mot doc gia." << endl;

    if (!isChuyenVien(user_session_info))
        cout << XOA_DOC_GIA_COMMAND_CODE << ". Xoa mot doc gia." << endl;

    cout << TIM_DOC_GIA_CMND_COMMAND_CODE << ". Tim doc gia theo CMND." << endl;
    cout << TIM_DOC_GIA_HO_TEN_COMMAND_CODE << ". Tim doc gia theo Ho ten." << endl;
}

void quanLySach(user_info* user_session_info) {
    cout << "== Quan ly sach ==" << endl;
    if (!isChuyenVien(user_session_info)) {
        cout << XEM_SACH_COMMAND_CODE << ". Xem danh sach cac sach trong thu vien." << endl;
        cout << THEM_SACH_CSV_COMMAND_CODE << ". Them sach tu file .csv." << endl;
        cout << DOI_THONG_TIN_SACH_COMMAND_CODE << ". Doi thong tin mot quyen sach." << endl;
        cout << XOA_SACH_COMMAND_CODE << ". Xoa thong tin mot quyen sach." << endl;
    }
    cout << TIM_SACH_THEO_ISBN_COMMAND_CODE << ". Tim sach theo ISBN." << endl;
    cout << TIM_SACH_THEO_TEN_COMAND_CODE << ". Tim sach theo ten sach." << endl;
}

void muonTraSach() {
    cout << "== Quan ly Muon - Tra sach ==" << endl;
    cout << MUON_SACH_COMMAND_CODE << ". Lap phieu muon sach." << endl;
    cout << TRA_SACH_COMMAND_CODE << ". Lap phieu tra sach." << endl;
}

void editInfoDocGia() {
    cout << "== Doi thong tin doc gia ==" << endl;
    cout << MENU_DOI_TEN_DOC_GIA_COMMAND_CODE << ". Doi ten doc gia." << endl;
    cout << MENU_DOI_CMND_DOC_GIA_COMMAND_CODE << ". Doi CMND doc gia." << endl;
    cout << MENU_DOI_NGAY_SINH_DOC_GIA_COMMAND_CODE << ". Doi ngay sinh doc gia." << endl;
    cout << MENU_DOI_GIOI_TINH_DOC_GIA_COMMAND_CODE << ". Doi gioi tinh doc gia." << endl;
    cout << MENU_DOI_EMAIL_DOC_GIA_COMMAND_CODE << ". Doi email doc gia." << endl;
    cout << MENU_DOI_DIA_CHI_DOC_GIA_COMMAND_CODE << ". Doi dia chi doc gia." << endl;
}

void editInfoBook() {
    cout << "== Thay doi thong tin sach ==" << endl;
    cout << MENU_DOI_TEN_SACH_COMMAND_CODE << ". Doi ten sach." << endl;
    cout << MENU_DOI_TAC_GIA_SACH_COMMAND_CODE << ". Doi tac gia sach." << endl;
    cout << MENU_DOI_NAM_XUAT_BAN_SACH_COMMAND_CODE << ". Doi nam xuat ban sach." << endl;
    cout << MENU_DOI_NHA_XUAT_BAN_SACH_COMMAND_CODE << ". Doi nha xuat ban sach." << endl;
    cout << MENU_DOI_THE_LOAI_SACH_COMMAND_CODE << ". Doi the loai sach." << endl;
    cout << MENU_DOI_GIA_SACH_COMMAND_CODE << ". Doi gia sach." << endl;
}

void thongKeCoBan(user_info* user_session_info) {
    cout << "== Thong ke co ban ==" << endl;

    if (!isChuyenVien(user_session_info)) {
        cout << THONG_KE_SO_LUONG_SACH_COMMAND_CODE << ". Thong ke so luong sach trong thu vien." << endl;
        cout << THONG_KE_SACH_THEO_THE_LOAI_COMMAND_CODE << ". Thong ke so sach theo the loai." << endl;
        cout << THONG_KE_SO_LUONG_DOC_GIA_COMMAND_CODE << ". Thong ke so luong doc gia." << endl;
        cout << THONG_KE_DOC_GIA_GIOI_TINH_COMMAND_CODE << ". Thong ke doc gia theo gioi tinh." << endl;
    }
    cout << THONG_KE_SACH_DANG_MUON << ". Thong ke sach dang muon." << endl;
    cout << THONG_KE_DOC_GIA_TRE_HAN << ". Thong ke doc gia tre han." << endl;
}

// Controller (xu ly) cho cac menu

void getInfoMenu(user_info* user_session_info) {
    cout << "== Thong tin cua ban ==" << endl;
    cout << "Ho va ten: " << user_session_info->ho_Ten << endl;
    cout << "Dia chi: " << user_session_info->dia_Chi << endl;
    cout << "CMND: " << user_session_info->so_CMND << endl;
    //cout << "Ngay sinh: " << user_session_info->ngay_Sinh << endl;
	ngayThangNam ngay_sinh_;
	ngay_sinh_ = chuyenDoiNgay(user_session_info->ngay_Sinh);
	cout << "Ngay sinh: " << ngay_sinh_.ngay << "/" << ngay_sinh_.thang << "/" << ngay_sinh_.nam << endl;
    cout << "Gioi tinh: " << user_session_info->gioi_Tinh << endl;
}

void catchEditInfoMenu(account*& account_session_info, user_info*& user_session_info) {
    int editInfoCommand = -1; 
    
    // Bat loi nhap ky tu la vao command
    if (!(cin >> editInfoCommand)) {
        cin.clear();
        cin.ignore();
        cout << "Lenh khong hop le." << endl;
        return;
    }

    switch (editInfoCommand) {
        case MENU_XEM_THONG_TIN_COMMAND_CODE:
            getInfoMenu(user_session_info);
            break;

        case MENU_DOI_CMND_COMMAND_CODE:
            cout << "So CMND hien tai cua ban la: " << user_session_info->so_CMND << endl;
            cout << "Doi so CMND:" << endl;
            
            if (editUserCMND(user_session_info)) {
                cout << "Da doi CMND thanh cong. Xin vui long dang nhap lai de luu moi thay doi." << endl;
            }
            else cout << "CMND khong hop le." << endl;

            break;
            
        case MENU_DOI_TEN_COMMAND_CODE:
            cout << "Ten cua ban hien tai la: " << user_session_info->ho_Ten << endl;
            cout << "Doi ten: " << endl;
            
            if (editUserHoTen(user_session_info)) {
                cout << "Da doi ho va ten thanh cong. Xin vui long dang nhap lai de luu moi thay doi." << endl;
            }
            else cout << "Ho va ten khong hop le." << endl;

            break;

        case MENU_DOI_DIA_CHI_COMMAND_CODE:
            cout << "Dia chi cua ban hien tai la: " << user_session_info->dia_Chi << endl;
            cout << "Doi dia chi: " << endl;

            if (editUserDiaChi(user_session_info)) {
                cout << "Da doi dia chi thanh cong. Xin vui long dang nhap lai de luu moi thay doi." << endl;
            }
            else cout << "Dia chi khong hop le." << endl;

            break;

        case MENU_DOI_GIOI_TINH_COMMAND_CODE:
            cout << "Gioi tinh cua ban hien tai la: " << user_session_info->gioi_Tinh << endl;
            cout << "Doi gioi tinh: " << endl;

            if (editUserGioiTinh(user_session_info))
                cout << "Da doi gioi tinh thanh cong. Xin vui long dang nhap lai de luu moi thay doi." << endl;
            else cout << "Doi gioi tinh that bai." << endl;
            break;

        case MENU_DOI_NGAY_SINH_COMMAND_CODE:
            cout << "Ngay sinh cua ban hien tai la: " << user_session_info->ngay_Sinh << endl;
            cout << "Doi ngay sinh: " << endl;

            if (editUserNgaySinh(user_session_info))
                cout << "Da doi ngay sinh thanh cong. Xin vui long dang nhap lai de luu moi thay doi." << endl;
            else {
                cout << "Doi ngay sinh that bai vi mot trong cac ly do sau:" << endl;
                cout << "- Ngay sinh khong hop le." << endl;
                cout << "- Lenh doi ngay sinh bi huy." << endl;
            }
            break;

        default:
            cout << "Khong tim thay chuc nang nay." << endl;
    }
}

void catchEditInfoDocGia(nodeDocGia*& docGia, danhSachDocGia*& dsDocGia) {
    int command = -1;
    cout << "Chon phan thong tin can chinh sua: ";
    if (!(cin >> command)) {
        cin.clear();
        cin.ignore();
        cout << "Lenh khong hop le." << endl;
        return;
    }
    switch (command) {
        case MENU_DOI_TEN_DOC_GIA_COMMAND_CODE: {
            cout << "Doi Ho ten doc gia." << endl;
            cout << "Ho ten doc gia hien tai la " << docGia->thongTinDocGia.ho_Ten << endl;

            if (editTenDocGia(docGia))
                cout << "Da doi Ho ten doc gia thanh cong." << endl;
            else {
                cout << "Doi Ho ten doc gia that bai vi mot trong cac ly do sau:" << endl;
                cout << "- Ho ten doc gia qua dai / qua ngan." << endl;
                cout << "- Tien trinh doi Ho ten bi huy." << endl;
            }
            break;
        }

        case MENU_DOI_CMND_DOC_GIA_COMMAND_CODE: {
            cout << "Doi CMND doc gia: " << endl;
            cout << "CMND doc gia hien tai la " << docGia->thongTinDocGia.so_CMND << endl;
            cout << "Luu y: CMND moi khong duoc trung voi cac doc gia hien co." << endl;

            if (editCMNDDocGia(docGia, dsDocGia))
                cout << "Da doi CMND doc gia thanh cong." << endl;
            else {
                cout << "Doi CMND doc gia that bai vi mot trong cac ly do sau: " << endl;
                cout << "- CMND qua dai / qua ngan." << endl;
                cout << "- CMND trung voi doc gia khac hoac trung voi CMND cu." << endl;
                cout << "- Tien trinh doi CMND bi huy." << endl;
            }
            break;
        }

        case MENU_DOI_NGAY_SINH_DOC_GIA_COMMAND_CODE: {
            cout << "Doi ngay sinh doc gia: " << endl;
            cout << "Ngay sinh doc gia hien tai la " << docGia->thongTinDocGia.ngay_Sinh << endl;

            if (editNgaySinhDocGia(docGia))
                cout << "Da doi Ngay sinh doc gia thanh cong." << endl;
            else {
                cout << "Doi Ngay sinh doc gia that bai vi mot trong cac ly do sau: " << endl;
                cout << "- Ngay sinh khong hop le." << endl;
                cout << "- Tien trinh doi Ngay sinh bi huy." << endl;
            }
            break;
        }

        case MENU_DOI_EMAIL_DOC_GIA_COMMAND_CODE: {
            cout << "Doi Email doc gia: " << endl;
            cout << "Email doc gia hien tai la " << docGia->thongTinDocGia.email << endl;

            if (editEmailDocGia(docGia))
                cout << "Da doi Email doc gia thanh cong." << endl;
            else {
                cout << "Doi Email doc gia that bai vi mot trong cac ly do sau: " << endl;
                cout << "- Email qua dai / qua ngan." << endl;
                cout << "- Tien trinh doi Email bi huy." << endl;
            }
            break;
        }

        case MENU_DOI_DIA_CHI_DOC_GIA_COMMAND_CODE: {
            cout << "Doi Dia chi doc gia: " << endl;
            cout << "Dia chi doc gia hien tai la " << docGia->thongTinDocGia.diaChi << endl;

            if (editDiaChiDocGia(docGia))
                cout << "Da doi Dia chi doc gia thanh cong." << endl;
            else {
                cout << "Doi Dia chi doc gia that bai vi mot trong cac ly do sau: " << endl;
                cout << "- Dia chi qua dai / qua ngan." << endl;
                cout << "- Tien trinh doi Dia chi bi huy." << endl;
            }
            break;
        }

        case MENU_DOI_GIOI_TINH_DOC_GIA_COMMAND_CODE: {
            cout << "Doi Gioi tinh doc gia: " << endl;
            cout << "Gioi tinh doc gia hien tai la " << ((isNam(docGia->thongTinDocGia)) ? "NAM" : "NU") << endl;
            cout << "Luu y: " << endl;
            cout << DOCGIA_NAM << ". Nam" << endl;
            cout << DOCGIA_NU << ". Nu" << endl;

            if (editGioiTinhDocGia(docGia))
                cout << "Da doi Gioi tinh doc gia thanh cong." << endl;
            else {
                cout << "Doi Gioi tinh doc gia that bai vi mot trong cac ly do sau: " << endl;
                cout << "- Gioi tinh khong hop le." << endl;
                cout << "- Tien trinh doi Gioi tinh bi huy." << endl;
            }
        }


        default:
            cout << "Khong tim thay lenh " << command << endl;
    }
}

void catchEditInfoBook(bookNode*& thisBook, bookList*& dsSach) {
    int command_code = -1;
    cout << "Chon phan thong tin can chinh sua: " << endl;
    if (!(cin >> command_code)) {
        cin.clear();
        cin.ignore();
        cout << "Lenh khong hop le." << endl;
        return;
    }

    switch (command_code) {
        case MENU_DOI_TEN_SACH_COMMAND_CODE: {
            cout << "Ten sach hien tai la " << thisBook->bookInfo.book_Name << endl;
            cout << "Doi ten sach: " << endl;
            
            if (editBookName(thisBook))
                cout << "Da doi ten sach thanh cong." << endl;
            else cout << "Doi ten sach that bai." << endl;

            break;
        }

        case MENU_DOI_TAC_GIA_SACH_COMMAND_CODE: {
            cout << "Tac gia sach hien tai la " << thisBook->bookInfo.book_Author << endl;
            cout << "Doi tac gia: " << endl;

            if (editAuthorName(thisBook))
                cout << "Da doi tac gia thanh cong. " << endl;
            else cout << "Doi tac gia that bai." << endl;
            break;
        }

        case MENU_DOI_NHA_XUAT_BAN_SACH_COMMAND_CODE: {
            cout << "Nha xuat ban hien tai la " << thisBook->bookInfo.book_publisher << endl;
            cout << "Doi NXB: " << endl;

            if (editPublisherName(thisBook))
                cout << "Da doi NXB thanh cong." << endl;
            else cout << "Doi NXB that bai." << endl;

            break;
        }

        case MENU_DOI_NAM_XUAT_BAN_SACH_COMMAND_CODE: {
            cout << "Nam xuat ban sach hien tai la " << thisBook->bookInfo.book_published_year << endl;
            cout << "Doi nam xuat ban sach: " << endl;

            if (editPublishedYear(thisBook))
                cout << "Da doi nam xuat ban thanh cong." << endl;
            else cout << "Doi nam xuat ban that bai." << endl;
            break;
        }

        case MENU_DOI_THE_LOAI_SACH_COMMAND_CODE: {
            cout << "The loai sach hien tai la " << thisBook->bookInfo.book_type << endl;
            cout << "Doi the loai sach: " << endl;

            if (editBookType(thisBook))
                cout << "Da doi the loai sach thanh cong." << endl;
            else cout << "Doi the loai sach that bai." << endl;

            break;
        }

        case MENU_DOI_GIA_SACH_COMMAND_CODE: {
            cout << "Gia sach hien tai la " << thisBook->bookInfo.price << endl;
            cout << "Cap nhat gia sach: " << endl;

            if (editBookPrice(thisBook))
                cout << "Da doi gia sach thanh cong." << endl;
            else {
                cout << "Doi gia sach that bai vi mot trong cac nguyen nhan sau:" << endl;
                cout << "- Gia sach am" << endl;
                cout << "- Lenh doi gia sach bi huy." << endl;
            }

            break;
        }
        default:
            cout << "Khong tim thay lenh " << command_code << endl;
    }
}

// Ham xac nhan xem nguoi dung co muon thuc hien hanh dong hay khong.
// Noi cach khac, ham nay giup nguoi dung thoat khoi mot hanh dong/
// bo khong lam tiep mot hanh dong.
bool confirmationBox() {
    cout << "Ban co muon thuc hien hanh dong nay?" << endl;
    cout << "1. Co, tiep tuc." << endl;
    cout << "2. Khong, huy." << endl;

    int answer = -1;
    do {
        if (!(cin >> answer)) {
            cin.clear();
            cin.ignore();
            continue;
        }
    } while (answer != 1 && answer != 2);
    
    if (answer == 2) cout << "Ban da huy hanh dong nay." << endl;

    return answer == 1;
}