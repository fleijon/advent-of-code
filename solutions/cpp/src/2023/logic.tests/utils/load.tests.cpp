#include "pch.h"

#include "CppUnitTest.h"
#include "./utils/preprocess.h"
#include <variant>
#include <array>
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logictests
{

	TEST_CLASS(utilstests)
	{


	public:

		TEST_METHOD(Should_LoadInput)
		{
			// arrange
			std::error_code errorCode;
			auto tempDir = std::filesystem::temp_directory_path(errorCode);
			std::string name1 = "file_Should_LoadInput.txt";
			std::string tempfile = std::format("{}{}", tempDir.generic_string(), name1);

			std::filesystem::remove(tempfile);
			{
				std::ofstream writeFile(tempfile);
				Assert::IsTrue(writeFile.is_open());

				writeFile << "1 2 3 4 5\n";
				writeFile << "1 2 3 4 5\n";
				writeFile << "1 2 3 4 5\n";
				writeFile << "1 2 3 4 5\n";
				writeFile << "1 2 3 4 5\n";
			}

			const size_t expectedSize = 5;

			input_format fileContent;

			// act
			const auto result = LoadInput(tempfile, ' ', fileContent);

			// assert
			Assert::IsTrue(result);
			size_t actualSize = fileContent.size();
			Assert::AreEqual(expectedSize, actualSize);
		}
	};
}