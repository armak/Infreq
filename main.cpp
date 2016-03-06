#include "wavloader.h"

int main(int argc, char** argv){
	if(argc < 2)
	{
		std::cout << "Usage: infreq.exe [filename]" << std::endl;
		return 0;
	}
	else
	{
		WavLoader loader = WavLoader::WavLoader(std::string(argv[1]));
		std::unique_ptr<std::vector<uint8_t>> file = loader.getFileContents();
		file->clear();
		file.reset();
	}
	return 0;
}
