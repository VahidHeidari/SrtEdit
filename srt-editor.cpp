#include "srt-editor.h"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <utility>

using namespace std;

typedef pair<int, int> Range;

static inline int ToString(const char* str)
{
	int num = 0;
	char ch = *str;
	while (ch && isdigit(ch)) {
		num *= 10;
		num += *str - 0x30;
		ch = *(++str);
	}

	return num;
}

static Range ParseRange(const std::string& str, int end)
{
	// Find numbers positions.
	string::size_type first_num = str.find("from:") + 5;
	string::size_type second_num = str.find("to:", first_num);

	// Parse numbers.
	int first_record = ToString(str.c_str() + first_num);
	int second_record;
	if (second_num == string::npos)
		second_record = end;
	else
		second_record = ToString(str.c_str() + second_num + 3);


	if (first_record > second_record)
		swap(first_record, second_record);

	return make_pair(first_record - 1, second_record);
}



SrtEditor::SrtEditor()
{
}

SrtEditor::~SrtEditor()
{
}

void SrtEditor::DoActions()
{
	string command;

	PrintCommands();

	do {
		cout << "> ";		// Print prompt.
		getline(cin, command);
		DoCommand(command);
	} while (command != "quit");
}

void SrtEditor::PrintStats() const
{
	cout << "Number of records : " << records.size() << endl;
}

bool SrtEditor::ReadRecords(const char* file_path)
{
	ifstream input_file(file_path);
	if (!input_file.is_open()) {
		cout << "Could not open " << file_path << " file!" << endl;
		return false;	
	}

	int i = 0;
	records.clear();
	while (!input_file.eof()) {
		SrtRecord r;
		input_file >> r;
		records.push_back(r);

		// Print progress.
		if (++i >= 100) {
			i = 0;
			cout << '\r' << "Num Records : " << records.size();
		}
	}

	// Remove last use less record.
	// Because the deserialization process ends at the end of file, it cann't
	// detect the last empty line, and it tries to deserialize it.
	if (records.size()) {
		if (records[records.size() - 1].text.empty())
			records.erase(records.begin() + records.size() - 1);

		if (records.size() >= 100)
			cout << endl;
	}

	input_file.close();
	return !input_file.is_open();
}

void SrtEditor::DoCommand(const string& command)
{
	CommandType type = FindCommandType(command);

	switch (type) {
		case CMD_HELP:			PrintCommands();		break;
		case CMD_PRINT:			Print(command);			break;
		case CMD_SAVE:			Save(command);			break;
		case CMD_SYNC:			Sync(command);			break;
		case CMD_SYNC_RECORDS:	SyncRecords(command);	break;
		case CMD_QUIT:									break;

		case CMD_UNKNOWN:
		default:
			cout << "Unknown command!" << endl << endl;
			break;
	}
}

SrtEditor::CommandType
SrtEditor::FindCommandType(const string& command) const
{
	if (command.empty())
		return CMD_UNKNOWN;

	switch (command[0]) {
		case 'f':
			if (strncmp(command.c_str(), "from:", 5) == 0)
				return CMD_SYNC_RECORDS;
			break;

		case 'h':
			if (command == "help")
				return CMD_HELP;
			break;

		case 'p':
			if (command.size() < 5)
				break;
			if (strncmp(command.c_str(), "print", 5) == 0)
				return CMD_PRINT;
			break;

		case 's':
			if (command.size() < 4)
				break;
			if (strncmp(command.c_str(), "save", 4) == 0)
				return CMD_SAVE;
			else if (strncmp(command.c_str(), "sync", 4) == 0)
				return CMD_SYNC;
			break;

		case 'q':
			if (command == "quit")
				return CMD_QUIT;
			break;

		default:
			break;
	}

	return CMD_UNKNOWN;
}

void SrtEditor::PrintCommands() const
{
	cout << "help                     This help menu." << endl;
	cout << "quit                     Quits the application!" << endl;
	cout << "print from:REC to:REC    Print from-to." << endl;
	cout << "save PATH                "
		<< "Saves the modified srt file to the given path." << endl;
	cout << "sync TIME                Syncs all records." << endl;
	cout << "from:REC to:RED TIME     Sync records from-to." << endl;
	cout << endl;
}

void SrtEditor::Print(const std::string& command) const
{
	Range range = ParseRange(command.substr(5), records.size());

	// Print records.
	while (range.first < range.second)
		cout << records[range.first++];
}

bool SrtEditor::Save(const std::string& command) const
{
	std::string path = command.substr(5);

	ofstream output_file(path.c_str());
	if (!output_file.is_open()) {
		cout << "Could not open a file for save into!" << endl;
		return false;
	}

	for (unsigned i = 0; i < records.size(); ++i)
		output_file << records[i];

	cout << "Save done!" << endl;
	return true;
}

void SrtEditor::Sync(const std::string& command)
{
	(void)command;
}

void SrtEditor::SyncRecords(const std::string& command)
{
	(void)command;
}

