#include <stdexcept>

#include "CsvReader.h"

#define CSV_EXTENSION ".csv"
#define CSV_EXTENSION_LEN 4

void CsvReader::open(std::string filename) noexcept(false)
{
    // validate format (extension) of file
    if (filename.find(CSV_EXTENSION) != filename.length() - CSV_EXTENSION_LEN)
    {
        throw std::runtime_error("Bad format (extension) for file " + filename);
    }

    // close opened file
    if (mReader.is_open())
    {
        mReader.close();
    }

    // open file
    mReader.open(filename);

    // check is file opened
    if (!mReader.is_open())
    {
        throw std::runtime_error("Failed to open file " + filename);
    }
}

bool CsvReader::read(std::string* line) noexcept(false)
{
    if (!mReader.is_open())
    {
        throw std::runtime_error("Can't read row because file is not opened.");
    }

    // reset offsets & counters
    mRowStartOffset = mColsCounter = 0;
    mRowEndOffset = -1;

    // try to read line
    if (std::getline(mReader, mRow))
    {
        // assign to output if it's possible
        if (line)
        {
            line->assign(mRow);
        }
        return true;
    }
    return false;
}

std::string CsvReader::extract() noexcept(false)
{
    // check there are more cells within row
    if (mColsCounter >= mNumOfCols)
    {
        throw std::runtime_error("There are no more cells within a row");
    }

    // set starting offset
    mRowStartOffset = mRowEndOffset + 1;

    // check the range of the cell
    if (mColsCounter == mNumOfCols - 1)
    {
        // set end offset to end of row
        mRowEndOffset = mRow.length();
    }
    else
    {
        // search for semicolon
        const size_t semicolonPos = mRow.find(';', mRowStartOffset);
        if (semicolonPos == std::string::npos)
        {
            mRowEndOffset = -1;
        }
        else
        {
            mRowEndOffset = static_cast<int>(semicolonPos);
        }
    }

    if (mRowStartOffset == mRowEndOffset || mRowEndOffset == -1)
    {
        throw std::runtime_error("Can't find cell");
    }

    // increment columns counter
    mColsCounter++;

    // substring cell
    return mRow.substr(mRowStartOffset, mRowEndOffset - mRowStartOffset);
}
