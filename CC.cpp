#include "CC.h"

bool CC::ConsoleNumInputCheck() {
	if (std::cin.fail()) {
		std::cerr << std::endl;
		std::cerr << "You wrote not a number, pls be careful!" << std::endl;
		std::cerr << std::endl;
		std::cin.clear();
		std::cin.ignore();
		return true;
	}
	else {
		return false;
	}
}

int CC::ConsoleNumInputCheck(const std::vector<std::string>& message, int& src) {
	do
	{
		if (message.size() == 1) {
			std::cout << message[0];
		}
		else {
			for (int i = 0; i < message.size(); i++) {
				if (i < message.size() - 1) {
					std::cout << message[i] << std::endl;
				}
				else
				{
					std::cout << message[i];
				}
			}
		}

		std::cin >> src;
	} while (CC::ConsoleNumInputCheck());

	return src;
}

void CC::CIWithBoundariesCheck(
	const std::vector<std::string>& message,
	int& value,
	const std::function<bool(int& v)>& check,
	const std::string error) {
	bool success = false;
	do
	{
		CC::ConsoleNumInputCheck(message, value);
		success = check(value);
		if (!success) {
			CC::WriteErrorMessage(error);
		}
	} while (!success);
}

void CC::WriteErrorMessage(const std::string message) {
	std::cout << std::endl;
	std::cout << message << std::endl;
	std::cout << std::endl;
}
