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
	Glib::RefPtr<Gtk::Application> app;
	Glib::RefPtr<Gtk::Clipboard> clipboard;
	std::list<std::string> targets;
	std::list<std::string>::const_iterator current;

public:
	ClipDumper(Glib::RefPtr<Gtk::Application> a)
		: app(a), clipboard(Gtk::Clipboard::get())
	{
		// Initiate by registering a callback from the start of the main loop
		Glib::signal_idle().connect_once(sigc::mem_fun(this, &ClipDumper::fetch_targets));
	}

	void fetch_targets()
	{
		// Discover what target types are available
		clipboard->request_targets(sigc::mem_fun(*this, &ClipDumper::receive_targets));
	}

	void receive_targets(const Glib::StringArrayHandle& targets_array)
	{
		// Save the list of clipboard target types
		std::list<std::string> tmp(targets_array);
		targets.swap(tmp);

		// Dump the list to std::cout
		std::copy(targets.begin(), targets.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

		// Start iterating through them, one callback at a time
		current = targets.begin();
		Glib::signal_idle().connect_once(sigc::mem_fun(this, &ClipDumper::fetch_target));
	}

	void fetch_target()
	{
		if (current != targets.end())
		{
			// Fetch the data for the next target type
			clipboard->request_contents(*current++, sigc::mem_fun(*this, &ClipDumper::receive_target));
		}
		else
		{
			app->quit();
		}
	}

	void receive_target(const Gtk::SelectionData& data)
	{
		std::cout << "Got target: " << data.get_target() << "\n";

		// Dump target data
		if (data.get_data())
			HexDump(data.get_data(), data.get_length());
		else
			std::cout << "<null>\n";

		// Iterate
		Glib::signal_idle().connect_once(sigc::mem_fun(this, &ClipDumper::fetch_target));
	}
};

int main(int argc, char *argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);
	ClipDumper dumper(app);

	app->hold();
	app->run();

	return 0;
}

