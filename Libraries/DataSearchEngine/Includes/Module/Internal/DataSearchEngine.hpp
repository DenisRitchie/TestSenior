#pragma once
#ifndef __MODULE_DATA_SEARCH_ENGINE_HPP__ // clang-format off
#define __MODULE_DATA_SEARCH_ENGINE_HPP__ // clang-format on

 #include "Module/IDataSearchEngine.hpp"

namespace Program::Module::Internal
{
    /**
     * @brief Data search engine
     * @details This class is used to search for a specific data in a given source data
     * @note This class is used to search for a specific data in a given source data
     */
    struct DataSearchEngine final : public IDataSearchEngine
    {
        /**
         * @brief Default constructor
         * @details Default constructor
         * @note Default constructor
         */
        DataSearchEngine() noexcept = default;

        /**
         * @brief Destructor
         * @details Virtual destructor
         * @note Virtual destructor
         */
        virtual ~DataSearchEngine() = default;

        /**
         * @brief Search for a specific data in a given source data
         * @param source The source data to search in
         * @param values_to_search The data to search for
         * @return The index of the first occurrence of the data to search for in the source data
         * @note If the data to search for is not found, the function will return an empty optional
         */
        virtual std::optional<int32_t> Search(const std::vector<std::byte>& source, const std::vector<std::byte> values_to_search) const noexcept override;
    };
} // namespace Program::Module::Internal

#endif // __MODULE_DATA_SEARCH_ENGINE_HPP__
