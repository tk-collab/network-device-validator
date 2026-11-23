# Test Specification
## Network Device Configuration Validator

## 1. Test Environment

| Item | Description |
|---|---|
| Language | C |
| Standard | C11 |
| Compiler | GCC 16.2.0 |
| Test Framework | Unity |
| Coverage Tool | gcov |

## 2. Test Target

### 2.1 VLAN ID Validation

Function: `is_valid_vlan_id()`

- Valid range: 1?4094 (inclusive)

| ID | Input | Expected | Test Purpose |
|---|---:|---|---|
| TC01 | -1 | false | Negative value |
| TC02 | 0 | false | Below lower boundary |
| TC03 | 1 | true | Lower boundary |
| TC04 | 2 | true | Above lower boundary |
| TC05 | 100 | true | Normal value |
| TC06 | 4093 | true | Below upper boundary |
| TC07 | 4094 | true | Upper boundary |
| TC08 | 4095 | false | Above upper boundary |
| TC09 | 4096 | false | Exceeds upper limit |

### 2.2 VLAN Array Validation

Function: `are_vlan_ids_valid()`

| ID | Input | Expected | Test Purpose |
|---|---|---|---|
| TC10 | {1, 100, 4094}, count=3 | true | All VLAN IDs valid |
| TC11 | {0, 100, 4094}, count=3 | false | First element invalid |
| TC12 | {1, 0, 4094}, count=3 | false | Middle element invalid |
| TC13 | {1, 100, 4095}, count=3 | false | Last element invalid |
| TC14 | NULL, count=3 | false | NULL pointer |
| TC15 | {1}, count=0 | false | Zero elements |

### 2.3 Pointer Validation

Function: `are_vlan_ids_valid()`

| ID | Input | Expected | Test Purpose |
|---|---|---|---|
| TC16 | {0, 100, 4094}, pointer=&array[1], count=2 | true | Valid sub-array |
| TC17 | {1, 100, 4095}, pointer=&array[1], count=2 | false | Invalid value in sub-array |

### 2.4 VLAN List Structure Validation

Function: `is_valid_vlan_id_list()`

- Maximum capacity: 16 VLAN IDs.
- Duplicate VLAN IDs are not allowed.

| ID | Input | Expected | Test Purpose |
|---|---|---|---|
| TC18 | {1, 100, 4094}, count=3 | true | All elements valid |
| TC19 | {1, 4095, 100}, count=3 | false | Contains invalid VLAN ID |
| TC20 | {1}, count=0 | false | Zero elements |
| TC21 | count=17 | false | Exceeds capacity |
| TC22 | VLAN IDs 1?16, count=16 | true | Maximum capacity |
| TC23 | NULL | false | NULL pointer |
| TC40 | {100, 100}, count=2 | false | Duplicate VLAN IDs |
| TC41 | {100, 200, 100}, count=3 | false | Non-adjacent duplicate VLAN IDs |

### 2.5 Port Mode Validation

Function: `is_valid_port_mode()`

| ID | Input | Expected | Test Purpose |
|---|---|---|---|
| TC24 | PORT_MODE_ACCESS | true | Valid ACCESS mode |
| TC25 | PORT_MODE_TRUNK | true | Valid TRUNK mode |
| TC26 | -1 | false | Negative enum value |
| TC27 | 2 | false | Undefined enum value |

### 2.6 Port Configuration Validation

Function: `is_valid_port_config()`

Specification:

- ACCESS mode: Exactly one valid VLAN ID.
- TRUNK mode: One to 16 valid VLAN IDs.
- Undefined port modes are rejected.

| ID | Input | Expected | Test Purpose |
|---|---|---|---|
| TC28 | ACCESS, {100}, count=1 | true | Valid ACCESS configuration |
| TC29 | ACCESS, {100, 200}, count=2 | false | Multiple VLANs in ACCESS |
| TC30 | ACCESS, count=0 | false | No VLAN in ACCESS |
| TC31 | ACCESS, {4095}, count=1 | false | Invalid VLAN ID |
| TC32 | TRUNK, {100}, count=1 | true | Single VLAN in TRUNK |
| TC33 | TRUNK, {1, 100, 4094}, count=3 | true | Multiple valid VLANs |
| TC34 | TRUNK, count=0 | false | No VLAN in TRUNK |
| TC35 | TRUNK, {100, 4095}, count=2 | false | Invalid VLAN ID |
| TC36 | TRUNK, VLAN IDs 1?16, count=16 | true | Maximum capacity |
| TC37 | TRUNK, count=17 | false | Exceeds capacity |
| TC38 | Undefined mode (2) | false | Invalid port mode |
| TC39 | NULL | false | NULL pointer |

## 3. Test Design Techniques

- Boundary Value Analysis (BVA)
- Normal and abnormal input testing
- Pointer validation
- NULL pointer testing
- Structure validation
- Enum validation
- Branch testing
- Array capacity boundary testing

## 4. Test Results

| Item | Result |
|---|---:|
| Total Test Cases | 39 |
| Passed | 39 |
| Failed | 0 |

## 5. Code Coverage

Tool: GCC gcov

Target: config_validator.c

| Metric | Result |
|---|---:|
| Line Coverage | 100% (34/34) |
| Branches Executed | 100% (25/25) |
| Branches Taken at Least Once | 100% (25/25) |

Note: 100% code coverage does not guarantee that the software is free of defects.