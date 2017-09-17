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
	std::string ToString() const;

	int hours;
	int minutes;
	int seconds;
	int milliseconds;
};



std::ostream& operator<<(std::ostream& output, const SrtTime& t);
std::istream& operator>>(std::istream& input, SrtTime& t);

#endif

