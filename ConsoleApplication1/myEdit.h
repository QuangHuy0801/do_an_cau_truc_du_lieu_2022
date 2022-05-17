#pragma once
#include"mylib.h"
#include<iostream>
#include<string.h>

#define color_black 0x0000
#define color_darkblue 0x0001
#define color_darkgreen 0x0002
#define color_darkcyan 0x0003
#define color_darkred 0x0004
#define color_darkpink 0x0005
#define color_darkyellow 0x0006
#define color_darkwhite 0x0007
#define color_grey 0x0008
#define color_blue 0x0009
#define color_green 0x000a
#define color_cyan 0x000b
#define color_red 0x000c
#define color_pink 0x000d
#define color_yellow 0x000e
#define color_white 0x000f

#define colorbk_black 0x0000
#define colorbk_darkblue 0x0010
#define colorbk_darkgreen 0x0020
#define colorbk_darkcyan 0x0030
#define colorbk_darkred 0x0040
#define colorbk_darkpink 0x0050
#define colorbk_darkyellow 0x0060
#define colorbk_darkwhite 0x0070
#define colorbk_grey 0x0080
#define colorbk_blue 0x0090
#define colorbk_green 0x00a0
#define colorbk_cyan 0x00b0
#define colorbk_red 0x00c0
#define colorbk_pink 0x00d0
#define colorbk_yellow 0x00e0
#define colorbk_white 0x00f0


#define key_Up		-72
#define key_Down	-80
#define key_Left	-75
#define key_Right	-77
#define key_Enter   13
#define key_none	-1
#define key_bkspace 8
#define key_tab		9
#define key_esc     27
#define key_F11		133
#define key_F12		134
#define key_F1		-59
#define key_F2		-60
#define key_F3		-61
#define key_Space   32

#define lech_Top 5

using namespace std;
const int so_item = 4;
const int dong = 4;
const int cot = 60;
const int MAXLIST = 100;
const int so_item_ltc = 5;

//char itemloptinchi[so_item_ltc][70] = {
//	"Them Lop Tin Chi","Xoa Hoac Sua LTC","In Danh Sach LTC","In danh sach SV","Dang Ky Lop TC"
//};
char itemloptinchi[so_item_ltc][70] = {
	"           THEM LOP TIN CHI            ","          XOA SUA LOP TIN CHI           ","         IN DANH SACH LOP TIN CHI        " ,"DANH SACH SINH VIEN DANG KI LOP TIN CHI","          DANG KI LOP TIN CHI           "
};
//char menu[so_item][50] = {
//	"Lop Tin Chi","Sinh Vien","Mon Hoc","Diem"
//};
void Normal()
{
	SetBGColor(6);
	SetColor(7);

}
void Normal2()
{
	SetBGColor(color_green);
	SetColor(7);

}
void HighLight()
{
	SetColor(color_darkred);
	//SetBGColor(2);
}
void BGHightLight()
{
	SetBGColor(15);
	SetColor(1);
}
void Normal1()
{
	SetBGColor(color_darkwhite);
	SetColor(color_black);
}
int DrawMenu(int vt_item, int vt_y) //huu lam
{
	Normal();
	HideCursor(true);
	system("cls");
	SetBGColor(12);
	SetColor(15);
	gotoxy(67, 4);
	cout << "CHUONG TRINH QUAN LI DIEM SINH VIEN";
	Normal();
	char tuychon[so_item][50] = {
	"LOP TIN CHI","SINH VIEN","MON HOC","DIEM"
	};
	int i;
	for (i = 0; i < so_item; i++)
	{
		rectagle(cot, dong + i * 7 + lech_Top, 50, 4);
		gotoxy(cot + 20, dong + i * 7 + lech_Top + 2);
		cout << tuychon[i];
	}
	HighLight();

	// rectagle(l, t, r, b) *b so voi t
	rectagle(cot, dong + vt_y + lech_Top, 50, 4);
	gotoxy(cot + 20, dong + vt_y + lech_Top + 2);
	cout << tuychon[vt_item];
	int chon = vt_item;
	char kytu;
	do {
		kytu = GetKey();
		switch (kytu) {
		case key_Up:if (chon + 1 > 1)
		{
			Normal();
			rectagle(cot, dong + chon * 7 + lech_Top, 50, 4);
			gotoxy(cot + 20, dong + chon * 7 + lech_Top + 2);
			cout << tuychon[chon];
			chon--;
			HighLight();
			rectagle(cot, dong + chon * 7 + lech_Top, 50, 4);
			gotoxy(cot + 20, dong + chon * 7 + lech_Top + 2);
			cout << tuychon[chon];
		}
				   break;
		case key_Down:if (chon + 1 < so_item)
		{
			Normal();
			rectagle(cot, dong + chon * 7 + lech_Top, 50, 4);
			gotoxy(cot + 20, dong + chon * 7 + lech_Top + 2);
			cout << tuychon[chon];
			chon++;
			HighLight();
			rectagle(cot, dong + chon * 7 + lech_Top, 50, 4);
			gotoxy(cot + 20, dong + chon * 7 + lech_Top + 2);
			cout << tuychon[chon];
		}
					 break;
		case key_Enter:
		{
			clrscr();
			return chon + 1;
		}
		case key_esc:
		{
			chon = -1;
			return chon;
		}
		}
	} while (1);
}

int VeLopTinChi(char ltc[so_item_ltc][70])
{
	Normal();
	int chon = 0;
	int i;
	for (i = 0; i < so_item_ltc; i++)
	{
		rectagle(cot, dong + i * 7 + 3, 50, 4);
		gotoxy(cot + 5, dong + i * 7 + 3 + 2);
		cout << ltc[i];
	}
	HighLight();
	rectagle(cot, dong + 3, 50, 4);
	gotoxy(cot + 5, dong + 2 + 3);
	cout << ltc[0];
	char kytu;
	int cuchi;
	do {
		HideCursor(true);
		kytu = GetKey();
		cuchi = kytu;
		switch (cuchi) {
		case key_Up:if (chon + 1 > 1)
		{
			Normal();
			rectagle(cot, dong + chon * 7 + 3, 50, 4);
			gotoxy(cot + 5, dong + chon * 7 + 2 + 3);
			cout << ltc[chon];
			chon--;
			HighLight();
			rectagle(cot, dong + chon * 7 + 3, 50, 4);
			gotoxy(cot + 5, dong + chon * 7 + 2 + 3);
			cout << ltc[chon];
		}
				   break;
		case key_Down:if (chon + 1 < so_item_ltc)
		{
			Normal();
			rectagle(cot, dong + chon * 7 + 3, 50, 4);
			gotoxy(cot + 5, dong + chon * 7 + 2 + 3);
			cout << ltc[chon];
			chon++;
			HighLight();
			rectagle(cot, dong + chon * 7 + 3, 50, 4);
			gotoxy(cot + 5, dong + chon * 7 + 2 + 3);
			cout << ltc[chon];
		}
					 break;
		case key_Enter:
		{
			return chon + 1;
		}
		case key_esc:return 0;
		}
	} while (1);
}

void VeKhungDangNhap()
{
	gotoxy(0, 4);
	int a, b, size = 15;
	for (a = size / 2; a <= size; a = a + 2)
	{
		for (b = 1; b < size - a; b = b + 2)
			cout << " ";
		for (b = 1; b <= a; b++)
			cout << "$";
		for (b = 1; b <= size - a; b++)
			cout << " ";
		for (b = 1; b <= a - 1; b++)
			cout << "$";

		cout << "\n";
	}
	for (a = size; a >= 0; a--)
	{
		for (b = a; b < size; b++)
			cout << " ";
		for (b = 1; b <= ((a * 2) - 1); b++)
			cout << "$";

		cout << "\n";
	}
	HideCursor(true);
	gotoxy(58, 8);
	cout << "DANG NHAP VAO HE THONG";
	rectagle(45, 10, 50, 12);
	gotoxy(49, 12);
	cout << "Usename";
	rectagle(48, 13, 30, 2);
	gotoxy(49, 16);
	cout << "Password";
	rectagle(48, 17, 30, 2);
	SetBGColor(7);
	SetColor(7);
	rectagle(2, 30, 30, 4);
	SetColor(0);
	gotoxy(3, 31);

	cout << "TRAN THU DAT - N19DCCN036";
	gotoxy(3, 33);
	cout << "NGUYEN SON BA - N19DCCN013";
	Normal();
}
void Khung_lop_tin_chi()
{
	int x = 40, y = 4;
	Normal();
	//ve duong ngang
	for (int i = x + 1; i < x + 90; i++)
	{
		gotoxy(i, y);
		cout << char(196);
		gotoxy(i, y + 2);
		cout << char(196);
		gotoxy(i, y + 27);
		cout << char(196);
	}

	//ve duong doc
	for (int i = y + 1; i < y + 27; i++)
	{
		gotoxy(x, i);
		cout << char(179);
		gotoxy(x + 6, i);
		cout << char(179);
		gotoxy(x + 15, i);
		cout << char(179);
		gotoxy(x + 30, i);
		cout << char(179);
		gotoxy(x + 45, i);
		cout << char(179);
		gotoxy(x + 55, i);
		cout << char(179);
		gotoxy(x + 62, i);
		cout << char(179);
		gotoxy(x + 71, i);
		cout << char(179);
		gotoxy(x + 80, i);
		cout << char(179);
		gotoxy(x + 90, i);
		cout << char(179);
	}
	//4 goc
	gotoxy(x, y); cout << char(218);
	gotoxy(x, y + 27); cout << char(192);
	gotoxy(x + 90, y + 27); cout << char(217);
	gotoxy(x + 90, y); cout << char(191);
	//canh vuong
	gotoxy(x + 6, y);
	cout << char(194);
	gotoxy(x + 15, y);
	cout << char(194);
	gotoxy(x + 30, y);
	cout << char(194);
	gotoxy(x + 45, y);
	cout << char(194);
	gotoxy(x + 55, y);
	cout << char(194);
	gotoxy(x + 62, y);
	cout << char(194);
	gotoxy(x + 71, y);
	cout << char(194);
	gotoxy(x + 80, y);
	cout << char(194);

	gotoxy(x, y + 2);
	cout << char(195);
	gotoxy(x + 6, y + 2);
	cout << char(197);
	gotoxy(x + 15, y + 2);
	cout << char(197);
	gotoxy(x + 30, y + 2);
	cout << char(197);
	gotoxy(x + 45, y + 2);
	cout << char(197);
	gotoxy(x + 55, y + 2);
	cout << char(197);
	gotoxy(x + 62, y + 2);
	cout << char(197);
	gotoxy(x + 71, y + 2);
	cout << char(197);
	gotoxy(x + 80, y + 2);
	cout << char(197);
	gotoxy(x + 90, y + 2);
	cout << char(180);

	gotoxy(x + 6, y + 27);
	cout << char(193);
	gotoxy(x + 15, y + 27);
	cout << char(193);
	gotoxy(x + 30, y + 27);
	cout << char(193);
	gotoxy(x + 45, y + 27);
	cout << char(193);
	gotoxy(x + 55, y + 27);
	cout << char(193);
	gotoxy(x + 62, y + 27);
	cout << char(193);
	gotoxy(x + 71, y + 27);
	cout << char(193);
	gotoxy(x + 80, y + 27);
	cout << char(193);
	gotoxy(x + 1, y + 1); cout << "STT";
	gotoxy(x + 7, y + 1);
	cout << "MA LOP";
	gotoxy(x + 16, y + 1);
	cout << "MA MH";
	gotoxy(x + 31, y + 1);
	cout << "NIEN KHOA";
	gotoxy(x + 46, y + 1);
	cout << "NHOM";
	gotoxy(x + 56, y + 1);
	cout << "HOC KY";
	gotoxy(x + 64, y + 1);
	cout << "SV MAX";
	gotoxy(x + 73, y + 1);
	cout << "SV MIN";
	gotoxy(x + 81, y + 1);
	cout << "CON LAI";
}
void Xoa_khung_lop_tin_chi()
{
	int x = 40, y = 4;
	for (int i = y + 3; i < y + 27; i++)
	{
		gotoxy(x, i);
		cout << "                                                                                                 ";
	}
}
void Hien_thi_trang(int trang, int tongTrang, int x, int y)
{
	Normal();
	gotoxy(x + 2, y + 1);
	cout << "           ";
	rectagle(x, y, 10, 2);
	gotoxy(x + 2, y + 1);
	cout << trang << "/" << tongTrang;
}
void bang_xoa_sua(int x, int y)
{
	SetBGColor(12);
	SetColor(15);
	gotoxy(x, y);
	cout << "  F1 : SUA   ";
	gotoxy(x+20,y);
	cout<<"   F2 : XOA   ";
	Normal();
}
void Thong_bao(int x, int y, char* c)
{
	gotoxy(x, y);
	cout << c;
}
void khung_thong_bao(int x,int y,int w,int h,char *s)
{
	SetBGColor(colorbk_cyan);
	SetColor(color_darkwhite);
	rectagle(x, y, w, h);
	gotoxy(x + 8, y + 2);
	cout << s;
}
int bang_thong_bao(string s)
{
	Normal();
	HideCursor(true);
	BGHightLight();
	rectagle(60, 15, 58, 4);
	gotoxy(64, 16); cout << s;
	gotoxy(95, 18); cout << "YES";
	HighLight();
	gotoxy(80, 18); cout << "NO";
	char kitu;
	int luachon1 = 0;
	while (true)
	{
		kitu = GetKey();
		if (kitu == key_Right)
		{
			luachon1++;
			if (luachon1 >= 2)
				luachon1 = 1;
			else
			{
				BGHightLight();
				gotoxy(80, 18);
				cout << "NO";
				HighLight();
				gotoxy(95, 18);
				cout << "YES";
			}
		}
		else if (kitu == key_Left)
		{
			luachon1--;
			if (luachon1 < 0)
				luachon1 = 0;
			else
			{
				BGHightLight();
				gotoxy(95, 18);
				cout << "YES";
				HighLight();
				gotoxy(80, 18);
				cout << "NO";
			}
		}
		else if (kitu == key_Enter)
		{
			if (luachon1 == 0)
			{
				Normal();
				return 0;
			}
			else if (luachon1 == 1)
			{
				Normal();
				return 1;
			}
		}
	}
}
int bang_thong_bao_da_nhap(int x, int y, char* c)
{
	Normal();
	HideCursor(true);
	BGHightLight();
	rectagle(x, y, 58, 4);
	gotoxy(x+14, y+1); cout << c;
	gotoxy(x+25, y+3); cout << "YES";
	HighLight();
	gotoxy(x+20, y+3); cout << "NO";
	char kitu;
	int luachon1 = 0;
	while (true)
	{
		kitu = GetKey();
		if (kitu == key_Right)
		{
			luachon1++;
			if (luachon1 >= 2)
				luachon1 = 1;
			else
			{
				BGHightLight();
				gotoxy(x + 20, y + 3);
				cout << "NO";
				HighLight();
				gotoxy(x + 25, y + 3);
				cout << "YES";
			}
		}
		else if (kitu == key_Left)
		{
			luachon1--;
			if (luachon1 < 0)
				luachon1 = 0;
			else
			{
				BGHightLight();
				gotoxy(x + 25, y + 3);
				cout << "YES";
				HighLight();
				gotoxy(x + 20, y + 3);
				cout << "NO";
			}
		}
		else if (kitu == key_Enter)
		{
			if (luachon1 == 0)
			{
				Normal();
				return 0;
			}
			else if (luachon1 == 1)
			{
				Normal();
				return 1;
			}
		}
	}
}
void khung_danh_sach_sv_dk()
{
	//ve khung
	int x = 45, y = 5;
	rectagle(40, 4, 90, 25);
	for (int i = 0; i <= 80; i++)
	{
		HideCursor(true);
		SetBGColor(color_darkwhite);
		gotoxy(x + i, y);
		cout << ' ';
	}
	SetColor(color_black);
	gotoxy(x + 2, y); cout << "Masv";
	gotoxy(x + 2 + 15, y); cout << "Ho";
	gotoxy(x + 17 + 20, y); cout << "Ten";
	gotoxy(x + 37 + 15, y); cout << "Phai";
	gotoxy(x + 52 + 5, y); cout << "SDT";
	gotoxy(x + 57 + 15, y); cout << "Ma lop";
	Normal();
}
void xoa_khung_ds_sv_dk()
{
	Normal();
	int x = 45, y = 5;
	for (int i = 1; i <= 21; i++)
	{
		gotoxy(x, y + i);
		cout << "                                                                             ";
	}
}
void khung_mon_dki()
{
	int x = 45, y = 5;
	rectagle(40, 4, 90, 25);
	for (int i = 0; i <= 80; i++)
	{
		HideCursor(true);
		SetBGColor(color_darkwhite);
		gotoxy(x + i, y);
		cout << ' ';
	}
	SetColor(color_black);
	gotoxy(x + 4, y); cout << "MA MH";
	gotoxy(x + 11, y); cout << char(179);
	gotoxy(x + 25 , y); cout << "TEN MH";
	gotoxy(x + 41, y); cout << char(179);
	gotoxy(x + 47 , y); cout << "NHOM";
	gotoxy(x + 56 , y); cout << char(179);
	gotoxy(x + 61, y); cout << "SV DK";
	gotoxy(x + 69, y); cout << char(179);
	gotoxy(x + 71, y); cout << "Con Lai";
	Normal();
}
void xoa_khung_mon_dki()
{
	int x=40,y=4;
		for(int j=y+2;j<y+24;j++)
		{
			gotoxy(x+2, j);
			cout << "                                                                                 ";		
		}
}
void xoa_khung_nhap()
{
	int x=40,y=4;
		for(int j=y;j<y+34;j++)
		{
			gotoxy(x+2, j);
			cout << "                                                                                 ";		
		}
}
void bang_vao_ra(int x, int y)
{
	SetBGColor(12);
	SetColor(15);
	gotoxy(x, y);
	cout << "  ESC : Thoat   ";
	gotoxy(x+40,y);
	cout<<"   ENTER : Tiep tuc   ";
	Normal();
}
void xoa_bang_vao_ra(int x, int y)
{
	Normal();
	gotoxy(x, y);
	cout << "                     ";
	gotoxy(x+40,y);
	cout<<"                         ";
}
void xoa_ben_phai()
{
	int x=39,y=2;
		for(int j=y;j<y+38;j++)
		{
			gotoxy(x, j);
			cout << "                                                                                            ";
		}
}
void Ve_lai_sau_khi_sua_ltc(char ltc[so_item_ltc][70],int vt)
{
	HideCursor(true);
	for (int i = 0; i < so_item_ltc; i++)
	{
		rectagle(cot, dong + i * 7, 26, 4);
		gotoxy(cot + 4, dong + i * 7 + 2);
		cout << ltc[i];
	}
	HighLight();
	rectagle(cot, dong + vt * 7 , 26, 4);
	gotoxy(cot + 4 , dong + 7 * vt + 2);
	cout << ltc[vt];
	Normal();
}
