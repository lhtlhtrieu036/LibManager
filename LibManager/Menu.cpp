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
        int editInfoCommand = -1; cin >> editInfoCommand;
        switch (editInfoCommand) {
            case MENU_XEM_THONG_TIN_COMMAND_CODE:
                getInfoMenu(user_session_info);
                break;

            case MENU_DOI_CMND_COMMAND_CODE:
                cout << "So CMND hien tai cua ban la: " << user_session_info->so_CMND << endl;
                cout << "Doi so CMND:" << endl;
                if (editUserCMND(user_session_info)) {
                    cout << "Da doi CMND thanh cong. Xin vui long dang nhap lai." << endl;
                    logUserOut(account_session_info, user_session_info);
                }
                else cout << "CMND khong hop le." << endl;

                break;
            
            case MENU_DOI_TEN_COMMAND_CODE:
                cout << "Ten cua ban hien tai la: " << user_session_info->ho_Ten << endl;
                cout << "Doi ten: " << endl;
                break;

            case MENU_DOI_DIA_CHI_COMMAND_CODE:
                cout << "Dia chi cua ban hien tai la: " << user_session_info->dia_Chi << endl;
                cout << "Doi dia chi: " << endl;
                break;

            case MENU_DOI_GIOI_TINH_COMMAND_CODE:
                cout << "Gioi tinh cua ban hien tai la: " << user_session_info->gioi_Tinh << endl;
                cout << "Doi gioi tinh: " << endl;
                break;

            case MENU_DOI_NGAY_SINH_COMMAND_CODE:
                cout << "Ngay sinh cua ban hien tai la: " << user_session_info->ngay_Sinh << endl;
                cout << "Doi ngay sinh: " << endl;
                break;

            default:
                cout << "Khong tim thay chuc nang nay." << endl;
        }
    
}