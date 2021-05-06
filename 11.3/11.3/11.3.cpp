#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Specialnist { KN, ME, IF, FI, TN }; // перелік спеціальностей  
string specialnistList[] = { "комп науки", "мат і економ", "інформ", "фіз і інформ", "труд навч" }; // масив назв спеціальностей
struct Student
{
	char prizv[101];
	int kurs;
	Specialnist spec;
	int fiz;
	int mat;
	double average;
	union
	{
		int prog;
		int chis_metod;
		int pedagog;
	};
};

void Create(char* fname);
void Print(char* fname);
void Sort(char* fname);
void IndexSort(char* fname, char* gname);

int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	char fname[61];
	char gname[61];

	int menuItem;
	do {
		cout << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури та збереження" << endl;
		cout << " [2] - завантаження та вивід даних на екран" << endl;
		cout << " [3] - Сортування" << endl;
		cout << " [4] - Індексне сортування та його вивід" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			Create(fname);
			break;
		case 2:
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			Print(fname);
			break;
		case 3:
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Введіть назву файлу: "; cin.getline(fname, sizeof(fname));
			Sort(fname);
			cout << "Таблиця була відсортована!";
			break;
		case 4:
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Назва файлу: "; cin.getline(fname, sizeof(fname));
			cout << endl;
			cout << "Назва файлу для виведення: "; cin.getline(gname, sizeof(gname));
			cout << endl;
			IndexSort(fname, gname);
			cout << "Відсортований файл створено!" << endl << endl;
			Print(gname);
			cout << endl;
		case 0:
			break;
		default:
			cout << "Неправильне значення" << endl;
		}
	} while (menuItem != 0);
	return 0;
}

void Create(char* fname)
{
	ofstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}
	int spec;
	Student p;
	char ch;
	int i = 0;
	do{
		cout << "Cтудент № " << i + 1 << ":" << endl;
		cout << "прізвище: "; cin >> p.prizv;
		cout << "курс: "; cin >> p.kurs;
		cout << "оцінка з фізики: "; cin >> p.fiz;
		cout << "оцінка з математики: "; cin >> p.mat;
		cout << "cпеціальність (0 - комп. науки, 1 - мат і економ, 2 - інформ, 3 - фіз і інформ, 4 - труд. навч): ";  cin >> spec;
		if (spec > 4) {
			cout << "неправильне значення, вибрано 0 (комп. науки)" << endl;
			spec = 0;
		}

		p.spec = (Specialnist)spec; // присвоєння спеціальності, введенної користувачем через перелік
		switch (p.spec)
		{
		case KN:
			cout << "оцінка з програмування: "; cin >> p.prog;
			p.average = (p.mat + p.fiz + p.prog) / 3.0;
			break;
		case ME:
			cout << "оцінка з педагогіки: "; cin >> p.pedagog;
			p.average = (p.mat + p.fiz + p.pedagog) / 3.0;
			break;
		case IF:
			cout << "оцінка з чисельних методів: "; cin >> p.chis_metod;
			p.average = (p.mat + p.fiz + p.chis_metod) / 3.0;
			break;
		case FI:
			cout << "оцінка з педагогіки: "; cin >> p.pedagog;
			p.average = (p.mat + p.fiz + p.pedagog) / 3.0;
			break;
		case TN:
			cout << "оцінка з педагогіки: "; cin >> p.pedagog;
			p.average = (p.mat + p.fiz + p.pedagog) / 3.0;
			break;
		}

		if (!f.write((char*)&p, sizeof(Student)))
		{
			cerr << "Помилка запису в файл." << endl;
			f.close();
		}
		cout << "Продовжити? (Y/N) "; cin >> ch;
	} while (ch == 'Y' || ch == 'y');
	
	f.close();

}

void Print(char* fname)
{
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}
	Student student;
	cout << "============================================================================================================"
		<< endl;
	cout << "| № | Прізвище | Курс | Cпеціальність | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |"
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------------"
		<< endl;
	int i = 0;
	while (f.read((char*)&student, sizeof(Student)))
	{
		cout << "|" << setw(2) << right << i + 1 << " "; i++;
		cout << "| " << setw(9) << left << student.prizv
			<< "| " << setw(2) << right << student.kurs << "  "
			<< " | " << setw(14) << left << specialnistList[student.spec]
			<< setw(4) << "| " << setw(3) << left << student.fiz << "  "
			<< setw(6) << "| " << setw(6) << left << student.mat << " ";
		switch (student.spec)
		{
		case KN:
			cout << setw(8) << "| " << setw(7) << left << student.prog << setw(19)
				<< " | " << setw(12) << left
				<< "| " << left << " |" << endl;
			break;
		case ME:
			cout << "" << setw(15) << "| " << " "
				<< "" << setw(18) << "| "
				<< setw(6) << "| " << setw(6) << left << student.pedagog << " |" << endl;
			break;
		case IF:
			cout << "" << setw(15) << "| " << setw(9) << " |" << " "
				<< setw(8) << student.chis_metod << " |" << " "
				<< setw(10) << "" << " |" << endl;
			break;
		case FI:
			cout << "" << setw(15) << "| " << " "
				<< "" << setw(18) << "| "
				<< setw(6) << "| " << setw(6) << left << student.pedagog << " |" << endl;
			break;
		case TN:
			cout << "" << setw(15) << "| " << " "
				<< "" << setw(18) << "| "
				<< setw(6) << "| " << setw(6) << left << student.pedagog << " |" << endl;
			break;
		}
	}
	cout << "============================================================================================================"
		<< endl;
	cout << endl;
	f.close();
}

void Sort(char* fname)
{
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}
	f.seekg(0, ios::end); // курсор ставиться в кінець
	int size = f.tellg(); // визначає величину файлу
	size = size / sizeof(Student); // визначається кількість студентів
	f.seekg(0, ios::beg); 
	Student* student = new Student[size];
	Student tmp;
	f.read((char*)student, size * sizeof(Student));
	f.close();
	for (int i = 0; i < size - 1; i++) {
		for (int j = size - 1; j > i; j--) {
			string prizv1 = student[j].prizv;
			string prizv2 = student[j - 1].prizv;
			if ((student[j].average > student[j - 1].average)
				||
				(student[j].average == student[j - 1].average &&
					student[j].kurs > student[j - 1].kurs)
				||
				(student[j].average == student[j - 1].average &&
					student[j].kurs == student[j - 1].kurs &&
					prizv1 > prizv2))
			{
				tmp = student[j];
				student[j] = student[j - 1];
				student[j - 1] = tmp;
			}
		}
	}
	f.close();
	ofstream file(fname, ios::binary);
	file.write((char*)student, size * sizeof(Student));
	file.close();
}

void IndexSort(char* fname, char* gname)
{
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}
	f.seekg(0, ios::end); 
	int size = f.tellg();
	size = size / sizeof(Student);
	f.seekg(0, ios::beg);
	Student* student = new Student[size];
	Student tmp;
	f.read((char*)student, size * sizeof(Student));
	for (int i = 0; i < size - 1; i++) {
		for (int j = size - 1; j > i; j--) {
			string prizv1 = student[j].prizv;
			string prizv2 = student[j - 1].prizv;
			if ((student[j].average > student[j - 1].average)
				||
				(student[j].average == student[j - 1].average &&
					student[j].kurs > student[j - 1].kurs)
				||
				(student[j].average == student[j - 1].average &&
					student[j].kurs == student[j - 1].kurs &&
					prizv1 > prizv2))
			{
				tmp = student[j];
				student[j] = student[j - 1];
				student[j - 1] = tmp;
			}
		}
	}
	ofstream file(gname, ios::binary);
	if (!file)
	{
		cerr << "Помилка відкриття файлу '" << gname << "'" << endl;
		f.close();
		return;
	}
	file.write((char*)student, size * sizeof(Student));
	file.close();
}