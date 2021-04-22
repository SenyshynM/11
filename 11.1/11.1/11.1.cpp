#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

void CreateBIN(char* fname)
{
    ofstream f(fname, ios::binary);
    if (f.fail())
    {
        cerr << "Помилка при відкритті файлу " << endl;
        exit(1);
    }

    char ch;
    int x;
    do
    {
        cout << "enter number: "; cin >> x;
        f.write((char*)&x, sizeof(x));
        cout << "continue? (y/n): "; cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << endl;

}

void PrintBIN(char* filename)
{
    ifstream f(filename, ios::binary);

    if (f.fail())
    {
        cerr << "Помилка при відкритті файлу " << endl;
        exit(1);
    }

    int x;

    while (f.read((char*)&x, sizeof(x)))
        cout << x << endl;

    
    cout << endl;
}



void ProcessBIN(char* fname, char* outnameodd, char* outnameeven)
{
    ifstream f(fname, ios::binary);
    ofstream godd(outnameodd, ios::binary);
    ofstream geven(outnameeven, ios::binary);

    int x;

    while (f.read((char*)&x, sizeof(x)))
    {
        if (x % 2 == 0)
            geven.write((char*)&x, sizeof(x));
        else
            godd.write((char*)&x, sizeof(x));
    }
}

int main()
{
    char fname[100];
    cout << "enter input file name: "; cin >> fname;

    CreateBIN(fname);
    PrintBIN(fname);

    char outnameodd[100]; char outnameeven[100];
    cout << "enter output file name (for odd numbers): "; cin >> outnameodd;
    cout << "enter output file name (for even numbers): "; cin >> outnameeven;

    ProcessBIN(fname, outnameodd, outnameeven);

    cout << "Even numbers: " << endl;
    PrintBIN(outnameeven);

    cout << "Odd numbers: " << endl;
    PrintBIN(outnameodd);

    return 0;
}
