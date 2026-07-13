# Tools CMake for th10 decomp
# These are Python-based utilities for data extraction and analysis

add_custom_target(run_tools
    COMMAND echo "Available tools:"
    COMMAND echo "  python3 tools/msg10_decoder.py <file.msg>         - Decode dialogue messages"
    COMMAND echo "  python3 tools/extract_dat.py <file.dat> <out_dir> - Extract DAT archive"
    COMMAND echo "  python3 tools/ecl_dump.py <file.ecl>              - Dump ECL script"
    COMMAND echo "  python3 tools/anm_viewer.py <file.anm>            - View ANM sprites"
)
