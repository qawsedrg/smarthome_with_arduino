#pragma once
#ifndef RECV_H_
#define RECV_H_
#include <IRremote.h>
//struct options
//{
//	char* name;
//	int* signal;
//	void init(char* n, int* s)
//	{
//		name = n;
//		signal = s;
//	}
//};
class RECV
{
private:
	IRrecv* irrecv;
	IRsend* irsend;
	//options* opt;
	/*int* receive();*/
public:
	RECV(IRrecv* ir);
	void send(int khz=38);
};
//int* RECV::receive()
//{
//	int count = results.rawlen;
//	if (irrecv->decode(&results)) 
//	{
//		Serial.println(results.value, HEX);
//		irrecv->resume();
//	}
//	int* response = new int[count];
//	for (int i = 1; i < count; i++)
//	{
//		response[i - 1] = results.rawbuf[i] * USECPERTICK;
//	}
//	return response;
//}
RECV::RECV(IRrecv* ir)
{
	irrecv = ir;
	irsend = new IRsend;
}
void RECV::send(int khz)
{
	irsend->sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz);
}
#endif