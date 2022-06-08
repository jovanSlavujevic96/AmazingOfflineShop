#include <iostream>
#include <string>
#include <regex>
#include <stdexcept>

#include "Items.h"

#define ITEMS_NUM_OF_COLS 4
#define EAN13_LEN 13

void Items::operator<<(std::shared_ptr<IFileReader> reader) noexcept(false)
{
    Item* item;
    uint64_t key;

    // clear map
    mItems.clear();

    // pass expected number of columns
    reader->setNumOfCols(ITEMS_NUM_OF_COLS);

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
        item = &mItems.insert(std::make_pair(key, Item())).first->second;

        // read product name
        item->name = reader->extractString();

        // read price without taxes
        item->priceWoTax = reader->extractDouble();

        // read tax percentage
        item->taxPercent = reader->extractFloat();
    }
}

const char* Items::getObjectType() const
{
    return "Items";
}

const Item* Items::getItem(uint64_t key) const
{
    try
    {
        return &mItems.at(key);
    }
    catch (...)
    {
        return nullptr;
    }
}
