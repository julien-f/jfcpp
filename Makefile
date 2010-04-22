.PHONY: all clean examples mrproper tests

all:
	@echo 'Type “make tests” to compile and execute the available tests.'
	@echo ''
	@echo 'Type “make examples” to compile the available examples.'

clean mrproper:
	@cd examples && $(MAKE) $(MAKEFLAGS) $@
	@cd tests && $(MAKE) $(MAKEFLAGS) $@

examples tests:
	@cd $@ && $(MAKE) $(MAKEFLAGS)
