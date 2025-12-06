#pragma once

#include <string>
#include <vector>

// Type alias for input data: a vector of strings, one per line
using input_format = std::vector<std::string>;

/// <summary>
/// Load input file and split by delimiter
/// </summary>
/// <param name="filepath">Path to the input file</param>
/// <param name="delimiter">Delimiter to split lines (can be single char or multi-char string)</param>
/// <param name="output">Output vector containing split strings</param>
/// <returns>true if file was loaded successfully, false otherwise</returns>
bool LoadInput(const std::string& filepath, const std::string& delimiter, input_format& output);

/// <summary>
/// Split a string by delimiter
/// </summary>
/// <param name="text">String to split</param>
/// <param name="delimiter">Delimiter character or string</param>
/// <returns>Vector of split strings</returns>
std::vector<std::string> split(const std::string& text, const std::string& delimiter);

/// <summary>
/// Convert string to unsigned long long
/// </summary>
/// <param name="str">String to convert</param>
/// <returns>Converted value or 0 if conversion fails</returns>
unsigned long long str_to_ull(const std::string& str);

/// <summary>
/// Trim whitespace from both ends of string
/// </summary>
/// <param name="str">String to trim</param>
/// <returns>Trimmed string</returns>
std::string trim(const std::string& str);
