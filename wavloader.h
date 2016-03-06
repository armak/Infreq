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
		file_.open(filename, std::fstream::in | std::fstream::binary | std::fstream::ate);
		filename_ = filename;
	}

	void freeFile()
	{
		filename_ = "";
	}
	
	const std::string& getFilename() const
	{
		return filename_;
	}

	std::unique_ptr<std::vector<uint8_t>> getFileContents() const
	{
		std::streamsize size = file_.tellg();
		std::cout << size << std::endl;
		file_.seekg(0, std::ios::beg);
		std::vector<char> buffer(size);
		if (file_.read( buffer.data(), size))
		{
			std::cout << "File read successfully." << std::endl;
		}

		std::unique_ptr<std::vector<uint8_t>> contents(new std::vector<uint8_t>);
		contents->assign(buffer.begin(), buffer.end());
		return contents;
	}
private:
	mutable std::fstream file_;
	std::string filename_;
};
