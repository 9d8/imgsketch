CC=gcc
TARGET=imgsketch

#Directories
BUILDDIR=build
INCLUDEDIRS=include
SRCDIR=src
TESTDIR=tests

CFLAGS=
# You can comment out the JPEG_SUPPORT line to disable jpeg support.
CPPFLAGS=			\
	-D JPEG_SUPPORT	\

############################################

LIBS=m png

TARGETOBJECT=$(BUILDDIR)/$(TARGET).o

# Objects include objects for all source files in src except for the target
# source file (whichever one has main in it).
OBJECTS=$(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(wildcard $(SRCDIR)/*.c))
OBJECTS:=$(filter-out $(TARGETOBJECT),$(OBJECTS))

TESTS=$(patsubst $(TESTDIR)/%.c,$(BUILDDIR)/%,$(wildcard $(TESTDIR)/*.c))
TESTOBJECTS=$(patsubst %,%.o,$(TESTS))

# Link jpeg if lib is enabled
ifneq (,$(findstring JPEG_SUPPORT,$(CPPFLAGS)))
	LIBS:=$(LIBS) jpeg
else
	OBJECTS:=$(filter-out $(BUILDDIR)/jpegfile.o,$(OBJECTS))
endif

INCLUDE=$(patsubst %,-I%,$(INCLUDEDIRS))
EXTERNLIB=$(patsubst %,-l%,$(LIBS))

all: $(TARGET)

# Compiles object files from source files.
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< $(INCLUDE) $(EXTERNLIB)

# This is needed to make objects of files in the test directory.
$(BUILDDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< $(INCLUDE) $(EXTERNLIB)

# Make build directory when trying to create an object file.
$(TESTOBJECTS) $(TARGETOBJECT) $(OBJECTS): | $(BUILDDIR)  

# Link all objects and compile executable.
$(TARGET): $(TARGETOBJECT) $(OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(BUILDDIR)/$@ $^ $(INCLUDE) $(EXTERNLIB)

# Link all objects and compile test executables.
$(TESTS): $(TESTOBJECTS) $(OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $@.o $(OBJECTS) $(INCLUDE) $(EXTERNLIB)

$(BUILDDIR):
	mkdir $(BUILDDIR)

.PHONY: tests debug clean

tests: $(TESTS)

debug: CFLAGS:=$(CFLAGS)-ggdb
debug: $(TARGET)

clean:
	-rm $(BUILDDIR)/$(TARGET) $(TARGETOBJECT) $(OBJECTS) $(TESTS) $(TESTOBJECTS) 2>/dev/null
