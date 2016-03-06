#include "fileinterface.h"
#include <fstream>

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
		file_.open(filename, std::fstream::in | std::fstream::binary);
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
		std::unique_ptr<std::vector<uint8_t>> contents(new std::vector<uint8_t>);
		return contents;
	}
private:
	std::fstream file_;
	std::string filename_;
};