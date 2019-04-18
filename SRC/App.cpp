#include "App.h"

App::App(void): BApplication("application/x-vnd.nccruz-RomanNumbers"){
	this->window = new MainWindow();
	this->window->Show();
}

int App::DecimalConsole(char* val){
	char* errorMessage = 0;
	char* result = FromDecimalToRoman(val, &errorMessage);
	if(result!=0){
		printf("%s\n", result);
		free(result);
		return 0;
	}else{
		printf("Error: %s\n", errorMessage);
		return 1;
	}
}

int App::RomanConsole(char* val){
	char* errorMessage = 0;
	char* result = FromRomanToDecimal(val, &errorMessage);
	if(result!=0){
		printf("%s\n", result);
		free(result);
		return 0;
	}else{
		printf("Error: %s\n", errorMessage);
		return 1;
	}
}

int App::ConsoleMode(char* val){
	if(val[0]>=48 && val[0]<=57){//The input seems to be a decimal value (i.e., the first char is a number between 0 and 9)
		return DecimalConsole(val);
	}else{
		return RomanConsole(val);
	}
}

int main(int argc, char* argv[]){
	if(argc==1){//The filename is the default parameter
		srand(time(0));
		App* app = new App();
		app->Run();
		delete app;
		return 0;
	}else if(argc==2){//Filename plus a value for the console mode
		return App::ConsoleMode(argv[1]);
	}else{
		printf("Type: ./RomanNumbers without parameters will launch the complete GUI mode.\n\nType ./RomanNumbers <val> to use the console mode:\n");
		printf("\tIf <val> is a decimal number, it will be converted to roman.\n");
		printf("\tIf <val> is a roman number, it will be converted to decimal.\n");
		return 1;
	}
}
