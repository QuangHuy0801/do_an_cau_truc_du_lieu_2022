#pragma once
#include <string.h>
#include "ctdl.h"
#include "handleFile.h"
#include  <ctime>
#include "myEdit.h"
#include "xu_ly_sinh_vien.h"

using namespace std;
void tao_khung_mon_hoc(TREE_MON_HOC& T);
void menu_monhoc();
void them_sua_mon_hoc(TREE_MON_HOC& T, TREE_MON_HOC p, bool mode);
void dem_mon_hoc(TREE_MON_HOC T,int &so);
TREE_MON_HOC get_mon_hoc( TREE_MON_HOC ds, int vt);
void HighLight_mon_hoc(TREE_MON_HOC p, int x, int y, int stt);
void in_ds_mon_hoc(TREE_MON_HOC& T, bool mode);
void Inorder_in(TREE_MON_HOC T, int& count, int x, int y, int& y1, int& stt);
//void Inorder_in_thu_tu(TREE_MON_HOC T, int& count, int x, int y, int& y1, int& stt);


#define MAX 10000
#define item_mh 4


void menu_monhoc()
{
	TREE_MON_HOC T = NULL;
	Doc_file_mon_hoc(T);
	tao_khung_mon_hoc(T);
}
void tao_khung_mon_hoc(TREE_MON_HOC& T)
{
	velai:
	system("cls");
	gotoxy(79,4);
	SetBGColor(12);
	SetColor(15);
	cout << "XU LY MON HOC";
	Normal();
	int x = 65, y = 9, d = 0, width = 40, heigh = 4;
	HideCursor(true);
	char menu[item][30] = {
		" In danh sach mon hoc",
		"   Xu li mon hoc"
	};
	for (int i = 0; i < item; i++) {
		rectagle(x, y + d, width, heigh);
		gotoxy(x + 10, y + d + 2);
		d += 7;
		cout << menu[i];
	}
	HighLight();
	rectagle(x, y, width, heigh);
	gotoxy(x + 10, y + 2);
	cout << menu[0];

	d = 7;
	int luachon = 0;
	char kitu;
	gotoxy(x, y);
	while (true)
	{
		kitu = GetKey();
		if (kitu == key_esc) return;
		if (kitu == key_Down)
		{
			luachon++;
			if (luachon >= item)
			{
				luachon = 0;
				y -= d * (item - 1);

				Normal();
				rectagle(x, y + d * (item - 1), width, heigh);
				gotoxy(x + 10, y + d * (item - 1) + 2);
				cout << menu[item - 1];

				HighLight();
				rectagle(x, y, width, heigh);
				gotoxy(x + 10, y + 2);
				cout << menu[luachon];
			}
			else {
				y += d;

				Normal();
				rectagle(x, y - d, width, heigh);
				gotoxy(x + 10, y - d + 2);
				cout << menu[luachon - 1];

				HighLight();
				rectagle(x, y, width, heigh);
				gotoxy(x + 10, y + 2);
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
				gotoxy(x + 10, y - d * (item - 1) + 2);
				cout << menu[0];

				HighLight();
				rectagle(x, y, width, heigh);
				gotoxy(x + 10, y + 2);
				cout << menu[luachon];
			}
			else {
				y -= d;

				Normal();
				rectagle(x, y + d, width, heigh);
				gotoxy(x + 10, y + d + 2);
				cout << menu[luachon + 1];

				HighLight();
				rectagle(x, y, width, heigh);
				gotoxy(x + 10, y + 2);
				cout << menu[luachon];
			}
		}
		else if (kitu == key_Enter)
		{
			clrscr();
			if (luachon == 0)
			{
				//in ds mon hoc
				in_ds_mon_hoc(T, false);
			}
			else if (luachon == 1)
			{
				//hieu chinh mon hoc

				in_ds_mon_hoc(T, true);
			}
			goto velai;
		}
	}
}

void them_sua_mon_hoc(TREE_MON_HOC& T, TREE_MON_HOC p, bool mode)
{
	HideCursor(false);
	int x = 70, y = 13, width = 30, heigh = 2;
	int luachon = 0;
	char kitu;
	char A[MAX_MAMH];
	char B[MAX_TENMH];
	int C, D;
reset:
	xoa_man_hinh();
	SetBGColor(color_green);
	SetColor(color_green);
	rectagle(x - 5, y - 3, 60, 15);
	char menu[item_mh][30] = {
		"Ma mon hoc",
		"Ten mon hoc",
		"So TCLT",
		"So TCTH"
	};
	for (int i = 0, j = 0; i < item_mh; i++, j += 3) {
		gotoxy(x, y + j);
		SetColor(color_white);
		cout << menu[i];
		SetColor(color_white);
		rectagle(x + 20, y + j - 1, width, heigh);
	}

	Normal2();
	int a = 0, b = 0, c = 0, d = 0;
	if (mode == true)
	{
		gotoxy(x + 22, y);		cout << p->data.MAMH;
		gotoxy(x + 22, y + 3);	cout << p->data.TENMH;
		gotoxy(x + 22, y + 6);	cout << p->data.STCLT;
		gotoxy(x + 22, y + 9);	cout << p->data.STCTH;
		a = strlen(p->data.MAMH);
		b = strlen(p->data.TENMH);
		c = 1;
		d = 1;
		strcpy_s(A, p->data.MAMH);
		strcpy_s(B, p->data.TENMH);
		C = p->data.STCLT;
		D = p->data.STCTH;
	}
	HideCursor(false);
	goto Mamh;
Mamh:
	gotoxy(x + 22 + a, y );
	Normal2();
	while (true)
	{
		kitu = GetKey();
		if (kitu == key_esc) goto Out;
		else if (!kitudieukhien(kitu) && a < MAX_MAMH)
		{

			if (chu_so(kitu)) {
				p->data.MAMH[a] = chu_in_hoa(kitu);
				cout << p->data.MAMH[a++];
			}
			else if (kitu == key_Space && p->data.MAMH[a - 1] != key_Space && a != 0) {
				p->data.MAMH[a++] = kitu;
				cout << kitu;
			}
		}
		else if (kitu == key_bkspace && a > 0)
		{
			p->data.MAMH[--a] = ' ';
			gotoxy(wherex() - 1, wherey());
			cout << ' ';
			gotoxy(wherex() - 1, wherey());
		}
		else if (kitu == key_Down)
			goto Tenmh;
		else if (kitu == key_Up) goto Stcth;
		else if (kitu == key_Enter) goto Them;
	}
Tenmh:
	Normal2();
	gotoxy(x + 22 + b, y + 3);
	while (true)
	{
		kitu = GetKey();
		if (kitu == key_esc) goto Out;
		else if (!kitudieukhien(kitu) && b < MAX_TENMH)
		{

			if (chu_so(kitu)) {
				p->data.TENMH[b] = chu_in_hoa(kitu);
				cout << p->data.TENMH[b++];
			}
			else if (kitu == key_Space && p->data.TENMH[b - 1] != key_Space && b != 0) {
				p->data.TENMH[b++] = kitu;
				cout << kitu;
			}
		}
		else if (kitu == key_bkspace && b > 0)
		{
			p->data.TENMH[--b] = ' ';
			gotoxy(wherex() - 1, wherey());
			cout << ' ';
			gotoxy(wherex() - 1, wherey());
		}
		else if (kitu == key_Down)
			goto Stclt;
		else if (kitu == key_Up) goto Mamh;
		else if (kitu == key_Enter) goto Them;
	}
Stclt:
	Normal2();
	gotoxy(x + 22 + c, y + 6);
	while (true)
	{
		kitu = GetKey();
		if (!kitudieukhien(kitu) && kituso(kitu) && c < 1)
		{
			c++;
			p->data.STCLT = int(kitu - 48);
			cout << p->data.STCLT;
		}
		else if (kitu == key_bkspace && c > 0)
		{
			c--;
			gotoxy(wherex() - 1, wherey());
			cout << ' ';
			gotoxy(wherex() - 1, wherey());
		}
		else if (kitu == key_Down)
			goto Stcth;
		else if (kitu == key_Up) goto Tenmh;
		else if (kitu == key_esc) goto Out;
		else if (kitu == key_Enter) goto Them;
	}
Stcth:
	Normal2();
	gotoxy(x + 22 + d, y + 9);
	while (true)
	{
		kitu = GetKey();
		if (!kitudieukhien(kitu) && kituso(kitu) && d < 1)
		{
			d++;
			p->data.STCTH = int(kitu - 48);
			cout << p->data.STCTH;
		}
		else if (kitu == key_bkspace && d > 0)
		{
			d--;
			gotoxy(wherex() - 1, wherey());
			cout << ' ';
			gotoxy(wherex() - 1, wherey());
		}
		else if (kitu == key_Down)
			goto Mamh;
		else if (kitu == key_Up) goto Stclt;
		else if (kitu == key_Enter) goto Them;
		else if (kitu == key_esc) goto Out;
	}

Them:
	if (a == 0 ||b == 0 || c == 0 || d == 0) {
		gotoxy(70, 30);
		HideCursor(true);
		Normal2();
		cout << "Khong thanh cong!!! Ban can dien du thong tin.";
		Sleep(1000);
		gotoxy(70, 30);
		Normal();
		cout << "                                                  ";
		HideCursor(false);
		if (a == 0) goto Mamh;
		else if (b == 0) goto Tenmh;
		else if (c == 0) goto Stclt;
		else if (d == 0) goto Stcth;
	}
	else {
		if (a < MAX_MAMH)
			p->data.MAMH[a] = '\0';
		else
			p->data.MAMH[MAX_MAMH - 1] = '\0';
		if (b < MAX_TENMH)
			p->data.TENMH[b] = '\0';
		else
			p->data.TENMH[MAX_TENMH - 1] = '\0';

		if (mode == false) {
			if (check_mamh(p->data.MAMH)) {
				gotoxy(70, 30);
				HideCursor(true);
				Normal2();
				cout << "Khong thanh cong!ma sinh vien cua ban da ton tai.";
				Sleep(1000);
				Normal();
				gotoxy(70, 30);
				cout << "                                                  ";
				HideCursor(false);
				goto Mamh;
			}
			else
			them_mon_hoc(T, p);
		}

		Ghi_file_mon_hoc(T);
		Normal2();
		HideCursor(true);
		gotoxy(80, 30);
		if (mode == false)
			cout << "Them thanh cong !!!";
		else
			cout << "Sua thanh cong !!!";
		Sleep(1000);
		Normal();
		gotoxy(80, 30);
		cout << "                   ";
		goto reset;
	}
Out:
	if (mode == false)
	{
		string thong_bao = "Ban co that su muon thoat ?";
		int check = bang_thong_baoo(thong_bao, 70, 15, 34, 4, 7, 6);
		Normal();
		if (check == 1) goto reset;
		else return;
	}
	else
	{
		string thong_bao = "Neu ban thoat nhung thay doi se khong duoc luu !!!";
		int check = bang_thong_baoo(thong_bao, 60, 15, 58, 4, 15, 14);
		if (check == 0)
		{
			strcpy(p->data.MAMH, A);
			strcpy(p->data.TENMH, B);
			c = C;
			d = D;
			Normal();
			return;
		}
		else goto reset;
	}
}

void dem_mon_hoc(TREE_MON_HOC T,int &so)
{
	if (T != NULL) {
		dem_mon_hoc(T->pleft, so);
			++so;
			dem_mon_hoc(T->pright, so);
	}
}
TREE_MON_HOC get_mon_hoc(TREE_MON_HOC ds, int vt)
{
	TREE_MON_HOC p = ds;
	while (p != NULL) {
		if (p->key == vt + 1)return p;
		else if (p->key < vt + 1)
			p = p->pright;
		else p=p->pleft;
	}
	return NULL;
}

void HighLight_mon_hoc(TREE_MON_HOC p, int x, int y, int stt)
{
	for (int i = 0; i <= 85; i++)
	{
		BGHightLight();
		gotoxy(x + i, y);
		cout << ' ';
	}
	SetColor(color_black);
	gotoxy(x + 2, y);
	cout << "    " << char(179) << "              " << char(179) << "                                  " << char(179) << "               " << char(179);
	gotoxy(x + 2, y);			cout << p->key;
	gotoxy(x + 2 + 5 + 2, y);	cout << p->data.MAMH;
	gotoxy(x + 12 + 10 + 2, y);	cout << p->data.TENMH;
	gotoxy(x + 22 + 30 + 9, y);	cout << "   " << p->data.STCLT;
	gotoxy(x + 52 + 15 + 9, y); cout << "   " << p->data.STCTH;
	Normal();
}

//dg lam
void Inorder_in(TREE_MON_HOC T,int &count,int x,int y,int &y1,int &stt) {  
	if (T != NULL) {
			Inorder_in(T->pleft, count, x, y, y1, stt);
			if (count < 20 && T->key>=stt) {
				mon_hoc a;
				a = T->data;
				count++;
				gotoxy(x + 2, y + y1);
				cout << "    " << char(179) << "              " << char(179) << "                                  " << char(179) << "               " << char(179);
				gotoxy(x + 2, y + y1);					cout << T->key;
				gotoxy(x + 2 + 5 + 2, y + y1);			cout << a.MAMH;
				gotoxy(x + 12 + 10 + 2, y + y1);		cout << a.TENMH;
				gotoxy(x + 22 + 33 + 9, y + y1);		cout << a.STCLT;
				gotoxy(x + 52 + 15 + 9, y + (y1++));	cout << "   " << a.STCTH;
				cout << endl;
			}
			Inorder_in(T->pright, count, x, y, y1, stt);
	}
}

//void Inorder_in_thu_tu(TREE_MON_HOC T, int& count, int x, int y, int& y1, int& stt) {
//	if (T != NULL) {
//		Inorder_in_thu_tu(T->pleft, count, x, y, y1, stt);
//		if (count < 20 && T->key >= stt) {
//			mon_hoc a;
//			a = T->data;
//			count++;
//			gotoxy(x + 2, y + y1);
//			cout << "    " << char(179) << "              " << char(179) << "                                  " << char(179) << "               " << char(179);
//			gotoxy(x + 2, y + y1);					cout << T->key;
//			gotoxy(x + 2 + 5 + 2, y + y1);			cout << a.MAMH;
//			gotoxy(x + 12 + 10 + 2, y + y1);		cout << a.TENMH;
//			gotoxy(x + 22 + 33 + 9, y + y1);		cout << a.STCLT;
//			gotoxy(x + 52 + 15 + 9, y + (y1++));	cout << "   " << a.STCTH;
//			cout << endl;
//		}
//		Inorder_in_thu_tu(T->pright, count, x, y, y1, stt);
//	}
//}



void Normal_mon_hoc(TREE_MON_HOC p, int x, int y, int stt)
{
	for (int i = 0; i <= 85; i++)
	{
		Normal();
		gotoxy(x + i, y);
		cout << ' ';
	}
	Normal;
	gotoxy(x + 2, y);
	cout << "    " << char(179) << "              " << char(179) << "                                  " << char(179) << "               " << char(179);
	gotoxy(x + 2, y);			cout << stt;
	gotoxy(x + 2 + 5 + 2, y);	cout << p->data.MAMH;
	gotoxy(x + 12 + 10 + 2, y);	cout << p->data.TENMH;
	gotoxy(x + 22 + 30 + 9, y);	cout << "   " << p->data.STCLT;
	gotoxy(x + 52 + 15 + 9, y); cout << "   " << p->data.STCTH;

}

void in_ds_mon_hoc(TREE_MON_HOC& T, bool mode)
{
tudau:
	int sp = 0;
	int stt = 1, x =45, y = 8, trang = 1, luachon = 0, tong_trang;
	char kitu;
	int tong_mon = 0;
	dem_mon_hoc(T, tong_mon);
	if (mode == true)
	{
		SetBGColor(12);
		SetColor(15);
		gotoxy(50, 35);
		cout << "F1: SUA";
		gotoxy(50, 37);
		cout << "F2: XOA";
		gotoxy(70, 35);
		cout << "F3: THEM";
		gotoxy(120, 35);
		cout << "ESC: THOAT";
	}
	gotoxy(75 , 4);
	SetBGColor(12);
	SetColor(15);
	cout << "DANH SACH TAT CA MON HOC";
chuyen_trang:;
	xoa_man_hinh();
	Normal();
	gotoxy(135, 32);
	tong_trang = so_trang(1.0 * tong_mon / 20);
	cout << trang << '/' << tong_trang;
	rectagle(x - 5, y - 2, 95, 25);
	for (int i = 0; i <= 85; i++)
	{
		HideCursor(true);
		SetBGColor(color_darkwhite);
		gotoxy(x + i, y);
		cout << ' ';
	}
	SetColor(color_black);
	gotoxy(x + 2, y);			cout << "Stt" << " " << char(179);
	gotoxy(x + 2 + 5 + 2, y);	cout << "Ma mon hoc" << "  " << char(179);
	gotoxy(x + 12 + 10 + 2, y);	cout << "Ten mon hoc" << "                     " << char(179);
	gotoxy(x + 22 + 30 + 9, y);	cout << "So TCLT" << "    " << char(179);
	gotoxy(x + 52 + 15 + 9, y); cout << "So TCTH";
	Normal();
	if (tong_mon == 0) {
		gotoxy(80, 29);
		cout << "DANH SACH TRONG !!!";
		Sleep(1000);
		return;
	}
	int y1 = 2, count = 0;
	gotoxy(x + 2, y + 1);
	cout << "    " << char(179) << "              " << char(179) << "                                  " << char(179) << "               " << char(179);
	if (mode == true)
	{
		Inorder_in(T, count, x, y, y1, stt);
		if (tong_mon - stt > 20) {
			stt += 20;
		}
		else {
			stt = tong_mon+1;
		}
		HighLight_mon_hoc(get_mon_hoc( T, stt - count -1 + luachon), x, y + 2 + luachon, stt - count + luachon);
	}
	else
	{
		Inorder_in(T, count, x, y, y1,stt);
		if (tong_mon -stt> 20) {
			stt += 20;
		}
		else {
			stt=tong_mon+1;
		}
	}
Huy_lop_failed:
	while (true)
	{
		kitu = GetKey();
		if (kitu == key_Right)
		{
			trang++;
			if (trang > tong_trang) trang = tong_trang;
			else
			{
				luachon = 0;
				goto chuyen_trang;
			}
		}
		else if (kitu == key_Left && trang > 1)
		{
			trang--;
			if (trang < 1) trang = 1;
			else
			{
				stt -= (count + 20);
				luachon = 0;
				goto chuyen_trang;
			}
		}
		else if (kitu == key_Down && mode == true)
		{
			luachon++;
			if (luachon > count - 1) luachon = count - 1;
			else
			{
				Normal_mon_hoc(get_mon_hoc(T, stt - count + luachon - 1 - 1), x, y + 2 + luachon - 1, stt - count + luachon - 1);
				HighLight_mon_hoc(get_mon_hoc( T, stt - count + luachon - 1), x, y + 2 + luachon, stt - count + luachon);
			}
		}
		else if (kitu == key_Up && mode == true)
		{
			luachon--;
			if (luachon < 0) luachon = 0;
			else
			{
				Normal_mon_hoc(get_mon_hoc( T,  stt - count + luachon + 1 - 1), x, y + 2 + luachon + 1, stt - count + luachon + 1);
				HighLight_mon_hoc(get_mon_hoc( T,  stt - count + luachon - 1), x, y + 2 + luachon, stt - count + luachon);
			}
		}
		else if (kitu == key_F1 && mode == true)
		{
			TREE_MON_HOC sua = get_mon_hoc( T, stt - count - 1 + luachon);
			if (check_mh_dk(sua->data.MAMH))
			{
				gotoxy(65, 33);
				cout << "MON HOC DA DUOC DANG KI LOP TIN CHI, KHONG THE SUA";
				Sleep(1500);
				gotoxy(65, 33);
				Normal();
				cout << "                                                   ";
				goto Huy_lop_failed;
			}
			else
			{
				them_sua_mon_hoc(T, sua, true);
				stt -= count;
				goto chuyen_trang;
			}
		}
		else if (kitu == key_F2 && mode == true)
		{
			TREE_MON_HOC temp = get_mon_hoc(T, stt - count + luachon - 1);
			if (check_mh_dk(temp->data.MAMH))
			{
				SetBGColor(12);
				SetBGColor(12);
				gotoxy(65, 33);
				cout << "MON HOC DA DUOC DANG KI LOP TIN CHI, KHONG THE XOA";
				Sleep(1500);
				Normal();
				gotoxy(65, 33);
				cout << "                                                   ";
				goto Huy_lop_failed;
			}
			else
			{
				string thong_bao = "Ban co that su muon xoa ?";
				int check = bang_thong_baoo(thong_bao, 70, 15, 34, 4, 7, 6);
				if (check == 0)
				{
					xoa_mon_hoc(T, temp->key,T);
					tong_mon--;
					if (luachon + stt - count > tong_mon) luachon--;
					if (luachon < 0)
					{
						luachon = 19;
						stt -= 20;
						trang--;
					}
					Ghi_file_mon_hoc(T);
				}
			}
			stt -= count;
			goto chuyen_trang;
		}
		else if (kitu == key_F3 && mode == true)
		{
			clrscr();
			TREE_MON_HOC p = new ds_mon_hoc;
			them_sua_mon_hoc(T, p, false);
			goto tudau;
		}
		else if (kitu == key_esc)
		{
			gotoxy(82, 4);
			Normal();
			cout << "                        ";
			gotoxy(50, 35);
			cout << "        ";
			gotoxy(50, 37);
			cout << "        ";
			return;
		}
	}
}

