#include <iostream>
#include <cmath>																	//cmath needed for pow function (power) 

using namespace std; 

void conversion(string input, int* number); 

int main() {
	int repeat = 1;

	do{
		cout << "Enter the operator and two numbers: "; 
		
		char operat;																//operat = operator 
		string input1, input2; 
		cin >> operat >> input1 >> input2;

		int num1 = 0, num2 = 0; 
		
		conversion(input1, &num1);													//conversion function will convert the input numbers into decimal form 
		conversion(input2, &num2);													//use call by address for num1 and num2 
		
		if (num1 < 0 || num2 < 0) {															
			cout << "Wrong input number(s)." << endl;
			continue; 
		}

		double result;																//Since a division operator can have answer in decimal form, use double data type 
		if (operat == '+') {
			result = num1 + num2; 
		}
		else if (operat == '-') {
			result = num1 - num2;
		}
		else if (operat == '*') {
			result = num1 * num2;
		}
		else if(operat == '/') {
			result = (double)num1 / num2;											//type conversion of num1 so that the result is in decimal form. 
		}
		else {
			cout << "Wrong operator!" << endl;										//If user input an operator other than +, -, *, and / 
			continue; 
		}

		if (result - (int)result == 0) {											//정수인 경우 
			cout << "The result is " << (int)result << endl;
		}
		else {																		//소수인 경우 
			cout << fixed;															//decimal in 3 places and print the result
			cout.precision(3);
			cout << "The result is " << result << endl;
		}

		cout << "If you wish to repeat the calculation, type 1. " << endl;			//Asks the user to repeat the calculation or end the program 
		cout << "If you wish to end the calculation, type 0. " << endl; 
		cout << "Type: "; 
		cin >> repeat; 

	} while (repeat);																//1 = true, repeat the program and 0 = false, end the program  
	
	return 0; 
}

void conversion(string input, int* number) {
	int power = 0, i;																//power will be used like 2 to the nth power, 8 to the nth power, etc. (n = value assinged in power)
																					//'i' will track the string from the end up to 'b' 'X' or ' '
	
	if (input[1] == 'b') {															//when the input number is a binary number 
		for (i = input.size() - 1; i > 1; i--) {
			if (input[i] != '1' && input[i] != '0') {								//When a binary input is neither 1 nor 0 --> wrong input 
				*number = -1;
				return; 
			}
			else {
				if (input[i] == '1') {												//when 'i'th string is 1, multiply 2 to the nth power
					*number += pow(2, power);
				}
			}
			power++;																//As 'i' approach to the power will increase by 1 
		}
	}
	else if (input[1] == 'X') {														//when the input number is a hexadecimal number 
		int hex_int = 0; 
		for (i = input.size() - 1; i > 1; i--) {
			
			if (input[i] >= '0' && input[i] <= '9') {								//when 'i'th input value is between 0 and 9 
				hex_int = input[i] - '0';											//convert string into an integer using ASCII code value 
			}
			else if (input[i] >= 'A' && input[i] <= 'F') {							//when 'i'th input value is between A and F (each 10 and 15) 
				hex_int = input[i] - 'A' + 10;										//convert string(char) into an integer using ASCII code value 
			}
			else {																	//when the input is not in hexadecimal form 
				*number = -1; 
				return; 
			}

			*number += hex_int * pow(16, power); 
			power++; 
		}
	}
	else if (input[1] >= '0' && input[1] <= '9') {									//when the input number is a octal number 
		int oct_int = 0; 
		for (i = input.size() - 1; i > 0; i--) {
			if (input[i] >= '0' && input[i] <= '7') {								//when 'i'th input value is between 0 and 9 
				oct_int = input[i] - '0'; 
			}
			else {																	//when the input is not in octal form 
				*number = -1; 
				return; 
			}
			
			*number += oct_int * pow(8, power);
			power++; 
		}
	}
	return; 
}