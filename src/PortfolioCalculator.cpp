#include "PortfolioCalculator.h"
#include <cmath>
#include <algorithm>
#include <iostream>

// 생성자
PortfolioCalculator::PortfolioCalculator(const std::vector<std::vector<double>>& correlationMatrix,
                                         const std::vector<double>& expectedReturns,
                                         const std::vector<double>& volatilities)
    : correlationMatrix_(correlationMatrix), expectedReturns_(expectedReturns), volatilities_(volatilities) {}

// 포트폴리오의 수익률 및 변동성 계산
std::pair<double, double> PortfolioCalculator::calculatePortfolioMetrics(const std::vector<int>& portfolio) const {
    double portfolioReturn = 0.0;
    double portfolioVariance = 0.0;
    
    // 포트폴리오의 기대 수익률 계산
    for (int asset : portfolio) {
        portfolioReturn += expectedReturns_[asset];
    }
    portfolioReturn /= portfolio.size();  // 평균 수익률
    
    // 포트폴리오의 분산 계산
    for (int i = 0; i < portfolio.size(); ++i) {
        for (int j = 0; j < portfolio.size(); ++j) {
            int asset_i = portfolio[i];
            int asset_j = portfolio[j];
            portfolioVariance += volatilities_[asset_i] * volatilities_[asset_j] * correlationMatrix_[asset_i][asset_j];
        }
    }
    portfolioVariance /= (portfolio.size() * portfolio.size());
    double portfolioVolatility = std::sqrt(portfolioVariance);
    
    return {portfolioReturn, portfolioVolatility};
}

// 모든 자산의 조합을 생성하는 함수 (조합 생성)
void PortfolioCalculator::generateCombinations(int offset, int k, 
                                               std::vector<int>& current, 
                                               std::vector<std::vector<int>>& combinations) const {
    if (k == 0) {
        combinations.push_back(current);
        return;
    }
    for (int i = offset; i <= expectedReturns_.size() - k; ++i) {
        current.push_back(i);
        generateCombinations(i + 1, k - 1, current, combinations);
        current.pop_back();
    }
}

// 조건에 맞는 포트폴리오를 찾는 함수
std::vector<std::pair<std::vector<int>, std::pair<double, double>>> 
PortfolioCalculator::findPortfolios(int numAssets, double targetReturnMin, double targetReturnMax, 
                                    double targetVolatilityMin, double targetVolatilityMax) const {
    std::vector<std::pair<std::vector<int>, std::pair<double, double>>> validPortfolios;
    std::vector<std::vector<int>> combinations;
    std::vector<int> current;
    
    // numAssets 개수의 자산 조합 생성
    generateCombinations(0, numAssets, current, combinations);
    
    // 각 조합에 대해 포트폴리오 수익률 및 변동성 계산
    for (const auto& portfolio : combinations) {
        auto [portfolioReturn, portfolioVolatility] = calculatePortfolioMetrics(portfolio);
        
        // 주어진 수익률 및 변동성 범위에 해당하는지 확인
        if (portfolioReturn >= targetReturnMin && portfolioReturn <= targetReturnMax &&
            portfolioVolatility >= targetVolatilityMin && portfolioVolatility <= targetVolatilityMax) {
            validPortfolios.push_back({portfolio, {portfolioReturn, portfolioVolatility}});
        }
    }
    
    return validPortfolios;
}
