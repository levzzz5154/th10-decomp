# Matching source progress

Generated from [regions.json](regions.json) with `make progress-update`.

| Source classification | Regions | Bytes |
| --- | ---: | ---: |
| Ordinary C++ | 49 | 1,903 |
| Inline assembly | 2,810 | 383,617 |
| Embedded .text data | 73 | 11,267 |
| Padding | 1,937 | 15,885 |
| Total .text | 4,869 | 412,672 |

These are source-manifest classifications, not a fresh build result.
Regions can be function fragments; their count is not an original function count.
Assembly, data, and padding do not count as ordinary C++ recovery.
Readability requires source review. Run `make verify` to check exact executable output.
