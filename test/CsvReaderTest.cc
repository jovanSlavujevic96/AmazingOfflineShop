// standard library
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>

// GTest
#include <gtest/gtest.h>

// AmazingAPI
#include <file_reader/CsvReader.h>

TEST(CsvReader_TestSuite, FailedOpen_NonExistingFile)
{
    CsvReader reader;
    const char* filename = "test.csv";

    // make sure that file will not exist
    std::remove(filename);

    // expect reader to throw exception if file doesn't exist
    EXPECT_ANY_THROW(reader.open(filename));
}

TEST(CsvReader_TestSuite, FailedOpen_BadFileExtension)
{
    CsvReader reader;
    const char* filename = "test.txt";

    // create file with ofstream & write some data
    std::ofstream writer(filename);
    writer << "test\t;test\t;test\t";
    writer.close();

    // expect reader to throw exception if file exists, but has bad extension (".txt")
    EXPECT_ANY_THROW(reader.open(filename));

    // make sure that file has been deleted
    std::remove(filename);
}

TEST(CsvReader_TestSuite, SuccedOpen_SingleCsvFile)
{
    CsvReader reader;
    const char* filename = "test.csv";

    // create file with ofstream & write some data & close
    std::ofstream writer(filename);
    writer << "test" ";\t" "test" ";\t" "test";
    writer.close();

    // expect reader not to throw exception if file exists & has good extension
    EXPECT_NO_THROW(reader.open(filename));

    // make sure that file has been deleted
    std::remove(filename);
}

TEST(CsvReader_TestSuite, SuccedOpen_MultipleCsvFiles)
{
    CsvReader reader;
    const char* filenames[] = { "test1.csv", "test2.csv", "test3.csv" };

    for (const char* filename : filenames)
    {
        // create file with ofstream & write some data
        std::ofstream writer(filename);
        writer << "test" ";\t" "test" ";\t" "test";
    }

    for (const char* filename : filenames)
    {
        // expect reader not to throw exception if file exists & has good extension
        // even if reader has opened previous file (he closed it)
        EXPECT_NO_THROW(reader.open(filename));
    }

    for (const char* filename : filenames)
    {
        // make sure that file has been deleted
        std::remove(filename);
    }
}

TEST(CsvReader_TestSuite, FailedRead_IfFileNotOpened)
{
    CsvReader reader;
    const char* filename = "test.csv";

    // create file with ofstream & write some data
    std::ofstream writer(filename);
    writer << "test" ";\t" "test" ";\t" "test";
    writer.close();

    // don't open the file with reader

    // expect reader to throw exception because file is not opened
    EXPECT_ANY_THROW(reader.read());

    // make sure that file has been deleted
    std::remove(filename);
}

TEST(CsvReader_TestSuite, FailedRead_IfFileIsEmpty)
{
    CsvReader reader;
    const char* filename = "test.csv";

    // create file with ofstream & close it
    std::ofstream writer(filename);
    writer.close();

    // open the file with reader
    reader.open(filename);

    // expect reader not to throw exception & to return false, because file is empty
    EXPECT_NO_THROW(EXPECT_FALSE(reader.read()));

    // make sure that file has been deleted
    std::remove(filename);
}

TEST(CsvReader_TestSuite, SucceedRead_IfNullArgument)
{
    CsvReader reader;
    const char* filename = "test.csv";

    // create file with ofstream & close it
    std::ofstream writer(filename);
    writer << "test" ";\t" "test" ";\t" "test";
    writer.close();

    // open the file with reader
    reader.open(filename);

    // expect reader not to throw exception & to return true
    EXPECT_NO_THROW(EXPECT_TRUE(reader.read(nullptr)));

    // make sure that file has been deleted
    std::remove(filename);
}

TEST(CsvReader_TestSuite, SucceedRead_CheckSingleLine)
{
    CsvReader reader;
    const char* filename = "test.csv";
    const std::string input = "test" ";\t" "test" ";\t" "test";
    std::string output;

    // create file with ofstream, write data & close it
    std::ofstream writer(filename);
    writer << input;
    writer.close();

    // open the file with reader
    reader.open(filename);

    // expect reader to read the line & store it to output
    EXPECT_TRUE(reader.read(&output));
    EXPECT_TRUE(input == output);

    // make sure that file has been deleted
    std::remove(filename);
}

TEST(CsvReader_TestSuite, SucceedRead_CheckMultipleLines)
{
    CsvReader reader;
    const char* filename = "test.csv";
    const std::vector<std::string> inputs =
    {
        "TEST; \t TEST; \t TEST; #123",
        "TEST; \t TEST; \t TEST; #312",
        "TEST; \t TEST; \t TEST; #231",
    };
    std::string output;

    // create file with ofstream, write data in multiple lines & close it
    std::ofstream writer(filename);
    for (const std::string& input : inputs)
    {
        writer << input << std::endl;
    }
    writer.close();

    // open the file with reader
    reader.open(filename);

    // expect reader to read the lines & store them to the output
    for (const std::string& input : inputs)
    {
        EXPECT_TRUE(reader.read(&output));
        EXPECT_TRUE(input == output);
    }

    // make sure that file has been deleted
    std::remove(filename);
}

TEST(CsvReader_TestSuite, FailedExtractULongLong_ZeroColumns)
{
    CsvReader reader;
    const char* filename = "test.csv";
    const std::string input = "1000";

    reader.setNumOfCols(0);

    // create file with ofstream, write data & close it
    std::ofstream writer(filename);
    writer << input;
    writer.close();

    // open the file with reader & read line
    reader.open(filename);
    reader.read();

    // expect reader to throw exception because input is not just a number
    EXPECT_ANY_THROW(reader.extractULongLong());

    // make sure that file has been deleted
    std::remove(filename);
}

TEST(CsvReader_TestSuite, FailedExtractULongLong_NonDigitCharacters)
{
    CsvReader reader;
    const char* filename = "test.csv";
    const std::string input = "1000Test";

    reader.setNumOfCols(1);

    // create file with ofstream, write data & close it
    std::ofstream writer(filename);
    writer << input;
    writer.close();

    // open the file with reader & read line
    reader.open(filename);
    reader.read();

    // expect reader to throw exception because input is not just a number
    EXPECT_ANY_THROW(reader.extractULongLong());

    // make sure that file has been deleted
    std::remove(filename);
}

TEST(CsvReader_TestSuite, SucceedExtractULongLong_SingleColumn)
{
    CsvReader reader;
    const char* filename = "test.csv";
    const uint64_t input = 555333;

    reader.setNumOfCols(1);

    // create file with ofstream, write data & close it
    std::ofstream writer(filename);
    writer << std::to_string(input);
    writer.close();

    // open the file with reader & read line
    reader.open(filename);
    reader.read();

    // expect reader not to throw exception because input is just a number
    EXPECT_NO_THROW(EXPECT_TRUE(reader.extractULongLong() == input));

    // make sure that file has been deleted
    std::remove(filename);
}

TEST(CsvReader_TestSuite, SucceedExtract_MultipleColumns)
{
    CsvReader reader;
    const char* filename = "test.csv";
    constexpr uint64_t inputULong = 555333;
    constexpr float inputFloat = 5.5f;
    constexpr double inputDouble = 3.300452;
    const std::string inputString = "Hello world";

    reader.setNumOfCols(4);

    // create file with ofstream, write data & close it
    std::ofstream writer(filename);
    writer << std::to_string(inputULong) << ";\t" << std::to_string(inputFloat) << ";\t\t";
    writer << std::to_string(inputDouble) << ";\t" << inputString;
    writer.close();

    // open the file with reader & read line
    reader.open(filename);
    reader.read();

    // expect raeder to read good values
    EXPECT_TRUE(reader.extractULongLong() == inputULong);
    EXPECT_TRUE(reader.extractFloat() == inputFloat);
    EXPECT_TRUE(reader.extractDouble() == inputDouble);
    EXPECT_TRUE(reader.extractString() == inputString);

    // make sure that file has been deleted
    std::remove(filename);
}

TEST(CsvReader_TestSuite, SucceedExtract_CrLfNewline)
{
    CsvReader reader;
    const char* filename = "test.csv";
    constexpr uint64_t inputULong = 555333;
    constexpr float inputFloat = 5.5f;
    constexpr double inputDouble = 3.300452;
    const std::string inputString = "Hello world";

    reader.setNumOfCols(4);

    // create file with ofstream, write data, end line with carriage return + line feed & close it
    std::ofstream writer(filename);
    writer << inputString << ";\t" << std::to_string(inputFloat) << ";\t\t";
    writer << std::to_string(inputDouble) << ";\t" << std::to_string(inputULong) << "\r\n";
    writer.close();

    // open the file with reader & read line
    reader.open(filename);
    reader.read();

    // expect raeder to read good values
    EXPECT_TRUE(reader.extractString() == inputString);
    EXPECT_TRUE(reader.extractFloat() == inputFloat);
    EXPECT_TRUE(reader.extractDouble() == inputDouble);
    EXPECT_TRUE(reader.extractULongLong() == inputULong);

    // make sure that file has been deleted
    std::remove(filename);
}
