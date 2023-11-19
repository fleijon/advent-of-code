#pragma once

#include <vector>
#include <string>

using input_format = std::vector<std::vector<std::string>>;

bool LoadInput(const std::string& filepath, char delimiter, input_format& outputTarget);
