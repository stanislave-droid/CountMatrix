// CountMatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Matrix.h"
#include "CC.h"

void writeToConsole(std::map<int, std::string> m, int i) {
    std::cout << std::this_thread::get_id() << " " << i << std::endl;
    std::map<int, std::string>::iterator it;
    for (it = m.begin(); it != m.end(); it++) {
        if (it == m.begin() && i == 1)
            it++;
        std::cout << "[" << it->first << "]: " << it->second << std::endl;

        if (i == 1) {
            if (it == m.end()) break;
            std::next(it);
        }
        else {
            if (it++ == m.end()) break;
        }
    }
}

void print(std::map<int, std::string>& m) {
    for (const auto& [key, value] : m) {
        std::cout << "[" << key << "]: " << value << std::endl;
    }
}

int main()
{
    srand(time(nullptr));
    std::cout << "Hello World!\n";
    std::cout << "Practuchna #3, made by Drochak Stanislave" << std::endl;
    std::cout << "Main purpose is to count have many times appear each number in 2 dimensional matrix" << std::endl;

    //print(m);

    std::cout << "To start the program: " << std::endl;
    system("pause");
    std::cout << std::endl;

    int rows = 0;
    int columns = 0;

    Matrix::changeSize(rows, columns);

    Matrix m(rows, columns);
    
    bool exit = false;

    do {
        int option = 0;
        int ChangeOption = 0;
        std::vector<std::string> message = { "\nChose option below: ", " Exit - 0,\n count repeats - 1,\n clear out map - 2,\n write to console - 3,\n save to file - 4,\n change size of matrix - 5\n: " };
        CC::CIWithBoundariesCheck(message, option, [](int& v) { if (v < 0 || v > 5) return false; else return true;}, (std::string)("You wrote wrong option"));
        
        switch (option) {
        case 0:
            std::cout << "GoodBye" << std::endl;
            return 0;
        case 1:
            if (!m.getFieldStatus()) {
                int type = 0;
                std::vector<std::string> countMessage = { "Now, chose the way to count amount of repeats: " ,"Multithreads - 0, singleThread - 1: " };
                CC::CIWithBoundariesCheck(countMessage, type, [](int& v) { if (v < 0 || v > 1) return false; else return true;}, (std::string)("You wrote wrong option"));
                std::cout << "Start counting" << std::endl;
                m.parallelCount(type);
                std::cout << "Counting ended" << std::endl;
            }
            else {
                CC::WriteErrorMessage((std::string)("Sorry, but you have to clear out map first"));
            }
            break;
        case 2:
            m.clearOutMap();
            break;
        case 3:
            if (m.getFieldStatus()) {
                std::cout << "In square quotes is number and after it\n goes how many times that number was repeated: " << std::endl;
                std::cout << m << std::endl;
                std::cout << "Write was done" << std::endl;
            }
            else {
                CC::WriteErrorMessage((std::string)("Sorry, but out map is empty, fill it before write into console"));
            }
            break;
        case 4:
            if (m.getFieldStatus()) {
                std::ofstream save("./savedOutMap.map");
                std::cout << "\nIn square quotes is number and after it,\ngoes how many times that number was repeated: " << std::endl;
                save << m;
                std::cout << "Filling was done" << std::endl;
            }
            else {
                CC::WriteErrorMessage((std::string)("Sorry, but out map is empty, fill it before write into file"));
            }
            break;
        case 5:
            message = { "Are you shure to change size? " "It will absolutely clear all data and recreate it!", "No - 0, Yes - 1: " };
            CC::CIWithBoundariesCheck(message, ChangeOption, [](int& v) { if (v < 0 || v > 1) return false; else return true;}, (std::string)("You wrote wrong option"));
            if (ChangeOption == 0) {
                break;
            }
            if (m.getFieldStatus()) {
                m.clearOutMap();
            }
            m.recreateMatrix(); // Dangerous move
            break;
        default:
            break;
        }
    } while (!exit);

    system("pause");
    return 0;
}