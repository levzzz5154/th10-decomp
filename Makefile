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
	$(PYTHON) -m unittest discover -s matching2/tests -p 'matching_progress_test.py'
	$(PYTHON) -m unittest discover -s matching2/tests -p 'common_tools_test.py'
	$(PYTHON) -m unittest discover -s matching2/tests -p 'coff_regions_test.py'
	$(PYTHON) -m unittest discover -s matching2/tests -p 'msvc_port_test.py'
	$(PYTHON) -m unittest discover -s matching2/tests -p 'msvc_keyboard_state_test.py'
	$(PYTHON) -m unittest discover -s matching2/tests -p 'msvc_input_pattern_count_test.py'
	$(PYTHON) -m unittest discover -s matching2/tests -p 'msvc_playfield_bounds_test.py'
	$(PYTHON) -m unittest discover -s matching2/tests -p 'msvc_resource_lifetime_test.py'
	$(PYTHON) -m unittest discover -s matching2/tests -p 'mismatch_test.py'
	$(PYTHON) -m unittest discover -s matching2/tests -p 'pe_pack_test.py'

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
