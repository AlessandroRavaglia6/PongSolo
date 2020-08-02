#include "FileReader.h"

#include "../PreprocessorSettings.h"

#ifdef _STD_OUT
#include <iostream>
#endif

FileReader::FileReader() {};

FileReader::FileReader(const std::string& fileName) : _pos(0), _isOpen(false)
{
	std::ifstream fileStream(fileName, std::ios_base::binary);

	fileStream.seekg(0, fileStream.end);
	_fileLength = fileStream.tellg();
	fileStream.seekg(0, fileStream.beg);

	_isOpen = fileStream.is_open();
	if (!_isOpen) 
	{
		#ifdef _STD_OUT
		std::cout << "Error opening file [" << fileName << "]" << std::endl;
		#else
		return;
		#endif
	}
	_fileStream = std::move(fileStream);
}

FileReader::~FileReader() 
{
	#ifdef _STD_OUT
	std::cout << "Closing file.."<< std::endl;
	#endif
	if (_isOpen)
	{
		_fileStream.close();
	}
}

int FileReader::GetFileLenght() { return _fileLength; }

void FileReader::operator>>(char& c) 
{
	if (_isOpen)
	{
		if (_pos == _fileLength) 
		{
			c = EOF;
		}
		else
		{
			_fileStream.read(&c, 1);
			++_pos;
		}
	}
	else 
	{
		c = EOF;
	}
}