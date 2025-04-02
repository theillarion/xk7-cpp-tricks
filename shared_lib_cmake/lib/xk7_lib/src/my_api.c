#include "calculator.h"

#include "my_api.h"

int FooImpl(int lhs, int rhs)
{
    return Sum(lhs, rhs);
}

int Foo(int lhs, int rhs)
{
    return FooImpl(lhs, rhs);
}

int Bar(int lhs, int rhs)
{
    return Multiply(lhs, rhs);
}
