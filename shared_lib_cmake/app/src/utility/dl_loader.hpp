#pragma once

#include <string>
#include <type_traits>
#include <optional>

namespace xk7
{
namespace sys
{

#pragma GCC diagnostic push // raw pointer
#pragma GCC diagnostic ignored "-Weffc++"

/**
 * RAII class for loading symbols from dynamic library
 */
class DlLoader
{
public:
    using handler_type = void*;

    /**
     * @brief Open dynamic library
     * @param[in] lib_name - name of dynamic library
     */
    explicit DlLoader(const std::string& lib_name);

    /**
     * @brief Close dynamic library
     */
    ~DlLoader() noexcept;

    /**
     * @brief Object health check
     * @return true if dynamic library is loaded successfully
    */
    operator bool() const noexcept;

    /**
     * @brief Get a raw pointer to a symbol
     * @param[in] symbol_name - symbol (function) name
     * @return raw symbol pointer
     */
    void* LoadRawSymbol(const std::string& symbol_name);

    /**
     * @brief Get a pointer to a symbol
     * @param[in] symbol_name - symbol (function) name
     * @return symbol pointer (if possible)
     */
    template<typename SymbolPtr, typename = std::enable_if_t<std::is_pointer<SymbolPtr>::value>>
    inline SymbolPtr LoadSymbol(const std::string& symbol_name)
    {
        return reinterpret_cast<SymbolPtr>(LoadRawSymbol(symbol_name));
    }

    /**
     * @brief Get the lastest error
     * @note Call it again will not return an error
     * @return last error (if possible)
    */
    std::optional<std::string> Error() const noexcept;

    /**
     * @brief Get library handler
     * @return native handler
    */
    handler_type NativeHandler() const noexcept;

private:
    handler_type m_handle{nullptr};    // Library handler
};

#pragma GCC diagnostic pop

} // namespace sys
} // namespace abak