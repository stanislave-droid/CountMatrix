#pragma once
#include <thread>
#include <map>
#include <Windows.h>
#include <string>
#include <mutex>
#include <iostream>
#include <chrono>
#include "CC.h"
#include <fstream>
#include "Animation.h"

class Matrix
{
	int rows;
	int columns;
	int** inMatrix;
	std::map<int, int> outMap;
	bool field{ false };

	void initialize();

public:
	Matrix() : Matrix(1000, 1000) {};
	Matrix(int rows, int columns);
	~Matrix();

	void parallelCount(int type);
	void clearOutMap();
	void recreateMatrix();
	static void changeSize(int& rows, int& columns);

	bool getFieldStatus() {
		return this->field;
	}

	friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
		/*for (int i = 0; i < m.rows; i++) {
			for (int j = 0; j < m.columns; j++) {
				os << "(" << m.inMatrix[i][j] << ")";
			}
			os << std::endl;
		}*/
		for (const auto& [key, value] : m.outMap) {
			os << "[" << key << "], qty: " << value << std::endl;
		}
		return os;
	};

	friend std::ofstream& operator<<(std::ofstream& os, const Matrix& m) {
		for (const auto& [key, value] : m.outMap) {
			os << "[" << key << "], qty: " << value << std::endl;
		}
		return os;
	}
};

