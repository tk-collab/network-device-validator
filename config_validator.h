#ifndef CONFIG_VALIDATOR_H
#define CONFIG_VALIDATOR_H

#include <stdbool.h>
#include <stddef.h>

#define MAX_VLAN_IDS 16

typedef struct
{
    int vlan_ids[MAX_VLAN_IDS];
    size_t count;
} vlan_id_list_t;

typedef enum
{
    PORT_MODE_ACCESS,
    PORT_MODE_TRUNK
} port_mode_t;

typedef struct
{
    port_mode_t mode;
    vlan_id_list_t vlan_ids;
} port_config_t;

bool is_valid_vlan_id(int vlan_id);

bool are_vlan_ids_valid(const int *vlan_ids, size_t count);

bool is_valid_vlan_id_list(const vlan_id_list_t *list);

bool is_valid_port_mode(port_mode_t mode);

bool is_valid_port_config(const port_config_t *config);

#endif