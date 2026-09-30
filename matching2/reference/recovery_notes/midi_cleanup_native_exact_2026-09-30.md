# MIDI cleanup 0x0043A910: exact C++ landing

New selected CleanupMidi_0043a910 at0x0043A910,156bytes. IncomingEAX, plainRET; void source returncontract. Noinlineasm, naked bodies, emissions or outputpatching. Initial158-byte candidate became156 by capturing evidenced timeEndPeriod IAT pointer in a typed local and reusing it across both calls, as retail savedEDI does.

Retail quirks preserved: sequencer vtable46F80C then Shutdown43AE20 and ReleaseTracks43AA60;32filebuffers conditionalfree/null followed by unconditionalnull; reloadoutputhandle betweenReset/Close/null; timerbasevtable46F810; eventkill; twoEndPeriod calls withtimer clearbetween. No inventedstate/simplifiedextra timer calls.

Extended existingnativecluster selects4realfunctions. Compiler-only context composes grounded LoadTrack operations with GameMain's globalcleanup/delete/clear operations; it is unselected160bytes, NOT a recoveredcaller and no outgoingprivatecallee ABI is claimed. ReleaseTracks ABIanchor copiedverbatim canonicalexistingmidi_file.cpp body withonlysectionnamechange, no production duplicateowner/credit. Existing callback/shutdown/completion andcanonicaltrackrelease source unchanged.

Parent independentlyprobed scratch andmaintained all4EXACT:265WndProc,156Cleanup,129Shutdown,79Completion. Checkedcompleteoriginalrecord/ownerand onlynewmanifestrecord43A910, applied onlynewsource/extendedlayout/context. Full makebuild1925maintained+10optionalcompiler sources, zerofailures; wholeEXEexact487936bytes.

Parent also extracted107bytes43AA60 from freshmaintainednativecluster PE andcompletebuiltPE, confirmedbyteidentity: SHA2567bbe1c65e3b0a7a222dd69ce9d80731dca3ff0c0f0b7b7b48c0cf2e61f0e1b8d. Compileranchor supplies the sameESIreceiver implementation asactualcanonicalowner.

Progress1839ordinaryC++regions/95775bytes;465remainingasmregions/227275bytes. Newcreditedrecovery156bytes only. gitdiffcheckpassed. WIPnotcommitted aftercheckpoint3d2c1c11.

Scratchreceipts /home/levzzz/.hermes/cache/scratch/midi-destroy-native/{HANDOFF.md,handoff.json,probe03,parent_verify,maintained_verify}; scratchmayexpire, maintainedlayout/source+makebuildreproducegate.
