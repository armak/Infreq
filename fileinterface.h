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
	// read and return file as an array of bytes
	virtual std::unique_ptr<std::vector<uint8_t>> getFileContents() const = 0;
};