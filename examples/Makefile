##
# My Great Makefile
#
# Julien Fontanet <julien.fontanet@isonoe.net>
#
# Copyleft 2010
##

##
# This Makefile works only with gcc/g++ (g++ is used for linking).
# The C prefix is ".c".
# The C++ prefix is ".cpp".
##

DEBUG := 1

# Do we want to use OpenMP for parallelization if availabled?
OPENMP := 1

# Projects list.
PROJECTS := \
	array\
	array_view\
	expression\
	functional\
	interpolation\
	math\
	matrix\
	meta\
	numerical_derivate\
	quaternion\
	rational\
	ref

# Global configuration.
PREFIX   := /usr/local
CXXFLAGS += -I../include/ -I../contracts/include/
CXXFLAGS += -std=c++98 -pedantic -Wall -Wextra -Winline -Wconversion -ggdb3

ifneq ($(DEBUG),1)
	CXXFLAGS += -DNDEBUG -fno-strict-aliasing -funroll-loops -O3 -g0
endif

ifeq ($(OPENMP),1)
	CXXFLAGS += -fopenmp
	LDFLAGS  += -fopenmp
endif



# DO NOT MODIFY ANYTHING AFTER THIS LINE.



.DEFAULT_GOAL  := all
CC             := gcc
CFLAGS         += -MMD
CXX            := g++
CXXFLAGS       += -MMD

# Rules to always execute.
.PHONY: all clean mrproper install uninstall

# Generic rule definition.
define PROJECT_TPL
# The default target is "bin/PROJECT_NAME".
$(1)_TARGET ?= bin/$(1)

# The default source is "src/PROJECT_NAME.cpp".
$(1)_SRCS ?= $(wildcard $(1)/main.cpp)

# The default install directory is "PREFIX/bin".
$(1)_INSTALL ?= $(PREFIX)/bin

$(1)_OBJECTS := $$(addsuffix .o,$$(basename $$($(1)_SRCS)))
$(1)_DEPS    := $$($(1)_OBJECTS:.o=.d)

$$($(1)_OBJECTS): CFLAGS := $(CFLAGS) $$($(1)_CFLAGS)
$$($(1)_OBJECTS): CXXFLAGS := $(CXXFLAGS) $$($(1)_CXXFLAGS)
$$($(1)_OBJECTS): Makefile

-include $$($(1)_DEPS)

all: $$($(1)_TARGET)
$$($(1)_TARGET): $$($(1)_OBJECTS)
	mkdir -p -- $$(@D)
	$(CXX) $(LDFLAGS) $$($(1)_LDFLAGS) -o $$@ $$^

.PHONY: install-$(1) uninstall-$(1) clean-$(1) mrproper-$(1)

install: install-$(1)
install-$(1): $$($(1)_TARGET)
	mkdir -p -- $$($(1)_INSTALL)
	cp -f $$^ $$($(1)_INSTALL)

uninstall: uninstall-$(1)
uninstall-$(1):
	$(RM) $$($(1)_INSTALL)/$$(notdir $$($(1)_TARGET))

clean: clean-$(1)
clean-$(1):
	$(RM) $$($(1)_DEPS) $$($(1)_OBJECTS)

mrproper: mrproper-$(1)
mrproper-$(1): clean-$(1)
	$(RM) $$($(1)_TARGET)
endef

# Creates rules for each project.
$(foreach project,$(PROJECTS),$(eval $(call PROJECT_TPL,$(project))))
