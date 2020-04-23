
#include <iostream>
#include <limits>


int main()
{
	//std::cout << "Hello CMake Solver." << std::endl;

	int input = 0;
	int count = 0;
	int skippedCount = 0;

	for (;;) {
		std::cin >> input;

		if (std::cin.eof() || std::cin.bad()) {
			break;
		}
		else if (std::cin.fail()) {
			++skippedCount;
			std::cin.clear(); // unset failbit
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // skip bad input
		}
		else {
			++count;
			std::cout << input << std::endl;
		}
	}
	std::cout << "\nEntered : " << count << "\nSkipped  : " << skippedCount;


	return 0;
}
