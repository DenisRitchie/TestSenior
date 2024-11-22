#pragma once
#ifndef __INTERFACE_MODULE_DATA_PRINTING_ENGINE_HPP__ // clang-format off
#define __INTERFACE_MODULE_DATA_PRINTING_ENGINE_HPP__ // clang-format on

 #include <vector>
 #include <cstddef>
 #include <ctime>
 #include <tuple>

namespace Program::Module
{
    /**
     * @brief Interface for the Data Printing Engine module.
     */
    struct IDataPrintingEngine
    {
        /**
         * @brief Virtual destructor.
         * @details A virtual destructor is necessary to ensure that the destructor of the derived class is called when the object is destroyed.
         * This is necessary to avoid memory leaks.
         * @note The destructor is declared as virtual to ensure that the destructor of the derived class is called when the object is destroyed.
         */
        virtual ~IDataPrintingEngine() = default;

        /**
         * @brief Prints the data to the output stream.
         * @param data The data to be printed.
         */
        virtual void Print(const std::byte data) const noexcept = 0;

        /**
         * @brief Prints the data to the output stream.
         * @param data The data to be printed.
         */
        virtual void Print(const std::time_t data) const noexcept = 0;

        /**
         * @brief Prints the data to the output stream.
         * @param data The data to be printed.
         */
        virtual void Print(const std::vector<std::byte>& data) const noexcept = 0;

        /**
         * @brief Prints the data to the output stream.
         * @param data The data to be printed.
         */
        virtual void Print(const std::tuple<std::time_t, std::vector<std::byte>>& data) const noexcept = 0;

        /**
         * @brief Prints the data to the output stream.
         * @param data The data to be printed.
         */
        virtual void Print(const std::vector<std::tuple<std::time_t, std::vector<std::byte>>>& data) const noexcept = 0;

        /**
         * @brief Prints the data to the output stream and adds a new line.
         * @param data The data to be printed.
         */
        virtual void PrintLine(const std::byte data) const noexcept = 0;

        /**
         * @brief Prints the data to the output stream and adds a new line.
         * @param data The data to be printed.
         */
        virtual void PrintLine(const std::time_t data) const noexcept = 0;

        /**
         * @brief Prints the data to the output stream and adds a new line.
         * @param data The data to be printed.
         */
        virtual void PrintLine(const std::vector<std::byte>& data) const noexcept = 0;

        /**
         * @brief Prints the data to the output stream and adds a new line.
         * @param data The data to be printed.
         */
        virtual void PrintLine(const std::tuple<std::time_t, std::vector<std::byte>>& data) const noexcept = 0;

        /**
         * @brief Prints the data to the output stream and adds a new line.
         * @param data The data to be printed.
         */
        virtual void PrintLine(const std::vector<std::tuple<std::time_t, std::vector<std::byte>>>& data) const noexcept = 0;
    };
} // namespace Program::Module

#endif // __INTERFACE_MODULE_DATA_PRINTING_ENGINE_HPP__
