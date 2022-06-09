#pragma once
#include<iostream>
#include<string.h>
#include<fstream>
#include <iomanip>
#include "xu_ly_sinh_vien.h"
#include "xu_ly_mon_hoc.h"
#include "xu_li_lop_tin_chi.h"
#include "myEdit.h"
#include "ctdl.h"
#include "handleFile.h"
using namespace std;
#define item_diem 3
#define max_mh 100

void tao_khung_diem(TREE_MON_HOC ,DS_LOP_TIN_CHI&, DS_SINH_VIEN& );
void in_diem_ltc(DS_LOP_TIN_CHI& , DS_SINH_VIEN& ,bool);
void In_Diem(DS_LOP_TIN_CHI&, DS_SV_DANG_KY&, LOP_TIN_CHI*, DS_SINH_VIEN, bool);
void ghi_diem_ltc(TREE_MON_HOC ,DS_LOP_TIN_CHI& , DS_SINH_VIEN& ,bool );
void In_Diem_cua_lop(DS_LOP_TIN_CHI& , DS_SINH_VIEN& );
void get_so_tin_chi(TREE_MON_HOC&, char*, int&);
void In_Diem_tong_ket(DS_LOP_TIN_CHI& , DS_SINH_VIEN& );

void menu_diem()
{
	DS_LOP_TIN_CHI ds_ltc;
	int n;
	Doc_file_ltc(ds_ltc, n);
	DS_SINH_VIEN ds_sv;
	TREE_MON_HOC T = NULL;
	int nLTC;
	Doc_file_mon_hoc(T);
	Doc_file_sinh_vien(ds_sv);
	tao_khung_diem(T,ds_ltc, ds_sv);
}
void tao_khung_diem(TREE_MON_HOC T,DS_LOP_TIN_CHI& ds_ltc, DS_SINH_VIEN& ds_sv)
{
velai:
	system("cls");
	gotoxy(75, 4);
	SetBGColor(12);
	SetColor(15);
	cout << "XU LI DIEM";
	Normal();
	int x = 55, y = 9, d = 0, width = 55, heigh = 4;
	HideCursor(true);
	char menu[4][40] = {
		"           Nhap diem",
		"    In diem cua lop tin chi",
		"   In diem trung binh cua lop",
		"  In bang diem tong ket cua lop",
	};
	for (int i = 0; i < 4; i++) {
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
			if (luachon >= 4)
			{
				luachon = 0;
				y -= d * (4 - 1);

				Normal();
				rectagle(x, y + d * (4 - 1), width, heigh);
				gotoxy(x + 10, y + d * (4 - 1) + 2);
				cout << menu[4 - 1];

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
				luachon = 4 - 1;
				y += d * (4 - 1);

				Normal();
				rectagle(x, y - d * (4 - 1), width, heigh);
				gotoxy(x + 10, y - d * (4 - 1) + 2);
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
				ghi_diem_ltc(T,ds_ltc, ds_sv,true);
			}
			else if (luachon == 1) {
				ghi_diem_ltc(T,ds_ltc,  ds_sv,false);
			}
			else if (luachon == 2) {
				DS_SINH_VIEN ds_lop;
				char malop[MAX_MALOP] = "";
				int check = Ma_Lop(ds_sv, malop);
				if (check == 1)
				{
					ds_theo_ma_lop(ds_sv, ds_lop, malop);
					In_Diem_cua_lop( ds_ltc,ds_lop);
				}
			}
			else if (luachon == 3) {
				DS_SINH_VIEN ds_lop;
				char malop[MAX_MALOP] = "";
				int check = Ma_Lop(ds_sv, malop);
				if (check == 1)
				{
					ds_theo_ma_lop(ds_sv, ds_lop, malop);
					In_Diem_tong_ket(ds_ltc, ds_lop);
				}
			}
			goto velai;
		}
	}
}
void get_SV_Lop(DS_SINH_VIEN& ds_sv, NODE_SINH_VIEN*& p, int vt) {
    p= ds_sv.pHead;
	for (int i = 0; i < vt; i++) {
		p = p->pNext;
	}
}


void get_so_tin_chi(TREE_MON_HOC& T, char* ma_mh, int &tin_chi) {
	if (T != NULL) {
		get_so_tin_chi(T->pleft, ma_mh, tin_chi);
		if (strcmp(T->data.MAMH, ma_mh) == 0) {
			tin_chi = T->data.STCLT + T->data.STCTH;
			return;
		}
		get_so_tin_chi(T->pright, ma_mh, tin_chi);
	}
}

void In_Diem_cua_lop(DS_LOP_TIN_CHI& dsltc, DS_SINH_VIEN& ds_lop)
{
	NODE_SINH_VIEN* p = ds_lop.pHead;
	SetBGColor(12);
	gotoxy(60, 2);
	cout << "BANG THONG KE DIEM TRUNG BINH KHOA HOC ";
	gotoxy(65, 4);
	cout << "Ma lop: " << ds_lop.pHead->data.MALOP;
	Normal();
	int stt = 1, x = 45, y = 8, trang = 1, luachon = 0;
	int tong_trang = so_trang(1.0 * ds_lop.tongSV / 20);
	NODE_SINH_VIEN* sv;
	NODE_SV_DANG_KI* sv_dk;
chuyen_trang:
	xoa_man_hinh();
	Normal();
	HideCursor(true);
	gotoxy(135, 32);
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
	gotoxy(x + 2, y);	cout << "STT" << " ";
	gotoxy(x + 9, y);	cout << char(179) << "  MASV" << "  ";
	gotoxy(x + 24, y);	cout << char(179) << "  HO" << "                     ";
	gotoxy(x + 56, y);	cout << char(179) << "  TEN" << "    ";
	gotoxy(x + 71, y);	cout << char(179) << "  DIEM";
	Normal();

	gotoxy(x + 9, y + 1);	cout << char(179) << "              " << char(179) << "                               " << char(179) << "              " << char(179);
	get_SV_Lop(ds_lop, p, stt - 1);
	int y1 = 1, count = 0;
	int diem = 0;
	float tong_diem = 0.00;
	int tong_tin_chi = 0;
	int tin_chi = 0;
	TREE_MON_HOC T = NULL;
	LOP_TIN_CHI* t;
	Doc_file_mon_hoc(T);
	for (NODE_SINH_VIEN* j = p; j != NULL && count < 20; j = j->pNext){
		count++;
		gotoxy(x + 9, y + (++y1));	cout << char(179) << "              " << char(179) << "                               " << char(179) << "              " << char(179);
		gotoxy(x + 2 + 1, y + y1);	cout << stt++;
		gotoxy(x + 9 + 3, y + y1);	cout << j->data.MASV;
		gotoxy(x + 24 + 3, y + y1);	cout << j->data.HO;
		gotoxy(x + 56 + 3, y + y1);	cout << j->data.TEN;
		for (int v = 0; v < dsltc.sl; v++) {
			 t = dsltc.data[v];
			 if (t->HUY_LOP == 0) {
				 for (NODE_SV_DANG_KI* h = dsltc.data[v]->DSSV.pHead; h != NULL; h = h->pNext)
					 if (strcmp(j->data.MASV, h->data.MASV) == 0)
					 {
						 if (h->data.DIEM != -1) {
							 get_so_tin_chi(T, t->MAMH, tin_chi);
							 diem += h->data.DIEM * tin_chi;
							 tong_tin_chi += tin_chi;
						 }
						 break;
					 }
			 }
		}
		if (diem != -1 && tong_tin_chi !=0) {
			tong_diem = diem*1.00 / tong_tin_chi;
			gotoxy(x + 71 + 3, y + y1);	cout << setprecision(2) << fixed << tong_diem;
		}
		tin_chi = 0;
		tong_diem = 0;
		tong_tin_chi = 0;
		diem = 0;
	}
	char kitu;
	while (true)
	{
		kitu = GetKey();
		if (kitu == key_Right)
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
				stt -= (count + 20);
				Normal();
				goto chuyen_trang;
			}
		}
		else if (kitu == key_esc)
		{
			Normal();
			gotoxy(50, 34);
			cout << "             ";
			return;
		}
	}

}
bool check_mang_mh(char arr[][MAX_MAMH], int n, char* ma) {
	for (int i = 0; i < n; i++) {
		if (strcmp(arr[i],ma)==0)
			return 0;
	}
	return 1;
}


void mon_hoc_co_trong_lop(DS_LOP_TIN_CHI& dsltc, DS_SINH_VIEN& ds_lop, char arr[][MAX_MAMH], int &n) {
	LOP_TIN_CHI* t;
	for (NODE_SINH_VIEN* j = ds_lop.pHead; j != NULL; j = j->pNext) {
		for (int v = 0; v < dsltc.sl; v++) {
			t = dsltc.data[v];
			if (t->HUY_LOP == 0) {
				if (t->HUY_LOP == 0) {
					for (NODE_SV_DANG_KI* h = dsltc.data[v]->DSSV.pHead; h != NULL; h = h->pNext)
						if (strcmp(j->data.MASV, h->data.MASV) == 0 && h->data.HUYDK == 0 && check_mang_mh(arr, n, t->MAMH))
						{
							strcpy(arr[n], t->MAMH);
							n++;
							break;
						}
				}
			}
		}
	}
}
void In_Diem_tong_ket(DS_LOP_TIN_CHI& dsltc, DS_SINH_VIEN& ds_lop)
{
	NODE_SINH_VIEN* p = ds_lop.pHead;
	SetBGColor(12);
	gotoxy(63, 2);
	cout << "BANG THONG TONG KET";
	gotoxy(65, 4);
	cout << "Ma lop: " << ds_lop.pHead->data.MALOP;
	Normal();
	int so_mon_hoc = 0;
	char arr_mon_hoc[max_mh][MAX_MAMH];
	mon_hoc_co_trong_lop(dsltc, ds_lop, arr_mon_hoc, so_mon_hoc);
	int stt = 1, x = 20, y = 8, trang = 1,trang2 = 1;
	int st = 0;
	int tong_trang = so_trang(1.0 * ds_lop.tongSV / 20);
	int tong_trang2 = so_trang(1.0 * so_mon_hoc / 5);
	NODE_SINH_VIEN* sv;
	NODE_SV_DANG_KI* sv_dk;
chuyen_trang:
	xoa_man_hinh();
	Normal();
	HideCursor(true);
	gotoxy(135, 32);
	cout << "^ "<<trang << '/' << tong_trang << " v";
	gotoxy(120, 32);
	cout << "< " << trang2 << '/' << tong_trang2 << " >";
	rectagle(x - 5, y - 2, 138, 25);
	for (int i = 0; i <= 122; i++)
	{
		HideCursor(true);
		SetBGColor(color_darkwhite);
		gotoxy(x + i, y);
		cout << ' ';
	}
	int d = 0;
	SetColor(color_black);
	gotoxy(x + 2, y);	cout << "STT" << " ";
	gotoxy(x + 9, y);	cout << char(179) << "  MASV" << "  ";
	gotoxy(x + 24, y);	cout << char(179) << "  HO VA TEN" << "         ";
	for (int i = st; i < so_mon_hoc&&i<(st+5); i++) {
		gotoxy(x + 56+d, y);	cout << char(179) << "    "<<arr_mon_hoc[i]<< "   ";
		d += 15;
	}
	Normal();

	get_SV_Lop(ds_lop, p, stt - 1);
	int y1 = 1, count = 0;
	for (NODE_SINH_VIEN* j = p; j != NULL && count < 20; j = j->pNext) {
			count++;
			gotoxy(x + 9, y + (++y1));	cout << char(179) << "              " << char(179) << "                               " << char(179);
			gotoxy(x + 2 + 1, y + y1);	cout << stt++;
			gotoxy(x + 9 + 3, y + y1);	cout << j->data.MASV;
			gotoxy(x + 24 + 3, y + y1);	cout << j->data.HO << " " << j->data.TEN;
	}
	LOP_TIN_CHI* t;
	int y2 = 1; int diem = -1; d = 0; int dem = 0;int count2 = 0;
	for (int j = st; j < so_mon_hoc && count2 <  5; j++) {
		for (NODE_SINH_VIEN* i = p; i != NULL && dem < 20; i = i->pNext)
		{
			for (int v = 0; v < dsltc.sl; v++) {
				t = dsltc.data[v];
				if (t->HUY_LOP != 0) continue;
				if (strcmp(t->MAMH, arr_mon_hoc[j]) != 0)continue;
					for (NODE_SV_DANG_KI* h = dsltc.data[v]->DSSV.pHead; h != NULL; h = h->pNext)
						if (strcmp(i->data.MASV, h->data.MASV) == 0)
						{
							if (diem < h->data.DIEM)diem = h->data.DIEM;
							break;
						}
			}
			if (diem != -1) {
				gotoxy(x + 63 + d, y + (++y2));	cout << diem;
			}
			else ++y2;
			if (j != 4) {
				gotoxy(x + 71 + d, y + y2);
				cout << char(179);
			}
			dem++;
			diem = -1;
		}
		dem = 0;
		d += 15;
		y2 = 1;
		st++;
		count2++;
	}
	char kitu;
	while (true)
	{
		kitu = GetKey();
		if (kitu == key_Down)
		{
			trang += 1;
			if (trang > tong_trang)	trang = tong_trang;
			else
			{
				st -= count2;
				Normal();
				goto chuyen_trang;
			}
		}
		else if (kitu == key_Up)
		{
			trang -= 1;
			if (trang < 1)	trang = 1;
			else
			{
				st -= count2;
				stt -= (count + 20);
				Normal();
				goto chuyen_trang;
			}
		}
		else if (kitu == key_Right)
		{
			trang2 += 1;
			if (trang2 > tong_trang2)	trang2 = tong_trang2;
			else
			{
				stt -= count;
				Normal();
				goto chuyen_trang;
			}
		}
		else if (kitu == key_Left)
		{
			trang2 -= 1;
			if (trang2 < 1)	trang2 = 1;
			else
			{
				stt -= count;
				st -= (count2 + 5);
				Normal();
				goto chuyen_trang;
			}
		}
		else if (kitu == key_esc)
		{
			Normal();
			gotoxy(50, 34);
			cout << "             ";
			return;
		}
	}

}


void ghi_diem_ltc(TREE_MON_HOC T, DS_LOP_TIN_CHI& dsltc, DS_SINH_VIEN& ds_sv,bool mode) {
BD:
	
	int vitri = Search_danh_sach_sv_dang_ki(T,dsltc, true);
	int x = 45, y = 5;
	if (vitri == -1)
	{
		char c[100] = "KHONG TIM THAY LOP TIN CHI NAY !";
		Thong_bao(x + 4, y + 23, c);
		Sleep(1000);
		goto BD;
	}
	else if (vitri == -2)
	{
		return;
	}
	else if (vitri == -3)
	{
		in_diem_ltc(dsltc, ds_sv,mode);
		return;
	}
	else if (dsltc.data[vitri]->tong_sv_dk - So_luong_sv_huy_lop(dsltc.data[vitri]) == 0)
	{
		char c[100] = "KHONG CO SINH VIEN DANG KI LOP NAY !";
		Thong_bao(x + 4, y + 23, c);
		Sleep(1000);
		goto BD;
	}
	In_Diem(dsltc, dsltc.data[vitri]->DSSV ,dsltc.data[vitri], ds_sv, mode);
}



bool check_chua_nhap_diem(DS_SV_DANG_KY& ds_sv_dk) {
	for (NODE_SV_DANG_KI* i = ds_sv_dk.pHead; i != NULL; i = i->pNext) {
		if (i->data.DIEM >=0) return 0;
	}
	return 1;
}


void in_diem_ltc(DS_LOP_TIN_CHI& dsltc, DS_SINH_VIEN& ds_sv,bool mode)
{tudau:
	clrscr();
	HideCursor(true);
INRA:
	{
		int x = 40, y = 4, row = 0, trang = 0, tongTrang = 0;
		char c;
		while (1)
		{
			if (dsltc.sl == 0)
			{
				rectagle(x + 15, y + 8, 40, 6);
				gotoxy(x + 18, y + 11);
				cout << "DANH SACH TIN CHI TRONG !";
				c = GetKey();
			
				if (c == key_esc || c == key_Enter)
				{
					break;
				}
			}
			else
			{
				if (dsltc.sl < 22)
				{
					trang = 0;
					tongTrang = 1;
				}
				else
				{
					tongTrang = (dsltc.sl - 1) / 22 + 1;
				}
			}

			Xoa_khung_lop_tin_chi();
			Khung_lop_tin_chi();
			for (int i = trang * 22; i < 22 + trang * 22 && i < dsltc.sl; i++)
			{
					gotoxy(x + 2, y + 3 + row); cout << i + 1;
					gotoxy(x + 8, y + 3 + row); cout << dsltc.data[i]->MALOPTC;
					gotoxy(x + 17, y + 3 + row); cout << dsltc.data[i]->MAMH;
					gotoxy(x + 32, y + 3 + row); cout << dsltc.data[i]->NIEN_KHOA;
					gotoxy(x + 47, y + 3 + row); cout << dsltc.data[i]->NHOM;
					gotoxy(x + 57, y + 3 + row); cout << dsltc.data[i]->HOC_KY;
					gotoxy(x + 65, y + 3 + row); cout << dsltc.data[i]->SO_SV_MAX;
					gotoxy(x + 74, y + 3 + row); cout << dsltc.data[i]->SO_SV_MIN;
					gotoxy(x + 82, y + 3 + row); cout << dsltc.data[i]->SO_SV_MAX - dsltc.data[i]->DSSV.tongSVDK + So_luong_sv_huy_lop(dsltc.data[i]);
					gotoxy(x + 92, y + 3 + row); cout << dsltc.data[i]->HUY_LOP;
					row++;
				
			}
			int chon = 0;
			row = 0;
			while (1)
			{
				Hien_thi_trang(trang + 1, tongTrang, x + 80, y + 28);
				if (chon == trang * 22)
				{
					
					HighLight();
					gotoxy(x + 2, y + 3); cout << chon + 1;
					gotoxy(x + 8, y + 3); cout << dsltc.data[chon]->MALOPTC;
					gotoxy(x + 17, y + 3); cout << dsltc.data[chon]->MAMH;
					gotoxy(x + 32, y + 3); cout << dsltc.data[chon]->NIEN_KHOA;
					gotoxy(x + 47, y + 3); cout << dsltc.data[chon]->NHOM;
					gotoxy(x + 57, y + 3); cout << dsltc.data[chon]->HOC_KY;
					gotoxy(x + 65, y + 3); cout << dsltc.data[chon]->SO_SV_MAX;
					gotoxy(x + 74, y + 3); cout << dsltc.data[chon]->SO_SV_MIN;
					gotoxy(x + 82, y + 3); cout << dsltc.data[chon]->SO_SV_MAX - dsltc.data[chon]->DSSV.tongSVDK + So_luong_sv_huy_lop(dsltc.data[chon]);
					Normal();
				}
				c = GetKey();
				if (c == key_esc)
				{
					if (bang_thong_bao("Ban co chac chan thoat ?") == 1) return;
					else goto tudau;
				}
				else if ((c == key_Down) && trang < tongTrang && chon < dsltc.sl - 1)
				{
					Normal();
					gotoxy(x + 2, y + 3 + chon - 22 * trang); cout << chon + 1;
					gotoxy(x + 8, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->MALOPTC;
					gotoxy(x + 17, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->MAMH;
					gotoxy(x + 32, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->NIEN_KHOA;
					gotoxy(x + 47, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->NHOM;
					gotoxy(x + 57, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->HOC_KY;
					gotoxy(x + 65, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->SO_SV_MAX;
					gotoxy(x + 74, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->SO_SV_MIN;
					gotoxy(x + 82, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->SO_SV_MAX - dsltc.data[chon]->DSSV.tongSVDK + So_luong_sv_huy_lop(dsltc.data[chon]);;
					chon++;
					HighLight();
					gotoxy(x + 2, y + 3 + chon - 22 * trang); cout << chon + 1;
					gotoxy(x + 8, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->MALOPTC;
					gotoxy(x + 17, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->MAMH;
					gotoxy(x + 32, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->NIEN_KHOA;
					gotoxy(x + 47, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->NHOM;
					gotoxy(x + 57, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->HOC_KY;
					gotoxy(x + 65, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->SO_SV_MAX;
					gotoxy(x + 74, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->SO_SV_MIN;
					gotoxy(x + 82, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->SO_SV_MAX - dsltc.data[chon]->DSSV.tongSVDK + So_luong_sv_huy_lop(dsltc.data[chon]);;
					if (chon == 22 * (trang + 1))
					{
						trang++;
						Xoa_khung_lop_tin_chi();
						Khung_lop_tin_chi();
						row = 0;
						for (int i = trang * 22; i < 22 + trang * 22 && i < dsltc.sl; i++)
						{
							gotoxy(x + 2, y + 3 + row); cout << i + 1;
							gotoxy(x + 8, y + 3 + row); cout << dsltc.data[i]->MALOPTC;
							gotoxy(x + 17, y + 3 + row); cout << dsltc.data[i]->MAMH;
							gotoxy(x + 32, y + 3 + row); cout << dsltc.data[i]->NIEN_KHOA;
							gotoxy(x + 47, y + 3 + row); cout << dsltc.data[i]->NHOM;
							gotoxy(x + 57, y + 3 + row); cout << dsltc.data[i]->HOC_KY;
							gotoxy(x + 65, y + 3 + row); cout << dsltc.data[i]->SO_SV_MAX;
							gotoxy(x + 74, y + 3 + row); cout << dsltc.data[i]->SO_SV_MIN;
							gotoxy(x + 82, y + 3 + row); cout << dsltc.data[i]->SO_SV_MAX - dsltc.data[i]->DSSV.tongSVDK + So_luong_sv_huy_lop(dsltc.data[chon]);;
							row++;
						}
					}
				}
				else if (c == key_Up && chon > 0 && trang >= 0)
				{
					Normal();
					gotoxy(x + 2, y + 3 + chon - 22 * trang); cout << chon + 1;
					gotoxy(x + 8, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->MALOPTC;
					gotoxy(x + 17, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->MAMH;
					gotoxy(x + 32, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->NIEN_KHOA;
					gotoxy(x + 47, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->NHOM;
					gotoxy(x + 57, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->HOC_KY;
					gotoxy(x + 65, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->SO_SV_MAX;
					gotoxy(x + 74, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->SO_SV_MIN;
					gotoxy(x + 82, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->SO_SV_MAX - dsltc.data[chon]->DSSV.tongSVDK + So_luong_sv_huy_lop(dsltc.data[chon]);;
					chon--;
					HighLight();
					gotoxy(x + 2, y + 3 + chon - 22 * trang); cout << chon + 1;
					gotoxy(x + 8, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->MALOPTC;
					gotoxy(x + 17, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->MAMH;
					gotoxy(x + 32, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->NIEN_KHOA;
					gotoxy(x + 47, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->NHOM;
					gotoxy(x + 57, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->HOC_KY;
					gotoxy(x + 65, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->SO_SV_MAX;
					gotoxy(x + 74, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->SO_SV_MIN;
					gotoxy(x + 82, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->SO_SV_MAX - dsltc.data[chon]->DSSV.tongSVDK + So_luong_sv_huy_lop(dsltc.data[chon]);;
					if (chon == 22 * trang - 1 && chon != 0)
					{
						trang--;
						Xoa_khung_lop_tin_chi();
						Khung_lop_tin_chi();
						row = 0;
						for (int i = trang * 22; i < 22 + trang * 22 && i < dsltc.sl; i++)
						{
							gotoxy(x + 2, y + 3 + row); cout << i + 1;
							gotoxy(x + 8, y + 3 + row); cout << dsltc.data[i]->MALOPTC;
							gotoxy(x + 17, y + 3 + row); cout << dsltc.data[i]->MAMH;
							gotoxy(x + 32, y + 3 + row); cout << dsltc.data[i]->NIEN_KHOA;
							gotoxy(x + 47, y + 3 + row); cout << dsltc.data[i]->NHOM;
							gotoxy(x + 57, y + 3 + row); cout << dsltc.data[i]->HOC_KY;
							gotoxy(x + 65, y + 3 + row); cout << dsltc.data[i]->SO_SV_MAX;
							gotoxy(x + 74, y + 3 + row); cout << dsltc.data[i]->SO_SV_MIN;
							gotoxy(x + 82, y + 3 + row); cout << dsltc.data[i]->SO_SV_MAX - dsltc.data[i]->DSSV.tongSVDK + So_luong_sv_huy_lop(dsltc.data[chon]);;
							row++;
						}
						HighLight();
						gotoxy(x + 2, y + 3 + chon - 22 * trang);
						cout << 22 * (trang + 1);
						gotoxy(x + 8, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->MALOPTC;
						gotoxy(x + 17, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->MAMH;
						gotoxy(x + 32, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->NIEN_KHOA;
						gotoxy(x + 47, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->NHOM;
						gotoxy(x + 57, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->HOC_KY;
						gotoxy(x + 65, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->SO_SV_MAX;
						gotoxy(x + 74, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->SO_SV_MIN;
						gotoxy(x + 82, y + 3 + chon - 22 * trang); cout << dsltc.data[chon]->SO_SV_MAX - dsltc.data[chon]->DSSV.tongSVDK + So_luong_sv_huy_lop(dsltc.data[chon]);;
						Normal();

					}
				}
				else if (c == key_Enter) {
					clrscr();
					if (dsltc.data[chon]->HUY_LOP == 1) {
						clrscr();
						SetBGColor(12);
						rectagle(65, 15, 50, 4);
						gotoxy(70, 17);
						cout << "Lop nay da bi huy !!";
						Sleep(1500);
						Normal();
					}
					else if (dsltc.data[chon]->DSSV.pHead != NULL)
						In_Diem(dsltc, dsltc.data[chon]->DSSV, dsltc.data[chon] , ds_sv, mode);
					else if (check_chua_nhap_diem(dsltc.data[chon]->DSSV) && mode == false && dsltc.data[chon]->DSSV.pHead == NULL) {
						clrscr();
						rectagle(60, 15, 50, 4);
						gotoxy(70, 17);
						cout << "Lop tin chi chua cap nhat diem !!";
						Sleep(1000);
						Normal();
					}
					else {
						clrscr();
						char s[50] = "Chua co sinh vien trong lop tin chi !!";
						khung_thong_bao(60, 17, 60, 4, s);
						Sleep(1000);
						Normal();
					}
					goto tudau;
				}				
			}
			row = 0;
			break;
		}
	}
}


void HighLight_SV_DK(NODE_SV_DANG_KI* p1, NODE_SINH_VIEN* p, int x, int y, int stt)
{
	for (int i = 0; i <= 86; i++)
	{
		BGHightLight();
		gotoxy(x + i, y);
		cout << ' ';
	}
	SetColor(color_black);

	gotoxy(x + 9, y);	cout << char(179) << "              " << char(179) << "                               " << char(179) << "              " << char(179);
	gotoxy(x + 2 + 1, y);		cout << stt;
	gotoxy(x + 9 + 3, y);	cout << p->data.MASV;
	gotoxy(x + 24 + 3, y);	cout << p->data.HO;
	gotoxy(x + 56 + 3, y);	cout << p->data.TEN;
	if (p1->data.DIEM != -1) {
		gotoxy(x + 71 + 3, y);	cout << p1->data.DIEM;
	}
	Normal();
}

void get_SV_DK(DS_SV_DANG_KY ds_sv_dk, DS_SINH_VIEN& ds_sv,  NODE_SV_DANG_KI* &svdk, NODE_SINH_VIEN* &sv, int vt)
{
	svdk = ds_sv_dk.pHead;
	
	if (vt != 0 || svdk->data.HUYDK == 1)
	{
		int dem = -1;
		while (dem != vt && svdk->pNext != NULL)
		{
			if (svdk->pNext->data.HUYDK == 0) dem++;
			svdk = svdk->pNext;
		}
	}
	//for (int i = 0; i < vt; i++, svdk = svdk->pNext);
	sv = ds_sv.pHead;
	while (strcmp(sv->data.MASV, svdk->data.MASV) != 0)
	{
		sv = sv->pNext;
	}
}


void HighLight_SV_DK(SV_DANG_KY* p1, NODE_SINH_VIEN* p, int x, int y, int stt)
{
	for (int i = 0; i <= 86; i++)
	{
		BGHightLight();
		gotoxy(x + i, y);
		cout << ' ';
	}
	SetColor(color_black);
	gotoxy(x + 9, y);	cout << char(179) << "              " << char(179) << "                               " << char(179) << "              " << char(179);
	gotoxy(x + 2 + 1, y);		cout << stt;
	gotoxy(x + 9 + 3, y);	cout << p->data.MASV;
	gotoxy(x + 24 + 3, y);	cout << p->data.HO;
	gotoxy(x + 56 + 3, y);	cout << p->data.TEN;
	if (p1->DIEM != -1) {
		gotoxy(x + 71 + 3, y);	cout << p1->DIEM;
	}
	Normal();
}


void Normal_SV_DK(SV_DANG_KY p1, NODE_SINH_VIEN* p, int x, int y, int stt)
{
	for (int i = 0; i <= 86; i++)
	{
		Normal();
		gotoxy(x + i, y);
		cout << ' ';
	}
	Normal();
	gotoxy(x + 9, y);	cout << char(179) << "              " << char(179) << "                               " << char(179) << "              " << char(179);
	gotoxy(x + 2 + 1, y);		cout << stt;
	gotoxy(x + 9 + 3, y);	cout << p->data.MASV;
	gotoxy(x + 24 + 3, y);	cout << p->data.HO;
	gotoxy(x + 56 + 3, y);	cout << p->data.TEN;
	if (p1.DIEM != -1) {
		gotoxy(x + 71 + 3, y);	cout << p1.DIEM;
	}
}


void get_ten_mh(TREE_MON_HOC &T, char *ma_mh) {
	if (T != NULL) {
		get_ten_mh(T->pleft,ma_mh);
		if (strcmp(T->data.MAMH,ma_mh)==0 ){
			cout << T->data.TENMH;
			return;
		}
		get_ten_mh(T->pright, ma_mh);
	}
}



void In_Diem(DS_LOP_TIN_CHI& ds_ltc, DS_SV_DANG_KY& ds_sv_dk, LOP_TIN_CHI* ltc, DS_SINH_VIEN ds_sv, bool mode)
{
	clrscr();
	if (mode == false) {
		TREE_MON_HOC T=NULL;
		Doc_file_mon_hoc(T);
		SetBGColor(12);
		gotoxy(73, 2);
		cout << "BANG DIEM MON HOC: ";
		get_ten_mh(T, ltc->MAMH); cout << endl;
		gotoxy(65, 4);
		cout << "NIEN KHOA: " << ltc->NIEN_KHOA << "    HOC KI: " << ltc->HOC_KY << "     NHOM :" << ltc->NHOM;
		Normal();
	}

	int stt = 1, x = 45, y = 8, trang = 1, luachon = 0;
	int tong_trang = so_trang(1.0 * (ds_sv_dk.tongSVDK - So_luong_sv_huy_lop(ltc) )/ 20);

	if (tong_trang == 0)
	{
		clrscr();
		gotoxy(70, 10);
		cout << "Danh sach lop trong !!!";
		Sleep(1500);
		gotoxy(70, 10);
		cout << "                   ";
		return;
	}

	NODE_SINH_VIEN* sv;
	NODE_SV_DANG_KI* sv_dk;
	
	if (mode == true) {
		SetBGColor(12);
		gotoxy(50, 34);
		cout << "Enter : Sua diem";
	}
chuyen_trang:
	xoa_man_hinh();
	Normal();
	HideCursor(true);
	gotoxy(135, 32);
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
	gotoxy(x + 2, y);	cout << "STT" << " ";
	gotoxy(x + 9, y);	cout << char(179) << "  MASV" << "  ";
	gotoxy(x + 24, y);	cout << char(179) << "  HO" << "                     ";
	gotoxy(x + 56, y);	cout << char(179) << "  TEN" << "    ";
	gotoxy(x + 71, y);	cout << char(179) << "  DIEM";
	Normal();

	gotoxy(x + 9, y + 1);	cout << char(179) << "              " << char(179) << "                               " << char(179) << "              " << char(179);

	get_SV_DK(ds_sv_dk, ds_sv, sv_dk, sv, stt - 1);


	int y1 = 1, count = 0;
	for (NODE_SV_DANG_KI* i = sv_dk; i != NULL && count < 20; i = i->pNext)
	{
		if (i->data.HUYDK == 0)
		{
			for (NODE_SINH_VIEN* j = ds_sv.pHead; j != NULL; j = j->pNext)
				if (strcmp(j->data.MASV, i->data.MASV) == 0)
				{
					count++;
					y1++;
					gotoxy(x + 9, y + y1);	cout << char(179) << "              " << char(179) << "                               " << char(179) << "              " << char(179);
					gotoxy(x + 2 + 1, y + y1);	cout << stt++;
					gotoxy(x + 9 + 3, y + y1);	cout << j->data.MASV;
					gotoxy(x + 24 + 3, y + y1);	cout << j->data.HO;
					gotoxy(x + 56 + 3, y + y1);	cout << j->data.TEN;
					if (i->data.DIEM != -1) {
						gotoxy(x + 71 + 3, y + y1);	cout << i->data.DIEM;
					}
					break;
				}
		}
		
	}
	if (mode == true)
	{
		get_SV_DK(ds_sv_dk, ds_sv, sv_dk, sv, stt - count - 1);
		HighLight_SV_DK(sv_dk, sv, x, y + 2, stt - count);
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
				cout << count;
				get_SV_DK(ds_sv_dk, ds_sv, sv_dk, sv, stt - count - 1 + luachon - 1);
				Normal_SV_DK(sv_dk->data, sv, x, y + 2 + luachon - 1, stt - count - 1 + luachon);
				get_SV_DK(ds_sv_dk, ds_sv, sv_dk, sv, stt - count - 1 + luachon);
				HighLight_SV_DK(sv_dk, sv, x, y + 2 + luachon, stt - count - 1 + luachon + 1);
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
				get_SV_DK(ds_sv_dk, ds_sv, sv_dk, sv, stt - count - 1 + luachon + 1);
				Normal_SV_DK(sv_dk->data, sv, x, y + 2 + luachon + 1, stt - count + luachon + 1);
				get_SV_DK(ds_sv_dk, ds_sv, sv_dk, sv, stt - count - 1 + luachon);
				HighLight_SV_DK(sv_dk, sv, x, y + 2 + luachon, stt - count + luachon);
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
				stt -= (count + 20);
				Normal();
				goto chuyen_trang;
			}
		}
		else if (kitu ==key_Enter && mode == true)
		{
			if (sv_dk->data.HUYDK == 1)
				{
					gotoxy(70, 33);
					cout << "Sinh vien nay da huy dang ki lop !!!";
					Sleep(1500);
					gotoxy(70, 33);
					Normal();
					cout << "                                         ";
				}
				else
				{
				HideCursor(false);

				SetBGColor(color_green);

				gotoxy(x + 71 + 1, y + 2 + luachon);
				cout << "          ";
				int a = 0;
				if (sv_dk->data.DIEM > 0)
				{
					gotoxy(x + 71 + 3, y + 2 + luachon);
					cout << sv_dk->data.DIEM;
					if (sv_dk->data.DIEM == 10) a = 2;
					else a = 1;
				}
			reset:

				gotoxy(x + 71 + 3 + a, y + 2 + luachon);
				while (true)
				{
					kitu = GetKey();
					if (!kitudieukhien(kitu) && kituso(kitu) && a < 2)
					{
						a++;
						if (sv_dk->data.DIEM < 0)
							sv_dk->data.DIEM = 0;
						sv_dk->data.DIEM = sv_dk->data.DIEM * 10 + int(kitu - 48);
						cout << kitu;
					}
					else if (kitu == key_bkspace && a > 0)
					{
						a = 0;
						sv_dk->data.DIEM = 0;
						gotoxy(x + 71 + 3, y + 2 + luachon);
						cout << "  ";
						gotoxy(x + 71 + 3, y + 2 + luachon);
					}
					else if (kitu == key_Enter)
					{
						if (sv_dk->data.DIEM > 10)
						{
							Normal2();
							gotoxy(70, 33);
							cout << "Diem he so 10, ban vui long nhap lai !!!";
							Sleep(1500);
							gotoxy(70, 33);
							Normal();
							cout << "                                         ";
							SetBGColor(6);
							goto reset;
						}
						else
						{
							BGHightLight();
							HideCursor(true);
							gotoxy(x + 71 + 1, y + 2 + luachon);
							cout << "          ";
							if (a == 0) sv_dk->data.DIEM = -1;
							else
							{
								gotoxy(x + 71 + 3, y + 2 + luachon);
								cout << sv_dk->data.DIEM;
							}
							Ghi_file_lop_tin_chi(ds_ltc);
							Normal();
							break;
						}
					}
				}
				}
			
		}
		else if (kitu == key_esc)
		{
			Normal();
			gotoxy(50, 34);
			cout << "             ";
			return;
		}
	}
}
