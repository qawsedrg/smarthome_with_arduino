#pragma once
#ifndef ALARM_H_
#define ALARM_H_
#include <virtuabotixRTC.h>
class Alarm
{
private:
	int** alarms;
	int num;
	virtuabotixRTC* RTC;
public:
	Alarm(virtuabotixRTC* rtc,int n);
	void input();
	bool istime()const;
	void print()const;
	void add(int hour, int minute);
};
Alarm::Alarm(virtuabotixRTC* rtc,int n)
{
	RTC =rtc;
	num = 0;
	alarms = new int* [3];
	for (int i = 0; i < 2; ++i)
	{
		alarms[i] = new int[n+1];
	}
}
void Alarm::input()
{
	char hour[2];
	char minute[2];
	if (Serial.available() > 0)
	{
		Serial.readBytes(hour, 2);
		Serial.readBytes(minute, 2);
	}
	add((int)hour, (int)minute);
}
void Alarm::add(int hour, int minute)
{
	if (num > 4)
	{
		Serial.print("Alarms number out of range.");
		return;
	}
	for (int i = 0; i < 2; ++i)
	{
		switch (i) {
		case 0:
			alarms[0][num] = hour;
			break;
		case 1:
			alarms[1][num] = minute;
			break;
		}
	}
	++num;
}
bool Alarm::istime() const
{
	RTC->updateTime();
	for (int i = 0; i < num; ++i)
	{
		if (RTC->minutes == alarms[1][i]&& RTC->hours == alarms[0][i])
		{
			return true;
		}
	}
	return false;
}
void Alarm::print()const
{
	RTC->updateTime();
	Serial.print(RTC->dayofmonth);
	Serial.print("/");
	Serial.print(RTC->month);
	Serial.print("/");
	Serial.print(RTC->year);
	Serial.print(RTC->hours);
	Serial.print(":");
	Serial.print(RTC->minutes);
	Serial.print(":");
	Serial.println(RTC->seconds);
	delay(1000);
}
#endif