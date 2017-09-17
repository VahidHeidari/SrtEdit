#ifndef SRT_EDITOR_H_
#define SRT_EDITOR_H_

#include <string>
#include <vector>

#include "srt-record.h"

class SrtEditor
{
public:
	enum CommandType
	{
		CMD_HELP,
		CMD_PRINT,
		CMD_SAVE,
		CMD_SYNC,
		CMD_SYNC_RECORDS,
		CMD_QUIT,

		CMD_UNKNOWN
	};

	typedef std::vector<SrtRecord> SrtRecords;

	SrtEditor();
	~SrtEditor();

	void DoActions();
	void PrintStats() const;
	bool ReadRecords(const char* file_path);

private:
	void DoCommand(const std::string& command);
	CommandType FindCommandType(const std::string& command) const;
	void PrintCommands() const;
	void Print(const std::string& command) const;
	bool Save(const std::string& command) const;
	void Sync(const std::string& commnad);
	void SyncRecords(const std::string& command);

	SrtRecords records;
};

#endif

