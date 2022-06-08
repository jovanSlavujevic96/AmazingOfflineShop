#pragma once

#include <map>
#include <string>
#include <cstdint>
#include <fstream>

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

class ProcessedOrders
{
public:
    ~ProcessedOrders() = default;

    void operator>>(std::ofstream& writer) noexcept(false);
    void processOrder(const Orders* initialOrders, const  Items* items, const  Discounts* discounts = nullptr) noexcept(false);
private:
    std::map<std::string, ProcessedOrder> mProcessedOrders;
    double mTotal;
};
