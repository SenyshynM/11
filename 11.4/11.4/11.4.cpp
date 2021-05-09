#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>

using namespace std;

struct route
{
	char start[101];
	char end[101];
	int nomer;
};

void Sort(char* fname);
void Search(char* fname);
void create(char* fname);
void print(char* fname);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char fname[101];
	int choice;

	do {
		cout << "--------------------------\n";
		cout << "Меню\n";
		cout << "[1] - Сортування\n";
		cout << "[2] - Пошук\n";
		cout << "[3] - Введення і збереження\n";
		cout << "[4] - Загрузка і вивід\n";
		cout << "[0] - Вихід\n";
		cout << "--------------------------\n";
		cout << "Виберіть: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Сортування:\n";
			cin.get();
			cin.sync();
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			Sort(fname);
			break;

		case 2:
		{
			cout << "Пошук:\n";
			cin.get();
			cin.sync();
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			Search(fname);
			break;
		}

		case 3:
			cout << "Введення і збереження:\n";
			cin.get();
			cin.sync();
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			create(fname);
			break;
		
		case 4:
			cout << "Виведення інформації:\n";
			cin.get();
			cin.sync();
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			print(fname);
			break;


		case 0:
			break;

		default:
			cout << "--------------------------\n";
			cout << "Меню\n";
			cout << "[1] - Сортування\n";
			cout << "[2] - Пошук\n";
			cout << "[3] - Загрузка і вивід\n";
			cout << "[4] - Введення і збереження\n";
			cout << "[0] - Вихід\n";
			cout << "--------------------------\n";
			cout << "Виберіть:";
			cin >> choice;
		}
	} while (choice != 0);
}

void Sort(char* fname) {
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}

	f.seekg(0, ios::end);
	int size = f.tellg() / sizeof(route);
	f.seekg(0, ios::beg);
	route* r = new route[size];
	route tmp;
	f.read((char*)r, size * sizeof(route));

	for (int i0 = 0; i0 < size - 1; i0++) {
		for (int i1 = 0; i1 < size - i0 - 1; i1++) {
			if (r[i1].nomer > r[i1 + 1].nomer)
			{
				tmp = r[i1];
				r[i1] = r[i1 + 1];
				r[i1 + 1] = tmp;
			}
		}
	}

	f.close();
	ofstream file(fname, ios::binary);
	file.write((char*)r, size * sizeof(route));
	file.close();
}

void Search(char* fname) {

	int nomer; 
	bool n = false;
	cout << "Введіть номер маршруту для пошуку: ";
	cin.sync(); cin >> nomer;

	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}

	route r;

	while (f.read((char*)&r, sizeof(route)))
	{
		if (r.nomer == nomer)
		{
			n = true;
			break;
		}
	}

	if (n == true) 
	{
		cout << " Маршрут з номером " << nomer << " знайдено: " << endl;
		cout << " Початок: " << r.start << endl;
		cout << " Кінець: " << r.end << endl;
	}
	else
	{
		cout << " Маршруту з таким номером не знайдено." << endl;
	}
}

void create(char* fname)
{
	ofstream fout(fname, ios::binary);
	char ch; route r;

	do
	{
		cout << "Номер маршруту: "; cin >> r.nomer;
		cout << "Початок: "; cin >> r.start;
		cout << "Кінець: "; cin >> r.end;

		if (!fout.write((char*)&r, sizeof(route)))
		{
			cerr << "Помилка запису." << endl;
		}
		cout << "Продовжити? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');

	cout << endl;
	fout.close();
}

void print(char* fname)
{
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}
	
	route r;

	cout << "====================================="
		<< endl;
	cout << "| Початок | Кінець | Номер " << setw(3) << "|"
		<< endl;
	cout << "-------------------------------------"
		<< endl;

	while (f.read((char*)&r, sizeof(route)))
	{
		cout << "| " << setw(7) << left << r.start << " "
			<< "| " << setw(6) << right << r.end << " "
			<< "| " << setw(7) << left << r.nomer << " |" << endl;
	}
	cout << "-------------------------------------" << endl << endl;

	f.close();
}