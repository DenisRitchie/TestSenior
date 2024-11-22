#include "Module/ModuleFactory.hpp"
#include "Module/DataGeneratorFactory.hpp"
#include "Module/DataSearchEngineFactory.hpp"
#include "Module/DataPrintingEngineFactory.hpp"
#include "Module/Internal/DataModule.hpp"

/**
 * @brief Create a new instance of the module.
 * @return A new instance of the module.
 */
std::unique_ptr<Program::Module::IModule> Program::Module::ModuleFactory::Create() noexcept
{
    return std::make_unique<Internal::DataModule>();
}

/**
 * @brief Create a new instance of the data generator.
 * @return A new instance of the data generator.
 */
std::unique_ptr<Program::Module::IDataGenerator> Program::Module::ModuleFactory::CreateDataGenerator() noexcept
{
    return DataGeneratorFactory::Create();
}

/**
 * @brief Create a new instance of the data search engine.
 * @return A new instance of the data search engine.
 */
std::unique_ptr<Program::Module::IDataSearchEngine> Program::Module::ModuleFactory::CreateDataSearchEngine() noexcept
{
    return DataSearchEngineFactory::Create();
}

/**
 * @brief Create a new instance of the data printing engine.
 * @return A new instance of the data printing engine.
 */
std::unique_ptr<Program::Module::IDataPrintingEngine> Program::Module::ModuleFactory::CreateDataPrintingEngine() noexcept
{
    return DataPrintingEngineFactory::Create();
}
