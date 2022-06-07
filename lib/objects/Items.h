#pragma once

#include <string>
#include <cstdint>
#include <map>
#include <memory>

#include "IObjects.h"

struct Item
{
    std::string name;
    double priceWoTax;
    float taxPercent;
};

class Items : public IObjects
{
public:
    ~Items() = default;

    void operator<<(std::shared_ptr<IFileReader> reader) noexcept(false) override;
    const char* getObjectType() const override;

    const Item* getItem(uint64_t key) const;
private:
    std::map<uint64_t, Item> mItems;
};
