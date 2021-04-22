#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include "../11.1/11.1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			ofstream f("test", ios::binary);
			for (int i = 1; i <= 5; i++) {
				f.write((char*)&i, sizeof(i));
			}
			f.close();

			ProcessBIN("test", "outodd", "outeven");
			ifstream file("outodd", ios::binary);
			int x;
			file.read((char*)&x, sizeof(x));
			Assert::AreEqual(1, x);
			file.read((char*)&x, sizeof(x));
			Assert::AreEqual(3, x);
			file.read((char*)&x, sizeof(x));
			Assert::AreEqual(5, x);


		}
	};
}
