PREFIX = $(HOME)
BINDIR = $(PREFIX)/bin

CXXFLAGS = -O2 -g

export GTKMM_CPP = $(shell pkg-config --cflags gtkmm-3.0)
export GTKMM_LIB = $(shell pkg-config --libs   gtkmm-3.0)

CPPFLAGS += $$GTKMM_CPP
LDLIBS   += $$GTKMM_LIB

clipsnoop: clipsnoop.o HexDump.o
	$(LINK.cc) -o $@ $^ $(LDLIBS)

clean:
	$(RM) clipsnoop *.[od]

install:
	install -d $(DESTDIR)$(BINDIR)/
	install clipsnoop $(DESTDIR)$(BINDIR)/
