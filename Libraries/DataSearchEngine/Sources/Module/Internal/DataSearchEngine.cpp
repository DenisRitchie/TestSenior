#include "Module/Internal/DataSearchEngine.hpp"
#include <algorithm>
#include <functional>

/**
 * @brief Search for a sequence of bytes in a source sequence.
 * @param source The source sequence.
 * @param values_to_search The sequence of bytes to search for.
 * @return The index of the first occurrence of the sequence of bytes in the source sequence, or std::nullopt if the sequence of bytes is not found.
 */
std::optional<int32_t> Program::Module::Internal::DataSearchEngine::Search(const std::vector<std::byte>& source, const std::vector<std::byte> values_to_search) const noexcept
{
    if ( source.empty() || values_to_search.empty() )
    {
        return std::nullopt;
    }

    const std::boyer_moore_searcher searcher(values_to_search.cbegin(), values_to_search.cend()); //!< Boyer-Moore algorithm is used for searching.

    const auto iterator_result = std::search(source.cbegin(), source.cend(), searcher);

    if ( iterator_result == source.cend() )
    {
        return std::nullopt;
    }

    return static_cast<int32_t>(std::distance(source.cbegin(), iterator_result));
}
