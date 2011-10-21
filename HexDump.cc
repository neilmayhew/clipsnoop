
#include "HexDump.h"
#include <ostream>

using std::size_t;

void HexDump(const void *theData, size_t size, std::ostream& s)
{
	static char hDigits[] = "0123456789ABCDEF";

	const unsigned char* data = static_cast<const unsigned char*>(theData);

	for (size_t j = 0; j < size; j += 16)
	{
		s << hDigits[j >> 16 & 15];
		s << hDigits[j >> 12 & 15];
		s << hDigits[j >>  8 & 15];
		s << hDigits[j >>  4 & 15];
		s << hDigits[j       & 15];

		s << ':';
		s << ' ';

		for (size_t i = 0; i < 16; i++)
		{
			if (j + i < size)
			{
				s << hDigits[data[j + i] >> 4];
				s << hDigits[data[j + i] & 15];
			}
			else
			{
				s << "  ";
			}
			if ((i & 1) == 1)
				s << ' ';
		}

		s << ' ';

		for (size_t i = 0; i < std::min(size_t(16), size-j); i++)
		{
			if (j + i < size)
			{
				if (' ' <= data[j + i] && data[j + i] <= '~')
					s << data[j + i];
				else
					s << '.';
			}
			else
			{
				s << " ";
			}
		}

		s << '\n';
	}
}
