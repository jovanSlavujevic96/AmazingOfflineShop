#include "IFileReader.h"

double IFileReader::extractDouble(std::function<bool(const std::string&, std::string&)> validate) noexcept(false)
{
    // read cell
    std::string cell = this->extract();

    // remove whitespaces & tabs
    this->eraseCharactersFromString(cell, "\t ", true);

    // remove newline
    this->eraseCharactersFromString(cell, "\r\n", false);

    // validate cell
    if (!std::regex_match(cell, cPositiveDecReg))
    {
        throw std::runtime_error('"' + cell + '"' + " is not a decimal number.");
    }

    // additional validation
    if (validate)
    {
        std::string error;
        if (!validate(cell, error))
        {
            throw std::runtime_error('"' + cell + '"' + " is not valid. " + error);
        }
    }

    // convert to double
    return std::stod(cell);
}

float IFileReader::extractFloat(std::function<bool(const std::string&, std::string&)> validate) noexcept(false)
{
    // read cell
    std::string cell = this->extract();

    // remove whitespaces & tabs
    this->eraseCharactersFromString(cell, "\t ", true);

    // remove newline
    this->eraseCharactersFromString(cell, "\r\n", false);

    // validate third cell
    if (!std::regex_match(cell, cPositiveDecReg))
    {
        throw std::runtime_error('"' + cell + '"' + " is not a decimal number.");
    }

    // additional validation
    if (validate)
    {
        std::string error;
        if (!validate(cell, error))
        {
            throw std::runtime_error('"' + cell + '"' + " is not valid. " + error);
        }
    }

    // convert to float
    return std::stof(cell);
}

uint64_t IFileReader::extractULongLong(std::function<bool(const std::string&, std::string&)> validate) noexcept(false)
{
    // read cell
    std::string cell = this->extract();

    // remove whitespaces & tabs
    this->eraseCharactersFromString(cell, "\t ", true);

    // remove newline
    this->eraseCharactersFromString(cell, "\r\n", false);

    // validate cell
    if (!std::regex_match(cell, cPositiveNumReg))
    {
        throw std::runtime_error('"' + cell + '"' + " is not a natural number.");
    }

    // additional validation
    if (validate)
    {
        std::string error;
        if (!validate(cell, error))
        {
            throw std::runtime_error('"' + cell + '"' + " is not valid. " + error);
        }
    }

    // convert string to int
    return std::stoull(cell);
}

std::string IFileReader::extractString(std::function<bool(const std::string&, std::string&)> validate) noexcept(false)
{
    // read cell
    std::string cell = this->extract();

    // remove whitespaces & tabs
    this->eraseCharactersFromString(cell, "\t ", true);

    // remove newline
    this->eraseCharactersFromString(cell, "\r\n", false);

    // additional validation
    if (validate)
    {
        std::string error;
        if (!validate(cell, error))
        {
            throw std::runtime_error('"' + cell + '"' + " is not valid. " + error);
        }
    }

    return cell;
}

int IFileReader::getNumOfCols() const
{
    return mNumOfCols;
}

void IFileReader::setNumOfCols(int num)
{
    mNumOfCols = num;
}

void IFileReader::eraseCharactersFromString(std::string& str, const char* charGroup, bool front)
{
    // erase indexes
    int eraseStart = -1;
    int eraseEnd = -1;

    // front/back utils
    int step;
    int beginIdx;
    std::function<bool(int)> check;

    // assign utils values
    if (front)
    {
        step = 1;
        beginIdx = 0;
        check = [&](int i)
        {
            return i < (int)str.length();
        };
    }
    else
    {
        step = -1;
        beginIdx = (int)str.length() - 1;
        check = [](int i)
        {
            return i >= 0;
        };
    }

    // iterate through string
    for (int i = beginIdx; check(i); i += step)
    {
        // iterate to character group
        for (int j = 0; j < strlen(charGroup); j++)
        {
            if (str[i] == charGroup[j])
            {
                if (front)
                {
                    if (eraseStart == -1)
                    {
                        eraseStart = i;
                    }
                    eraseEnd = i;
                }
                else
                {
                    if (eraseEnd == -1)
                    {
                        eraseEnd = i;
                    }
                    eraseStart = i;
                }
                break;
            }
        }
        // exit condition
        if (eraseEnd != i && eraseStart != i)
        {
            break;
        }
    }
    if (eraseStart != -1)
    {
        str.erase(eraseStart, eraseEnd + 1);
    }
}
