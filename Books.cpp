#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include "MyFunction.h"
using namespace std;

// Hàm thêm sách
/*Tham số truyền vào là thông tin các sách theo kiểu book và số lượng sách hiện có trong thư viện
(dạng tham chiếu để trả về số lượng sau khi thêm sách)*/
void addBooks(book noBooks[], int& numberBooks)
{
	for (int i = 0;; i++)
	{
		int Row = 2;
		system("cls");
		gotoxy(70, Row);
		cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
		gotoxy(68, Row);
		cout << "THEM SACH THEO YEU CAU\n"; Row += 2;
		fstream f4;
		f4.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Books.txt", ios::in);
		f4 >> numberBooks;
		f4.close();
		readBooksData(noBooks, numberBooks);
		numberBooks++;
		if (numberBooks == 1)
			noBooks[0].ISBN = 100001;
		else if (numberBooks >= 2)
			noBooks[numberBooks - 1].ISBN = noBooks[numberBooks - 2].ISBN + 1;
		cout << "Sach thu " << numberBooks << endl;
		cout << "Ma ISBN (cap tu dong): " << noBooks[numberBooks - 1].ISBN << endl;
		cout << "Nhap ten sach (VIET IN HOA): "; cin.ignore(); getline(cin, noBooks[numberBooks - 1].bookName);
		cout << "Nhap tac gia: "; getline(cin, noBooks[numberBooks - 1].author);
		cout << "Nhap nha xuat ban (VIET IN HOA): "; getline(cin, noBooks[numberBooks - 1].publishers);
		cout << "Nhap the loai: "; getline(cin, noBooks[numberBooks - 1].bookGenre);
		cout << "Nhap nam xuat ban: "; cin >> noBooks[numberBooks - 1].publishYear;
		cout << "Nhap gia sach (nghin dong): "; cin >> noBooks[numberBooks - 1].bookPrice;
		cout << "Nhap so quyen hien tai: "; cin >> noBooks[numberBooks - 1].numberOfThisBook;
		f4.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Books.txt", ios::out);
		f4 << numberBooks << endl;
		f4.close();

		writeBooksData(noBooks, numberBooks);

		int next;
		cout << "\nBan co muon tiep tuc them sach? Co, nhan '1'. Khong, nhan so bat ky ngoai '1'\n";
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

// Hàm ghi thông tin sách vào file "Books.txt"
// Tham số truyền vào là thông tin các sách theo kiểu book và số lượng sách hiện có trong thư viện
void writeBooksData(book noBooks[], int numberBooks)
{
	fstream f3;
	f3.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Books.txt", ios::out | ios::app);
	if (f3.fail())
	{
		cout << "Failed to open this file to write down data!" << endl;
		return;
	}
	else
	{
		f3 << noBooks[numberBooks - 1].ISBN << endl;
		f3 << noBooks[numberBooks - 1].bookName << endl;
		f3 << noBooks[numberBooks - 1].author << endl;
		f3 << noBooks[numberBooks - 1].publishers << endl;
		f3 << noBooks[numberBooks - 1].bookGenre << endl;
		f3 << noBooks[numberBooks - 1].publishYear << endl;
		f3 << noBooks[numberBooks - 1].bookPrice << endl;
		f3 << noBooks[numberBooks - 1].numberOfThisBook << endl;
	}
	f3.close();
}

// Hàm đọc dữ liệu từ file "Books.txt"
// Tham số truyền vào là thông tin các sách theo kiểu book và số lượng sách hiện có trong thư viện
void readBooksData(book noBooks[], int numberBooks)
{
	fstream f3;
	f3.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Books.txt", ios::in);
	for (int i = 0; i < numberBooks; i++)
	{
		f3 >> noBooks[i].ISBN;
		f3.ignore();
		getline(f3, noBooks[i].bookName);
		getline(f3, noBooks[i].author);
		getline(f3, noBooks[i].publishers);
		getline(f3, noBooks[i].bookGenre);
		f3 >> noBooks[i].publishYear;
		f3 >> noBooks[i].bookPrice;
		f3 >> noBooks[i].numberOfThisBook;
	}
	f3.close();
}

// Hàm xuất danh sách sách
// Tham số truyền vào là thông tin các sách theo kiểu book và số lượng sách hiện có trong thư viện
void listOfBooks(book noBooks[], int numberBooks)
{
	int Row = 2;
	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(66, Row);
	cout << "DANH SACH SACH TRONG THU VIEN\n"; Row += 2;
	cout << endl;
	fstream f4;
	f4.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Books.txt", ios::in);
	f4 >> numberBooks;
	f4.close();

	readBooksData(noBooks, numberBooks);
	if (numberBooks == 0)
	{
		cout << "Chua co danh sach cac sach trong thu vien!" << endl;
		system("pause");
		return;
	}
	for (int i = 0; i < numberBooks; i++)
	{
		cout << "Sach thu " << i + 1 << ": ";
		cout << "\t\tMa ISBN: " << noBooks[i].ISBN << endl;;
		cout << "\t\tTen sach: " << noBooks[i].bookName << endl;
		cout << "\t\tTac gia: " << noBooks[i].author << endl;
		cout << "\t\tNha xuat ban: " << noBooks[i].publishers << endl;
		cout << "\t\tThe loai: " << noBooks[i].bookGenre << endl;
		cout << "\t\tNam xuat ban: " << noBooks[i].publishYear << endl;
		cout << "\t\tGia sach (nghin dong): " << noBooks[i].bookPrice << endl;
		cout << "\t\tSo quyen hien tai trong thu vien: " << noBooks[i].numberOfThisBook << endl;
		cout << endl;
	}
	system("pause");
}

// Hàm chỉnh sửa thông tin sách
// Tham số truyền vào là thông tin các sách theo kiểu book và số lượng sách hiện có trong thư viện
void editBooks(book noBooks[], int numberBooks)
{
	int CODE;
	int Index = -1;
	int Row = 2;
	int choice = 0;
	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(67, Row);
	cout << "CHINH SUA THONG TIN MOT SACH\n"; Row += 2;
	gotoxy(5, Row);

	fstream f4;
	f4.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Books.txt", ios::in);
	f4 >> numberBooks;
	f4.close();

	if (numberBooks == 0)
	{
		cout << "CHUA CO SACH DE CHINH SUA\n";
		system("pause");
		return;
	}

	readBooksData(noBooks, numberBooks);
	cout << "Nhap ISBN cua sach de chinh sua thong tin: "; Row++;
	cin >> CODE;
	for (int i = 0; i < numberBooks; i++)
	{
		if (CODE == noBooks[i].ISBN)
		{
			Index = i;
			break;
		}
	}
	if (Index == -1)
	{
		cout << "Khong co sach voi ISBN la " << CODE << endl;
		system("pause");
	}
	else if (Index != -1)
	{
		cout << "\t\tMa ISBN: " << noBooks[Index].ISBN << endl; Row++;
		cout << "\t\tTen sach: " << noBooks[Index].bookName << endl; Row++;
		cout << "\t\tTac gia: " << noBooks[Index].author << endl; Row++;
		cout << "\t\tNha xuat ban: " << noBooks[Index].publishers << endl; Row++;
		cout << "\t\tThe loai: " << noBooks[Index].bookGenre << endl; Row++;
		cout << "\t\tNam xuat ban: " << noBooks[Index].publishYear << endl; Row++;
		cout << "\t\tGia sach (nghin dong): " << noBooks[Index].bookPrice << endl; Row++;
		cout << "\t\tSo quyen hien tai trong thu vien: " << noBooks[Index].numberOfThisBook << endl; Row += 2;

		gotoxy(10, Row);
		cout << "0 : LUU THONG TIN VA TRO VE MAN HINH CHINH\n"; Row += 2;
		gotoxy(10, Row);
		cout << "1 : SUA TEN SACH\n"; Row += 2;
		gotoxy(10, Row);
		cout << "2 : SUA TAC GIA\n"; Row += 2;
		gotoxy(10, Row);
		cout << "3 : SUA NHA XUAT BAN\n"; Row += 2;
		gotoxy(10, Row);
		cout << "4 : SUA THE LOAI\n"; Row += 2;
		gotoxy(10, Row);
		cout << "5 : SUA NAM XUAT BAN\n"; Row += 2;
		gotoxy(10, Row);
		cout << "6 : SUA GIA SACH (NGHIN DONG)\n"; Row += 2;
		gotoxy(10, Row);
		cout << "7 : SUA SO QUYEN HIEN TAI TRONG THU VIEN\n"; Row += 2;

		while (1 < 2)
		{
			int choice;
			cout << endl; Row++;
			cout << "NHAP VAO LUA CHON CUA BAN: "; cin >> choice; Row++;
			if (choice == 0)
			{
				system("cls");
				refreshBooks(noBooks, numberBooks);
				Row = 2;
				gotoxy(70, Row);
				cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
				gotoxy(67, Row);
				cout << "Ma ISBN: " << noBooks[Index].ISBN << endl; Row++;
				cout << "Ten sach: " << noBooks[Index].bookName << endl; Row++;
				cout << "Tac gia: " << noBooks[Index].author << endl; Row++;
				cout << "Nha xuat ban: " << noBooks[Index].publishers << endl; Row++;
				cout << "The loai: " << noBooks[Index].bookGenre << endl; Row++;
				cout << "Nam xuat ban: " << noBooks[Index].publishYear << endl; Row++;
				cout << "Gia sach (nghin dong): " << noBooks[Index].bookPrice << endl; Row++;
				cout << "So quyen hien tai trong thu vien: " << noBooks[Index].numberOfThisBook << endl; Row += 2;
				break;
			}
			else if (choice == 1)
			{
				cout << "Ten sach (viet in hoa) sau chinh sua: "; Row++;
				cin.ignore();
				getline(cin, noBooks[Index].bookName);
			}
			else if (choice == 2)
			{
				cout << "Tac gia sau chinh sua: "; Row++;
				cin.ignore();
				getline(cin, noBooks[Index].author);
			}
			else if (choice == 3)
			{
				cout << "Nha xuat ban sau chinh sua: "; Row++;
				cin.ignore();
				getline(cin, noBooks[Index].publishers);
			}
			else if (choice == 4)
			{
				cout << "The loai sau chinh sua: "; Row++;
				cin.ignore();
				getline(cin, noBooks[Index].bookGenre);
			}
			else if (choice == 5)
			{
				cout << "Nam xuat ban sau chinh sua: "; Row++;
				cin >> noBooks[Index].publishYear;
			}
			else if (choice == 6)
			{
				cout << "Gia sach (nghin dong) sau chinh sua: ";
				cin >> noBooks[Index].bookPrice;
				Row++;
			}
			else if (choice == 7)
			{
				cout << "So quyen hien tai sau chinh sua: ";
				cin >> noBooks[Index].numberOfThisBook;
				Row++;
			}
		}
		system("pause");
	}
}

// Hàm ghi thông tin sách sau chỉnh sửa, xóa
// Tham số truyền vào là thông tin các sách theo kiểu book và số lượng sách hiện có trong thư viện
void refreshBooks(book noBooks[], int numberBooks)
{
	fstream f3;
	f3.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Books.txt", ios::out);
	for (int i = 0; i < numberBooks; i++)
	{
		if (f3.fail())
		{
			cout << "Failed to open this file to write down data!" << endl;
			return;
		}
		else
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
}

// Hàm xóa một sách
// Tham số truyền vào là thông tin các sách theo kiểu book và số lượng sách hiện có trong thư viện
void deleteBooks(book noBooks[], int numberBooks)
{
	int CODE;
	int Index = -1;
	int Row = 2;
	int choice;
	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(72, Row);
	cout << "XOA SACH THEO ISBN\n"; Row += 2;
	gotoxy(5, Row);

	fstream f4;
	f4.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Books.txt", ios::in);
	f4 >> numberBooks;
	f4.close();

	if (numberBooks == 0)
	{
		cout << "CHUA CO SACH DE XOA\n";
		system("pause");
		return;
	}

	readBooksData(noBooks, numberBooks);
	cout << "Nhap ISBN cua sach de xoa sach: "; Row++;
	cin >> CODE;
	for (int i = 0; i < numberBooks; i++)
	{
		if (CODE == noBooks[i].ISBN)
		{
			Index = i;
			break;
		}
	}
	if (Index == -1)
	{
		cout << "Khong co sach voi ISBN la " << CODE << endl;
		system("pause");
	}
	else if (Index != -1)
	{
		cout << "Ma ISBN: " << noBooks[Index].ISBN << endl; Row++;
		cout << "Ten sach: " << noBooks[Index].bookName << endl; Row++;
		cout << "Tac gia: " << noBooks[Index].author << endl; Row++;
		cout << "Nha xuat ban: " << noBooks[Index].publishers << endl; Row++;
		cout << "The loai: " << noBooks[Index].bookGenre << endl; Row++;
		cout << "Nam xuat ban: " << noBooks[Index].publishYear << endl; Row++;
		cout << "Gia sach (nghin dong): " << noBooks[Index].bookPrice << endl; Row++;
		cout << "So quyen hien tai trong thu vien: " << noBooks[Index].numberOfThisBook << endl; Row += 2;
		cout << "Ban co xac nhan xoa sach? Luu y: Khong the hoan tac sau khi xac nhan\n"; Row++;
		int DeleteOrNot;
		cout << "Neu co, nhap '1'. Neu khong, nhap '0' de TRO VE\n";
		cout << "Lua chon cua ban: "; cin >> DeleteOrNot;
		if (DeleteOrNot == 0)
			return;
		else if (DeleteOrNot == 1)
		{
			cout << "DA XOA SACH '" << noBooks[Index].bookName << "' CO SO ISBN LA " << noBooks[Index].ISBN << endl; Row++;
			numberBooks--;
			fstream f4;
			f4.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Books.txt", ios::out);
			f4 << numberBooks;
			f4.close();

			int temp = Index;
			for (temp; temp < numberBooks; temp++)
			{
				noBooks[temp].ISBN = noBooks[temp + 1].ISBN;
				noBooks[temp].bookName = noBooks[temp + 1].bookName;
				noBooks[temp].author = noBooks[temp + 1].author;
				noBooks[temp].publishers = noBooks[temp + 1].publishers;
				noBooks[temp].bookGenre = noBooks[temp + 1].bookGenre;
				noBooks[temp].publishYear = noBooks[temp + 1].publishYear;
				noBooks[temp].bookPrice = noBooks[temp + 1].bookPrice;
				noBooks[temp].numberOfThisBook = noBooks[temp + 1].numberOfThisBook;
			}
			refreshBooks(noBooks, numberBooks);
			system("pause");
		}
	}
}

// Hàm tìm kiếm thông tin một sách theo ISBN
// Tham số truyền vào là thông tin các sách theo kiểu book và số lượng sách hiện có trong thư viện
void findBooksByISBN(book noBooks[], int numberBooks)
{
	int Row = 2;
	int Index = -1;
	int CODE;
	system("cls");
	gotoxy(70, Row);
	cout << "WELCOME TO MY LIBRARY\n"; Row += 2;
	gotoxy(69, Row);
	cout << "TIM KIEM SACH THEO ISBN\n"; Row += 2;

	fstream f4;
	f4.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Books.txt", ios::in);
	f4 >> numberBooks;
	f4.close();
	readBooksData(noBooks, numberBooks);

	if (numberBooks == 0)
	{
		cout << "CHUA CO SACH DE TIM KIEM\n";
		system("pause");
	}
	else
	{
		cout << "Nhap ISBN cua ban de tim kiem sach: "; Row++;
		cin >> CODE;
		for (int i = 0; i < numberBooks; i++)
		{
			if (CODE == noBooks[i].ISBN)
			{
				Index = i;
				break;
			}
		}

		if (Index == -1)
		{
			cout << "Khong co sach co so ISBN la " << CODE << endl;
			system("pause");
		}
		else if (Index != -1)
		{
			cout << endl;
			cout << "Ma ISBN: " << noBooks[Index].ISBN << endl; Row++;
			cout << "Ten sach: " << noBooks[Index].bookName << endl; Row++;
			cout << "Tac gia: " << noBooks[Index].author << endl; Row++;
			cout << "Nha xuat ban: " << noBooks[Index].publishers << endl; Row++;
			cout << "The loai: " << noBooks[Index].bookGenre << endl; Row++;
			cout << "Nam xuat ban: " << noBooks[Index].publishYear << endl; Row++;
			cout << "Gia sach (nghin dong): " << noBooks[Index].bookPrice << endl; Row++;
			cout << "So quyen hien tai trong thu vien: " << noBooks[Index].numberOfThisBook << endl; Row += 2;
			system("pause");
		}
	}
}

// Hàm tìm kiếm sách theo họ tên
// Tham số truyền vào là thông tin các sách theo kiểu book và số lượng sách hiện có trong thư viện
void findBooksByName(book noBooks[], int numberBooks)
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
	cout << "TIM KIEM SACH THEO TEN SACH\n"; Row += 2;

	fstream f4;
	f4.open("C:\\Users\\ngthi\\source\\repos\\Do_an_2\\Project\\Number of Books.txt", ios::in);
	f4 >> numberBooks;
	f4.close();
	readBooksData(noBooks, numberBooks);

	if (numberBooks == 0)
	{
		cout << "CHUA CO SACH DE TIM KIEM\n";
		system("pause");
	}
	else
	{
		cout << "\nNhap ten sach de tim kiem thong tin (viet in hoa): "; Row += 2;
		cin.ignore();
		getline(cin, NAME);
		for (int i = 0; i < numberBooks; i++)
		{
			if (NAME == noBooks[i].bookName)
			{
				count++;
			}
		}

		if (count == 0)
		{
			cout << "Khong tim thay sach " << NAME << endl;
			system("pause");
		}

		else if (count > 0)
		{
			cout << endl;
			cout << "Da tim thay " << count << " sach co ten la " << NAME << endl;
			for (int i = 0; i < numberBooks; i++)
			{
				if (NAME == noBooks[i].bookName)
				{
					temp++;
					Index = i;
					cout << "SACH THU " << temp << ": " << endl;
					cout << endl;
					cout << "Ma ISBN: " << noBooks[Index].ISBN << endl; Row++;
					cout << "Ten sach: " << noBooks[Index].bookName << endl; Row++;
					cout << "Tac gia: " << noBooks[Index].author << endl; Row++;
					cout << "Nha xuat ban: " << noBooks[Index].publishers << endl; Row++;
					cout << "The loai: " << noBooks[Index].bookGenre << endl; Row++;
					cout << "Nam xuat ban: " << noBooks[Index].publishYear << endl; Row++;
					cout << "Gia sach (nghin dong): " << noBooks[Index].bookPrice << endl; Row++;
					cout << "So quyen hien tai trong thu vien: " << noBooks[Index].numberOfThisBook << endl; Row += 2;
					cout << endl << endl;
				}
			}
			system("pause");
		}
	}
}