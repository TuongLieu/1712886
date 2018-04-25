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
	wchar_t KHoc[5];
	wchar_t ngaySinh[11];
	wchar_t Hinh[31];
	wchar_t Mo_ta_ban_than[256];
	wchar_t Sothich[256];
}SinhVien;

void Doc_thong_tin_sv(FILE* f, SinhVien* &sv,int* n)
{	
	f = _wfopen(L"sinh_vien.csv", L"r,ccs=UTF-8");
	if (!f)
	{
		wprintf(L"\nKhông tìm thấy FILE CSV.");
	}

	//
	int i = 0;
	while (!feof(f))
	{
		sv = (SinhVien*)realloc(sv, (i + 1)*sizeof(SinhVien));
		fwscanf(f, L"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", sv[i].MSSV, sv[i].HoTen, sv[i].Khoa, sv[i].KHoc, sv[i].ngaySinh, sv[i].Hinh, sv[i].Mo_ta_ban_than, sv[i].Sothich);
		i++;
	}
	*n = i;
fclose(f);
}

wchar_t* Lay_email(wchar_t ten[])
{
	int i = 0, j=0;
	wchar_t *email=new wchar_t;	
	while (i < wcslen(ten))
	{
	
		if (ten[i] >= 65 && ten[i] <= 92)
		{
			email = (wchar_t*)realloc(email, (j + 1)*sizeof(wchar_t));		
			email[j] = ten[i]+32;
			j++;
		}
		i++;		
	}
	email[j] = NULL;
	return email;
	
}

int Vi_tri_chuoi(wchar_t *cha, wchar_t *con)
{
	wchar_t *tmp;
	if (tmp= wcsstr(cha, con))
	{
		return (tmp - cha);
	}
	else
	{
		return -1;
	}
}

void chen(wchar_t cha[], wchar_t con[], int vt)
{
	wchar_t temp[256];
	wcscpy(temp, cha + vt);
	wcscpy(cha + vt, con);
	wcscat(cha, temp);
	
}

void xoa(wchar_t cha[], int vt, int so_tu)
{
	wcscpy(cha + vt, cha + vt + so_tu);	
}
void Xuat_HTML( SinhVien* sv,int n)
{
	for (int i = 0; i < n; i++)
	{
		wchar_t * email = Lay_email(sv[i].HoTen);
		FILE* fo = NULL;
		FILE* Template = _wfopen(L"WEBSITE/1212123danhso.html", L"r,ccs=UTF-8");
		if (!Template)
		{
			wprintf(L"\nKhông tìm thấy FILE 1212123.html");
		}
		fseek(Template, 3, SEEK_SET);
		//Tao duong link dan toi website
		wchar_t link[256];
		wchar_t fileName[21];
		wcscpy(link, L"WEBSITE/");
		wcscpy(fileName, sv[i].MSSV);
		wcscat(fileName, L".html");
		wcscat(link, fileName);

		fo = _wfopen(link, L"w,ccs=UTF-8");
		wchar_t line[256];
		wchar_t temp[100];
		int vt;
		while (!feof(Template))
		{
			fgetws(line, 255, Template);
			if (Vi_tri_chuoi(line, L"</title>") != -1)
			{

				vt = Vi_tri_chuoi(line, L"</title>");
				wcscpy(temp, L"HCMUS - ");
				wcscat(temp, sv[i].HoTen);
				chen(line, temp, vt);
				fputws(line, fo);
			}
			if (Vi_tri_chuoi(line, L"(1)") != -1)
			{
				wcscpy(temp, sv[i].HoTen);
				wcscat(temp, L" - ");
				wcscat(temp, sv[i].MSSV);
				chen(line, temp, Vi_tri_chuoi(line, L"(1)") + wcslen(L"(1)"));
				xoa(line, Vi_tri_chuoi(line, L"(1)"), 3);
			}
			if (Vi_tri_chuoi(line, L"(2)") != -1)
			{				
				wcscpy(temp, email);
				chen(line, temp, Vi_tri_chuoi(line, L"(2)") + wcslen(L"(2)"));
				xoa(line, Vi_tri_chuoi(line, L"(2)"), 3);
			}
			if (Vi_tri_chuoi(line, L"(3)") != -1)
			{
				wcscpy(temp, sv[i].Hinh);
				chen(line, temp, Vi_tri_chuoi(line, L"(3)") + wcslen(L"(3)"));
				xoa(line, Vi_tri_chuoi(line, L"(3)"), 3);
			}
			if (Vi_tri_chuoi(line, L"(4)") != -1)
			{
				wcscpy(temp,sv[i].HoTen);
				chen(line, temp, Vi_tri_chuoi(line, L"(4)") + wcslen(L"(4)"));
				xoa(line, Vi_tri_chuoi(line, L"(4)"), 3);
			}
			if (Vi_tri_chuoi(line, L"(5)") != -1)
			{
				wcscpy(temp, sv[i].MSSV);
				chen(line, temp, Vi_tri_chuoi(line, L"(5)") + wcslen(L"(5)"));
				xoa(line, Vi_tri_chuoi(line, L"(5)"), 3);
			}
			if (Vi_tri_chuoi(line, L"(6)") != -1)
			{
				wcscpy(temp, sv[i].Khoa);
				chen(line, temp, Vi_tri_chuoi(line, L"(6)") + wcslen(L"(6)"));
				xoa(line, Vi_tri_chuoi(line, L"(6)"), 3);
			}
			if (Vi_tri_chuoi(line, L"(7)") != -1)
			{
				wcscpy(temp, sv[i].ngaySinh);
				chen(line, temp, Vi_tri_chuoi(line, L"(7)") + wcslen(L"(7)"));
				xoa(line, Vi_tri_chuoi(line, L"(7)"), 3);
			}
			if (Vi_tri_chuoi(line, L"(8)") != -1)
			{
				wcscpy(temp, email);
				chen(line, temp, Vi_tri_chuoi(line, L"(8)") + wcslen(L"(8)"));
				xoa(line, Vi_tri_chuoi(line, L"(8)"), 3);
			}
			
			if (Vi_tri_chuoi(line, L"(9)") != -1)
			{
				wcscpy(temp, sv[i].Sothich);
				chen(line, temp, Vi_tri_chuoi(line, L"(9)") + wcslen(L"(9)"));
				xoa(line, Vi_tri_chuoi(line, L"(9)"), 3);
			}
			if (Vi_tri_chuoi(line, L"(10)") != -1)
			{
				wcscpy(temp, sv[i].Mo_ta_ban_than);
				chen(line, temp, Vi_tri_chuoi(line, L"(10)") + wcslen(L"(10)"));
				xoa(line, Vi_tri_chuoi(line, L"(10)"), 4);
			}
			if (Vi_tri_chuoi(line, L"(11)") != -1)
			{
				wcscpy(temp,sv[i].KHoc);
				chen(line, temp, Vi_tri_chuoi(line, L"(11)") + wcslen(L"(11)"));
				xoa(line, Vi_tri_chuoi(line, L"(11)"), 4);
			}
			fputws(line, fo);
		
		}
		fclose(fo);
		fclose(Template);
	}
}


void wmain()
{

	//Doc unicode
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);


	FILE*f = NULL;
	SinhVien* sv;
	int n;
	sv = (SinhVien*)malloc(sizeof(SinhVien));

	Doc_thong_tin_sv(f, sv, &n);
	Xuat_HTML(sv,n);
	free(sv);
	_getch();
}