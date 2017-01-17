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
	int m_body_type;
	int m_fuel;
	int m_transmission;
	int m_engine_size;
	int m_year;
	int m_value;
	string convert_for_save(string, string, int, int, int, int, int, int);
	string replacing_space(string&);
	string fuel(int);

public:
	Data();
	Data(string, string, int, int, int, int, int, int);
	void save_to_file(string);
	void browsing();
	void browsing_wfilter();
	string body_type(int);
	string get_make();
	string get_model();
	int get_body();
	int get_fuel();
	int get_transmission();
	int get_engine();
	int get_year();
	int get_value();
	void set_make(string);
	void set_model(string);
	void set_body_type(int);
	void set_fuel(int);
	void set_transmission(int);
	void set_engine_size(int);
	void set_year(int);
	void set_value(int);
	friend bool compare_by_year(const Data &, const Data &);
	friend bool compare_by_value(const Data &, const Data &);
	friend bool compare_by_eng(const Data &, const Data &);
	friend bool compare_by_make(const Data &, const Data &);
	friend bool compare_by_model(const Data &, const Data &);
};
