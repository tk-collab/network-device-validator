# Test Cases: Port Number Validation

- Specification ID: SPEC-PORT-001
- Specification version: 1.0
- Scope: REQ-001 through REQ-006
- Status: Draft

## 1. Test Cases

The input is a string representing a port number, except for TC-007, where the test passes a NULL pointer directly to the function.

| Test Case ID | Requirement ID | Input | Expected Result | Purpose |
|---|---|---|---|---|
| TC-001 | REQ-001 | `"1"` | `VALID` | Verify the lower boundary of the valid range. |
| TC-002 | REQ-001 | `"65535"` | `VALID` | Verify the upper boundary of the valid range. |
| TC-003 | REQ-001 | `"10000"` | `VALID` | Verify a representative integer within the valid range. |
| TC-004 | REQ-002 | `"0"` | `INVALID` | Verify that zero is rejected. |
| TC-005 | REQ-003 | `"65536"` | `INVALID` | Verify that an integer immediately above the upper boundary is rejected. |
| TC-006 | REQ-004 | `""` | `INVALID` | Verify that an empty string is rejected. |
| TC-007 | REQ-005 | `NULL` (null pointer) | `INVALID` | Verify that a NULL pointer is rejected. Pass NULL from the test code; it is not keyboard input. |
| TC-008 | REQ-006 | `"44A3"` | `INVALID` | Verify that an input containing an uppercase English letter is rejected. |
| TC-009 | REQ-006 | `"44a3"` | `INVALID` | Verify that an input containing a lowercase English letter is rejected. |
| TC-010 | REQ-006 | `"44#3"` | `INVALID` | Verify that an input containing a symbol is rejected. |

## 2. Notes

- Ordinary inputs are represented as strings because the specification defines the input as a string representing a port number.
- `""` is an empty string. It is different from `NULL`, which is a null pointer.
- TC-007 must call the function with a NULL pointer in test code. Typing the four characters `NULL` would instead pass the string `"NULL"`.
- The unresolved input formats listed in the specification (whitespace, signs, leading zeros, decimal points, non-ASCII digits, and very long digit strings) are excluded until the specification owner clarifies their expected behavior.
- These test cases cover the currently specified requirements. They do not establish behavior for unspecified input formats.
