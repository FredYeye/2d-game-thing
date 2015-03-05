#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "main.hpp"
#include "../file.hpp"


int main(int argc, char* argv[])
{
	if(argc < 2) {
		std::cout << "imageconvert infile [-alpha]" << std::endl;
		exit(0);
	}
	const std::string inFile = argv[1];
	const std::string mode = (argv[2]) ? argv[2] : "-bg";

	std::vector<uint8_t> rgb = FileToU8vec(inFile);
	std::vector<uint16_t> rgb15;
	if(mode == "-alpha")
	{
		rgb15 = ConvertRgba32ToRgba16(rgb);
	}
	else
	{
		rgb15 = ConvertRgb24ToRgb15(rgb);
	}

	U16vecToFile(rgb15, inFile + ".i15");
	return 0;
}


std::vector<uint16_t> ConvertRgb24ToRgb15(const std::vector<uint8_t> &rgb24)
{
	std::vector<uint16_t> rgb15;
	for(int x=0; x<rgb24.size() / 3; ++x)
	{
		uint8_t red = rgb24[x*3];
		if(red & 4)
		{
			red = (uint8_t(red + 4) >= 4) ? red + 4 : 255;
		}
		red >>= 3;

		uint8_t green = rgb24[x*3+1];
		if(green & 4)
		{
			green = (uint8_t(green + 4) >= 4) ? green + 4 : 255;
		}
		green >>= 3;

		uint8_t blue = rgb24[x*3+2];
		if(blue & 4)
		{
			blue = (uint8_t(blue + 4) >= 4) ? blue + 4 : 255;
		}
		blue >>= 3;

		rgb15.push_back((red << 11) | (green << 6) | (blue << 1) | 1);
	}
	return rgb15;
}


std::vector<uint16_t> ConvertRgba32ToRgba16(const std::vector<uint8_t> &rgba32)
{
	std::vector<uint16_t> rgba16;
	for(int x=0; x<rgba32.size() / 4; ++x)
	{
		uint8_t red = rgba32[x*4];
		if(red & 4)
		{
			red = (uint8_t(red + 4) >= 4) ? red + 4 : 255;
		}
		red >>= 3;

		uint8_t green = rgba32[x*4+1];
		if(green & 4)
		{
			green = (uint8_t(green + 4) >= 4) ? green + 4 : 255;
		}
		green >>= 3;

		uint8_t blue = rgba32[x*4+2];
		if(blue & 4)
		{
			blue = (uint8_t(blue + 4) >= 4) ? blue + 4 : 255;
		}
		blue >>= 3;

		uint8_t alpha = rgba32[x*4+3] & 1;

		rgba16.push_back((red << 11) | (green << 6) | (blue << 1) | alpha);
	}
	return rgba16;
}
