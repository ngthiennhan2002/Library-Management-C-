#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include "MyFunction.h"
using namespace std;

// Hàm thống kê số lượng sách
// Tham số truyền vào là thông tin các sách theo kiểu book và số lượng sách hiện có trong thư viện
void statisticBooks(book noBooks[], int numberBooks)
{
	int Row = 2;
	int Index = -1;
	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(69, Row);
	cout << "THONG KE SO LUONG SACH\n\n"; Row += 3;

	fstream f4;
	f4.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Books.txt", ios::in);
	f4 >> numberBooks;
	f4.close();
	readBooksData(noBooks, numberBooks);

	cout << "So luong dau sach hien co trong thu vien: " << numberBooks << endl;
	cout << endl;
	for (int i = 0; i < numberBooks; i++)
	{
		cout << "Sach thu " << i + 1 << ":\tMa ISBN: " << noBooks[i].ISBN << "\t\tTen sach: " << noBooks[i].bookName;
		cout << "\t\tSo quyen: " << noBooks[i].numberOfThisBook << endl;
	}
	system("pause");

}

// Hàm thống kê số lượng sách theo thể loại
// Tham số truyền vào là thông tin các sách theo kiểu book và số lượng sách hiện có trong thư viện
void statisticNumbersByGenres(book noBooks[], int numberBooks)
{
	fstream f4;
	f4.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Books.txt", ios::in);
	f4 >> numberBooks;
	f4.close();
	readBooksData(noBooks, numberBooks);

	int Row = 2;
	string Genres[2000];
	int NumbersOfEachGenre[2000] = { 0 };
	int count = 0;
	int Total = numberBooks;
	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(60, Row);
	cout << "THONG KE SO LUONG SACH THEO THE LOAI\n\n"; Row += 3;

	if (Total == 0)
	{
		cout << "Hien co 0 sach trong thu vien\n";
	}
	else
	{
		for (int i = 0; i < numberBooks; i++)
		{
			Genres[i] = noBooks[i].bookGenre;
		}

		for (int i = 0; i < Total - 1; i++)
		{
			for (int j = i + 1; j < Total; j++)
			{
				if (Genres[i] == Genres[j])
				{
					int index = j;
					for (int k = index + 1; k < Total; k++)
					{
						Genres[k - 1] = Genres[k];
					}
					Total--;
				}
			}
		}

		for (int i = 0; i < Total; i++)
		{
			for (int j = 0; j < numberBooks; j++)
			{
				if (Genres[i] == noBooks[j].bookGenre)
				{
					NumbersOfEachGenre[i]++;
				}
			}
		}

		cout << "\nThong ke the loai sach: \n"; Row++;
		cout << "Tong co " << Total << " the loai sach\n"; Row++;
		for (int i = 0; i < Total; i++)
		{
			cout << "The loai: " << Genres[i];
			gotoxy(35, Row);
			cout << "So luong: " << NumbersOfEachGenre[i] << endl; Row++;
		}
	}

	system("pause");

}

// Hàm thống kê số lượng độc giả
// Tham số truyền vào là thông tin các độc giả theo kiểu reader và số lượng độc giả hiện có trong thư viện
void statisticReaders(reader noReaders[], int numberReaders)
{
	int Row = 2;
	int Index = -1;
	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(68, Row);
	cout << "THONG KE SO LUONG DOC GIA\n\n"; Row += 3;
	fstream f2;
	f2.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers.txt", ios::in);
	f2 >> numberReaders;
	f2.close();
	readReadersData(noReaders, numberReaders);
	cout << "So luong doc gia hien co trong thu vien: " << numberReaders << endl;
	cout << endl;
	for (int i = 0; i < numberReaders; i++)
	{
		cout << "Doc gia thu " << i + 1 << ":\tMa doc gia: " << noReaders[i].id << "\tHo ten: " << noReaders[i].nameReader << endl;
	}
	system("pause");
}

// Hàm thống kê số lượng độc giả theo giới tính
// Tham số truyền vào là thông tin các độc giả theo kiểu reader và số lượng độc giả hiện có trong thư viện
void statisticReadersByGender(reader noReaders[], int numberReaders)
{
	int Row = 2;
	int Index = -1;
	int countMale = 0;
	int countFemale = 0;
	string NAME;
	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(58, Row);
	cout << "THONG KE SO LUONG DOC GIA THEO GIOI TINH\n\n"; Row += 3;

	fstream f2;
	f2.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers.txt", ios::in);
	f2 >> numberReaders;
	f2.close();
	readReadersData(noReaders, numberReaders);

	for (int i = 0; i < numberReaders; i++)
	{
		if (noReaders[i].gender == "NAM")
			countMale++;
		else if (noReaders[i].gender == "NU")
			countFemale++;
	}
	cout << "Thu vien hien co " << countMale << " doc gia nam, " << countFemale << " doc gia nu" << endl; Row++;
	cout << endl;

	if (countMale > 0)
	{
		cout << "Doc gia nam: "; Row++;
		for (int i = 0; i < numberReaders; i++)
		{
			gotoxy(14, Row);
			if (noReaders[i].gender == "NAM")
			{
				cout << " - " << noReaders[i].nameReader << endl; Row++;
			}
		}
	}

	if (countFemale > 0)
	{
		gotoxy(0, Row);
		cout << endl; Row++;
		cout << "Doc gia nu: "; Row++;
		for (int i = 0; i < numberReaders; i++)
		{
			gotoxy(14, Row);
			if (noReaders[i].gender == "NU")
			{
				cout << " - " << noReaders[i].nameReader << endl; Row++;
			}
		}
	}
	cout << endl;
	system("pause");
}

// Hàm thống kê số lượng độc giả đang mượn sách
// Tham số truyền vào là danh sách độc giả mượn sách và số lượng độc giả đang mượn sách
void statisticBorrowing(borrow ReadersBorrow[], int numBorrowReaders)
{
	int total = 0;
	int Row = 2;
	int Index = -1;
	bool flag = false;

	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(60, Row);
	cout << "THONG KE SO LUONG SACH DANG DUOC MUON SACH\n\n"; Row += 2;

	fstream f6;
	f6.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers borrowed.txt", ios::in);
	f6 >> numBorrowReaders;
	f6.close();
	readBorrowData(ReadersBorrow, numBorrowReaders);

	gotoxy(0, Row);
	for (int i = 0; i < numBorrowReaders; i++)
	{
		total += ReadersBorrow[i].numBorrow;
	}
	cout << "Tong so sach dang duoc muon: " << total << endl; Row++;
	if (total == 0)
		system("pause");
	else
	{
		cout << "Cac quyen dang duoc muon: " << endl;
		for (int i = 0; i < numBorrowReaders; i++)
		{
			for (int j = 0; j < ReadersBorrow[i].numBorrow; j++)
			{
				cout << " - " << ReadersBorrow[i].bookInfo[j].ISBN << endl;
			}
		}
		system("pause");
	}
}

//

void statisticLate(borrow ReadersBorrow[], int numBorrowReaders)
{
	int total = 0;
	int Row = 2;
	int Index = -1;

	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(57, Row);
	cout << "THONG KE SO LUONG DOC GIA DANG TRE HAN TRA SACH\n\n"; Row += 2;

	fstream f6;
	f6.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Readers borrowed.txt", ios::in);
	f6 >> numBorrowReaders;
	f6.close();
	readBorrowData(ReadersBorrow, numBorrowReaders);

	if (numBorrowReaders == 0)
	{
		cout << "Chua co doc gia muon sach!" << endl;
		system("pause");
		return;
	}

	int nowDay, nowMonth, nowYear;
	cout << "Nhap vao ngay hien tai: ";
	cin >> nowDay;
	gotoxy(27, Row); cout << "/";
	cin >> nowMonth;
	gotoxy(30, Row); cout << "/";
	cin >> nowYear;
	for (int i = 0; i < numBorrowReaders; i++)
	{
		int t = 0, distance = 0;
		int A = daysFromFirstDay(ReadersBorrow[i].expectedReturn.day, ReadersBorrow[i].expectedReturn.month, ReadersBorrow[i].expectedReturn.year);
		int B = daysFromFirstDay(nowDay, nowMonth, nowYear);
		if (ReadersBorrow[i].expectedReturn.year < nowYear)
		{
			for (int j = ReadersBorrow[i].expectedReturn.year; j < nowYear; j++)
			{
				if (j % 400 == 0 || (j % 4 == 0 && j % 100 != 0))
					t += 366;
				else
					t += 365;
			}
			distance = A - (B + t);
			ReadersBorrow[i].late = distance;
			ReadersBorrow[i].isLate = true;
			cout << " - Ma doc gia: " << ReadersBorrow[i].id << endl;
			cout << "\t\tMuon " << ReadersBorrow[i].numBorrow << " quyen" << endl;
			cout << "\t\tNgay tra du kien: " << ReadersBorrow[i].expectedReturn.day << "/" << ReadersBorrow[i].expectedReturn.month << "/" << ReadersBorrow[i].expectedReturn.year << endl;
			cout << "\t\tDang tre han tra sach " << abs(ReadersBorrow[i].late) << " ngay" << endl;
			cout << endl;
		}
		else if (ReadersBorrow[i].expectedReturn.year == nowYear)
		{
			distance = A - B;
			ReadersBorrow[i].late = distance;
			if (distance < 0)
			{
				ReadersBorrow[i].isLate = true;
				cout << " - Ma doc gia: " << ReadersBorrow[i].id << endl;
				cout << "\t\tMuon " << ReadersBorrow[i].numBorrow << " quyen" << endl;
				cout << "\t\tNgay tra du kien: " << ReadersBorrow[i].expectedReturn.day << "/" << ReadersBorrow[i].expectedReturn.month << "/" << ReadersBorrow[i].expectedReturn.year << endl;
				cout << "\t\tDang tre han tra sach " << abs(ReadersBorrow[i].late) << " ngay" << endl;
				cout << endl;
			}
			else
				ReadersBorrow[i].isLate = false;
		}
		else if (ReadersBorrow[i].expectedReturn.year > nowYear)
			ReadersBorrow[i].isLate = false;
	}
	
	int count = 0;
	for (int temp = 0; temp < numBorrowReaders; temp++)
	{
		if (ReadersBorrow[temp].isLate == true)
			count++;
	}

	if (count == 0)
		cout << "Khong co doc gia dang tre han tra sach!" << endl;

	system("pause");
}