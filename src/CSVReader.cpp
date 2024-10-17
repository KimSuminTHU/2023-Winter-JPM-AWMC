#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

// CSV 파일을 문자열로 읽기
std::vector<std::vector<std::string>> CSVReader::readCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file " + filename);
    }

    std::vector<std::vector<std::string>> data;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    return data;
}

// CSV 파일을 숫자로 읽기
std::vector<std::vector<double>> CSVReader::readDoubleCSV(const std::string& filePath) {
    std::vector<std::vector<double>> data;
    std::ifstream file(filePath);
    
    // 파일 열기 실패 시 예외 발생
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + filePath);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string value;
        std::vector<double> row;

        while (std::getline(ss, value, ',')) {
            // 공백 제거
            value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());
            try {
                if (!value.empty()) {
                    // 문자열을 double로 변환
                    row.push_back(std::stod(value));
                } else {
                    throw std::invalid_argument("Empty value found");
                }
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error parsing value: '" << value << "' in line: " << line << std::endl;
                throw std::runtime_error("Error parsing CSV file " + filePath + ": " + e.what());
            } catch (const std::out_of_range& e) {
                std::cerr << "Value out of range: '" << value << "' in line: " << line << std::endl;
                throw std::runtime_error("Error parsing CSV file " + filePath + ": " + e.what());
            }
        }

        if (!row.empty()) {
            data.push_back(row);
        }
    }

    return data;
}