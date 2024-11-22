#pragma once
#ifndef __MODULE_MODULE_HPP__ // clang-format off
#define __MODULE_MODULE_HPP__ // clang-format on

 #include "Module/IModule.hpp"

 #include <ctime>
 #include <tuple>
 #include <condition_variable>
 #include <thread>
 #include <mutex>
 #include <atomic>

namespace Program::Module::Internal
{
    /**
     * @brief The DataModule class is responsible for managing the data generation, search, and printing engines.
     * It also manages the threads that are used to generate and search for data.
     */
    class DataModule final : public IModule
    {
    public:
        /**
         * @brief Construct a new DataModule object.
         * @note The default constructor initializes the data generator, search engine, and printing engine to default values.
         */
        DataModule() noexcept;

        /**
         * @brief Destroy the DataModule object.
         * @note The destructor clears the threads and waits for them to finish before destroying the object.
         */
        ~DataModule() noexcept override;

        /**
         * @brief Get the data generator.
         * @return The data generator.
         * @note The data generator is used to generate data that will be searched for.
         */
        IDataGenerator& GetGenerator() const noexcept override;

        /**
         * @brief Get the data search engine.
         * @return The data search engine.
         * @note The data search engine is used to search for data that was generated.
         */
        IDataSearchEngine& GetSearchEngine() const noexcept override;

        /**
         * @brief Get the data printing engine.
         * @return The data printing engine.
         * @note The data printing engine is used to print the results of the search engine.
         */
        IDataPrintingEngine& GetPrintingEngine() const noexcept override;

        /**
         * @brief Set the data generator.
         * @param generator The data generator.
         * @note The data generator is used to generate data that will be searched for.
         */
        void SetGenerator(std::unique_ptr<IDataGenerator>&& generator) noexcept override;

        /**
         * @brief Set the data search engine.
         * @param search_engine The data search engine.
         * @note The data search engine is used to search for data that was generated.
         */
        void SetSearchEngine(std::unique_ptr<IDataSearchEngine>&& search_engine) noexcept override;

        /**
         * @brief Set the data printing engine.
         * @param printing_engine The data printing engine.
         * @note The data printing engine is used to print the results of the search engine.
         */
        void SetPrintingEngine(std::unique_ptr<IDataPrintingEngine>&& printing_engine) noexcept override;

        /**
         * @brief Run the data module asynchronously.
         * @note The RunAsync method starts the threads that are used to generate and search for data.
         */
        void RunAsync() noexcept override;

        /**
         * @brief Stop the data module asynchronously.
         * @note The StopAsync method stops the threads that are used to generate and search for data.
         */
        void StopAsync() noexcept override;

        /**
         * @brief Wait for the data module to finish asynchronously.
         * @param milliseconds The number of milliseconds to wait for the data module to finish.
         * @note The WaitForAsync method waits for the data module to finish running asynchronously.
         */
        void WaitForAsync(const std::chrono::milliseconds& milliseconds) const noexcept override;

        /**
         * @brief Print the results of the data module.
         * @note The PrintResults method prints the results of the data module.
         */
        void PrintResults() const noexcept override;

    private:
        /**
         * @brief Clear the threads.
         * @note The ClearThreads method clears the threads that are used to generate and search for data.
         */
        void ClearThreads() noexcept;

        /**
         * @brief Check if the thread cancellation is requested.
         * @return True if the thread cancellation is requested; otherwise, false.
         * @note The IsThreadCancellationRequested method checks if the thread cancellation is requested.
         */
        bool IsThreadCancellationRequested() const noexcept;

        /**
         * @brief Set the thread cancellation flag.
         * @param flag The thread cancellation flag.
         * @note The SetThreadCancellation method sets the thread cancellation flag.
         */
        void SetThreadCancellation(const bool flag) noexcept;

        /**
         * @brief Generate the bytes.
         * @return The bytes.
         * @note The GenerateBytes method generates the bytes that will be searched for.
         */
        std::vector<std::byte> GenerateBytes() const noexcept;

    private:
        std::unique_ptr<IDataGenerator>                                      m_DataGenerator;      //!< The data generator. Used to generate data that will be searched for.
        std::unique_ptr<IDataSearchEngine>                                   m_DataSearchEngine;   //!< The data search engine. Used to search for data that was generated.
        std::unique_ptr<IDataPrintingEngine>                                 m_DataPrintingEngine; //!< The data printing engine. Used to print the results of the search engine.
        std::atomic_bool                                                     m_ThreadCancellation; //!< The thread cancellation flag. Used to request the cancellation of the threads.
        std::vector<std::thread>                                             m_Threads;            //!< The threads that are used to generate and search for data.
        mutable std::vector<std::tuple<std::time_t, std::vector<std::byte>>> m_Results;            //!< The results of the search engine. Used to store the results of the search engine.
        mutable std::mutex                                                   m_ResultsMutex;       //!< The results mutex. Used to protect the results of the search engine.
    };
} // namespace Program::Module::Internal

#endif // !__MODULE_MODULE_HPP__
