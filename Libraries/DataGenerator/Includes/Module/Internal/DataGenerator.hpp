#pragma once
#ifndef __MODULE_DATA_GENERATOR_HPP__ // clang-format off
#define __MODULE_DATA_GENERATOR_HPP__ // clang-format on

 #include "Module/IDataGenerator.hpp"
 #include <random>

namespace Program::Module::Internal
{
    /**
     * @brief Data generator.
     * This class is used to generate random data for testing purposes.
     */
    struct DataGenerator final : public IDataGenerator
    {
        /**
         * @brief Random number generator.
         * @note Mersenne Twister 19937 engine.
         * @note Random device seed.
         * @note Default implementation.
         * @note Noexcept.
         */
        DataGenerator() noexcept = default;

        /**
         * @brief Destructor.
         * @note Default implementation.
         * @note Virtual destructor.
         */
        virtual ~DataGenerator() = default;

        /**
         * @brief Get a random byte.
         * @return Random byte.
         * @note Override.
         * @note Noexcept.
         */
        virtual std::byte GetRandomByte() const noexcept override;

        /**
         * @brief Get a random byte within a range.
         * @param max Maximum value.
         * @return Random byte.
         * @note Override.
         * @note Noexcept.
         */
        virtual std::byte GetRandomByte(const std::byte max) const noexcept override;

        /**
         * @brief Get a random byte within a range.
         * @param min Minimum value.
         * @param max Maximum value.
         * @return Random byte.
         * @note Override.
         * @note Noexcept.
         */
        virtual std::byte GetRandomByte(const std::byte min, const std::byte max) const noexcept override;

        /**
         * @brief Get a random byte array.
         * @param count Number of bytes.
         * @return Random byte array.
         * @note Override.
         * @note Noexcept.
         */
        virtual std::vector<std::byte> GetRandomBytes(const std::size_t count) const noexcept override;

        /**
         * @brief Get a random byte array within a range.
         * @param count Number of bytes.
         * @param max Maximum value.
         * @return Random byte array.
         * @note Override.
         * @note Noexcept.
         */
        virtual std::int32_t GetRandomNumber(const int32_t max) const noexcept override;

        /**
         * @brief Get a random byte array within a range.
         * @param count Number of bytes.
         * @param min Minimum value.
         * @param max Maximum value.
         * @return Random byte array.
         * @note Override.
         * @note Noexcept.
         */
        virtual std::int32_t GetRandomNumber(const int32_t min, const int32_t max) const noexcept override;
    };
} // namespace Program::Module::Internal
#endif // __MODULE_DATA_GENERATOR_HPP__
