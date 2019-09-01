#include "UserFeedback.h"


void UserFeedback::start() {
	begin(SSD1306_SWITCHCAPVCC, 0x3C, 1);
	clearDisplay();
	setTextSize(1);
	setTextColor(WHITE);
	print_in_Zeile_1("Start");
	display();
}

bool UserFeedback::timy(int neue_zeit)
{
	bool temp_bool = false;
	if (timy_save_time < millis())
	{
		timy_save_time = millis() + neue_zeit;
		temp_bool = true;
	}
	return temp_bool;
}

void UserFeedback::print_in_Zeile_n(const String &s, uint8_t Zeilennummer)
{

	int lang = (s.length() > 18) ? (18) : (s.length());
	for (int i = 0; i < 18; i++)
	{
		setTextColor(0);
		setCursor(i * 7 + 2, Zeilennummer * 9); write(218);
	}


	for (int i = 0; i < lang; i++)
	{
		setTextColor(1);
		setCursor(i * 7 + 2, Zeilennummer * 9); print(s[i]);



	}	display();
}
UserFeedback userFeedback;
