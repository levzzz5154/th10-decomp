.DEFAULT_GOAL := build
PYTHON ?= python3
BEHAVIOR_PYTHON ?= $(PYTHON)
MSVC_ARGS ?=
# EXACT=1 builds equivalent regions from their assembly: the bit-identical executable.
ifdef EXACT
MSVC_ARGS += --exact
endif
LTCG_ARGS ?=

.PHONY: build rebuild verify abi-check behavior-check progress ltcg-proof
build:
	./matching2/build_msvc.sh $(MSVC_ARGS)

# Recompile every unit instead of reusing unchanged ones from the cache.
rebuild:
	./matching2/build_msvc.sh --no-cache $(MSVC_ARGS)

verify: build

# Requires capstone; checks that equivalent models pass retail callees their register arguments.
abi-check: build
	$(PYTHON) matching2/tools/matching/callsite_abi.py

# Requires Unicorn; checks the installed item body with real retail callees.
behavior-check: abi-check
	$(BEHAVIOR_PYTHON) matching2/tests/item_update_shipped_differential.py
	$(BEHAVIOR_PYTHON) matching2/tests/replay_submenu_shipped_differential.py

progress:
	$(PYTHON) matching2/tools/matching/progress.py

# Positive/negative compiler controls plus two fresh exact cluster builds.
ltcg-proof:
	$(PYTHON) matching2/tools/matching/experiment_ltcg.py $(LTCG_ARGS)
