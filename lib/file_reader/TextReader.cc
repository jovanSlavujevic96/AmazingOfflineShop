#include "TextReader.h"

#define TXT_EXTENSION ".txt"
#define TXT_EXTENSION_LEN 4

void TextReader::open(std::string filename) noexcept(false)
{
    // validate format (extension) of file
    if (filename.find(TXT_EXTENSION) != filename.length() - TXT_EXTENSION_LEN)
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

void TextReader::close()
{
    // close opened file
    mReader.close();
}

bool TextReader::readLine(std::string* line) noexcept(false)
{
    if (!mReader.is_open())
    {
        throw std::runtime_error("Can't read row because file is not opened.");
    }

    // reset offsets & counters
    mLineStartOffset = mColsCounter = 0;
    mLineEndOffset = -1;

    // try to read line
    if (std::getline(mReader, mLine))
    {
        // assign to output if it's possible
        if (line)
        {
            line->assign(mLine);
        }
        return true;
    }
    return false;
}

std::string TextReader::readCell() noexcept(false)
{
    // check there are more cells within row
    if (mColsCounter >= mNumOfCols)
    {
        throw std::runtime_error("There are no more cells within a row");
    }

    // set starting offset
    mLineStartOffset = mLineEndOffset + 1;

    // check the range of the cell
    if (mColsCounter == mNumOfCols - 1)
    {
        // set end offset to end of row
        mLineEndOffset = mLine.length();
    }
    else
    {
        // search for end of cell
        mLineEndOffset = mLine.find(' ', mLineStartOffset);
        if (mLineEndOffset == std::string::npos)
        {
            mLineEndOffset = mLine.find('\t', mLineStartOffset);
        }
        if (mLineEndOffset == std::string::npos)
        {
            throw std::runtime_error("Can't find cell");
        }
    }

    // increment columns counter
    mColsCounter++;

    // substring cell
    return mLine.substr(mLineStartOffset, mLineEndOffset - mLineStartOffset);
}
