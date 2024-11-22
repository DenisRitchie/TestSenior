#include "Module/DataSearchEngineFactory.hpp"
#include "Module/Internal/DataSearchEngine.hpp"

/**
 * @brief Create a data search engine
 * @return A unique pointer to the created data search engine
 * @note A unique pointer to the created data search engine
 */
std::unique_ptr<Program::Module::IDataSearchEngine> Program::Module::DataSearchEngineFactory::Create() noexcept
{
    return std::make_unique<Internal::DataSearchEngine>();
}
