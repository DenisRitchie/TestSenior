#pragma once
#ifndef __MODULE_DATA_SEARCH_ENGINE_FACTORY_HPP__ // clang-format off
#define __MODULE_DATA_SEARCH_ENGINE_FACTORY_HPP__ // clang-format on

 #include "Module/IDataSearchEngine.hpp"
 #include <memory>

namespace Program::Module
{
    /**
     * @brief Factory for creating data search engine
     * @details This factory is used to create a data search engine
     * @note This factory is used to create a data search engine
     */
    struct DataSearchEngineFactory
    {
        /**
         * @brief Create a data search engine
         * @return A unique pointer to the created data search engine
         * @note A unique pointer to the created data search engine
         */
        static std::unique_ptr<IDataSearchEngine> Create() noexcept;
    };
} // namespace Program::Module

#endif // __MODULE_DATA_SEARCH_ENGINE_FACTORY_HPP__
