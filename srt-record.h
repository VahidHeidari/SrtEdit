#ifndef SRT_RECORD_H_
#define SRT_RECORD_H_

#include <istream>
#include <ostream>
#include <string>

#include "srt-time.h"

class SrtRecord
{
public:
	std::string ToString() const;

	int number;
	SrtTime start;
	SrtTime end;
	std::string text;
};



std::ostream& operator<<(std::ostream& output, const SrtRecord& r);
std::istream& operator>>(std::istream& input, SrtRecord& r);

#endif

