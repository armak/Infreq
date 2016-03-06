#include "fileinterface.h"
#include <fstream>

class WavLoader: public FileInterface
{
public:
	explicit WavLoader() : file(std::fstream()){}
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
		file.open(filename, std::fstream::in | std::fstream::binary);
	}

	void freeFile()
	{

	}
	
	std::unique_ptr<std::vector<uint8_t>> getFileContents()
	{
		std::unique_ptr<std::vector<uint8_t>> contents(new std::vector<uint8_t>);
		return contents;
	}
private:
	std::fstream file;
};