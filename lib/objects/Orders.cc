#include "Orders.h"

#define ORDERS_NUM_OF_COLS 2
#define EAN13_LEN 13

void Orders::operator<<(std::shared_ptr<IFileReader> reader) noexcept(false)
{
    Order* item;
    uint64_t key;

    // clear map
    mOrders.clear();

    // pass expected number of columns
    reader->setNumOfCols(ORDERS_NUM_OF_COLS);

    // lambda expression
    auto validateEan13 = [](const std::string& to_validate, std::string& error)
    {
        if (to_validate.length() != EAN13_LEN)
        {
            error = "EAN13 shall be 13 digits long.";
            return false;
        }
        return true;
    };

    // row reading loop
    while (reader->readLine())
    {
        // read EAN-13
        key = reader->readULongLongCell(validateEan13);

        // insert map element with EAN-13 key
        item = &mOrders.insert(std::make_pair(key, Order())).first->second;

        // read quantity
        item->quantity = reader->readFloatCell();
    }
}

const char* Orders::getObjectType() const
{
    return "Orders";
}

std::map<uint64_t, Order>::const_iterator Orders::getOrdersBegin() const
{
    return mOrders.cbegin();
}

std::map<uint64_t, Order>::const_iterator Orders::getOrdersEnd() const
{
    return mOrders.cend();
}
