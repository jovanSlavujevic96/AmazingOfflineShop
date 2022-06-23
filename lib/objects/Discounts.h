/**
 * @file Discounts.h
 * @author Jovan Slavujevic (slavujevic.jovan.96@gmail.com)
 * @brief Discount structure & Discounts class definition
 * @version 0.2
 * @date 2022-06-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <map>
#include <cstdint>

#include "IObjects.h"
#include "file_reader/CsvReader.h"

class ProcessedOrders;

/**
 * @brief Discount object structure
 */
struct Discount
{
    /**
     * @brief discount percent
     */
    float discountPercent;

    /**
     * @brief Overloaded perator.
     *        Method which handles comparing of discount objects
     *
     * @param[in] other - other discount object to compare
     * @return true - same discount percents
     * @return false - different discount percents
     */
    bool operator==(const Discount& other) const;
    /**
     * @brief Overloaded perator. Oppostie of operator==
     */
    inline bool operator!=(const Discount& other) const { return !(*this == other); }
};

/**
 * @brief Discount objects collection class
 *        handles deserialization of discount objects in combination with IFileReader
 */
class Discounts : public IObjects
{
    friend class ProcessedOrders;
public:
    /**
     * @brief Destroy the Discounts object
     */
    ~Discounts() = default;

    /**
     * @brief Overloaded perator.
     *        Method which handles deserialization of discount objects
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
private:
    /**
     * @brief Map of Discount objects
     */
    std::map<uint64_t, Discount> mDiscounts;
};
