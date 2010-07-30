/*
 * This file is part of Epoch, a timeline program
 *
 * Copyright (C) 2008-2010 Nikola Knezevic <nkcodeplus@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#ifndef NKJD_H
#define NKJD_H
//use JD to store date in your object, and NKJD for transformations
typedef double JD;
#include <QString>
#include <cmath>
class NKJD {
private:
	double m_jdate; //Julian dates (abbreviated JD)
	int m_day;
	int m_month;
	int m_year;
	short m_ihour;
	short m_iminute;
	double m_second;
	short m_weekday; //0-6  0= mon
public:
	NKJD(double datum = 0) {
		m_jdate = datum;
		jdo_gregorian();
	}
	double GetJD() {
		return m_jdate;
	}
	;
	int GetGregDay() {
		return m_day;
	}
	;
	int GetGregMonth() {
		return m_month;
	}
	;
	int GetGregYear() {
		return m_year;
	}
	;
	short GetMin() {
		return m_iminute;
	}
	;
	short GetHour() {
		return m_ihour;
	}
	;
	double GetSec() {
		return m_second;
	}
	;
	short GetWeekDay() {
		return m_weekday;
	}
	;
	int GetWeekDaySt() {
		return m_weekday;
	}
	void SetJD(double datum) {
		m_jdate = datum;
		jdo_gregorian();
	}
	int SetShortDate(int day, int month, int year) {
		m_day = day;
		m_month = month;
		m_year = year;
		m_ihour = 0;
		m_iminute = 0;
		m_second = 0;
		m_weekday = 0;
		return gregoriano_jd();
	}
	int SetLongDate(int day, int month, int year, short hour, short minute) {
		m_day = day;
		m_month = month;
		m_year = year;
		m_ihour = hour;
		m_iminute = minute;
		m_second = 0;
		m_weekday = 0;
		return gregoriano_jd();
	}
	int SetTime(short hour, short minute, double second) {
		m_ihour = hour;
		m_iminute = minute;
		m_second = second;
		m_weekday = 0;
		return gregoriano_jd();
	}
	void AddMin(double min) {
		double dan = min / 1440.0;
		m_jdate += dan;
		//m_second=0;
		jdo_gregorian();
	}
	void SubMin(double min) {
		double dan = min / 1440.0;
		m_jdate -= dan;
		//m_second=0;
		jdo_gregorian();
	}
	void AddHour(double min) {
		double dan = min / 24;
		m_jdate += dan;
		//m_second=0;
		jdo_gregorian();
	}
	void SubHour(double min) {
		double dan = min / 24;
		m_jdate -= dan;
		//m_second=0;
		jdo_gregorian();
	}
	void AddYear(long y) {
		m_year += y;
		gregoriano_jd();
	}
	void SubYear(long y) {
		m_year -= y;
		gregoriano_jd();
	}
	void AddDay(double dan) {
		m_jdate += dan;
		jdo_gregorian();
	}
	void SubDay(double dan) {
		m_jdate -= dan;
		jdo_gregorian();
	}
	double RoundDifferInDay(NKJD drugi) {
		return (floor(m_jdate) - floor(drugi.GetJD()));
	}
private:

	int gregoriano_jd() {
		QString era;
		int godina = m_year;

		if (godina < 0) {
			godina = -godina;
			era = "BCE";
		} else {
			era = "CE";
		}
		return calo_jd(era, godina, m_month, m_day, m_ihour, m_iminute,
				m_second);

	}
	void jdo_gregorian() {
		double jd = m_jdate;
		double j1, j2, j3, j4, j5;
		double intgr = floor(jd);
		double frac = jd - intgr;
		double gregjd = 2299161;
		if (intgr >= gregjd) { //Gregorian calendar correction
			double tmp = floor(((intgr - 1867216.0) - 0.25) / 36524.25);
			j1 = intgr + 1 + tmp - floor(0.25 * tmp);
		} else
			j1 = intgr;

		//correction for half day offset
		double df = frac + 0.5;
		if (df >= 1.0) {
			df -= 1.0;
			++j1;
		}

		j2 = j1 + 1524.0;
		j3 = floor(6680.0 + ((j2 - 2439870.0) - 122.1) / 365.25);
		j4 = floor(j3 * 365.25);
		j5 = floor((j2 - j4) / 30.6001);

		double d = floor(j2 - j4 - floor(j5 * 30.6001));
		double m = floor(j5 - 1.0);
		if (m > 12)
			m -= 12;
		double y = floor(j3 - 4715.0);
		if (m > 2)
			--y;
		if (y <= 0)
			--y;

		double hr = floor(df * 24.0);
		double mn = floor((df * 24.0 - hr) * 60.0);
		double f = ((df * 24.0 - hr) * 60.0 - mn) * 60.0;
		double sc = floor(f);
		f -= sc;
		if (f > 0.5)
			++sc;
		if (sc == 60) {
			sc = 0;
			++mn;
		}
		if (mn == 60) {
			mn = 0;
			++hr;
		}
		if (hr == 24) {
			hr = 0;
			++d;
		}

		m_day = (int) d;
		m_month = (int) m;
		m_year = (int) y;
		m_ihour = (short) hr;
		m_iminute = (short) mn;
		m_second = sc;
		double t = m_jdate + 0.5;
		m_weekday = (short) floor((t / 7.0 - floor(t / 7.0)) * 7.0
				+ 0.000000000317);

	}
public:
	bool isti(NKJD pp) {
		if (m_jdate == pp.GetJD()) {
			return true;
		} else {
			return false;
		}
	}
	bool razliciti(NKJD pp) {
		if (m_jdate != pp.GetJD()) {
			return true;
		} else {
			return false;
		}
	}
	bool Vece(NKJD pp) {
		if (m_jdate > pp.GetJD()) {
			return true;
		} else {
			return false;
		}
	}
	bool Manje(NKJD pp) {
		if (m_jdate < pp.GetJD()) {
			return true;
		} else {
			return false;
		}
	}
	bool VeceE(NKJD pp) {
		if (m_jdate >= pp.GetJD()) {
			return true;
		} else {
			return false;
		}
	}
	bool ManjeE(NKJD pp) {
		if (m_jdate <= pp.GetJD()) {
			return true;
		} else {
			return false;
		}
	}

	double RoundDifferInMin(NKJD drugi) {
		return ceil((m_jdate - drugi.GetJD()) * 1440);
	}

	int calo_jd(QString era, int y, int m, int d, int h, int mn, double s) {
		double jy, ja, jm;
		if (y == 0) {
			//("There is no year 0 in the Julian system!");
			return 1;
		}
		if (y == 1582 && m == 10 && d > 4 && d < 15 && era == "CE") {
			//("The dates 5 through 14 October, 1582, do not exist in the Gregorian system!");
			return 2;
		}
		//			if( y < 0 )  ++y;
		if (era == "BCE")
			y = -y + 1;
		if (m > 2) {
			jy = y;
			jm = m + 1;
		} else {
			jy = y - 1;
			jm = m + 13;
		}
		double intgr = floor(floor(365.25 * jy) + floor(30.6001 * jm) + d
				+ 1720995);
		//check for switch to Gregorian calendar
		double gregcal = 15 + 31 * (10 + 12 * 1582);
		if (d + 31 * (m + 12 * y) >= gregcal) {
			ja = floor(0.01 * jy);
			intgr += 2 - ja + floor(0.25 * ja);
		}
		//correct for half-day offset
		double dayfrac = h / 24.0 - 0.5;
		if (dayfrac < 0.0) {
			dayfrac += 1.0;
			--intgr;
		}
		//now set the fraction of a day
		double frac = dayfrac + (mn + s / 60.0) / 60.0 / 24.0;
		//round to nearest second
		double jd0 = ((intgr + frac) * 100000);
		double jd = floor(jd0);
		if (jd0 - jd > 0.5)
			++jd;
		m_jdate = jd / 100000.0;
		double t = m_jdate + 0.5;
		m_weekday = (short) floor((t / 7 - floor(t / 7)) * 7 + 0.000000000317); //add 0.01 sec for truncation error correction
		return 0;
	}
	//////////////////
	bool ParsDatum(QString g, NKJD &rez) {

		g = (" ") + g;
		QString deo = ("");
		int red = 0;
		QString dan, mesec, god;
		for (int i = 1; i <= g.length(); i++) {
			if ((g[i]).isDigit()) {
				deo = deo + g[i];
			} else {
				if (g[i] == '-') {
					deo = deo + g[i];
					goto endelse;
				}
				if (red == 0) {
					dan = deo;
					deo = ("");
					red++;
					goto endelse;
				}
				if (red == 1) {
					mesec = deo;
					deo = ("");
					red++;
				}
				endelse: ;
			}

		}
		god = deo;
		rez.SetLongDate((dan).toInt(), (mesec).toInt(), (god).toInt(),
				rez.GetHour(), rez.GetMin());
		if ((dan).toInt() < 1 || (dan).toInt() > 31) {
			return false;
		}
		if ((mesec).toInt() < 1 || (mesec).toInt() > 12) {
			return false;
		}
		return true;
	}
	bool ParsTime(QString g, NKJD &rez) {

		g = (" ") + g + (".");
		QString deo = ("");
		int red = 0;
		QString sat, min;
		for (int i = 1; i <= g.length(); i++) {
			if ((g[i]).isDigit()) {
				deo = deo + g[i];
			} else {
				if (red == 0) {
					sat = deo;
					deo = ("");
					red++;
					goto endelse;
				}
				if (red == 1) {
					min = deo;
					deo = ("");
					red++;
				}
				endelse: ;
			}

		}
		QString hh;

		if ((sat).toInt() < 0 || (sat).toInt() > 24) {
			return false;
		}
		if ((min).toInt() < 0 || (min).toInt() > 60) {
			return false;
		}
		NKJD vreme;

		vreme.SetLongDate(rez.GetGregDay(), rez.GetGregMonth(),
				rez.GetGregYear(), (sat).toInt(), (min).toInt());
		rez = vreme;
		return true;
	}
	QString getString(NKJD temp) {
		QString dd = QString("%1.%2.%3").arg(abs(temp.GetGregDay())).arg(abs(
				temp.GetGregMonth())).arg(temp.GetGregYear());
		return dd;
	}
};
#endif
