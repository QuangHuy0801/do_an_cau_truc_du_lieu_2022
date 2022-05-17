#pragma once
#include "mylib.h" 
#include "myEdit.h"
#include "ctdl.h"
#include <math.h>
#include <string>
#include "handleFile.h"
#include<stdio.h>
using namespace std;
int so_trang(float);
void tao_khung_sinh_vien(ds_sinh_vien&);
void in_xoa_sua_danh_sach_sv(DS_SINH_VIEN&, bool);
void them_sua_sinh_vien(ds_sinh_vien&, NODE_SINH_VIEN*, bool);
void HighLight_SV(NODE_SINH_VIEN*, int, int, int);
void Normal_SV(NODE_SINH_VIEN*, int, int y, int);
int Ma_Lop(ds_sinh_vien, char*);
void ds_theo_ma_lop(ds_sinh_vien, ds_sinh_vien&, char*);
bool so_sanh(char*, char*);
void flashSort(DS_SINH_VIEN&);
NODE_SINH_VIEN* get_SV(NODE_SINH_VIEN*, int);
bool search_masv(DS_SINH_VIEN, char*);

#define item 2
#define item1 6



void menu_sinhvien()
{
	DS_SINH_VIEN ds_sv;
	Doc_file_sinh_vien(ds_sv);
	tao_khung_sinh_vien(ds_sv);
}
//khung ban dau
void tao_khung_sinh_vien(ds_sinh_vien& ds)
{
velai:
	system("cls");
	gotoxy(75, 4);
	SetBGColor(12);
	SetColor(15);
	cout << "XU LY SINH VIEN";
	Normal();
	HideCursor(true);
	char menu[item][30] = {
		"In sinh vien theo lop",
		"   Xu li sinh vien"
	};
	int x = 65, y = 10, d = 0, width = 35, heigh = 4;
	HighLight();
	for (int i = 0; i < item; i++) {
		rectagle(x, y + d, width, heigh);
		gotoxy(x + 7, y + d + 2);
		d += 7;
		cout << menu[i];
		Normal();
	}
	int luachon = 0;
	d = 7;
	char kitu;
	gotoxy(x, y);
	while (true)
	{
		HideCursor(true);
		kitu = GetKey();
		if (kitu == key_esc) return;
		else if (kitu == key_Down)
		{
			luachon++;
			if (luachon >= item)
			{
				luachon = 0;
				y -= d * (item - 1);

				Normal();
				rectagle(x, y + d * (item - 1), width, heigh);
				gotoxy(x + 7, y + d * (item - 1) + 2);
				cout << menu[item - 1];

				HighLight();
				rectagle(x, y, width, heigh);
				gotoxy(x + 7, y + 2);
				cout << menu[luachon];
			}
			else {
				y += d;

				Normal();
				rectagle(x, y - d, width, heigh);
				gotoxy(x + 7, y - d + 2);
				cout << menu[luachon - 1];

				HighLight();
				rectagle(x, y, width, heigh);
				gotoxy(x + 7, y + 2);
				cout << menu[luachon];
			}
		}
		else if (kitu == key_Up)
		{
			luachon--;
			if (luachon < 0)
			{
				luachon = item - 1;
				y += d * (item - 1);

				Normal();
				rectagle(x, y - d * (item - 1), width, heigh);
				gotoxy(x + 7, y - d * (item - 1) + 2);
				cout << menu[0];

				HighLight();
				rectagle(x, y, width, heigh);
				gotoxy(x + 7, y + 2);
				cout << menu[luachon];
			}
			else {
				y -= d;

				Normal();
				rectagle(x, y + d, width, heigh);
				gotoxy(x + 7, y + d + 2);
				cout << menu[luachon + 1];

				HighLight();
				rectagle(x, y, width, heigh);
				gotoxy(x + 7, y + 2);
				cout << menu[luachon];
			}
		}
		else if (kitu == key_Enter)
		{
			clrscr();
			if (luachon == 0)//in_danh_sach
			{
				DS_SINH_VIEN ds_lop;
				char malop[MAX_MALOP] = "";
				int check = Ma_Lop(ds, malop);
				if (check == 1)
				{
					ds_theo_ma_lop(ds, ds_lop, malop);
					in_xoa_sua_danh_sach_sv(ds_lop, false);
				}
			}
			else if (luachon == 1)
			{
				in_xoa_sua_danh_sach_sv(ds, true);
			}
			goto velai;
		}
	}
}






NODE_SINH_VIEN* get_SV(NODE_SINH_VIEN* sv, int vt)
{
	NODE_SINH_VIEN* temp = sv;
	for (int i = 0; i < vt; i++)
		temp = temp->pNext;
	return temp;
}

NODE_SINH_VIEN* get_SV_theo_ten(NODE_SINH_VIEN* sv, char *x)
{
	NODE_SINH_VIEN* temp = sv;
	while( temp != NULL) {
		if (strcmp(temp->data.TEN, x) < 0) {
			temp = temp->pNext;
			continue;
		}
		return temp;
	}
	return NULL;
}
//in ds cua 1 trang
void ds_theo_ma_lop(ds_sinh_vien ds, ds_sinh_vien& ds_lop, char* malop)
{
	for (NODE_SINH_VIEN* p = ds.pHead; p != NULL; p = p->pNext)
	{
		if (strcmp(p->data.MALOP, malop) == 0)
		{
			NODE_SINH_VIEN* sv = new NODE_SINH_VIEN;
			sv->pNext = NULL;
			sv->data = p->data;
			them_sinhvien(ds_lop, sv);
		}
	}
}

bool Search_MaLop(ds_sinh_vien ds, char* malop)
{
	for (NODE_SINH_VIEN* i = ds.pHead; i != NULL; i = i->pNext)
		if (strcmp(malop, i->data.MALOP) == 0)
			return true;
	return false;
}

int Ma_Lop(ds_sinh_vien ds, char* malop)
{
	Normal();
	char kitu;
	int x = 70, y = 12, f;
dien:
	HideCursor(false);
	f = 0;
	rectagle(x, y, 40, 4);
	gotoxy(x + 2, y + 2);
	cout << "Nhap ma lop: ";
	while (true)
	{
		kitu = GetKey();
		if (!dieukien(kitu) && chu_so(kitu) && f < MAX_MALOP)
		{
			malop[f] = chu_in_hoa(kitu);
			cout << malop[f++];
		}
		else if (kitu == key_bkspace && f > 0)
		{
			malop[--f] = ' ';

			gotoxy(wherex() - 1, wherey());
			cout << ' ';
			gotoxy(wherex() - 1, wherey());
		}
		else if (kitu == key_Enter)
		{
			malop[f] = '\0';
			if (f == 0)
			{
				HideCursor(true);
				gotoxy(x, y + 10);
				cout << "Ban can dien thong tin !!!";
				Sleep(500);
				gotoxy(x, y + 10);
				cout << "                            ";
				goto dien;
			}
			else if (Search_MaLop(ds, malop) == false)
			{
				HideCursor(true);
				gotoxy(x, y + 10);
				cout << "Ma lop khong ton tai !!!";
				Sleep(500);
				gotoxy(x, y + 10);
				cout << "                          ";
				goto dien;
			}
			else if (Search_MaLop(ds, malop) == true)
			{
				return 1;
			}
		}
		else if (kitu == key_esc)
		{
			Normal();
			HideCursor(true);
			return 0;
		}
	}
}

 
 
 
 
 
void HighLight_SV(NODE_SINH_VIEN* p, int x, int y, int stt)
{
	gotoxy(x - 7, y);
	BGHightLight();
	cout << "                                                                                              ";
	SetColor(color_black);
	gotoxy(x, y);
	cout << char(179) << "             " << char(179) << "                   " << char(179) << "              " << char(179) << "         " << char(179) << "              " << char(179);
	gotoxy(x - 5, y);			cout << stt;
	gotoxy(x + 2, y);			cout << p->data.MASV;
	gotoxy(x + 2 + 15, y);		cout << p->data.HO;
	gotoxy(x + 17 + 20, y);		cout << p->data.TEN;
	gotoxy(x + 37 + 15, y);		cout << p->data.PHAI;
	gotoxy(x + 52 + 5 + 5, y);  cout << p->data.SDT;
	gotoxy(x + 57 + 15 + 5, y); cout << p->data.MALOP;
}

void Normal_SV(NODE_SINH_VIEN* p, int x, int y, int stt)
{
	gotoxy(x - 7, y);
	Normal();
	cout << "                                                                                              ";
	Normal();
	gotoxy(x, y);
	cout << char(179) << "             " << char(179) << "                   " << char(179) << "              " << char(179) << "         " << char(179) << "              " << char(179);
	gotoxy(x - 5, y);			cout << stt;
	gotoxy(x + 2, y);			cout << p->data.MASV;
	gotoxy(x + 2 + 15, y);		cout << p->data.HO;
	gotoxy(x + 17 + 20, y);		cout << p->data.TEN;
	gotoxy(x + 37 + 15, y);		cout << p->data.PHAI;
	gotoxy(x + 52 + 5 + 5, y);  cout << p->data.SDT;
	gotoxy(x + 57 + 15 + 5, y); cout << p->data.MALOP;
}

int tong_sv(NODE_SINH_VIEN* sv) {
	int i = 0;
	NODE_SINH_VIEN* p = sv;
	while (p!=NULL) {
		p = p->pNext;
		i++;
	}
	return i;
}



void in_xoa_sua_danh_sach_sv(DS_SINH_VIEN& ds_sv, bool mode)
{
tudau:
	flashSort(ds_sv);
	NODE_SINH_VIEN* sv = ds_sv.pHead;
	int luive = 0;
timkiem:
	int stt = 1, x = 45, y = 8, trang = 1, luachon = 0;
	int tong_trang;
	tong_trang = so_trang(1.0 * tong_sv(sv) / 20);
	NODE_SINH_VIEN* STACK[100];
	int sp = -1;
	NODE_SINH_VIEN* h_light;
	if (mode == true)
	{
		SetBGColor(12);
		SetColor(15);
		gotoxy(70, 35);
		cout << "F3: THEM";
		gotoxy(50, 35);
		cout << "F1: SUA";
		gotoxy(50, 37);
		cout << "F2: XOA";
		gotoxy(120, 37);
		cout << "ENTER: TIM KIEM";
		gotoxy(120, 35);
		cout << "ESC: THOAT";
	}
	gotoxy(72, 4);
	SetBGColor(12);
	SetColor(15);
	if (mode == true) cout << "DANH SACH TAT CA SINH VIEN";
	else cout << "DANH SACH SINH VIEN CUA LOP " << ds_sv.pHead->data.MALOP;
chuyen_trang:
	xoa_man_hinh();
	Normal();
	HideCursor(true);
	gotoxy(137, 32);
	cout << trang << '/' << tong_trang;
	rectagle(x - 11, y - 2, 97 + 5, 25);
	gotoxy(x - 7, y);
	SetBGColor(color_darkwhite);
	cout << "                                                                                              ";
	SetColor(color_black);
	gotoxy(x - 5, y);			cout << "STT  " << char(179);
	gotoxy(x + 2, y);			cout << "Masv" << "        " << char(179);
	gotoxy(x + 2 + 15, y);		cout << "Ho" << "               " << char(179);
	gotoxy(x + 17 + 20, y);		cout << "Ten" << "         " << char(179);
	gotoxy(x + 37 + 15, y);		cout << "Phai" << "   " << char(179);
	gotoxy(x + 52 + 5 + 5, y);	cout << "SDT" << "         " << char(179);
	gotoxy(x + 57 + 15 + 5, y);	cout << "Ma lop";
	Normal();
	if (tong_sv(sv) == 0)
	{
		gotoxy(80, 29);
		cout << "DANH SACH TRONG !!!";
		Sleep(1000);
		return;
	}
	gotoxy(x, y + 1);
	cout << char(179) << "             " << char(179) << "                   " << char(179) << "              " << char(179) << "         " << char(179) << "              " << char(179);
	STACK[++sp] = sv;
	int y1 = 1, count = 0;
	for (; sv != NULL && count < 20; sv = sv->pNext)
	{
		count++;
		gotoxy(x, y + (++y1));
		cout << char(179) << "             " << char(179) << "                   " << char(179) << "              " << char(179) << "         " << char(179) << "              " << char(179);
		gotoxy(x - 5, y + y1);					cout << stt++;
		gotoxy(x + 2, y + y1);					cout << sv->data.MASV;
		gotoxy(x + 2 + 15, y + y1);				cout << sv->data.HO;
		gotoxy(x + 17 + 20, y + y1);			cout << sv->data.TEN;
		gotoxy(x + 37 + 15, y + y1);			cout << sv->data.PHAI;
		gotoxy(x + 52 + 5 + 5, y + y1);			cout << sv->data.SDT;
		gotoxy(x + 57 + 15 + 5, y + y1);		cout << sv->data.MALOP;
	}
	if (mode == true)
	{
		h_light = get_SV(STACK[sp], luachon);
		HighLight_SV(h_light, x, y + 2 + luachon, stt - count + luachon);
	}
	char kitu;
	while (true)
	{
		kitu = GetKey();
		if (kitu == key_Down && mode == true)
		{
			luachon++;
			if (luachon >= count) {
				luachon = count - 1;
			}
			else
			{
				h_light = get_SV(STACK[sp], luachon - 1);
				Normal_SV(h_light, x, y + 1 + luachon, stt - count + luachon - 1);
				HighLight_SV(h_light->pNext, x, y + 1 + luachon + 1, stt - count + luachon);
			}
		}
		else if (kitu == key_Up && mode == true)
		{
			luachon--;
			if (luachon < 0) {
				luachon = 0;
			}
			else
			{
				h_light = get_SV(STACK[sp], luachon);
				Normal_SV(h_light->pNext, x, y + 1 + luachon + 2, stt - count + luachon + 1);
				HighLight_SV(h_light, x, y + 1 + luachon + 1, stt - count + luachon);
			}
		}
		else if (kitu == key_Right)
		{
			trang += 1;
			if (trang > tong_trang)	trang = tong_trang;
			else
			{
				luachon = 0;
				Normal();
				goto chuyen_trang;
			}
		}
		else if (kitu == key_Left)
		{
			trang -= 1;
			if (trang < 1)	trang = 1;
			else
			{
				luachon = 0;
				stt = stt - count - 20;
				sv = STACK[(--sp)--];
				Normal();
				goto chuyen_trang;
			}
		}
		else if (kitu == key_F2 && mode == true) // xoa sv
		{
			h_light = get_SV(STACK[sp], luachon);
			string thong_bao;
			int check;
			if (check_sv_dk(h_light->data.MASV))
			{
				thong_bao = "Sinh vien da duoc dang ki lop tin chi, ban van muon xoa ?";
				check = bang_thong_baoo(thong_bao, 60, 15, 64, 4, 15, 16);
			}
			else
			{
				thong_bao = "Ban co that su muon xoa ?";
				check = bang_thong_baoo(thong_bao, 70, 15, 34, 4, 7, 6);
			}
			if (check == 0)
			{

				if (h_light == STACK[sp]) STACK[sp] = STACK[sp]->pNext;
				xoa_sv_ltc(h_light->data.MASV);
				xoa_sinhvien(ds_sv, h_light);

				if ((stt - count - 1 + luachon) >= ds_sv.tongSV)
				{
					luachon--;
					if (luachon < 0)
					{
						stt = stt - 20;
						luachon = 19;
						sp--;
						trang--;
					}
				}
				Ghi_file(ds_sv);
			}
			sv = STACK[sp--];
			stt -= count;
			goto chuyen_trang;
		}
		else if (kitu == key_F1 && mode == true) // sua sv
		{
			h_light = get_SV(STACK[sp], luachon);
			xoa_man_hinh();
			them_sua_sinh_vien(ds_sv, h_light, false);
			stt -= count;
			sv = STACK[sp--];
			goto chuyen_trang;
		}
		else if (kitu == key_F3 && mode == true) // them sv
		{
			NODE_SINH_VIEN* p = new NODE_SINH_VIEN;
			p->pNext = NULL;
			them_sua_sinh_vien(ds_sv, p, true);
			goto tudau;
		}
		else if (kitu == key_Enter && mode == true) // sua sv
		{
			Normal();
			char kitu;
			int x = 120, y = 3, f;
			HideCursor(false);
			f = 0;
			rectagle(x, y, 20, 2);
			gotoxy(x + 2+f, y +1);
			char finder[MAX_TEN]=" ";
			while (true)
			{
				kitu = GetKey();
				if (kitu == key_esc)
				{
					xoa_man_hinh();
					goto tudau;
				}
				else if (!dieukien(kitu) && f < MAX_MAMH)
				{

					if (chu(kitu)) {
						if (f == 0)
							finder[f] = chu_in_hoa(kitu);
						else
							finder[f] = chu_in_thuong(kitu);
						cout << finder[f++];
					}
					else if (kitu == key_Space && finder[f - 1] != key_Space && f != 0) {
						finder[f++] = kitu;
						cout << kitu;

					}
				}
				else if (kitu == key_bkspace && f > 0)
				{
					finder[--f] = ' ';
					gotoxy(wherex() - 1, wherey());
					cout << ' ';
					gotoxy(wherex() - 1, wherey());
				}
				else if (kitu == key_Enter)
				{
					sv = get_SV_theo_ten(ds_sv.pHead, finder);
					luive = true;
					goto timkiem;
				}
			}
		}
		else if (kitu == key_esc)
		{
			if (luive == false) {
				Normal();
				for (int i = 0; i <= 3; i++)
				{
					gotoxy(82, 3+i);
					cout << "                                                                           ";
				}
				gotoxy(50, 35);
				cout << "                                                     ";
				gotoxy(50, 37);
				cout << "             ";
				return;
			}
			else {
				luive = false;
				xoa_man_hinh();
				goto tudau;
			}
		}
	}
}

void them_sua_sinh_vien(ds_sinh_vien& ds, NODE_SINH_VIEN* p, bool mode)
{
	int x = 60, y = 10, width = 30, heigh = 2;
	char kitu;
	int luachon;
	char B[MAX_HO], C[MAX_TEN], D[MAX_PHAI], E[MAX_SDT], F[MAX_MALOP];
	int a, b, c, d, e, f;
	if (mode == false)
	{
		//strcpy(A, p->data.MASV);
		strcpy_s(B, p->data.HO);
		strcpy_s(C, p->data.TEN);
		strcpy_s(D, p->data.PHAI);
		strcpy_s(E, p->data.SDT);
		strcpy_s(F, p->data.MALOP);
	}
reset:
	Normal();
	clrscr();
	HideCursor(false);
	SetBGColor(color_green);
	SetColor(color_green);
	rectagle(x - 5, y - 3, 60, 21);
	char menu[item1][30] = {
		"Ma sinh vien",
		"Ho",
		"Ten",
		"Phai",
		"So dien thoai",
		"Ma lop"
	};
	for (int i = 0, j = 0; i < item1; i++, j += 3) {
		gotoxy(x, y + j);
		SetColor(color_white);
		cout << menu[i];
		SetColor(color_white);
		rectagle(x + 20, y + j - 1, width, heigh);
	}
	a = 0; b = 0; c = 0; d = 0; e = 0; f = 0;
	Normal2();
	gotoxy(x + 28, y + 9);
	cout << "Nam";
	Normal2();
	gotoxy(x + 38, y + 9);
	cout << "Nu";
	if (mode == false)// in thong tin SV can sua
	{
		a = strlen(p->data.MASV); b = strlen(p->data.HO); c = strlen(p->data.TEN); d = strlen(p->data.PHAI); e = strlen(p->data.SDT); f = strlen(p->data.MALOP);
		gotoxy(x + 22, y);   cout << p->data.MASV;
		gotoxy(x + 22, y + 3);   cout << p->data.HO;
		gotoxy(x + 22, y + 6);  cout << p->data.TEN;
		//gotoxy(x + 22, y + 9);  cout << p->data.PHAI;
		gotoxy(x + 22, y + 12);   cout << p->data.SDT;
		gotoxy(x + 22, y + 15);  cout << p->data.MALOP;
		//----------------------------
		if (d == 3)
		{
			luachon = 0;
			gotoxy(x + 28, y + 9);
			BGHightLight();
			cout << "Nam";
			Normal2();
			gotoxy(x + 38, y + 9);
			cout << "Nu";
			gotoxy(x + 28, y + 9);
		}							//hien gioi tinh
		else if (d == 2)
		{
			luachon = 1;
			gotoxy(x + 38, y + 9);
			BGHightLight();
			cout << "Nu";
			Normal2();
			gotoxy(x + 28, y + 9);
			cout << "Nam";
			gotoxy(x + 38, y + 9);
		}
		//---------------------------
	}
	if (mode == false)
		goto Ho;
Masv:Normal2();
	gotoxy(x + 22 + a, y);
	while (true)
	{
		kitu = GetKey();
		if (!dieukien(kitu) && chu_so(kitu) && kitu != key_Space && a < MAX_MASV)
		{
			p->data.MASV[a] = chu_in_hoa(kitu);
			cout << p->data.MASV[a++];
		}
		else if (kitu == key_bkspace && a > 0)
		{
			p->data.MASV[--a] = ' ';
			gotoxy(wherex() - 1, wherey());
			cout << ' ';
			gotoxy(wherex() - 1, wherey());
		}
		else if (kitu == key_Down)
			goto Ho;
		else if (kitu == key_Up) goto Malop;
		else if (kitu == key_esc) goto Out;
		else if (kitu == key_Enter) goto Them;
	}
Ho:Normal2();
	gotoxy(x + 22 + b, y + 3);
	while (true)
	{
		kitu = GetKey();
		if (kitu == key_esc) goto Out;
		else if (!dieukien(kitu) && b < MAX_HO)
		{
			if (chu(kitu)) {
				p->data.HO[b] = kitu;
				if (p->data.HO[b - 1] == ' ' && p->data.HO[b] >= 'a' && p->data.HO[b] <= 'z')
					p->data.HO[b] = chu_in_hoa(p->data.HO[b]);
				else if (p->data.HO[b - 1] != ' ' && p->data.HO[b] >= 'A' && p->data.HO[b] <= 'Z')
					p->data.HO[b] = chu_in_thuong(p->data.HO[b]);
				p->data.HO[0] = chu_in_hoa(p->data.HO[0]);
				cout << p->data.HO[b++];
			}
			else if (kitu == key_Space && p->data.HO[b - 1] != key_Space && b != 0) {
				p->data.HO[b++] = kitu;
				cout << kitu;
			}
		}
		else if (kitu == key_bkspace && b > 0)
		{
			p->data.HO[--b] = ' ';
			gotoxy(wherex() - 1, wherey());
			cout << ' ';
			gotoxy(wherex() - 1, wherey());
		}
		else if (kitu == key_Down) goto Ten;
		else if (kitu == key_Up)
		{
			if (mode == true) goto Masv;
			else goto Malop;
		}
		else if (kitu == key_Enter) goto Them;
	}
Ten:Normal2();
	gotoxy(x + 22 + c, y + 6);
	while (true)
	{
		kitu = GetKey();
		if (!dieukien(kitu) && chu(kitu) && c < MAX_TEN)
		{
			p->data.TEN[c] = chu_in_thuong(kitu);
			p->data.TEN[0] = chu_in_hoa(p->data.TEN[0]);
			cout << p->data.TEN[c++];
		}
		else if (kitu == key_bkspace && c > 0)
		{
			p->data.TEN[--c] = ' ';

			gotoxy(wherex() - 1, wherey());
			cout << ' ';
			gotoxy(wherex() - 1, wherey());
		}
		else if (kitu == key_Down)
			goto Phai;
		else if (kitu == key_Up) goto Ho;
		else if (kitu == key_esc) goto Out;
		else if (kitu == key_Enter) goto Them;
	}
Phai:Normal2();
	HideCursor(true);
	if (d == 3)
	{
		gotoxy(x + 28, y + 9);
		BGHightLight();
		cout << "Nam";
		Normal2();
		gotoxy(x + 38, y + 9);
		cout << "Nu";
		gotoxy(x + 28, y + 9);
	}
	else if (d == 2)
	{
		gotoxy(x + 38, y + 9);
		BGHightLight();
		cout << "Nu";
		Normal2();
		gotoxy(x + 28, y + 9);
		cout << "Nam";
		gotoxy(x + 38, y + 9);
	}
	while (true)
	{
		kitu = GetKey();
		if ((kitu == key_Right && d == 0) || (kitu == key_Left && d == 2))
		{
			d = 3;
			gotoxy(x + 38, y + 9);
			Normal2();
			cout << "Nu";
			gotoxy(x + 28, y + 9);
			BGHightLight();
			cout << "Nam";
			p->data.PHAI[0] = 'N';
			p->data.PHAI[1] = 'a';
			p->data.PHAI[2] = 'm';
		}
		else if ((kitu == key_Left && d == 0) || (kitu == key_Right && d == 3))
		{
			d = 2;
			gotoxy(x + 28, y + 9);
			Normal2();
			cout << "Nam";
			gotoxy(x + 38, y + 9);
			BGHightLight();
			cout << "Nu";
			p->data.PHAI[0] = 'N';
			p->data.PHAI[1] = 'u';
		}
		else if (kitu == key_Up)
		{
			Normal2();
			HideCursor(false);
			goto Ten;
		}
		else if (kitu == key_Down)
		{
			Normal2();
			HideCursor(false);
			goto Sdt;
		}
		else if (kitu == key_esc) goto Out;
		else if (kitu == key_Enter) goto Them;
	}
Sdt:Normal2();
	gotoxy(x + 22 + e, y + 12);
	while (true)
	{
		kitu = GetKey();
		if (!dieukien(kitu) && so(kitu) && e < MAX_SDT)
		{
			p->data.SDT[e++] = kitu;
			cout << kitu;
		}
		else if (kitu == key_bkspace && e > 0)
		{
			p->data.SDT[--e] = ' ';

			gotoxy(wherex() - 1, wherey());
			cout << ' ';
			gotoxy(wherex() - 1, wherey());
		}
		else if (kitu == key_Down)
			goto Malop;
		else if (kitu == key_Up) goto Phai;
		else if (kitu == key_esc) goto Out;
		else if (kitu == key_Enter) goto Them;
	}
Malop:
	Normal2();
	gotoxy(x + 22 + f, y + 15);
	while (true)
	{
		kitu = GetKey();
		if (!dieukien(kitu) && chu_so(kitu) && f < MAX_MALOP)
		{
			p->data.MALOP[f] = chu_in_hoa(kitu);
			cout << p->data.MALOP[f++];
		}
		else if (kitu == key_bkspace && f > 0)
		{
			p->data.MALOP[--f] = ' ';

			gotoxy(wherex() - 1, wherey());
			cout << ' ';
			gotoxy(wherex() - 1, wherey());
		}
		else if (kitu == key_Down)
		{
			if (mode == true) goto Masv;
			else goto Ho;
		}

		else if (kitu == key_Up) goto Sdt;
		else if (kitu == key_esc) goto Out;
		else if (kitu == key_Enter) goto Them;
	}
Them:
	if (a == 0) return;
	if (b == 0 || c == 0 || d == 0 || e == 0 || f == 0) {
		gotoxy(70, 30);
		HideCursor(true);
		Normal2();
		cout << "Khong thanh cong!!! Ban can dien du thong tin.";
		Sleep(1000);
		Normal();
		gotoxy(70, 30);
		cout << "                                                   ";
		HideCursor(false);

		if (b == 0) goto Ho;
		else if (c == 0) goto Ten;
		else if (d == 0) goto Phai;
		else if (e == 0) goto Sdt;
		else if (f == 0) goto Malop;
	}
	else {
		if (a < MAX_MASV) p->data.MASV[a] = '\0';
		else p->data.MASV[MAX_MASV - 1] = '\0';
		if (b < MAX_HO) p->data.HO[b] = '\0';
		else p->data.HO[MAX_HO - 1] = '\0';
		if (c < MAX_TEN)  p->data.TEN[c] = '\0';
		else p->data.TEN[MAX_TEN - 1] = '\0';
		if (e < MAX_SDT) p->data.SDT[e] = '\0';
		else p->data.SDT[MAX_SDT - 1] = '\0';
		if (f < MAX_MALOP) p->data.MALOP[f] = '\0';
		else p->data.MALOP[MAX_MALOP - 1] = '\0';
		p->data.PHAI[d] = '\0';
		Normal2();
		if (search_masv(ds, p->data.MASV) && mode == true)
		{
			gotoxy(70, 30);
			Normal2();
			cout << "Ma sinh vien da ton tai !!!";
			Normal();
			Sleep(1000);
			gotoxy(70, 30);
			cout << "                            ";
			HideCursor(false);
			goto Masv;
		}
		gotoxy(70, 30);
		HideCursor(true);
		Normal2();
		if (mode == false)
			cout << "Sua thanh cong !!!";
		else {
			them_sinhvien(ds, p);
			cout << "Them thanh cong !!!";
		}
		Ghi_file(ds);
		Sleep(1000);
		gotoxy(70, 30);
		Normal();
		cout << "                    ";
		return;
	}
Out:
	int check;
	if (mode == false)
	{
		string thong_bao = "Neu ban thoat nhung thay doi se khong duoc luu !!!";
		check = bang_thong_baoo(thong_bao, 60, 15, 58, 4, 15, 14);
		strcpy_s(p->data.HO, B);
		strcpy_s(p->data.TEN, C);
		strcpy_s(p->data.PHAI, D);
		strcpy_s(p->data.SDT, E);
		strcpy_s(p->data.MALOP, F);
	}
	else
	{
		string thong_bao = "Ban co that su muon thoat ?";
		check = bang_thong_baoo(thong_bao, 70, 15, 34, 4, 7, 6);
	}

	if (check == 0)
	{
		Normal();
		return;
	}
	else
	{
		xoa_man_hinh();
		Normal();
		goto reset;
	}
}

bool search_masv(DS_SINH_VIEN ds_sv, char* masv)
{
	for (NODE_SINH_VIEN* i = ds_sv.pHead; i != NULL; i = i->pNext)
		if (strcmp(i->data.MASV, masv) == 0)
			return true;
	return false;
}

int so_trang(float a)
{
	if (a > int(a))
		return a + 1;
	return a;
}

bool so_sanh(char* a, char* b)
{
	for (int i = 0; i < strlen(a) && i < strlen(b); i++)
	{
		if (a[i] < b[i])
			return true;
		else if (a[i] > b[i])
			return false;
	}
}


void insertionSortName(SINH_VIEN a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int k = i - 1;
		SINH_VIEN key = a[i];
		while (strcmp(a[k].TEN,key.TEN) > 0 && k >= 0)
		{
			a[k + 1] = a[k];
			k--;
		}
		a[k + 1] = key;
	}
}
void insertionSortHo(SINH_VIEN a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int k = i - 1;
		SINH_VIEN key = a[i];
			while (strcmp(a[k].HO, key.HO) > 0 && k >= 0&& strcmp(a[k].TEN, key.TEN) == 0)
			{
				a[k + 1] = a[k];
				k--;
			}
		a[k + 1] = key;
	}
}

void flashSort(DS_SINH_VIEN &ds_sv) {
	int n = ds_sv.tongSV;
	if (n == 1)return;
	SINH_VIEN* a = new SINH_VIEN[n];
	int i = 0;
	for (NODE_SINH_VIEN* p = ds_sv.pHead; p != NULL; p = p->pNext)
	{
		a[i] = p->data;
		i++;
	}
	int minVal = a[0].TEN[0];
	int max = 0;
	int m = int(0.45 * n);
	int* l = new int[m];
	for (int i = 0; i < m; i++)
		l[i] = 0;
	for (int i = 1; i < n; i++)
	{
		if (a[i].TEN[0] < minVal)
			minVal = a[i].TEN[0];
		if (a[i].TEN[0] > a[max].TEN[0])
			max = i;
	}
	if (a[max].TEN[0] != minVal) {
		double c1 = (double)(m - 1) / (a[max].TEN[0] - minVal);

		for (int i = 0; i < n; i++)
		{
			int k = int(c1 * (a[i].TEN[0] - minVal));
			++l[k];
		}
		for (int i = 1; i < m; i++)
			l[i] += l[i - 1];

		swap(a[max], a[0]);
		int nmove = 0;
		int j = 0;
		int k = m - 1;
		int t = 0;
		SINH_VIEN flash;
		while (nmove < n - 1)
		{
			while (j > l[k] - 1)
			{
				j++;
				k = int(c1 * (a[j].TEN[0] - minVal));
			}
			flash = a[j];
			if (k < 0) break;
			while (j != l[k])
			{
				k = int(c1 * (flash.TEN[0] - minVal));
				SINH_VIEN hold = a[t = --l[k]];
				a[t] = flash;
				flash = hold;
				++nmove;
			}
		}
		insertionSortName(a, n);
	}
	delete[] l;
	insertionSortHo(a, n);
	i = 0;
	for (NODE_SINH_VIEN* p = ds_sv.pHead; p != NULL; p = p->pNext)
	{
		p->data = a[i];
		i++;
	}



}