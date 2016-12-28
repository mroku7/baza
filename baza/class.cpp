#include "stdafx.h"
#include "class.h"


Data::Data(){}
Data::Data(string make, string model, char body_type, char fuel, char transmission, int engine_size, int year, int value)
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
string Data::convert_for_save(string mk, string md, char bt, char fu, char tr, int eng, int year, int val)
{
	string text;
	replacing_space(mk);
	replacing_space(md);
	text.append(mk);
	text.append(" ");
	text.append(md);
	text.append(" ");
	text.push_back(bt);
	text.append(" ");
	text.push_back(fu);
	text.append(" ");
	text.push_back(tr);
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
void Data::save_to_file()
{
	fstream save("data.xdd", ios::out | ios::app);
	save << convert_for_save(m_make, m_model, m_body_type, m_fuel, m_transmission, m_engine_size, m_year, m_value);
	save << endl;
	save.close();
}


void Data::browsing()
{
	
	cout << "Model: " <<"\t\t\t"<< m_make << endl;
	cout << "Marka: " << "\t\t\t" << m_model << endl;
	cout << "Typ nadwodzia: " << "\t\t" << body_type(m_body_type)<< endl;
	cout << "Rodzaj skrzyni biegow: "<<"\t";
	if (m_transmission == 1)
		cout << "Manualna" << endl;
	else cout << "Automatyczna" << endl;
	cout << "Rodzaj paliwa: " << "\t\t"<< fuel(m_fuel) << endl;
	cout << "Pojemnosc silnika: " <<"\t"<< m_engine_size <<" cm^3"<< endl;
	cout << "Rok produkcji: " <<"\t\t"<< m_year <<" rok"<< endl;
	cout << "Wartosc: " << "\t\t" << m_value << " zl" << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "^-strzalka w gore = nastepny    v-strzalka w dol = poprzedni" << endl;
	cout << "ESC = wyjscie                   DELETE = usun wybrany element";
}



string Data::body_type(char nr)
{
	string one = "Hatchback";
	string two = "Sedan";
	string three = "Kombi";
	string four= "Kabriolet";
	string five = "Coupe";
	string six = "SUV";
	string seven = "Terenowy";
	if (nr == '1')
		return one;
	else if (nr == '2')
		return two;
	else if (nr == '3')
		return three;
	else if (nr == '4')
		return four;
	else if (nr == '5')
		return five;
	else if (nr == '6')
		return six;
	else if (nr == '7')
		return seven;
}

string Data::fuel(char nr)
{
	string one = "Benzyna";
	string two = "Diesel";
	string three = "LPG";
	string four = "Elektryczny";
	string five = "Hybryda";
	if (nr == '1')
		return one;
	else if (nr == '2')
		return two;
	else if (nr == '3')
		return three;
	else if (nr == '4')
		return four;
	else if (nr == '5')
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