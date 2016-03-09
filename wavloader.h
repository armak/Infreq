#include "fileinterface.h"
#include <fstream>
#include <iostream>

class WavLoader: public FileInterface
{
public:
	explicit WavLoader() : file_(std::fstream()), filename_(""){}
	explicit WavLoader(const std::string& filename)
	{
		this->loadFile(filename);
	}

	~WavLoader()
	{
		this->freeFile();
	}
	
	void loadFile(const std::string& filename)
	{
		if(file_.is_open()) freeFile();
		file_.open(filename, std::fstream::in | std::fstream::binary | std::fstream::ate);
		filename_ = filename;
	}

	void freeFile()
	{
		file_.close();
		raw_.clear();
		filename_ = "";
	}
	
	const std::string& getFilename() const
	{
		return filename_;
	}

	std::unique_ptr<std::vector<uint8_t>> getRawFile()
	{
		loadFileToMemory();
		std::unique_ptr<std::vector<uint8_t>> contents(new std::vector<uint8_t>(raw_));
		return contents;
	}

	std::unique_ptr<std::vector<uint8_t>> getFileData()
	{
		loadFileToMemory();
		std::unique_ptr<std::vector<uint8_t>> contents(new std::vector<uint8_t>(raw_));
		return contents;
	}

	std::unique_ptr<std::vector<uint8_t>> getFileHeader()
	{
		loadFileToMemory();
		std::unique_ptr<std::vector<uint8_t>> contents(new std::vector<uint8_t>(raw_));
		return contents;
	}

	// these are not needed
	WavLoader& operator= (const WavLoader&) = delete;
	WavLoader(const WavLoader&) = delete;
private:
	// stream state is allowed to be changed by a const function
	mutable std::fstream file_;
	std::string filename_;
	std::vector<uint8_t> raw_;

	void loadFileToMemory()
	{
		if(raw_.size() < 1)
		{
			if(!file_.is_open())
			{
				std::cout << "No file currently open, aborting." << std::endl;
			}
			else
			{
				std::streamsize size = file_.tellg();
				file_.seekg(0, std::ios::beg);
				raw_ = std::vector<uint8_t>(size);
				if (file_.read(reinterpret_cast<char*>(raw_.data()), size))
				{
					std::cout << "File read successfully." << std::endl;
				}
			}
		}
	}
};
