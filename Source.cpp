#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<fcntl.h>
#include<io.h>
#include<stdlib.h>
#include<wchar.h>
#include<string.h>

typedef struct
{
	wchar_t MSSV[11];
	wchar_t HoTen[31];
	wchar_t Khoa[31];
	int KHoc;
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
		wprintf(L"\nKhông tìm thấy FILE.");
	}

	//
	int i = 0;
	while (!feof(f))
	{
		sv = (SinhVien*)realloc(sv, (i + 1)*sizeof(SinhVien));
		fwscanf(f,L"%[^,],%[^,],%[^,],", sv[i].MSSV, sv[i].HoTen,sv[i].Khoa);
		fwscanf(f,L"%[^,],",&sv[i].KHoc);
		fwscanf(f, L"%[^,],%[^,],%[^,],%[^\n]\n", sv[i].ngaySinh, sv[i].Hinh, sv[i].Mo_ta_ban_than, sv[i].Sothich);
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
		wprintf(L"\n-Khoa: %ls ", sv[i].Khoa);
		wprintf(L"\n-Khóa: %ls  ", sv[i].KHoc);
		wprintf(L"\n-Ngày sinh: %ls  ", sv[i].ngaySinh); 
		wprintf(L"\n-Hình ảnh: %ls  ", sv[i].Hinh);
		wprintf(L"\n-Mô tả bản thân:  %ls ", sv[i].Mo_ta_ban_than);
		wprintf(L"\n-Sở thích: %ls  ", sv[i].Sothich);
	}
}
void Lay_email(wchar_t ten[])
{
	int i = 0, j = 0;
	wchar_t email[6];
	while (i < wcslen(ten))
	{
		
		if (ten[i] >= 65 && ten[i] <= 90)
		{
			ten[i] = ten[i] + 32;
			email[j] = ten[i];
			j++;
		}
		i++;
		
	}
	email[j] = NULL;
}

void Xuat_HTML(FILE* fi, SinhVien* sv,int n)
{
	for (int i = 0; i < n; i++)
	{

		
		wchar_t str[256];
		fi = _wfopen(L"1212123.txt", L"r,ccs=UTF-8");
		if (!fi)
		{
			wprintf(L"\nKhông tìm thấu FILE.");
		}
		FILE* fo = _wfopen(sv[i].MSSV, L"w,ccs=UTF-8");
		if (!fo)
		{
			wprintf(L"\nKhông tìm thấy FILE.");
		}


		while (fgetws(str, 256, fi))
		{
			fputws(str, fo);
			if (wcsstr(str, L"<title>"))
			{
				fseek(fo, -11, SEEK_END);
				fwprintf(fo, L"%ls", sv[i].HoTen);
			}
			if (wcsstr(str, L"span class"))
			{
				fseek(fo, -9, SEEK_END);
				fwprintf(fo, L"%ls-%ls",sv[i].HoTen,sv[i].MSSV);
			}
			if (wcsstr(str, L"<li>"))
			{
				if (wcsstr(str, L"<li>Họ và tên: "))
				{

					fseek(fo, -7, SEEK_END);
					fwprintf(fo, L"%ls",sv[i].HoTen);
					fseek(fo, 0, SEEK_END);
				}
				else if (wcsstr(str, L"<li>MSSV: "))
				{
					fseek(fo, -7, SEEK_END);
					fwprintf(fo, L"%ls", sv[i].MSSV);
					fseek(fo, 0, SEEK_END);
				}
				else if (wcsstr(str, L"<li>Sinh viên khoa"))
				{
					fseek(fo, -7, SEEK_END);
					fwprintf(fo, L"%ls", sv[i].Khoa);
				}
				else if (wcsstr(str, L"<li>Ngày sinh: "))
				{
					fseek(fo, -7, SEEK_END);
					fwprintf(fo, L"%ls", sv[i].ngaySinh);
				}
				else if (wcsstr(str, L"<li>Email: "))
				{
					fseek(fo, -7, SEEK_END);
					fwprintf(fo, L"%ls", sv[i].HoTen);
				}
				else
				{
					fseek(fo, -7, SEEK_END);
					fwprintf(fo, L"%ls", sv[i].Sothich);
				}

			}
			if (wcsstr(str, L"Description"))
			{
				fwprintf(fo, L"%ls", sv[i].Mo_ta_ban_than);
			}


		}


		fclose(fo);
		fclose(fi);

	}
}
void wmain()
{
	//Doc unicode
	_setmode(_fileno(stdout), _O_U8TEXT);
	_setmode(_fileno(stdin),_O_U8TEXT);
	

	FILE*f = NULL;
	
	SinhVien* sv;
	int n;
	sv = (SinhVien*)malloc(sizeof(SinhVien));


	Doc_thong_tin_sv(f, sv, &n);
	
	//Xuat(sv, n);
	
	Xuat_HTML(f, sv,n);

	


	
	
	_getch();
}