#include "account.h"

void read_user_data(ifstream& p, user_info& a)
{
	if (p.fail())
	{
		cout << " KHONG MO DUOC FILE HOAC LOI!";
	}
	else
	{
		char temp[255];
		p.getline(temp, 255);
		string line = temp;
		int n = strlen(temp);
		int i;
		char id_kieu_char[20] = { 0 };
		for (i = 0; i < n; i++)
		{
			if (temp[i] != ',')
			{
				id_kieu_char[i] = temp[i];
			}
			else
			{
				id_kieu_char[i] = NULL; break;
			}
		};

		a.ID = int(strtod(id_kieu_char, NULL));
		for (int i1 = 0; i1 < NAME_MAX; i1++)
		{
			i++;
			if (temp[i] != ',')
			{
				a.ho_Ten[i1] = temp[i];
			}
			else
			{
				a.ho_Ten[i1] = NULL; break;
			}
		};

		for (int i2 = 0; i2 < BIRTH_DAY; i2++)
		{
			i++;
			if (temp[i] != ',')
			{
				a.ngay_Sinh[i2] = temp[i];
			}
			else
			{
				a.ngay_Sinh[i2] = NULL; break;
			}
		};

		for (int i3 = 0; i3 < CMND; i3++)
		{
			i++;
			if (temp[i] != ',')
			{
				a.so_CMND[i3] = temp[i];
			}
			else
			{
				a.so_CMND[i3] = NULL; break;
			}
		};

		for (int i4 = 0; i4 < ADDRESS; i4++)
		{
			i++;
			if (temp[i] != ',')
			{
				a.dia_Chi[i4] = temp[i];
			}
			else
			{
				a.dia_Chi[i4] = NULL; break;
			}
		};

		for (int i5 = 0; i5 < SEX; i5++)
		{
			i++;
			if (temp[i] != ',')
			{
				a.gioi_Tinh[i5] = temp[i];
			}
			else
			{
				a.gioi_Tinh[i5] = NULL; break;
			}
		};

		char tinh_trang[2] = { 0 };
		for (int i6 = 0; i6 < 2; i6++)
		{
			i++;
			tinh_trang[i6] = temp[i];
		};
		a.tinh_Trang = bool(strtod(tinh_trang, NULL));

	};

};

void  read_Mang_User(ifstream& p, user_info* a, int& n)
{
	if (p.fail())
	{
		cout << "ERROR";
	}
	else
	{
		char temp[255];
		p.getline(temp, 255);
		//string line = temp;
		n = 0;
		do
		{
			read_user_data(p, *(a + n));
			if (p.eof())
			{
				break;
			};
			n++;
		} while (!p.eof());
		p.close();
	}
};