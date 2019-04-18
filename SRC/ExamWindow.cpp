#include "ExamWindow.h"

enum{
	E_BUTTON_TRY = 'try',
	E_GO_HARD = 'har'
};

const int MAX_IN_HARD_TEST = 2147483647;
const int MAX_IN_EASY_TEST = 10000;
const int MAX_QUESTIONS = 10;

ExamWindow::ExamWindow(BWindow* parent)
	: BWindow(BRect(INIT_TOP_LEFT, INIT_TOP_LEFT, INIT_RIGHT, INIT_BOTTOM), "Roman Numbers' Exam", B_TITLED_WINDOW, 
	B_NOT_RESIZABLE | B_NOT_ZOOMABLE | B_AUTO_UPDATE_SIZE_LIMITS){
	this->parent = parent;
	BPoint pt = parent->ConvertToScreen(BPoint(0, 0));
	MoveTo(pt.x, pt.y + parent->Bounds().IntegerHeight());
	targetValue = 0;
	mode = 0;
	failed = 0;
	correct = 0;
	buildComponents();
	adjustControls();
	SetUpQuestion();
	Show();
}

void ExamWindow::buildComponents(void){
	view = new BView(BRect(0,0, Frame().Width(), Frame().Height()),"colorview",B_FOLLOW_ALL, B_WILL_DRAW);
	AddChild(view);
	view->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	
	taskLabel = new BStringView(BRect(0, 0, 1, 1), "taskLabel", "Convert to decimal: ((MDCCCLXXXVIII)DCCCLXXXVIII)DCCCLXXXVIII");
	taskLabel->ResizeToPreferred();
	taskLabel->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	view->AddChild(taskLabel);
	
	textInput = new BTextControl(BRect(0, 0, 1, 1), "textInput", "", 0, 0);
	view->AddChild(textInput);
	textInput->ResizeTo(TEXT_FIELD_WIDTH, textInput->Bounds().IntegerHeight());
	
	setHard = new BCheckBox(BRect(0,0,0,0), "chkSetHard", "Hard mode", new BMessage(E_GO_HARD), B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_NAVIGABLE);
	setHard->ResizeToPreferred();
	setHard->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	view->AddChild(setHard);
	
	tryButton = new BButton(BRect(0, 0, 1, 1),"tryButton","Try", new BMessage(E_BUTTON_TRY));
	tryButton->ResizeToPreferred();
	view->AddChild(tryButton);
	
	scoreBoard = new BStringView(BRect(0, 0, 1, 1), "socreBoard", "Correct: 0; Failed: 0 (Total: 0)");
	scoreBoard->ResizeToPreferred();
	scoreBoard->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	view->AddChild(scoreBoard);
	
	labelAbout = new BStringView(BRect(0, 0, 1, 1), "authorLabel", AUTHOR_TEXT);
	labelAbout->ResizeToPreferred();
	labelAbout->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	view->AddChild(labelAbout);
}

void ExamWindow::adjustControls(void){//Function that separates creation from position (in case of future responsiveness)
	int marginX = 5, marginY = 5;
	int BoundsIntWidth = Bounds().IntegerWidth();
	int BoundsIntHeight = Bounds().IntegerHeight();
	taskLabel->MoveTo(marginX, marginY);
	textInput->MoveTo((BoundsIntWidth - textInput->Bounds().IntegerWidth())/2, 2*marginY + taskLabel->Bounds().IntegerHeight());
	tryButton->MoveTo((BoundsIntWidth - tryButton->Bounds().IntegerWidth())/2, 2*(marginY + textInput->Bounds().IntegerHeight()));
	int rowScore = 4+marginY + 4*textInput->Bounds().IntegerHeight();
	scoreBoard->MoveTo(marginX, rowScore);
	setHard->MoveTo(BoundsIntWidth - setHard->Bounds().IntegerWidth() - marginX, rowScore-marginY);
	labelAbout->MoveTo((BoundsIntWidth - labelAbout->Bounds().IntegerWidth())/2, BoundsIntHeight-labelAbout->Bounds().IntegerHeight());
}

void ExamWindow::SetUpQuestion(void){
	mode = rand() % 2; // 0-> Decimal to roman; 1-> Roman to decimal
	int reference = (setHard->Value()==B_CONTROL_ON)?MAX_IN_HARD_TEST:MAX_IN_EASY_TEST;
	targetValue = (rand() % reference)+1;
	int out_len = 0;
	targetRoman = decimalToRoman(targetValue, out_len);//Directly accessing the underlying library
	char textBuffer[100];
	if(mode){
		sprintf(textBuffer, "Convert to decimal: %s", targetRoman);
		taskLabel->SetText(textBuffer);
	}else{
		sprintf(textBuffer, "Convert to roman: %d", targetValue);
		taskLabel->SetText(textBuffer);
	}
	sprintf(textBuffer, "Correct: %d; Failed: %d (Total: %d)", correct, failed, correct+failed);
	scoreBoard->SetText(textBuffer);
}

void ExamWindow::Correct(void){
	const char* userInput = textInput->Text();
	char textBuffer[100];
	if(mode){// 0-> Decimal to roman; 1-> Roman to decimal
		int numberEntered = atoi(userInput);
		if(numberEntered==targetValue){
			correct++;
		}else{
			failed++;
			sprintf(textBuffer, "Sorry, the answer was: %d", targetValue);
			(new BAlert("alert", textBuffer, "Ok", 0, 0, B_WIDTH_AS_USUAL, B_INFO_ALERT))->Go();
		}
	}else{
		if(strcmp(userInput, targetRoman)==0){
			correct++;
		}else{
			failed++;
			sprintf(textBuffer, "Sorry, the answer was: %s", targetRoman);
			(new BAlert("alert", textBuffer, "Ok", 0, 0, B_WIDTH_AS_USUAL, B_INFO_ALERT))->Go();
		}
	}
	textInput->SetText("");
	free(targetRoman);//Free the previous reference before resetting
	if((correct+failed)<MAX_QUESTIONS){
		SetUpQuestion();
	}else{
		sprintf(textBuffer, "You completed the test. Congratulations! %d Corrects; %d Failed.", correct, failed);
		(new BAlert("alert", textBuffer, "Ok", 0, 0, B_WIDTH_AS_USUAL, B_INFO_ALERT))->Go();
		PostMessage(B_QUIT_REQUESTED);//Quit();
	}
}

void ExamWindow::SwitchToHard(void){
	if(setHard->Value()==B_CONTROL_ON){
		(new BAlert("alert", "Resetting and entering into the hard mode!", "Ok", 0, 0, B_WIDTH_AS_USUAL, B_INFO_ALERT))->Go();
	}
	targetValue = 0;
	mode = 0;
	failed = 0;
	correct = 0;
	SetUpQuestion();
}

void ExamWindow::MessageReceived(BMessage* message){
	switch(message->what){
		case E_BUTTON_TRY:
			Correct();
			break;
		case E_GO_HARD:
			SwitchToHard();
			break;
	}
}

bool ExamWindow::QuitRequested(void){
	parent->PostMessage(new BMessage('ublc'));
	return true;	
}
