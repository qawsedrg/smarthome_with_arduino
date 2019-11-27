#pragma once
#ifndef FINGER_H_
#define FINGER_H_
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
class Finger
{
private:
	Adafruit_Fingerprint* finger;
	uint8_t getimage();
	uint8_t convertimage(int i);
	uint8_t convertimage();
	uint8_t creat_and_store(int id);
	uint8_t enroll(int id);
	uint8_t search();
	uint8_t verify();
	const int try_time = 3;
public:
	Finger(SoftwareSerial *mySerial);
	void enrollment();
	bool authoritized(int seuil);
	void setup();
};
uint8_t Finger::getimage()
{
	int p = -1;
	while (p != FINGERPRINT_OK) {
		p = finger->getImage();
		switch (p) {
		case FINGERPRINT_OK:
			Serial.println("Image taken");
			return p;
		case FINGERPRINT_NOFINGER:
			return p;
		case FINGERPRINT_PACKETRECIEVEERR:
			Serial.println("Communication error");
			return p;
		case FINGERPRINT_IMAGEFAIL:
			Serial.println("Imaging error");
			return p;
		default:
			Serial.println("Unknown error");
			return p;
		}
	}
}
uint8_t Finger::convertimage(int i)
 {
	int p = finger->image2Tz(i);
	switch (p) {
	case FINGERPRINT_OK:
		Serial.println("Image converted");
		return p;
	case FINGERPRINT_IMAGEMESS:
		Serial.println("Image too messy");
		return p;
	case FINGERPRINT_PACKETRECIEVEERR:
		Serial.println("Communication error");
		return p;
	case FINGERPRINT_FEATUREFAIL:
		Serial.println("Could not find fingerprint features");
		return p;
	case FINGERPRINT_INVALIDIMAGE:
		Serial.println("Could not find fingerprint features");
		return p;
	default:
		Serial.println("Unknown error");
		return p;
	}
 }
uint8_t Finger::convertimage()
{
	int p = finger->image2Tz();
	switch (p) {
	case FINGERPRINT_OK:
		Serial.println("Image converted");
		return p;
	case FINGERPRINT_IMAGEMESS:
		Serial.println("Image too messy");
		return p;
	case FINGERPRINT_PACKETRECIEVEERR:
		Serial.println("Communication error");
		return p;
	case FINGERPRINT_FEATUREFAIL:
		Serial.println("Could not find fingerprint features");
		return p;
	case FINGERPRINT_INVALIDIMAGE:
		Serial.println("Could not find fingerprint features");
		return p;
	default:
		Serial.println("Unknown error");
		return p;
	}
}
uint8_t Finger::creat_and_store(int id)
{
	int p = finger->createModel();
	switch (p) {
	case FINGERPRINT_OK:
		Serial.println("Prints matched!");
		break;
	case FINGERPRINT_PACKETRECIEVEERR:
		Serial.println("Communication error");
		return p;
	case FINGERPRINT_ENROLLMISMATCH:
		Serial.println("Fingerprints did not match");
		return p;
	default:
		Serial.println("Unknown error");
		return p;
	}
	p = finger->storeModel(id);
	switch (p) {
	case FINGERPRINT_OK:
		Serial.println("Stored!");
		return p;
	case FINGERPRINT_PACKETRECIEVEERR:
		Serial.println("Communication error");
		return p;
	case FINGERPRINT_BADLOCATION:
		Serial.println("Could not store in that location");
		return p;
	case FINGERPRINT_FLASHERR:
		Serial.println("Error writing to flash");
		return p;
	default:
		Serial.println("Unknown error");
		return p;
	}
}
Finger::Finger(SoftwareSerial *mySerial)
{
	finger =  new Adafruit_Fingerprint(mySerial);
}
void Finger::enrollment()
{
	Serial.println("Fingerprint sensor enrollment");
	Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
	int id = 0;
	while (id == 0) {
		while (!Serial.available());
		id = Serial.parseInt();
	}
	Serial.print("Enrolling ID #");
	Serial.println(id);
	int p = 0;
	while (!p) {
		p = enroll(id);
	}
}
bool Finger::authoritized(int seuil)
{
	int value;
	int n = 0;
	while (true)
	{
		int p = FINGERPRINT_NOFINGER;
		while (p !=FINGERPRINT_OK) p = finger->getImage();
		value = verify();
		if (value >= seuil)return true;
		n += 1;
		if (n >= try_time) return false;
		else Serial.println("Please try again.");
		p = FINGERPRINT_OK;
		while (p != FINGERPRINT_NOFINGER) p = finger->getImage();
	}
}
void Finger::setup()
{
	while (!Serial);
	finger->begin(57600);
	if (finger->verifyPassword()) {
		Serial.println("Found fingerprint sensor!");
	}
	else {
		Serial.println("Did not find fingerprint sensor :(");
		while (true) { delay(1); }
	}
}
uint8_t Finger::enroll(int id)
{
	int p = -1;
	p = getimage();
	p = convertimage(1);
	if (p != 0) return p;
	getimage();
	p = convertimage(2);
	if (p != 0) return p;
	p = creat_and_store(id);
	return 1;
}
inline uint8_t Finger::search()
{
	int p = finger->fingerFastSearch();
	switch (p)
	{case FINGERPRINT_OK:
		Serial.println("Found a print match!");
		return p;
	case FINGERPRINT_PACKETRECIEVEERR:
		Serial.println("Communication error");
		return p;
	case FINGERPRINT_NOTFOUND:
		Serial.println("Did not find a match");
		return p;
	default:
		Serial.println("Unknown error");
		return p;
	}
}
uint8_t Finger::verify()
{
	int p=getimage();
	if (p != 0) return p;
	p = convertimage();
	if (p != 0) return p;
	p = search();
	if (p != 0) return p;
	return finger->confidence;
}
#endif