#include <iomanip>
#include <iostream>

#include "srt-editor.h"
#include "srt-record.h"
#include "srt-time.h"

using namespace std;

static void TestToString()
{
	SrtTime t1(0, 3, 5, 109);
	cout << t1 << endl;

	SrtTime t2(1, 2, 3, 432);
	cout << t2 << endl << endl;

	SrtRecord r = { 123, t1, t2, "This is test text!" };
	cout << r << endl;
}

static void TestTimeOperators()
{
	SrtTime t1(0, 0, 0, 999);
	SrtTime t2(0, 0, 0, 1);
	cout << t1 + t2 << endl;

	cout << boolalpha << (t1 < t2) << endl;
	cout << boolalpha << (t1 > t2) << endl;
	cout << boolalpha << (t1 == t2) << endl;
	cout << boolalpha << (t1 != t2) << endl;
}

static void PrintTests()
{
	return;

	TestToString();
	TestTimeOperators();
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

int main(int argc, char** argv)
{
	CheckInputFile(argc, argv);
	PrintTests();

	SrtEditor editor;
	if (!editor.ReadRecords(argv[1]))
		return 1;

	editor.PrintStats();
	editor.DoActions();

	return 0;
}

