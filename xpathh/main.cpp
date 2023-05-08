#include "PathHandler.hpp"
#include "cmd_op.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "include.h"

std::istream& is(std::cin);
std::ostream& os(std::cout);

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
		os << "[$]: ";
		string cmd;
		getline(is, cmd);
		stringstream ss(cmd);
		string temp;

		while (ss >> temp) {
			command.push_back(temp);
		}

		cmd_op temp_op = CheckOperation(command[0]);
		PerformAction(temp_op, command);
		command.clear();
	}
}

cmd_op CheckOperation(string op)
{
	if (op == "-p") {
		return Print;
	}
	else if (op == "-d") {
		return Delete;
	}
	else if (op == "-c") {
		return Copy;
	}
	else if (op == "-a") {
		return Create;
	}
	else if (op == "-r") {
		return Refile;
	}
	else if (op == "-fp")
		return FProperties;

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