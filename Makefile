.DEFAULT_GOAL := build
PYTHON ?= python3
MSVC_ARGS ?=

.PHONY: build verify progress
build:
	./matching2/build_msvc.sh $(MSVC_ARGS)

verify: build

progress:
	$(PYTHON) matching2/tools/matching/progress.py
