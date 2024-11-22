#pragma once
#ifndef __MODULE_DATA_PRINTING_ENGINE_FACTORY_HPP__ // clang-format off
#define __MODULE_DATA_PRINTING_ENGINE_FACTORY_HPP__ // clang-format on

 #include "Module/IDataPrintingEngine.hpp"
 #include <memory>

namespace Program::Module
{
    /**
     * @brief Factory for creating instances of the Data Printing Engine.
     */
    struct DataPrintingEngineFactory
    {
        /**
         * @brief Creates a new instance of the Data Printing Engine.
         * @return A new instance of the Data Printing Engine.
         */
        static std::unique_ptr<IDataPrintingEngine> Create() noexcept;
    };
} // namespace Program::Module

#endif // __MODULE_DATA_PRINTING_ENGINE_FACTORY_HPP__
