#pragma once
#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "UserFeedback.h"

#define OLED_RESET 4


class UserFeedback :public Adafruit_SSD1306 //;	SSD1306_128_64  128x64 pixel display
{
public:
	
	void start();

	

	void print_in_Zeile_1(const String &s) { print_in_Zeile_n(s, 0); };
	void print_in_Zeile_2(const String &s) { print_in_Zeile_n(s, 1); };
	void print_in_Zeile_3(const String &s) { print_in_Zeile_n(s, 2); };
	void print_in_Zeile_4(const String &s) { print_in_Zeile_n(s, 3); };

	

private:
	uint32_t timy_save_time = millis();
	bool timy(int neue_zeit);
	void print_in_Zeile_n(const String & s, uint8_t Zeilennummer);

};
extern UserFeedback userFeedback;