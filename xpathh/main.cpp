#include "PathHandler.hpp"
#include "cmd_op.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "include.h"

std::istream& is(std::cin);
std::ostream& os(std::cout);
fs::path current_path = fs::current_path();

int main()
{
	vector<string> command;

	/* flag -p = print dir
	flag -d = delete file
	flag -c = copy file
	flag -a = create file 
	flag -r = rename file 
	flag -fp = file prop */
	while (true)
	{
		os << "Current path: " << current_path << " ~ ";
		os << "[$]: ";
		string cmd;
		getline(is, cmd);
		stringstream ss(cmd);
		string temp;

		while (ss >> temp) {
			command.push_back(temp);
		}

		cmd_op temp_op = CheckOperation(command);
		PerformAction(temp_op, command);
		command.clear();
	}
}

cmd_op CheckOperation(vector<string>& cmd)
{
	for (auto& c : cmd) {
		if (c == "~") {
			c = current_path.string();
		}
	}

	if (cmd[0] == "-p") {
		return Print;
	}
	else if (cmd[0] == "-d") {
		return Delete;
	}
	else if (cmd[0] == "-c") {
		return Copy;
	}
	else if (cmd[0] == "-a") {
		return Create;
	}
	else if (cmd[0] == "-r") {
		return Refile;
	}
	else if (cmd[0] == "-fp") {
		return FProperties;
	}
	else if (cmd[0] == "-h") {
		return Help;
	}
	else if (cmd[0] == "-cl" || cmd[0] == "-clear") {
		return CClear;
	}
	else if (cmd[0] == "-cd") {
		return CurrentPath;
	}

	return None;
}

void PerformAction(cmd_op temp_op, vector<string> param)
{
	try
	{
		switch (temp_op)
		{
		case Print:
			PathHandler::PrintDirectoryContent(param[1]);
			break;
		case Delete:
			PathHandler::DeleteFile(param[1]);
			break;
		case Copy:
			PathHandler::CopyFile(param[1], param[2]);
			break;
		case Create:
			PathHandler::CreateFile(param[1], param[2]);
			break;
		case Refile:
			PathHandler::Rename(param[1], param[2]);
			break;
		case FProperties:
			PathHandler::FileProperties(param[1]);
			break;
		case Help:
			PathHandler::HelpView();
			break;
		case CClear:
			system("cls");
			break;
		case CurrentPath:
			PathHandler::ChangeCurrentDirectory(param[1], current_path);
			break;
		case None:
			os << "Unkown operation" << endl;
			break;
		}
	}
	catch (const std::exception& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
}
