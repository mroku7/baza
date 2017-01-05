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
void get_data(string&, string&, int&, int&, int&, int&, int&, int&);
void loading_from_file(int&, vector <Data>&,string);
string delete_underscore(string&);
void searching(vector <Data>&, vector<Data>, string, string, int, int, int, int, int, int, int, int, int, int);



int main()
{

	string make;
	string model;
	int body_type = 0;
	int fuel = 0;
	int transmission = 0;
	int engine_size = 0;
	int year = 0;
	int value = 0;
	vector <Data> vec;
	vector <Data> vec_s;
	int counter = 0;
	string name_of_data = "data.xdd";
	loading_from_file(counter, vec, name_of_data);

	for (;;)
	{
		system("CLS");
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
						while (!(cin >> menu) || menu > 2 || menu == 0)
						{
							cin.clear();
							cin.ignore();
							cout << "Podaj prawidlowa wartosc" << endl;
						}
						cin.sync();
						if (menu == 1)
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
							if (c > 0) c -= 1;
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
							cout << "Podaj prawidlowa wartosc" << endl;
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
			cout << "1. Watrosc" << endl;
			cout << "2. Rok produkcji" << endl;
			cout << "3. Pojemnosc silnika" << endl;
			cout << "4. Marka" << endl;
			cout << "5. Model" << endl;
			auto *comparator = &compare_by_value;
			int menu;
			while (!(cin >> menu) || menu > 5 || menu == 0)
			{
				cin.clear();
				cin.ignore();
				cout << "Podaj prawidlowa wartosc" << endl;
			}

			if (menu == 1)
			{
				comparator = &compare_by_value;
				sort(vec.begin(), vec.end(), comparator);
				cout << "\n\nSortowanie zakonczone.";
				Sleep(1000);
				break;
			}
			else if (menu == 2)
			{
				comparator = &compare_by_year;
				sort(vec.begin(), vec.end(), comparator);
				cout << "\n\nSortowanie zakonczone.";
				Sleep(1000);
				break;
			}
			else if (menu == 3)
			{
				comparator = &compare_by_eng;
				sort(vec.begin(), vec.end(), comparator);
				cout << "\n\nSortowanie zakonczone.";
				Sleep(1000);
				break;
			}
			else if (menu == 4)
			{
				comparator = &compare_by_make;
				sort(vec.begin(), vec.end(), comparator);
				cout << "\n\nSortowanie zakonczone.";
				Sleep(1000);
				break;
			}
			else if (menu == 5)
			{
				comparator = &compare_by_model;
				sort(vec.begin(), vec.end(), comparator);
				cout << "\n\nSortowanie zakonczone.";
				Sleep(1000);
				break;
			}
			if (cin) cin.ignore(cin.rdbuf()->in_avail());
			break;
		}
		case '4':
		{
			system("CLS");
			cout << "Podaj nazwe pliku wraz z rozszerzeniem: " << endl;
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
				cout << "Podaj prawidlowa wartosc" << endl;
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
		case '5':
		{
			
				string s_make = " ";
				string s_model = " ";
				int s_body_type = 0;
				int s_fuel = 0;
				int s_transmission = 0;
				int s_engine_size_min = 0;
				int s_engine_size_max = 0;
				int s_year_min = 0;
				int s_year_max = 0;
				int s_value_min = 0;
				int s_value_max = 0;
				bool set = false;
				for (;;)
				{
					system("CLS");
					cout << "Wybierz typ dla ktorego zastosowac filtr:" << endl;
					cout << "1. Marka." << endl;
					cout << "2. Model." << endl;
					cout << "3. Typ nadwozia." << endl;
					cout << "4. Rodzaj paliwa." << endl;
					cout << "5. Rodzaj skrzyni biegow." << endl;
					cout << "6. Pojemnosc silnika." << endl;
					cout << "7. Rok produkcji." << endl;
					cout << "8. Wartosc." << endl << endl;
					cout << "9. Wyswietl." << endl << endl << endl << endl;
					cout << "0. Wyjscie." << endl;


					int menu;
					while (!(cin >> menu) || menu > 9)
					{
						cin.clear();
						cin.ignore();
						cout << "Podaj prawidlowa wartosc" << endl;
					}
					if (menu == 9)
					{
						if (set)
						{
							searching(vec_s, vec,s_make, s_model, s_body_type, s_fuel, s_transmission, s_engine_size_min, s_engine_size_max, s_year_min, s_year_max, s_value_min, s_value_max, counter);
						}
						else
						{
							cout << "Nie ustawiono zadnych filtrow!";
							Sleep(2000);
							continue;
						}


					}
					else if (menu == 1)
					{
						cout << "\n\n\nWpisz poszukiwana marke: ";
						getline(cin, s_make);
						getline(cin, s_make);
						cout << "\nUstawiono filtr \"" << s_make << "\" dla marki.";
						transform(s_make.begin(), s_make.end(), s_make.begin(), ::toupper);
						set = true;
						Sleep(2000);
					}
					else if (menu == 2)
					{
						cout << "\n\n\nWpisz poszukiwany model: ";
						getline(cin, s_model);
						getline(cin, s_model);
						cout << "\nUstawiono filtr \"" << s_model << "\" dla modelu.";
						transform(s_model.begin(), s_model.end(), s_model.begin(), ::toupper);
						set = true;
						Sleep(2000);
					}
					else if (menu == 3)
					{
						cout << "\n\n\nWybierz typ nadwozia: " << endl;
						cout << "1.Hatchback  2.Sedan  3.Kombi 4.Kabriolet  5.Coupe  6.SUV  7.Terenowy" << endl;
						while (!(cin >> s_body_type) || s_body_type > 7 || s_body_type == 0)
						{
							cin.clear();
							cin.ignore();
							cout << "Podaj prawidlowa wartosc" << endl;
						}
						cout << "\nUstawiono filtr \"";
						if (s_body_type == 1)
							cout << "Hatchback";
						else if (s_body_type == 2)
							cout << "Sedan";
						else if (s_body_type == 3)
							cout << "Kombi";
						else if (s_body_type == 4)
							cout << "Kabriolet";
						else if (s_body_type == 5)
							cout << "Coupe";
						else if (s_body_type == 6)
							cout << "SUV";
						else if (s_body_type == 7)
							cout << "Terenowy";
						cout << "\" dla typu nadwozia.";
						set = true;

						Sleep(2000);
					}
					else if (menu == 4)
					{
						cout << "\n\n\nWybierz rodzaj paliwa: " << endl;
						cout << "1.Benzyna  2.Diesel  3.LPG  4.Elektryczny  5.Hybryda" << endl;
						while (!(cin >> s_fuel) || s_fuel > 5 || s_fuel == 0)
						{
							cin.clear();
							cin.ignore();
							cout << "Podaj prawidlowa wartosc" << endl;
						}
						cout << "\nUstawiono filtr \"";
						if (s_fuel == 1)
							cout << "Benzyna";
						else if (s_fuel == 2)
							cout << "Diesel";
						else if (s_fuel == 3)
							cout << "LPG";
						else if (s_fuel == 4)
							cout << "Elektryczny";
						else if (s_fuel == 5)
							cout << "Hybryda";
						cout << "\" dla rodzaju paliwa.";
						set = true;
						Sleep(2000);
					}
					else if (menu == 5)
					{
						cout << "\n\n\nWybierz typ skrzyni biegow: " << endl;
						cout << "1.Manualna  2.Automatyczna" << endl;
						while (!(cin >> s_transmission) || s_transmission > 2 || s_transmission == 0)
						{
							cin.clear();
							cin.ignore();
							cout << "Podaj prawidlowa wartosc" << endl;
						}
						cout << "\nUstawiono filtr \"";
						if (s_transmission == 1)
							cout << "Manualna";
						else if (s_transmission == 2)
							cout << "Automatyczna";
						cout << "\" dla typu skrzyni biegow.";
						set = true;
						Sleep(2000);
					}
					else if (menu == 6)
					{
						cout << "\n\n\nWpisz przedzial pojemnosci silnika (cm^3): " << endl;
						cout << "Minimalna: ";
						while (!(cin >> s_engine_size_min) || s_engine_size_min < 0)
						{
							cin.clear();
							cin.ignore();
							cout << "Podaj prawidlowa wartosc" << endl;
						}
						cout << "Maksmyalna: ";
						while (!(cin >> s_engine_size_max) || s_engine_size_min > s_engine_size_max)
						{
							cin.clear();
							cin.ignore();
							cout << "Podaj prawidlowa wartosc" << endl;
						}
						cout << "\nUstawiono przedzial pojemnosci silnika od " << s_engine_size_min << " do " << s_engine_size_max << " cm^3.";
						set = true;
						Sleep(2000);

					}
					else if (menu == 7)
					{
						cout << "\n\n\nWpisz zakres roku produkcji: " << endl;
						cout << "Od: ";
						while (!(cin >> s_year_min) || s_year_min <= 0)
						{
							cin.clear();
							cin.ignore();
							cout << "Podaj prawidlowa wartosc" << endl;
						}
						cout << "Do: ";
						while (!(cin >> s_year_max) || s_year_min > s_year_max)
						{
							cin.clear();
							cin.ignore();
							cout << "Podaj prawidlowa wartosc" << endl;
						}
						cout << "\nUstawiono zakres roku produkcji od " << s_year_min << " do " << s_year_max << " r.";
						set = true;
						Sleep(2000);

					}
					else if (menu == 8)
					{
						cout << "\n\n\nWpisz zakres wartosci pojazdu: " << endl;
						cout << "Od: ";
						while (!(cin >> s_value_min) || s_value_min <= 0)
						{
							cin.clear();
							cin.ignore();
							cout << "Podaj prawidlowa wartosc" << endl;
						}
						cout << "Do: ";
						while (!(cin >> s_value_max) || s_value_min > s_value_max)
						{
							cin.clear();
							cin.ignore();
							cout << "Podaj prawidlowa wartosc" << endl;
						}
						cout << "\nUstawiono zakres wartosci pojazdu od " << s_value_min << " do " << s_value_max << " zl.";
						set = true;
						Sleep(2000);

					}





					if (menu == 0)
					{
						system("CLS");
						continue;
					}






				}
			break;
		}





		case '7':
			exit(0);
			break;

		default:
		{
			cout << "Nie ma takiej opcji w menu!";
			Sleep(1500);
		}
		system("CLS");
		}
		
	}
	return 0;
}


void show_menu()
{
	cout << "1. Dodaj samochod do bazy." << endl;
	cout << "2. Przeglad bazy danych." << endl;
	cout << "3. Sortowanie" << endl;
	cout << "4. Wczytanie bazy z pliku" << endl;
	cout << "5. Wyszukiwanie/filtrowanie" << endl;
	cout << "6." << endl;
	cout << "7. Wyjscie z programu." << endl;
}

void get_data(string &make, string &model, int &body_type, int &fuel, int &transmission, int &engine_size, int &year, int &value)
{
	string clear;
	cout << "Podaj marke auta: " << endl;
	getline(cin, make);
	transform(make.begin(), make.end(), make.begin(), ::toupper);
	cout << "Podaj model auta: " << endl;
	getline(cin, model);
	transform(model.begin(), model.end(), model.begin(), ::toupper);
	cout << "Wybierz rodzaj nadwozia." << endl;
	cout << "1.Hatchback  2.Sedan  3.Kombi 4.Kabriolet  5.Coupe  6.SUV  7.Terenowy"<<endl;
	while (!(cin>>body_type) || body_type > '7' || body_type == '0')
	{
		cin.clear();
		cin.ignore();
		cout << "Podaj prawidlowa wartosc" << endl;
	}
	cout << "Wybierz rodzaj paliwa." << endl;
	cout << "1.Benzyna  2.Diesel  3.LPG  4.Elektryczny  5.Hybryda" << endl;
	while (!(cin >> fuel) || fuel > '5' || fuel == '0')
	{
		cin.clear();
		cin.ignore();
		cout << "Podaj prawidlowa wartosc" << endl;
	}
	cout << "Wybierz typ skrzyni biegow." << endl;
	cout << "1.Manualna  2.Automatyczna" << endl;
	while (!(cin >> transmission) || transmission > '2' || transmission == '0')
	{
		cin.clear();
		cin.ignore();
		cout << "Podaj prawidlowa wartosc" << endl;
	}
	cout << "Podaj pojemnosc silnika w cm^3: " << endl;
	while (!(cin >> engine_size))
	{
		cin.clear();
		cin.ignore();
		cout << "Podaj prawidlowa wartosc" << endl;
	}
	cin.ignore();
	cout << "Podaj rok produkcji auta: " << endl;
	while (!(cin >> year))
	{
		cin.clear();
		cin.ignore();
		cout << "Podaj prawidlowa wartosc" << endl;
	}
	cin.ignore();
	cout << "Podaj wartosc auta w zl: " << endl;
	while (!(cin >> value))
	{
		cin.clear();
		cin.ignore();
		cout << "Podaj prawidlowa wartosc" << endl;
	}
	if (cin) cin.ignore(cin.rdbuf()->in_avail());
	
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




void searching(vector <Data>& vector_s, vector<Data> vec, string s_make, string s_model, int s_body, int s_fuel, int s_transmission, int s_eng_min, int s_eng_max, int s_year_min, int s_year_max, int s_val_min, int s_val_max, int c )
{	
	vector_s = vec;
	if (s_make != " ")
	{
		bool flag = false;
		bool flag2 = false;
		for (;;)
		{
			for (int i = 0; i < vector_s.size(); i++)
			{
				string make = vector_s[i].get_make();
				for (int j = 0; j < make.length(); j++)
				{
					if (s_make[j] != make[j])
					{
						vector_s.erase(vector_s.begin()+ i);
						flag = true;
						c -= 1;
						break;
					}
				}
				if (flag)
				{
					flag = false;
					break;
				}
				if (i == (vector_s.size()-1))
				{
					flag2 = true;
					break;
				}
			}
			if (flag2 || vector_s.size()==0)
				break;
		}	
	}

	if (s_model != " ")
	{
		bool flag = false;
		bool flag2 = false;
		for (;;)
		{
			for (int i = 0; i < vector_s.size(); i++)
			{
				string model = vector_s[i].get_model();
				for (int j = 0; j < model.length(); j++)
				{
					if (s_model[j] != model[j])
					{
						vector_s.erase(vector_s.begin() + i);
						flag = true;
						c -= 1;
						break;
					}
				}
				if (flag)
				{
					flag = false;
					break;
				}
				if (i == (vector_s.size() - 1))
				{
					flag2 = true;
					break;
				}
			}
			if (flag2)
				break;
		}
	}

	if (s_body != 0)
	{
		bool flag = false;
		for (;;)
		{
			for (int i = 0; i < vector_s.size(); i++)
			{
				int body = (vector_s[i].get_body())-48;
				if (s_body != body)
				{
					vector_s.erase(vector_s.begin() + i);
					c -= 1;
					break;
				}
				
				if (i == (vector_s.size() - 1))
				{
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
	}

	if (s_fuel != 0)
	{
		bool flag = false;
		for (;;)
		{
			for (int i = 0; i < vector_s.size(); i++)
			{
				int fuel = (vector_s[i].get_fuel()) - 48;
				if (s_fuel != fuel)
				{
					vector_s.erase(vector_s.begin() + i);
					c -= 1;
					break;
				}

				if (i == (vector_s.size() - 1))
				{
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
	}

	if (s_transmission != 0)
	{
		bool flag = false;
		for (;;)
		{
			for (int i = 0; i < vector_s.size(); i++)
			{
				int transmission = (vector_s[i].get_transmission()) - 48;
				if (s_transmission != transmission)
				{
					vector_s.erase(vector_s.begin() + i);
					c -= 1;
					break;
				}

				if (i == (vector_s.size() - 1))
				{
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
	}

	if (s_eng_min != 0 || s_eng_max != 0)
	{
		bool flag = false;
		for (;;)
		{
			for (int i = 0; i < vector_s.size(); i++)
			{
				int eng = vector_s[i].get_engine();
				if (eng < s_eng_min || eng > s_eng_max)
				{
					vector_s.erase(vector_s.begin() + i);
					c -= 1;
					break;
				}

				if (i == (vector_s.size() - 1))
				{
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
	}

	if (s_year_min != 0 || s_year_max != 0)
	{
		bool flag = false;
		for (;;)
		{
			for (int i = 0; i < vector_s.size(); i++)
			{
				int year = vector_s[i].get_year();
				if (year < s_year_min || year > s_year_max)
				{
					vector_s.erase(vector_s.begin() + i);
					c -= 1;
					break;
				}

				if (i == (vector_s.size() - 1))
				{
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
	}

	if (s_val_min != 0 || s_val_max != 0)
	{
		bool flag = false;
		for (;;)
		{
			for (int i = 0; i < vector_s.size(); i++)
			{
				int val = vector_s[i].get_value();
				if (val < s_val_min || val > s_val_max)
				{
					vector_s.erase(vector_s.begin() + i);
					c -= 1;
					break;
				}

				if (i == (vector_s.size() - 1))
				{
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
	}

	if (vector_s.size() == 0)
	{	
		system("CLS");
		cout << "Brak samochodow w bazie spelniajacych kryteria";
		Sleep(4000);
	}
	else
	{
		int s = 0;
		bool g = false;
		system("CLS");
		vector_s[s].browsing_wfilter();
		for (;;)
		{
			for (;;)
			{
				if (GetAsyncKeyState(VK_ESCAPE) & 1)
				{
					g = true;
					break;
				}
				if (GetAsyncKeyState(VK_UP) & 1)
				{
					s -= 1;
					if (s < 0)
					{
						s = 0;
						break;
					}
					system("CLS");
					vector_s[s].browsing_wfilter();
				}
				if (GetAsyncKeyState(VK_DOWN) & 1)
				{
					s += 1;
					if (s >= c)
					{
						s = c - 1;
						break;
					}
					system("CLS");
					vector_s[s].browsing_wfilter();
				}


			}
			if (g)
			{
				g = false;
				while (_kbhit())
					_getch();
				break;
			}

		}
	}

}
