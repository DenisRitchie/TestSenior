#pragma once
#ifndef __INTERFACE_MODULE_DATA_GENERATOR_HPP__ // clang-format off
#define __INTERFACE_MODULE_DATA_GENERATOR_HPP__ // clang-format on

 #include <vector>
 #include <cinttypes>
 #include <cstddef>

namespace Program::Module
{
    /**
     * @brief Interface for generating random data.
     * This interface is used to generate random data for testing purposes.
     */
    struct IDataGenerator
    {
        /**
         * @brief Destructor.
         * @note Default implementation.
         * @note Virtual destructor.
         */
        virtual ~IDataGenerator() = default;

        /**
         * @brief Get a random byte.
         * @return Random byte.
         */
        virtual std::byte GetRandomByte() const noexcept = 0;

        /**
         * @brief Get a random byte within a range.
         * @param max Maximum value.
         * @return Random byte.
         */
        virtual std::byte GetRandomByte(const std::byte max) const noexcept = 0;

        /**
         * @brief Get a random byte within a range.
         * @param min Minimum value.
         * @param max Maximum value.
         * @return Random byte.
         */
        virtual std::byte GetRandomByte(const std::byte min, const std::byte max) const noexcept = 0;

        /**
         * @brief Get a random byte array.
         * @param count Number of bytes.
         * @return Random byte array.
         */
        virtual std::vector<std::byte> GetRandomBytes(std::size_t count) const noexcept = 0;

        /**
         * @brief Get a random byte array within a range.
         * @param count Number of bytes.
         * @param max Maximum value.
         * @return Random byte array.
         */
        virtual std::int32_t GetRandomNumber(const int32_t max) const noexcept = 0;

        /**
         * @brief Get a random byte array within a range.
         * @param count Number of bytes.
         * @param min Minimum value.
         * @param max Maximum value.
         * @return Random byte array.
         */
        virtual std::int32_t GetRandomNumber(const int32_t min, const int32_t max) const noexcept = 0;
    };
} // namespace Program::Module

#endif // __INTERFACE_MODULE_DATA_GENERATOR_HPP__
