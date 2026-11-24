#!/usr/bin/env python3
"""Build non-code PE sections (.data, .rdata, .rsrc) from source manifests.

Each section manifest declares how to assemble its bytes without relying on
committed retail binary dumps:
  - ``library``: extract a section from an MSVC 7.1 toolkit ``.lib`` member and
    apply its COFF ``DIR32`` relocations.
  - ``cpp``: compile a maintained C++ source file with MSVC 7.1 ``cl.exe``
    (content-addressed cached), extract its placed data/const sections, and
    apply COFF ``DIR32`` relocations against project symbols.
  - ``pointer_table``: emit an array of 32-bit addresses or constants.
  - ``import_table``: emit a Win32 Import Directory, ILTs, IATs, and Hint/Name
    strings from a declarative DLL/symbol list.
  - ``rsrc``: emit a Win32 ``.rsrc`` section from declarative dialog, group
    icon, and icon bitmap definitions (optionally extracting copyrighted icon
    pixels from a user-supplied retail executable).
  - ``bytes``: emit small explicit byte runs (e.g., alignment/sentinel bytes).
"""

from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct
import subprocess
import tempfile
from typing import Any, Mapping

from matching2.tools.common.library import ar_members
from matching2.tools.common.wine import compiler_environment, winpath

IMAGE_REL_I386_DIR32 = 0x0006
IMAGE_REL_I386_DIR32NB = 0x0007


class NoncodeSectionError(RuntimeError):
    """A non-code section manifest could not be built or verified."""


def _int(value: Any, field: str) -> int:
    if isinstance(value, bool):
        raise NoncodeSectionError(f"{field} must be an integer")
    if isinstance(value, int):
        return value
    if isinstance(value, str):
        try:
            return int(value, 0)
        except ValueError as exc:
            raise NoncodeSectionError(f"{field} is not an integer: {value!r}") from exc
    raise NoncodeSectionError(f"{field} must be an integer")


def _resolve_addr(value: Any, symbols: Mapping[str, int], field: str) -> int:
    if isinstance(value, int) and not isinstance(value, bool):
        return value
    if isinstance(value, str):
        if value in symbols:
            return symbols[value]
        if "+" in value:
            base_name, off_s = value.split("+", 1)
            if base_name in symbols:
                return symbols[base_name] + int(off_s, 0)
        try:
            return int(value, 0)
        except ValueError as exc:
            raise NoncodeSectionError(f"unresolved symbol for {field}: {value!r}") from exc
    raise NoncodeSectionError(f"invalid address for {field}: {value!r}")


def _parse_coff(raw: bytes) -> tuple[list[dict[str, Any]], list[dict[str, Any]]]:
    """Parse COFF sections, relocations, and symbol table from raw .obj bytes."""
    machine, nsec, _ts, symoff, nsym, opt, _chars = struct.unpack_from("<HHIIIHH", raw, 0)
    if machine != 0x014C:
        raise NoncodeSectionError(f"expected i386 COFF object, got machine {machine:#x}")
    str_off = symoff + nsym * 18

    def read_name(name_b: bytes) -> str:
        if name_b.startswith(b"/"):
            so = int(name_b[1:].rstrip(b"\0"))
            end = raw.index(b"\0", str_off + so)
            return raw[str_off + so:end].decode("ascii", errors="replace")
        return name_b.rstrip(b"\0").decode("ascii", errors="replace")

    section_list: list[dict[str, Any]] = []
    pos = 20 + opt
    for idx in range(nsec):
        name_b, _vsz, _va, rsz, rptr, relptr, _lptr, nrel, _nl, schars = struct.unpack_from(
            "<8sIIIIIIHHI", raw, pos
        )
        pos += 40
        name = read_name(name_b)
        sdata = raw[rptr:rptr + rsz] if (rptr and rsz) else b""
        relocs = []
        if relptr and nrel:
            for j in range(nrel):
                roff, symi, rtype = struct.unpack_from("<IIH", raw, relptr + j * 10)
                relocs.append({"offset": roff, "symbol_index": symi, "type": rtype})
        entry = {"index": idx + 1, "name": name, "data": sdata, "relocations": relocs, "chars": schars}
        section_list.append(entry)

    symbols: list[dict[str, Any]] = [{}] * nsym
    i = 0
    while i < nsym:
        soff = symoff + i * 18
        n8 = raw[soff:soff + 8]
        val, sec_num, stype, sclass, naux = struct.unpack_from("<IhHBB", raw, soff + 8)
        z, so = struct.unpack_from("<II", n8, 0)
        if z == 0:
            end = raw.index(b"\0", str_off + so)
            sname = raw[str_off + so:end].decode("ascii", errors="replace")
        else:
            sname = n8.rstrip(b"\0").decode("ascii", errors="replace")
        symbols[i] = {"name": sname, "value": val, "section": sec_num, "class": sclass}
        i += 1 + naux

    return section_list, symbols


def _compile_cpp(source_path: Path, project_root: Path, toolkit: Path,
                 cache_dir: Path | None, extra_flags: list[str]) -> bytes:
    """Compile a C++ data unit with MSVC 7.1 cl.exe, with content-addressed caching."""
    compiler = toolkit / "bin" / "cl.exe"
    if not compiler.is_file():
        raise NoncodeSectionError(f"MSVC compiler not found at {compiler}")
    src_bytes = source_path.read_bytes()
    h = hashlib.sha256()
    h.update(b"noncode-cpp-v1\0")
    h.update(str(source_path.resolve()).encode() + b"\0" + src_bytes)
    h.update(repr(extra_flags).encode() + b"\0")
    h.update(compiler.read_bytes())
    cache_key = h.hexdigest()
    if cache_dir is not None:
        cache_dir.mkdir(parents=True, exist_ok=True)
        cached = cache_dir / f"{cache_key}.obj"
        if cached.is_file():
            return cached.read_bytes()

    env = compiler_environment(toolkit)
    with tempfile.TemporaryDirectory(prefix="noncode-") as td:
        work = Path(td)
        obj = work / "unit.obj"
        cmd = [
            "wine", str(compiler),
            "/nologo", "/c", "/TP", "/O2", "/Gy", "/GF", "/MT", "/DNDEBUG",
            *extra_flags,
            "/I" + winpath(project_root / "include"),
            "/Fo" + winpath(obj),
            winpath(source_path),
        ]
        proc = subprocess.run(cmd, env=env, cwd=work, capture_output=True, text=True, timeout=120)
        if proc.returncode != 0 or not obj.is_file():
            raise NoncodeSectionError(
                f"cl.exe failed compiling {source_path} (rc={proc.returncode}):\n{proc.stdout}\n{proc.stderr}"
            )
        raw = obj.read_bytes()
    if cache_dir is not None:
        (cache_dir / f"{cache_key}.obj").write_bytes(raw)
    return raw


def _apply_relocations(buf: bytearray, relocs: list[dict[str, Any]], coff_syms: list[dict[str, Any]],
                       overrides: Mapping[str, Any], symbol_map: Mapping[str, int],
                       section_vas: Mapping[int, int], image_base: int) -> None:
    for rel in relocs:
        roff = rel["offset"]
        rtype = rel["type"]
        if rtype not in (IMAGE_REL_I386_DIR32, IMAGE_REL_I386_DIR32NB):
            raise NoncodeSectionError(f"unsupported relocation type {rtype:#x} at offset {roff:#x}")
        key_hex = f"{roff:#x}"
        key_dec = str(roff)
        addend = struct.unpack_from("<I", buf, roff)[0]
        if key_hex in overrides:
            target = _resolve_addr(overrides[key_hex], symbol_map, f"reloc[{key_hex}]")
            val = target if rtype == IMAGE_REL_I386_DIR32 else (target - image_base)
            struct.pack_into("<I", buf, roff, val & 0xFFFFFFFF)
        elif key_dec in overrides:
            target = _resolve_addr(overrides[key_dec], symbol_map, f"reloc[{key_dec}]")
            val = target if rtype == IMAGE_REL_I386_DIR32 else (target - image_base)
            struct.pack_into("<I", buf, roff, val & 0xFFFFFFFF)
        else:
            sym = coff_syms[rel["symbol_index"]]
            sname = sym["name"]
            if sname in symbol_map:
                base = symbol_map[sname]
            elif sym["section"] in section_vas:
                base = section_vas[sym["section"]] + sym["value"]
            else:
                raise NoncodeSectionError(
                    f"unresolved COFF relocation symbol {sname!r} at offset {roff:#x}"
                )
            val = (base + addend) if rtype == IMAGE_REL_I386_DIR32 else (base + addend - image_base)
            struct.pack_into("<I", buf, roff, val & 0xFFFFFFFF)


def _emit_import_table(out: bytearray, base_va: int, image_base: int, entry: Mapping[str, Any]) -> None:
    """Emit Win32 IMAGE_IMPORT_DESCRIPTOR[], ILTs, IATs, and Hint/Name entries."""
    dir_va = _int(entry["directory_va"], "import_table.directory_va")
    dlls = entry["dlls"]
    dir_off = dir_va - base_va
    for idx, dll in enumerate(dlls):
        ilt_va = _int(dll["ilt_va"], f"dll[{idx}].ilt_va")
        iat_va = _int(dll["iat_va"], f"dll[{idx}].iat_va")
        name_va = _int(dll["name_va"], f"dll[{idx}].name_va")
        dll_name = dll["name"].encode("ascii") + b"\0"
        name_off = name_va - base_va
        out[name_off:name_off + len(dll_name)] = dll_name
        struct.pack_into(
            "<5I", out, dir_off + idx * 20,
            ilt_va - image_base, 0, 0, name_va - image_base, iat_va - image_base,
        )
        for slot, imp in enumerate(dll["imports"]):
            if "ordinal" in imp:
                thunk = 0x80000000 | _int(imp["ordinal"], f"dll[{idx}].imports[{slot}].ordinal")
            else:
                hn_va = _int(imp["hint_name_va"], f"dll[{idx}].imports[{slot}].hint_name_va")
                hint = _int(imp["hint"], f"dll[{idx}].imports[{slot}].hint")
                fn_b = imp["name"].encode("ascii") + b"\0"
                hn_off = hn_va - base_va
                struct.pack_into("<H", out, hn_off, hint)
                out[hn_off + 2:hn_off + 2 + len(fn_b)] = fn_b
                thunk = hn_va - image_base
            struct.pack_into("<I", out, (ilt_va - base_va) + slot * 4, thunk)
            struct.pack_into("<I", out, (iat_va - base_va) + slot * 4, thunk)


def _pack_sz_or_ord(val: Any) -> bytes:
    if val == "" or val is None:
        return struct.pack("<H", 0)
    if isinstance(val, int):
        return struct.pack("<HH", 0xFFFF, val)
    return val.encode("utf-16le") + b"\0\0"


def _pack_dialog_ex(spec: Mapping[str, Any]) -> bytes:
    buf = bytearray()
    buf += struct.pack(
        "<HHIIIHHHHH",
        _int(spec.get("version", 1), "dialog.version"),
        0xFFFF,
        _int(spec.get("help_id", 0), "dialog.help_id"),
        _int(spec.get("ex_style", 0), "dialog.ex_style"),
        _int(spec["style"], "dialog.style"),
        len(spec["items"]),
        _int(spec["x"], "dialog.x"),
        _int(spec["y"], "dialog.y"),
        _int(spec["cx"], "dialog.cx"),
        _int(spec["cy"], "dialog.cy"),
    )
    buf += _pack_sz_or_ord(spec.get("menu", ""))
    buf += _pack_sz_or_ord(spec.get("class", ""))
    buf += _pack_sz_or_ord(spec.get("title", ""))
    font = spec.get("font")
    if font:
        buf += struct.pack(
            "<HHBB",
            _int(font["point_size"], "dialog.font.point_size"),
            _int(font.get("weight", 400), "dialog.font.weight"),
            _int(font.get("italic", 0), "dialog.font.italic"),
            _int(font.get("charset", 1), "dialog.font.charset"),
        )
        buf += _pack_sz_or_ord(font["typeface"])
    for item in spec["items"]:
        while len(buf) % 4:
            buf.append(0)
        buf += struct.pack(
            "<IIIhhhhI",
            _int(item.get("help_id", 0), "item.help_id"),
            _int(item.get("ex_style", 0), "item.ex_style"),
            _int(item["style"], "item.style"),
            _int(item["x"], "item.x"),
            _int(item["y"], "item.y"),
            _int(item["cx"], "item.cx"),
            _int(item["cy"], "item.cy"),
            _int(item["id"], "item.id") & 0xFFFFFFFF,
        )
        buf += _pack_sz_or_ord(item["class"])
        buf += _pack_sz_or_ord(item.get("text", ""))
        buf += struct.pack("<H", 0)
    return bytes(buf)


def _emit_rsrc(out: bytearray, base_va: int, image_base: int, entry: Mapping[str, Any],
               manifest_dir: Path, oracle: bytes | None) -> None:
    """Emit a Win32 .rsrc section tree from declarative resource entries."""
    rsrc_rva = base_va - image_base
    # Build resource payloads
    payloads: dict[str, bytes] = {}
    for res in entry["resources"]:
        rid = res["key"]
        rtype = res["payload_kind"]
        if rtype == "dialog_ex":
            payloads[rid] = _pack_dialog_ex(res["dialog"])
        elif rtype == "group_icon":
            g = res["group_icon"]
            b = bytearray(struct.pack("<HHH", 0, 1, len(g["entries"])))
            for e in g["entries"]:
                b += struct.pack(
                    "<BBBBHHIH",
                    e["width"], e["height"], e.get("colors", 0), 0,
                    e.get("planes", 1), e.get("bpp", 32), e["bytes"], e["icon_id"],
                )
            payloads[rid] = bytes(b)
        elif rtype == "icon_file":
            # Look for explicit file, or extract from oracle/retail exe if provided
            src_path = (manifest_dir / res["path"]).resolve() if "path" in res else None
            if src_path and src_path.is_file():
                raw = src_path.read_bytes()
                # If .ico file, strip 22-byte ICO header to get DIB payload
                if raw[:4] == b"\x00\x00\x01\x00" and len(raw) == _int(res["size"], "icon.size") + 22:
                    raw = raw[22:]
                payloads[rid] = raw
            elif oracle is not None:
                ro = _int(res["retail_file_offset"], "icon.retail_file_offset")
                sz = _int(res["size"], "icon.size")
                payloads[rid] = oracle[ro:ro + sz]
            else:
                raise NoncodeSectionError(
                    f"icon payload {rid!r} requires either {res.get('path')} or --verify / retail oracle"
                )
        else:
            raise NoncodeSectionError(f"unsupported rsrc payload_kind: {rtype!r}")

    # Emit directory tables, string table, data entries, and payloads at declared offsets
    for node in entry["directories"]:
        off = _int(node["offset"], "dir.offset")
        struct.pack_into(
            "<IIHHHH", out, off,
            0, _int(node.get("timestamp", 0), "dir.timestamp"),
            _int(node.get("major", 0), "dir.major"), _int(node.get("minor", 0), "dir.minor"),
            _int(node["named_count"], "dir.named_count"), _int(node["id_count"], "dir.id_count"),
        )
        for idx, item in enumerate(node["entries"]):
            name_or_id = _int(item["name_or_id"], "dir.entry.name_or_id")
            target_off = _int(item["target_offset"], "dir.entry.target_offset")
            if item.get("is_subdir"):
                target_off |= 0x80000000
            if item.get("is_named"):
                name_or_id |= 0x80000000
            struct.pack_into("<II", out, off + 16 + idx * 8, name_or_id, target_off)

    for s in entry.get("strings", []):
        off = _int(s["offset"], "rsrc.string.offset")
        txt = s["text"].encode("utf-16le")
        struct.pack_into("<H", out, off, len(s["text"]))
        out[off + 2:off + 2 + len(txt)] = txt

    for res in entry["resources"]:
        data_entry_off = _int(res["data_entry_offset"], "res.data_entry_offset")
        payload_off = _int(res["payload_offset"], "res.payload_offset")
        data = payloads[res["key"]]
        if len(data) != _int(res["size"], "res.size"):
            raise NoncodeSectionError(
                f"rsrc payload {res['key']!r} has {len(data)} bytes; expected {res['size']}"
            )
        struct.pack_into(
            "<IIII", out, data_entry_off,
            rsrc_rva + payload_off, len(data), _int(res.get("codepage", 0), "res.codepage"), 0,
        )
        out[payload_off:payload_off + len(data)] = data


def build_section(manifest_path: Path, *, toolkit: Path | None, cache_dir: Path | None = None,
                  oracle: bytes | None = None) -> bytes:
    """Build a complete non-code PE section from its JSON manifest."""
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    manifest_dir = manifest_path.parent
    project_root = (manifest_dir / manifest.get("project_root", "..")).resolve()
    image_base = _int(manifest.get("image_base", "0x00400000"), "image_base")
    base_va = _int(manifest["virtual_address"], "virtual_address")
    raw_size = _int(manifest["raw_size"], "raw_size")
    out = bytearray(raw_size)

    # Load symbol table from regions.json (if declared) + manifest overrides
    symbol_map: dict[str, int] = {}
    if "regions_manifest" in manifest:
        reg_path = (manifest_dir / manifest["regions_manifest"]).resolve()
        reg_data = json.loads(reg_path.read_text(encoding="utf-8"))
        for k, v in reg_data.get("symbols", {}).items():
            symbol_map[k] = _int(v, f"regions.symbols[{k}]")
    for k, v in manifest.get("symbols", {}).items():
        symbol_map[k] = _int(v, f"manifest.symbols[{k}]")

    # Cache archive members per library path
    lib_cache: dict[str, dict[str, bytes]] = {}

    def get_lib_member(lib_name: str, member_name: str) -> bytes:
        if toolkit is None:
            raise NoncodeSectionError(f"toolkit required to extract {lib_name}/{member_name}")
        if lib_name not in lib_cache:
            lib_cache[lib_name] = dict(ar_members(toolkit / "lib" / lib_name))
        members = lib_cache[lib_name]
        if member_name not in members:
            raise NoncodeSectionError(f"member {member_name!r} not found in {lib_name}")
        return members[member_name]

    for entry in manifest["entries"]:
        kind = entry["kind"]
        if kind == "library":
            raw_obj = get_lib_member(entry["library"], entry["member"])
            sec_list, coff_syms = _parse_coff(raw_obj)
            sec_name = entry["section"]
            if "section_index" in entry:
                sidx = _int(entry["section_index"], "library.section_index")
                matches = [s for s in sec_list if s["index"] == sidx and s["name"] == sec_name]
            else:
                matches = [s for s in sec_list if s["name"] == sec_name]
            if not matches:
                raise NoncodeSectionError(f"section {sec_name!r} not in {entry['library']}/{entry['member']}")
            sec = matches[0]
            buf = bytearray(sec["data"])
            va = _int(entry["address"], "library.address")
            sec_vas = {sec["index"]: va}
            _apply_relocations(
                buf, sec["relocations"], coff_syms, entry.get("relocations", {}),
                symbol_map, sec_vas, image_base,
            )
            slice_off = _int(entry.get("slice_offset", 0), "library.slice_offset")
            slice_len = _int(entry.get("slice_size", len(buf) - slice_off), "library.slice_size")
            off = va - base_va
            out[off:off + slice_len] = buf[slice_off:slice_off + slice_len]

        elif kind == "cpp":
            if toolkit is None:
                raise NoncodeSectionError(f"toolkit required to compile {entry['source']}")
            src_path = (project_root / entry["source"]).resolve()
            raw_obj = _compile_cpp(src_path, project_root, toolkit, cache_dir, entry.get("flags", []))
            sec_list, coff_syms = _parse_coff(raw_obj)
            secs = {s["name"]: s for s in sec_list}
            # Map all placed section indices to their target VAs so internal relocs resolve automatically
            sec_vas: dict[int, int] = {}
            for p in entry["placements"]:
                sname = p["section"]
                if sname not in secs:
                    raise NoncodeSectionError(f"section {sname!r} not emitted by {entry['source']}")
                sec_vas[secs[sname]["index"]] = _int(p["address"], f"cpp.placement[{sname}].address")
            for p in entry["placements"]:
                sec = secs[p["section"]]
                va = _int(p["address"], f"cpp.placement[{p['section']}].address")
                buf = bytearray(sec["data"])
                _apply_relocations(
                    buf, sec["relocations"], coff_syms, p.get("relocations", {}),
                    symbol_map, sec_vas, image_base,
                )
                expected_size = _int(p.get("size", len(buf)), f"cpp.placement[{p['section']}].size")
                if len(buf) < expected_size:
                    raise NoncodeSectionError(
                        f"section {p['section']} from {entry['source']} has {len(buf)} bytes; expected {expected_size}"
                    )
                off = va - base_va
                out[off:off + expected_size] = buf[:expected_size]

        elif kind == "pointer_table":
            va = _int(entry["address"], "pointer_table.address")
            off = va - base_va
            for idx, item in enumerate(entry["values"]):
                val = _resolve_addr(item, symbol_map, f"pointer_table[{idx}]")
                struct.pack_into("<I", out, off + idx * 4, val & 0xFFFFFFFF)

        elif kind == "import_table":
            _emit_import_table(out, base_va, image_base, entry)

        elif kind == "rsrc":
            _emit_rsrc(out, base_va, image_base, entry, manifest_dir, oracle)

        elif kind == "bytes":
            va = _int(entry["address"], "bytes.address")
            data = bytes.fromhex(entry["hex"])
            off = va - base_va
            out[off:off + len(data)] = data

        else:
            raise NoncodeSectionError(f"unknown entry kind: {kind!r}")

    expected_sha = manifest.get("sha256")
    actual_sha = hashlib.sha256(out).hexdigest()
    if expected_sha and actual_sha != expected_sha:
        raise NoncodeSectionError(
            f"reconstructed section {manifest.get('name')} SHA-256 mismatch: "
            f"expected {expected_sha}, got {actual_sha}"
        )
    return bytes(out)
