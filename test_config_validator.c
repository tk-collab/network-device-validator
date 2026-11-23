#include "config_validator.h"
#include "unity/src/unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_vlan_id_negative(void)
{
    TEST_ASSERT_FALSE(is_valid_vlan_id(-1));
}

void test_vlan_id_zero(void)
{
    TEST_ASSERT_FALSE(is_valid_vlan_id(0));
}

void test_vlan_id_lower_boundary(void)
{
    TEST_ASSERT_TRUE(is_valid_vlan_id(1));
}

void test_vlan_id_above_lower_boundary(void)
{
    TEST_ASSERT_TRUE(is_valid_vlan_id(2));
}

void test_vlan_id_normal_value(void)
{
    TEST_ASSERT_TRUE(is_valid_vlan_id(100));
}

void test_vlan_id_below_upper_boundary(void)
{
    TEST_ASSERT_TRUE(is_valid_vlan_id(4093));
}

void test_vlan_id_upper_boundary(void)
{
    TEST_ASSERT_TRUE(is_valid_vlan_id(4094));
}

void test_vlan_id_above_upper_boundary(void)
{
    TEST_ASSERT_FALSE(is_valid_vlan_id(4095));
}

void test_vlan_id_exceeds_upper_limit(void)
{
    TEST_ASSERT_FALSE(is_valid_vlan_id(4096));
}

void test_all_vlan_ids_valid(void)
{
    int vlan_ids[] = {1, 100, 4094};
    TEST_ASSERT_TRUE(are_vlan_ids_valid(vlan_ids, 3));
}

void test_first_vlan_id_invalid(void)
{
    int vlan_ids[] = {0, 100, 4094};
    TEST_ASSERT_FALSE(are_vlan_ids_valid(vlan_ids, 3));
}

void test_middle_vlan_id_invalid(void)
{
    int vlan_ids[] = {1, 0, 4094};
    TEST_ASSERT_FALSE(are_vlan_ids_valid(vlan_ids, 3));
}

void test_last_vlan_id_invalid(void)
{
    int vlan_ids[] = {1, 100, 4095};
    TEST_ASSERT_FALSE(are_vlan_ids_valid(vlan_ids, 3));
}

void test_null_vlan_ids(void)
{
    TEST_ASSERT_FALSE(are_vlan_ids_valid(NULL, 3));
}

void test_zero_vlan_count(void)
{
    int vlan_ids[] = {1};
    TEST_ASSERT_FALSE(are_vlan_ids_valid(vlan_ids, 0));
}

void test_vlan_ids_from_middle_pointer_valid(void)
{
    int vlan_ids[] = {0, 100, 4094};

    TEST_ASSERT_TRUE(are_vlan_ids_valid(&vlan_ids[1], 2));
}

void test_vlan_ids_from_middle_pointer_invalid(void)
{
    int vlan_ids[] = {1, 100, 4095};

    TEST_ASSERT_FALSE(are_vlan_ids_valid(&vlan_ids[1], 2));
}

void test_vlan_id_list_all_valid(void)
{
    vlan_id_list_t list = {
        .vlan_ids = {1, 100, 4094},
        .count = 3
    };

    TEST_ASSERT_TRUE(is_valid_vlan_id_list(&list));
}

void test_vlan_id_list_contains_invalid_value(void)
{
    vlan_id_list_t list = {
        .vlan_ids = {1, 4095, 100},
        .count = 3
    };

    TEST_ASSERT_FALSE(is_valid_vlan_id_list(&list));
}

void test_vlan_id_list_zero_count(void)
{
    vlan_id_list_t list = {
        .vlan_ids = {1},
        .count = 0
    };

    TEST_ASSERT_FALSE(is_valid_vlan_id_list(&list));
}

void test_vlan_id_list_exceeds_capacity(void)
{
    vlan_id_list_t list = {
        .vlan_ids = {1},
        .count = MAX_VLAN_IDS + 1
    };

    TEST_ASSERT_FALSE(is_valid_vlan_id_list(&list));
}

void test_vlan_id_list_max_capacity(void)
{
    vlan_id_list_t list = {
        .vlan_ids = {
            1, 2, 3, 4, 5, 6, 7, 8,
            9, 10, 11, 12, 13, 14, 15, 16
        },
        .count = MAX_VLAN_IDS
    };

    TEST_ASSERT_TRUE(is_valid_vlan_id_list(&list));
}

void test_vlan_id_list_null_pointer(void)
{
    TEST_ASSERT_FALSE(is_valid_vlan_id_list(NULL));
}

void test_port_mode_access(void)
{
    TEST_ASSERT_TRUE(is_valid_port_mode(PORT_MODE_ACCESS));
}

void test_port_mode_trunk(void)
{
    TEST_ASSERT_TRUE(is_valid_port_mode(PORT_MODE_TRUNK));
}

void test_port_mode_invalid_negative(void)
{
    TEST_ASSERT_FALSE(is_valid_port_mode((port_mode_t)-1));
}

void test_port_mode_invalid_value(void)
{
    TEST_ASSERT_FALSE(is_valid_port_mode((port_mode_t)2));
}

void test_access_port_single_valid_vlan(void)
{
    port_config_t config = {
        .mode = PORT_MODE_ACCESS,
        .vlan_ids = {
            .vlan_ids = {100},
            .count = 1
        }
    };

    TEST_ASSERT_TRUE(is_valid_port_config(&config));
}

void test_access_port_multiple_vlans(void)
{
    port_config_t config = {
        .mode = PORT_MODE_ACCESS,
        .vlan_ids = {
            .vlan_ids = {100, 200},
            .count = 2
        }
    };

    TEST_ASSERT_FALSE(is_valid_port_config(&config));
}

void test_access_port_zero_vlans(void)
{
    port_config_t config = {
        .mode = PORT_MODE_ACCESS,
        .vlan_ids = {
            .vlan_ids = {0},
            .count = 0
        }
    };

    TEST_ASSERT_FALSE(is_valid_port_config(&config));
}

void test_access_port_invalid_vlan(void)
{
    port_config_t config = {
        .mode = PORT_MODE_ACCESS,
        .vlan_ids = {
            .vlan_ids = {4095},
            .count = 1
        }
    };

    TEST_ASSERT_FALSE(is_valid_port_config(&config));
}

void test_trunk_port_single_vlan(void)
{
    port_config_t config = {
        .mode = PORT_MODE_TRUNK,
        .vlan_ids = {
            .vlan_ids = {100},
            .count = 1
        }
    };

    TEST_ASSERT_TRUE(is_valid_port_config(&config));
}

void test_trunk_port_multiple_vlans(void)
{
    port_config_t config = {
        .mode = PORT_MODE_TRUNK,
        .vlan_ids = {
            .vlan_ids = {1, 100, 4094},
            .count = 3
        }
    };

    TEST_ASSERT_TRUE(is_valid_port_config(&config));
}

void test_trunk_port_zero_vlans(void)
{
    port_config_t config = {
        .mode = PORT_MODE_TRUNK,
        .vlan_ids = {
            .vlan_ids = {0},
            .count = 0
        }
    };

    TEST_ASSERT_FALSE(is_valid_port_config(&config));
}

void test_trunk_port_invalid_vlan(void)
{
    port_config_t config = {
        .mode = PORT_MODE_TRUNK,
        .vlan_ids = {
            .vlan_ids = {100, 4095},
            .count = 2
        }
    };

    TEST_ASSERT_FALSE(is_valid_port_config(&config));
}

void test_trunk_port_max_capacity(void)
{
    port_config_t config = {
        .mode = PORT_MODE_TRUNK,
        .vlan_ids = {
            .vlan_ids = {
                1, 2, 3, 4, 5, 6, 7, 8,
                9, 10, 11, 12, 13, 14, 15, 16
            },
            .count = MAX_VLAN_IDS
        }
    };

    TEST_ASSERT_TRUE(is_valid_port_config(&config));
}

void test_trunk_port_exceeds_capacity(void)
{
    port_config_t config = {
        .mode = PORT_MODE_TRUNK,
        .vlan_ids = {
            .vlan_ids = {100},
            .count = MAX_VLAN_IDS + 1
        }
    };

    TEST_ASSERT_FALSE(is_valid_port_config(&config));
}

void test_port_config_invalid_mode(void)
{
    port_config_t config = {
        .mode = (port_mode_t)2,
        .vlan_ids = {
            .vlan_ids = {100},
            .count = 1
        }
    };

    TEST_ASSERT_FALSE(is_valid_port_config(&config));
}

void test_port_config_null_pointer(void)
{
    TEST_ASSERT_FALSE(is_valid_port_config(NULL));
}

void test_duplicate_vlan_ids(void)
{
    vlan_id_list_t list = {
        .vlan_ids = {100, 100},
        .count = 2
    };

    TEST_ASSERT_FALSE(is_valid_vlan_id_list(&list));
}

void test_non_adjacent_duplicate_vlan_ids(void)
{
    vlan_id_list_t list = {
        .vlan_ids = {100, 200, 100},
        .count = 3
    };

    TEST_ASSERT_FALSE(is_valid_vlan_id_list(&list));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_vlan_id_negative);
    RUN_TEST(test_vlan_id_zero);
    RUN_TEST(test_vlan_id_lower_boundary);
    RUN_TEST(test_vlan_id_above_lower_boundary);
    RUN_TEST(test_vlan_id_normal_value);
    RUN_TEST(test_vlan_id_below_upper_boundary);
    RUN_TEST(test_vlan_id_upper_boundary);
    RUN_TEST(test_vlan_id_above_upper_boundary);
    RUN_TEST(test_vlan_id_exceeds_upper_limit);
    RUN_TEST(test_all_vlan_ids_valid);
    RUN_TEST(test_first_vlan_id_invalid);
    RUN_TEST(test_middle_vlan_id_invalid);
    RUN_TEST(test_last_vlan_id_invalid);
    RUN_TEST(test_null_vlan_ids);
    RUN_TEST(test_zero_vlan_count);
    RUN_TEST(test_vlan_ids_from_middle_pointer_valid);
    RUN_TEST(test_vlan_ids_from_middle_pointer_invalid);
    RUN_TEST(test_vlan_id_list_all_valid);
    RUN_TEST(test_vlan_id_list_contains_invalid_value);
    RUN_TEST(test_vlan_id_list_zero_count);
    RUN_TEST(test_vlan_id_list_exceeds_capacity);
    RUN_TEST(test_vlan_id_list_max_capacity);
    RUN_TEST(test_vlan_id_list_null_pointer);
    RUN_TEST(test_port_mode_access);
    RUN_TEST(test_port_mode_trunk);
    RUN_TEST(test_port_mode_invalid_negative);
    RUN_TEST(test_port_mode_invalid_value);
    RUN_TEST(test_access_port_single_valid_vlan);
    RUN_TEST(test_access_port_multiple_vlans);
    RUN_TEST(test_access_port_zero_vlans);
    RUN_TEST(test_access_port_invalid_vlan);
    RUN_TEST(test_trunk_port_single_vlan);
    RUN_TEST(test_trunk_port_multiple_vlans);
    RUN_TEST(test_trunk_port_zero_vlans);
    RUN_TEST(test_trunk_port_invalid_vlan);
    RUN_TEST(test_trunk_port_max_capacity);
    RUN_TEST(test_trunk_port_exceeds_capacity);
    RUN_TEST(test_port_config_invalid_mode);
    RUN_TEST(test_port_config_null_pointer);
    RUN_TEST(test_duplicate_vlan_ids);
    RUN_TEST(test_non_adjacent_duplicate_vlan_ids);
    
    return UNITY_END();
}