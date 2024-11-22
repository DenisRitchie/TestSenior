#include "Module/Internal/DataPrintingEngine.hpp"
#include "Helpers/ostream_joiner.hpp"
#include <algorithm>
#include <iostream>
#include <iomanip>

namespace Program::Module::Internal
{
    /**
     * @brief Prints the data to the output stream.
     * @details The function prints the data to the output stream in the format 0xXX where XX is the hexadecimal representation of the data.
     * @param data The data to be printed.
     * @note The function is noexcept.
     * @note The function is marked as noexcept to ensure that the function does not throw exceptions.
     */
    void DataPrintingEngine::Print(const std::byte data) const noexcept
    {
        std::cout << "0x" << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << std::to_integer<int32_t>(data);
    }

    /**
     * @brief Prints the data to the output stream.
     * @details The function prints the data to the output stream in the format YYYY-MM-DD HH:MM:SS UTC.
     * @param time The data to be printed.
     * @note The function is noexcept.
     * @note The function is marked as noexcept to ensure that the function does not throw exceptions.
     */
    void DataPrintingEngine::Print(const std::time_t time) const noexcept
    {
        const std::tm* utc_time = std::gmtime(std::addressof(time)); //!< The time is converted to UTC time.
        std::cout << std::put_time(utc_time, "%Y-%m-%d %H:%M:%S") << " UTC";
    }

    /**
     * @brief Prints the data to the output stream.
     * @details The function prints the data to the output stream in the format [0xXX, 0xYY, ..., 0xZZ] where XX, YY, ..., ZZ are the hexadecimal representation of the data.
     * @param data The data to be printed.
     * @note The function is noexcept.
     * @note The function is marked as noexcept to ensure that the function does not throw exceptions.
     */
    void DataPrintingEngine::Print(const std::vector<std::byte>& data) const noexcept
    {
        // clang-format off
        std::cout << "[";
        std::copy(data.cbegin(), data.cend(), Helpers::make_ostream_joiner(std::cout, ", ",
            [](auto& os, const auto& value)
            {
                os << "0x" << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << std::to_integer<int32_t>(value);
            })
        );
        std::cout << "]";
        // clang-format on
    }

    /**
     * @brief Prints the data to the output stream.
     * @details The function prints the data to the output stream in the format YYYY-MM-DD HH:MM:SS UTC followed by the data in the format [0xXX, 0xYY, ..., 0xZZ] where XX, YY, ..., ZZ are the hexadecimal representation of the data.
     * @param data The data to be printed.
     * @note The function is noexcept.
     * @note The function is marked as noexcept to ensure that the function does not throw exceptions.
     */
    void DataPrintingEngine::Print(const std::tuple<std::time_t, std::vector<std::byte>>& data) const noexcept
    {
        Print(std::get<0>(data));
        std::cout << "\n";
        Print(std::get<1>(data));
    }

    /**
     * @brief Prints the data to the output stream.
     * @details The function prints the data to the output stream in the format YYYY-MM-DD HH:MM:SS UTC followed by the data in the format [0xXX, 0xYY, ..., 0xZZ] where XX, YY, ..., ZZ are the hexadecimal representation of the data.
     * @param data The data to be printed.
     * @note The function is noexcept.
     * @note The function is marked as noexcept to ensure that the function does not throw exceptions.
     */
    void DataPrintingEngine::Print(const std::vector<std::tuple<std::time_t, std::vector<std::byte>>>& data) const noexcept
    {
        // clang-format off
        std::copy(data.cbegin(), data.cend(), Helpers::make_ostream_joiner(std::cout, "\n\n",
            [this]([[maybe_unused]] auto& os, const auto& value)
            {
                Print(value);
            })
        );
        // clang-format on
    }

    /**
     * @brief Prints the data to the output stream and adds a new line.
     * @param data The data to be printed.
     * @note The function is noexcept.
     * @note The function is marked as noexcept to ensure that the function does not throw exceptions.
     */
    void DataPrintingEngine::PrintLine(const std::byte data) const noexcept
    {
        Print(data);
        std::cout << std::endl;
    }

    /**
     * @brief Prints the data to the output stream and adds a new line.
     * @param data The data to be printed.
     * @note The function is noexcept.
     * @note The function is marked as noexcept to ensure that the function does not throw exceptions.
     */
    void DataPrintingEngine::PrintLine(const std::time_t data) const noexcept
    {
        Print(data);
        std::cout << std::endl;
    }

    /**
     * @brief Prints the data to the output stream and adds a new line.
     * @param data The data to be printed.
     * @note The function is noexcept.
     * @note The function is marked as noexcept to ensure that the function does not throw exceptions.
     */
    void DataPrintingEngine::PrintLine(const std::vector<std::byte>& data) const noexcept
    {
        Print(data);
        std::cout << std::endl;
    }

    /**
     * @brief Prints the data to the output stream and adds a new line.
     * @param data The data to be printed.
     * @note The function is noexcept.
     * @note The function is marked as noexcept to ensure that the function does not throw exceptions.
     */
    void DataPrintingEngine::PrintLine(const std::tuple<std::time_t, std::vector<std::byte>>& data) const noexcept
    {
        Print(data);
        std::cout << std::endl;
    }

    /**
     * @brief Prints the data to the output stream and adds a new line.
     * @param data The data to be printed.
     * @note The function is noexcept.
     * @note The function is marked as noexcept to ensure that the function does not throw exceptions.
     */
    void DataPrintingEngine::PrintLine(const std::vector<std::tuple<std::time_t, std::vector<std::byte>>>& data) const noexcept
    {
        Print(data);
        std::cout << std::endl;
    }
} // namespace Program::Module::Internal
