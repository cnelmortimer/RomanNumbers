#include "ConversionHelper.h"

char* FromDecimalToRoman(const char* val, char** outErrorMessage){
	int len = strlen(val);
	char* output = 0;
	if(len>0 && len<11){
		bool valid = true;
		for(int i = 0; i<len; i++){
			if(val[i]<48 || val[i]>57){
				*outErrorMessage = "Each digit must be a number between 0 and 9";	
				valid = false;
				break;
			}
		}
		if(valid){
			int input = atoi(val);
			if(input>0){
				output = decimalToRoman(input, len);
			}else{
				*outErrorMessage = "Number 0 cannot be expressed in roman numbers";
			}
		}
	}else{
		*outErrorMessage = "Your decimal number must contain between 1 and 10 digits";
	}
	return output;
}

char* FromRomanToDecimal(const char* val, char** outErrorMessage){
	int len = strlen(val);
	char* output = 0;
	if(len<1||len>41){
		*outErrorMessage = "Your roman number must contain between 1 and 41 characters";
	}else{
		int result = romanToDecimal(len, val);
		if(result<0){
			if(result==-1){
				*outErrorMessage = "Use only the following chars to write roman numbers: 'M', 'D', 'C', 'L', 'X', 'V', 'I', '(' and ')'";
			}else{
				*outErrorMessage = "The roman number in unbalanced. Missing parenthesis";
			}
		}else{
			char* extraTest = decimalToRoman(result, len);//To ensure that the roman input was OK
			if(strcmp(extraTest, val)==0){
				output = (char*) malloc(sizeof(char)*12);
				sprintf(output, "%d", result);
			}else{
				printf("The input roman number seems incorrect");
			}
			free(extraTest);
		}	
	}
	return output;
}
