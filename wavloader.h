#include "fileinterface.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdio>

typedef std::unique_ptr<std::vector<short>> Audio;
typedef std::unique_ptr<std::vector<uint8_t>> Bytes;

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
		file_.unsetf(std::ios::skipws);
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

	Bytes getRawFile()
	{
		loadFileToMemory();
		Bytes contents(new std::vector<uint8_t>(raw_));
		return contents;
	}

	Bytes getFileData()
	{
		loadFileToMemory();
		Bytes contents(new std::vector<uint8_t>( raw_.begin()+offset_, raw_.end() ));
		return contents;
	}

	Bytes getFileHeader()
	{
		loadFileToMemory();
		Bytes contents(new std::vector<uint8_t>( raw_.begin(), raw_.begin()+offset_-1 ));
		return contents;
	}

	void writeNewData(Bytes& newData)
	{
		std::remove(filename_.c_str());

		std::fstream outfile = std::fstream();
		outfile.open("output.wav", std::fstream::out | std::fstream::binary);// | std::fstream::app);
		std::ostream_iterator<uint8_t> output(outfile);

		std::vector<uint8_t> newFile;
		std::copy(raw_.begin(), raw_.begin()+offset_, output);
		std::copy(newData->begin(), newData->end(), output);
	}

	// these are not needed
	WavLoader& operator= (const WavLoader&) = delete;
	WavLoader(const WavLoader&) = delete;
private:
	// stream state is allowed to be changed by a const function
	mutable std::fstream file_;
	std::string filename_;
	std::vector<uint8_t> raw_;

	const int offset_ = 44;

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
				if(raw_.max_size() < size)
				{
					std::cout << "File too large, aborting." << std::endl;
				}
				else
				{
					file_.seekg(0, std::ios::beg);
					raw_ = std::vector<uint8_t>(size);
					if (file_.read(reinterpret_cast<char*>(raw_.data()), size))
					{
						std::cout << "File read successfully." << std::endl;
					}
					//raw_.insert(raw_.begin(), std::istream_iterator<uint8_t>(file_), std::istream_iterator<uint8_t>());
				}
			}
		}
	}
};
