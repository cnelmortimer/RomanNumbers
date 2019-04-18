all:
	g++ -o RomanNumbers -O2 SRC/App.cpp SRC/ConversionHelper.cpp SRC/Definitions.cpp SRC/ExamWindow.cpp SRC/MainWindow.cpp SRC/RomanNumbers.cpp -lbe
	xres -o RomanNumbers Resources/Resources.rsrc
	mimeset -f "RomanNumbers"
clean:
	rm RomanNumbers
