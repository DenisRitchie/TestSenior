#ifndef __HELPER_OSTREAM_JOINER_HPP__ // clang-format off
#define __HELPER_OSTREAM_JOINER_HPP__ // clang-format on

#include <iterator>
#include <iosfwd>
#include <type_traits>
#include <functional>
#include "Helpers/semiregular_box.hpp"

namespace Program::Helpers
{
    namespace Details
    {
        /**
         * @brief Default callback for ostream_joiner
         */
        struct OstreamJoinerCallback
        {
            /**
             * @brief Default callback for ostream_joiner
             */
            template<typename TStream, typename TValue>
            void operator()(TStream& os, const TValue& value) const
            {
                os << value;
            }
        };
    } // namespace Details

    /**
     * @brief ostream_joiner
     * @details ostream_joiner is an output iterator that writes elements to a std::basic_ostream
     * separated by a delimiter. The delimiter is written to the stream before each element except the first.
     * The elements are written to the stream using a callback function.
     *
     * @tparam TDelimiter Delimiter type
     * @tparam TChar      Character type
     * @tparam TTraits    Traits type
     * @tparam TCallback  Callback type
     */
    template<typename TDelimiter, typename TChar, typename TTraits, typename TCallback>
    class ostream_joiner
    {
    public:
        using char_type         = TChar;                              //!< Character type
        using traits_type       = TTraits;                            //!< Traits type of the stream type used by the ostream_joiner
        using ostream_type      = std::basic_ostream<TChar, TTraits>; //!< Output stream type
        using iterator_category = std::output_iterator_tag;           //!< Iterator category
        using value_type        = void;                               //!< Value type
        using difference_type   = void;                               //!< Difference type
        using pointer           = void;                               //!< Pointer type
        using reference         = void;                               //!< Reference type

        /**
         * @brief Construct a new ostream_joiner object
         * @details Construct a new ostream_joiner object
         * with the specified output stream, delimiter, and callback.
         * The callback is a function object that is called for each element written to the stream.
         * The callback must have the signature void(TStream&, const TValue&), where TStream is the output stream type and TValue is the element type.
         * The default callback writes the element to the stream using the stream's operator<<.
         * The callback can be any function object that can be called with the specified signature.
         * The callback can be a lambda, a function object, or a function pointer.
         *
         * @param os        Output stream
         * @param delimiter Delimiter
         * @param callback  Callback
         */
        ostream_joiner(ostream_type& os, const TDelimiter& delimiter, const TCallback& callback)
            : m_Output{ std::addressof(os) }
            , m_Delimiter{ delimiter }
            , m_Callback{ callback }
            , m_First{ true }
        {
        }

        /**
         * @brief Construct a new ostream_joiner object
         * @details Construct a new ostream_joiner object
         * with the specified output stream, delimiter, and callback.
         * The callback is a function object that is called for each element written to the stream.
         * The callback must have the signature void(TStream&, const TValue&), where TStream is the output stream type and TValue is the element type.
         * The default callback writes the element to the stream using the stream's operator<<.
         * The callback can be any function object that can be called with the specified signature.
         * The callback can be a lambda, a function object, or a function pointer.
         *
         * @param os        Output stream
         * @param delimiter Delimiter
         * @param callback  Callback
         */
        ostream_joiner(ostream_type& os, TDelimiter&& delimiter, TCallback&& callback)
            : m_Output{ std::addressof(os) }
            , m_Delimiter{ std::move(delimiter) }
            , m_Callback{ std::move(callback) }
            , m_First{ true }
        {
        }

        /**
         * @brief Copy assignment operator
         * @details Copy assignment operator
         * that writes the specified value to the output stream using the callback.
         * The delimiter is written to the stream before the value if this is not the first element.
         * The value is written to the stream using the callback.
         * The callback must have the signature void(TStream&, const TValue&), where TStream is the output stream type and TValue is the element type.
         * The default callback writes the element to the stream using the stream's operator<<.
         * The callback can be any function object that can be called with the specified signature.
         * The callback can be a lambda, a function object, or a function pointer.
         *
         * @tparam TValue Value type
         * @param value Value
         * @return ostream_joiner&
         */
        template<typename TValue>
        ostream_joiner& operator=(const TValue& value)
        {
            if ( not m_First )
            {
                *m_Output << m_Delimiter;
            }

            m_First = false;
            std::invoke(m_Callback, *m_Output, value);

            return *this;
        }

        /**
         * @brief Dereference operator
         * @details Dereference operator
         * that returns a reference to the ostream_joiner object.
         * @return ostream_joiner&
         */
        ostream_joiner& operator*() noexcept
        {
            return *this;
        }

        /**
         * @brief Pre-increment operator
         * @details Pre-increment operator
         * that returns a reference to the ostream_joiner object.
         * @return ostream_joiner&
         */
        ostream_joiner& operator++() noexcept
        {
            return *this;
        }

        /**
         * @brief Post-increment operator
         * @details Post-increment operator
         * that returns a reference to the ostream_joiner object.
         * @return ostream_joiner&
         */
        ostream_joiner& operator++(int32_t) noexcept
        {
            return *this;
        }

    private:
        ostream_type*                m_Output;    //!< Output stream
        TDelimiter                   m_Delimiter; //!< Delimiter
        semiregular_box_t<TCallback> m_Callback;  //!< Callback
        bool                         m_First;     //!< First element flag (true if this is the first element)
    };

    /**
     * @brief Make ostream_joiner
     * @details Make ostream_joiner
     * with the specified output stream, delimiter.
     *
     * @tparam TChar      Character type
     * @tparam TTraits    Traits type
     * @tparam TDelimiter Delimiter type
     *
     * @param os        Output stream
     * @param delimiter Delimiter
     * @return ostream_joiner<std::decay_t<TDelimiter>, TChar, TTraits, TCallback>
     */
    template<typename TChar, typename TTraits, typename TDelimiter>
    inline ostream_joiner<std::decay_t<TDelimiter>, TChar, TTraits, Details::OstreamJoinerCallback> make_ostream_joiner(std::basic_ostream<TChar, TTraits>& os, TDelimiter&& delimiter)
    {
        return { os, std::forward<TDelimiter>(delimiter), Details::OstreamJoinerCallback{} };
    }

    /**
     * @brief Make ostream_joiner
     * @details Make ostream_joiner
     * with the specified output stream, delimiter, and callback.
     * The callback is a function object that is called for each element written to the stream.
     * The callback must have the signature void(TStream&, const TValue&), where TStream is the output stream type and TValue is the element type.
     * The default callback writes the element to the stream using the stream's operator<<.
     * The callback can be any function object that can be called with the specified signature.
     * The callback can be a lambda, a function object, or a function pointer.
     *
     * @tparam TChar      Character type
     * @tparam TTraits    Traits type
     * @tparam TDelimiter Delimiter type
     * @tparam TCallback  Callback type
     *
     * @param os        Output stream
     * @param delimiter Delimiter
     * @param callback  Callback
     *
     * @return ostream_joiner<std::decay_t<TDelimiter>, TChar, TTraits, TCallback>
     */
    template<typename TChar, typename TTraits, typename TDelimiter, typename TCallback>
    inline ostream_joiner<std::decay_t<TDelimiter>, TChar, TTraits, TCallback> make_ostream_joiner(std::basic_ostream<TChar, TTraits>& os, TDelimiter&& delimiter, TCallback&& callback)
    {
        return { os, std::forward<TDelimiter>(delimiter), std::forward<TCallback>(callback) };
    }
} // namespace Program::Helpers

#endif // __HELPER_OSTREAM_JOINER_HPP__
