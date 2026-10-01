.DEFAULT_GOAL := build
PYTHON ?= python3
MSVC_ARGS ?=
LTCG_ARGS ?=

.PHONY: build rebuild verify progress ltcg-proof
build:
	./matching2/build_msvc.sh $(MSVC_ARGS)

# Recompile every unit instead of reusing unchanged ones from the cache.
rebuild:
	./matching2/build_msvc.sh --no-cache $(MSVC_ARGS)

verify: build

progress:
	$(PYTHON) matching2/tools/matching/progress.py

# Positive/negative compiler controls plus two fresh exact cluster builds.
ltcg-proof:
	$(PYTHON) matching2/tools/matching/experiment_ltcg.py $(LTCG_ARGS)
