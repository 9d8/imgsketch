CC=gcc
TARGET=imgsketch

#Directories
BUILDDIR=build
INCLUDEDIRS=include
SRCDIR=src

CFLAGS=
LIBS=m png

############################################

OBJECTS=$(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(wildcard $(SRCDIR)/*.c))
INCLUDE=$(patsubst %,-I%,$(INCLUDEDIRS))
LIB=$(patsubst %,-l%,$(LIBS))

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE) $(LIB)

$(TARGET): mkdir $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$@ $(OBJECTS) $(INCLUDE) $(LIB)

.PHONY: debug clean mkdir

debug: CFLAGS:=$(CFLAGS)-ggdb
debug: $(TARGET)

clean:
	-rm $(BUILDDIR)/$(TARGET) $(OBJECTS) 2>/dev/null

mkdir:
	@-mkdir $(BUILDDIR) || true
