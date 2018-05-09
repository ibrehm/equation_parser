#ifndef __equation_h__
#define __equation_h__

#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
#include "utils.h"

//------------------------------------------------------------------------------
// EqLevel basically calculates individual equations. If the original string passed
// to Solve() has multiple brackets () in the overall equation, each bracket will have
// a EqLevel created for it. The program then solves each equation within each bracket
// and works it's way down until it has only a simple equation remaining and solves that.
class EqLevel {
	public:
		void AddNumber(double);
		void AddSymbol(char);
		double Result();
	private:
		std::vector<double> nums;
		std::vector<char> symbols;
};

// Adds a number to the nums vector
void EqLevel::AddNumber(double num) {
	this->nums.push_back(num);
}

// Adds a symbol to the symbols vector. They'll be used to find the result of the equation.
// They are typically '+', '-', '*', '/', '^'
void EqLevel::AddSymbol(char symbol) {
	this->symbols.push_back(symbol);
}

// Find the result of the equation
double EqLevel::Result() {

	double rtrn = 0;

	if(this->nums.size() > 0) {
		rtrn = nums[0];
		unsigned int i = 1;
		while(i < this->nums.size()) {

			if(this->symbols.size() >= 1) {
				switch(this->symbols[(i-1)]) {
					case '+': {
						rtrn += this->nums[i];
						break;
					}
					case '-': {
						rtrn -= this->nums[i];
						break;
					}
					case '*': {
						rtrn *= this->nums[i];
						break;
					}
					case '/': {
						rtrn /= this->nums[i];
						break;
					}
					case '%': {
						rtrn = (int(rtrn) % int(this->nums[i]));
						break;
					}
					case '^': {
						rtrn = pow(rtrn, this->nums[i]);
						break;
					}
				}
			} else {
				rtrn += this->nums[0];
			}
			i++;
		}
	}

	return rtrn;
}
//------------------------------------------------------------------------------
// Solves the full equation passed to the program.
double Solve(const std::string &str) {
	double rtrn = 0;
	std::vector<EqLevel> levels;
	std::string current_value = "0";
	bool parsing_value = false;

	EqLevel temp;
	levels.push_back(temp);

	unsigned int i = 0;
	while(i < str.size()) {
		if(str[i] == '(') {
			levels.push_back(temp);
		} else if( (str[i] == ')') || (str[i] == ';') ) {
			if(parsing_value == true) {
				parsing_value = false;
				levels[levels.size()-1].AddNumber(std::stod(current_value));
				current_value = "0";
			}

			if(levels.size() == 1) {
				break;
			}
			double result = levels[levels.size()-1].Result();
			levels.pop_back();

			current_value = patch::to_string(result);
			parsing_value = true;

		} else if( (str[i] == '+') || (str[i] == '-') || (str[i] == '*') || (str[i] == '/') || (str[i] == '%') || (str[i] == '^')) {

			if((i > 0) && (str[i] == '-') && (str[i-1] != ')') && ((str[i-1] < '0') || (str[i-1] > '9')) && ((str[i+1] >= '0') && (str[i+1] <= '9'))) {
				current_value = '-' + current_value;
				parsing_value = true;
			} else {
				parsing_value = false;
				levels[levels.size()-1].AddNumber(std::stod(current_value));
				current_value = "0";
				levels[levels.size()-1].AddSymbol(str[i]);
			}
		} else if( ( (str[i] >= '0') && (str[i] <= '9') ) || str[i] == '.') {
			parsing_value = true;
			current_value += str[i];

			if(i == (str.size()-1)) {
				levels[levels.size()-1].AddNumber(std::stod(current_value));
				current_value = "0";
			}
		}
		i++;
	}

	rtrn = levels[levels.size()-1].Result();

	return rtrn;
}
//------------------------------------------------------------------------------
// Experimental function, playing with return types
template <typename T>
T Solve(const std::string &str) {
	double rtrn;
	rtrn = Solve(str);

	return (T)rtrn;
}

#endif // __equation_h__
