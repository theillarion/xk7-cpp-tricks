#include <cstdio>
#include <cassert>
#include <sstream>

#include "my_api.h"

#include "utility/dl_loader.hpp"

static constexpr auto name_lib = "libxk7_api.so.0"; 

#define XK7_SUCCESS(MESSAGE, ...) std::fprintf(stdout, "\033[92m" MESSAGE "\033[0m\n", ##__VA_ARGS__);
#define XK7_FAILURE(MESSAGE, ...) std::fprintf(stderr, "\033[91m" MESSAGE "\033[0m\n", ##__VA_ARGS__);

#define XK7_ASSERT_EQ(LHS, RHS)                                                             \
[&]()                                                                                       \
{                                                                                           \
    std::ostringstream stream;                                                              \
    stream << "<" << LHS << ", " << RHS << ">";                                             \
    if (LHS != RHS)                                                                         \
    {                                                                                       \
        XK7_FAILURE("MISMATCH: %s (%s:%d)", stream.str().c_str(), __FILE__, __LINE__);      \
        exit(EXIT_FAILURE);                                                                 \
    }                                                                                       \
    else                                                                                    \
    {                                                                                       \
        XK7_SUCCESS("OK: %s", stream.str().c_str());                                        \
    }                                                                                       \
}()

int main()
{
    xk7::sys::DlLoader loader(name_lib);

    if (!loader)
    {
        XK7_FAILURE("Failed to load library: %s", loader.Error().value_or("unknown error").c_str());
        return EXIT_FAILURE;
    }
    XK7_SUCCESS("Loaded `%s` library", name_lib);

    // "Foo" symbol is expected to be loaded.
    auto foo = loader.LoadSymbol<decltype(&Foo)>("Foo");
    if (!foo)
    {
        XK7_FAILURE("Failed to load symbol: %s", loader.Error().value_or("unknown error").c_str());
        return EXIT_FAILURE;
    }
    XK7_SUCCESS("Loaded `Foo` symbol");
    XK7_ASSERT_EQ(foo(2, 3), 5);

    // "Bar" symbol is not expected to be loaded.
    auto bar = loader.LoadSymbol<decltype(&Bar)>("Bar");
    if (bar)
    {
        XK7_FAILURE("Loaded symbol: %s", loader.Error().value_or("unknown error").c_str());
        return EXIT_FAILURE;
    }
    XK7_SUCCESS("Failed to load `Bar` symbol: %s", loader.Error().value_or("unknown error").c_str());

    // "Sum" symbol is not expected to be loaded.
    auto sum = loader.LoadSymbol<int(*)(int, int)>("Sum");
    if (sum)
    {
        XK7_FAILURE("Loaded symbol: %s", loader.Error().value_or("unknown error").c_str());
        return EXIT_FAILURE;
    }
    XK7_SUCCESS("Failed to load `Sum` symbol: %s", loader.Error().value_or("unknown error").c_str());

    // "Multiply" symbol is not expected to be loaded.
    auto multiply = loader.LoadSymbol<int(*)(int, int)>("Multiply");
    if (multiply)
    {
        XK7_FAILURE("Loaded symbol: %s", loader.Error().value_or("unknown error").c_str());
        return EXIT_FAILURE;
    }
    XK7_SUCCESS("Failed to load `Multiply` symbol: %s", loader.Error().value_or("unknown error").c_str());

    return EXIT_SUCCESS;
}