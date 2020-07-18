#include"include.h"

// Chua dang nhap.
void nonLoggedInMenu() {
    

    // Xu ly dang nhap.
}

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
    cout << EXIT_COMMAND_CODE << ". Dang xuat va thoat khoi he thong." << endl;
}

// Menu cho admin
void adminMenu() {
    cout << "== Cac chuc nang nang cao cho admin ==" << endl;
    cout << MENU_THEM_USER_COMMAND_CODE << ". Tao nguoi dung tu danh sach .csv" << endl;
    cout << MENU_PHAN_QUYEN_USER_COMMAND_CODE << ". Phan quyen cho nguoi dung" << endl;
}

void quanlyMenu() {
    cout << "== Cac chuc nang nang cao cho quan ly ==" << endl;
}

void chuyenvienMenu() {
    cout << "== Cac chuc nang nang cao cho chuyen vien ==" << endl;
}

// Controller (xu ly) cho cac menu
void getInfoMenu(user_info* user_session_info) {
    cout << "== Thong tin cua ban ==" << endl;
    cout << "Ho va ten: " << user_session_info->ho_Ten << endl;
    cout << "Dia chi: " << user_session_info->dia_Chi << endl;
    cout << "CMND: " << user_session_info->so_CMND << endl;
    cout << "Ngay sinh: " << user_session_info->ngay_Sinh << endl;
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

            editUserGioiTinh(user_session_info);
            cout << "Da doi gioi tinh thanh cong. Xin vui long dang nhap lai de luu moi thay doi." << endl;

            break;

        case MENU_DOI_NGAY_SINH_COMMAND_CODE:
            cout << "Ngay sinh cua ban hien tai la: " << user_session_info->ngay_Sinh << endl;
            cout << "Doi ngay sinh: " << endl;

            editUserNgaySinh(user_session_info);
            cout << "Da doi ngay sinh thanh cong. Xin vui long dang nhap lai de luu moi thay doi." << endl;

            break;

        default:
            cout << "Khong tim thay chuc nang nay." << endl;
    }
}