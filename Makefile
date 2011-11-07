CPPUTEST_HOME = ./CppUTest
COMPONENT_NAME = chem
SRC_DIRS = .
TEST_SRC_DIRS = tests
INCLUDE_DIRS = \
	. \
	$(CPPUTEST_HOME)/include	
CPPUTEST_CFLAGS = -ansi
CPPUTEST_WARNINGFLAGS = -Wall -Wextra -pedantic-errors

include $(CPPUTEST_HOME)/build/MakefileWorker.mk

$(CPPUTEST_LIB):
	$(MAKE) -C $(CPPUTEST_HOME)

mrproper: realclean
	$(MAKE) -C $(CPPUTEST_HOME) clean
	rm -rf *~
	rm -rf lib
	rm -rf calc

calc: getop.o stack.o getch.o lib/libchem.a
