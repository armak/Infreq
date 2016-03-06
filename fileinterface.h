#include <string>
#include <memory>
#include <vector>
#include <cstdint>

//template <typename T> class FileInterface
class FileInterface
{
public:
	virtual ~FileInterface() = 0 {};
	// load "filename" internally as a file pointer
	virtual void loadFile(const std::string& filename) = 0;
	// close the currently open file
	virtual void freeFile() = 0;
	// read and return file as an array of bytes
	virtual std::unique_ptr<std::vector<uint8_t>> getFileContents() = 0;
};