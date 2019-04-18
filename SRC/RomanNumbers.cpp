#include "RomanNumbers.h"

const int ROM_LEN_VALS = 9;// Maximum int: 2147483647 -> ((MMCXLVII)CDLXXXIII)DCXLVII
const int MAX_ROM_LEN = 41;// To define the number that requires the most chars, i.e., 1888888888 -> ((MDCCCLXXXVIII)DCCCLXXXVIII)DCCCLXXXVIII
const char rom[] = {'M', 'D', 'C', 'L', 'X', 'V', 'I', '(', ')'};
const int dec[] = {1000, 500, 100, 50, 10, 5, 1, 0, 0};

//ROMAN TO DECIMAL. Returns: -2 -> Unbalanced parenthesis; -1 -> Unknown symbols; VALS otherwise
int lookForIndex(char symbol){
	for(int i = 0; i<ROM_LEN_VALS; i++){
		if(rom[i]==symbol)
			return i;
	}
	return -1;
}

int romanToDecimal(int len, const char* str){
	int number = 0, index = 0, next_index = 0, lefts = 0, rights = 0;
	char focus = '0';
	for(int i = 0; i<len; i++){
		focus = str[i];
		if(focus=='('){
			lefts += 1;
		}else if(focus==')'){
			number = number*1000;
			rights += 1;
		}else{
			index = lookForIndex(focus);
			if(index==-1) return -1;// Error: Unknown symbol
			if(i!=(len-1)){
				next_index = lookForIndex(str[i+1]);
				if(next_index==-1) return -1; // Error: Unknown symbol
				dec[index]>=dec[next_index] ? number += dec[index] : number -= dec[index];
			}else{
				number += dec[index];
			}
		}
	}
	return lefts==rights ? number : -2;// Were there missing parenthesis?
}

//DECIMAL TO ROMAN:
char* baseDec2Rom(int number, int& out_len){// < 3999 <INTERNAL AUXILIARY FUNCTION>
	out_len = 0;//Initial output
	char* buffer = (char*) malloc(sizeof(char)*MAX_ROM_LEN);
	int focus = 0;
	while(number>0){
		if(dec[focus]>number){
			if( (focus%2!=1) && (dec[focus] - dec[focus + 2]) <= number){
				buffer[out_len] = rom[focus + 2];
				buffer[out_len + 1] = rom[focus];
				number = number - (dec[focus] - dec[focus + 2]);
				out_len += 2;
			}else if( (focus%2!=0) && (dec[focus] - dec[focus + 1]) <= number){
				buffer[out_len] = rom[focus + 1];
				buffer[out_len + 1] = rom[focus];
				number = number - (dec[focus] - dec[focus + 1]);
				out_len += 2;
			}
			focus++;
		}else{
			buffer[out_len] = rom[focus];
			out_len++;//One more symbol
			number = number - dec[focus];
		}
	}
	char* res = (char*) malloc(sizeof(char)*out_len);//We want to keep the array as tight as possible...
	for(int i = 0; i<out_len; i++)
		res[i] = buffer[i];
	free(buffer);
	return res;
}

char* internalDec2Rom(int number, int& out_len){//Out of range should be 2147483647 <INTERNAL AUXILIARY FUNCTION>
	if(number>3999){//Parenthesis required
		out_len = 0;//Initial output
		int lenA = 0, lenB = 0;
		char* resA = internalDec2Rom(number/1000, lenA);
		char* resB = 0;
		if(number%1000 != 0){
			resB = internalDec2Rom(number - (number/1000)*1000, lenB);
		}
		char* res = (char*) malloc(sizeof(char)*(lenA + lenB + 2));
		res[0] = '('; 
		res[lenA+1] = ')';		
		for(int i = 0; i<lenA; i++)
			res[i+1] = resA[i];
		for(int i = 0; i<lenB; i++)
			res[lenA+2+i] = resB[i];
		out_len = lenA + 2 + lenB;
		free(resA);
		if(lenB>0) free(resB);
		return res;		
	}else{//No parenthesis are required (base case)
		return baseDec2Rom(number, out_len);
	}
}

char* decimalToRoman(int number, int& out_len){
	char* tmp = internalDec2Rom(number, out_len);
	char* res = (char*) malloc(sizeof(char)*(out_len+1));
	for(int i = 0; i<out_len; i++)
		res[i] = tmp[i];
	res[out_len] = '\0';
	free(tmp);
	return res;
}

