#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_10.1.B/lab_10.1.B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest101B
{
	TEST_CLASS(UnitTest101B)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(calc_n(10000), 5);
		}
	};
}
