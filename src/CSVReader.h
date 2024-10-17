#ifndef CSV_READER_H
#define CSV_READER_H

#include <vector>
#include <string>

class CSVReader {
public:
    static std::vector<std::vector<std::string>> readCSV(const std::string& filename);
    static std::vector<std::vector<double>> readDoubleCSV(const std::string& filename);
};

#endif
