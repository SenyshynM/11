#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>
using namespace std;

enum Specialnist { KN, ME, IF, FI, TN }; // перелік спеціальностей  
string specialnistList[] = { "комп науки", "мат і економ", "інформ", "фіз і інформ", "труд навч" }; // масив назв спеціальностей
struct Student
{
	char prizv[100];
	int kurs;
	Specialnist spec;
	int fiz;
	int mat;
	union
	{
		int prog;
		int chis_metod;
		int pedagog;
	};
};

void Create(char* fname);
void LoadFile(char* fname);
int SearchGood(char* fname);
double SearchPercent(char* fname);

int main()
{
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
	char fname[61];
	char ch;
	do
	{
		cout << endl;
		cout << "Виберіть:" << endl;
		cout << "[1] - Введення та збереження інформації" << endl;
		cout << "[2] - Завантаження та вивід інформації" << endl;
		cout << "[3] - Отримати кількість оцінок 'добре' серед студентів" << endl;
		cout << "[4] - Знайти студентів, які отримали 5 і з фізики і з математики" << endl;
		cout << "[0] - Завершити роботу." << endl << endl;
		cout << "Ваш вибір: "; cin >> ch;
		switch (ch)
		{
		case '0':
			break;
		case '1':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << endl;
			cout << "Назва файлу: "; cin.getline(fname, sizeof(fname));
			Create(fname);
			break;
		case '2':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << endl;
			cout << "Назва файлу: "; cin.getline(fname, sizeof(fname));
			cout << endl;
			LoadFile(fname);
			break;
		case '3':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << endl;
			cout << "Назва файлу: "; cin.getline(fname, sizeof(fname));
			cout << endl;
			cout << "Кількість оцінок 'добре' серед студентів: " << SearchGood(fname) << endl;
			cout << endl;
			break;
		case '4':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << endl;
			cout << "Назва файлу: "; cin.getline(fname, sizeof(fname));
			cout << endl;
			cout << "Процент студентів з '5' з фізики і математики: " << SearchPercent(fname) << endl;
			cout << endl;
			break;
		
		default:
			cout << "Помилка ";
		}
	} while (ch != '0');
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
	Student student;
	char ch;
	int i = 0;
	do
	{
		cout << "Cтудент № " << i + 1 << ":" << endl; i++;
		cout << "прізвище: "; cin >> student.prizv;
		cout << "курс: "; cin >> student.kurs;

		cout << "оцінка з фізики: "; cin >> student.fiz;
		cout << "оцінка з математики: "; cin >> student.mat;

		cout << "cпеціальність (0 - комп. науки, 1 - мат і економ, 2 - інформ, 3 - фіз і інформ, 4 - труд. навч): ";  cin >> spec;
		if (spec > 4) {
			cout << endl;
			cout << "Такої спеціальності немає. Вибрано 0 (комп. науки)";
			spec = 0;
		}
		student.spec = (Specialnist)spec; 
		switch (student.spec)
		{
		case KN:
			cout << "оцінка з програмування: "; cin >> student.prog;
			break;
		case IF:
			cout << "оцінка з чисельних методів: "; cin >> student.chis_metod;
			break;
		case ME:
		case FI:
		case TN:
			cout << "оцінка з педагогіки: "; cin >> student.pedagog;
			break;
		}
		if (!f.write((char*)&student, sizeof(Student)))
		{
			cerr << "Помилка запису в файл." << endl;
			f.close();
		}
		cout << "Продовжити? (Y/N) "; cin >> ch;
	} while (ch == 'Y' || ch == 'y');
	f.close();
}
void LoadFile(char* fname)
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

double SearchPercent(char* fname)
{
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка вікриття файлу '" << fname << "'" << endl;
		f.close();
		return 0;
	}
	Student student;
	double percent;
	int k = 0; int kilk = 0;
	while (f.read((char*)&student, sizeof(Student)))
	{
		if (student.mat == 5 && student.fiz == 5)
				k++;
		kilk++;
	}

	percent = static_cast<double>(k) / kilk * 100;
	return percent;
	f.close();
}

int SearchGood(char* fname)
{
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return 0;
	}
	Student student;
	int k = 0, n = 0;

	while (f.read((char*)&student, sizeof(Student)))
	{
		if (student.mat == 4) {
			k++;
			n++;
		}
		if (student.fiz == 4) {
			k++;
			n++;
		}
		switch (student.spec) {
		case KN:
			if (student.prog == 4) {
				k++;
				n++;
			}
			break;
		case ME:
			if (student.pedagog == 4) {
				k++;
				n++;
			}
			break;
		case IF:
			if (student.chis_metod == 4) {
				k++;
				n++;
			}
			break;
		case TN:
			if (student.pedagog == 4) {
				k++;
				n++;
			}
			break;
		case FI:
			if (student.pedagog == 4) {
				k++;
				n++;
			}
			break;
		}
		cout << "У студента " << student.prizv << " оцінок \"добре\": " << k << endl;
		k = 0;
	}
	cout << endl;
	f.close();
	return n;
}