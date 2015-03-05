#include <iostream>
#include <vector>

#include "rectangleconvert.hpp"
#include "../file.hpp"
#include "../render.hpp"

int main(int argc, char* argv[])
{
	if(argc < 2) {
		std::cout << "rectangleconvert infile" << std::endl;
		exit(0);
	}
	const std::string inFile = argv[1];

	std::string rectString = FileToString(inFile);

	std::vector<SpriteRect> spriteList;
	SpriteRect spriteRect;

	std::string::size_type pos = rectString.find("<", 0);
	while(pos != std::string::npos)
	{
		++pos;
		std::string::size_type end = rectString.find(">", pos);
		std::string rectList = rectString.substr(pos, end-pos);

		std::string::size_type pos2 = 0;
		while(pos2 != std::string::npos)
		{
			spriteList.push_back(spriteRect);
			std::string::size_type end2;
			for(uint8_t x = 0; x < 3; ++x)
			{
				end2 = rectList.find(",", pos2);
				std::string val = rectList.substr(pos2, end2-pos2);
				pos2 = end2 + 1;

				switch(x)
				{
					case 0:
						spriteList.back().x = uint16_t(std::stoi(val));
						break;
					case 1:
						spriteList.back().y = uint16_t(std::stoi(val));
						break;
					case 2:
						spriteList.back().w = uint8_t(std::stoi(val));
						break;
				}
			}

			end2 = rectList.find("|", pos2);
			if(end2 == std::string::npos)
			{
				end2 = rectList.size() + 1;
			}
			std::string val = rectList.substr(pos2, end2-pos2);

			spriteList.back().h = uint8_t(std::stoi(val));

			if(end2 == rectList.size() + 1)
			{
				spriteList.push_back(spriteRect);
				spriteList.back().x = 0xFFFF;
				spriteList.back().y = 0xFFFF;
				spriteList.back().w = 0xFF;
				spriteList.back().h = 0xFF;
			}

			pos2 = rectList.find("|", end2);
			if(pos2 != std::string::npos)
			{
				++pos2;
			}
		}

		pos = rectString.find("<", end);
	}

	std::vector<uint8_t> spritePrint;
	for(auto &v : spriteList)
	{
		spritePrint.push_back(uint8_t(v.x));
		spritePrint.push_back(v.x >> 8);
		spritePrint.push_back(uint8_t(v.y));
		spritePrint.push_back(v.y >> 8);
		spritePrint.push_back(v.w);
		spritePrint.push_back(v.h);
	}
	U8vecToFile(spritePrint, "spriteRects");

	return 0;
}
