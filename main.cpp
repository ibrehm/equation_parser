#include <iostream>
#include "equation.h"

//------------------------------------------------------------------------------
int main(int argc, char *argv[]) {

	std::string equation = "";
	int precision = 0;
	if(argc > 1) {
		if(argc > 2) {
			precision = std::stoi(argv[2]);
			std::cout << std::setprecision(precision);
		}
		equation.append(argv[1]);

		if(equation[ equation.size() -1 ] != ';') {
            equation.push_back(';');
		}

		double num = Solve<double>(equation);
		std::cout << num << "\n";
	}

	return(0);

}
//------------------------------------------------------------------------------
