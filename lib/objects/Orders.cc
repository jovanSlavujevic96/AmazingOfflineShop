#include "Orders.h"

#define ORDERS_NUM_OF_COLS 2
#define EAN13_LEN 13

bool Order::operator==(const Order& other) const
{
    if (this->quantity != other.quantity)
    {
        return false;
    }
    return this->ean13 == other.ean13;
}

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
    while (reader->read())
    {
        // read EAN-13
        key = reader->extractULongLong(validateEan13);

        // insert map element with EAN-13 key
        item = &mOrders.insert(std::make_pair(key, Order())).first->second;

        // read quantity
        item->quantity = reader->extractFloat();
    }

    mOrderNum = Orders::OrderCount++;
}

const char* Orders::getObjectType() const
{
    return "Orders";
}
