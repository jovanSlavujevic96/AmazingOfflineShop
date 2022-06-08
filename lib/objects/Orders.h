/**
 * @file Orders.h
 * @author Jovan Slavujevic (slavujevic.jovan.96@gmail.com)
 * @brief Order structure & Orders class definition
 * @version 0.1
 * @date 2022-06-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <cstdint>
#include <map>
#include <memory>

#include "IObjects.h"

/**
 * @brief Order object structure
 */
struct Order
{
    /**
     * @brief order quantity
     */
    float quantity;

    /**
     * @brief Overloaded perator.
     *        Method which handles comparing of order objects
     *
     * @param[in] other - other order object to compare
     * @return true - order's quantity are matching
     * @return false - order's quantity aren't matching
     */
    bool operator==(const Order& other) const;
    /**
     * @brief Overloaded perator. Oppostie of operator==
     */
    inline bool operator!=(const Order& other) const { return !(*this == other); }
};

/**
 * @brief Order objects collection class
 *        handles deserialization of order objects in combination with IFileReader
 */
class Orders : public IObjects
{
public:
    /**
     * @brief Destroy the Orders object
     */
    ~Orders() = default;

    /**
     * @brief Overloaded perator.
     *        Method which handles deserialization of order objects
     *
     * @exception std::runtime_error reading error
     *
     * @param[in] reader - file reading handler
     */
    void operator<<(std::shared_ptr<IFileReader> reader) noexcept(false) override;
    /**
     * @brief Get the Object type (name)
     *
     * @return name in string format
     */
    const char* getObjectType() const override;

    /**
     * @brief Get the Orders map beginning iterator
     *
     * @return std::map<uint64_t, Order>::const_iterator begin
     */
    std::map<uint64_t, Order>::const_iterator getOrdersBegin() const;
    /**
     * @brief Get the Orders map ending iterator
     *
     * @return std::map<uint64_t, Order>::const_iterator end
     */
    std::map<uint64_t, Order>::const_iterator getOrdersEnd() const;

    /**
     * @brief Get the Order number
     *
     * @return size_t - order number
     */
    size_t getOrderNum() const;
    /**
     * @brief Set the Order number
     *
     * @param order - order number
     */
    void setOrderNum(size_t order);
private:
    /**
     * @brief Map of Order objects
     */
    std::map<uint64_t, Order> mOrders;
    /**
     * @brief Order Number
     */
    size_t mOrderNum = 0;

    /**
     * @brief Static order counter. Increases on every succesfully deserialization
     */
    inline static size_t OrderCount = 0;
};
