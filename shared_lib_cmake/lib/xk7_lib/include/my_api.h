#pragma once

#define PUBLIC_API __attribute__ ((visibility("default")))

/**
 * @brief Sum of two operands
 * @param[in] lhs - left operand
 * @param[in] rhs - right operand
 * @return sum left and right operand
 */
PUBLIC_API int Foo(int lhs, int rhs);

/**
 * @brief Multiply of two operands
 * @param[in] lhs - left operand
 * @param[in] rhs - right operand
 * @return multiply left and right operand
 */
int Bar(int lhs, int rhs);
