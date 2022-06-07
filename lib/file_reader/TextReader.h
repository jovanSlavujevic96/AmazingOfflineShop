#pragma once

#include "IFileReader.h"

class TextReader : public IFileReader
{
public:
    explicit TextReader() = default;
    ~TextReader() = default;

    void open(std::string filename) noexcept(false) override;
    void close() override;
    bool readLine(std::string * line = nullptr) noexcept(false) override;

private:
    std::string mLine;
    int mLineStartOffset = 0;
    int mLineEndOffset = 0;
    int mColsCounter = 0;

    std::string readCell() noexcept(false) override;
};
