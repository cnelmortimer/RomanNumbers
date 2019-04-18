#include "MainWindow.h"

enum{
	M_BUTTON_DEC2ROM = 'd2r',
	M_BUTTON_ROM2DEC = 'r2d',
	M_BUTTON_EXAM = 'exam',
	M_BUTTON_CLEAR = 'clea',
	M_UNBLOCK = 'ublc'
};

MainWindow::MainWindow(void)
	: BWindow(BRect(INIT_TOP_LEFT, INIT_TOP_LEFT, INIT_RIGHT, INIT_BOTTOM), "Roman Numbers", B_TITLED_WINDOW, 
	B_NOT_RESIZABLE | B_NOT_ZOOMABLE | B_AUTO_UPDATE_SIZE_LIMITS | B_QUIT_ON_WINDOW_CLOSE){
	buildComponents();
	adjustControls();
	examRunning = false;
}

void MainWindow::Decimal2Roman(void){
	const char* input = textDecimal->Text();
	char* errorMessage = 0;
	char* result = FromDecimalToRoman(input, &errorMessage);
	if(result!=0){
		textRoman->SetText(result);
		free(result);
		if(atoi(input)==2147483647){//In case the number was longer than the maximum, correct the left part
			textDecimal->SetText("2147483647");
		}
	}else{
		(new BAlert("alert", errorMessage, "Ok", 0, 0, B_WIDTH_AS_USUAL, B_INFO_ALERT))->Go();
		butClear->Invoke();
	}
}

void MainWindow::Roman2Decimal(void){
	const char* input = textRoman->Text();
	char* errorMessage = 0;
	char* result = FromRomanToDecimal(input, &errorMessage);
	if(result!=0){
		textDecimal->SetText(result);
		free(result);
	}else{
		(new BAlert("alert", errorMessage, "Ok", 0, 0, B_WIDTH_AS_USUAL, B_INFO_ALERT))->Go();
		butClear->Invoke();
	}
}

void MainWindow::LaunchExam(void){
	if(!examRunning){
		textDecimal->SetText("");
		textRoman->SetText("");
		butDec2Rom->SetEnabled(false);
		butRom2Dec->SetEnabled(false);
		butExam->SetEnabled(false);
		ExamWindow* exam = new ExamWindow(this);
		exam->Show();
		examRunning = true;
	}
}

void MainWindow::Unblock(void){
	butDec2Rom->SetEnabled(true);
	butRom2Dec->SetEnabled(true);
	butExam->SetEnabled(true);
	examRunning = false;
}

void MainWindow::MessageReceived(BMessage* message){
	switch(message->what){
		case M_BUTTON_DEC2ROM:
			Decimal2Roman();
			break;
		case M_BUTTON_ROM2DEC:
			Roman2Decimal();
			break;
		case M_BUTTON_EXAM:
			LaunchExam();
			break;
		case M_UNBLOCK:
			Unblock();
			break;
		case M_BUTTON_CLEAR:
			textDecimal->SetText("");
			textRoman->SetText("");
			break;
	}
}

void MainWindow::buildComponents(void){
	view = new BView(BRect(0,0, Frame().Width(), Frame().Height()),"colorview",B_FOLLOW_ALL, B_WILL_DRAW);
	AddChild(view);
	view->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	labelDecimal = new BStringView(BRect(0, 0, 1, 1), "labelDecimal", "Decimal number:");
	labelDecimal->ResizeToPreferred();
	labelDecimal->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	view->AddChild(labelDecimal);
	
	labelRoman = new BStringView(BRect(0, 0, 1, 1), "labelDecimal", "Roman number:");
	labelRoman->ResizeToPreferred();
	labelRoman->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	view->AddChild(labelRoman);
	
	textDecimal = new BTextControl(BRect(0, 0, 1, 1), "textDecimal", "", 0, 0);	
	view->AddChild(textDecimal);
	textDecimal->ResizeTo(TEXT_FIELD_WIDTH, textDecimal->Bounds().IntegerHeight());
	
	textRoman = new BTextControl(BRect(0, 0, 1, 1), "textRoman", "", 0, 0);
	view->AddChild(textRoman);
	textRoman->ResizeTo(TEXT_FIELD_WIDTH, textRoman->Bounds().IntegerHeight());
	
	butClear = new BButton(BRect(0, 0, 1, 1),"clear","Clear", new BMessage(M_BUTTON_CLEAR));
	butClear->ResizeToPreferred();
	view->AddChild(butClear);
	
	butDec2Rom = new BButton(BRect(0, 0, 1, 1),"dec2rom",">>>", new BMessage(M_BUTTON_DEC2ROM));
	butDec2Rom->ResizeToPreferred();
	view->AddChild(butDec2Rom);
	
	butRom2Dec = new BButton(BRect(0, 0, 1, 1),"rom2dec","<<<", new BMessage(M_BUTTON_ROM2DEC));
	butRom2Dec->ResizeToPreferred();
	view->AddChild(butRom2Dec);
	
	butExam = new BButton(BRect(0, 0, 1, 1),"exam","Exam!", new BMessage(M_BUTTON_EXAM));
	butExam->ResizeToPreferred();
	view->AddChild(butExam);
		
	labelAbout = new BStringView(BRect(0, 0, 1, 1), "authorLabel", AUTHOR_TEXT);
	labelAbout->ResizeToPreferred();
	labelAbout->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	view->AddChild(labelAbout);
}

void MainWindow::adjustControls(void){//Function that separates creation from position (in case of future responsiveness)
	int marginX = 5, marginY = 5;
	labelDecimal->MoveTo(marginX, marginY);
	labelRoman->MoveTo(Frame().Width() - (TEXT_FIELD_WIDTH + marginX), marginY);
	int secondRowY = 2*marginY + labelDecimal->Bounds().IntegerHeight();
	textDecimal->MoveTo(marginX, secondRowY);
	textRoman->MoveTo(Frame().Width() - (TEXT_FIELD_WIDTH + marginX), secondRowY);
	labelAbout->MoveTo((Bounds().IntegerWidth() - labelAbout->Bounds().IntegerWidth())/2, Bounds().IntegerHeight()-labelAbout->Bounds().IntegerHeight());
	int thirdRowY = secondRowY + marginY + textDecimal->Bounds().IntegerHeight();
	butDec2Rom->MoveTo(marginX, thirdRowY);
	butRom2Dec->MoveTo(Frame().Width() - (butRom2Dec->Bounds().IntegerWidth() + marginX), thirdRowY);
	butClear->MoveTo((Bounds().IntegerWidth() - butClear->Bounds().IntegerWidth())/2, thirdRowY);
	butExam->MoveTo((Bounds().IntegerWidth() - butExam->Bounds().IntegerWidth())/2, thirdRowY + marginY + butClear->Bounds().IntegerHeight());
}
