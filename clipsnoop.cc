/*
 *	clipsnoop.cc
 *
 *	Snoop the contents of the clipboard
 *
 *	Neil Mayhew - 2008-11-20
 *
 *	$Id: clipsnoop.cc,v 1.1 2008-11-24 04:29:52 mayhewn Exp $
 */

#include <gtkmm.h>
#include <algorithm>
#include <iostream>

#include "HexDump.h"

class ClipDumper
{
	Glib::RefPtr<Gtk::Clipboard> clipboard;
	std::list<std::string> targets;
	std::list<std::string>::const_iterator current;

public:
	ClipDumper()
		: clipboard(Gtk::Clipboard::get())
	{
	}

	void on_received_target(const Gtk::SelectionData& data)
	{
		std::cout << "Got target: " << data.get_target() << "\n";

		// Dump target data
		if (data.get_data())
			HexDump(data.get_data(), data.get_length());
		else
			std::cout << "<null>\n";
		
		// Iterate
		fetch_target();
	}

	void on_received_targets(const Glib::StringArrayHandle& targets_array)
	{
		// Save the list of clipboard target types
		std::list<std::string> tmp(targets_array);
		targets.swap(tmp);

		// Dump the list to std::cout
		std::copy(targets.begin(), targets.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

		// Start iterating through them, one callback at a time
		current = targets.begin();
		fetch_target();
	}

	void fetch_target()
	{
		if (current != targets.end())
		{
			// Fetch the data for the next target type
			clipboard->request_contents(*current,
				sigc::mem_fun(*this, &ClipDumper::on_received_target));
			++current;
		}
		else
		{
			Gtk::Main::quit();
		}
	}

	void start()
	{
		// Discover what target types are available
		clipboard->request_targets(sigc::mem_fun(*this, &ClipDumper::on_received_targets));
	}
};

int main(int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);
	ClipDumper dumper;

	// Initiate by registering a callback from the start of the main loop
	Gtk::Main::signal_run().connect(sigc::mem_fun(dumper, &ClipDumper::start));
	Gtk::Main::run();

	return 0;
}

