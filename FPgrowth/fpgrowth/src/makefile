#-----------------------------------------------------------------------
# File    : makefile
# Contents: build fpgrowth program (on Unix systems)
# Author  : Christian Borgelt
# History : 2004.11.21 file created from eclat makefile
#           2004.12.10 general memory management system added
#           2008.08.11 adapted to name change from vecops to arrays
#           2009.10.19 external module pfxtree added
#           2010.02.08 external module pfxtree replaced by module clomax
#           2010.08.22 module escape added (for module tabread)
#           2010.10.08 changed standard from -ansi to -std=c99
#           2013.03.20 extended the requested warnings in CFBASE
#-----------------------------------------------------------------------
# For large file support (> 2GB) compile with
#   make ADDFLAGS=-D_FILE_OFFSET_BITS=64
#-----------------------------------------------------------------------
SHELL    = /bin/bash
THISDIR  = ../../fpgrowth/src
UTILDIR  = ../../util/src
TRACTDIR = ../../tract/src

CC       = gcc -std=c99
# CC       = g++
CFBASE   = -Wall -Wextra -Wno-unused-parameter -Wconversion \
           -pedantic $(ADDFLAGS)
CFLAGS   = $(CFBASE) -DNDEBUG -O3
# CFLAGS   = $(CFBASE) -DNDEBUG -O3 -DBENCH
# CFLAGS   = $(CFBASE) -g
# CFLAGS   = $(CFBASE) -g -DSTORAGE
INCS     = -I$(UTILDIR) -I$(TRACTDIR)

LD       = gcc
LDFLAGS  = $(ADDFLAGS)
LIBS     = -lm

# ADDOBJS  = $(UTILDIR)/storage.o

HDRS     = $(UTILDIR)/memsys.h   $(UTILDIR)/arrays.h   \
           $(UTILDIR)/symtab.h   $(UTILDIR)/escape.h   \
           $(UTILDIR)/tabread.h  $(UTILDIR)/tabwrite.h \
           $(UTILDIR)/scanner.h  $(TRACTDIR)/tract.h   \
           $(TRACTDIR)/patspec.h $(TRACTDIR)/clomax.h  \
           $(TRACTDIR)/report.h  $(TRACTDIR)/fim16.h   \
           fpgrowth.h
OBJS     = $(UTILDIR)/memsys.o   $(UTILDIR)/arrays.o   \
           $(UTILDIR)/idmap.o    $(UTILDIR)/escape.o   \
           $(UTILDIR)/tabread.o  $(UTILDIR)/tabwrite.o \
           $(UTILDIR)/scform.o   $(TRACTDIR)/tract.o   \
           $(TRACTDIR)/patspec.o $(TRACTDIR)/clomax.o  \
           $(TRACTDIR)/repcm.o   $(TRACTDIR)/fim16.o   \
           fpgrowth.o $(ADDOBJS)
PRGS     = fpgrowth

#-----------------------------------------------------------------------
# Build Program
#-----------------------------------------------------------------------
all:        $(PRGS)

fpgrowth:   $(OBJS) makefile
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

#-----------------------------------------------------------------------
# Main Program
#-----------------------------------------------------------------------
fpgrowth.o: $(HDRS)
fpgrowth.o: fpgrowth.c makefile
	$(CC) $(CFLAGS) $(INCS) -DFPG_MAIN -c fpgrowth.c -o $@

#-----------------------------------------------------------------------
# External Modules
#-----------------------------------------------------------------------
$(UTILDIR)/memsys.o:
	cd $(UTILDIR);  $(MAKE) memsys.o  ADDFLAGS="$(ADDFLAGS)"
$(UTILDIR)/arrays.o:
	cd $(UTILDIR);  $(MAKE) arrays.o  ADDFLAGS="$(ADDFLAGS)"
$(UTILDIR)/idmap.o:
	cd $(UTILDIR);  $(MAKE) idmap.o   ADDFLAGS="$(ADDFLAGS)"
$(UTILDIR)/escape.o:
	cd $(UTILDIR);  $(MAKE) escape.o  ADDFLAGS="$(ADDFLAGS)"
$(UTILDIR)/tabread.o:
	cd $(UTILDIR);  $(MAKE) tabread.o ADDFLAGS="$(ADDFLAGS)"
$(UTILDIR)/scform.o:
	cd $(UTILDIR);  $(MAKE) scform.o  ADDFLAGS="$(ADDFLAGS)"
$(TRACTDIR)/tract.o:
	cd $(TRACTDIR); $(MAKE) tract.o   ADDFLAGS="$(ADDFLAGS)"
$(TRACTDIR)/patspec.o:
	cd $(TRACTDIR); $(MAKE) patspec.o ADDFLAGS="$(ADDFLAGS)"
$(TRACTDIR)/clomax.o:
	cd $(TRACTDIR); $(MAKE) clomax.o  ADDFLAGS="$(ADDFLAGS)"
$(TRACTDIR)/repcm.o:
	cd $(TRACTDIR); $(MAKE) repcm.o   ADDFLAGS="$(ADDFLAGS)"
$(TRACTDIR)/fim16.o:
	cd $(TRACTDIR); $(MAKE) fim16.o   ADDFLAGS="$(ADDFLAGS)"

#-----------------------------------------------------------------------
# Source Distribution Packages
#-----------------------------------------------------------------------
dist:
	$(MAKE) clean
	cd ../..; rm -f fpgrowth.zip fpgrowth.tar.gz; \
        zip -rq fpgrowth.zip fpgrowth/{src,ex,doc} \
          tract/src/{tract.[ch],fim16.[ch]} \
          tract/src/{patspec.[ch],clomax.[ch],report.[ch]} \
          tract/src/{makefile,tract.mak} tract/doc \
          util/src/{fntypes.h,error.h} \
          util/src/{arrays.[ch],memsys.[ch],symtab.[ch]} \
          util/src/{escape.[ch],tabread.[ch],tabwrite.[ch]} \
          util/src/scanner.[ch] \
          util/src/{makefile,util.mak} util/doc; \
        tar cfz fpgrowth.tar.gz fpgrowth/{src,ex,doc} \
          tract/src/{tract.[ch],fim16.[ch]} \
          tract/src/{patspec.[ch],clomax.[ch],report.[ch]} \
          tract/src/{makefile,tract.mak} tract/doc \
          util/src/{fntypes.h,error.h} \
          util/src/{arrays.[ch],memsys.[ch],symtab.[ch]} \
          util/src/{escape.[ch],tabread.[ch],tabwrite.[ch]} \
          util/src/scanner.[ch] \
          util/src/{makefile,util.mak} util/doc

#-----------------------------------------------------------------------
# Installation
#-----------------------------------------------------------------------
install:
	cp $(PRGS) $(HOME)/bin

#-----------------------------------------------------------------------
# Clean up
#-----------------------------------------------------------------------
localclean:
	rm -f *.o *~ *.flc core $(PRGS)

clean:
	$(MAKE) localclean
	cd $(UTILDIR);  $(MAKE) clean
	cd $(TRACTDIR); $(MAKE) clean
