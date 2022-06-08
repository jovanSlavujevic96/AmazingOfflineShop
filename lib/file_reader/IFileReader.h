/**
 * @file IFileReader.h
 * @author Jovan Slavujevic (slavujevic.jovan.96@gmail.com)
 * @brief IFileReader interface definition
 * @version 0.1
 * @date 2022-06-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <fstream>
#include <regex>
#include <string>
#include <cstdint>
#include <functional>

/**
 * @brief File Reader Interface class
 *        handles read of lines and extraction of cells in various data formats
 */
class IFileReader
{
public:
    /**
     * @brief Construct a new IFileReader object
     */
    explicit IFileReader() = default;
    /**
     * @brief Destroy the IFileReader object
     */
    virtual ~IFileReader() = default;

    /**
     * @brief Method which tries to open file
     *
     * @exception std::runtime_error - if open file has failed
     *
     * @param[in] filename - file to read
     */
    virtual void open(std::string filename) noexcept(false) = 0;
    /**
     * @brief Method which reads line within file.
     *        It shall read next line every time until EOF.
     *
     * @exception std::runtime_error if file is not opened
     *
     * @param[out] line - external storage for readen line (optional/nullable)
     * @return true - line succesfully read
     * @return false - EOF
     */
    virtual bool read(std::string* line = nullptr) noexcept(false) = 0;

    /**
     * @brief Method which extracts cell from line, expecting decimal number
     *
     * @exception std::runtime_error internal or external validation failure
     *
     * @param[in] validate - external validation function (optional/nullable)
     * @return double - data within cell converted in double
     */
    double extractDouble(std::function<bool(const std::string&, std::string&)> validate = nullptr) noexcept(false);
    /**
     * @brief Method which extracts cell from line, expecting decimal number
     *
     * @exception std::runtime_error internal or external validation failure
     *
     * @param[in] validate - external validation function (optional/nullable)
     * @return float - data within cell converted in float
     */
    float extractFloat(std::function<bool(const std::string&, std::string&)> validate = nullptr) noexcept(false);
    /**
     * @brief Method which extracts cell from line, expecting positive number (or zero)
     *
     * @exception std::runtime_error internal or external validation failure
     *
     * @param[in] validate - external validation function (optional/nullable)
     * @return uint64_t - data within cell converted in uint64_t
     */
    uint64_t extractULongLong(std::function<bool(const std::string&, std::string&)> validate = nullptr) noexcept(false);
    /**
     * @brief Method which extracts cell from line and places it into string
     *
     * @exception std::runtime_error on external validation failure
     *
     * @param[in] validate - external validation function (optional/nullable)
     * @return std::string - data within cell converted in string format
     */
    std::string extractString(std::function<bool(const std::string&, std::string&)> validate = nullptr) noexcept(false);

    /**
     * @brief Get the number of columns
     *
     * @return int - number of columns
     */
    int getNumOfCols() const;
    /**
     * @brief Set the number of columns
     *
     * @param[in] num - number of columns to set
     */
    void setNumOfCols(int num);
protected:
    /**
     * @brief file reader
     */
    std::ifstream mReader;
    /**
     * @brief number of columns within a row/line 
     */
    int mNumOfCols = 0;

    /**
     * @brief regex internal validator for positive numbers
     */
    inline static const std::regex cPositiveNumReg = std::regex(R"(^[0-9]+$)");
    /**
     * @brief regex internal validator for positive decimal number
     */
    inline static const std::regex cPositiveDecReg = std::regex(R"(^[+]?[0-9]*(?:\.[0-9]*)?$)");

    /**
     * @brief Method which extracts cell from line and leaves it in raw (including whitespaces, etc.)
     *
     * @return std::string extracted cell
     */
    virtual std::string extract() noexcept(false) = 0;
};
