/**
 * @file Items.h
 * @author Jovan Slavujevic (slavujevic.jovan.96@gmail.com)
 * @brief Item structure & Items class definition
 * @version 0.1
 * @date 2022-06-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <string>
#include <cstdint>
#include <map>
#include <memory>

#include "IObjects.h"

/**
 * @brief Item object structure
 */
struct Item
{
    /**
     * @brief item name
     */
    std::string name;
    /**
     * @brief item price withouth taxes
     */
    double priceWoTax;
    /**
     * @brief tax percent for particular item
     */
    float taxPercent;

    /**
     * @brief Overloaded perator.
     *        Method which handles comparing of item objects
     *
     * @param[in] other - other item object to compare
     * @return true - items are matching
     * @return false - items aren't matching
     */
    bool operator==(const Item& other) const;
};

/**
 * @brief Item objects collection class
 *        handles deserialization of item objects in combination with IFileReader
 */
class Items : public IObjects
{
public:
    /**
     * @brief Destroy the Items object
     */
    ~Items() = default;

    /**
     * @brief Overloaded perator.
     *        Method which handles deserialization of item objects
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
     * @brief Get the Item object from map
     *
     * @param[in] key - EAN 13 ID
     * @return const Item* - pointer to item object if fount it or NULL if not
     */
    const Item* getItem(uint64_t key) const;
private:
    /**
     * @brief Map of Item objects
     */
    std::map<uint64_t, Item> mItems;
};
