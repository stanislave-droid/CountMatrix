#include "Matrix.h"

Matrix::Matrix(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
    initialize();
}

Matrix::~Matrix() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->inMatrix[i];
    }
    delete[] this->inMatrix;
}

void Matrix::initialize() {
    this->inMatrix = new int * [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->inMatrix[i] = new int[this->columns];
    }
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            this->inMatrix[i][j] = rand() % 100;
        }
    }
}

void count(int index, std::mutex& mut, int** matrix, int& rows, int& columns, std::map<int, int>& outMap) {
    mut.lock();
    int** tempRow = new int*[rows];
    std::map<int, int> tempMap;
    for (int i = index; i < rows; i++) {
        for (int j = 0; j < rows / 2; j++) {
            // Fill row from main matrix
            tempRow[j] = matrix[i];
        }

        if (i < rows - 1) {
            i++;
        }
        else
        {
            break;
        }
    }
    mut.unlock();

    // Fill temporary map with values
    for (int i = 0; i < rows / 2; i++) {
        for (int j = 0; j < columns; j++) {
            tempMap[tempRow[i][j]] += 1;
        }
    }

    mut.lock();
    // Synchronize values
    for (const auto& [key, value] : tempMap) {
        outMap[key] += value;
    }
    mut.unlock();

    // Free up memory
    delete[] tempRow;
    tempRow = nullptr;
}

void Matrix::parallelCount(int type) {

    auto start = std::chrono::high_resolution_clock::now();
    std::mutex mut;

    if (type == 0) {
        std::thread t1(count, 0, std::ref(mut), std::ref(this->inMatrix), std::ref(this->rows), std::ref(this->columns), std::ref(this->outMap));
        std::thread t2(count, 1, std::ref(mut), std::ref(this->inMatrix), std::ref(this->rows), std::ref(this->columns), std::ref(this->outMap));
        t1.join();
        t2.join();
    }
    else {
        count(0, std::ref(mut), std::ref(this->inMatrix), std::ref(this->rows), std::ref(this->columns), std::ref(this->outMap));
        count(1, std::ref(mut), std::ref(this->inMatrix), std::ref(this->rows), std::ref(this->columns), std::ref(this->outMap));
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Elapsed time: " << diff << std::endl;
    this->field = true;
}

void Matrix::clearOutMap() {
    if (!this->field) {
        CC::WriteErrorMessage((std::string)("Sorry, but map already clear"));
        return;
    }

    std::cout << "\nMap was cleared\n" << std::endl;

    this->outMap.clear();
    this->field = false;
}

void Matrix::recreateMatrix() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->inMatrix[i];
    }
    delete[] this->inMatrix;
    this->inMatrix = nullptr;
    Matrix::changeSize(this->rows, this->columns);
    this->initialize();
    this->field = false;
    Animation::showProgress();
    std::cout << "Matrix was recreated" << std::endl;
}

void Matrix::changeSize(int& rows, int& columns) {
    auto checkMatrixSize = [](int& v) { if (v <= 0) return false; else return true;};
    do {
        std::vector<std::string> message = { "Pls, write qty of rows: " };
        CC::CIWithBoundariesCheck(message, rows, checkMatrixSize, (std::string)("You wrote wrong number of rows"));
        message = { "Pls, write qty of columns: " };
        CC::CIWithBoundariesCheck(message, columns, checkMatrixSize, (std::string)("You wrote wrong number of columns"));
    } while (rows <= 0 || columns <= 0);
}