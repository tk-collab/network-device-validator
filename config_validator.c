#include "config_validator.h"

bool is_valid_vlan_id(int vlan_id)
{
    return (vlan_id >= 1 && vlan_id <= 4094);
}

bool are_vlan_ids_valid(const int *vlan_ids, size_t count)
{
    if (vlan_ids == NULL || count == 0)
    {
        return false;
    }

    const int *current = vlan_ids;

    for (size_t i = 0; i < count; i++, current++)
    {
        if (!is_valid_vlan_id(*current))
        {
            return false;
        }
    }

    return true;
}

bool is_valid_vlan_id_list(const vlan_id_list_t *list)
{
    if (list == NULL)
    {
        return false;
    }

    if (list->count > MAX_VLAN_IDS)
    {
        return false;
    }

    return are_vlan_ids_valid(list->vlan_ids, list->count);
}

bool is_valid_port_mode(port_mode_t mode)
{
    switch (mode)
    {
        case PORT_MODE_ACCESS:
        case PORT_MODE_TRUNK:
            return true;    

        default:
            return false;
    }
}

bool is_valid_port_config(const port_config_t *config)
{
    if (config == NULL)
    {
        return false;
    }

    switch (config->mode)
    {
        case PORT_MODE_ACCESS:
            if (config->vlan_ids.count != 1)
            {
                return false;
            }
            return is_valid_vlan_id_list(&config->vlan_ids);

        case PORT_MODE_TRUNK:
            return is_valid_vlan_id_list(&config->vlan_ids);

        default:
            return false;
    }
}