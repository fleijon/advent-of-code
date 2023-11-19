#include "pch.h"

#include <string>
#include <vector>
#include "../utils/load.h"
#include <algorithm>
#include "day07solver.h"
#include <cctype>

int Directory::TotalSize() const {
	int tot = 0;
	std::ranges::for_each(this->files.cbegin(), this->files.cend(), [&tot](const File& file) { tot += file.size;});
	std::ranges::for_each(this->directories.cbegin(), this->directories.cend(), [&tot](const auto& dir) {tot += dir.get()->TotalSize();});

	return tot;
}

bool Directory::isRoot() const {
	return this->parent.lock().get() == this;
}

void AddDirIfNotExists(std::weak_ptr<Directory> parent, const std::string& name) {
	if (std::ranges::any_of(parent.lock().get()->directories.begin(), parent.lock().get()->directories.end(), [&name](const auto& dir) {return dir.get()->dirName == name;})) {
		return;
	}
	
	auto subDir = std::make_shared<Directory>(name, parent);
	parent.lock().get()->directories.push_back(subDir);
}

void Directory::AddFileIfNotExists(const std::string& name, int size)
{
	if (std::ranges::any_of(files.begin(), files.end(), [&name](const File& file) { return file.name == name;}))
		return;

	files.emplace_back(name, size);
}	

int calculate_total_size_with_max(std::shared_ptr<Directory> parent, int max)
{
	int tot = 0;
	if (parent->TotalSize() <= max)
	{
		tot += parent->TotalSize();
	}
	for (const auto &child: parent->directories) {
		tot += calculate_total_size_with_max(child, max);
	}

	return tot;
}

int find_smallest_space_with_min_space(const std::shared_ptr<Directory>& parent, int space);

int free_space(const std::shared_ptr<Directory>& parent, int totalDiskSpace , int requiredSpace) {

	const int usedDiskSpace = parent->TotalSize();
	const int freeDiskSpace = totalDiskSpace - usedDiskSpace;
	const int diskSpaceToFree = requiredSpace - freeDiskSpace;

	if (diskSpaceToFree < 0)
		return 0;

	return find_smallest_space_with_min_space(parent, diskSpaceToFree);
}

int find_smallest_space_with_min_space(const std::shared_ptr<Directory>& parent, int space) {
	int smallest = 0;
	if (int size = parent->TotalSize(); size > space)
	{
		smallest = size;
	}

	for (const auto& child: parent->directories) {
		int child_smallest = find_smallest_space_with_min_space(child, space);
 
		if (child_smallest < smallest && child_smallest > space)
		{
			smallest = child_smallest;
		}
	}

	return smallest;
}

bool is_number(const std::string_view s)
{
    auto it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void build_directory_tree(std::shared_ptr<Directory> root, const input_format& input) {
	std::weak_ptr current = root;

	for (const std::vector<std::string>& line: input) {
		if (line.empty())
			continue;

		if (line[0] == "$")
		{
			if (line.size() == 3 && line[1] == "cd") {

				if (line[2] == "/") {
					current = root;
				}
				else if (line[2] == "..") {
					current = current.lock().get()->parent;
				}
				else {
					auto maybeDir = std::ranges::find_if(
						current.lock().get()->directories.cbegin(),
						current.lock().get()->directories.cend(),
						[&line](const auto& dir) { return dir.get()->dirName == line[2];});
					if (maybeDir != current.lock().get()->directories.cend())
					{
						current = *maybeDir;
					}
				}
			}
			else if (line.size() == 2 && line[1] == "ls")
			{
				continue;
			}
		}
		else
		{
			if (line.size() == 2 && line[0] == "dir")
			{
				AddDirIfNotExists(current, line[1]);
			}
			else if (line.size() == 2 && is_number(line[0]))
			{
				int filesize = std::stoi(line[0]);

				current.lock().get()->AddFileIfNotExists(line[1], filesize);
			}

		}
	}
}
