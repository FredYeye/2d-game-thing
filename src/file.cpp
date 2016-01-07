#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ostream>
#include <vector>

#include "file.hpp"


const std::vector<uint8_t> FileToU8vec(const std::string inFile)
{
	std::ifstream iFile(inFile.c_str(), std::ios::in | std::ios::ate | std::ios::binary);
	if(iFile.is_open() == false)
	{
		std::cout << "File not found" << std::endl;
		exit(0);
	}

	const uint32_t size = iFile.tellg();
	const std::vector<uint8_t> content(size);
	iFile.seekg(0, std::ios::beg);
	iFile.read((char*)content.data(), size);
	iFile.close();

	return content;
}


void U8vecToFile(const std::vector<uint8_t> &outVec, const std::string outFile)
{
	std::ofstream result(outFile.c_str(), std::ios::out | std::ios::binary);
	result.write((char*)outVec.data(), outVec.size());
	result.close();
	std::cout << "Created " << outFile << std::endl;
}


const std::vector<uint16_t> FileToU16vec(const std::string inFile)
{
	std::ifstream iFile(inFile.c_str(), std::ios::in | std::ios::ate | std::ios::binary);
	if(iFile.is_open() == false)
	{
		std::cout << "File not found" << std::endl;
		exit(0);
	}

	const uint32_t size = iFile.tellg();
	if(size & 1)
	{
		std::cout << "file must contain an even amount of bytes" << std::endl;
		exit(0);
	}
	const std::vector<uint16_t> content(size/2);
	iFile.seekg(0, std::ios::beg);
	iFile.read((char*)content.data(), size);
	iFile.close();

	return content;
}


void U16vecToFile(const std::vector<uint16_t> &outVec, const std::string outFile)
{
	std::ofstream result(outFile.c_str(), std::ios::out | std::ios::binary);
	result.write((char*)outVec.data(), outVec.size() * 2);
	result.close();
	std::cout << "Created " << outFile << std::endl;
}


const std::string FileToString(const std::string inFile)
{
	std::ifstream iFile(inFile.c_str(), std::ios::in | std::ios::binary);
	if(iFile.is_open() == false)
	{
		std::cout << "File not found" << std::endl;
		exit(0);
	}

	// auto ss = std::ostringstream{};
	// ss << iFile.rdbuf();
	// auto s = ss.str();

	// auto s = static_cast<std::ostringstream&>(std::ostringstream{} << iFile.rdbuf()).str();
	// iFile.close();
	// return s;

	std::ostringstream contents;
    contents << iFile.rdbuf();
	iFile.close();
	return contents.str();
}
