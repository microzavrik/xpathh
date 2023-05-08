#include "PathHandler.hpp"
#include <filesystem>
#include <map>
#include <fstream>
#include <iostream>
#include <string>

namespace PathHandler
{
	ostream& os = cout;
	istream& is = cin;

	const fs::path PrintDirectoryContent(const fs::path& path)
	{
		if (!fs::exists(path) || !fs::is_directory(path)) {
			cerr << "Invalid directory path: " << path << endl;

			return fs::path("");
		}

		os << "Contents of directory " << path << ": " << endl;

		map<unsigned, fs::path> fmap;
		int count = 1;

		for (const auto& entry : fs::directory_iterator(path)) {
			fmap[count] = entry;
			os << count++ << ": " << entry.path().filename() << endl;
		}

		is.clear();

		int nfile = 0;
		return fmap[1];
	}

	void DeleteFile(const fs::path& path)
	{
		if (fs::is_directory(path)) {
			os << "This is the directory" << endl;
			return;
		}
		
		try
		{
			os << "File deleted" << endl;
			fs::remove(path);
		}
		catch (const std::filesystem::filesystem_error& e) {
			cerr << "Error deleting file: " << e.what() << endl;
		}
	}

	void CopyFile(const fs::path& source_path, const fs::path& target_path)
	{
		if (!fs::exists(source_path)) {
			cerr << "Source file not found" << endl;
			return;
		}

		try
		{
			fs::copy(source_path, target_path);
			os << "File copied" << endl;
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			cerr << "Error copying file: " << e.what() << endl;
			return;
		}
	}

	void CreateFile(const fs::path& folder_path, const fs::path name_file)
	{
		fs::path file_path = folder_path / name_file;
		ofstream outfile(file_path);

		if (outfile.is_open()) {
			outfile << "new file" << endl;
			outfile.close();

			os << "File created" << endl;
		}
		else {
			cerr << "Failed to open a file" << endl;
		}
	}

	void Rename(const fs::path& old_path, const fs::path& new_path)
	{
		auto parent_path = old_path.parent_path();
		auto new_dir = parent_path / new_path;
		
		try
		{
			fs::rename(old_path, new_dir);
			os << "File rename" << endl;
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			cerr << "Error: " << e.what() << endl;
		}
	}

	void FileProperties(const fs::path& path)
	{
		try
		{
			fs::directory_entry file(path);

			os << "File size: " << file.file_size() << " bytes." << endl;
			os << "Full path to file: " << file.path().string() << endl;
			os << "Extension file: " << path.extension() << endl;
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			cerr << "Error: " << e.what() << endl;
		}
	}

	void HelpView()
	{
		os << "flag -p = print dir\nflag -d = delete file\nflag -c = copy file\nflag -a = create file" <<
			"\nflag -r = rename file\nflag -fp = file prop" << endl;
	}

	void ChangeCurrentDirectory(const string new_path, fs::path& current_path)
	{
		fs::path p = new_path;

		try
		{
			if (fs::is_directory(p)) {
				current_path = p;
			}
			else {
				throw std::runtime_error("Error change directory");
			}
		}
		catch (const std::runtime_error& e)
		{
			cerr << e.what() << endl;
		}
	}
}