#include <dlfcn.h>

#include "utility/dl_loader.hpp"

namespace xk7
{
namespace sys
{

DlLoader::DlLoader(const std::string& lib_name) : m_handle{::dlopen(lib_name.c_str(), RTLD_LAZY)}
{
}

DlLoader::~DlLoader() noexcept
{
    if (m_handle)
    {
        ::dlclose(m_handle);
    }
}

DlLoader::operator bool() const noexcept
{
    return m_handle != nullptr;
}

void* DlLoader::LoadRawSymbol(const std::string& symbol_name)
{
    return ::dlsym(m_handle, symbol_name.c_str());
}

std::optional<std::string> DlLoader::Error() const noexcept
{
    using Result = std::optional<std::string>;

    auto error = ::dlerror();
    return (error) ? Result{error} : Result{};
}

DlLoader::handler_type DlLoader::NativeHandler() const noexcept
{
    return m_handle;
}

} // namespace sys
} // namespace abak