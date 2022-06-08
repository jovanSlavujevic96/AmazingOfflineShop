/**
 * @file IObjects.h
 * @author Jovan Slavujevic (slavujevic.jovan.96@gmail.com)
 * @brief IObjects interface definition
 * @version 0.1
 * @date 2022-06-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <string>
#include <memory>

#include "file_reader/IFileReader.h"

/**
 * @brief Shop Objects Interface class
 *        handles deserialization of objects in combination with IFileReader
 */
class IObjects
{
public:
    /**
     * @brief Destroy the IObjects object
     */
    virtual ~IObjects() = default;

    /**
     * @brief Overloaded perator.
     *        Method which shall handle deserialization of shop objects
     *
     * @exception std::runtime_error reading error
     *
     * @param[in] reader - file reading handler
     */
    virtual void operator<<(std::shared_ptr<IFileReader> reader) noexcept(false) = 0;
    /**
     * @brief Get the Object type (name)
     *
     * @return name in string format
     */
    virtual const char* getObjectType() const = 0;
};
