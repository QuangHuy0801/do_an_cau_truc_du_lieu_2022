#include<iostream>
#include"myEdit.h"
#include"handleFile.h"
#include "xu_ly_sinh_vien.h"
#include "xu_ly_mon_hoc.h"
#include "xu_li_diem.h"
#include "xu_li_lop_tin_chi.h" 
using namespace std;

int main()
{
	HideCursor(true);
	SetSizeWindows(1200, 700);
	RemoveScrollbar();
	int luachon = 1, vt_y = 0;
	while (true)
	{
		luachon = DrawMenu(luachon - 1, vt_y);
		if (luachon == 1)
		{
			menu_ltc();
			vt_y = 0;
		}
		else if (luachon == 2)
		{
			//SINH VIEN
			menu_sinhvien();
			vt_y = 7;
		}
		else if (luachon == 3)
		{
			menu_monhoc();
			vt_y = 14;
		}
		else if (luachon == 4)
		{
			//DIEM
			menu_diem();
			vt_y = 21;
		}
		else if (luachon == -1)
		{
			//THOAT
			system("cls");
			break;
		}
	}
}