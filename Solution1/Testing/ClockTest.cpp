#include "stdafx.h"
#include "CppUnitTest.h"
#include "Clock.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(ClockTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestClockInitializationUpdate)
		{
			// Test initialization
			CClock clock;

			// now test update
			clock.Update(2.0f, NULL);
			// assert time updates correctly
			Assert::IsTrue(clock.GetTimePassed() == 2.0);
			
		
			// now test clear
			clock.Reset();
			Assert::IsTrue(clock.GetTimePassed() == 0);
		}

	};
}