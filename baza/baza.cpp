// baza.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "class.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;


void show_menu();


int main()
{
	for (;;)
	{
		show_menu();
		char menu = _getch();
		switch (menu)
		{
		case '1':
			cin.get();
			cin.get();
			break;

		case '2':
			
			break;

		case '3':
		
			break;

		case '4':

			break;

		case '7':
			exit(0);
			break;

		default:
			cout << "Nie ma takiej opcji w menu!";
			Sleep(1500);
		}
		system("CLS");
	}



	getchar();
	getchar();

	return 0;
}

void show_menu()
{
	cout << "1. Dodaj samochod do bazy." << endl;
	cout << "2." << endl;
	cout << "3." << endl;
	cout << "4." << endl;
	cout << "5." << endl;
	cout << "6." << endl;
	cout << "7. Wyjscie z programu." << endl;
}
