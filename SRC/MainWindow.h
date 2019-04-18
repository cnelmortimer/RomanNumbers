// N.C. Cruz, University of Almeria, Spain (2019)
#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include "ExamWindow.h"//Required includes indirectly come from here

class MainWindow: public BWindow{
	public:
		MainWindow(void);

	private:
		BView* view;
		
		BStringView* labelDecimal;
		BStringView* labelRoman;
		
		BTextControl* textDecimal;
		BTextControl* textRoman;
		
		BButton* butRom2Dec;
		BButton* butDec2Rom;
		BButton* butClear;
		BButton* butExam;
		
		BStringView* labelAbout;
		bool examRunning;
		
		void buildComponents(void);
		void adjustControls(void);
		
		void Decimal2Roman(void);
		void Roman2Decimal(void);
		
		void Unblock(void);
		void LaunchExam(void);
		
		void MessageReceived(BMessage* message);
};

#endif
