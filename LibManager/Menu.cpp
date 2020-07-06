#include"include.h"

// Chua dang nhap.
void nonLoggedInMenu() {
    

    // Xu ly dang nhap.
}

// Menu xu ly sua doi thong tin.
void editInfoMenu() {
    cout << "== Thay doi thong tin ==" << endl;
    cout << MENU_DOI_TEN_COMMAND_CODE << ". Doi ho va ten nguoi dung." << endl;
    cout << MENU_DOI_NGAY_SINH_COMMAND_CODE << ". Doi ngay sinh." << endl;
    cout << MENU_DOI_CMND_COMMAND_CODE << ". Doi CMND." << endl;
    cout << MENU_DOI_DIA_CHI_COMMAND_CODE << ". Doi dia chi." << endl;
    cout << MENU_DOI_GIOI_TINH_COMMAND_CODE << ". Chuyen gioi." << endl; // thay doi sau.
    cout << "Nhap lenh can thay doi: " << endl;
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
    /*cout << "=== Sua thong tin tai khoan   ===" << endl;
    cout << "1. Sua password" << endl;
    cout << "2. Sua thong tin ca nhan" << endl;
    cout << "3. Tao nguoi dung tu danh sach .csv" << endl;
    cout << "4. Chinh sua quyen cho nguoi dung" << endl;
    cout << "=== Ket thuc phien lam viec ===" << endl;
    cout << "5. Dang xuat khoi he thong." << endl;*/
}

void quanlyMenu() {
    cout << "== Cac chuc nang nang cao cho quan ly ==" << endl;
}

void chuyenvienMenu() {
    cout << "== Cac chuc nang nang cao cho chuyen vien ==" << endl;
}