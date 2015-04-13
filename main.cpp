#include <iostream>
#include "Salat.h"
using namespace std;

int main()
{
	string *salatTimes = new string[7];
    int year = 2015;
    int month = 4;
    int day = 10;
    int calcMethod = 2;
    int asrMethod = 0;
    int highLatitude = 0;
    float latitude = 45.5454;
    float longitude = -73.6391;
    float timezone = -4;
    Salat *salat = new Salat();
    salat->setCalcMethod(calcMethod);
    salat->setAsrMethod(asrMethod);
    salat->setHighLatsMethod(highLatitude);
    salatTimes = salat->getDatePrayerTimes(year,month,day,latitude,longitude,timezone);

	int numElements = sizeof(salatTimes)/sizeof(salatTimes[0]);
	for (int i = 0; i < 7; i++) 
    	cout << salatTimes[i] << "\n";
    delete[] salatTimes;
    delete salat;
    return 0;
}
