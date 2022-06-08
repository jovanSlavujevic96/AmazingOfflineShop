// standard library
#include <string>
#include <fstream>
#include <cstdint>
#include <memory>

// GTest
#include <gtest/gtest.h>

// AmazingAPI
#include <objects/Items.h>
#include <file_reader/CsvReader.h>

TEST(Items_TestSuite, CompareItemsWithDifferentFields)
{
    const Item a = {"test1", 112.453, 1.18f};
    const Item b = {"test2", 15.02,   1.18f};

    EXPECT_NE(a, b);
}

TEST(Items_TestSuite, CompareItemsWithSameFields)
{
    const Item a = {"test1", 112.453, 1.18f};
    const Item b = {"test1", 112.453, 1.18f};

    EXPECT_EQ(a, b);
}

TEST(Items_TestSuite, CompareSameItem)
{
    const Item a = {"test1", 112.453, 1.18f};

    EXPECT_EQ(a, a);
}

TEST(Items_TestSuite, FailedDeserialization_InvalidEan13)
{
    Items items;
    std::shared_ptr<CsvReader> reader(new CsvReader);
    const char* filename = "test.csv";

    // create file with ofstream & write some data
    std::ofstream writer(filename);
    writer << "44324413730;\tCoca-Cola;\t1.21;\t3.5";
    writer.close();

    // open file with reader
    reader->open(filename);

    // expect reader to throw exception due to EAN 13 validation
    EXPECT_ANY_THROW(items << reader);

    // make sure that file has been deleted
    std::remove(filename);
}

TEST(Items_TestSuite, FailedDeserialization_InvalidPriceWoTax)
{
    Items items;
    std::shared_ptr<CsvReader> reader(new CsvReader);
    const char* filename = "test.csv";

    // create file with ofstream & write some data
    std::ofstream writer(filename);
    writer << "4432441693730;\tCoca-Cola;\tSH1.2f1fX;\t3.5";
    writer.close();

    // open file with reader
    reader->open(filename);

    // expect reader to throw exception due to price validation
    EXPECT_ANY_THROW(items << reader);

    // make sure that file has been deleted
    std::remove(filename);
}

TEST(Items_TestSuite, FailedDeserialization_InvalidTaxPercent)
{
    Items items;
    std::shared_ptr<CsvReader> reader(new CsvReader);
    const char* filename = "test.csv";

    // create file with ofstream & write some data
    std::ofstream writer(filename);
    writer << "4432441693730;\tCoca-Cola;\t1.21;\t33H1F5.0";
    writer.close();

    // open file with reader
    reader->open(filename);

    // expect reader to throw exception due to tax validation
    EXPECT_ANY_THROW(items << reader);

    // make sure that file has been deleted
    std::remove(filename);
}

TEST(Items_TestSuite, SucceedDeserialization_WithoutException)
{
    Items items;
    std::shared_ptr<CsvReader> reader(new CsvReader);
    const char* filename = "test.csv";

    // create file with ofstream & write some data
    std::ofstream writer(filename);
    writer << "4432441693730;\tCoca-Cola;\t1.21;\t3.5";
    writer.close();

    // open file with reader
    reader->open(filename);

    // expect reader not to throw exception during deserialization
    EXPECT_NO_THROW(items << reader);

    // make sure that file has been deleted
    std::remove(filename);
}

TEST(Items_TestSuite, SucceedDeserialization_SingleLineCheck)
{
    Items items;
    std::shared_ptr<CsvReader> reader(new CsvReader);
    const char* filename = "test.csv";
    const uint64_t ean13 = 4432441693730;
    const Item comparingItem = {"Coca-Cola", 1.21, 3.5};

    // create file with ofstream & write some data
    std::ofstream writer(filename);
    writer << ean13 << ";\t" << comparingItem.name << ";\t" << comparingItem.priceWoTax << ";\t" << comparingItem.taxPercent;
    writer.close();

    // open file with reader
    reader->open(filename);
    items << reader;

    // expect NULL for passed bad EAN 13 id
    EXPECT_EQ(items.getItem(ean13 + 1), nullptr);

    // compare deserialized item with initial
    EXPECT_EQ(*items.getItem(ean13), comparingItem);

    // make sure that file has been deleted
    std::remove(filename);
}
