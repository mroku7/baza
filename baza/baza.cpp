// baza.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "class.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <algorithm>

using namespace std;


void show_menu();
void get_data(string&, string&, char&, char&, char&, int&, int&, int&);
void loading_from_file(int&, vector <Data>&,string);
string delete_underscore(string&);



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
	string name_of_data = "data.xdd";
	loading_from_file(counter, vec, name_of_data);
	
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
			vec[counter].save_to_file(name_of_data);
			counter++;
			break;
		}
		case '2':
		{
			system("CLS");
			if (counter == 0)
			{
				cout << "Brak elementow w bazie.";
				Sleep(1500);
				break;
			}
			int c = 0;
			bool b = 0;
			vec[c].browsing();
			for (;;)
			{
				for (;;)
				{
					if (GetAsyncKeyState(VK_ESCAPE) & 1)
					{
						b = 1;
						break;
					}
					if (GetAsyncKeyState(VK_UP) & 1)
					{
						c -= 1;
						if (c < 0)
						{
							c = 0;
							break;
						}
						system("CLS");
						vec[c].browsing();

					}
					if (GetAsyncKeyState(VK_DOWN) & 1)
					{
						c += 1;
						if (c >= counter)
						{
							c = counter - 1;
							break;
						}
						system("CLS");
						vec[c].browsing();
					}
					if (GetAsyncKeyState(VK_DELETE) & 1)
					{
						cout << "\n\n\nCZY NA PEWNO CHCESZ USUNAC WYBRANY ELEMENT?" << endl;
						cout << "1.TAK\n2.NIE" << endl;
						int menu;
						while (!(cin >> menu) || menu > 2 || menu==0)
						{
							cin.clear();
							cin.ignore();
						}
						cin.sync();
						if (menu==1)
						{
							vec.erase(vec.begin() + c);
							counter -= 1;
							if (counter == 0)
							{
								system("CLS");
								cout << "Brak elementow w bazie.";
								Sleep(1500);
								b = 1;
								break;
							}
							if(c>0) c -= 1;
							system("CLS");
							vec[c].browsing();
						}
						else
						{	
							system("CLS");
							vec[c].browsing();
						}
						
					}

					if (GetAsyncKeyState(112) & 1)
					{
						cin.sync();
						cout << "\n\n\nChcesz nadpisac aktualnie wczytana baze danych?" << endl;
						cout << "1.TAK\n2.NIE" << endl;
						while (_kbhit())
							_getch();
						int menu;
						while (!(cin >> menu) || menu > 2 || menu == 0)
						{
							cin.clear();
							cin.ignore();
						}
						if (menu == 1)
						{
							fstream del(name_of_data, ios::out | ios::trunc);
							del.close();
							for (int i = 0; i < vec.size(); i++)
								vec[i].save_to_file(name_of_data);
							b = 1;
							break;
						}
						else
						{
							string new_name;
							while (cin.get() != '\n') continue;
							cin.sync();
							system("CLS");
							cout << "Podaj nazwe nowej bazy: ";
							getline(cin, new_name);
							new_name.append(".xdd");
							for (int i = 0; i < vec.size(); i++)
								vec[i].save_to_file(new_name);
							b = 1;
							break;
						}
					}
				}
			if (b == 1)
			{
				b = 0;
				while (_kbhit())
					_getch();
				break;
			}
				
				
			}
			break;
		}
		case '3':
		{	
			system("CLS");
			cout << "Prosze wybrac wartosc wg. ktorej sortowac." << endl;
			cout << "1. Watrosc"<<endl;
			cout << "2. Rok produkcji"<<endl;
			cout << "3. Pojemnosc silnika" << endl;
			auto *comparator = &compare_by_value;
			int menu = _getch();
			if (menu == '1')
			{
				comparator = &compare_by_value;
				sort(vec.begin(), vec.end(), comparator);
				cout << "\n\nSortowanie zakonczone.";
				Sleep(1000);
			}
			else if (menu == '2')
			{
				comparator = &compare_by_year;
				sort(vec.begin(), vec.end(), comparator);
				cout << "\n\nSortowanie zakonczone.";
				Sleep(1000);
			}
			else if (menu=='3')
			{
				comparator = &compare_by_eng;
				sort(vec.begin(), vec.end(), comparator);
				cout << "\n\nSortowanie zakonczone.";
				Sleep(1000);
			}
			else if(menu=='4')
			{
				comparator = &compare_by_make;
				sort(vec.begin(), vec.end(), comparator);
				cout << "\n\nSortowanie zakonczone.";
				Sleep(1000);
			}
			else
				break;
			

			break;
		}
		case '4':
		{	
			system("CLS");
			cout << "Podaj nazwe pliku wraz z rozszerzeniem: "<<endl;
			string name;
			getline(cin, name);
			cout << "Wybierz:" << endl;
			cout << "1. Nadpisz aktualnie istniejaca baze." << endl;
			cout << "2. Dopisz do aktualnie istniejacej bazy." << endl;
			cout << "3. Anuluj." << endl;
			int menu;
			while (!(cin >> menu) || menu > 3 || menu == 0)
			{
				cin.clear();
				cin.ignore();
			}
			if (menu == 1)
			{
				vec.clear();
				counter = 0;
				loading_from_file(counter, vec, name);
			}
			else if (menu == 2)
			{
				loading_from_file(counter, vec, name);
			}
			
			break;

			
		}

			

		case '7':
			exit(0);
			break;

		default:
			cout << "Nie ma takiej opcji w menu!";
			Sleep(1500);
		}
		system("CLS");
	}
	return 0;
}

void show_menu()
{
	cout << "1. Dodaj samochod do bazy." << endl;
	cout << "2. Przeglad bazy danych." << endl;
	cout << "3. Sortowanie" << endl;
	cout << "4. Wczytanie bazy z pliku" << endl;
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



void loading_from_file(int &cou, vector <Data> &vec, string name)
{
	fstream load(name, ios::in);
	if (load.good() == true)
	{
		string line;
		string mk;
		string md;
		char bt;
		char fuel;
		char tran;
		int eng;
		int year;
		int val;
		while (!load.eof())
		{
			getline(load, line);
			cou++;	
		}
		cou -= 1;
		fstream load(name, ios::in);
		for (int i = 0; i < cou; i++)
		{
			load >> mk;
			delete_underscore(mk);
			load >> md;
			delete_underscore(md);
			load >> bt;
			load >> fuel;
			load >> tran;
			load >> eng;
			load >> year;
			load >> val;
			vec.push_back(Data(mk, md, bt, fuel, tran, eng, year, val));
		}

	}
	else
	{
		cout << "Nie uda³o sie zaloadowac bazy danych." << endl;
		cout << "Czy chcesz kontynu³owac z pusta baza danych?" << endl;
		cout << "1.TAK\n2.NIE" << endl;
		int menu;
		while (!(cin >> menu) || menu > 2 || menu == 0)
		{
			cin.clear();
			cin.ignore();
		}
		while (cin.get() != '\n')
		{
			continue;
		}
		if(menu==2)
			exit(0);
	}


	system("CLS");


}

string delete_underscore(string &text)
{
	for (unsigned int i = 0; i <= text.size(); i++)
		if (text[i] == '_')
			text.replace(i, 1, " ");
	return text;
}

