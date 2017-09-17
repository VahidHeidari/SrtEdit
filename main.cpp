#include <fstream>
#include <iostream>
#include <vector>

#include "srt-record.h"
#include "srt-time.h"

using namespace std;

typedef vector<SrtRecord> SrtRecords;

static void TestToString()
{
	return;

	SrtTime t1 = { 0, 3, 5, 109 };
	cout << t1 << endl;

	SrtTime t2 = { 1, 2, 3, 432 };
	cout << t2 << endl << endl;

	SrtRecord r = { 123, t1, t2, "This is test text!" };
	cout << r << endl;
}

static void PrintArgs(int argc, char** argv)
{
	return;

	for (int i = 0; i < argc; ++i)
		cout << "argv[" << i << "] : " << argv[i] << endl;
}

static void CheckInputFile(int argc, char** argv)
{
	if (argc < 2) {
		cout << "File name required!" << endl;
		exit(1);
	}

	PrintArgs(argc, argv);
}

static vector<SrtRecord> ReadRecords(char* file_path)
{
	ifstream input_file(file_path);
	if (!input_file.is_open()) {
		cout << "Could not open " << file_path << " file!" << endl;
		exit(1);
	}

	SrtRecords records;
	while (!input_file.eof()) {
		SrtRecord r;
		input_file >> r;
		records.push_back(r);
	}

	// Remove last use less record.
	// Because the deserialization process ends at the end of file, it cann't
	// detect the last empty line, and it tries to deserialize it.
	if (records.size())
		records.erase(records.begin() + records.size() - 1);
	return records;
}

static void PrintSrtRecordsStats(const SrtRecords& records)
{
	cout << "Number of records : " << records.size() << endl;
}

int main(int argc, char** argv)
{
	CheckInputFile(argc, argv);
	TestToString();
	SrtRecords records = ReadRecords(argv[1]);
	PrintSrtRecordsStats(records);

	return 0;
}

