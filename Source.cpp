#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<fcntl.h>
#include<io.h>
#include<stdlib.h>
#include<wchar.h>


typedef struct
{
	wchar_t MSSV[11];
	wchar_t HoTen[31];
	wchar_t Khoa[31];
	wchar_t KHoc[5];
	wchar_t ngaySinh[11];
	wchar_t Hinh[31];
	wchar_t Mo_ta_ban_than[1000];
	wchar_t Sothich[1000];
}SinhVien;

void Doc_thong_tin_sv(FILE* f, SinhVien* &sv,int* n)
{	
	f = _wfopen(L"ds_sv.csv", L"r,ccs=UTF-8");
	if (!f)
	{
		wprintf(L"\nKhoong tìm thấy FILE.");
	}

	//
	int i = 0;
	while (!feof(f))
	{
		sv = (SinhVien*)realloc(sv, (i + 1)*sizeof(SinhVien));
		fwscanf(f,L"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", sv[i].MSSV, sv[i].HoTen,sv[i].Khoa,sv[i].KHoc,sv[i].ngaySinh,sv[i].Hinh,sv[i].Mo_ta_ban_than,sv[i].Sothich);
		i++;
	}
	*n = i;
fclose(f);
}
void Xuat(SinhVien* sv, int n)
{
	for (int i = 0; i < n; i++)
	{
		wprintf(L"\n\n\t************* SINH VIÊN THỨ %d ", i + 1);
		wprintf(L"\n-MSSV: %ls ", sv[i].MSSV);
		wprintf(L"\n-Họ tên: %ls  ", sv[i].HoTen);
		wprintf(L"\n-Khoa: %ls  ", sv[i].Khoa);
		wprintf(L"\n-Khóa: %ls  ", sv[i].KHoc);
		wprintf(L"\n-Ngày sinh: %ls  ", sv[i].ngaySinh);
		wprintf(L"\n-Hình ảnh: %ls  ", sv[i].Hinh);
		wprintf(L"\n-Mô tả bản thân:  %ls ", sv[i].Mo_ta_ban_than);
		wprintf(L"\n-Sở thích: %ls  ", sv[i].Sothich);
	}
}
void wmain()
{
	//Doc unicode
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin),_O_U16TEXT);
	

	FILE*f = NULL;
	SinhVien* sv;
	int n;
	sv = (SinhVien*)malloc(sizeof(SinhVien));


	Doc_thong_tin_sv(f, sv, &n);
	Xuat(sv, n);
	
	
	

	
	_getch();
}