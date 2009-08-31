CXXFLAGS = -g

export GTKMM_CPP = $(shell pkg-config --cflags gtkmm-2.4)
export GTKMM_LD  = $(shell pkg-config --libs   gtkmm-2.4)

CPPFLAGS += $$GTKMM_CPP
LDFLAGS  += $$GTKMM_LD

clipsnoop: clipsnoop.o HexDump.o
	$(LINK.cc) -o $@ $^

clean:
	$(RM) clipsnoop *.[od]
