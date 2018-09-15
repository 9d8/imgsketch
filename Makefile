CC=gcc
TARGET=imgsketch

#Directories
BUILDDIR=build
INCLUDEDIRS=include
SRCDIR=src
TESTDIR=tests

CFLAGS=
LIBS=m png

############################################

INCLUDE=$(patsubst %,-I%,$(INCLUDEDIRS))
EXTERNLIB=$(patsubst %,-l%,$(LIBS))

TARGETOBJECT=$(BUILDDIR)/$(TARGET).o

OBJECTS=$(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(wildcard $(SRCDIR)/*.c))
OBJECTS:=$(filter-out $(TARGETOBJECT),$(OBJECTS))

TESTS=$(patsubst $(TESTDIR)/%.c,$(BUILDDIR)/%,$(wildcard $(TESTDIR)/*.c))
TESTOBJECTS=$(patsubst %,%.o,$(TESTS))

all: $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE) $(EXTERNLIB)

$(BUILDDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE) $(EXTERNLIB)

# Make build directory when trying to create an object file
$(TESTOBJECTS) $(TARGETOBJECT) $(OBJECTS): | $(BUILDDIR)  

$(TARGET): $(TARGETOBJECT) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$@ $^ $(INCLUDE) $(EXTERNLIB)

$(TESTS): $(TESTOBJECTS) $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $@.o $(OBJECTS) $(INCLUDE) $(EXTERNLIB)

$(BUILDDIR):
	mkdir $(BUILDDIR)

.PHONY: tests debug clean

tests: $(TESTS)

debug: CFLAGS:=$(CFLAGS)-ggdb
debug: $(TARGET)

clean:
	-rm $(BUILDDIR)/$(TARGET) $(TARGETOBJECT) $(OBJECTS) $(TESTS) $(TESTOBJECTS) 2>/dev/null
