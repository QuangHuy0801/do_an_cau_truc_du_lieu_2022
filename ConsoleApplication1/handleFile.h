#pragma once
#include "mylib.h"
#include "myEdit.h"
#include "ctdl.h"
#include <fstream>
#include <string>
#include <ctime>
#define MAX_ID 1000
using namespace std;
void xoa_man_hinh();
bool kitudieukhien(char& c);
bool chu(char& a);
bool kituso(char& a);
bool chu_so(char& a);
void xoa_kitu(char* a, int vt);
void chuan_hoa_chu(char* a);
char chu_in_hoa(char a);
char chu_in_thuong(char a);
void chuoi_in_hoa(char* a);
int bang_thong_baoo(string a, int x, int y, int width, int height, int d, int thut_dong);
void swap(int& a, int& b);
void them_mon_hoc(TREE_MON_HOC& T, TREE_MON_HOC p);
void Doc_file_mon_hoc(TREE_MON_HOC& T);
bool kt_ma_trung_mon_hoc(TREE_MON_HOC& T, char x[]);
ds_mon_hoc* CreateAVLNode_MONHOC(mon_hoc x, int so);
int xoa_mon_hoc(TREE_MON_HOC& T, int x, TREE_MON_HOC& p);
int searchStandFor(TREE_MON_HOC& T, TREE_MON_HOC& p);


void xoa_man_hinh()
{
	Normal();
	for (int i = 0; i <= 32; i++)
	{
		gotoxy(40, i);       
		cout << "                                                                                                                      ";
	}
}

bool kitudieukhien(char& c)
{
	if (c == key_Down || c == key_Up || c == key_Left || c == key_Right)
		return true;
	else if (c == key_Enter || c == key_bkspace)
		return true;
	return false;
}
bool chu(char& a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'z'))
		return true;
	return false;
}

bool kituso(char& a)
{
	if (a >= '0' && a <= '9')
		return true;
	return false;
}

bool chu_so(char& a)
{
	if (chu(a) || kituso(a))
		return true;
	return false;
}

void xoa_kitu(char* a, int vt)
{
	for (int i = vt; i < strlen(a); i++)
		a[i] = a[i + 1];
}
void chuan_hoa_chu(char* a)
{
	//bo dau space

	while (a[0] == ' ')
	{
		xoa_kitu(a, 0);
	}
	while (a[strlen(a) - 1] == ' ')
	{
		xoa_kitu(a, strlen(a) - 1);
	}
	for (int i = 0; i < strlen(a); i++)
	{
		if (a[i] == ' ' && a[i + 1] == ' ') {
			xoa_kitu(a, i + 1);
			i--;
		}
	}
	//chu dau in hoa
	if (a[0] >= 97 && a[0] <= 122)
		a[0] -= 32;
	for (int i = 1; i < strlen(a); i++)
	{
		if (a[i] == ' ' && a[i + 1] >= 97 && a[i + 1] <= 122)
			a[++i] -= 32;
		else if (a[i] >= 65 && a[i] <= 90 && a[i - 1] != ' ')
			a[i] += 32;
	}
}
char chu_in_hoa(char a)
{
	char temp = a;
	if (temp >= 'a' && temp <= 'z')
		temp -= 32;
	return temp;
}

char chu_in_thuong(char a)
{
	char temp = a;
	if (temp >= 'A' && temp <= 'Z')
		temp += 32;
	return temp;
}
void chuoi_in_hoa(char* a)
{
	for (int i = 0; i < strlen(a); i++)
		if (a[i] >= 'a' && a[i] <= 'z')
			a[i] -= 32;
}

int bang_thong_baoo(string a, int x, int y, int width, int height, int d, int thut_dong)
{
	HideCursor(true);
	BGHightLight();
	rectagle(x, y, width, height);
	gotoxy(x + 4, y + 1); cout << a;
	gotoxy(x + 4 + thut_dong, y + 3); cout << "Co";
	HighLight();
	gotoxy(x + 4 + thut_dong + d, y + 3); cout << "Khong";
	char kitu;
	int luachon1 = 1;
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
				gotoxy(x + 4 + thut_dong, y + 3);
				cout << "Co";
				HighLight();
				gotoxy(x + 4 + thut_dong + d, y + 3);
				cout << "Khong";
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
				gotoxy(x + 4 + thut_dong + d, y + 3);
				cout << "Khong";
				HighLight();
				gotoxy(x + 4 + thut_dong, y + 3);
				cout << "Co";
			}
		}
		else if (kitu == key_Enter)
		{
			if (luachon1 == 0)
			{
				Normal();
				xoa_man_hinh();
				return 0;
			}
			else if (luachon1 == 1)
			{
				Normal();
				xoa_man_hinh();
				return 1;
			}
		}
	}
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

//xu li mon hoc

void Rotate_Left_Left(TREE_MON_HOC& T)
{
	TREE_MON_HOC p;

	p = T->pleft;
	T->pleft = p->pright;
	p->pright = T;

	switch (p->bf)
	{
	case 1:
		T->bf = 0;
		p->bf = 0;
		break;
	case 0:
		p->bf = -1;
		T->bf = 1;
		break;
	}
	T = p;
}

void Rotate_Right_Right(TREE_MON_HOC& T)
{
	TREE_MON_HOC p;

	p = T->pright;
	T->pright = p->pleft;
	p->pleft = T;

	switch (p->bf)
	{
	case 0:
		T->bf = -1;
		p->bf = 0;
		break;
	case -1:
		p->bf = 0;
		T->bf = 0;
		break;
	}

	T = p;
}
void Rotate_Right_Left(TREE_MON_HOC& T)
{
	TREE_MON_HOC p1, p2;

	p1 = T->pright;
	p2 = p1->pleft;
	T->pright = p2->pleft;
	p1->pleft = p2->pright;
	p2->pleft = T;
	p2->pright = p1;

	switch (p2->bf)
	{
	case 1:
		T->bf = 0;
		p1->bf = -1;
		break;
	case 0:
		T->bf = 0;
		p1->bf = 0;
		break;
	case -1:
		T->bf = 1;
		p1->bf = 0;
		break;
	}

	p2->bf = 0;
	T = p2;
}

void Rotate_Left_Right(TREE_MON_HOC& T)
{
	TREE_MON_HOC p1, p2;

	p1 = T->pleft;
	p2 = p1->pright;
	T->pleft = p2->pright;
	p1->pright = p2->pleft;
	p2->pright = T;
	p2->pleft = p1;

	switch (p2->bf)
	{
	case 1:
		p1->bf = 0;
		T->bf = -1;
		break;
	case 0:
		T->bf = 0;
		p1->bf = 0;
		break;
	case -1:
		T->bf = 0;
		p1->bf = 1;
		break;
	}

	p2->bf = 0;
	T = p2;
}

int balanceLeft(TREE_MON_HOC& T)
{
	TREE_MON_HOC p;

	p = T->pleft;

	switch (p->bf)
	{
	case 1:
		Rotate_Left_Left(T);
		return 2;
	case 0:
		Rotate_Left_Left(T);
		return 1;
	case -1:
		Rotate_Left_Right(T);
		return 2;
	}
}

//can bang cay lech phai
int balanceRight(TREE_MON_HOC& T)
{
	TREE_MON_HOC p;

	p = T->pright;

	switch (p->bf)
	{
	case -1:
		Rotate_Right_Right(T);
		return 2;
	case 0:
		Rotate_Right_Right(T);
		return 1;
	case 1:
		Rotate_Right_Left(T);
		return 2;
	}
}

int Inrorder_Find_Number(TREE_MON_HOC& T, mon_hoc a, int n) {    //tim gia tri thich hop cua key de them vao tree
	mon_hoc DATA;
	TREE_MON_HOC p = T;
	while (p != NULL) {
		DATA = p->data;
		if (strcmp(DATA.TENMH, a.TENMH) < 0) {
			if (p->pright == NULL) {
				n = p->key + 1;
				return n;
			}
			else p = p->pright;
		}
		else {
			if (p->pleft == NULL) {
				n = p->key;
				return n;
			}
			else p = p->pleft;
		}
	}
}


void Inorder_Up(TREE_MON_HOC& T, int x) {   //tang moi gia tri lon hon x len 1
	if (T != NULL) {
		Inorder_Up(T->pleft, x);
		if (T->key >= x) {
			++T->key;
		}
		Inorder_Up(T->pright, x);
	}
}
void Inorder_Down(TREE_MON_HOC& T, int x) {   //tang moi gia tri lon hon x len 1
	if (T != NULL) {
		Inorder_Down(T->pleft, x);
		if (T->key > x) {
			--T->key;
		}
		Inorder_Down(T->pright, x);
	}
}


int InsertNode(TREE_MON_HOC& T, int so, mon_hoc noiDung)
{
	int Res;
	if (T!=NULL)
	{
		//gia tri da co trong cay
		if (T->key == so) return 0;

		//Root->x > x
		//chen vao ben trai
		if (T->key > so)
		{
			Res = InsertNode(T->pleft, so, noiDung);
			if (Res < 2) return Res;

			//Res >= 2
			else {
				switch (T->bf)
				{
				case -1:
					T->bf = 0;
					return 1;
				case 0:
					T->bf = 1;
					return 2;
				case 1:
					balanceLeft(T);
					return 1;
				}
			}
		}

		//Root->x < x
		//chen vao ben phai
		else
		{
			Res = InsertNode(T->pright, so, noiDung);

			if (Res < 2) return Res;

			//Res >= 2
			else {
				switch (T->bf)
				{
				case 1:
					T->bf = 0;
					return 1;
				case 0:
					T->bf = -1;
					return 2;
				case -1:
					balanceRight(T);
					return 1;
				}
			}
		}
	}

	T = CreateAVLNode_MONHOC(noiDung, so);
	return 2;
}

ds_mon_hoc* CreateAVLNode_MONHOC(mon_hoc x, int so)
{
	ds_mon_hoc* p = new ds_mon_hoc;

	if (!p) exit(1);
	p->key = so;
	p->bf = 0;
	p->data = x;
	p->pleft = NULL;
	p->pright = NULL;

	return p;
}


void them_mon_hoc(TREE_MON_HOC& T, TREE_MON_HOC p) {
	if (T == NULL) {
		p->key = 1;
		p->bf = 0;
		T = p;
	}
	else {
		int so = Inrorder_Find_Number(T, p->data, 0);
		Inorder_Up(T, so);
		InsertNode(T, so, p->data);
	}
}

void Doc_file_mon_hoc(TREE_MON_HOC& T)
{
	ifstream file_mon_hoc;
	int so_monhoc = 0;
	file_mon_hoc.open("ds_monhoc.txt");
	TREE_MON_HOC p;
	while (!file_mon_hoc.eof())
	{
		p = new ds_mon_hoc;
		file_mon_hoc.getline(p->data.MAMH, MAX_MAMH, ',');
		if (strcmp(p->data.MAMH, "\0") == 0)
		{
			delete p;
			file_mon_hoc.close();
			return;
		}
		file_mon_hoc.getline(p->data.TENMH, MAX_TENMH, ',');
		file_mon_hoc >> p->data.STCLT;
		file_mon_hoc >> p->data.STCTH;
		file_mon_hoc.ignore();
		chuoi_in_hoa(p->data.MAMH);
		chuoi_in_hoa(p->data.TENMH);
		them_mon_hoc(T, p);
	}
	file_mon_hoc.close();
}

void Ghi_file(TREE_MON_HOC& T, ofstream& file)
{
	if (T != NULL)
	{
		Ghi_file(T->pleft, file);
		file << T->data.MAMH << ',';
		file << T->data.TENMH << ',';
		file << T->data.STCLT << ' ';
		file << T->data.STCTH << '\n';
		Ghi_file(T->pright, file);
	}
}

void Ghi_file_mon_hoc(TREE_MON_HOC& T)
{
	ofstream file_mon_hoc;
	file_mon_hoc.open("ds_monhoc.txt");
	Ghi_file(T, file_mon_hoc);
	file_mon_hoc.close();
}


void check_trong_cay(TREE_MON_HOC p, char* mamh,bool &so) {
	if (p != NULL) {
		check_trong_cay(p->pleft, mamh, so);
		if (strcmp(p->data.MAMH, mamh) == 0) so = 1;
		check_trong_cay(p->pright, mamh, so);
	}
}



bool check_mamh(char* mamh)
{
	TREE_MON_HOC T = NULL;
	Doc_file_mon_hoc(T);
	TREE_MON_HOC p = T;
	bool so = 0;
	check_trong_cay(p, mamh,so);
	return so;
}

int searchStandFor(TREE_MON_HOC& T, TREE_MON_HOC& p)
{
	int Res;

	if (p->pleft)
	{
		Res = searchStandFor(T, p->pleft);

		if (Res < 2) return Res;

		switch (p->bf)
		{
		case 1:
			p->bf = 0;
			return 1;
		case 0:
			p->bf = -1;
			return 2;
		case -1:
			return balanceRight(T);
		}
	}

	T->key = p->key;
	T->data = p->data;
	T = p;
	p = p->pright;
	return 2;
}
//xoa 1 node tren cay
int xoa_mon_hoc(TREE_MON_HOC& T, int x, TREE_MON_HOC& p)
{

	//khong ton tai node nay tren cay
	if (T==NULL) {
		return 0;
	}
	int res;
	//qua duoc if tren tuc la ton tai
	//root->x > x => sang ben trai tim xoa
	if (T->key > x)
	{
		res = xoa_mon_hoc(T->pleft, x, p);

		//neu co xoa thi res = 1 hoac 2. 2 tuc thay doi chieu cao cay
		if (res < 2) return res;

		//chieu cao bi thay doi
		switch (T->bf)
		{
		case 1:
			T->bf = 0;
			return 1;
		case 0:
			T->bf = -1;
			return 2;
		case -1:
			return balanceRight(T);
		}
	}

	if (T->key < x)
	{
		res = xoa_mon_hoc(T->pright, x, p);

		if (res < 2) return res;

		switch (T->bf)
		{
		case 1:
			return balanceLeft(T);
		case 0:
			T->bf = 1;
			return 2;
		case -1:
			T->bf = 0;
			return 1;
		}
	}

	//root->x = x
	TREE_MON_HOC p1 = T;
	TREE_MON_HOC p2 = p1->pright;

	if (T->pleft == NULL)
	{
		T = T->pright;
		res = 2;
	}
	else
	{
		if (T->pright == NULL)
		{
			T = T->pleft;
			res = 2;
		}
		else
		{
			res = searchStandFor(p1, p2);

			if (res >= 2) {
				switch (T->bf)
				{
				case 1:
					T->bf = 0;
					res = 1;
					break;
				case 0:
					T->bf = -1;
					res = 2;
					break;
				case -1:
					res = balanceRight(T);
					break;
				}
			}
		}

	}
	Inorder_Down(p, x);
	delete p1;
	return res;
}
//ket thuc xu li mon hoc

// DS SINH VIEN

void them_sinhvien(ds_sinh_vien& ds, NODE_SINH_VIEN* x)
{
	NODE_SINH_VIEN* p = ds.pHead;
	if (ds.pHead == NULL)
	{
		ds.pHead = x;
	}
	else {
		while (p->pNext != NULL) {
			p = p->pNext;
		}
		p->pNext = x;//Gán next cua thang cuoi = x.
	}
	ds.tongSV++;
}

void xoa_sinhvien(ds_sinh_vien& ds, NODE_SINH_VIEN* x)
{
	NODE_SINH_VIEN* p;
	p = ds.pHead;
	char* ma = x->data.MASV;
	SINH_VIEN i = p->data;
	if (strcmp(i.MASV,ma)==0) {  //con tro dau la con tro can xoa
		ds.pHead = p->pNext;
	}
	else {
		while (p != NULL || p->pNext != NULL) {
			i = p->pNext->data;
			if (strcmp(i.MASV, ma) == 0) {
				p->pNext = p->pNext->pNext;
				break;
			}
			p = p->pNext;
		}

	}
	ds.tongSV--;
}

void Doc_file_sinh_vien(ds_sinh_vien& ds)
{
	ifstream file_SV;
	NODE_SINH_VIEN* p;
	string a;
	file_SV.open("ds_sinhvien.txt");
	while (!file_SV.eof())
	{
		p = new NODE_SINH_VIEN;
		p->pNext = NULL;
		file_SV.getline(p->data.MALOP, MAX_MALOP, ',');
		file_SV.getline(p->data.MASV, MAX_MASV, ',');
		file_SV.getline(p->data.HO, MAX_HO, ',');
		file_SV.getline(p->data.TEN, MAX_TEN, ',');
		file_SV.getline(p->data.PHAI, MAX_PHAI, ',');
		file_SV.getline(p->data.SDT, MAX_SDT);
		chuoi_in_hoa(p->data.MASV);
		chuoi_in_hoa(p->data.MALOP);
		chuan_hoa_chu(p->data.HO);
		chuan_hoa_chu(p->data.TEN);
		chuan_hoa_chu(p->data.PHAI);
		them_sinhvien(ds, p);
	}
	file_SV.close();
}

void Ghi_file(ds_sinh_vien ds)
{
	ofstream file_SV;
	NODE_SINH_VIEN* p;
	file_SV.open("ds_sinhvien.txt", ios_base::out);
	if (ds.tongSV == 0)
	{
		file_SV.close();
		return;
	}
	for (p = ds.pHead; p->pNext != NULL; p = p->pNext)
	{
		file_SV << p->data.MALOP << ',';
		file_SV << p->data.MASV << ',';
		file_SV << p->data.HO << ',';
		file_SV << p->data.TEN << ',';
		file_SV << p->data.PHAI << ',';
		file_SV << p->data.SDT << '\n';
	}
	file_SV << p->data.MALOP << ',';
	file_SV << p->data.MASV << ',';
	file_SV << p->data.HO << ',';
	file_SV << p->data.TEN << ',';
	file_SV << p->data.PHAI << ',';
	file_SV << p->data.SDT;
	file_SV.close();
}


//LOP TIN CHI





void Init_ds_dang_ki(DS_SV_DANG_KY& dsdk)
{
	dsdk.pHead = NULL;
}

void them_sv_dang_ki(DS_SV_DANG_KY& ds, NODE_SV_DANG_KI* x)
{
	NODE_SV_DANG_KI* p = ds.pHead;
	if (ds.pHead == NULL)
		ds.pHead = x;
	else {
		while (p->pNext != NULL) {
			p = p->pNext;
		}
		p->pNext = x;
	}
	ds.tongSVDK++;
}


void them_vao_lop_tin_chi(DS_LOP_TIN_CHI& ds_ltc, LOP_TIN_CHI* x)
{
	if (ds_ltc.sl == MAX_LOP_TIN_CHI - 1)
	{
		cout << "Danh sach lop tin chi da day . Khong them duoc nua !!!";
	}
	else if (ds_ltc.sl < x->SO_SV_MAX)
	{
		ds_ltc.data[ds_ltc.sl] = x;
		++ds_ltc.sl;
	}
}


void Doc_file_ltc(DS_LOP_TIN_CHI& ds_ltc, int& nLTC)
{
	ifstream filein;
	filein.open("ds_loptinchi.txt", ios_base::in);
	if (filein.fail())
	{
		cout << "Mo file (ds_loptinchi.txt) khong thanh cong. Vui long kiem tra lai !!" << endl;
		return;
	};
	string c;
	filein >> nLTC;
	getline(filein, c);
	for (int i = 0; i < nLTC; i++)
	{
		LOP_TIN_CHI* data = new LOP_TIN_CHI;
		filein >> data->MALOPTC;
		filein.ignore(1);
		filein.getline(data->MAMH, MAX_MAMH, ',');
		filein.getline(data->NIEN_KHOA, MAX_NIEN_KHOA, ',');
		filein >> data->HOC_KY;
		filein.ignore(1);
		filein >> data->NHOM;
		filein.ignore(1);
		filein >> data->SO_SV_MIN;
		filein.ignore(1);
		filein >> data->SO_SV_MAX;
		filein.ignore(1);
		filein >> data->HUY_LOP;
		getline(filein, c);
		Init_ds_dang_ki(data->DSSV);
		filein >> data->tong_sv_dk;
		filein.ignore();
		if (data->tong_sv_dk > 0)
		{
			for (int i = 0; i < data->tong_sv_dk; i++)
			{
				node_sv_dang_ki* sv_dk = new node_sv_dang_ki;
				filein.getline(sv_dk->data.MASV, MAX_MASV, ',');
				filein >> sv_dk->data.DIEM;
				filein.ignore(1);
				filein >> sv_dk->data.HUYDK;
				filein.ignore();
				//getline(filein, c);
				sv_dk->pNext = NULL;
				them_sv_dang_ki(data->DSSV, sv_dk);
			}
		}
		them_vao_lop_tin_chi(ds_ltc, data);
	}
	filein.close();
}
bool check_huy_lop(LOP_TIN_CHI* x)
{
	if (x->tong_sv_dk > 0)
	{
		return false;
	}
	else return true;
}
void Ghi_file_lop_tin_chi(DS_LOP_TIN_CHI ds_ltc)
{
	ofstream fileOut;
	fileOut.open("ds_loptinchi.txt", ios_base::out);
	fileOut << ds_ltc.sl << "\n";
	for (int i = 0; i < ds_ltc.sl; i++)
	{
		fileOut << ds_ltc.data[i]->MALOPTC << "," << ds_ltc.data[i]->MAMH << ","
			<< ds_ltc.data[i]->NIEN_KHOA << "," << ds_ltc.data[i]->HOC_KY << ","
			<< ds_ltc.data[i]->NHOM << "," << ds_ltc.data[i]->SO_SV_MIN << ","
			<< ds_ltc.data[i]->SO_SV_MAX << "," << ds_ltc.data[i]->HUY_LOP << "\n";
		/*if (check_huy_lop(ds_ltc.data[i]))
		{
			fileOut << 1 << "\n";
		}
		else
		{
			fileOut << 0 << "\n";
		}*/
		fileOut << ds_ltc.data[i]->tong_sv_dk << "\n";
		if (ds_ltc.data[i]->tong_sv_dk > 0)
		{
			NODE_SV_DANG_KI* k = NULL;
			for (k = ds_ltc.data[i]->DSSV.pHead; k != NULL; k = k->pNext)
			{
				fileOut << k->data.MASV << "," << k->data.DIEM << ',' << k->data.HUYDK << "\n";
			}
		}
	}
	fileOut.close();
}
bool check_mh_dk(char* mamh)
{
	DS_LOP_TIN_CHI ds_ltc;
	int n_ltc;
	Doc_file_ltc(ds_ltc, n_ltc);
	for (int i = 0; i < n_ltc; i++)
		if (strcmp(ds_ltc.data[i]->MAMH, mamh) == 0)
			return true;
	return false;
}

bool check_sv_dk(char* masv)
{
	DS_LOP_TIN_CHI ds_ltc;
	int n_ltc;
	Doc_file_ltc(ds_ltc, n_ltc);
	for (int i = 0; i < n_ltc; i++)
		for (NODE_SV_DANG_KI* p = ds_ltc.data[i]->DSSV.pHead; p != NULL; p = p->pNext)
			if (strcmp(p->data.MASV, masv) == 0)
				return true;
	return false;
}

void xoa_sv_ltc(char* masv)
{
	DS_LOP_TIN_CHI ds_ltc;
	int n_ltc;
	Doc_file_ltc(ds_ltc, n_ltc);
	NODE_SV_DANG_KI* t = new NODE_SV_DANG_KI;
	for (int i = 0; i < n_ltc; i++)
	{
		for (NODE_SV_DANG_KI* p = ds_ltc.data[i]->DSSV.pHead; p != NULL; t = p, p = p->pNext)
		{
			if (strcmp(masv, p->data.MASV) == 0)
			{
				if (p == ds_ltc.data[i]->DSSV.pHead)
				{
					ds_ltc.data[i]->DSSV.pHead = ds_ltc.data[i]->DSSV.pHead->pNext;
					delete p;
					ds_ltc.data[i]->tong_sv_dk--;
					break;
				}
				else if (p->pNext == NULL)
				{
					t->pNext = NULL;
					delete p;
					ds_ltc.data[i]->tong_sv_dk--;
					break;
				}
				else
				{
					t->pNext = p->pNext;
					delete p;
					ds_ltc.data[i]->tong_sv_dk--;
					break;
				}

			}
		}
	}
	Ghi_file_lop_tin_chi(ds_ltc);
	delete t;
}