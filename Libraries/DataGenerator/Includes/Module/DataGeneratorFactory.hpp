#pragma once
#ifndef __MODULE_DATA_GENERATOR_FACTORY_HPP__ // clang-format off
#define __MODULE_DATA_GENERATOR_FACTORY_HPP__ // clang-format on

 #include "Module/IDataGenerator.hpp"
 #include <memory>

namespace Program::Module
{
    /**
     * @brief Factory for creating data generators.
     */
    struct DataGeneratorFactory
    {
        /**
         * @brief Create a data generator.
         * @return Data generator.
         */
        static std::unique_ptr<IDataGenerator> Create() noexcept;
    };
} // namespace Program::Module

#endif // __MODULE_DATA_GENERATOR_FACTORY_HPP__
