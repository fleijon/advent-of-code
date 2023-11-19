#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../utils/load.h"

struct File {
	std::string name{};
	int size{0};
};

struct Directory {
	std::string dirName{};
	std::weak_ptr<Directory> parent;
	std::vector<std::shared_ptr<Directory>> directories{};
	std::vector<File> files{};

	Directory() {}
	Directory(const std::string& dirName, std::weak_ptr<Directory> parent) : dirName{ dirName }, parent{ parent } {}

	bool isRoot() const;
	void AddFileIfNotExists(const std::string& name, int size);
	int TotalSize() const;
};

void AddDirIfNotExists(std::weak_ptr<Directory> parent, const std::string& name);
int calculate_total_size_with_max(std::shared_ptr<Directory> parent, int max);
void build_directory_tree(std::shared_ptr<Directory> root, const input_format& input);
int free_space(const std::shared_ptr<Directory>& parent, int totalDiskSpace, int requiredSpace);
