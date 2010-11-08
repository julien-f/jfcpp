PREFIX      := /usr/local
INSTALL_DIR := $(PREFIX)/include

.DEFAULT_GOAL := all
.PHONY        := all install uninstall clean mrproper

MKDIR := mkdir --parents
RMDIR := rmdir --parents --ignore-fail-on-non-empty

.PHONY: all install uninstall clean-tests test

all:
	@echo 'This is a set of C++ headers, there is nothing to compile ;)'
	@echo
	@echo 'Type “make install” to install at the default location (“'"$(INSTALL_DIR)"'”).'
	@echo 'Type “make INSTALL_DIR=/some/directory” to install where you want.'
	@echo
	@echo 'Type “make test” to compile and execute the available tests.'

install:
	$(MKDIR) -- '$(INSTALL_DIR)'
	cp -r -- include/jfcpp/ '$(INSTALL_DIR)/jfcpp/'

uninstall:
	$(RM) -r -- '$(INSTALL_DIR)/jfcpp/'
	$(RMDIR) -- '$(INSTALL_DIR)'

clean-tests:
	@$(MAKE) -C tests/ mrproper

test:
	@$(MAKE) -C tests/
