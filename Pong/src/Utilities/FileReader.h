#ifndef _FILE_READER
#define _FILE_READER

#include <fstream>
#include <string>

class FileReader 
{
private:
	std::ifstream _fileStream;
	int _fileLength;
	int _pos;
	bool _isOpen;

private:
	FileReader();

public:
	~FileReader();

	FileReader(const std::string& fileName);

	int GetFileLenght();

	void operator>>(char& c);
};

#endif