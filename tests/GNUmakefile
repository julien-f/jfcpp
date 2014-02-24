TARGETS := \
	array \
	circular_buffer \
	functional \
	matrix \
	meta

# Default compilation flags.
CXXFLAGS := -std=c++98 -I ../include/ -I ../tools/contracts/include/

# Because these are unit tests (see contracts.h).
DEBUG    := 1
CXXFLAGS += -DEXDEBUG

# Includes MyGreatMakefile
include ../tools/mgm/mgm.mk

all:
	@for f in bin/*; do \
		[ -x "$$f" ] || continue; \
		basename="$${f#*/}"; \
		printf '%s\033[72G' "$$basename"; \
		"$$f" 2> "$$basename".log >&2 && { \
			rm -f "$$basename.log"; \
			printf '$(COLOR_GREEN_BOLD)[passed]$(COLOR_NONE)\n'; \
		} || { \
			printf '$(COLOR_RED_BOLD)[failed]$(COLOR_NONE)\n\n$(COLOR_YELLOW_BOLD)%s$(COLOR_NONE)\n' "$$basename".log; \
			cat "$$basename".log; \
			printf '\n'; \
		} \
	done
