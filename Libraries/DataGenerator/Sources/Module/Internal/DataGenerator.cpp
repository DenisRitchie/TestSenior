    #include "Module/Internal/DataGenerator.hpp"
#include <algorithm>

/**
 * @brief Generates a random byte.
 * @return A random byte.
 * @note The byte will be in the range of 0 to 255.
 */
std::byte Program::Module::Internal::DataGenerator::GetRandomByte() const noexcept
{
    return GetRandomByte(std::byte{ 255 });
}

/**
 * @brief Generates a random byte.
 * @param max The maximum value of the byte.
 * @return A random byte.
 * @note The byte will be in the range of 0 to max.
 */
std::byte Program::Module::Internal::DataGenerator::GetRandomByte(const std::byte max) const noexcept
{
    return GetRandomByte(std::byte{ 0 }, max);
}

/**
 * @brief Generates a random byte.
 * @param min The minimum value of the byte.
 * @param max The maximum value of the byte.
 * @return A random byte.
 * @note The byte will be in the range of min to max.
 */
std::byte Program::Module::Internal::DataGenerator::GetRandomByte(const std::byte min, const std::byte max) const noexcept
{
    return static_cast<std::byte>(GetRandomNumber(std::to_integer<int32_t>(min), std::to_integer<int32_t>(max)));
}

/**
 * @brief Generates a random byte array.
 * @param count The number of bytes to generate.
 * @return A vector of random bytes.
 * @note The bytes will be in the range of 0 to 255.
 * @note The size of the vector will be equal to count.
 * @note The vector will be empty if count is 0.
 */
std::vector<std::byte> Program::Module::Internal::DataGenerator::GetRandomBytes(const std::size_t count) const noexcept
{
    std::vector<std::byte> bytes(count);

    for ( std::byte& value : bytes )
        value = GetRandomByte();

    return bytes;
}

/**
 * @brief Generates a random byte array.
 * @param count The number of bytes to generate.
 * @param max The maximum value of the bytes.
 * @return A random number.
 * @note The number will be in the range of 0 to max.
 */
std::int32_t Program::Module::Internal::DataGenerator::GetRandomNumber(const std::int32_t max) const noexcept
{
    return GetRandomNumber(0, max);
}

/**
 * @brief Generates a random byte array.
 * @param count The number of bytes to generate.
 * @param min The minimum value of the bytes.
 * @param max The maximum value of the bytes.
 * @return A random number.
 * @note The bytes will be in the range of min to max.
 */
std::int32_t Program::Module::Internal::DataGenerator::GetRandomNumber(const int32_t min, const int32_t max) const noexcept
{
    std::random_device                          random_device;                              //!< Will be used to obtain a seed for the random number engine
    std::mt19937                                mersenne_twister_engine{ random_device() }; //!< Standard mersenne_twister_engine seeded with random_device
    std::uniform_int_distribution<std::int32_t> distribution{ min, max };                   //!< Will be used to generate random numbers
    return static_cast<int32_t>(distribution(mersenne_twister_engine));                     //!< Generate a random number
}
