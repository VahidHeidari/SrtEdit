#include "srt-editor.h"

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

SrtEditor::SrtEditor()
{
}

SrtEditor::~SrtEditor()
{
}

void SrtEditor::DoActions()
{
	string command;

	do {
		PrintCommands();
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
		case CMD_SAVE:			Save(command);			break;
		case CMD_SYNC:			Sync(command);			break;
		case CMD_SYNC_RECORDS:	SyncRecords(command);	break;

		case CMD_QUIT:
		case CMD_UNKNOWN:
		default:
			break;
	}
}

SrtEditor::CommandType
SrtEditor::FindCommandType(const string& command) const
{
	if (command.empty())
		return CMD_UNKNOWN;

	if (command == "quit")
		return CMD_QUIT;

	switch (command[0]) {
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

		case 'f':
			if (strncmp(command.c_str(), "from:", 5) == 0)
				return CMD_SYNC_RECORDS;

			break;

		default:
			break;
	}

	return CMD_UNKNOWN;
}

void SrtEditor::PrintCommands() const
{
	cout << "quit                     Quits the application!" << endl;
	cout << "save PATH                "
		<< "Saves the modified srt file to the given path." << endl;
	cout << "sync TIME                Syncs all records." << endl;
	cout << "from:REC to:RED TIME     Sync records from-to." << endl;
	cout << endl;
}

void SrtEditor::Print(const std::string& command) const
{
	(void)command;
}

bool SrtEditor::Save(const std::string& command) const
{
	std::string path = command.substr(6);

	ofstream output_file(path.c_str());
	if (!output_file.is_open())
		return false;

	for (unsigned i = 0; i < records.size(); ++i)
		output_file << records[i] << endl << endl;

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

