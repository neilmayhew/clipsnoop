CXXFLAGS = -g

CPPFLAGS += $(shell pkg-config --cflags gtkmm-2.4)
LDFLAGS  += $(shell pkg-config --libs   gtkmm-2.4)

clipsnoop: clipsnoop.o HexDump.o
	$(LINK.cc) -o $@ $^

clean:
	$(RM) clipsnoop *.[od]
