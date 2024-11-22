#include "Module/DataGeneratorFactory.hpp"
#include "Module/Internal/DataGenerator.hpp"

/**
 * @brief Create a new instance of the data generator.
 * @return A new instance of the data generator.
 */
std::unique_ptr<Program::Module::IDataGenerator> Program::Module::DataGeneratorFactory::Create() noexcept
{
    return std::make_unique<Internal::DataGenerator>();
}
