#pragma once
#ifndef __MODULE_FACTORY_HPP__ // clang-format off
#define __MODULE_FACTORY_HPP__ // clang-format on

 #include "Module/IModule.hpp"
 #include <memory>

namespace Program::Module
{
    /**
     * @brief ModuleFactory class is a factory class that creates the module objects.
     * It is a static class that has static methods to create the module objects.
     */
    struct ModuleFactory
    {
        /**
         * @brief Create method creates the module object.
         * @return std::unique_ptr<IModule> - The module object.
         */
        static std::unique_ptr<IModule> Create() noexcept;

        /**
         * @brief CreateDataGenerator method creates the DataGenerator object.
         * @return std::unique_ptr<IDataGenerator> - The DataGenerator object.
         */
        static std::unique_ptr<IDataGenerator> CreateDataGenerator() noexcept;

        /**
         * @brief CreateDataSearchEngine method creates the DataSearchEngine object.
         * @return std::unique_ptr<IDataSearchEngine> - The DataSearchEngine object.
         */
        static std::unique_ptr<IDataSearchEngine> CreateDataSearchEngine() noexcept;

        /**
         * @brief CreateDataPrintingEngine method creates the DataPrintingEngine object.
         * @return std::unique_ptr<IDataPrintingEngine> - The DataPrintingEngine object.
         */
        static std::unique_ptr<IDataPrintingEngine> CreateDataPrintingEngine() noexcept;
    };
} // namespace Program::Module

#endif // !__MODULE_FACTORY_HPP__
