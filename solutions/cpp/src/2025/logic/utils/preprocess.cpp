#include "preprocess.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>

bool LoadInput(const std::string &filepath, const std::string &delimiter,
               input_format &output) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filepath << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (delimiter == "\n" || delimiter.empty()) {
      output.push_back(line);
    } else {
      auto parts = split(line, delimiter);
      for (const auto &part : parts) {
        output.push_back(part);
      }
    }
  }

  file.close();
  return true;
}

std::vector<std::string> split(const std::string &text,
                               const std::string &delimiter) {
  std::vector<std::string> result;
  size_t start = 0;
  size_t end = text.find(delimiter);

  while (end != std::string::npos) {
    std::string token = text.substr(start, end - start);
    if (!token.empty()) {
      result.push_back(trim(token));
    }
    start = end + delimiter.length();
    end = text.find(delimiter, start);
  }

  std::string token = text.substr(start);
  if (!token.empty()) {
    result.push_back(trim(token));
  }

  return result;
}

unsigned long long str_to_ull(const std::string &str) {
  try {
    return std::stoull(str);
  } catch (const std::exception &) {
    return 0;
  }
}

std::string trim(const std::string &str) {
  auto start = str.begin();
  while (start != str.end() && std::isspace(*start)) {
    start++;
  }

  auto end = str.end();
  do {
    end--;
  } while (std::distance(start, end) > 0 && std::isspace(*end));

  return std::string(start, end + 1);
}
