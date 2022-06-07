#include <iostream>

#include "Discounts.h"

#define DISCOUNTS_NUM_OF_COLS 2
#define EAN13_LEN 13

void Discounts::operator<<(std::shared_ptr<IFileReader> reader) noexcept(false)
{
	Discount* item;
	uint64_t key;

	// clear map
	mDiscounts.clear();

	// pass expected number of columns
	reader->setNumOfCols(DISCOUNTS_NUM_OF_COLS);

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
		item = &mDiscounts.insert(std::make_pair(key, Discount())).first->second;

		// read discount percentage
		item->discountPercent = reader->readFloatCell();
	}
}

const char* Discounts::getObjectType() const
{
	return "Discounts";
}

const Discount* Discounts::getDiscount(uint64_t key) const
{
	try
	{
		return &mDiscounts.at(key);
	}
	catch (...)
	{
		return nullptr;
	}
}
