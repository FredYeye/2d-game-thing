#pragma once

std::vector<uint16_t> ConvertRgb24ToRgb15(const std::vector<uint8_t> &rgb24);
std::vector<uint16_t> ConvertRgba32ToRgba16(const std::vector<uint8_t> &rgba32);