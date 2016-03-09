#include "wavloader.h"

int main(int argc, char** argv){
	if(argc < 2)
	{
		std::cout << "Usage: specinv.exe [filename]" << std::endl;
		return 0;
	}
	else
	{
		WavLoader loader = WavLoader::WavLoader(std::string(argv[1]));
		auto data = loader.getRawFile();
		data->clear();
		data.reset();
	}
	return 0;
}
