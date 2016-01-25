CXX = clang++
LD = clang++
CFLAGS = -g -Wall -D_GNU_SOURCE -MMD -std=c++11 -I .
LDFLAGS=
AR = ar
ARFLAGS = crs
BUILDDIR = build
sortSources=bubbleSort.cpp insertionSort.cpp
sortObjs=$(patsubst %.cpp, $(BUILDDIR)/%.o, $(sortSources))
sortDepends=$(patsubst %.cpp, $(BUILDDIR)/%.d, $(sortSources))

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

prep:
	$(Q) "  MKDIR           build"
	$(E) mkdir -p $(BUILDDIR)
	$(Q) "  LN              SOURCES"
	$(E) $(foreach f,$(sortSources),ln -sf ../$f $(BUILDDIR)/$f;)
	
testSort: $(BUILDDIR)/testSort.o $(BUILDDIR)/libsort.a
	$(Q) " LD $@"
	$(E) $(LD) -o $(BUILDDIR)/$@ $(BUILDDIR)/testSort.o -L $(BUILDDIR) -lsort $(LDFLAGS)

$(BUILDDIR)/testSort.o: testSort.cpp
	$(Q) " CXX $@"
	$(CXX) -o $@ $< $(CFLAGS) -c

$(BUILDDIR)/libsort.a: $(sortObjs)
	$(Q) " AR $@"
	$(AR) $(ARFLAGS) $@ $^

$(sortObjs): %.o: %.cpp
	$(Q) " CXX $@"
	$(CXX) $(CFLAGS) $< -c -o $@

all:: prep testSort

clean:
	$(Q) "CLEAN "
	$(E) rm -rf $(BUILDDIR)
