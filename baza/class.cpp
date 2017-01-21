#include "stdafx.h"
#include "class.h"


Data::Data(){}
Data::Data(string make, string model, int body_type, int fuel, int transmission, int engine_size, int year, int value)
{
	m_make = make;
	m_model = model;
	m_body_type = body_type;
	m_fuel = fuel;
	m_transmission = transmission;
	m_engine_size = engine_size;
	m_year = year;
	m_value = value;
}
string Data::convert_for_save(string mk, string md, int bt, int fu, int tr, int eng, int year, int val)
{
	string text;
	replacing_space(mk);
	replacing_space(md);
	text.append(mk);
	text.append(" ");

	text.append(md);
	text.append(" ");

	text += to_string(bt);
	text.append(" ");

	text += to_string(fu);
	text.append(" ");

	text += to_string(tr);
	text.append(" ");

	text += to_string(eng);
	text.append(" ");

	text += to_string(year);
	text.append(" ");

	text += to_string(val);
	return text;
}

string Data::replacing_space(string &text)
{
	for (unsigned int i = 0; i <= text.size(); i++)
		if (text[i] == ' ')
			text.replace(i, 1, "_");
	return text;
}

void Data::save_to_file(string name)
{
		fstream save(name, ios::out | ios::app);
		save << convert_for_save(m_make, m_model, m_body_type, m_fuel, m_transmission, m_engine_size, m_year, m_value);
		save << endl;
		save.close();
}

void Data::browsing()
{
	cout << "Marka: " << "\t\t\t" << m_make << endl;
	cout << "Model: " <<"\t\t\t"<< m_model << endl;
	cout << "Typ nadwodzia: " << "\t\t" << body_type(m_body_type)<< endl;
	cout << "Rodzaj skrzyni biegow: "<<"\t";
	if (m_transmission == 1)
		cout << "Manualna" << endl;
	else cout << "Automatyczna" << endl;
	cout << "Rodzaj paliwa: " << "\t\t"<< fuel(m_fuel) << endl;
	cout << "Pojemnosc silnika: " <<"\t"<< m_engine_size <<" cm^3"<< endl;
	cout << "Rok produkcji: " <<"\t\t"<< m_year <<" rok"<< endl;
	cout << "Wartosc: " << "\t\t" << m_value << " zl" << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "^-strzalka w gore = poprzedni    v-strzalka w dol = nastepny" << endl;
	cout << "ESC = wyjscie                   DELETE = usun wybrany element" << endl;
	cout << "F1 = zapisz                     F3 = aktualizacja danych";
}

void Data::browsing_wfilter()
{
	cout << "Marka: " << "\t\t\t" << m_make << endl;
	cout << "Model: " << "\t\t\t" << m_model << endl;
	cout << "Typ nadwodzia: " << "\t\t" << body_type(m_body_type) << endl;
	cout << "Rodzaj skrzyni biegow: " << "\t";
	if (m_transmission == 1)
		cout << "Manualna" << endl;
	else cout << "Automatyczna" << endl;
	cout << "Rodzaj paliwa: " << "\t\t" << fuel(m_fuel) << endl;
	cout << "Pojemnosc silnika: " << "\t" << m_engine_size << " cm^3" << endl;
	cout << "Rok produkcji: " << "\t\t" << m_year << " rok" << endl;
	cout << "Wartosc: " << "\t\t" << m_value << " zl" << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "^-strzalka w gore = poprzedni    v-strzalka w dol = nastepny" << endl;
	cout << "ESC = wyjscie";
	
}

string Data::body_type(int nr)
{
	string one = "Hatchback";
	string two = "Sedan";
	string three = "Kombi";
	string four= "Kabriolet";
	string five = "Coupe";
	string six = "SUV";
	string seven = "Terenowy";
	if (nr == 1)
		return one;
	else if (nr == 2)
		return two;
	else if (nr == 3)
		return three;
	else if (nr == 4)
		return four;
	else if (nr == 5)
		return five;
	else if (nr == 6)
		return six;
	else if (nr == 7)
		return seven;
}

string Data::fuel(int nr)
{
	string one = "Benzyna";
	string two = "Diesel";
	string three = "LPG";
	string four = "Elektryczny";
	string five = "Hybryda";
	if (nr == 1)
		return one;
	else if (nr == 2)
		return two;
	else if (nr == 3)
		return three;
	else if (nr == 4)
		return four;
	else if (nr == 5)
		return five;
}

bool compare_by_year(const Data & lhs, const Data &rhs)
{
	return lhs.m_year < rhs.m_year;
}
bool compare_by_value(const Data &lhs, const Data &rhs)
{
	return lhs.m_value < rhs.m_value;
}
bool compare_by_eng(const Data &lhs, const Data &rhs)
{
	return lhs.m_engine_size < rhs.m_engine_size;
}
bool compare_by_make(const Data &lhs, const Data &rhs)
{
	return lhs.m_make < rhs.m_make;
}
bool compare_by_model(const Data &lhs, const Data &rhs)
{
	return lhs.m_model < rhs.m_model;
}


string Data::get_make()
{
	return m_make;
}
string Data::get_model()
{
	return m_model;
}
int Data::get_body()
{
	return m_body_type;
}
int Data::get_fuel()
{
	return m_fuel;
}
int Data::get_transmission()
{
	return m_transmission;
}
int Data::get_engine()
{
	return m_engine_size;
}
int Data::get_year()
{
	return m_year;
}
int Data::get_value()
{
	return m_value;
}



void Data::set_make(string  e_make)
{
	m_make = e_make;
}

void Data::set_model(string e_model)
{
	m_model = e_model;
}

void Data::set_body_type(int nr)
{
	m_body_type = nr;
}

void Data::set_fuel(int nr)
{
	m_fuel = nr;
}

void Data::set_transmission(int nr)
{
	m_transmission = nr;
}

void Data::set_engine_size(int nr)
{
	m_engine_size = nr;
}

void Data::set_year(int nr)
{
	m_year = nr;
}

void Data::set_value(int nr)
{
	m_value = nr;
}
