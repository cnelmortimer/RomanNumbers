// N.C. Cruz, University of Almeria, Spain (2019)
#ifndef APP_ROMAN_NUMBERS
#define APP_ROMAN_NUMBERS

#include <Application.h>
#include <cstdio>
#include <cstring>
#include "MainWindow.h"
#include "ConversionHelper.h"

class App: public BApplication{
	public:
		App(void);
		static int ConsoleMode(char* val);
		static int DecimalConsole(char* val);
		static int RomanConsole(char* val);
	private:
		MainWindow* window;
};

#endif
