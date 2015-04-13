/****************************************************************************
 ** Qsalat project V1.0
 ** Salat.h
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

#ifndef Salat_H
#define Salat_H

#include <string>
#include <ctime>
#include <cmath>
#include <typeinfo>
#include <iostream>
#include <sstream>

using namespace std;

class Salat
{
    
public:
    Salat();
    ~Salat();
    
    string* getDatePrayerTimes(int, int , int , double , double , double);
    
    
    // set the calculation method
    void setCalcMethod(int);
    
    // set the juristic method for Asr
    void setAsrMethod(int);
    
    
    // set the angle for calculating Fajr
    void setFajrAngle(double);
    
    
    // set the angle for calculating Maghrib
    void setMaghribAngle(double);
    
    // set the angle for calculating Isha
    void setIshaAngle(double);
    
    
    // set the minutes after mid-day for calculating Dhuhr
    void setDhuhrMinutes(int);
    
    
    // set the minutes after Sunset for calculating Maghrib
    void setMaghribMinutes(int);
    
    
    // set the minutes after Maghrib for calculating Isha
    void setIshaMinutes(int);
    
    
    // set custom values for calculation parameters
    void setCustomParams(double*);
    
    
    // set adjusting method for higher latitudes
    void setHighLatsMethod(int);
    
    
    // set the time format
    void setTimeFormat(int);
    
    
    // convert float hours to 24h format
    string floatToTime24(double);
    
    
    // convert float hours to 12h format
    string floatToTime12(double);
    
    
    
    //---------------------- Calculation Functions -----------------------
    
    // References:
    // http://www.ummah.net/astronomy/saltime
    // http://aa.usno.navy.mil/faq/docs/SunApprox.html
    
    
    // compute declination angle of sun and equation of time
    double sunPosition(double, int flag);
    
    
    // compute equation of time
    double equationOfTime(double);
    
    
    // compute declination angle of sun
    double sunDeclination(double);
    
    
    // compute mid-day (Dhuhr, Zawal) time
    double computeMidDay(double);
    
    
    // compute time for a given angle G
    double computeTime(double, double);
    
    
    // compute the time of Asr
    double computeAsr(int, double);  // Shafii: step=1, Hanafi: step=2
    
    
    
    //---------------------- Compute Prayer Times -----------------------
    
    
    // compute prayer times at given julian date
    void computeTimes();
    
    
    // compute prayer times at given julian date
    void computeDayTimes();
    
    
    
    // adjust times in a prayer time array
    void adjustTimes();
    
    
    
    // convert times array to given time format
    void adjustTimesFormat();
    
    
    
    // adjust Fajr, Isha and Maghrib for locations in higher latitudes
    void adjustHighLatTimes();
    
    
    
    // the night portion used for adjusting times in higher latitudes
    double nightPortion(double);
    
    
    
    // convert hours to day portions
    void dayPortion();
    
    
    
    
    //---------------------- Misc Functions -----------------------
    
    
    // compute the difference between two times
    double timeDiff(double, double);
    
    
    
    // add a leading 0 if necessary
    string twoDigitsFormat(int);
    
    
    //bool isNaN(int);
    
    
    //bool isNaN(float);
    
    
    bool isNaN(double);
    
    //---------------------- Julian Date Functions -----------------------
    
    
    // calculate julian date from a calendar date
    double julianDate(int, int, int);
    
    
    //---------------------- Time-Zone Functions -----------------------
    
    
    // compute local time-zone for a specific date
    /*void getTimeZone(QDate date);
     
     
     
     // compute base time-zone of the system
     void getBaseTimeZone();
     
     
     
     // detect daylight saving in a given date
     void detectDaylightSaving(QDate date);*/
    
    
    
    // return effective timezone for a given date
    //void effectiveTimeZone(int year, int month, int day, int timeZone);
    
    
    
    //---------------------- Trigonometric Functions -----------------------
    
    // degree sin
    double dsin(double);
    
    
    // degree cos
    double dcos(double);
    
    
    // degree tan
    double dtan(double);
    
    
    // degree arcsin
    double darcsin(double);
    
    
    // degree arccos
    double darccos(double);
    
    
    // degree arctan
    double darctan(double);
    
    
    // degree arctan2
    double darctan2(double, double);
    
    
    // degree arccot
    double darccot(double);
    
    
    // degree to radian
    double dtr(double);
    
    
    // radian to degree
    double rtd(double);
    
    
    // range reduce angle in degrees.
    double fixangle(double);
    
    
    // range reduce hours to 0..23
    double fixhour(double);
    
    
private:
    //Ui::SalatClass ui;
    // Calculation Methods
    double * times;
    string* prayerTimes;
    double PI;
    
    int Jafari;    // Ithna Ashari
    int Karachi;    // University of Islamic Sciences, Karachi
    int ISNA;    // Islamic Society of North America (ISNA)
    int MWL;    // Muslim World League (MWL)
    int Makkah;    // Umm al-Qura, Makkah
    int Egypt;    // Egyptian General Authority of Survey
    int Tehran;    // Institute of Geophysics, University of Tehran
    int Custom;    // Custom Setting
    
    // Juristic Methods
    int Shafii;    // Shafii (standard)
    int Hanafi;    // Hanafi
    
    // Adjusting Methods for Higher Latitudes
    int None;    // No adjustment
    int MidNight;    // middle of night
    int OneSeventh;    // 1/7th of night
    int AngleBased;    // angle/60th of night
    
    
    // Time Formats
    int Time24;    // 24-hour format
    int Time12;    // 12-hour format
    int Time12NS;    // 12-hour format with no suffix
    int Float;    // floating point number
    
    // Time Names
    //string timeNames[7];
    
    string InvalidTime;	 // The string used for invalid times
    
    
    //---------------------- Global Variables --------------------
    
    
    int calcMethod;		// caculation method
    double asrJuristic;		// Juristic method for Asr
    double dhuhrMinutes;		// minutes after mid-day for Dhuhr
    int adjustHighLats;	// adjusting method for higher latitudes
    
    int timeFormat;		// time format
    
    double lat;        // latitude
    double lng;        // longitude
    double timezone;   // time-zone
    double JDate;      // Julian date
    
    
    //--------------------- Technical Settings --------------------
    
    
    int numIterations;		// number of iterations needed to compute times
    
    
    
    
    //------------------- Calc Method Parameters --------------------
    
    double methodParams[8][5];
    
    
    /*  methodParams[methodNum] = new Array(fa, ms, mv, is, iv);
     
     fa : fajr angle
     ms : maghrib selector (0 = angle; 1 = minutes after sunset)
     mv : maghrib parameter value (in angle or minutes)
     is : isha selector (0 = angle; 1 = minutes after maghrib)
     iv : isha parameter value (in angle or minutes)
    	*/
    	
    string _2String(double);
    string _2String(int);
    	
    void debug(string*);
    void debug(int*);
    
    
};

#endif // Salat_H
