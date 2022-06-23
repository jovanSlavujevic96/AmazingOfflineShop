// standard library
#include <string>
#include <fstream>
#include <cstdint>
#include <memory>

// GTest
#include <gtest/gtest.h>

// AmazingAPI
#include <objects/Items.h>
#include <objects/Orders.h>
#include <objects/ProcessedOrders.h>
#include <objects/Discounts.h>
#include <file_reader/CsvReader.h>

TEST(ProcessOrders_TestSuite, CompareProcOrdersWithDifferentFields)
{
    const ProcessedOrder a = {1.11f, 1.21f, 3.0f, 15.67, 115.67};
    const ProcessedOrder b = {1.21f, 1.11f, 3.0f, 15.67, 115.67};

    EXPECT_NE(a, b);
}

TEST(ProcessOrders_TestSuite, CompareProcOrdersWithSameFields)
{
    const ProcessedOrder a = {1.11f, 1.21f, 3.0f, 15.67, 115.67};
    const ProcessedOrder b = {1.11f, 1.21f, 3.0f, 15.67, 115.67};

    EXPECT_EQ(a, b);
}

TEST(ProcessOrders_TestSuite, CompareSameProceOrder)
{
    const ProcessedOrder a = {1.11f, 1.21f, 3.0f, 15.67, 115.67};

    EXPECT_EQ(a, a);
}

TEST(ProcessOrders_TestSuite, ProcessOrderFailure_NullOrders)
{
    std::shared_ptr<CsvReader> reader(new CsvReader);
    const char* item_filename = "test_item.csv";
    const char* discount_filename = "test_discount.csv";
    std::ofstream writer;
    Items item;
    Discounts discount;

    // create file with ofstream & write some data for item
    writer.open(item_filename);
    writer << "5720092407427;\t \t \tFanta;\t1.21;\t3.5" << std::endl;
    writer.close();

    reader->open(item_filename);
    ASSERT_NO_THROW(item << reader);

    // create file with ofstream & write some data for discount
    writer.open(discount_filename);
    writer << "5720092407427;\t\t5.12\r\n";
    writer.close();

    reader->open(discount_filename);
    ASSERT_NO_THROW(discount << reader);

    // create discount 
    ProcessedOrders proc;
    EXPECT_ANY_THROW(proc.processOrder(nullptr, &item, &discount));

    // make sure that file has been deleted
    std::remove(discount_filename);
    std::remove(item_filename);
}

TEST(ProcessOrders_TestSuite, ProcessOrderFailure_NullItems)
{
    std::shared_ptr<CsvReader> reader(new CsvReader);
    const char* discount_filename = "test_discount.csv";
    const char* order_filename = "test_order.csv";
    std::ofstream writer;
    Discounts discount;
    Orders order;

    // create file with ofstream & write some data for order
    writer.open(order_filename);
    writer << "5720092407427;\t\t1.00\r\n";
    writer.close();

    reader->open(order_filename);
    ASSERT_NO_THROW(order << reader);

    // create file with ofstream & write some data for discount
    writer.open(discount_filename);
    writer << "5720092407427;\t\t5.12\r\n";
    writer.close();

    reader->open(discount_filename);
    ASSERT_NO_THROW(discount << reader);

    // create discount 
    ProcessedOrders proc;
    EXPECT_ANY_THROW(proc.processOrder(&order, nullptr, &discount));

    // make sure that file has been deleted
    std::remove(discount_filename);
    std::remove(order_filename);
}

TEST(ProcessOrders_TestSuite, ProcessOrderSucceed_NullDiscounts)
{
    std::shared_ptr<CsvReader> reader(new CsvReader);
    const char* item_filename = "test_item.csv";
    const char* order_filename = "test_order.csv";
    std::ofstream writer;
    Items item;
    Orders order;

    // create file with ofstream & write some data for order
    writer.open(order_filename);
    writer << "5720092407427;\t\t1.00\r\n";
    writer.close();

    reader->open(order_filename);
    ASSERT_NO_THROW(order << reader);

    // create file with ofstream & write some data for item
    writer.open(item_filename);
    writer << "5720092407427;\t \t \tFanta;\t1.21;\t3.5" << std::endl;
    writer.close();

    reader->open(item_filename);
    ASSERT_NO_THROW(item << reader);

    // create discount 
    ProcessedOrders proc;
    EXPECT_NO_THROW(proc.processOrder(&order, &item, nullptr));

    auto procOrder = proc.getProcessedOrder("Fanta");

    ASSERT_TRUE(procOrder != nullptr);
    EXPECT_EQ(procOrder->discountPercent, 0);
    EXPECT_EQ(procOrder->quantity, 1.00f);
    EXPECT_EQ(procOrder->taxPercent, 3.5f);
    EXPECT_EQ(procOrder->unitPrice, 1.21 * (1.0f + procOrder->taxPercent/100));
    EXPECT_EQ(procOrder->finalPrice, procOrder->unitPrice * procOrder->quantity);

    // make sure that file has been deleted
    std::remove(item_filename);
    std::remove(order_filename);
}

TEST(ProcessOrders_TestSuite, ProcessOrderSucceed_IncludingDiscounts)
{
    std::shared_ptr<CsvReader> reader(new CsvReader);
    const char* item_filename = "test_item.csv";
    const char* order_filename = "test_order.csv";
    const char* discount_filename = "test_discount.csv";
    std::ofstream writer;
    Items item;
    Orders order;
    Discounts discount;

    // create file with ofstream & write some data for order
    writer.open(order_filename);
    writer << "5720092407427;\t\t1.00\r\n";
    writer.close();

    reader->open(order_filename);
    ASSERT_NO_THROW(order << reader);

    // create file with ofstream & write some data for item
    writer.open(item_filename);
    writer << "5720092407427;Fanta;\t1.21;\t\t3.5";
    writer.close();

    reader->open(item_filename);
    ASSERT_NO_THROW(item << reader);

    // create file with ofstream & write some data for discount
    writer.open(discount_filename);
    writer << "5720092407427;\t\t5.12\r\r\n";
    writer.close();

    reader->open(discount_filename);
    ASSERT_NO_THROW(discount << reader);

    // create discount 
    ProcessedOrders proc;
    EXPECT_NO_THROW(proc.processOrder(&order, &item, &discount));

    auto procOrder = proc.getProcessedOrder("Fanta");

    ASSERT_TRUE(procOrder != nullptr);
    EXPECT_EQ(procOrder->discountPercent, 5.12f);
    EXPECT_EQ(procOrder->quantity, 1.00f);
    EXPECT_EQ(procOrder->taxPercent, 3.5f);
    EXPECT_EQ(procOrder->unitPrice, 1.21 * (1.0f + procOrder->taxPercent/100) * (1.0f - procOrder->discountPercent/100));
    EXPECT_EQ(procOrder->finalPrice, procOrder->unitPrice * procOrder->quantity);

    // make sure that file has been deleted
    std::remove(item_filename);
    std::remove(order_filename);
    std::remove(discount_filename);
}
