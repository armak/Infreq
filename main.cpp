#include "wavloader.h"

Bytes convertToBytes(const Audio& samples);
Audio convertToSamples(const Bytes& data);

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		std::cout << "Usage: specinv.exe [filename]" << std::endl;
	}
	else
	{
		// load file and make it into audo samples
		WavLoader loader = WavLoader(std::string(argv[1]));
		auto data = loader.getFileData();
		auto samples = convertToSamples(data);

		// invert spectrum via inverting every other sample
		for(auto it = samples->begin(), end = samples->end(); it != end; it+=2)
		{
			*it *= -1;
		}

		// write back to file
		data->clear();
		data = convertToBytes(samples);
		loader.writeNewData(data);
		
		// clear resources
		data->clear();
		data.reset();
		samples->clear();
		samples.reset();
	}
	return 0;
}

Bytes convertToBytes(const Audio& samples)
{
	Bytes data(new std::vector<uint8_t>);
	data->reserve(data->size()*2);
	// split 16-bit sample to two bytes
	// assume little-endian as per RIFF specifications
	std::for_each(samples->begin(), samples->end(), [&](short s){
		data->push_back( (s >> 8) & 0xff );
		data->push_back( s & 0xff );
	});	
	return data;
}

Audio convertToSamples(const Bytes& data)
{
	Audio samples(new std::vector<short>);
	samples->reserve(data->size()/2);
	// pack two bytes to a 16-bit integer
	// assume little-endian as per RIFF specifications
	for(int i = 0; i < data->size()-1; i += 2)
	{
		samples->push_back((((short) data->at(i) ) << 8) | data->at(i+1));
	}
	return samples;
}