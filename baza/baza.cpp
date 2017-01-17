// baza.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "class.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

bool password_is_set = false;
int key = 5;
void read_pass();
void save(string);
void get_new_password();
string salt();
string ha(string);
string de_ha(string);
bool check_pass();
void pass_settings();
string get_path();
void show_menu();
void show_menu_wfilter(string, string, int, int, int, int, int, int, int, int, int);
void get_data(string&, string&, int&, int&, int&, int&, int&, int&);
void loading_from_file(int&, vector <Data>&,string);
string delete_underscore(string&);
void searching(vector <Data>&, vector<Data>, string, string, int, int, int, int, int, int, int, int, int, int);

int main()
{
	read_pass();
	if (!password_is_set)
	{
		get_new_password();
		system("CLS");
	}
	if(check_pass())
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
				bool b = true;
				bool j = true;
				vec[c].browsing();
				do
				{
					do
					{
						if (GetAsyncKeyState(VK_ESCAPE) & 1)
						{
							b = 0;
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
							bool del_flag = false;
							cout << "\n\n\nCZY NA PEWNO CHCESZ USUNAC WYBRANY ELEMENT?" << endl;
							cout << "y/n" << endl;
							do
							{
								while (_kbhit()) _getch();
								char menu_del = _getch();

								switch (menu_del)
								{
								case 'y':
								{
									vec.erase(vec.begin() + c);
									counter -= 1;
									if (counter == 0)
									{
										system("CLS");
										cout << "Brak elementow w bazie.";
										Sleep(1500);
										b = 0;
										break;
									}
									if (c > 0) c -= 1;
									system("CLS");
									vec[c].browsing();
									del_flag = false;
									break;
								}
								case 'n':
								{
									system("CLS");
									vec[c].browsing();
									del_flag = false;
									break;
								}
								default:
								{
									cin.clear();
									cout << "Podaj prawidlowa wartosc" << endl;
									del_flag = true;
								}
								}
							} while (del_flag);

						}
						if (GetAsyncKeyState(112) & 1)
						{
							cin.sync();
							bool save_flag = false;
							cout << "\n\n\nChcesz nadpisac aktualnie wczytana baze danych?" << endl;
							cout << "y/n?         a = anuluj" << endl;
							do
							{
								while (_kbhit()) _getch();
								char menu_save = _getch();
								switch (menu_save)
								{
								case 'y':
								{
									fstream del(name_of_data, ios::out | ios::trunc);
									del.close();
									for (int i = 0; i < vec.size(); i++)
										vec[i].save_to_file(name_of_data);
									cout << "Zapisano!";
									Sleep(2000);
									b = false;
									j = false;
									save_flag = false;
									break;
								}
								case 'n':
								{
									string new_name;
									cin.sync();
									system("CLS");
									cout << "Podaj nazwe nowej bazy: ";
									getline(cin, new_name);
									new_name.append(".xdd");
									for (int i = 0; i < vec.size(); i++)
										vec[i].save_to_file(new_name);
									cout << "Zapisano!";
									Sleep(2000);
									b = false;
									j = false;
									save_flag = false;
									break;
								}
								case 'a':
								{
									b = false;
									j = false;
									save_flag = false;
									break;
								}
								default:
								{
									cin.clear();
									cout << "Podaj prawidlowa wartosc" << endl;
									save_flag = true;
									break;
								}
								}
							} while (save_flag);
						}
						if (GetAsyncKeyState(114) & 1)
						{
							string e_make = " ";
							string e_model = " ";
							int e_body_type = 0;
							int e_fuel = 0;
							int e_transmission = 0;
							int e_engine = 0;
							int e_year = 0;
							int e_value = 0;
							system("CLS");
							cout << "Wybierz ceche ktora chcesz edytowac:" << endl;
							cout << "1. Marka." << endl;
							cout << "2. Model." << endl;
							cout << "3. Typ nadwozia." << endl;
							cout << "4. Rodzaj paliwa." << endl;
							cout << "5. Rodzaj skrzyni biegow." << endl;
							cout << "6. Pojemnosc silnika." << endl;
							cout << "7. Rok produkcji." << endl;
							cout << "8. Wartosc." << endl;
							while (_kbhit()) _getch();
							char edit_menu = _getch();
							switch (edit_menu)
							{
							case '1':
							{
								cout << "Podaj marke: ";
								getline(cin, e_make);
								transform(e_make.begin(), e_make.end(), e_make.begin(), ::toupper);
								vec[c].set_make(e_make);
								system("CLS");
								b = false;
								j = false;
								break;
							}
							case '2':
							{
								cout << "Podaj model: ";
								getline(cin, e_model);
								transform(e_model.begin(), e_model.end(), e_model.begin(), ::toupper);
								vec[c].set_model(e_model);
								system("CLS");
								b = false;
								j = false;
								break;
							}
							case '3':
							{
								cout << "Wybierz rodzaj nadwozia." << endl;
								cout << "1.Hatchback  2.Sedan  3.Kombi 4.Kabriolet  5.Coupe  6.SUV  7.Terenowy" << endl;
								while (!(cin >> e_body_type) || e_body_type > 7 || e_body_type == 0)
								{
									cin.clear();
									cin.ignore();
									cout << "Podaj prawidlowa wartosc" << endl;
								}
								vec[c].set_body_type(e_body_type);
								system("CLS");
								b = false;
								j = false;
								break;
							}
							case '4':
							{
								cout << "Wybierz rodzaj paliwa." << endl;
								cout << "1.Benzyna  2.Diesel  3.LPG  4.Elektryczny  5.Hybryda" << endl;
								while (!(cin >> e_fuel) || e_fuel > 5 || e_fuel == 0)
								{
									cin.clear();
									cin.ignore();
									cout << "Podaj prawidlowa wartosc" << endl;
								}
								vec[c].set_fuel(e_fuel);
								system("CLS");
								b = false;
								j = false;
								break;
							}
							case '5':
							{
								cout << "Wybierz typ skrzyni biegow." << endl;
								cout << "1.Manualna  2.Automatyczna" << endl;
								while (!(cin >> e_transmission) || e_transmission > 2 || e_transmission == 0)
								{
									cin.clear();
									cin.ignore();
									cout << "Podaj prawidlowa wartosc" << endl;
								}
								vec[c].set_transmission(e_transmission);
								system("CLS");
								b = false;
								j = false;
								break;
							}
							case '6':
							{
								cout << "Podaj pojemnosc silnika w cm^3: " << endl;
								while (!(cin >> e_engine) || e_engine <= 0)
								{
									cin.clear();
									cin.ignore();
									cout << "Podaj prawidlowa wartosc" << endl;
								}
								cin.ignore();
								vec[c].set_engine_size(e_engine);
								system("CLS");
								b = false;
								j = false;
								break;
							}
							case '7':
							{
								cout << "Podaj rok produkcji auta: " << endl;
								while (!(cin >> e_year) || e_year <= 0)
								{
									cin.clear();
									cin.ignore();
									cout << "Podaj prawidlowa wartosc" << endl;
								}
								cin.ignore();
								vec[c].set_year(e_year);
								system("CLS");
								b = false;
								j = false;
								break;
							}
							case '8':
							{
								cout << "Podaj wartosc auta w zl: " << endl;
								while (!(cin >> e_value) || e_value <= 0)
								{
									cin.clear();
									cin.ignore();
									cout << "Podaj prawidlowa wartosc" << endl;
								}
								cin.ignore();
								vec[c].set_value(e_value);
								system("CLS");
								b = false;
								j = false;
								break;
							}
							default:
								break;
							}
						}
					} while (j);
				} while (b);
				break;
			}
			case '3':
			{
				bool sort_flag = true;
				do
				{
					system("CLS");
					cout << "Prosze wybrac wartosc wg. ktorej sortowac." << endl;
					cout << "1. Watrosc" << endl;
					cout << "2. Rok produkcji" << endl;
					cout << "3. Pojemnosc silnika" << endl;
					cout << "4. Marka" << endl;
					cout << "5. Model" << endl;
					auto *comparator = &compare_by_value;
					while (_kbhit()) _getch();
					char sort_menu = _getch();
					switch (sort_menu)
					{
					case '1':
					{
						comparator = &compare_by_value;
						sort(vec.begin(), vec.end(), comparator);
						cout << "\n\nSortowanie zakonczone.";
						Sleep(1000);
						sort_flag = false;
						break;
					}
					case '2':
					{
						comparator = &compare_by_year;
						sort(vec.begin(), vec.end(), comparator);
						cout << "\n\nSortowanie zakonczone.";
						Sleep(1000);
						sort_flag = false;
						break;
					}
					case '3':
					{
						comparator = &compare_by_eng;
						sort(vec.begin(), vec.end(), comparator);
						cout << "\n\nSortowanie zakonczone.";
						Sleep(1000);
						sort_flag = false;
						break;
					}
					case '4':
					{
						comparator = &compare_by_make;
						sort(vec.begin(), vec.end(), comparator);
						cout << "\n\nSortowanie zakonczone.";
						Sleep(1000);
						sort_flag = false;
						break;
					}
					case '5':
					{
						comparator = &compare_by_model;
						sort(vec.begin(), vec.end(), comparator);
						cout << "\n\nSortowanie zakonczone.";
						Sleep(1000);
						sort_flag = false;
						break;
					}
					default:
					{
						cin.clear();
						cout << "Podaj prawidlowa wartosc" << endl;
						Sleep(1500);
						sort_flag = true;
					}
					}
					if (cin) cin.ignore(cin.rdbuf()->in_avail());
				} while (sort_flag);
				break;
			}
			case '4':
			{
				system("CLS");
				cout << "Podaj nazwe pliku wraz z rozszerzeniem: " << endl;
				bool save_flag = true;
				string name;
				getline(cin, name);
				cout << "Wybierz:" << endl;
				cout << "1. Nadpisz aktualnie istniejaca baze." << endl;
				cout << "2. Dopisz do aktualnie istniejacej bazy." << endl;
				cout << "3. Anuluj." << endl;
				do
				{
					while (_kbhit()) _getch();
					char save_menu = _getch();
					switch (save_menu)
					{
					case '1':
					{
						vec.clear();
						counter = 0;
						loading_from_file(counter, vec, name);
						cout << "Nadpisano!";
						Sleep(1500);
						save_flag = false;
						break;
					}
					case '2':
					{
						loading_from_file(counter, vec, name);
						save_flag = false;
						cout << "Dopisano!";
						Sleep(1500);
						break;
					}
					case '3':
					{
						save_flag = false;
						break;
					}
					default:
					{
						cin.clear();
						cout << "Podaj prawidlowa wartosc" << endl;
						break;
					}
					}
				} while (save_flag);
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
				bool filter_flag = true;
				do
				{
					show_menu_wfilter(s_make, s_model, s_body_type, s_fuel, s_transmission, s_engine_size_min, s_engine_size_max, s_year_min, s_year_max, s_value_min, s_value_max);
					while (_kbhit()) _getch();
					char f_menu = _getch();
					switch (f_menu)
					{
					case '0':
					{
						filter_flag = false;
						system("CLS");
						break;
					}
					case '1':
					{
						cout << "\n\n\nWpisz poszukiwana marke: ";
						while (_kbhit()) _getch();
						getline(cin, s_make);
						cout << "\nUstawiono filtr \"" << s_make << "\" dla marki.";
						transform(s_make.begin(), s_make.end(), s_make.begin(), ::toupper);
						set = true;
						Sleep(2000);
						break;
					}
					case '2':
					{
						cout << "\n\n\nWpisz poszukiwany model: ";
						while (_kbhit()) _getch();
						getline(cin, s_model);
						cout << "\nUstawiono filtr \"" << s_model << "\" dla modelu.";
						transform(s_model.begin(), s_model.end(), s_model.begin(), ::toupper);
						set = true;
						Sleep(2000);
						break;
					}
					case '3':
					{

						bool body_flag = true;
						do
						{
							cout << "\n\n\nWybierz typ nadwozia: " << endl;
							cout << "1.Hatchback  2.Sedan  3.Kombi 4.Kabriolet  5.Coupe  6.SUV  7.Terenowy" << endl;
							while (_kbhit()) _getch();
							char body_menu = _getch();
							cout << "\nUstawiono filtr \"";
							switch (body_menu)
							{
							case '1':
							{
								cout << "Hatchback";
								s_body_type = 1;
								set = true;
								body_flag = false;
								break;
							}
							case '2':
							{
								cout << "Sedan";
								s_body_type = 2;
								set = true;
								body_flag = false;
								break;
							}
							case '3':
							{
								cout << "Kombi";
								s_body_type = 3;
								set = true;
								body_flag = false;
								break;
							}
							case '4':
							{
								cout << "Kabriolet";
								s_body_type = 4;
								set = true;
								body_flag = false;
								break;
							}
							case '5':
							{
								cout << "Coupe";
								s_body_type = 5;
								set = true;
								body_flag = false;
								break;
							}
							case '6':
							{
								cout << "SUV";
								s_body_type = 6;
								set = true;
								body_flag = false;
								break;
							}
							case '7':
							{
								cout << "Terenowy";
								s_body_type = 7;
								set = true;
								body_flag = false;
								break;
							}
							default:
							{
								system("CLS");
								cin.clear();
								cout << "Podaj prawidlowa wartosc" << endl;
								break;
							}
							}

						} while (body_flag);
						cout << "\" dla typu nadwozia.";
						Sleep(2000);
						break;
					}
					case '4':
					{
						bool fuel_flag = true;
						do
						{
							cout << "\n\n\nWybierz rodzaj paliwa: " << endl;
							cout << "1.Benzyna  2.Diesel  3.LPG  4.Elektryczny  5.Hybryda" << endl;
							while (_kbhit()) _getch();
							char fuel_menu = _getch();
							cout << "\nUstawiono filtr \"";
							switch (fuel_menu)
							{
							case '1':
							{
								cout << "Benzyna";
								s_fuel = 1;
								set = true;
								fuel_flag = false;
								break;
							}
							case '2':
							{
								cout << "Diesel";
								s_fuel = 2;
								set = true;
								fuel_flag = false;
								break;
							}
							case '3':
							{
								cout << "LPG";
								s_fuel = 3;
								set = true;
								fuel_flag = false;
								break;
							}
							case '4':
							{
								cout << "Elektryczny";
								s_fuel = 4;
								set = true;
								fuel_flag = false;
								break;
							}
							case '5':
							{
								cout << "Hybryda";
								s_fuel = 5;
								set = true;
								fuel_flag = false;
								break;
							}
							default:
							{
								system("CLS");
								cin.clear();
								cout << "Podaj prawidlowa wartosc" << endl;
								break;
							}
							}

						} while (fuel_flag);
						cout << "\" dla rodzaju paliwa.";
						Sleep(2000);
						break;
					}
					case '5':
					{
						bool transmission_flag = true;
						do
						{
							cout << "\n\n\nWybierz typ skrzyni biegow: " << endl;
							cout << "1.Manualna  2.Automatyczna" << endl;
							while (_kbhit()) _getch();
							char transmission_menu = _getch();
							cout << "\nUstawiono filtr \"";
							switch (transmission_menu)
							{
							case '1':
							{
								cout << "Manualna";
								s_transmission = 1;
								set = true;
								transmission_flag = false;
								break;
							}
							case '2':
							{
								cout << "Automatyczna";
								s_transmission = 2;
								set = true;
								transmission_flag = false;
								break;
							}

							default:
							{
								system("CLS");
								cin.clear();
								cout << "Podaj prawidlowa wartosc" << endl;
								break;
							}
							}
						} while (transmission_flag);
						cout << "\" dla typu skrzyni biegow.";
						Sleep(2000);
						break;
					}
					case '6':
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
						break;
					}
					case '7':
					{
						cout << "\n\n\nWpisz zakres roku produkcji: " << endl;
						cout << "Od: ";
						while (!(cin >> s_year_min) || s_year_min < 0)
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
						break;
					}
					case '8':
					{
						cout << "\n\n\nWpisz zakres wartosci pojazdu: " << endl;
						cout << "Od: ";
						while (!(cin >> s_value_min) || s_value_min < 0)
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
						break;
					}
					case '9':
					{
						if (set)
							searching(vec_s, vec, s_make, s_model, s_body_type, s_fuel, s_transmission, s_engine_size_min, s_engine_size_max, s_year_min, s_year_max, s_value_min, s_value_max, counter);
						else
						{
							cout << "Nie ustawiono zadnych filtrow!";
							Sleep(2000);
						}
						break;
					}
					default:
					{
						cin.clear();
						cout << "Podaj prawidlowa wartosc" << endl;
						Sleep(1500);
						break;
					}
					}
				} while (filter_flag);
				break;
			}
			case '6':
			{
				exit(0);
				break;
			}
			default:
			{
				cout << "Nie ma takiej opcji w menu!";
				while (_kbhit()) _getch();
				Sleep(1500);
			}
			system("CLS");
			}
		}
	}
	else
	{
		cout << "\nHaslo nieprawidlowe";
		Sleep(2000);
		return 0;
	}
	
}


void show_menu()
{
	cout << "1. Dodaj samochod do bazy." << endl;
	cout << "2. Przeglad bazy danych." << endl;
	cout << "3. Sortowanie" << endl;
	cout << "4. Wczytanie bazy z pliku" << endl;
	cout << "5. Wyszukiwanie/filtrowanie" << endl;
	cout << "6. Wyjscie z programu." << endl;
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
	while (!(cin>>body_type) || body_type > 7 || body_type == 0)
	{
		cin.clear();
		cin.ignore();
		cout << "Podaj prawidlowa wartosc" << endl;
	}
	cout << "Wybierz rodzaj paliwa." << endl;
	cout << "1.Benzyna  2.Diesel  3.LPG  4.Elektryczny  5.Hybryda" << endl;
	while (!(cin >> fuel) || fuel > 5 || fuel == 0)
	{
		cin.clear();
		cin.ignore();
		cout << "Podaj prawidlowa wartosc" << endl;
	}
	cout << "Wybierz typ skrzyni biegow." << endl;
	cout << "1.Manualna  2.Automatyczna" << endl;
	while (!(cin >> transmission) || transmission > 2 || transmission == 0)
	{
		cin.clear();
		cin.ignore();
		cout << "Podaj prawidlowa wartosc" << endl;
	}
	cout << "Podaj pojemnosc silnika w cm^3: " << endl;
	while (!(cin >> engine_size) || engine_size <= 0)
	{
		cin.clear();
		cin.ignore();
		cout << "Podaj prawidlowa wartosc" << endl;
	}
	cin.ignore();
	cout << "Podaj rok produkcji auta: " << endl;
	while (!(cin >> year) || year <= 0)
	{
		cin.clear();
		cin.ignore();
		cout << "Podaj prawidlowa wartosc" << endl;
	}
	cin.ignore();
	cout << "Podaj wartosc auta w zl: " << endl;
	while (!(cin >> value) || value <= 0)
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
		int bt;
		int fuel;
		int tran;
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
		cout << "Czy chcesz kontynuowac z pusta baza danych?" << endl;
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
				for (int j = 0; j < s_make.length(); j++)
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
				for (int j = 0; j < s_model.length(); j++)
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
			if (flag2 || vector_s.size() == 0)
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
				int body = vector_s[i].get_body();
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
			if (flag || vector_s.size() == 0)
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
				int fuel = vector_s[i].get_fuel();
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
			if (flag || vector_s.size() == 0)
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
				int transmission = vector_s[i].get_transmission();
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
			if (flag || vector_s.size() == 0)
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
			if (flag || vector_s.size() == 0)
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
			if (flag || vector_s.size() == 0)
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
			if (flag || vector_s.size() == 0)
				break;
		}
	}

	if (vector_s.size() == 0)
	{	
		system("CLS");
		cout << "Brak samochodow w bazie spelniajacych wybrane kryteria";
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

void show_menu_wfilter(string make, string model, int body, int fuel, int tra, int eng_min, int eng_max, int year_min, int year_max, int val_min, int val_max  )
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
	cout << "9. Wyswietl." << endl;
	cout << "0. Wyjscie." << endl << endl << endl;
	if (make != " " || model != " " || body != 0 || fuel != 0 || tra != 0 || eng_min != 0 || eng_max != 0 || year_min != 0 || year_max != 0 || val_min != 0 || val_max != 0)
	cout << "Aktualnie ustawione filtry: " << endl;
	if (make != " ")
		cout << "Marka: " << make << endl;
	if (model != " ")
		cout << "Model: " << model << endl;
	if (body != 0)
	{
		cout << "Typ nadwozia: ";
		if (body == 1)
			cout << "Hatchback" << endl;
		else if (body == 2)
			cout << "Sedan" << endl;
		else if (body == 3)
			cout << "Kombi" << endl;
		else if (body == 4)
			cout << "Kabriolet" << endl;
		else if (body == 5)
			cout << "Coupe" << endl;
		else if (body == 6)
			cout << "SUV" << endl;
		else if (body == 7)
			cout << "Terenowy" << endl;
	}
	if (fuel != 0)
	{
		cout << "Rodzaj paliwa: ";
		if (fuel == 1)
			cout << "Benzyna" << endl;
		else if (fuel == 2)
			cout << "Diesel" << endl;
		else if (fuel == 3)
			cout << "LPG" << endl;
		else if (fuel == 4)
			cout << "Elektryczny" << endl;
		else if (fuel == 5)
			cout << "Hybryda" << endl;
	}
	if (tra != 0)
	{
		cout << "Rodzaj skrzyni biegow: ";
		if (tra == 1)
			cout << "Manualna" << endl;
		else if (tra == 2)
			cout << "Automatyczna" << endl;
	}
	if (eng_min != 0 || eng_max != 0)
		cout << "Pojemnosc silnika od: " << eng_min << " do: " << eng_max << " cm^3." << endl;
	if (year_min != 0 || year_max != 0)
		cout << "Rok produkcji od: " << year_min << " do: " << year_max << " roku. " << endl;
	if (val_min != 0 || val_max != 0)
		cout << "Wartosc od: " << val_min << " do: " << val_max << " zl." << endl;
}

void read_pass()
{
	fstream open("set.dot", ios::in);
	if (open.good())
		open >> password_is_set;
	else
	{
		cout << "Fatal error";
		Sleep(2000);
		exit(0);
	}
}

void get_new_password()
{
	string a1;
	string a2;

	do
	{	
		a1.clear();
		a2.clear();
		char f;
		char s;
		cout << "Ustawianie hasla." << endl;
		cout << "Wprowadz haslo: ";
		for (int i = 0; i < 1000; i++)
		{
			f = _getch();
			if (f == '\r')
				break;
			cout << "*";
			a1 += f;
		}
		cout << endl;
		cout << "Wprowadz haslo ponownie: ";
		for (int i = 0; i < 1000; i++)
		{
			s = _getch();
			if (s == '\r')
				break;
			cout << "*";
			a2 += s;
		}
		cout << endl;
		if (a1 != a2)
		{
			cout << "Podane hasla nie zgadzaja sie" << endl;
			Sleep(2000);
			system("CLS");
		}
	} while (a1 != a2);
	cout << "Haslo ustawione!" << endl;
	Sleep(2000);
	::save(a1);
}
void save(string a)
{
	string path = get_path();
	string salti = salt();
	a.insert(0, salti);
	string pass = ha(a);
	fstream sv(path, ios::out | ios::trunc);
	if (sv.good())
	{
		password_is_set = true;
		pass_settings();
		sv << salti << endl;
		sv << pass;
		sv.close();
	}
	else
	{
		cout << "Blad odczytu" << endl;
		Sleep(2000);
		exit(0);
	}
}
string get_path()
{
	string pt;
	char *pPath;
	size_t sz = 0;
	if (_dupenv_s(&pPath, &sz, "USERPROFILE") == 0)
	{
		pt = pPath;
		pt.append("\\database.conf");
		return pt;
	}
	else
	{
		cout << "Blad odczytu" << endl;
		Sleep(2000);
		exit(0);
	}
}
string salt()
{
	string salt;
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		char lol = (rand() % 90) + 33;
		salt += lol;
	}
	return salt;
}
string ha(string a)
{
	string ps;
	for (int i = 0; i<a.size(); i++)
	{
		char b = a[i];
		b += key;
		if (b > 122)
			b %= 90;
		ps += b;
	}
	return ps;
}
void pass_settings()
{
	fstream sett("set.dot", ios::out | ios::trunc);
	sett << password_is_set;
	sett.close();
}
bool check_pass()
{
	char k;
	string entered_password;
	string loaded_password;
	string loaded_salt;

	cout << "Podaj haslo: ";
	for (int i = 0; i < 1000; i++)
	{
		k = _getch();
		if (k == '\r')
			break;
		cout << "*";
		entered_password += k;
	}
	fstream load(get_path(), ios::in);
	if (load.good())
	{
		load >> loaded_salt;
		load >> loaded_password;
		entered_password.insert(0, loaded_salt);
		string de_pass = de_ha(loaded_password);
		if (entered_password == de_pass)
			return true;

	}
	else return false;
	return false;
}
string de_ha(string p)
{
	string pass;
	for (int i = 0; i < p.size(); i++)
	{
		char b = p[i];
		b -= key;
		if (b < 33)
			b += 90;
		pass += b;
	}
	return pass;
}