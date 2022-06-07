#pragma once

#include <fstream>
#include <regex>
#include <string>
#include <cstdint>
#include <functional>

class IFileReader
{
public:
    explicit IFileReader() = default;
    virtual ~IFileReader() = default;

    virtual void open(std::string filename) noexcept(false) = 0;
    virtual void close() = 0;
    virtual bool readLine(std::string* line = nullptr) noexcept(false) = 0;

    double readDoubleCell(std::function<bool(const std::string&, std::string&)> validate = nullptr) noexcept(false);
    float readFloatCell(std::function<bool(const std::string&, std::string&)> validate = nullptr) noexcept(false);
    uint64_t readULongLongCell(std::function<bool(const std::string&, std::string&)> validate = nullptr) noexcept(false);
    std::string readStringCell(std::function<bool(const std::string&, std::string&)> validate = nullptr) noexcept(false);

    int getNumOfCols() const;
    void setNumOfCols(int num);
protected:
    std::ifstream mReader;
    int mNumOfCols = 0;

    inline static const std::regex cPositiveNumReg = std::regex(R"(^[0-9]+$)");
    inline static const std::regex cPositiveDecReg = std::regex(R"(^[+]?[0-9]*(?:\.[0-9]*)?$)");

    virtual std::string readCell() noexcept(false) = 0;
    void eraseWhitespacesFromString(std::string& str);
};
