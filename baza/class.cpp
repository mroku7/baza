#include "stdafx.h"
#include "class.h"


Data::Data(bool init)
{
	
	cout << "Podaj marke samochodu: ";
	cin >> m_make;
}
Data::Data() 
{
	fstream load;
}

void Data::show()
{
	cout <<  m_make;
}