#pragma once
#include "stdafx.h"
#include "class.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Data {
private:

	string m_make;
	string m_model;
	char m_body_type;
	char m_fuel;
	char m_transmission;
	int m_engine_size;
	int m_year;
	int m_value;
	string convert_for_save(string, string, char, char, char, int, int, int);
	string replacing_space(string&);
	string body_type(char);
	string fuel(char);

public:
	Data();
	Data(string, string, char, char, char, int, int, int);
	void save_to_file();
	void browsing();
	friend bool compare_by_year(const Data &, const Data &);
	friend bool compare_by_value(const Data &, const Data &);
	friend bool compare_by_eng(const Data &, const Data &);
	friend bool compare_by_make(const Data &, const Data &);
};
