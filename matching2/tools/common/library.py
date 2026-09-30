"""Read members of the toolkit's static libraries.

A ``library`` region is code the retail image took verbatim from one of the
MSVC runtime libraries shipped with the toolkit.  Its translation unit is named
``lib/<library>/<member>``, for example
``lib/libcmt.lib/build/intel/mt_obj/xtoa.obj``, and the build links the named
section of that member exactly as the original linker did.
"""
from pathlib import Path

LIBRARY_PREFIX = "lib/"


def ar_members(path):
    """Yield (name, blob) for every member of an ar archive.

    MSVC writes a long member name as an offset into the ``//`` string table,
    terminated by ``\\0`` when it holds a path and by ``/`` when it holds a flat
    name, so both terminators are accepted.
    """
    data = Path(path).read_bytes()
    if data[:8] != b"!<arch>\n":
        return
    offset, longnames = 8, b""
    while offset + 60 <= len(data):
        header = data[offset:offset + 60]
        offset += 60
        name = header[:16].decode("latin1").rstrip()
        try:
            size = int(header[48:58].decode().strip())
        except ValueError:
            return
        body = data[offset:offset + size]
        offset += size + (size & 1)
        if name == "//":
            longnames = body
            continue
        if name in ("/", "/SYM64/") or name == "":
            continue
        if name.startswith("/") and longnames:
            start = int(name[1:])
            stop = start
            while stop < len(longnames) and longnames[stop] not in (0x00, 0x2F, 0x0A):
                stop += 1
            name = longnames[start:stop].decode("latin1").replace("\\", "/")
        yield name, body


def is_library_source(source):
    return source.startswith(LIBRARY_PREFIX)


def library_source(library, member):
    return f"{LIBRARY_PREFIX}{library}/{member}"


def split_library_source(source):
    """Return (library file name, member path) for a library translation unit."""
    if not is_library_source(source):
        raise ValueError("not a library translation unit: " + source)
    library, _, member = source[len(LIBRARY_PREFIX):].partition("/")
    if not library.endswith(".lib") or not member or "/" in library:
        raise ValueError("malformed library translation unit: " + source)
    return library, member


def read_library_member(toolkit, source):
    """Return the one COFF member a library translation unit names."""
    library, member = split_library_source(source)
    blobs = [blob for name, blob in ar_members(Path(toolkit) / "lib" / library) if name == member]
    if len(blobs) != 1:
        raise ValueError(f"{source}: expected exactly one member, found {len(blobs)}")
    return blobs[0]
