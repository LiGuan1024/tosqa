// Blinky demo sketch, controlled by Bencoded commands.
// 2012-10-03 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

// Sample data:
//  l4:ratei250eel7:triggeri4eel5:counti10ee
//  l4:ratei100eel7:triggeri10eel5:counti20ee

#include "lpc17xx.h"
#include "uart0.c"
#include "string.h"
//#include "stdio.h"

extern "C" void startup_delay () {}

#if 1
  // there's no proper std C library support yet, so implement everything here

  static char* uconv(char* p, uint32_t v, uint8_t r) {
    if (v >= r)
      p = uconv(p, v / r, r);
    *p = v % r + '0';
    return p + 1;
  }

  char* ultoa (uint32_t value, char* buffer, uint8_t radix) {
  	//sprintf(buffer, "%lu", value);
    char *p = uconv(buffer, value, radix);
    *p = 0;
  	return buffer;
  }

  size_t strlen(const char* p) {
    size_t i;
    for (i = 0; *p++; ++i)
      ;
    return i;
  }
#endif

#include "EmBencode.cpp"

#define VERSION 101

volatile int dummy;
long millis;

char embuf [200];
EmBdecode decoder (embuf, sizeof embuf);
EmBencode encoder;

int rate;       // time between toggling the LED (ms)
int count;      // number of blinks still to go
int trigger;    // after how many blinks to trigger
long total;     // total number of blinks
long lastFlip;  // time when we last flipped the LED (ms)

static void initLed () {
	LPC_PINCON->PINSEL1 &= ~ (3 << 12); // set general GPIO mode 0
	LPC_GPIO0->FIODIR |= 1 << 22; // P0.22 connected to LED2
}

static uint8_t toggleLed () {
	LPC_GPIO0->FIOPIN ^= 1 << 22; // Toggle P0.22
  return (LPC_GPIO0->FIOPIN >> 22) & 1;
}

/*
static void wasteSomeTime (int t) {
	for (int i = dummy = 0; i < 10000 * t && !dummy; ++i) {}
}
*/

void EmBencode::PushChar (char ch) {
	UART0_Sendchar(ch);
}

static void sendGreeting () {
  encoder.startList();
  encoder.push("blinky");
  encoder.push(VERSION);
  encoder.endList();
}

static void sendErrorMsg (const char* msg) {
  encoder.startList();
  encoder.push(1); // error code
  encoder.push(msg);
  encoder.endList();
}

static void sendDoneMsg () {
  encoder.startList();
  encoder.push("done");
  encoder.endList();
}

void sendTriggerTime () {
  encoder.startList();
  encoder.push("time");
  encoder.push(millis);
  encoder.endList();
}

static void setNumber (int& ivar) {
  if (decoder.nextToken() == EmBdecode::T_NUMBER)
    ivar = decoder.asNumber();
  else
    sendErrorMsg("number expected");
}

void setup () {
  UART0_Init(57600);
  UART0_PrintString("hello!!!!!!!!!!!!!!\r\n");
  sendGreeting();
  initLed();
  lastFlip = millis;
#if 1
  rate = 250;
  trigger = 4;
  count = 10;
#endif
}

void loop () {
  // process incoming serial data
  if (UART0_Haschar() > 0 &&
      decoder.process(UART0_Getchar()) > 0 &&
      decoder.nextToken() == EmBdecode::T_LIST &&
      decoder.nextToken() == EmBdecode::T_STRING) {
    // a complete message has been received
    const char* cmd = decoder.asString();
    if (strcmp(cmd, "rate") == 0)
      setNumber(rate);
    else if (strcmp(cmd, "count") == 0)
      setNumber(count);
    else if (strcmp(cmd, "trigger") == 0)
      setNumber(trigger);
    else
      sendErrorMsg("command expected");
    decoder.reset();
    total = 0; // synchronise on each new setting
  }
  // perform the requested blinky work
  long now = ++millis;
	//wasteSomeTime(1);
  if (count > 0 && rate > 0 && now >= lastFlip + rate) {
    // the time has come to flip the LED state
    lastFlip = now;
    bool on = toggleLed();
    // check whether the LED just went off
    if (!on) {
      // has the time come to send out a trigger report?
      if (trigger > 0 && ++total % trigger == 0)
        sendTriggerTime();
      // have we completed our work?
      if (--count == 0)
        sendDoneMsg();
    }
  }
}

int main () {
	setup();
	while (1)
		loop();
	return 0;
}
