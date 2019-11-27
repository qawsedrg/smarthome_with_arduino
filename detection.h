#pragma once
#ifndef DETECTION_H_
#define DETECTION_H_
class Sonor_Detecteur
{
private:
	int TrigPin;
	int EchoPin;
public:
	Sonor_Detecteur(int t=2, int e=3);
	void Setup();
	bool detected();
};
Sonor_Detecteur::Sonor_Detecteur(int t, int e)
{
	TrigPin = t;
	EchoPin = e;
}
void Sonor_Detecteur::Setup()
{
	pinMode(TrigPin, OUTPUT);
	pinMode(EchoPin, INPUT);
}
bool Sonor_Detecteur::detected()
{
	digitalWrite(TrigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(TrigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(TrigPin, LOW);
	float distance = pulseIn(EchoPin, HIGH) / 58;
	if (distance >= 1000 || distance < 20) {
		//Serial.println(distance);
		return true;
	}
	else return false;
}
#endif