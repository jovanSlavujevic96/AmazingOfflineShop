#pragma once

#include <string>
#include <memory>

#include "file_reader/IFileReader.h"

class IObjects
{
public:
    virtual ~IObjects() = default;

    virtual void operator<<(std::shared_ptr<IFileReader> reader) noexcept(false) = 0;
    virtual const char* getObjectType() const = 0;
};
