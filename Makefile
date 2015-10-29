SOURCES=atmost2maxsubstr.cpp balance.cpp compareBinHex.cpp isSorted.cpp maxpalindrome.cpp \
        maxsubstr.cpp median.cpp medianSortedArrays.cpp myatoi.cpp palindromindex.cpp pathIter.cpp permute.cpp replace.cpp \
        reverse.cpp reverseDigits.cpp reverseVec.cpp rle.cpp rowCol.cpp twosum.cpp vecInit.cpp regex.cpp bst.cpp \
        searchRotateSorted.cpp moveZeroes.cpp removeDup.cpp binarytree.cpp recpermute.cpp recsubset.cpp \
        clusterSort.cpp binarytreeencode.cpp isbst.cpp bfs.cpp

BUILDDIR?=build
OBJS=$(patsubst %.cpp,$(BUILDDIR)/%.o, $(SOURCES))
BINS=$(patsubst %.cpp,$(BUILDDIR)/%, $(SOURCES))
DEPENDS=$(patsubst %.cpp,$(BUILDDIR)/%.d, $(SOURCES))
CC=clang++
CFLAGS=-I . -g -std=c++11 -D_GNU_SOURCE -MMD
LD=clang++
QUIET_COMPILE=1

ifdef V
    QUIET_COMPILE = 0
endif

ifeq ($(QUIET_COMPILE),1)
  # say a one-line description of the action, do not echo the command
  Q=@echo
  E=@
else
  # do not say the short Q lines, but do echo the entire command
  Q=@echo >/dev/null
  E=
endif

# default rule for building executables from object files
$(BINS): %: %.o
	$(Q) "  LD		$@"
	$(E) $(LD) -o $@ $< $(LDFLAGS)

# default rule for building objects 
$(OBJS): %.o: %.cpp
	$(Q) "  CC		$@"
	$(E) $(CC) $(CFLAGS) $< -c -o $@

prep:
	$(Q) "  MKDIR           build"
	$(E) mkdir -p $(BUILDDIR)
	$(Q) "  LN              SOURCES"
	$(E) $(foreach f,$(SOURCES),ln -sf ../$f $(BUILDDIR)/$f;)

all:: prep

all:: $(BINS)

clean:
	$(Q) rm -f $(BUILDDIR)/*
