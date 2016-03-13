#include <string>
#include <memory>
#include <vector>
#include <cstdint>

class FileInterface
{
public:
	virtual ~FileInterface() = 0 {};
	// load "filename" internally as a file pointer
	virtual void loadFile(const std::string& filename) = 0;
	// close the currently open file
	virtual void freeFile() = 0;
	// returns the currently open file name, empty if no file loaded
	virtual const std::string& getFilename() const = 0;
	// read and return entire file as an array of bytes
	virtual std::unique_ptr<std::vector<uint8_t>> getRawFile() = 0;
	// read and return "relevant" data from the file
	virtual std::unique_ptr<std::vector<uint8_t>> getFileData() = 0;
	// Get header information of file, if it exists
	virtual std::unique_ptr<std::vector<uint8_t>> getFileHeader() = 0;
	// Write given data to output file using original header
	virtual void writeNewData(std::unique_ptr<std::vector<uint8_t>>& newData) = 0;

	// these are not needed
	FileInterface& operator= (const FileInterface&) = delete;
	FileInterface(const FileInterface&) = delete;
protected:
	// force a default constructor for implementors
	FileInterface() = default;
};
