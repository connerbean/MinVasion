#include "stdafx.h"
#include "CppUnitTest.h"
#include "Game.h"
#include "RestartSide.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(StartButtonHitTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestRestartButtonHitTest)
		{
			//Create a game to test
			CGame game;
			CRestartSide Restart(&game);

			// Give it a location
			// Always make the numbers different, in case they are mixed up
			Restart.SetLocation(100, 200);

			// Center of the button should be a true
			Assert::IsTrue(Restart.HitTest(100, 200));

			// Left of the button
			Assert::IsFalse(Restart.HitTest(-100, 200));

			// Right of the button
			Assert::IsFalse(Restart.HitTest(500, 200));

			// Above the button
			Assert::IsFalse(Restart.HitTest(100, -200));

			// Below the button
			Assert::IsFalse(Restart.HitTest(100, 500));
		}

	};
}