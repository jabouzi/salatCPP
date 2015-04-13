/****************************************************************************
 ** Qsalat project V1.0
 ** Salat.cpp
 **
 ** Copyright (C) 2008 Skander Jabouzi (Skander Software Solutions).
 ** Contact: skander@skanderjabouzi.com or jabouzi@gmail.com
 **
 ** This file is part of the Qsalat open source software.
 **
 ** GNU General Public License Usage
 ** This file may be used under the terms of the GNU
 ** General Public License versions 2.0 or 3.0 as published by the Free
 ** Software Foundation and appearing in the file LICENSE.GPL included in
 ** the packaging of this file.  Please review the following information
 ** to ensure GNU General Public Licensing requirements will be met:
 ** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
 ** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
 ** exception, Nokia gives you certain additional rights. These rights
 ** are described in the Nokia Qt GPL Exception version 1.3, included in
 ** the file GPL_EXCEPTION.txt in this package.
 **
 ***************************************************************************/
#include "Salat.h"

Salat::Salat()
{
    //ui.setupUi(this);
    
    PI = 4.0*atan(1.0);
    // Calculation Methods
    Jafari     = 0;    // Ithna Ashari
    Karachi    = 1;    // University of Islamic Sciences, Karachi
    ISNA       = 2;    // Islamic Society of North America (ISNA)
    MWL        = 3;    // Muslim World League (MWL)
    Makkah     = 4;    // Umm al-Qura, Makkah
    Egypt      = 5;    // Egyptian General Authority of Survey
    Tehran     = 6;    // Institute of Geophysics, University of Tehran
    Custom     = 7;    // Custom Setting
    
    // Juristic Methods
    Shafii     = 0;    // Shafii (standard)
    Hanafi     = 1;    // Hanafi
    
    // Adjusting Methods for Higher Latitudes
    None       = 0;    // No adjustment
    MidNight   = 1;    // middle of night
    OneSeventh = 2;    // 1/7th of night
    AngleBased = 3;    // angle/60th of night
    
    
    // Time Formats
    Time24     = 0;    // 24-hour format
    Time12     = 1;    // 12-hour format
    Time12NS   = 2;    // 12-hour format with no suffix
    Float      = 3;    // floating point number
    
    // Time Names
    //timeNames = {'Fajr','Sunrise','Dhuhr','Asr','Sunset','Maghrib','Isha'};
    
    InvalidTime = "-----";     // The string used for invalid times
    
    
    //---------------------- Global Variables --------------------
    
    
    calcMethod   = 0;        // caculation method
    asrJuristic  = 0.0;        // Juristic method for Asr
    dhuhrMinutes = 0.0;        // minutes after mid-day for Dhuhr
    adjustHighLats = 0;    // adjusting method for higher latitudes
    
    timeFormat   = 0;        // time format
    
    
    //--------------------- Technical Settings --------------------
    
    
    numIterations = 1;        // number of iterations needed to compute times
    
    
    
    
    //------------------- Calc Method Parameters --------------------
    
    
    /*  methodParams[methodNum] = new Array(fa, ms, mv, is, iv);
     
     fa : fajr angle
     ms : maghrib selector (0 = angle; 1 = minutes after sunset)
     mv : maghrib parameter value (in angle or minutes)
     is : isha selector (0 = angle; 1 = minutes after maghrib)
     iv : isha parameter value (in angle or minutes)
     */
    methodParams[0][0] = 16.0;
    methodParams[0][1] = 0.0;
    methodParams[0][2] = 4.0;
    methodParams[0][3] = 0.0;
    methodParams[0][4] = 14.0;
    
    methodParams[1][0] = 18.0;
    methodParams[1][1] = 1.0;
    methodParams[1][2] = 0.0;
    methodParams[1][3] = 0.0;
    methodParams[1][4] = 18.0;
    
    methodParams[2][0] = 15.0;
    methodParams[2][1] = 1.0;
    methodParams[2][2] = 0.0;
    methodParams[2][3] = 0.0;
    methodParams[2][4] = 15.0;
    
    methodParams[3][0] = 18.0;
    methodParams[3][1] = 1.0;
    methodParams[3][2] = 0.0;
    methodParams[3][3] = 0.0;
    methodParams[3][4] = 17.0;
    
    methodParams[4][0] = 19.0;
    methodParams[4][1] = 1.0;
    methodParams[4][2] = 0.0;
    methodParams[4][3] = 1.0;
    methodParams[4][4] = 90.0;
    
    methodParams[5][0] = 19.5;
    methodParams[5][1] = 1.0;
    methodParams[5][2] = 0.0;
    methodParams[5][3] = 0.0;
    methodParams[5][4] = 17.5;
    
    methodParams[6][0] = 18.0;
    methodParams[6][1] = 1.0;
    methodParams[6][2] = 0.0;
    methodParams[6][3] = 0.0;
    methodParams[6][4] = 17.0;
    
    methodParams[7][0] = 17.7;
    methodParams[7][1] = 0.0;
    methodParams[7][2] = 4.5;
    methodParams[7][3] = 0.0;
    methodParams[7][4] = 15.0;
    times = new double[7];
    prayerTimes = new string[7];
}

Salat::~Salat()
{
	cout << "DELETING MEMORIES\n";
    delete[] times;
    delete[] prayerTimes;
}

// return prayer times for a given date
string* Salat::getDatePrayerTimes(int year, int month, int day, double latitude, double longitude, double timeZone)
{
    lat = latitude;
    lng = longitude;
    timezone = timeZone;
    //timeZone = effectiveTimeZone(year, month, day, timeZone);
    JDate = julianDate(year, month, day)- longitude/ (15* 24);
    computeDayTimes();

    return prayerTimes;
}

// set the calculation method
void Salat::setCalcMethod(int methodID)
{
    calcMethod = methodID;
}

// set the juristic method for Asr
void Salat::setAsrMethod(int methodID)
{
    if (methodID < 0 || methodID > 1)
        return;
    asrJuristic = methodID;
}

// set the minutes after mid-day for calculating Dhuhr
void Salat::setDhuhrMinutes(int minutes)
{
    dhuhrMinutes = minutes;
}

// set the minutes after Sunset for calculating Maghrib
void Salat::setMaghribMinutes(int minutes)
{
    double customParams[] = {NULL, 1, minutes, NULL, NULL};
}

// set the minutes after Maghrib for calculating Isha
void Salat::setIshaMinutes(int minutes)
{
    double customParams[] = {NULL, 1, minutes, NULL, NULL};
}

// set adjusting method for higher latitudes
void Salat::setHighLatsMethod(int methodID)
{
    adjustHighLats = methodID;
}

// set the time format
void Salat::setTimeFormat(int timeFormat)
{
    timeFormat = timeFormat;
}

// convert float hours to 24h format
string Salat::floatToTime24(double time)
{
    if (isNaN(time))
        return InvalidTime;
    else{
        time = fixhour(time + 0.5/ 60);  // add 0.5 minutes to round
        double hours = floor(time);
        double minutes = floor((time- hours)* 60);
        return twoDigitsFormat(hours)+':'+ twoDigitsFormat(minutes);
    }
}

// convert float hours to 12h format
string Salat::floatToTime12(double time)
{
    if (isNaN(time))
        return InvalidTime;
    else{
        time = fixhour(time+ 0.5/ 60);  // add 0.5 minutes to round
        int hours = ((int)time);
        int minutes = (((int)time- hours)* 60);
        string suffix = hours >= 12.0 ? " pm" : " am";
        hours = (hours + 12 - 1) % 12 + 1;
        return _2String(hours)+':'+ twoDigitsFormat(minutes)+ suffix;
    }
}


//---------------------- Calculation Functions -----------------------

// References:
// http://www.ummah.net/astronomy/saltime
// http://aa.usno.navy.mil/faq/docs/SunApprox.html


// compute declination angle of sun and equation of time
double Salat::sunPosition(double jd, int flag)
{
    double D = jd - 2451545.0;
    double g = fixangle(357.529 + 0.98560028* D);
    double q = fixangle(280.459 + 0.98564736* D);
    double L = fixangle(q + 1.915* dsin(g) + 0.020* dsin(2*g));
    //double R = 1.00014 - 0.01671* dcos(g) - 0.00014* dcos(2*g);
    double e = 23.439 - 0.00000036* D;
    double d = darcsin(dsin(e)* dsin(L));
    double RA = darctan2(dcos(e)* dsin(L), dcos(L))/ 15;
    RA = fixhour(RA);
    double EqT = q/15 - RA;
    //double * result = new double[2];
    if (flag == 0) return d;
    return EqT;
}

// compute equation of time
double Salat::equationOfTime(double jd)
{
    return sunPosition(jd, 1);
}

// compute declination angle of sun
double Salat::sunDeclination(double jd)
{
    return sunPosition(jd, 0);
}

// compute mid-day (Dhuhr, Zawal) time
double Salat::computeMidDay(double t)
{
    double T = equationOfTime(JDate + t);
    double Z = fixhour(12 - T);
    return Z;
}

// compute time for a given angle G
double Salat::computeTime(double G, double t)
{
    double D = sunDeclination(JDate + t);
    double Z = computeMidDay(t);
    double V = 1.0/15.0* darccos((-dsin(G)- dsin(D)* dsin(lat)) / (dcos(D)* dcos(lat)));
    return Z + (G > 90.0 ? -V : V);
}

// compute the time of Asr
double Salat::computeAsr(int step, double t)  // Shafii: step=1, Hanafi: step=2
{
    double D = sunDeclination(JDate+ t);
    double G = -darccot(step+ dtan(abs(lat-D)));
    return computeTime(G, t);
}


//---------------------- Compute Prayer Times -----------------------


// compute prayer times at given julian date
void Salat::computeTimes()
{
    dayPortion();
    double Fajr    = computeTime(180.0 - methodParams[calcMethod][0], times[0]);
    double Sunrise = computeTime(180.0 - 0.833, times[1]);
    double Dhuhr   = computeMidDay(times[2]);
    double Asr     = computeAsr(1.0 + asrJuristic, times[3]);
    double Sunset  = computeTime(0.833, times[4]);;
    double Maghrib = computeTime(methodParams[calcMethod][2], times[5]);
    double Isha    = computeTime(methodParams[calcMethod][4], times[6]);
    times[0] = Fajr;
    times[1] = Sunrise;
    times[2] = Dhuhr;
    times[3] = Asr;
    times[4] = Sunset;
    times[5] = Maghrib;
    times[6] = Isha;
}


// compute prayer times at given julian date
void Salat::computeDayTimes()
{
    times[0] = 5.0;
    times[1] = 6.0;
    times[2] = 12.0;
    times[3] = 13.0;
    times[4] = 18.0;
    times[5] = 18.0;
    times[6] = 18.0; //default times

    for (int i=1; i<=numIterations; i++)
        computeTimes();
    adjustTimes();
    adjustTimesFormat();
}


// adjust times in a prayer time array
void Salat::adjustTimes()
{
    for (int i=0; i<7; i++)
        times[i] += timezone - lng/15.0;
    times[2] += dhuhrMinutes/ 60.0; //Dhuhr
    if (methodParams[calcMethod][1] == 1) // Maghrib
        times[5] = times[4]+ methodParams[calcMethod][2]/ 60.0;
    if (methodParams[calcMethod][3] == 1) // Isha
        times[6] = times[5]+ methodParams[calcMethod][4]/ 60.0;
    
    if (adjustHighLats != None)
        adjustHighLatTimes();
}


// convert times array to given time format
void Salat::adjustTimesFormat()
{
    for (int i=0; i<7; i++)
        if (timeFormat == Time12)
            prayerTimes[i] = floatToTime12(times[i]);
    /*else if (timeFormat == Time12NS)
     timesF[i] = floatToTime12(times[i], true);*/
        else
            prayerTimes[i] = floatToTime24(times[i]);
}


// adjust Fajr, Isha and Maghrib for locations in higher latitudes
void Salat::adjustHighLatTimes()
{
    double nightTime = timeDiff(times[4], times[1]); // sunset to sunrise
    
    // Adjust Fajr
    double FajrDiff = nightPortion(methodParams[calcMethod][0])* nightTime;
    if (isNaN(times[0]) || timeDiff(times[0], times[1]) > FajrDiff)
        times[0] = times[1]- FajrDiff;
    
    // Adjust Isha
    double IshaAngle = (methodParams[calcMethod][3] == 0) ? methodParams[calcMethod][4] : 18;
    double IshaDiff = nightPortion(IshaAngle)* nightTime;
    if (isNaN(times[6]) || timeDiff(times[4], times[6]) > IshaDiff)
        times[6] = times[4]+ IshaDiff;
    
    // Adjust Maghrib
    double MaghribAngle = (methodParams[calcMethod][1] == 0) ? methodParams[calcMethod][2] : 4;
    double MaghribDiff = nightPortion(MaghribAngle)* nightTime;
    if (isNaN(times[5]) || timeDiff(times[4], times[5]) > MaghribDiff)
        times[5] = times[4]+ MaghribDiff;
}


// the night portion used for adjusting times in higher latitudes
double Salat::nightPortion(double angle)
{
    double result = 0.0;
    if (adjustHighLats == AngleBased)
        result = 1.0/60.0* angle;
    if (adjustHighLats == MidNight)
        result = 1.0/2.0;
    if (adjustHighLats == OneSeventh)
        result = 1.0/7.0;
    return result;
}


// convert hours to day portions
void Salat::dayPortion()
{
    for (int i=0; i<7; i++)
        times[i] /= 24;
    //return times;
}



//---------------------- Misc Functions -----------------------


// compute the difference between two times
double Salat::timeDiff(double time1, double time2)
{
    return fixhour(time2- time1);
}


// add a leading 0 if necessary
string Salat::twoDigitsFormat(int num)
{
    return (num <10) ? '0'+ _2String(num) : _2String(num);
}

bool Salat::isNaN(double var)
{
    return (isnan(var) != 0);
}


//---------------------- Julian Date Functions -----------------------


// calculate julian date from a calendar date
double Salat::julianDate(int year, int month, int day)
{
    if (month <= 2)
    {
        year -= 1;
        month += 12;
    }
    double A = floor(year/ 100.0);
    double B = 2.0 - A+ floor(A/ 4.0);
    
    double JD = floor(365.25* (year+ 4716))+ floor(30.6001* (month+ 1))+ day+ B- 1524.5;
    return JD;
}

//---------------------- Time-Zone Functions -----------------------


// compute local time-zone for a specific date
/*void Salat::getTimeZone(date)
 {
 double localDate = new Date(date.getFullYear(), date.getMonth(), date.getDate(), 0, 0, 0, 0);
 double GMTstring = localDate.toGMTstring();
 double GMTDate = new Date(GMTstring.substring(0, GMTstring.lastIndexOf(' ')- 1));
 double hoursDiff = (localDate- GMTDate) / (1000* 60* 60);
 return hoursDiff;
 }*/


// compute base time-zone of the system
/*void Salat::getBaseTimeZone()
 {
 return getTimeZone(new Date(2000, 0, 15))
 }*/


// detect daylight saving in a given date
/*void Salat::detectDaylightSaving(date)
 {
 return getTimeZone(date) != getBaseTimeZone();
 }*/


// return effective timezone for a given date
//double Salat::effectiveTimeZone(int year, int month, int day, int timeZone)
//{
//    if (timeZone == NULL || typeof(timeZone) == 'undefined' || timeZone == 'auto')
//        timeZone = getTimeZone(new Date(year, month- 1, day));
//    return 1* timeZone;
//}


//---------------------- Trigonometric Functions -----------------------

// degree sin
double Salat::dsin(double d)
{
    return sin(dtr(d));
}

// degree cos
double Salat::dcos(double d)
{
    return cos(dtr(d));
}

// degree tan
double Salat::dtan(double d)
{
    return tan(dtr(d));
}

// degree arcsin
double Salat::darcsin(double x)
{
    return rtd(asin(x));
}

// degree arccos
double Salat::darccos(double x)
{
    return rtd(acos(x));
}

// degree arctan
double Salat::darctan(double x)
{
    return rtd(atan(x));
}

// degree arctan2
double Salat::darctan2(double y, double x)
{
    return rtd(atan2(y, x));
}

// degree arccot
double Salat::darccot(double x)
{
    return rtd(atan(1/x));
}

// degree to radian
double Salat::dtr(double d)
{
    return (d * PI) / 180.0;
}

// radian to degree
double Salat::rtd(double r)
{
    return (r * 180.0) / PI;
}

// range reduce angle in degrees.
double Salat::fixangle(double a)
{
    a = a - 360.0 * (floor(a / 360.0));
    a = a < 0 ? a + 360.0 : a;
    return a;
}

// range reduce hours to 0..23
double Salat::fixhour(double a)
{
    a = a - 24.0 * (floor(a / 24.0));
    a = a < 0 ? a + 24.0 : a;
    return a;
}

string Salat::_2String(double number)
{
	std::ostringstream ostr;
    ostr << number;
    return ostr.str();
}

string Salat::_2String(int number)
{
	std::ostringstream ostr;
    ostr << number;
    return ostr.str();
}

void Salat::debug(string* array)
{
	int numElements = sizeof(array)/sizeof(array[0]);
	for (int i = 0; i < numElements; i++) 
    	cout << array[i];
}
void Salat::debug(int* array)
{
	int numElements = sizeof(array)/sizeof(array[0]);
	for (int i = 0; i < numElements; i++) 
    	cout << array[i];
}
