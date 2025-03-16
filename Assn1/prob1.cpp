#include <iostream>

using namespace std;

string conversion(int num, int divider);													//return string of binary/octal/hexadecimal 
void print(string result); 

int main() {
	int input_dec, num_type; 
	string result_num; 
		cout << "Enter decimal number and the number you want to change to: ";
		cin >> input_dec >> num_type;														//save input numbers in integer type 

		if (num_type == 2 || num_type == 8 || num_type == 16) {
			result_num = conversion(input_dec, num_type);									//convert decimal number to n 진수 
			print(result_num);																//print the converted number 
		}
		else {
			cout << "Wrong input!";
		}
	return 0; 
}

string conversion(int num, int divider) {													//num = input decimal number ; divider = n 진수 
	int remainder = 0;
	char hex; 
	string result; 
	
	if (num > 9 && num < divider && divider == 16) {										//only when changing dec to hexadec & expressed in A~F
		hex = char(num + 55);																//convert integer to char type using ASCII code (ASCII code alphabet A is equal to 65)
		result = hex + result;	
	}
	else {
		while (num >= divider) {															//while loop until the input number is smaller than n진수
			remainder = num % divider;
			if (remainder > 9) {
				hex = (char)(remainder + 55);												//convert integer to char type using ASCII code
				result = hex + result;
			}
			else {
				result = char(remainder + 48) + result;										//convert integer to char type using ASCII code (ASCII code number 1 is equal to 48)
			}
			num = num / divider;
		}
		if (num > 9 && num < divider && divider == 16) {									//only when changing dec to hexadec & expressed in A~F
			hex = char(num + 55);															//convert integer to char type using ASCII code (ASCII code alphabet A is equal to 65)
			result = hex + result;
		}
		else {
			result = char(num + 48) + result;												//convert integer to char type using ASCII code
		}
	}
	return result;
}

void print(string result) {
	cout << "The result is "; 
	for (int i = 0; i < result.size(); i++) {												//print the saved array from 0 to the end (result.size() will give the size of the array)
		cout << result[i];
	}
	cout << endl;
}