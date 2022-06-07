#pragma once

#include <regex>

#include "IFileReader.h"

class CsvReader : public IFileReader
{
public:
    explicit CsvReader() = default;
    ~CsvReader() = default;

    void open(std::string filename) noexcept(false) override;
    void close() override;
    bool readLine(std::string* line = nullptr) noexcept(false) override;
private:
    std::string mRow;
    int mRowStartOffset = 0;
    int mRowEndOffset = 0;
    int mColsCounter = 0;

    std::string readCell() noexcept(false) override;
};
