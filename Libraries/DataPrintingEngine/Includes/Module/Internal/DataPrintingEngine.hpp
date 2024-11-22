#pragma once
#ifndef __MODULE_DATA_PRINTING_ENGINE_HPP__ // clang-format off
#define __MODULE_DATA_PRINTING_ENGINE_HPP__ // clang-format on

 #include "Module/IDataPrintingEngine.hpp"

namespace Program::Module::Internal
{
    /**
     * @brief Data Printing Engine module.
     * @details The Data Printing Engine module is responsible for printing data to the output stream.
     * The module provides a set of functions for printing different types of data to the output stream.
     * The module is implemented as a concrete class that implements the IDataPrintingEngine interface.
     */
    struct DataPrintingEngine : public IDataPrintingEngine
    {
        /**
         * @brief Default constructor.
         * @details The default constructor is necessary to create instances of the Data Printing Engine.
         */
        DataPrintingEngine() = default;

        /**
         * @brief Default destructor.
         * @details The default destructor is necessary to destroy instances of the Data Printing Engine.
         */
        ~DataPrintingEngine() = default;

        /**
         * @brief Prints the data to the output stream.
         * @param data The data to be printed.
         */
        void Print(const std::byte data) const noexcept override;

        /**
         * @brief Prints the data to the output stream.
         * @param data The data to be printed.
         */
        void Print(const std::time_t data) const noexcept override;

        /**
         * @brief Prints the data to the output stream.
         * @param data The data to be printed.
         */
        void Print(const std::vector<std::byte>& data) const noexcept override;

        /**
         * @brief Prints the data to the output stream.
         * @param data The data to be printed.
         */
        void Print(const std::tuple<std::time_t, std::vector<std::byte>>& data) const noexcept override;

        /**
         * @brief Prints the data to the output stream.
         * @param data The data to be printed.
         */
        void Print(const std::vector<std::tuple<std::time_t, std::vector<std::byte>>>& data) const noexcept override;

        /**
         * @brief Prints the data to the output stream and adds a new line.
         * @param data The data to be printed.
         */
        void PrintLine(const std::byte data) const noexcept override;

        /**
         * @brief Prints the data to the output stream and adds a new line.
         * @param data The data to be printed.
         */
        void PrintLine(const std::time_t data) const noexcept override;

        /**
         * @brief Prints the data to the output stream and adds a new line.
         * @param data The data to be printed.
         */
        void PrintLine(const std::vector<std::byte>& data) const noexcept override;

        /**
         * @brief Prints the data to the output stream and adds a new line.
         * @param data The data to be printed.
         */
        void PrintLine(const std::tuple<std::time_t, std::vector<std::byte>>& data) const noexcept override;

        /**
         * @brief Prints the data to the output stream and adds a new line.
         * @param data The data to be printed.
         */
        void PrintLine(const std::vector<std::tuple<std::time_t, std::vector<std::byte>>>& data) const noexcept override;
    };
} // namespace Program::Module::Internal

#endif // __MODULE_DATA_PRINTING_ENGINE_HPP__
