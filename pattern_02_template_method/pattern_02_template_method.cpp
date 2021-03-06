/*
Завдання 2. Скласти програму, яка буде
o	записувати контейнер цілих чисел у файл(текстовий чи бінарний)
o	читати  цілі числа з файлу(текстового чи бінарного) у контейнер
Запис контейнеру у файл(template method) повинен містити послідовність наступних операцій
o	Відкриття файлу
o	Запис чисел
o	Закриття файлу
Метод зчитування(template method) з файлу повинен містити послідовність наступних операцій
o	Відкриття файлу
o	Зчитування чисел та додавання їх у контейнер
o	Закриття файлу
Використати патерн Шаблонний Метод.

*/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Application
{
public:
	vector<int> numbers{ 1, 2, 3, 5, 7 };
protected:


	// кроки алгоритму перевизначатимуться в похідних класах
	virtual void openFile() = 0;
	virtual void workFile() = 0;
	virtual void closeFile() = 0;


public:
	// сам алгоритм незмінний
	void templateMethod()
	{
		openFile();
		workFile();
		closeFile();
	}
};

class WriteAppl : public Application
{
public:
	ofstream file;
protected:
	void openFile()
	{
		file.open("numbers.bin", ios::binary);
		cout << "\twrite:\tfile open\n";
	}

	void workFile()
	{
		for(auto elem : numbers)
			file.write((char*)&elem, sizeof(elem));
		cout << "\twrite:\tfile write\n";
	}
	
	void closeFile()
	{
		file.close();
		cout << "\twrite:\tfile close\n\n";
	}
};

class ReadAppl : public Application
{
public:
	ifstream file;
protected:

	void openFile()
	{
		file.open("numbers.bin", ios::binary);
		cout << "\n\tread:\tfile open\n";
	}

	void workFile()
	{
		int num;
		while (file.read((char*)&num, sizeof(num)))
		{
			cout << num << "\t";
		}
		cout << "\n\tread:\tfile read\n";
	}

	void closeFile()
	{
		file.close();
		cout << "\tread:\tfile close\n";
	}
};

int main()
{
	WriteAppl write;
	write.templateMethod();
	ReadAppl read;
	read.templateMethod();

	cout << endl;
	system("pause");
	return 0;
}