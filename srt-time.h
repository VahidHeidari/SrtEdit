#ifndef SRT_TIME_H_
#define SRT_TIME_H_

#include <istream>
#include <ostream>
#include <string>

/**
 * The time format is:
 *
 *	hours:minutes:seconds,milliseconds
 *
 *
 * Examples:
 *
 *  00:00:00,000
 *  00:20:41,150
 *  00:20:45,109
 */
class SrtTime
{
public:
	SrtTime();
	explicit SrtTime(long ms);
	SrtTime(int h, int m, int s, int ms, bool is_negative = false);
	SrtTime(const SrtTime& other);

	void FromMilliseconds(long ms);
	long ToMilliseconds() const;
	std::string ToString() const;

	bool is_negative;
	int hours;
	int minutes;
	int seconds;
	int milliseconds;
};



SrtTime operator+(const SrtTime& f, const SrtTime& s);
SrtTime& operator+=(SrtTime& f, long ms);
SrtTime operator-(const SrtTime& f, const SrtTime& s);
bool operator==(const SrtTime& f, const SrtTime& s);
bool operator!=(const SrtTime& f, const SrtTime& s);
bool operator<(const SrtTime& f, const SrtTime& s);
bool operator<=(const SrtTime& f, const SrtTime& s);
bool operator>(const SrtTime& f, const SrtTime& s);
bool operator>=(const SrtTime& f, const SrtTime& s);

std::ostream& operator<<(std::ostream& output, const SrtTime& t);
std::istream& operator>>(std::istream& input, SrtTime& t);

#endif

