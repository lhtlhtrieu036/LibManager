#pragma once
#ifndef MENU_H
#define MENU_H
#endif // !MENU_H

#define EXIT_COMMAND_CODE    3817 // E - X - I - T
#define LOGOUT_COMMAND_CODE  6969 // nonsense, se set gia tri khac trong tuong lai

// Chua dang nhap
void nonLoggedInMenu();

// Menu cho admin.
void adminMenu();

// Menu cho quan ly.
void quanlyMenu();

// Menu cho chuyen vien.
void chuyenvienMenu();
