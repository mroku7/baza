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
	string m_body_type;
	string m_fuel;
	string m_transmission;
	int m_engine_size;
	int m_year;

public:
	Data(bool);
	Data();
	void show();

};