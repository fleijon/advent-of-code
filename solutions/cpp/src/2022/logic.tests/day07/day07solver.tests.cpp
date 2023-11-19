#include "pch.h"
#include "../../logic/day07/day07solver.h"

#include "CppUnitTest.h"
#include <filesystem>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logictests
{
	TEST_CLASS(day07tests)
	{

	public:

		TEST_METHOD(Should_Build_Directory_Tree_From_Test_Input)
		{
			std::string filepath = "../../../../../../../../resources/2022/07/example.1.txt";
			input_format input;

			auto abs = std::filesystem::absolute(filepath);
			auto canLoadInput = LoadInput(filepath, ' ', input);
			Assert::IsTrue(canLoadInput);


			std::shared_ptr<Directory> nullRoot;
			Directory root("root", nullRoot);
			auto root_s = std::make_shared<Directory>(root);

			build_directory_tree(root_s, input);

			Assert::IsTrue(root_s->directories.size() == 2);
		}

		TEST_METHOD(Should_Calculate_Total_Size)
		{
			std::string filepath = "../../../../../../../../resources/2022/07/example.1.txt";
			input_format input;

			auto abs = std::filesystem::absolute(filepath);
			auto canLoadInput = LoadInput(filepath, ' ', input);
			Assert::IsTrue(canLoadInput);

			std::shared_ptr<Directory> nullRoot;
			Directory root("root", nullRoot);
			auto root_s = std::make_shared<Directory>(root);

			build_directory_tree(root_s, input);

			Assert::AreEqual(root_s->TotalSize(), 48381165);
		}
	};
}
