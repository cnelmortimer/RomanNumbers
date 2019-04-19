// N.C. Cruz, University of Almeria, Spain (2019)
#ifndef EXAM_WINDOW
#define EXAM_WINDOW

#include <Window.h>
#include <StringView.h>
#include <Alert.h>
#include <Button.h>
#include <TextControl.h>
#include <View.h>
#include <CheckBox.h>
#include <cstdlib>
#include <cstring>
#include "ConversionHelper.h"
#include "Definitions.h"

class ExamWindow: public BWindow{
	public:
		ExamWindow(BWindow* parent);
		
		bool QuitRequested(void);	
		
	private:
		BWindow* parent;
		
		BView* view;		
		BStringView* taskLabel;
		BTextControl* textInput;
		BCheckBox* setHard;
		BButton* tryButton;
		BStringView* scoreBoard;
		BStringView* labelAbout;
		
		int targetValue;
		char* targetRoman;
		bool mode;
		int failed;
		int correct;
		
		void buildComponents(void);
		void adjustControls(void);
		
		void SetUpQuestion(void);
		void Correct(void);
		void SwitchToHard(void);
		
		void MessageReceived(BMessage* message);
};

#endif
