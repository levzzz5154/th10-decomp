# 0x00420B10 / 0x00420C00 - dummy registrations and a new call shape

2026-09-18. Found by `screen_regions.py --entry none` (now that it actually
requires no register reads), the prime class: neither region reads a register
before writing it, and both are small - 73 and 41 bytes.

`0x00420C00`:

```
test byte [data_00491d78],10h
mov edx,46DF98h
push 0
mov eax,492590h
je  done
push 4
call AnimationManager_RegisterResource_0043e460
done:
xor eax,eax
ret
```

`0x00420B10` is the same test with the two `push`es adjacent and the call
unconditional inside the branch, then continues past it.

The interesting part is the call shape: the caller sets **EAX = 0x00492590** and
**EDX = 0x0046DF98**, pushes **4** and **0**, and leaves **ECX unset**. That is a
third distinct convention for `RegisterResource` - the blocker note for
`0x0043E460` recorded its *entry* in EDI from other call sites - so these two
regions are evidence for whatever convention the function actually has, and any
attempt at the `0x43E460` blocker should start by reconciling the call sites
rather than assuming one.

The regions themselves are otherwise trivial: a flag test on `data_00491D78`
bit 4, two literal addresses, and a fixed pair of stack arguments.
