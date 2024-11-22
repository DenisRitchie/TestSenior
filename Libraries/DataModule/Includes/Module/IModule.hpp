#pragma once
#ifndef __INTERFACE_MODULE_HPP__ // clang-format off
#define __INTERFACE_MODULE_HPP__ // clang-format on

 #include "Module/IDataGenerator.hpp"
 #include "Module/IDataSearchEngine.hpp"
 #include "Module/IDataPrintingEngine.hpp"
 #include <memory>
 #include <chrono>

namespace Program::Module
{
    /**
     * @brief IModule interface is an interface class that has the methods to be implemented by the Module class.
     */
    struct IModule
    {
        /**
         * @brief Destroy the IModule object
         * @note Virtual destructor to destroy the IModule object.
         */
        virtual ~IModule() noexcept = default;

        /**
         * @brief GetGenerator method gets the DataGenerator object.
         * @return IDataGenerator& - The DataGenerator object.
         */
        virtual IDataGenerator& GetGenerator() const noexcept = 0;

        /**
         * @brief GetSearchEngine method gets the DataSearchEngine object.
         * @return IDataSearchEngine& - The DataSearchEngine object.
         */
        virtual IDataSearchEngine& GetSearchEngine() const noexcept = 0;

        /**
         * @brief GetPrintingEngine method gets the DataPrintingEngine object.
         * @return IDataPrintingEngine& - The DataPrintingEngine object.
         */
        virtual IDataPrintingEngine& GetPrintingEngine() const noexcept = 0;

        /**
         * @brief SetGenerator method sets the DataGenerator object.
         * @param generator - The DataGenerator object.
         */
        virtual void SetGenerator(std::unique_ptr<IDataGenerator>&& generator) noexcept = 0;

        /**
         * @brief SetSearchEngine method sets the DataSearchEngine object.
         * @param search_engine - The DataSearchEngine object.
         */
        virtual void SetSearchEngine(std::unique_ptr<IDataSearchEngine>&& search_engine) noexcept = 0;

        /**
         * @brief SetPrintingEngine method sets the DataPrintingEngine object.
         * @param printing_engine - The DataPrintingEngine object.
         */
        virtual void SetPrintingEngine(std::unique_ptr<IDataPrintingEngine>&& printing_engine) noexcept = 0;

        /**
         * @brief RunAsync method runs the module asynchronously.
         */
        virtual void RunAsync() noexcept = 0;

        /**
         * @brief StopAsync method stops the module asynchronously.
         */
        virtual void StopAsync() noexcept = 0;

        /**
         * @brief WaitForAsync method waits for the module to finish asynchronously.
         * @param milliseconds - The milliseconds to wait.
         */
        virtual void WaitForAsync(const std::chrono::milliseconds& milliseconds) const noexcept = 0;

        /**
         * @brief PrintResults method prints the results.
         */
        virtual void PrintResults() const noexcept = 0;
    };
} // namespace Program::Module

#endif // !__INTERFACE_MODULE_HPP__
