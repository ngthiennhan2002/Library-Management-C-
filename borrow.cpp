#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include "MyFunction.h"
using namespace std;

void sevenDaysAfter(borrow ReadersBorrow[], int numBorrowReaders)
{
	switch (ReadersBorrow[numBorrowReaders - 1].expectedReturn.month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10:
		if (ReadersBorrow[numBorrowReaders - 1].expectedReturn.day > 31)
		{
			ReadersBorrow[numBorrowReaders - 1].expectedReturn.day -= 31;
			ReadersBorrow[numBorrowReaders - 1].expectedReturn.month++;
			break;
		}
		
	case 2:
		if (ReadersBorrow[numBorrowReaders - 1].expectedReturn.year % 400 == 0 || (ReadersBorrow[numBorrowReaders - 1].expectedReturn.year % 4 == 0 &&
			ReadersBorrow[numBorrowReaders - 1].expectedReturn.year % 100 != 0))
		{
			if (ReadersBorrow[numBorrowReaders - 1].expectedReturn.day > 29)
			{
				ReadersBorrow[numBorrowReaders - 1].expectedReturn.day -= 29;
				ReadersBorrow[numBorrowReaders - 1].expectedReturn.month = 3;
				break;
			}
		}
		else
		{
			if (ReadersBorrow[numBorrowReaders - 1].expectedReturn.day > 28)
			{
				ReadersBorrow[numBorrowReaders - 1].expectedReturn.day -= 28;
				ReadersBorrow[numBorrowReaders - 1].expectedReturn.month = 3;
				break;
			}
		}
	case 12:
		if (ReadersBorrow[numBorrowReaders - 1].expectedReturn.day > 31)
		{
			ReadersBorrow[numBorrowReaders - 1].expectedReturn.day -= 31;
			ReadersBorrow[numBorrowReaders - 1].expectedReturn.month = 1;
			ReadersBorrow[numBorrowReaders - 1].expectedReturn.year++;
			break;
		}
	}
}

// Hàm ghi dữ liệu độc giả mượn sách
// Tham số truyền vào là danh sách các độc giả đã thực hiện việc mượn sách và số lượng độc giả đã mượn
void writeBorrowData(borrow ReadersBorrow[], int numBorrowReaders)
{
	fstream f5;
	f5.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Readers borrowed.txt", ios::out | ios::app);
	f5 << ReadersBorrow[numBorrowReaders - 1].id << endl;
	f5 << ReadersBorrow[numBorrowReaders - 1].borrowDay.day << " " << ReadersBorrow[numBorrowReaders - 1].borrowDay.month << " " << ReadersBorrow[numBorrowReaders - 1].borrowDay.year << endl;
	f5 << ReadersBorrow[numBorrowReaders - 1].expectedReturn.day << " " << ReadersBorrow[numBorrowReaders - 1].expectedReturn.month << " " << ReadersBorrow[numBorrowReaders - 1].expectedReturn.year << endl;
	f5 << ReadersBorrow[numBorrowReaders - 1].numBorrow << endl;
	for (int i = 0; i < ReadersBorrow[numBorrowReaders - 1].numBorrow; i++)
	{
		f5 << ReadersBorrow[numBorrowReaders - 1].bookInfo[i].ISBN << " ";
	}
	f5 << endl;
	f5.close();
}

// Hàm đọc dữ liệu độc giả mượn sách
// Tham số truyền vào là danh sách các độc giả đã thực hiện việc mượn sách và số lượng độc giả đã mượn
void readBorrowData(borrow ReadersBorrow[], int numBorrowReaders)
{
	fstream f5;
	f5.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Readers borrowed.txt", ios::in);
	for (int i = 0; i < numBorrowReaders; i++)
	{
		f5 >> ReadersBorrow[i].id;
		f5 >> ReadersBorrow[i].borrowDay.day;
		f5 >> ReadersBorrow[i].borrowDay.month;
		f5 >> ReadersBorrow[i].borrowDay.year;
		f5 >> ReadersBorrow[i].expectedReturn.day;
		f5 >> ReadersBorrow[i].expectedReturn.month;
		f5 >> ReadersBorrow[i].expectedReturn.year;
		f5 >> ReadersBorrow[i].numBorrow;
		for (int j = 0; j < ReadersBorrow[i].numBorrow; j++)
		{
			f5 >> ReadersBorrow[i].bookInfo[j].ISBN;
		}
	}
	f5.close();
}


// Hàm tính khoảng cách ngày đến đầu năm đó
// Tham số truyền vào là ngày tháng năm
// Tham số trả ra là khoảng cách 1/1/year đến ngày hôm đó
int daysFromFirstDay(int day, int month, int year)
{
	int total = day;
	for (int i = 1; i < month; i++)
	{
		switch (i)
		{
		case 1: case 3: case 5: case 7: case 8: case 10:
			total += 31; break;
		case 2: 
			if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
			{
				total += 29; break;
			}
			else
			{
				total += 28; break;
			}
		case 4: case 6: case 9: case 11:
			total += 30; break;
		}
	}
	return total;
}

// Hàm tạo phiếu mượn sách
/* Tham số truyền vào danh sách độc giả, danh sách sách, số lượng độc giả, số lượng sách trong thư viện,
					và danh sách độc giả mượn, số lương độc giả mượn sách*/
void borrowBooks(borrow ReadersBorrow[], reader noReaders[], book noBooks[],
	int numberReaders, int numberBooks, int& numBorrowReaders)
{
	fstream f2;
	f2.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers.txt", ios::in);
	f2 >> numberReaders;
	f2.close();
	readReadersData(noReaders, numberReaders);

	fstream f4;
	f4.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Books.txt", ios::in);
	f4 >> numberBooks;
	f4.close();
	readBooksData(noBooks, numberBooks);

	int Row = 2;
	int Index = -1;
	bool flag = false;

	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(73, Row);
	cout << "PHIEU MUON SACH\n\n"; Row += 2;

	fstream f6;
	f6.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers borrowed.txt", ios::in);
	f6 >> numBorrowReaders;
	f6.close();
	readBorrowData(ReadersBorrow, numBorrowReaders);
	numBorrowReaders++;
	gotoxy(0, Row);
	cout << "Nhap ma doc gia: "; cin >> ReadersBorrow[numBorrowReaders - 1].id; Row++;

	for (int i = 0; i < numBorrowReaders - 1; i++)
	{
		if (ReadersBorrow[numBorrowReaders - 1].id == ReadersBorrow[i].id)
		{
			cout << "Ban hien van con sach dang muon, xin tra sach de tiep tuc\n";
			system("pause");
			return;
		}
	}
	for (int i = 0; i < numberReaders; i++)
	{
		if (ReadersBorrow[numBorrowReaders - 1].id == noReaders[i].id)
		{
			Index = i;
			break;
		}
	}
	if (Index == -1)
	{
		cout << "Khong tim thay ma doc gia\n";
		numBorrowReaders--;
		f6.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers borrowed.txt", ios::out);
		f6 << numBorrowReaders;
		f6.close();
		system("pause");
		return;
	}
	else
	{
		cout << "Nhap ngay muon sach: "; cin >> ReadersBorrow[numBorrowReaders - 1].borrowDay.day;
		gotoxy(24, Row); cout << "/"; cin >> ReadersBorrow[numBorrowReaders - 1].borrowDay.month;
		gotoxy(27, Row); cout << "/"; cin >> ReadersBorrow[numBorrowReaders - 1].borrowDay.year;
		Row++;

		ReadersBorrow[numBorrowReaders - 1].expectedReturn.day = ReadersBorrow[numBorrowReaders - 1].borrowDay.day + 7;
		ReadersBorrow[numBorrowReaders - 1].expectedReturn.month = ReadersBorrow[numBorrowReaders - 1].borrowDay.month;
		ReadersBorrow[numBorrowReaders - 1].expectedReturn.year = ReadersBorrow[numBorrowReaders - 1].borrowDay.year;
		sevenDaysAfter(ReadersBorrow, numBorrowReaders);
		cout << "Ngay tra sach du kien (7 ngay ke tu ngay muon): " << ReadersBorrow[numBorrowReaders - 1].expectedReturn.day << "/"
			<< ReadersBorrow[numBorrowReaders - 1].expectedReturn.month << "/" << ReadersBorrow[numBorrowReaders - 1].expectedReturn.year << endl; Row++;
		cout << "Nhap so sach ban muon muon (toi da 3 quyen va chi muon mot lan): "; Row++;
		cin >> ReadersBorrow[numBorrowReaders - 1].numBorrow;
		if (ReadersBorrow[numBorrowReaders - 1].numBorrow > 3)
		{
			cout << "Ban khong the muon hon 3 quyen!\n"; Row++;
			while (1 == 1)
			{
				cout << "Nhap lai so sach ban muon muon (toi da 3 quyen): "; Row++;
				cin >> ReadersBorrow[numBorrowReaders - 1].numBorrow;
				if (ReadersBorrow[numBorrowReaders - 1].numBorrow <= 3 && ReadersBorrow[numBorrowReaders - 1].numBorrow > 0)
					break;
			}
		}
			
		for (int i = 0; i < ReadersBorrow[numBorrowReaders - 1].numBorrow;)
		{
			flag == false;
			cout << "Ma ISBN cua quyen thu " << i + 1 << ": "; cin >> ReadersBorrow[numBorrowReaders - 1].bookInfo[i].ISBN;
			for (int j = 0; j < numberBooks; j++)
			{
				if (ReadersBorrow[numBorrowReaders - 1].bookInfo[i].ISBN == noBooks[j].ISBN)
				{
					ReadersBorrow[numBorrowReaders - 1].bookInfo[i].bookName = noBooks[j].bookName;
					cout << "Ten sach: " << ReadersBorrow[numBorrowReaders - 1].bookInfo[i].bookName << endl;
					flag = true;
					noBooks[j].numberOfThisBook--;
					if (noBooks[j].numberOfThisBook < 0)
					{
						cout << "Quyen nay hien da het! Xin muon sach khac!\n";
						noBooks[j].numberOfThisBook = 0;
						break;
					}
					else
					{
						i++;
						break;
					}
				}
			}
			if (flag == false)
			{
				cout << "Khong tim thay sach, xin nhap lai ma ISBN!\n";
			}
		}

		int DeleteOrNot;
		cout << "\nBan co xac nhan muon sach? Luu y: Khong the hoan tac sau khi xac nhan\n"; Row++;
		cout << "Neu co, nhap '1'. Neu khong, nhap '0' de tro lai\n"; Row++;
		cout << "Lua chon cua ban: "; cin >> DeleteOrNot; Row++;
		if (DeleteOrNot == 0)
			return;
		else if (DeleteOrNot == 1)
		{
			system("cls");
			int Row = 2;
			int Index = -1;
			bool flag = false;

			system("cls");
			gotoxy(70, Row);
			cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
			gotoxy(73, Row);
			cout << "PHIEU MUON SACH\n\n"; Row += 2;
			cout << "Ma doc gia: " << ReadersBorrow[numBorrowReaders - 1].id << endl;
			cout << "Ngay muon sach: " << ReadersBorrow[numBorrowReaders - 1].borrowDay.day << "/" << ReadersBorrow[numBorrowReaders - 1].borrowDay.month << "/" << ReadersBorrow[numBorrowReaders - 1].borrowDay.year << endl;
			cout << "Ngay tra sach du kien: " << ReadersBorrow[numBorrowReaders - 1].expectedReturn.day << "/" << ReadersBorrow[numBorrowReaders - 1].expectedReturn.month << "/" << ReadersBorrow[numBorrowReaders - 1].expectedReturn.year << endl;
			cout << "So sach ban muon: " << ReadersBorrow[numBorrowReaders - 1].numBorrow << endl;
			for (int i = 0; i < ReadersBorrow[numBorrowReaders - 1].numBorrow; i++)
			{
				cout << "Quyen thu " << i + 1 << ": " << ReadersBorrow[numBorrowReaders - 1].bookInfo[i].ISBN;
				cout << "\t Ten sach: " << ReadersBorrow[numBorrowReaders - 1].bookInfo[i].bookName << endl;
			}
			cout << endl;
			cout << "Ban da dang ky muon sach thanh cong. Hay den thu vien den nhan sach vao dung ngay da dang ky.\n";
			cout << "Luu y: Moi sach duoc muon toi da trong 7 ngay, neu qua han se phat tien 5.000 dong/ngay\n";
			cout << endl;

			fstream f3;
			f3.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Books.txt", ios::out);
			if (f3.fail())
			{
				cout << "Failed to open this file to write down data!" << endl;
				return;
			}
			else
			{
				for (int i = 0; i < numberBooks; i++)
				{
					f3 << noBooks[i].ISBN << endl;
					f3 << noBooks[i].bookName << endl;
					f3 << noBooks[i].author << endl;
					f3 << noBooks[i].publishers << endl;
					f3 << noBooks[i].bookGenre << endl;
					f3 << noBooks[i].publishYear << endl;
					f3 << noBooks[i].bookPrice << endl;
					f3 << noBooks[i].numberOfThisBook << endl;
				}
			}
			f3.close();

			fstream f6;
			f6.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers borrowed.txt", ios::out);
			if (f6.fail())
			{
				cout << "Failed to open this file to write down data!" << endl;
				return;
			}
			else
			{
				f6 << numBorrowReaders;
			}
			f6.close();

			writeBorrowData(ReadersBorrow, numBorrowReaders);
		}
		system("pause");
	}
}

// Hàm tạo phiếu trả sách
/* Tham số truyền vào danh sách sách, số lượng sách trong thư viện và danh sách độc giả mượn, số lương độc giả mượn sách*/
void backBooks(borrow ReadersBorrow[], book noBooks[], int numberBooks, int& numBorrowReaders)
{
	fstream f4;
	f4.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Books.txt", ios::in);
	f4 >> numberBooks;
	f4.close();
	readBooksData(noBooks, numberBooks);

	int CODE;
	int Row = 2;
	int Index = -1;
	bool flag = false;

	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(73, Row);
	cout << "PHIEU TRA SACH\n\n"; Row += 2;

	fstream f6;
	f6.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers borrowed.txt", ios::in);
	f6 >> numBorrowReaders;
	f6.close();
	readBorrowData(ReadersBorrow, numBorrowReaders);

	cout << "Nhap ma doc gia: "; cin >> CODE; Row++;

	for (int i = 0; i < numBorrowReaders; i++)
	{
		if (CODE == ReadersBorrow[i].id)
		{
			Index = i;
			break;
		}
	}

	if (Index == -1)
	{
		cout << "Doc gia chua thuc hien viec muon sach!\n";
		system("pause");
		return;
	}
	else
	{
		cout << "Thong tin cua ban: " << endl;
		cout << " - Ma doc gia: " << CODE << endl;
		cout << " - Ngay muon sach: " << ReadersBorrow[Index].borrowDay.day << "/" << ReadersBorrow[Index].borrowDay.month << "/" << ReadersBorrow[Index].borrowDay.year << endl;
		cout << " - Ngay tra sach du kien: " << ReadersBorrow[Index].expectedReturn.day << "/" << ReadersBorrow[Index].expectedReturn.month << "/" << ReadersBorrow[Index].expectedReturn.year << endl;
		cout << " - So quyen ban dang muon: " << ReadersBorrow[Index].numBorrow << endl;
		for (int i = 0; i < ReadersBorrow[Index].numBorrow; i++)
		{
			cout << " - Quyen thu " << i + 1 << ": " << "ISBN: " << ReadersBorrow[Index].bookInfo[i].ISBN << endl;
		}
		cout << "Nhap vao ngay tra sach thuc te: ";
		cin >> ReadersBorrow[Index].realReturn.day;
		cin >> ReadersBorrow[Index].realReturn.month;
		cin >> ReadersBorrow[Index].realReturn.year;

		int t = 0, distance = 0;
		int A = daysFromFirstDay(ReadersBorrow[Index].realReturn.day, ReadersBorrow[Index].realReturn.month, ReadersBorrow[Index].realReturn.year);
		int B = daysFromFirstDay(ReadersBorrow[Index].expectedReturn.day, ReadersBorrow[Index].expectedReturn.month, ReadersBorrow[Index].expectedReturn.year);
		if (ReadersBorrow[Index].expectedReturn.year < ReadersBorrow[Index].realReturn.year)
		{
			for (int i = ReadersBorrow[Index].expectedReturn.year; i < ReadersBorrow[Index].realReturn.year; i++)
			{
				if (i % 400 == 0 || (i % 4 == 0 && i % 100 != 0))
					t += 366;
				else
					t += 365;
			}
			distance = (A + t) - B;
		}
		else if (ReadersBorrow[Index].expectedReturn.year == ReadersBorrow[Index].realReturn.year)
			distance = A - B;
		else if (ReadersBorrow[Index].expectedReturn.year > ReadersBorrow[Index].realReturn.year)
		{
			for (int i = ReadersBorrow[Index].realReturn.year; i < ReadersBorrow[Index].expectedReturn.year; i++)
			{
				if (i % 400 == 0 || (i % 4 == 0 && i % 100 != 0))
					t += 366;
				else
					t += 365;
			}
			distance = A - (B + t);
		}

		ReadersBorrow[Index].late = abs(distance);
		if (distance > 0)
		{
			cout << "Ban da tre han tra sach " << ReadersBorrow[Index].late << " ngay!" << endl;
			cout << "Ban phai chiu phat moi quyen 5000 dong / ngay: " << ReadersBorrow[Index].late * 5000 * ReadersBorrow[Index].numBorrow << " dong" << endl;
		}
		else if (distance == 0)
			cout << "Ban da tra sach dung han!" << endl;
		else
			cout << "Ban da tra sach som " << ReadersBorrow[Index].late << " ngay!" << endl;

		for (int i = 0; i < ReadersBorrow[Index].numBorrow; i++)
		{
			for (int j = 0; i < numberBooks; j++)
			{
				if (ReadersBorrow[Index].bookInfo[i].ISBN == noBooks[j].ISBN)
				{
					noBooks[j].numberOfThisBook++;
					break;
				}
			}
		}
		int temp = Index;
		for (temp; temp < numberBooks; temp++)
		{
			ReadersBorrow[temp].id = ReadersBorrow[temp + 1].id;
			ReadersBorrow[temp].borrowDay.day = ReadersBorrow[temp + 1].borrowDay.day;
			ReadersBorrow[temp].borrowDay.month = ReadersBorrow[temp + 1].borrowDay.month;
			ReadersBorrow[temp].borrowDay.year = ReadersBorrow[temp + 1].borrowDay.year;
			ReadersBorrow[temp].expectedReturn.day = ReadersBorrow[temp + 1].expectedReturn.day;
			ReadersBorrow[temp].expectedReturn.month = ReadersBorrow[temp + 1].expectedReturn.month;
			ReadersBorrow[temp].expectedReturn.year = ReadersBorrow[temp + 1].expectedReturn.year;
			ReadersBorrow[temp].realReturn.day = ReadersBorrow[temp + 1].realReturn.day;
			ReadersBorrow[temp].realReturn.month = ReadersBorrow[temp + 1].realReturn.month;
			ReadersBorrow[temp].realReturn.year = ReadersBorrow[temp + 1].realReturn.year;
			for (int i = 0; i < ReadersBorrow[numBorrowReaders - 1].numBorrow; i++)
			{
				ReadersBorrow[temp].bookInfo[i].ISBN = ReadersBorrow[temp + 1].bookInfo[i].ISBN;
			}
		}

		numBorrowReaders--;

		fstream f3;
		f3.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Books.txt", ios::out);
		if (f3.fail())
		{
			cout << "Failed to open this file to write down data!" << endl;
			return;
		}
		else
		{
			for (int i = 0; i < numberBooks; i++)
			{
				f3 << noBooks[i].ISBN << endl;
				f3 << noBooks[i].bookName << endl;
				f3 << noBooks[i].author << endl;
				f3 << noBooks[i].publishers << endl;
				f3 << noBooks[i].bookGenre << endl;
				f3 << noBooks[i].publishYear << endl;
				f3 << noBooks[i].bookPrice << endl;
				f3 << noBooks[i].numberOfThisBook << endl;
			}
		}
		f3.close();

		fstream f6;
		f6.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers borrowed.txt", ios::out);
		if (f6.fail())
		{
			cout << "Failed to open this file to write down data!" << endl;
			return;
		}
		else
		{
			f6 << numBorrowReaders;
		}
		f6.close();

		fstream f5;
		f5.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Readers borrowed.txt", ios::out);
		for (int i = 0; i < numBorrowReaders; i++)
		{
			f5 << ReadersBorrow[i].id << endl;
			f5 << ReadersBorrow[i].borrowDay.day << " " << ReadersBorrow[i].borrowDay.month << " " << ReadersBorrow[i].borrowDay.year << endl;
			f5 << ReadersBorrow[i].expectedReturn.day << " " << ReadersBorrow[i].expectedReturn.month << " " << ReadersBorrow[i].expectedReturn.year << endl;
			f5 << ReadersBorrow[i].numBorrow << endl;
			for (int j = 0; j < ReadersBorrow[i].numBorrow; j++)
			{
				f5 << ReadersBorrow[i].bookInfo[j].ISBN << " ";
			}
		}
		f5 << endl;
		f5.close();
		system("pause");
	}
}

