# Matching source progress

Generated from [regions.json](regions.json) with `make progress-update`.

| Source classification | Regions | Bytes |
| --- | ---: | ---: |
| Ordinary C++ | 69 | 3,947 |
| Inline assembly | 2,789 | 381,576 |
| Embedded .text data | 73 | 11,267 |
| Padding | 1,936 | 15,882 |
| Total .text | 4,867 | 412,672 |

These are source-manifest classifications, not a fresh build result.
Regions can be function fragments; their count is not an original function count.
Assembly, data, and padding do not count as ordinary C++ recovery.
Readability requires source review. Run `make verify` to check exact executable output.
