#include "srt-time.h"

#include <iomanip>
#include <sstream>

using namespace std;

SrtTime::SrtTime()
	: hours(0)
	, minutes(0)
	, seconds(0)
	, milliseconds(0)
{
}

SrtTime::SrtTime(int h, int m, int s, int ms)
	: hours(h)
	, minutes(m)
	, seconds(s)
	, milliseconds(ms)
{
}

SrtTime::SrtTime(const SrtTime& other)
	: hours(other.hours)
	, minutes(other.minutes)
	, seconds(other.seconds)
	, milliseconds(other.milliseconds)
{
}

string SrtTime::ToString() const
{
	stringstream str;
	str << setfill('0') << setw(2) << hours   << ':';
	str << setfill('0') << setw(2) << minutes << ':';
	str << setfill('0') << setw(2) << seconds << ',';
	str << setfill('0') << setw(3) << milliseconds;
	return str.str();
}



inline static void Adjust(int& c, int& n, int bound)
{
	while (c >= bound) {
		c -= bound;
		++n;
	}
}

SrtTime operator+(const SrtTime& f, const SrtTime& s)
{
	SrtTime r (f);

	r.milliseconds += s.milliseconds;
	Adjust(r.milliseconds, r.seconds, 1000);

	r.seconds += s.seconds;
	Adjust(r.seconds, r.minutes, 60);

	r.minutes += s.minutes;
	Adjust(r.minutes, r.hours, 60);

	r.hours += s.hours;

	return r;
}

SrtTime operator-(const SrtTime& f, const SrtTime& s)
{
	SrtTime r;
	return r;
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

