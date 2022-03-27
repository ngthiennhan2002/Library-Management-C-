#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include "MyFunction.h"
using namespace std;
// Hàm dịch chuyển con trỏ đến tọa độ x, y.
// Tham số truyền vào là tọa độ x (số ký tự theo hàng ngang) và tọa độ y (số dòng)
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

// Hàm thay đổi kích cỡ của khung cmd.
// Tham số truyền vào là chiều dài và chiều rộng của console
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Hàm thêm độc giả
/*Tham số truyền vào là thông tin các độc giả theo kiểu reader và số lượng độc giả hiện có trong thư viện
(dạng tham chiếu để trả về số lượng sau khi thêm độc giả)*/
void addReaders(reader noReaders[], int& numberReaders)
{
	for (int i = 0;; i++)
	{
		int Row = 2;
		system("cls");
		gotoxy(70, Row);
		cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
		gotoxy(68, Row);
		cout << "THEM DOC GIA THEO YEU CAU\n"; Row += 2;
		fstream f2;
		f2.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers.txt", ios::in);
		f2 >> numberReaders;
		f2.close();
		readReadersData(noReaders, numberReaders);
		numberReaders++;
		if (numberReaders == 1)
			noReaders[0].id = 10001;
		else if(numberReaders >= 2)
			noReaders[numberReaders - 1].id = noReaders[numberReaders - 2].id + 1;
		cout << "Doc gia thu " << numberReaders << endl;
		cout << "Ma doc gia (cap tu dong): " << noReaders[numberReaders - 1].id << endl;
		cout << "Nhap ho ten (VIET IN HOA): "; cin.ignore(); getline(cin, noReaders[numberReaders - 1].nameReader);
		cout << "Nhap cmnd: "; getline(cin, noReaders[numberReaders - 1].cmnd);
		cout << "Nhap gioi tinh (VIET IN HOA): "; getline(cin, noReaders[numberReaders - 1].gender);
		if (noReaders[numberReaders - 1].gender != "NAM" && noReaders[numberReaders - 1].gender != "NU")
		{
			while (1 < 2)
			{
				cout << "Khong hop le.\nVui long nhap lai gioi tinh (viet in hoa): "; getline(cin, noReaders[numberReaders - 1].gender);
				if (noReaders[numberReaders - 1].gender == "NAM" || noReaders[numberReaders - 1].gender == "NU")
					break;
			}
		}
		cout << "Nhap email: "; getline(cin, noReaders[numberReaders - 1].email);
		cout << "Nhap dia chi: "; getline(cin, noReaders[numberReaders - 1].address);
		cout << "Nhap ngay sinh: \n";
		cin >> noReaders[numberReaders - 1].dob.day;
		cin >> noReaders[numberReaders - 1].dob.month;
		cin >> noReaders[numberReaders - 1].dob.year;
		cout << "Nhap ngay lap the: \n";
		cin >> noReaders[numberReaders - 1].created.day;
		cin >> noReaders[numberReaders - 1].created.month;
		cin >> noReaders[numberReaders - 1].created.year;
		noReaders[numberReaders - 1].expired.day = noReaders[numberReaders - 1].created.day;
		noReaders[numberReaders - 1].expired.month = noReaders[numberReaders - 1].created.month;
		noReaders[numberReaders - 1].expired.year = noReaders[numberReaders - 1].created.year + 4;
		cout << "Ngay het han: " << noReaders[numberReaders - 1].expired.day << "/" << noReaders[numberReaders - 1].expired.month << "/" << noReaders[numberReaders - 1].expired.year;
		f2.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers.txt", ios::out);
		f2 << numberReaders << endl;
		f2.close();

		writeReadersData(noReaders, numberReaders); 

		int next;
		cout << "\nBan co muon tiep tuc them doc gia? Co, nhan '1'. Khong, nhan so bat ky ngoai '1'\n";
		cout << "Lua chon cua ban: ";
		cin >> next;
		if (next == 1)
		{
			continue;
		}
		else
			break;
	}	
	system("pause");
}

// Hàm ghi thông tin độc giả vào file "Readers.txt"
// Tham số truyền vào là thông tin các độc giả theo kiểu reader và số lượng độc giả hiện có trong thư viện
void writeReadersData(reader noReaders[], int numberReaders)
{
	fstream f1;
	f1.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Readers.txt", ios::out | ios::app);
	if (f1.fail())
	{
		cout << "Failed to open this file to write down data!" << endl;
		return;
	}
	else
	{
		f1 << noReaders[numberReaders - 1].id << endl;
		f1 << noReaders[numberReaders - 1].nameReader << endl;
		f1 << noReaders[numberReaders - 1].cmnd << endl;
		f1 << noReaders[numberReaders - 1].gender << endl;
		f1 << noReaders[numberReaders - 1].email << endl;
		f1 << noReaders[numberReaders - 1].address << endl;
		f1 << noReaders[numberReaders - 1].dob.day << " " << noReaders[numberReaders - 1].dob.month << " " << noReaders[numberReaders - 1].dob.year << endl;
		f1 << noReaders[numberReaders - 1].created.day << " " << noReaders[numberReaders - 1].created.month << " " << noReaders[numberReaders - 1].created.year << endl;
		f1 << noReaders[numberReaders - 1].expired.day << " " << noReaders[numberReaders - 1].expired.month << " " << noReaders[numberReaders - 1].expired.year << endl;
	}
	f1.close();
}

// Hàm đọc dữ liệu từ file "Readers.txt"
// Tham số truyền vào là thông tin các độc giả theo kiểu reader và số lượng độc giả hiện có trong thư viện
void readReadersData(reader noReaders[], int numberReaders)
{
	fstream f1;
	f1.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Readers.txt", ios::in);
	for (int i = 0; i < numberReaders; i++)
	{
		f1 >> noReaders[i].id;
		f1.ignore();
		getline(f1, noReaders[i].nameReader);
		getline(f1, noReaders[i].cmnd);
		getline(f1, noReaders[i].gender);
		getline(f1, noReaders[i].email);
		getline(f1, noReaders[i].address);
		f1 >> noReaders[i].dob.day;
		f1 >> noReaders[i].dob.month;
		f1 >> noReaders[i].dob.year;
		f1 >> noReaders[i].created.day;
		f1 >> noReaders[i].created.month;
		f1 >> noReaders[i].created.year;
		f1 >> noReaders[i].expired.day;
		f1 >> noReaders[i].expired.month;
		f1 >> noReaders[i].expired.year;
	}
	f1.close();
}

// Hàm xuất danh sách độc giả
// Tham số truyền vào là thông tin các độc giả theo kiểu reader và số lượng độc giả hiện có trong thư viện
void listOfReaders(reader noReaders[], int numberReaders)
{
	int Row = 2;
	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(70, Row);
	cout << "XEM DANH SACH DOC GIA\n"; Row += 2;
	cout << endl;
	fstream f2;
	f2.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers.txt", ios::in);
	f2 >> numberReaders;
	f2.close();

	readReadersData(noReaders, numberReaders);
	if (numberReaders == 0)
	{
		cout << "Chua co danh sach doc gia!" << endl;
		system("pause");
		return;
	}
	for (int i = 0; i < numberReaders; i++)
	{
		cout << "Doc gia thu " << i + 1 << ": ";
		cout << "\t\tMa doc gia: " << noReaders[i].id << endl;;
		cout << "\t\tHo ten: " << noReaders[i].nameReader << endl;
		cout << "\t\tCMND: " << noReaders[i].cmnd << endl;
		cout << "\t\tGioi tinh: " << noReaders[i].gender << endl;
		cout << "\t\tEmail: " << noReaders[i].email << endl;
		cout << "\t\tDia chi: " << noReaders[i].address << endl;
		cout << "\t\tNgay sinh: " << noReaders[i].dob.day << "/" << noReaders[i].dob.month << "/" << noReaders[i].dob.year << endl;
		cout << "\t\tNgay lap the: " << noReaders[i].created.day << "/" << noReaders[i].created.month << "/" << noReaders[i].created.year << endl;
		cout << "\t\tNgay het han: " << noReaders[i].expired.day << "/" << noReaders[i].expired.month << "/" << noReaders[i].expired.year << endl;
		cout << endl;
	}
	system("pause");
}

// Hàm chỉnh sửa thông tin độc giả
// Tham số truyền vào là thông tin các độc giả theo kiểu reader và số lượng độc giả hiện có trong thư viện
void editReaders(reader noReaders[], int numberReaders)
{
	string CODE;
	int Index = -1;
	int Row = 2;
	int choice = 0;
	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(67, Row);
	cout << "CHINH SUA THONG TIN DOC GIA\n"; Row += 2;
	gotoxy(5, Row);

	fstream f2;
	f2.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers.txt", ios::in);
	f2 >> numberReaders;
	f2.close();

	if (numberReaders == 0)
	{
		cout << "CHUA CO DOC GIA DE CHINH SUA\n";
		system("pause");
		return;
	}

	readReadersData(noReaders, numberReaders);
	cout << "Nhap CMND cua ban de chinh sua thong tin: "; Row++;
	cin.ignore();
	getline(cin, CODE);
	for (int i = 0; i < numberReaders; i++)
	{
		if (CODE == noReaders[i].cmnd)
		{
			Index = i;
			break;
		}
	}
	if (Index == -1)
	{
		cout << "Khong co doc gia voi CMND la " << CODE << endl;
		system("pause");
	}
	else if (Index != -1)
	{
		cout << "Ma doc gia: " << noReaders[Index].id << endl; Row++;
		cout << "Ho va ten: " << noReaders[Index].nameReader << endl; Row++;
		cout << "Gioi tinh: " << noReaders[Index].gender << endl; Row++;
		cout << "CMND: " << noReaders[Index].cmnd << endl; Row++;
		cout << "Dia chi: " << noReaders[Index].address << endl; Row++;
		cout << "Email: " << noReaders[Index].email << endl; Row++;
		cout << "Ngay sinh: " << noReaders[Index].dob.day << "/" << noReaders[Index].dob.month << "/" << noReaders[Index].dob.year << endl; Row++;
		cout << "Ngay lap the: " << noReaders[Index].created.day << "/" << noReaders[Index].created.month << "/" << noReaders[Index].created.year << endl; Row++;
		cout << "Ngay het han: " << noReaders[Index].expired.day << "/" << noReaders[Index].expired.month << "/" << noReaders[Index].expired.year << endl; Row += 2;

		gotoxy(10, Row);
		cout << "0 : LUU THONG TIN VA TRO VE MAN HINH CHINH\n"; Row += 2;
		gotoxy(10, Row);
		cout << "1 : SUA TEN DOC GIA\n"; Row += 2;
		gotoxy(10, Row);
		cout << "2 : SUA GIOI TINH\n"; Row += 2;
		gotoxy(10, Row);
		cout << "3 : SUA CMND\n"; Row += 2;
		gotoxy(10, Row);
		cout << "4 : SUA DIA CHI\n"; Row += 2;
		gotoxy(10, Row);
		cout << "5 : SUA EMAIL\n"; Row += 2;
		gotoxy(10, Row);
		cout << "6 : SUA NGAY THANG NAM SINH\n"; Row += 2;
		gotoxy(10, Row);
		cout << "7 : SUA NGAY LAP THE\n"; Row += 2;

		while (1 < 2)
		{
			int choice;
			cout << endl; Row++;
			cout << "NHAP VAO LUA CHON CUA BAN: "; cin >> choice; Row++;
			if (choice == 0)
			{
				system("cls");
				refreshReaders(noReaders, numberReaders);
				Row = 2;
				gotoxy(70, Row);
				cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
				gotoxy(67, Row);
				cout << "Ma doc gia: " << noReaders[Index].id << endl; Row++;
				cout << "Ho va ten: " << noReaders[Index].nameReader << endl; Row++;
				cout << "Gioi tinh: " << noReaders[Index].gender << endl; Row++;
				cout << "CMND: " << noReaders[Index].cmnd << endl; Row++;
				cout << "Dia chi: " << noReaders[Index].address << endl; Row++;
				cout << "Email: " << noReaders[Index].email << endl; Row++;
				cout << "Ngay sinh: " << noReaders[Index].dob.day << "/" << noReaders[Index].dob.month << "/" << noReaders[Index].dob.year << endl; Row++;
				cout << "Ngay lap the: " << noReaders[Index].created.day << "/" << noReaders[Index].created.month << "/" << noReaders[Index].created.year << endl; Row++;
				cout << "Ngay het han: " << noReaders[Index].expired.day << "/" << noReaders[Index].expired.month << "/" << noReaders[Index].expired.year << endl; Row += 2;
				break;
			}
			else if (choice == 1)
			{
				cout << "Ho va ten (viet in hoa) sau chinh sua: "; Row++;
				cin.ignore();
				getline(cin, noReaders[Index].nameReader);
			}
			else if (choice == 2)
			{
				cout << "Gioi tinh (viet in hoa) sau chinh sua: "; Row++;
				cin.ignore();
				getline(cin, noReaders[Index].gender);
				if (noReaders[numberReaders - 1].gender != "NAM" && noReaders[numberReaders - 1].gender != "NU")
				{
					while (1 < 2)
					{
						cout << "Khong hop le.\nVui long nhap lai gioi tinh (viet in hoa): "; getline(cin, noReaders[numberReaders - 1].gender); Row += 2;
						if (noReaders[numberReaders - 1].gender == "NAM" || noReaders[numberReaders - 1].gender == "NU")
							break;
					}
				}
			}
			else if (choice == 3)
			{
				cout << "CMND sau chinh sua: "; Row++;
				cin.ignore();
				getline(cin, noReaders[Index].cmnd);
			}
			else if (choice == 4)
			{
				cout << "Dia chi sau chinh sua: "; Row++;
				cin.ignore();
				getline(cin, noReaders[Index].address);
			}
			else if (choice == 5)
			{
				cout << "Email sau chinh sua: "; Row++;
				cin.ignore();
				getline(cin, noReaders[Index].email);
			}
			else if (choice == 6)
			{
				cout << "Ngay sinh sau chinh sua: ";
				cin >> noReaders[Index].dob.day;
				gotoxy(28, Row - 1); cout << "/";
				cin >> noReaders[Index].dob.month;
				gotoxy(31, Row - 1); cout << "/";
				cin >> noReaders[Index].dob.year;
				Row++;
			}
			else if (choice == 7)
			{
				cout << "Ngay lap the sau chinh sua: ";
				cin >> noReaders[Index].created.day;
				gotoxy(31, Row - 1); cout << "/";
				cin >> noReaders[Index].created.month;
				gotoxy(34, Row - 1); cout << "/";
				cin >> noReaders[Index].created.year;
				Row++;
				cout << "Ngay het han sau chinh sua: ";
				noReaders[Index].created.day = noReaders[Index].expired.day;
				noReaders[Index].created.month = noReaders[Index].expired.month;
				noReaders[Index].created.year = noReaders[Index].expired.year + 4;
				cout << noReaders[Index].created.day;
				gotoxy(31, Row - 1); cout << "/";
				cout << noReaders[Index].created.month;
				gotoxy(34, Row - 1); cout << "/";
				cout << noReaders[Index].created.year;
				Row++;
			}
		}
		system("pause");
	}
}

// Hàm ghi thông tin độc giả sau chỉnh sửa, xóa
// Tham số truyền vào là thông tin các độc giả theo kiểu reader và số lượng độc giả hiện có trong thư viện
void refreshReaders(reader noReaders[], int numberReaders)
{
	fstream f1;
	f1.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Readers.txt", ios::out);
	for (int i = 0; i < numberReaders; i++)
	{
		if (f1.fail())
		{
			cout << "Failed to open this file to write down data!" << endl;
			return;
		}
		else
		{
			f1 << noReaders[i].id << endl;
			f1 << noReaders[i].nameReader << endl;
			f1 << noReaders[i].cmnd << endl;
			f1 << noReaders[i].gender << endl;
			f1 << noReaders[i].email << endl;
			f1 << noReaders[i].address << endl;
			f1 << noReaders[i].dob.day << " " << noReaders[i].dob.month << " " << noReaders[i].dob.year << endl;
			f1 << noReaders[i].created.day << " " << noReaders[i].created.month << " " << noReaders[i].created.year << endl;
			f1 << noReaders[i].expired.day << " " << noReaders[i].expired.month << " " << noReaders[i].expired.year << endl;
		}
	}
	f1.close();
}

// Hàm xóa một độc giả
// Tham số truyền vào là thông tin các độc giả theo kiểu reader và số lượng độc giả hiện có trong thư viện
void deleteReaders(reader noReaders[], int numberReaders)
{
	string CODE;
	int Index = -1;
	int Row = 2;
	int choice = 0;
	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(67, Row);
	cout << "XOA DOC GIA THEO CMND\n"; Row += 2;
	gotoxy(5, Row);

	fstream f2;
	f2.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers.txt", ios::in);
	f2 >> numberReaders;
	f2.close();

	if (numberReaders == 0)
	{
		cout << "CHUA CO DOC GIA DE XOA\n";
		system("pause");
		return;
	}

	readReadersData(noReaders, numberReaders);
	cout << "Nhap CMND cua ban de xoa doc gia: "; Row++;
	cin.ignore();
	getline(cin, CODE);
	for (int i = 0; i < numberReaders; i++)
	{
		if (CODE == noReaders[i].cmnd)
		{
			Index = i;
			break;
		}
	}
	if (Index == -1)
	{
		cout << "Khong co doc gia voi CMND la " << CODE << endl;
		system("pause");
	}
	else if (Index != -1)
	{
		cout << "Ma doc gia: " << noReaders[Index].id << endl; Row++;
		cout << "Ho va ten: " << noReaders[Index].nameReader << endl; Row++;
		cout << "Gioi tinh: " << noReaders[Index].gender << endl; Row++;
		cout << "CMND: " << noReaders[Index].cmnd << endl; Row++;
		cout << "Dia chi: " << noReaders[Index].address << endl; Row++;
		cout << "Email: " << noReaders[Index].email << endl; Row++;
		cout << "Ngay sinh: " << noReaders[Index].dob.day << "/" << noReaders[Index].dob.month << "/" << noReaders[Index].dob.year << endl; Row++;
		cout << "Ngay lap the: " << noReaders[Index].created.day << "/" << noReaders[Index].created.month << "/" << noReaders[Index].created.year << endl; Row++;
		cout << "Ngay het han: " << noReaders[Index].expired.day << "/" << noReaders[Index].expired.month << "/" << noReaders[Index].expired.year << endl; Row += 2;
		cout << "Ban co xac nhan xoa doc gia? Luu y: Khong the hoan tac sau khi xac nhan\n"; Row++;
		int DeleteOrNot;
		cout << "Neu co, nhap '1'. Neu khong, nhap '0' de TRO VE\n";
		cout << "Lua chon cua ban: "; cin >> DeleteOrNot;
		if (DeleteOrNot == 0)
			return;
		else if (DeleteOrNot == 1)
		{
			cout << "DA XOA DOC GIA '" << noReaders[Index].nameReader << "' CO SO CMND LA " << noReaders[Index].cmnd << endl; Row++;
			numberReaders--;
			fstream f2;
			f2.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers.txt", ios::out);
			f2 << numberReaders;
			f2.close();

			int temp = Index;
			for (temp; temp < numberReaders; temp++)
			{
				noReaders[temp].id = noReaders[temp + 1].id;
				noReaders[temp].nameReader = noReaders[temp + 1].nameReader;
				noReaders[temp].cmnd = noReaders[temp + 1].cmnd;
				noReaders[temp].email = noReaders[temp + 1].email;
				noReaders[temp].address = noReaders[temp + 1].address;
				noReaders[temp].gender = noReaders[temp + 1].gender;
				noReaders[temp].dob.day = noReaders[temp + 1].dob.day;
				noReaders[temp].dob.month = noReaders[temp + 1].dob.month;
				noReaders[temp].dob.year = noReaders[temp + 1].dob.year;
				noReaders[temp].created.day = noReaders[temp + 1].created.day;
				noReaders[temp].created.month = noReaders[temp + 1].created.month;
				noReaders[temp].created.year = noReaders[temp + 1].created.year;
				noReaders[temp].expired.day = noReaders[temp + 1].expired.day;
				noReaders[temp].expired.month = noReaders[temp + 1].expired.month;
				noReaders[temp].expired.year = noReaders[temp + 1].expired.year;
			}
			refreshReaders(noReaders, numberReaders);
			system("pause");
		}
	}
}

// Hàm tìm kiếm thông tin một độc giả theo CMND
// Tham số truyền vào là thông tin các độc giả theo kiểu reader và số lượng độc giả hiện có trong thư viện
void findReadersByCMND(reader noReaders[], int numberReaders)
{
	int Row = 2;
	int Index = -1;
	string CODE;
	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(68, Row);
	cout << "TIM KIEM DOC GIA THEO CMND\n"; Row += 2;

	fstream f2;
	f2.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers.txt", ios::in);
	f2 >> numberReaders;
	f2.close();
	readReadersData(noReaders, numberReaders);

	if (numberReaders == 0)
	{
		cout << "CHUA CO DOC GIA DE TIM KIEM\n";
		system("pause");
	}
	else
	{
		cout << "Nhap CMND cua ban de tim kiem thong tin: "; Row++;
		cin.ignore();
		getline(cin, CODE);
		for (int i = 0; i < numberReaders; i++)
		{
			if (CODE == noReaders[i].cmnd)
			{
				Index = i;
				break;
			}
		}

		if (Index == -1)
		{
			cout << "Khong co doc gia co so CMND la " << CODE << endl;
			system("pause");
		}
		else if (Index != -1)
		{
			cout << endl;
			cout << "Ma doc gia: " << noReaders[Index].id << endl;
			cout << "Ho va ten: " << noReaders[Index].nameReader << endl;
			cout << "Gioi tinh: " << noReaders[Index].gender << endl;
			cout << "CMND: " << noReaders[Index].cmnd << endl;
			cout << "Dia chi: " << noReaders[Index].address << endl;
			cout << "Email: " << noReaders[Index].email << endl;
			cout << "Ngay sinh: " << noReaders[Index].dob.day << "/" << noReaders[Index].dob.month << "/" << noReaders[Index].dob.year << endl;
			cout << "Ngay lap the: " << noReaders[Index].created.day << "/" << noReaders[Index].created.month << "/" << noReaders[Index].created.year << endl;
			cout << "Ngay het han: " << noReaders[Index].expired.day << "/" << noReaders[Index].expired.month << "/" << noReaders[Index].expired.year << endl; Row += 5;
			system("pause");
		}
	}
}

// Hàm tìm kiếm độc giả theo họ tên
// Tham số truyền vào là thông tin các độc giả theo kiểu reader và số lượng độc giả hiện có trong thư viện
void findReadersByName(reader noReaders[], int numberReaders)
{
	int Row = 2;
	int Index = -1;
	int count = 0;
	int temp = 0;
	string NAME;
	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(65, Row);
	cout << "TIM KIEM DOC GIA THEO HO VA TEN\n"; Row += 2;

	fstream f2;
	f2.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers.txt", ios::in);
	f2 >> numberReaders;
	f2.close();
	readReadersData(noReaders, numberReaders);

	if (numberReaders == 0)
	{
		cout << "CHUA CO DOC GIA DE TIM KIEM\n";
		system("pause");
	}
	else
	{
		cout << "\nNhap ho ten cua ban de tim kiem thong tin (viet in hoa): "; Row += 2;
		cin.ignore();
		getline(cin, NAME);
		for (int i = 0; i < numberReaders; i++)
		{
			if (NAME == noReaders[i].nameReader)
			{
				count++;
			}
		}

		if (count == 0)
		{
			cout << "Khong tim thay doc gia " << NAME << endl;
			system("pause");
		}

		else if (count > 0)
		{
			cout << endl;
			cout << "Da tim thay " << count << " doc gia co ten la " << NAME << endl;
			for (int i = 0; i < numberReaders; i++)
			{
				if (NAME == noReaders[i].nameReader)
				{
					temp++;
					Index = i;
					cout << "DOC GIA THU " << temp << ": " << endl;
					cout << endl;
					cout << "Ma doc gia: " << noReaders[Index].id << endl;
					cout << "Ho va ten: " << noReaders[Index].nameReader << endl;
					cout << "Gioi tinh: " << noReaders[Index].gender << endl;
					cout << "CMND: " << noReaders[Index].cmnd << endl;
					cout << "Dia chi: " << noReaders[Index].address << endl;
					cout << "Email: " << noReaders[Index].email << endl;
					cout << "Ngay sinh: " << noReaders[Index].dob.day << "/" << noReaders[Index].dob.month << "/" << noReaders[Index].dob.year << endl;
					cout << "Ngay lap the: " << noReaders[Index].created.day << "/" << noReaders[Index].created.month << "/" << noReaders[Index].created.year << endl;
					cout << "Ngay het han: " << noReaders[Index].expired.day << "/" << noReaders[Index].expired.month << "/" << noReaders[Index].expired.year << endl;
					cout << endl << endl;
				}
			}
			system("pause");
		}
	}
}
