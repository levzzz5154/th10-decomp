# Shared executable data

`data/` contains the supported executable's non-code section payloads, DOS
header, and Rich metadata. The assembly and MSVC builds use the same files.
Their separate `pe_layout.json` manifests resolve these paths relative to the
manifest and verify exact asset sizes and SHA-256 hashes before packaging.

The five payloads were consolidated from identical copies in `asm/data/` and
`msvc/data/`; their bytes and recorded hashes did not change. DOS executable
instructions remain source-owned by each build, outside this directory.
