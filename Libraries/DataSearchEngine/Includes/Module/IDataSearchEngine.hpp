#pragma once
#ifndef __INTERFACE_MODULE_DATA_SEARCH_ENGINE_HPP__ // clang-format off
#define __INTERFACE_MODULE_DATA_SEARCH_ENGINE_HPP__ // clang-format on

 #include <vector>
 #include <cinttypes>
 #include <cstddef>
 #include <optional>

namespace Program::Module
{
    /**
     * @brief Interface for data search engine
     * @details This interface is used to search for a specific data in a given source data
     * @note This interface is used to search for a specific data in a given source data
     */
    struct IDataSearchEngine
    {
        /**
         * @brief Destructor
         * @details Virtual destructor
         * @note Virtual destructor
         */
        virtual ~IDataSearchEngine() = default;

        /**
         * @brief Search for a specific data in a given source data
         * @param source The source data to search in
         * @param values_to_search The data to search for
         * @return The index of the first occurrence of the data to search for in the source data
         * @note If the data to search for is not found, the function will return an empty optional
         */
        virtual std::optional<int32_t> Search(const std::vector<std::byte>& source, const std::vector<std::byte> values_to_search) const noexcept = 0;
    };
} // namespace Program::Module

#endif // __INTERFACE_MODULE_DATA_SEARCH_ENGINE_HPP__
