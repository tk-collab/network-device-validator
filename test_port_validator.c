#include <stddef.h>

#include "port_validator.h"
#include "unity/src/unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_port_number_lower_boundary(void)
{
    TEST_ASSERT_TRUE(is_valid_port_number("1"));
}

void test_port_number_upper_boundary(void)
{
    TEST_ASSERT_TRUE(is_valid_port_number("65535"));
}

void test_port_number_normal_value(void)
{
    TEST_ASSERT_TRUE(is_valid_port_number("10000"));
}

void test_port_number_zero_is_invalid(void)
{
    TEST_ASSERT_FALSE(is_valid_port_number("0"));
}

void test_port_number_above_upper_boundary_is_invalid(void)
{
    TEST_ASSERT_FALSE(is_valid_port_number("65536"));
}

void test_port_number_empty_string_is_invalid(void)
{
    TEST_ASSERT_FALSE(is_valid_port_number(""));
}

void test_port_number_null_pointer_is_invalid(void)
{
    TEST_ASSERT_FALSE(is_valid_port_number(NULL));
}

void test_port_number_uppercase_letter_is_invalid(void)
{
    TEST_ASSERT_FALSE(is_valid_port_number("44A3"));
}

void test_port_number_lowercase_letter_is_invalid(void)
{
    TEST_ASSERT_FALSE(is_valid_port_number("44a3"));
}

void test_port_number_symbol_is_invalid(void)
{
    TEST_ASSERT_FALSE(is_valid_port_number("44#3"));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_port_number_lower_boundary);
    RUN_TEST(test_port_number_upper_boundary);
    RUN_TEST(test_port_number_normal_value);
    RUN_TEST(test_port_number_zero_is_invalid);
    RUN_TEST(test_port_number_above_upper_boundary_is_invalid);
    RUN_TEST(test_port_number_empty_string_is_invalid);
    RUN_TEST(test_port_number_null_pointer_is_invalid);
    RUN_TEST(test_port_number_uppercase_letter_is_invalid);
    RUN_TEST(test_port_number_lowercase_letter_is_invalid);
    RUN_TEST(test_port_number_symbol_is_invalid);

    return UNITY_END();
}
