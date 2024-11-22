#include "Module/DataPrintingEngineFactory.hpp"
#include "Module/Internal/DataPrintingEngine.hpp"

/**
 * @brief Creates a new instance of the Data Printing Engine.
 * @return A new instance of the Data Printing Engine.
 * @note The function is noexcept.
 * @note The function is marked as noexcept to ensure that the function does not throw exceptions.
 */
std::unique_ptr<Program::Module::IDataPrintingEngine> Program::Module::DataPrintingEngineFactory::Create() noexcept
{
    return std::make_unique<Internal::DataPrintingEngine>();
}
