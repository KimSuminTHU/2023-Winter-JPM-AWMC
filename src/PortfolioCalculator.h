#ifndef PORTFOLIO_CALCULATOR_H
#define PORTFOLIO_CALCULATOR_H

#include <vector>
#include <string>
#include <utility>

class PortfolioCalculator {
public:
    PortfolioCalculator(const std::vector<std::vector<double>>& correlationMatrix,
                        const std::vector<double>& expectedReturns,
                        const std::vector<double>& volatilities);
    
    std::pair<double, double> calculatePortfolioMetrics(const std::vector<int>& portfolio) const;
    
    std::vector<std::pair<std::vector<int>, std::pair<double, double>>> 
    findPortfolios(int numAssets, double targetReturnMin, double targetReturnMax, 
                   double targetVolatilityMin, double targetVolatilityMax) const;

private:
    std::vector<std::vector<double>> correlationMatrix_;
    std::vector<double> expectedReturns_;
    std::vector<double> volatilities_;

    void generateCombinations(int offset, int k, std::vector<int>& current, 
                              std::vector<std::vector<int>>& combinations) const;
};

#endif
