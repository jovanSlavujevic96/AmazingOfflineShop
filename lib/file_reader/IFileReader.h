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
    virtual bool read(std::string* line = nullptr) noexcept(false) = 0;

    double extractDouble(std::function<bool(const std::string&, std::string&)> validate = nullptr) noexcept(false);
    float extractFloat(std::function<bool(const std::string&, std::string&)> validate = nullptr) noexcept(false);
    uint64_t extractULongLong(std::function<bool(const std::string&, std::string&)> validate = nullptr) noexcept(false);
    std::string extractString(std::function<bool(const std::string&, std::string&)> validate = nullptr) noexcept(false);

    int getNumOfCols() const;
    void setNumOfCols(int num);
protected:
    std::ifstream mReader;
    int mNumOfCols = 0;

    inline static const std::regex cPositiveNumReg = std::regex(R"(^[0-9]+$)");
    inline static const std::regex cPositiveDecReg = std::regex(R"(^[+]?[0-9]*(?:\.[0-9]*)?$)");

    virtual std::string extract() noexcept(false) = 0;
};
