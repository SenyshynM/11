#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include "../11.2/11.2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			ofstream f("test", ios::binary);
			Student student;
			student.fiz = 5;
			student.mat = 5;
			student.spec = KN;
			student.prog = 5;
			f.write((char*)&student, sizeof(Student));

			student.fiz = 4;
			student.mat = 4;
			student.spec = KN;
			student.prog = 5;
			f.write((char*)&student, sizeof(Student));
			
			student.fiz = 5;
			student.mat = 5;
			student.spec = KN;
			student.prog = 5;
			f.write((char*)&student, sizeof(Student));

			f.close();

			ifstream file("test", ios::binary);

			int x = SearchGood("test");
			double y = SearchPercent("test");

			Assert::AreEqual(2, x);
			Assert::AreEqual(66.6, y, 0.1);
			f.close();
		}
	};
}
