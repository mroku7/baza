// baza.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "class.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>

using namespace std;


void show_menu();
void get_data(string&, string&, char&, char&, char&, int&, int&, int&);

string replacing_space(string&);
void loading_from_file();


int main()
{
	
	string make;
	string model;
	char body_type = 0;
	char fuel = 0;
	char transmission = 0;
	int engine_size = 0;
	int year = 0;
	int value = 0;
	vector <Data> vec;
	int counter = 0;

	
	for (;;)
	{
		show_menu();
		char menu = _getch();
		switch (menu)
		{
		case '1':
		{
			get_data(make, model, body_type, fuel, transmission, engine_size, year, value);
			vec.push_back(Data(make, model, body_type, fuel, transmission, engine_size, year, value));
			vec[counter].save_to_file();
			counter++;
			
	//		fstream save("data.xdd", ios::in | ios::app);
		//	save << convert_for_save(make, model, body_type, fuel, transmission, engine_size, year, value);
			//save << endl;
			//save.close();
			break;
		}
		case '2':


		
			
			
		
			cin.get();
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

void get_data(string &make, string &model, char &body_type, char &fuel, char &transmission, int &engine_size, int &year, int &value)
{
	cout << "Podaj marke auta: " << endl;
	getline(cin, make);
	cout << "Podaj model auta: " << endl;
	getline(cin, model);
	cout << "Wybierz rodzaj nadwozia." << endl;
	cout << "1.Hatchback  2.Sedan  3.Kombi 4.Kabriolet  5.Coupe  6.SUV  7.Terenowy"<<endl;
	body_type= _getch();
	cout << "Wybierz rodzaj paliwa." << endl;
	cout << "1.Benzyna  2.Diesel  3.LPG  4.Elektryczny  5.Hybryda" << endl;
	fuel= _getch();
	cout << "Wybierz Typ skrzyni biegow." << endl;
	cout << "1.Manualna  2.Automatyczna" << endl;
	transmission = _getch();
	cout << "Podaj pojemnosc silnika w cm^3: " << endl;
	cin >> engine_size;
	cin.ignore();
	cout << "Podaj rok produkcji auta: " << endl;
	cin >> year;
	cin.ignore();
	cout << "Podaj wartosc auta w zl: " << endl;
	cin >> value;
	cin.ignore();
}


void loading_from_file()
{



}


