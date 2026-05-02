#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>

// ConsoleController
class CC
{
public:
	static bool ConsoleNumInputCheck();
	static int ConsoleNumInputCheck(const std::vector<std::string>& message, int& src);
	static void WriteErrorMessage(const std::string message);
	static void CIWithBoundariesCheck(
		const std::vector<std::string>& message,
		int& value,
		const std::function<bool(int& v)>& check,
		const std::string error);
};

