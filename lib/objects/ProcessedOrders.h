/**
 * @file ProccesedOrders.h
 * @author Jovan Slavujevic (slavujevic.jovan.96@gmail.com)
 * @brief ProccesedOrder structure & ProccesedOrders class definition
 * @version 0.1
 * @date 2022-06-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <map>
#include <string>
#include <cstdint>
#include <fstream>

#include "Orders.h"
#include "Discounts.h"
#include "Items.h"

/**
 * @brief ProcessedOrder object structure
 */
struct ProcessedOrder
{
    /**
     * @brief processed order tax percent 
     */
    float taxPercent;
    /**
     * @brief processed order discount percent 
     */
    float discountPercent;
    /**
     * @brief processed order quantity 
     */
    float quantity;
    /**
     * @brief processed order price without discount
     */
    double priceWoDiscount;
    /**
     * @brief processed order final price (including quantity) 
     */
    double finalPrice;

    /**
     * @brief Overloaded perator.
     *        Method which handles comparing of processed order objects
     *
     * @param other - other processed order object to compare
     * @return true - processed order's quantity are matching
     * @return false - processed order's quantity aren't matching
     */
    bool operator==(const ProcessedOrder& other) const;
};

/**
 * @brief Order objects collection class
 *        handles deserialization of order objects in combination with ofstream (standard library)
 */
class ProcessedOrders
{
public:
    /**
     * @brief Construct a new ProcessedOrders object
     */
    ProcessedOrders();
    /**
     * @brief Destroy the ProcessedOrders object
     */
    ~ProcessedOrders() = default;

    /**
     * @brief Overloaded perator.
     *        Method which handles serialization of processed order objects
     *
     * @param[in] writer - writing handler
     */
    void operator>>(std::ofstream& writer) noexcept(false);
    /**
     * @brief Method which process initial Orders and makes final price
     *
     * @param[in] initialOrders - initial orders as input
     * @param[in] items - items values without discount calculation
     * @param[in] discounts - discounts (optional/nullable)
     */
    void processOrder(const Orders* initialOrders, const  Items* items, const  Discounts* discounts = nullptr) noexcept(false);
private:
    /**
     * @brief Map of ProcessedOrder objects
     */
    std::map<std::string, ProcessedOrder> mProcessedOrders;
    /**
     * @brief total price of orders
     */
    double mTotal;
};
