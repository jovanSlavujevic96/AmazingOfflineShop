#pragma once

#include <map>
#include <cstdint>

#include "IObjects.h"
#include "file_reader/CsvReader.h"

struct Discount
{
    float discountPercent;
};

class Discounts : public IObjects
{
public:
    ~Discounts() = default;

    void operator<<(std::shared_ptr<IFileReader> reader) noexcept(false) override;
    const char* getObjectType() const override;

    const Discount* getDiscount(uint64_t key) const;
private:
    std::map<uint64_t, Discount> mDiscounts;
};
