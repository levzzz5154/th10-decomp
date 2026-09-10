.DEFAULT_GOAL := help
PYTHON ?= python3
MSVC_ARGS ?=

.PHONY: help build test verify progress progress-update reference runtime runtime-test
help:
	@printf '%s\n' \
	  'Primary matching workflow:' \
	  '  make build            Compile with MSVC and require byte-exact output' \
	  '  make test             Test matching verification tools (no MSVC required)' \
	  '  make verify           Run matching tests, then the exact build' \
	  '  make progress         Show live manifest classifications' \
	  '  make progress-update  Refresh the checked progress document' \
	  '  MSVC_ARGS="..."       Forward options to build_msvc.sh' \
	  '' 'Secondary workflows:' \
	  '  make reference        Build the complete assembly baseline' \
	  '  make runtime          Build the experimental modern runtime' \
	  '  make runtime-test     Run runtime integrity and host tests'

build:
	./matching2/build_msvc.sh $(MSVC_ARGS)

test:
	$(PYTHON) matching2/tools/matching/progress.py --check
	$(PYTHON) -m unittest matching2.tests.matching_progress_test
	$(PYTHON) -m unittest matching2.tests.common_tools_test
	$(PYTHON) -m unittest matching2.tests.coff_regions_test
	$(PYTHON) -m unittest matching2.tests.msvc_port_test
	$(PYTHON) -m unittest matching2.tests.ltcg_cluster_test
	$(PYTHON) -m unittest matching2.tests.msvc_keyboard_state_test
	$(PYTHON) -m unittest matching2.tests.msvc_input_pattern_count_test
	$(PYTHON) -m unittest matching2.tests.msvc_playfield_bounds_test
	$(PYTHON) -m unittest matching2.tests.msvc_resource_lifetime_test
	$(PYTHON) -m unittest matching2.tests.msvc_rng_test
	$(PYTHON) -m unittest matching2.tests.msvc_legacy_string_test
	$(PYTHON) -m unittest matching2.tests.msvc_dialog_test
	$(PYTHON) -m unittest matching2.tests.msvc_frame_timer_test
	$(PYTHON) -m unittest matching2.tests.mismatch_test
	$(PYTHON) -m unittest matching2.tests.pe_pack_test

verify:
	$(MAKE) test
	$(MAKE) build

progress:
	$(PYTHON) matching2/tools/matching/progress.py

progress-update:
	$(PYTHON) matching2/tools/matching/progress.py --write

reference:
	./matching2/build_asm.sh

runtime:
	./matching2/build.sh

runtime-test:
	./matching2/test.sh
