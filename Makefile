# Test makefile

MAKEFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRENT_DIR := $(notdir $(patsubst %/,%,$(dir $(MAKEFILE_PATH))))

all:
	@echo $(MAKEFILE_PATH)
	@echo $(CURRENT_DIR)