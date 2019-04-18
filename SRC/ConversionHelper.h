// N.C. Cruz, University of Almeria, Spain (2019)
#ifndef CONVERSION_HELPER
#define CONVERSION_HELPER

#include <cstdio>
#include "RomanNumbers.h"

char* FromDecimalToRoman(const char* val, char** outErrorMessage);

char* FromRomanToDecimal(const char* val, char** outErrorMessage);

#endif
