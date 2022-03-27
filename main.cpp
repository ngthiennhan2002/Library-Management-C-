#include <iostream>
#include <Windows.h> 
#include <string>
#include <conio.h>
#include <fstream>
#include "MyFunction.h"
using namespace std;
int main()
{
	resizeConsole(3000, 3000);
	reader noReaders[200];
	int numberReaders = 0;
	book noBooks[200];
	int numberBooks = 0;
	borrow ReadersBorrow[100];
	int numBorrowReaders = 0;
	while (1 == 1)
	{
		int choice;
		system("cls");
		gotoxy(70, 2);
		cout << "WELCOME TO MY LIBRARY";
		gotoxy(30, 5);
		cout << "- 0 : DUNG CHUONG TRINH";
		gotoxy(30, 7);
		cout << "- 1 : THEM DOC GIA";
		gotoxy(30, 9);
		cout << "- 2 : XEM DANH SACH DOC GIA";
		gotoxy(30, 11);
		cout << "- 3 : CHINH SUA THONG TIN MOT DOC GIA";
		gotoxy(30, 13);
		cout << "- 4 : XOA MOT DOC GIA";
		gotoxy(30, 15);
		cout << "- 5 : TIM KIEM DOC GIA THEO CMND  ";
		gotoxy(30, 17);
		cout << "- 6 : TIM KIEM DOC GIA THEO HO VA TEN  ";
		gotoxy(30, 19);
		cout << "- 7 : THEM SACH";
		gotoxy(30, 21);
		cout << "- 8 : XEM DANH SACH CAC SACH TRONG THU VIEN";
		gotoxy(30, 23);
		cout << "- 9 : CHINH SUA THONG TIN MOT QUYEN SACH";
		gotoxy(30, 25);
		cout << "- 10 : XOA MOT SACH";
		gotoxy(100, 5);
		cout << "- 11 : TIM KIEM SACH THEO ISBN";
		gotoxy(100, 7);
		cout << "- 12 : TIM KIEM SACH THEO TEN SACH ";
		gotoxy(100, 9);
		cout << "- 13 : LAP PHIEU MUON SACH";
		gotoxy(100, 11);
		cout << "- 14 : LAP PHIEU TRA SACH";
		gotoxy(100, 13);
		cout << "- 15 : THONG KE SO LUONG SACH TRONG THU VIEN";
		gotoxy(100, 15);
		cout << "- 16 : THONG KE SACH THEO THE LOAI";
		gotoxy(100, 17);
		cout << "- 17 : THONG KE SO LUONG DOC GIA  ";
		gotoxy(100, 19);
		cout << "- 18 : THONG KE SO LUONG DOC GIA THEO GIOI TINH  ";
		gotoxy(100, 21);
		cout << "- 19 : THONG KE SO LUONG SACH DANG DUOC MUON ";
		gotoxy(100, 23);
		cout << "- 20 : THONG KE DANH SACH DOC GIA BI TRE HAN ";
		gotoxy(30, 27);
		cout << "LUA CHON CUA BAN: ";
		cin >> choice;
		if (choice == 0)
		{
			gotoxy(30, 29);
			cout << "Ket thuc chuong trinh.\n";
			gotoxy(30, 30);
			cout << "Tam biet va hen gap lai!\n";
			break;
		}
		if (choice == 1)
		{
			addReaders(noReaders, numberReaders);
		}
		if (choice == 2)
		{
			listOfReaders(noReaders, numberReaders);
		}
		if (choice == 3)
		{
			editReaders(noReaders, numberReaders);
		}
		if (choice == 4)
		{
			deleteReaders(noReaders, numberReaders);
		}
		if (choice == 5)
		{
			findReadersByCMND(noReaders, numberReaders);
		}
		if (choice == 6)
		{
			findReadersByName(noReaders, numberReaders);
		}
		if (choice == 7)
		{
			addBooks(noBooks, numberBooks);
		}
		if (choice == 8)
		{
			listOfBooks(noBooks, numberBooks);
		}
		if (choice == 9)
		{
			editBooks(noBooks, numberBooks);
		}
		if (choice == 10)
		{
			deleteBooks(noBooks, numberBooks);
		}
		if (choice == 11)
		{
			findBooksByISBN(noBooks, numberBooks);
		}
		if (choice == 12)
		{
			findBooksByName(noBooks, numberBooks);
		}
		if (choice == 13)
  		{
			borrowBooks(ReadersBorrow, noReaders, noBooks, numberReaders, numberBooks, numBorrowReaders);
		}
		if (choice == 14)
		{
			backBooks(ReadersBorrow, noBooks, numberBooks, numBorrowReaders);
		}
		if (choice == 15)
		{
			statisticBooks(noBooks, numberBooks);
		}
		if (choice == 16)
		{
			statisticNumbersByGenres(noBooks, numberBooks);
		}
		if (choice == 17)
		{
			statisticReaders(noReaders, numberReaders);
		}
		if (choice == 18)
		{
			statisticReadersByGender(noReaders, numberReaders);
		}
		if (choice == 19)
		{
			statisticBorrowing(ReadersBorrow, numBorrowReaders);
		}
		if (choice == 20)
		{
			statisticLate(ReadersBorrow, numBorrowReaders);
		}
	}

	return 0;
}