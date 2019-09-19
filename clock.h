#pragma once
#ifndef CLOCK_H_
#define CLOCK_H_
#include <virtuabotixRTC.h>
#include <TM1637.h>
class Clock
{
private:
	TM1637* tm1637;
	bool key;
	char Mode;
	virtuabotixRTC* RTC;
	void showyear();
	void showmonth();
	void showsecond();
	void showtime24();
	void showtime12();
public:
	Clock(int CLK,int DIO, virtuabotixRTC* RTC, char Time_Mode='t');
	void init();
	void start();
	void set(int Brightness);
};
Clock::Clock(int CLK, int DIO, virtuabotixRTC* rtc, char Time_Mode)
{
	tm1637 = new TM1637(CLK, DIO);
	RTC = rtc;
	Mode = Time_Mode;
	key = true;
}
void Clock::init()
{
	tm1637->init();
}
void Clock::start()
{
	RTC->updateTime();
	if (Serial.available() > 0)
	{
		char order = Serial.read();
		switch (order)
		{
		case 'Y':
			showyear();
			break;
		case 'M':
			showmonth();
			break;
		case 'T':
			showtime24();
			Mode = 'T';
			break;
		case 't':
			showtime12();
			Mode = 't';
			break;
		case 'S':
			showsecond();
			Mode = 'S';
			break;
		default:
			if (Mode == 'S')
				showsecond();
			else if (Mode == 'T')
				showtime24();
			else
				showtime12();
		}
	}
	else
	{
		if (Mode == 'S')
			showsecond();
		else if (Mode == 'T')
			showtime24();
		else
			showtime12();
	}
}
void Clock::set(int Brightness)
{
	tm1637->set(Brightness);
}
void Clock::showyear()
{
	tm1637->point(0);
	tm1637->display(0, RTC->year / 1000);
	tm1637->display(1, (RTC->year / 100) % 10);
	tm1637->display(2, (RTC->year / 10) % 10);
	tm1637->display(3, RTC->year % 10);
	delay(2000);
}
void Clock::showmonth()
{
	tm1637->point(0);
	tm1637->display(0, RTC->month / 10);
	tm1637->display(1, RTC->month % 10);
	tm1637->display(2, RTC->dayofmonth / 10);
	tm1637->display(3, RTC->dayofmonth % 10);
	delay(2000);
}
void Clock::showsecond()
{
	tm1637->display(0, RTC->minutes / 10);
	tm1637->display(1, RTC->minutes % 10);
	tm1637->display(2, RTC->seconds / 10);
	tm1637->display(3, RTC->seconds % 10);
	if (key == true)
	{
		tm1637->point(1);
		key = false;
	}
	else
	{
		tm1637->point(0);
		key = true;
	}
	delay(1000);
}
void Clock::showtime12()
{
	int hours;
	if (RTC->hours > 12)
		hours = RTC->hours % 12;
	else
		hours = RTC->hours;
	tm1637->display(0, hours / 10);
	tm1637->display(1, hours % 10);
	tm1637->display(2, RTC->minutes / 10);
	tm1637->display(3, RTC->minutes % 10);
	if (key == true)
	{
		tm1637->point(1);
		key = false;
	}
	else
	{
		tm1637->point(0);
		key = true;
	}
	delay(1000);
}
void Clock::showtime24()
{
	tm1637->display(0, RTC->hours / 10);
	tm1637->display(1, RTC->hours % 10);
	tm1637->display(2, RTC->minutes / 10);
	tm1637->display(3, RTC->minutes % 10);
	if (key == true)
	{
		tm1637->point(1);
		key = false;
	}
	else
	{
		tm1637->point(0);
		key = true;
	}
	delay(1000);
}
#endif