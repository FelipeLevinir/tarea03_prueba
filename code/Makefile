SRCDIR=src
default: all

all:
	(cd $(SRCDIR) && $(MAKE))
	mv src/./tarea03 ./tarea03

clean:
	(cd $(SRCDIR) && $(MAKE) clean)
	mv src/./tarea03 ./tarea03

distclean:
	(cd $(SRCDIR) && $(MAKE) clean && $(MAKE) distclean)
	mv src/./tarea03 ./tarea03


.PHONY: all clean distclean
