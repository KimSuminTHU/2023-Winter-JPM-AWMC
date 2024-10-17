#include "PortfolioCalculator.h"
#include "CSVReader.h"
#include "MatrixUtils.h"
#include <iostream>
#include <fstream>
#include <string>

// 결과를 콘솔에 출력하고 파일로 저장하는 함수
void outputResults(const std::vector<std::pair<std::vector<int>, std::pair<double, double>>>& results, 
                   const std::string& outputFile) {
    // 콘솔에 결과 출력
    for (const auto& result : results) {
        std::cout << "Assets: ";
        for (int asset : result.first) {
            std::cout << asset << " ";
        }
        std::cout << "| Return: " << result.second.first << ", Volatility: " << result.second.second << std::endl;
    }

    // 파일에 결과 저장
    std::ofstream file(outputFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << outputFile << " for writing." << std::endl;
        return;
    }

    file << "Assets,Return,Volatility\n";
    for (const auto& result : results) {
        for (int asset : result.first) {
            file << asset << " ";
        }
        file << "," << result.second.first << "," << result.second.second << "\n";
    }

    file.close();
    std::cout << "Results saved to " << outputFile << std::endl;
}

int main() {
    try {
        std::string assetTypeFile, correlationFile, returnVolatilityFile;

        // CSV 파일 경로 입력받기
        std::string defaultAssetTypeFile = "../data/Asset_Type_strings.csv";
        std::string defaultCorrelationFile = "../data/Correlation_Sheet_numbers.csv";
        std::string defaultReturnVolatilityFile = "../data/Return_Volatility_numbers.csv";

        std::cout << "Enter the path for Asset_Type_strings.csv (or press Enter to use default): ";
        std::getline(std::cin, assetTypeFile);
        if (assetTypeFile.empty()) {
            assetTypeFile = defaultAssetTypeFile;
        }

        std::cout << "Enter the path for Correlation_Sheet_numbers.csv (or press Enter to use default): ";
        std::getline(std::cin, correlationFile);
        if (correlationFile.empty()) {
            correlationFile = defaultCorrelationFile;
        }

        std::cout << "Enter the path for Return_Volatility_numbers.csv (or press Enter to use default): ";
        std::getline(std::cin, returnVolatilityFile);
        if (returnVolatilityFile.empty()) {
            returnVolatilityFile = defaultReturnVolatilityFile;
        }

        // 결과 출력
        std::cout << "Asset Type File: " << assetTypeFile << std::endl;
        std::cout << "Correlation File: " << correlationFile << std::endl;
        std::cout << "Return Volatility File: " << returnVolatilityFile << std::endl;

        // CSV 파일 읽기
        auto assetTypes = CSVReader::readCSV(assetTypeFile);
        auto correlationData = CSVReader::readDoubleCSV(correlationFile);
        auto returnVolatilityData = CSVReader::readDoubleCSV(returnVolatilityFile);

        // 대칭 상관관계 행렬 생성
        auto correlationMatrix = MatrixUtils::buildSymmetricMatrix(correlationData);

        // 자산의 기대 수익률 및 변동성 추출
        std::vector<double> expectedReturns, volatilities;
        for (const auto& row : returnVolatilityData) {
            expectedReturns.push_back(row[1]);   // Arithmetic Return 2024(%)
            volatilities.push_back(row[2]);      // Annualized Volatility
        }

        // 포트폴리오 계산기 생성
        PortfolioCalculator calculator(correlationMatrix, expectedReturns, volatilities);

        // 사용자 입력 받기
        int numAssets;
        double targetReturnMin, targetReturnMax, targetVolatilityMin, targetVolatilityMax;

        std::cout << "Enter the number of assets for the portfolio: ";
        std::cin >> numAssets;

        std::cout << "Enter the minimum target return: ";
        std::cin >> targetReturnMin;

        std::cout << "Enter the maximum target return: ";
        std::cin >> targetReturnMax;

        std::cout << "Enter the minimum target volatility: ";
        std::cin >> targetVolatilityMin;

        std::cout << "Enter the maximum target volatility: ";
        std::cin >> targetVolatilityMax;

        // 조건에 맞는 포트폴리오 찾기
        auto results = calculator.findPortfolios(numAssets, targetReturnMin, targetReturnMax, targetVolatilityMin, targetVolatilityMax);

        // 결과 출력 및 파일로 저장
        std::string outputFile = "results.csv";
        outputResults(results, outputFile);

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
