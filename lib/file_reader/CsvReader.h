/**
 * @file CsvReader.h
 * @author Jovan Slavujevic (slavujevic.jovan.96@gmail.com)
 * @brief CsvReader class definition
 * @version 0.1
 * @date 2022-06-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <regex>

#include "IFileReader.h"

/**
 * @brief CSV File Reader class
 *        handles read of rows and extraction of cells in various data formats
 */
class CsvReader : public IFileReader
{
public:
    /**
     * @brief Construct a new CsvReader object
     */
    explicit CsvReader() = default;
    /**
     * @brief Destroy the CsvReader object
     */
    ~CsvReader() = default;

    /**
     * @brief Method which tries to open file
     *
     * @exception std::runtime_error - if open file has failed
     *
     * @param[in] filename - file to read
     */
    void open(std::string filename) noexcept(false) override;
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
    bool read(std::string* line = nullptr) noexcept(false) override;
private:
    /**
     * @brief row storage 
     */
    std::string mRow;
    /**
     * @brief row / colums offsets
     */
    int mRowStartOffset = 0;
    int mRowEndOffset = 0;
    int mColsCounter = 0;

    /**
     * @brief Method which extracts cell from line and leaves it in raw (including whitespaces, etc.)
     *
     * @return std::string extracted cell
     */
    std::string extract() noexcept(false) override;
};
