CPPUTEST_HOME = ./CppUTest
COMPONENT_NAME = chem
SRC_DIRS = .
TEST_SRC_DIRS = tests
INCLUDE_DIRS = \
	. \
	$(CPPUTEST_HOME)/include	
CPPUTEST_CFLAGS = -g -ansi -pedantic -Wall

include $(CPPUTEST_HOME)/build/MakefileWorker.mk

$(CPPUTEST_LIB):
	$(MAKE) -C $(CPPUTEST_HOME)

mrproper: clean
	$(MAKE) -C $(CPPUTEST_HOME) clean
	rm -rf *~
	rm -rf lib