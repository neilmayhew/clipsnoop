CXXFLAGS = -g

export GTKMM_CPP = $(shell pkg-config --cflags gtkmm-2.4)
export GTKMM_LIB = $(shell pkg-config --libs   gtkmm-2.4)

CPPFLAGS += $$GTKMM_CPP
LDLIBS   += $$GTKMM_LIB

clipsnoop: clipsnoop.o HexDump.o
	$(LINK.cc) -o $@ $^ $(LDLIBS)

clean:
	$(RM) clipsnoop *.[od]
