#pragma once


const std::vector<uint8_t>  FileToU8vec (const std::string inFile);
void                        U8vecToFile (const std::vector<uint8_t> &outVec, const std::string outFile);

const std::vector<uint16_t> FileToU16vec(const std::string inFile);
void                        U16vecToFile(const std::vector<uint16_t> &outVec, const std::string outFile);

const std::string FileToString(const std::string inFile);
