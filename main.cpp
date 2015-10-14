#include <iostream>
#include <ctime>
#include "Salat.h"
using namespace std;

int main()
{
	string salatTimes[7] = {"","","","","","",""};;
	time_t t = time(0);  
	struct tm * now = localtime( & t );
    int year = now->tm_year + 1900;
    int month = now->tm_mon + 1;
    int day = now->tm_mday;
    cout << year << " - " << month << " - " << day << "\n";
    int calcMethod = 2;
    int asrMethod = 0;
    int highLatitude = 0;
    float latitude = 45.5454;
    float longitude = -73.6391;
    float timezone = -4;
    Salat salat;
    salat.setCalcMethod(calcMethod);
    salat.setAsrMethod(asrMethod);
    salat.setHighLatsMethod(highLatitude);
    salat.getDatePrayerTimes(year,month,day,latitude,longitude,timezone, salatTimes);

	for (int i = 0; i < 7; i++) 
    	cout << salatTimes[i] << "\n";

    return 0;
}
