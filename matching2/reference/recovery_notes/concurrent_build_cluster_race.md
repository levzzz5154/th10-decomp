# Concurrent builds race on the shared cluster directory

2026-09-18. Three `make` runs overlapped in this session (one killed by a shell
timeout, two more started before the first was reaped). Each one failed at the
link step with a *different* missing file:

```
ld: cannot find .../clusters/file_interface_install/bodies.obj
ld: cannot find .../clusters/load_deref_00450200/bodies.obj
ld: cannot find .../clusters/set_sprite_metadata/bodies.obj
```

All three objects were present before and afterwards. The build compiles every
LTCG cluster into the shared `matching2/build/msvc/clusters/<name>/` directory
(`build_msvc.py`, `compile_unit` -> `build_cluster`), so two builds writing that
directory concurrently unlink and rewrite each other's cluster objects; the
loser links against a tree that is momentarily incomplete, and the linker reports
whichever file it happened to reach first.

The failure mode is misleading: 2,358 sources compile with zero failures, the
`link.log` holds a single "cannot find" line, and the traceback points at the
link rather than at the second build. Two operational rules follow.

- Never let two builds share `matching2/build/msvc`. Check for a live `make`,
  `cl.exe`, `wine` or `ld` before starting one; the tool's background-job handle
  can outlive the process, so `ps` is the authority, not the job list.
- If the linker names a cluster object, do not assume the region is unregistered.
  Compare the manifest's `ltcg_clusters` count with the directories under
  `build/msvc/clusters/`, and re-run `register_cluster.py --layout
  layout/ltcg/<name>.json --apply` from `matching2/msvc`, which regenerates
  `bodies.obj` from the layout's context source.

Verified afterwards by a single solo build: `Whole EXE exact: 487,936 bytes`,
511 semantic regions / 34,411 bytes, 2,074 assembly regions / 354,617 bytes.
