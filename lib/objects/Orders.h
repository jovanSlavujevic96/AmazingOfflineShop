#pragma once

#include <cstdint>
#include <map>
#include <memory>

#include "IObjects.h"

struct Order
{
	float quantity;
};

class Orders : public IObjects
{
public:
	~Orders() = default;

	void operator<<(std::shared_ptr<IFileReader> reader) noexcept(false) override;
	const char* getObjectType() const override;

	std::map<uint64_t, Order>::const_iterator getOrdersBegin() const;
	std::map<uint64_t, Order>::const_iterator getOrdersEnd() const;
private:
	std::map<uint64_t, Order> mOrders;
};
