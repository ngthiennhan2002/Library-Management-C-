#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
using namespace std;

struct Date
{
	int day;
	int month;
	int year;
};

struct reader
{
	int id;
	string nameReader;
	string cmnd;
	string gender;
	string email;
	string address;
	Date dob;
	Date created;
	Date expired;
};

struct book
{
	int ISBN;
	string bookName;
	string author;
	string publishers;
	string bookGenre;
	int publishYear;
	int bookPrice;
	int numberOfThisBook;
};

struct borrow
{
	int id;
	string nameReader;
	Date borrowDay;
	Date expectedReturn;
	Date realReturn;
	int numBorrow;
	book bookInfo[3];
	int late;
	bool isLate;
};

// Các hàm trung gian
void gotoxy(int x, int y);
void resizeConsole(int width, int height);
void writeReadersData(reader noReaders[], int numberReaders);
void readReadersData(reader noReaders[], int numberReaders);
void refreshReaders(reader noReaders[], int numberReaders);
void writeBooksData(book noBooks[], int numberBooks);
void readBooksData(book noBooks[], int numberBooks);
void refreshBooks(book noBooks[], int numberBooks);
void sevenDaysAfter(borrow ReadersBorrow[], int numBorrowReaders);
void writeBorrowData(borrow ReadersBorrow[], int numBorrowReaders);
void readBorrowData(borrow ReadersBorrow[], int numBorrowReaders);
int daysFromFirstDay(int day, int month, int year);

// Hàm về độc giả của yêu cầu 1
void addReaders(reader noReaders[], int& numberReaders);
void listOfReaders(reader noReaders[], int numberReaders);
void editReaders(reader noReaders[], int numberReaders);
void deleteReaders(reader noReaders[], int numberReaders);
void findReadersByCMND(reader noReaders[], int numberReaders);
void findReadersByName(reader noReaders[], int numberReaders);

// Hàm về sách của yêu cầu 2
void addBooks(book noBooks[], int& numberBooks);
void listOfBooks(book noBooks[], int numberBooks);
void editBooks(book noBooks[], int numberBooks);
void deleteBooks(book noBooks[], int numberBooks);
void findBooksByISBN(book noBooks[], int numberBooks);
void findBooksByName(book noBooks[], int numberBooks);

// Hàm về mượn sách của yêu cầu 3
void borrowBooks(borrow ReadersBorrow[], reader noReaders[], book noBooks[],
	int numberReaders, int numberBooks, int& numBorrowReaders);

// Hàm về trả sách của yêu cầu 4
void backBooks(borrow ReadersBorrow[], book noBooks[], int numberBooks, int& numBorrowReaders);

// Hàm về thống kê của yêu cầu 5
void statisticBooks(book noBooks[], int numberBooks);
void statisticNumbersByGenres(book noBooks[], int numberBooks);
void statisticReaders(reader noReaders[], int numberReaders);
void statisticReadersByGender(reader noReaders[], int numberReaders);
void statisticBorrowing(borrow ReadersBorrow[], int numBorrowReaders);
void statisticLate(borrow ReadersBorrow[], int numBorrowReaders);