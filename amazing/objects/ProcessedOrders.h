#pragma once

#include <map>
#include <string>
#include <cstdint>
#include <fstream>

#include "IObjects.h"
#include "Orders.h"
#include "Discounts.h"
#include "Items.h"

struct ProcessedOrder
{
	float taxPercent;
	float discountPercent;
	float quantity;
	double priceWithoutDiscount;
	double finalPrice;
};

class ProcessedOrders : public IObjects
{
public:
	~ProcessedOrders() = default;

	void operator<<(std::shared_ptr<IFileReader> reader) noexcept(false) override;
	void operator>>(std::ofstream& writer) noexcept(false);
	void processOrder(Orders* initialOrders, Items* items, Discounts* discounts = nullptr) noexcept(false);

	const char* getObjectType() const override;
private:
	std::map<std::string, ProcessedOrder> mProcessedOrders;
	double mTotal;
};
