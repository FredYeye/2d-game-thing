#pragma once

#include <vector>

//use pointers to different entities? in sprite drawing for example

const std::vector<std::vector<SpriteRect>> spriteRectList
{
	{ //player
		{0,0,48,80}, {48,0,48,80}, {96,0,48,80}, {144,0,48,80}
	},
	{ //thing
		{0,0,32,32}
	}
};

const std::vector<std::vector<std::vector<uint8_t>>> frameList
{
	{ //player
		{}, {20,20,20}
	},
	{ //thing
		{}
	}
};

const std::vector<std::vector<std::vector<uint8_t>>> animationList
{
	{ //player
		{0}, {1,2,3}
	},
	{ //thing
		{0}
	}
};

const std::vector<uint16_t> sheetWidth
{
	192, 32
};
