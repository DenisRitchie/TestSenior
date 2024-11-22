#include "Module/Internal/DataModule.hpp"
#include "Module/DataGeneratorFactory.hpp"
#include "Module/DataSearchEngineFactory.hpp"
#include "Module/DataPrintingEngineFactory.hpp"

#include <tuple>
#include <iostream>
#include <algorithm>
#include <functional>

namespace Program::Module::Internal
{
    /**
     * @brief Construct a new DataModule object.
     * The default constructor initializes the data generator, search engine, and printing engine.
     * @note The default constructor is explicitly defined as noexcept.
     */
    DataModule::DataModule() noexcept
        : m_DataGenerator{ DataGeneratorFactory::Create() }
        , m_DataSearchEngine{ DataSearchEngineFactory::Create() }
        , m_DataPrintingEngine{ DataPrintingEngineFactory::Create() }
    {
    }

    /**
     * @brief Destroy the DataModule object.
     * The destructor clears the threads and waits for them to finish.
     * @note The destructor is explicitly defined as noexcept.
     */
    DataModule::~DataModule() noexcept
    {
        ClearThreads();
    }

    /**
     * @brief Get the data generator.
     * @return A reference to the data generator.
     */
    IDataGenerator& DataModule::GetGenerator() const noexcept
    {
        return *m_DataGenerator;
    }

    /**
     * @brief Get the data search engine.
     * @return A reference to the data search engine.
     */
    IDataSearchEngine& DataModule::GetSearchEngine() const noexcept
    {
        return *m_DataSearchEngine;
    }

    /**
     * @brief Get the data printing engine.
     * @return A reference to the data printing engine.
     */
    IDataPrintingEngine& DataModule::GetPrintingEngine() const noexcept
    {
        return *m_DataPrintingEngine;
    }

    /**
     * @brief Set the data generator.
     * The data generator is set to the default implementation if the parameter is nullptr.
     * @param generator The data generator to set.
     */
    void DataModule::SetGenerator(std::unique_ptr<IDataGenerator>&& generator) noexcept
    {
        if ( generator == nullptr )
        {
            m_DataGenerator = DataGeneratorFactory::Create();
        }
        else
        {
            m_DataGenerator = std::move(generator);
        }
    }

    /**
     * @brief Set the data search engine.
     * The data search engine is set to the default implementation if the parameter is nullptr.
     * @param search_engine The data search engine to set.
     */
    void DataModule::SetSearchEngine(std::unique_ptr<IDataSearchEngine>&& search_engine) noexcept
    {
        if ( search_engine == nullptr )
        {
            m_DataSearchEngine = DataSearchEngineFactory::Create();
        }
        else
        {
            m_DataSearchEngine = std::move(search_engine);
        }
    }

    /**
     * @brief Set the data printing engine.
     * The data printing engine is set to the default implementation if the parameter is nullptr.
     * @param printing_engine The data printing engine to set.
     */
    void DataModule::SetPrintingEngine(std::unique_ptr<IDataPrintingEngine>&& printing_engine) noexcept
    {
        if ( printing_engine == nullptr )
        {
            m_DataPrintingEngine = DataPrintingEngineFactory::Create();
        }
        else
        {
            m_DataPrintingEngine = std::move(printing_engine);
        }
    }

    /**
     * @brief Clear the threads.
     * The function joins all threads and clears the thread container.
     * @note The function is explicitly defined as noexcept.
     */
    void DataModule::ClearThreads() noexcept
    {
        for ( auto& thread : m_Threads )
        {
            if ( thread.joinable() )
            {
                thread.join();
            }
        }

        m_Threads.clear();
        SetThreadCancellation(false);
    }

    /**
     * @brief Check if the thread cancellation is requested.
     * The function returns true if the thread cancellation is requested, false otherwise.
     * @return True if the thread cancellation is requested, false otherwise.
     */
    bool DataModule::IsThreadCancellationRequested() const noexcept
    {
        return m_ThreadCancellation.load(std::memory_order_acquire);
    }

    /**
     * @brief Set the thread cancellation flag.
     * The function sets the thread cancellation flag to the specified value.
     * @param flag The value to set the thread cancellation flag.
     */
    void DataModule::SetThreadCancellation(const bool flag) noexcept
    {
        m_ThreadCancellation.store(flag, std::memory_order_release);
    }

    /**
     * @brief Generate random bytes.
     * The function generates a random number of random bytes.
     * @return A vector of random bytes.
     */
    std::vector<std::byte> DataModule::GenerateBytes() const noexcept
    {
        return GetGenerator().GetRandomBytes(GetGenerator().GetRandomNumber(1, 100));
    }

    /**
     * @brief Run the module asynchronously.
     * The function generates random bytes and searches for them in the generated data.
     * The function runs in multiple threads.
     * @note The function clears the threads and results before starting.
     * @note The function is explicitly defined as noexcept.
     */
    void DataModule::RunAsync() noexcept
    {
        ClearThreads();                                                                                         //!< Clear the threads. The threads are cleared before starting the asynchronous operation.
        {
            std::lock_guard lock{ m_ResultsMutex };                                                             //!< Lock the results mutex. The results mutex is locked before clearing the results.
            m_Results.clear();                                                                                  //!< Clear the results. The results are cleared before starting the asynchronous operation.
        }

        std::vector<std::vector<std::byte>> input_data(/* Count: */ 100);                                       //!< The input data to search for. The count is set to 100. The size of the input data is set to 100.
        std::generate(input_data.begin(), input_data.end(), std::bind_front(&DataModule::GenerateBytes, this)); //!< Generate the input data. The input data is generated using the GenerateBytes function.

        uint64_t       index                = 0;                                                                //!< The index of the thread. The index is set to 0.
        const uint64_t hardware_concurrency = std::thread::hardware_concurrency();                              //!< The number of hardware threads. The number of hardware threads is obtained using the hardware_concurrency function.
        const uint64_t thread_count         = hardware_concurrency == 0 ? 2 : hardware_concurrency;             //!< The number of threads. The number of threads is set to the hardware concurrency if it is not zero, otherwise it is set to 2.

        m_Threads.resize(thread_count);                                                                         //!< Resize the threads. The threads are resized to the number of threads.
        auto thread_function = [this](const std::vector<std::vector<std::byte>>& input_data)
        {
            while ( not IsThreadCancellationRequested() )                                                       //!< While the thread cancellation is not requested. The loop continues until the thread cancellation is requested.
            {
                auto source = GenerateBytes();                                                                  //!< Generate the source data. The source data is generated using the GenerateBytes function.

                for ( const auto& values_to_search : input_data )                                               //!< For each value to search in the input data. The loop iterates over the input data.
                {
                    if ( IsThreadCancellationRequested() )                                                      //!< If the thread cancellation is requested. The loop breaks if the thread cancellation is requested.
                    {
                        break;
                    }

                    if ( GetSearchEngine().Search(source, values_to_search) )                        //!< If the search engine finds the source in the values to search. The loop breaks if the search engine finds the source in the values to search.
                    {
                        std::lock_guard lock{ m_ResultsMutex };                                      //!< Lock the results mutex. The results mutex is locked before adding the result.
                        m_Results.push_back(std::make_tuple(std::time(nullptr), std::move(source))); //!< Add the result. The result is added to the results. The result is a tuple of the current time and the source data.
                        break;
                    }
                }

                std::this_thread::sleep_for(std::chrono::milliseconds{ 50 }); //!< Sleep for 50 milliseconds. The thread sleeps for 50 milliseconds after searching for the values.
            }
        };

        for ( index = 0; index < thread_count; ++index )
        {
            m_Threads[index] = std::thread(thread_function, input_data); //!< Start the thread. The thread is started with the thread function and the input data.
        }
    }

    void DataModule::StopAsync() noexcept
    {
        SetThreadCancellation(true); //!< Set the thread cancellation. The thread cancellation is set to true.
        ClearThreads();              //!< Clear the threads. The threads are cleared after setting the thread cancellation.
    }

    void DataModule::WaitForAsync(const std::chrono::milliseconds& milliseconds) const noexcept
    {
        std::this_thread::sleep_for(milliseconds); //!< Sleep for the specified milliseconds. The thread sleeps for the specified milliseconds.
    }

    void DataModule::PrintResults() const noexcept
    {
        std::lock_guard lock{ m_ResultsMutex };

        // Sort the results by time. The results are sorted by time before printing. The results are sorted in ascending order.
        // clang-format off
        std::sort(m_Results.begin(), m_Results.end(),
            [](const auto& lhs, const auto& rhs)
            {
                return std::get<0>(lhs) < std::get<0>(rhs);
            }
        );
        // clang-format on

        GetPrintingEngine().PrintLine(m_Results);
    }
} // namespace Program::Module::Internal
