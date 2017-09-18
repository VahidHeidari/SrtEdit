#include "srt-time.h"

#include <iomanip>
#include <sstream>

using namespace std;

SrtTime::SrtTime()
	: is_negative(false)
	, hours(0)
	, minutes(0)
	, seconds(0)
	, milliseconds(0)
{
}

SrtTime::SrtTime(long ms)
{
	FromMilliseconds(ms);
}

SrtTime::SrtTime(int h, int m, int s, int ms, bool is_negative)
	: is_negative(is_negative)
	, hours(h)
	, minutes(m)
	, seconds(s)
	, milliseconds(ms)
{
}

SrtTime::SrtTime(const SrtTime& other)
	: is_negative(other.is_negative)
	, hours(other.hours)
	, minutes(other.minutes)
	, seconds(other.seconds)
	, milliseconds(other.milliseconds)
{
}

void SrtTime::FromMilliseconds(long ms)
{
	is_negative = false;
	if (ms < 0) {
		is_negative = true;
		ms = -ms;
	}

	milliseconds = ms % 1000;
	ms /= 1000;
	seconds = ms % 60;
	ms /= 60;
	minutes = ms % 60;
	ms /= 60;
	hours = ms;
}

long SrtTime::ToMilliseconds() const
{
	long ms = milliseconds;
	ms += seconds * 1000;
	ms += minutes * 60 * 1000;
	ms += hours * 60 * 60 * 1000;

	ms *= is_negative ? -1 : 1;

	return ms;
}

string SrtTime::ToString() const
{
	stringstream str;
	if (is_negative)
		str << '-';
	str << setfill('0') << setw(2) << hours   << ':';
	str << setfill('0') << setw(2) << minutes << ':';
	str << setfill('0') << setw(2) << seconds << ',';
	str << setfill('0') << setw(3) << milliseconds;
	return str.str();
}



SrtTime operator+(const SrtTime& f, const SrtTime& s)
{
	long ms = f.ToMilliseconds() + s.ToMilliseconds();
	SrtTime r(ms);
	return r;
}

SrtTime& operator+=(SrtTime& f, long ms)
{
	ms += f.ToMilliseconds();
	f.FromMilliseconds(ms);
	return f;
}

SrtTime operator-(const SrtTime& f, const SrtTime& s)
{
	long ms = f.ToMilliseconds() - s.ToMilliseconds();
	SrtTime r(ms);
	return r;
}

bool operator==(const SrtTime& f, const SrtTime& s)
{
	return f.is_negative == s.is_negative
		&& f.hours == s.hours
		&& f.minutes == s.minutes
		&& f.seconds == s.seconds
		&& f.milliseconds == s.milliseconds;
}

bool operator!=(const SrtTime& f, const SrtTime& s)
{
	return !(f == s);
}

bool operator<(const SrtTime& f, const SrtTime& s)
{
	return f.ToMilliseconds() < s.ToMilliseconds();
}

bool operator<=(const SrtTime& f, const SrtTime& s)
{
	return f.ToMilliseconds() <= s.ToMilliseconds();
}

bool operator>(const SrtTime& f, const SrtTime& s)
{
	return f.ToMilliseconds() > s.ToMilliseconds();
}

bool operator>=(const SrtTime& f, const SrtTime& s)
{
	return f.ToMilliseconds() >= s.ToMilliseconds();
}



std::ostream& operator<<(std::ostream& output, const SrtTime& t)
{
	output << t.ToString();
	return output;
}

std::istream& operator>>(std::istream& input, SrtTime& t)
{
	char ch;
	input >> ch;
	if (ch == '-')
		t.is_negative = true;
	else
		input.putback(ch);

	input >> t.hours >> ch;
	input >> t.minutes >> ch;
	input >> t.seconds >> ch;
	input >> t.milliseconds;
	return input;
}

