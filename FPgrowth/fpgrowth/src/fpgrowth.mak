#-----------------------------------------------------------------------
# File    : fpgrowth.mak
# Contents: build fpgrowth program (on Windows systems)
# Author  : Christian Borgelt
# History : 2004.11.21 file created from eclat.mak
#           2006.07.20 adapted to Visual Studio 8
#           2010.08.22 module escape added (for module tabread)
#           2011.09.20 external module fim16 added (16 items machine)
#-----------------------------------------------------------------------
THISDIR  = ..\..\fpgrowth\src
UTILDIR  = ..\..\util\src
TRACTDIR = ..\..\tract\src

CC       = cl.exe
DEFS     = /D WIN32 /D NDEBUG /D _CONSOLE /D _CRT_SECURE_NO_WARNINGS
CFLAGS   = /nologo /W3 /O2 /GS- $(DEFS) /c $(ADDFLAGS)
INCS     = /I $(UTILDIR) /I $(TRACTDIR)

LD       = link.exe
LDFLAGS  = /nologo /subsystem:console /incremental:no
LIBS     = 

HDRS     = $(UTILDIR)\memsys.h     $(UTILDIR)\arrays.h     \
           $(UTILDIR)\symtab.h     $(UTILDIR)\escape.h     \
           $(UTILDIR)\tabread.h    $(UTILDIR)\tabwrite.h   \
           $(UTILDIR)\scanner.h    $(TRACTDIR)\tract.h     \
           $(TRACTDIR)\patspec.h   $(TRACTDIR)\clomax.h    \
           $(TRACTDIR)\report.h    $(TRACTDIR)\fim16.h     \
           fpgrowth.h
OBJS     = $(UTILDIR)\memsys.obj   $(UTILDIR)\arrays.obj   \
           $(UTILDIR)\idmap.obj    $(UTILDIR)\escape.obj   \
           $(UTILDIR)\tabread.obj  $(UTILDIR)\tabwrite.obj \
           $(UTILDIR)\scform.obj   $(TRACTDIR)\tract.obj   \
           $(TRACTDIR)\patspec.obj $(TRACTDIR)\clomax.obj  \
           $(TRACTDIR)\repcm.obj   $(TRACTDIR)\fim16.obj   \
           fpgrowth.obj
PRGS     = fpgrowth.exe

#-----------------------------------------------------------------------
# Build Program
#-----------------------------------------------------------------------
all:         $(PRGS)

fpgrowth.exe:   $(OBJS) fpgrowth.mak
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS) /out:$@

#-----------------------------------------------------------------------
# Main Program
#-----------------------------------------------------------------------
fpgrowth.obj:   $(HDRS) fpgrowth.mak
	$(CC) $(CFLAGS) $(INCS) /D FPG_MAIN fpgrowth.c /Fo$@

#-----------------------------------------------------------------------
# External Modules
#-----------------------------------------------------------------------
$(UTILDIR)\memsys.obj:
	cd $(UTILDIR)
	$(MAKE) /f util.mak memsys.obj   ADDFLAGS="$(ADDFLAGS)"
	cd $(THISDIR)
$(UTILDIR)\arrays.obj:
	cd $(UTILDIR)
	$(MAKE) /f util.mak arrays.obj   ADDFLAGS="$(ADDFLAGS)"
	cd $(THISDIR)
$(UTILDIR)\idmap.obj:
	cd $(UTILDIR)
	$(MAKE) /f util.mak idmap.obj    ADDFLAGS="$(ADDFLAGS)"
	cd $(THISDIR)
$(UTILDIR)\escape.obj:
	cd $(UTILDIR)
	$(MAKE) /f util.mak escape.obj   ADDFLAGS="$(ADDFLAGS)"
	cd $(THISDIR)
$(UTILDIR)\tabread.obj:
	cd $(UTILDIR)
	$(MAKE) /f util.mak tabread.obj  ADDFLAGS="$(ADDFLAGS)"
	cd $(THISDIR)
$(UTILDIR)\tabwrite.obj:
	cd $(UTILDIR)
	$(MAKE) /f util.mak tabwrite.obj ADDFLAGS="$(ADDFLAGS)"
	cd $(THISDIR)
$(UTILDIR)\scform.obj:
	cd $(UTILDIR)
	$(MAKE) /f util.mak scform.obj   ADDFLAGS="$(ADDFLAGS)"
	cd $(THISDIR)
$(TRACTDIR)\tract.obj:
	cd $(TRACTDIR)
	$(MAKE) /f tract.mak tract.obj   ADDFLAGS="$(ADDFLAGS)"
	cd $(THISDIR)
$(TRACTDIR)\patspec.obj:
	cd $(TRACTDIR)
	$(MAKE) /f tract.mak patspec.obj ADDFLAGS="$(ADDFLAGS)"
	cd $(THISDIR)
$(TRACTDIR)\clomax.obj:
	cd $(TRACTDIR)
	$(MAKE) /f tract.mak clomax.obj  ADDFLAGS="$(ADDFLAGS)"
	cd $(THISDIR)
$(TRACTDIR)\repcm.obj:
	cd $(TRACTDIR)
	$(MAKE) /f tract.mak repcm.obj   ADDFLAGS="$(ADDFLAGS)"
	cd $(THISDIR)
$(TRACTDIR)\fim16.obj:
	cd $(TRACTDIR)
	$(MAKE) /f tract.mak fim16.obj   ADDFLAGS="$(ADDFLAGS)"
	cd $(THISDIR)

#-----------------------------------------------------------------------
# Install
#-----------------------------------------------------------------------
install:
	-@copy $(PRGS) ..\..\..\bin

#-----------------------------------------------------------------------
# Clean up
#-----------------------------------------------------------------------
localclean:
	-@erase /Q *~ *.obj *.idb *.pch $(PRGS)

clean:
	$(MAKE) /f fpgrowth.mak localclean
	cd $(TRACTDIR)
	$(MAKE) /f tract.mak clean
	cd $(UTILDIR)
	$(MAKE) /f util.mak clean
	cd $(THISDIR)
