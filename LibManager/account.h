#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

// Username & password
#define USERNAME_MAX_SIZE 30
#define USERNAME_MIN_SIZE 1
#define PASSWORD_MAX_SIZE 30
#define PASSWORD_MIN_SIZE 8

// Phan quyen nguoi dung
#define USER_ADMIN  1
#define USER_QUANLY 2
#define USER_CVIEN  3

// Thong tin nguoi dung
#define NAME_MAX 30
#define BIRTH_DAY 12
#define CMND 10
#define ADDRESS 50
#define SEX 4


struct user_info
{
	int ID;
	char ho_Ten[NAME_MAX];
	char ngay_Sinh[BIRTH_DAY];
	char so_CMND[CMND];
	char dia_Chi[ADDRESS];
	char gioi_Tinh[SEX];
	bool tinh_Trang;

};

struct account 
{

	int ID;
	char user_name[USERNAME_MAX_SIZE];
	char pass_word[PASSWORD_MAX_SIZE];

};



#endif

