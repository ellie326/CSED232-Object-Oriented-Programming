#include <iostream>
#include <cstring>																			//cstring header for strcmp 
#include <cmath>																			//cmath needed for sqrt 

using namespace std; 

int main() {
	cout << "enter an operator and number(s) to operate: ";
	char operat[7];																			//If the user input square, including null character at the of the string, a char array [7] is needed 
	cin >> operat;

	float result = 0;

	if (operat[0] == '+' || operat[0] == '-' || operat[0] == '*' || operat[0] == '/') {

		float num1 = 0, num2 = 0;															//If the operator is among +, -, *, and /, the user should input two numbers 
		cin >> num1 >> num2;

		if (operat[0] == '+') {
			result = num1 + num2;
		}
		else if (operat[0] == '-') {
			result = num1 - num2;
		}
		else if (operat[0] == '*') {
			result = num1 * num2;
		}
		else if (operat[0] == '/') {
			result = num1 / num2;
		}
	}
	else if (strcmp(operat, "square") == 0 || strcmp(operat, "sqrt") == 0) {				//For strcmp(a,b), if a = b, then the value for strcmp will be 0

		float num = 0;																		//If the operator is either sqrt or square, the user should input a number 
		cin >> num;

		if (strcmp(operat, "square") == 0) {
			result = num * num;
		}
		else if (strcmp(operat, "sqrt") == 0) {
			result = sqrt(num);
		}
	}
	else {																					//When an operator is none of listed above 
		cout << "Wrong Operator Input!" << endl;
	}

	if (result - (int)result == 0) {														//정수의 경우 
		int int_result = (int)result;
		cout << "The result is " << int_result << endl;
	}
	else {																					//소수의 경우 
		cout << fixed;																		//round the decimal in 3 places and print 
		cout.precision(3);
		cout << "The result is " << result << endl;
	}
return 0;
}