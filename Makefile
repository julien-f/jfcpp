prefix     := /usr/local
includedir := $(prefix)/include

.DEFAULT_GOAL := all
.PHONY        := all install uninstall clean mrproper

MKDIR := mkdir --parents
RMDIR := rmdir --parents --ignore-fail-on-non-empty

.PHONY: all install uninstall clean-tests test

all:
	@echo 'This is a set of C++ headers, there is nothing to compile ;)'
	@echo
	@echo 'Type “make install” to install at the default location (“$(prefix)”).'
	@echo 'Type “make prefix=/some/directory install” to install somewhere else.'
	@echo
	@echo 'There are some examples available in the “examples/” directory.'
	@echo 'Type “make test” to compile and execute the available tests.'
	@echo
	@echo 'Before running the examples or the tests, be sure to run'
	@echo '“git submodule update --init”.'

install:
	$(MKDIR) -- '$(includedir)'
	cp -r -- include/jfcpp/ '$(includedir)/'

uninstall:
	$(RM) -r -- '$(includedir)/jfcpp/'
	$(RMDIR) -- '$(includedir)'

clean-tests:
	@$(MAKE) -C tests/ distclean

test:
	@$(MAKE) -C tests/
