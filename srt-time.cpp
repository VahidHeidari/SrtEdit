#include "srt-time.h"

#include <iomanip>
#include <sstream>

using namespace std;

string SrtTime::ToString() const
{
	stringstream str;
	str << setfill('0') << setw(2) << hours   << ':';
	str << setfill('0') << setw(2) << minutes << ':';
	str << setfill('0') << setw(2) << seconds << ',';
	str << setfill('0') << setw(3) << milliseconds;
	return str.str();
}



std::ostream& operator<<(std::ostream& output, const SrtTime& t)
{
	output << t.ToString();
	return output;
}

std::istream& operator>>(std::istream& input, SrtTime& t)
{
	char ch;
	input >> t.hours >> ch;
	input >> t.minutes >> ch;
	input >> t.seconds >> ch;
	input >> t.milliseconds;
	return input;
}

