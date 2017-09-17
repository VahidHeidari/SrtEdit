#include "srt-record.h"

#include <iomanip>
#include <sstream>

using namespace std;

string SrtRecord::ToString() const
{
	stringstream str;
	str << number << endl;
	str << start.ToString() << " --> " << end.ToString() << endl;
	str << text << endl;
	return str.str();
}



std::ostream& operator<<(std::ostream& output, const SrtRecord& r)
{
	output << r.ToString();
	return output;
}

std::istream& operator>>(std::istream& input, SrtRecord& r)
{
	string str;
	input >> r.number;
	input >> r.start >> str >> r.end;
	while (getline(input, str)) {
		if (str == "") {
			if (r.text.size())
				break;
			else
				continue;
		}

		r.text += str;
		r.text += '\n';
	}
	return input;
}

