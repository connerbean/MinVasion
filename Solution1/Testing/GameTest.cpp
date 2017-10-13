#include "stdafx.h"
#include "CppUnitTest.h"

#include "Game.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(GameTest)
	{
	public:
		const wstring StuartImageName = L"images/stuart.png";  ///< Stuart filename 
		const wstring MutantImageName = L"images/mutant.png";  ///< Mutant filename 
		const wstring JerryImageName = L"images/jerry.png";  ///< Jerry filename 

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestCGameConstructor)
		{
			CGame game;
		}

		TEST_METHOD(TestCGameIterator)
		{
			// Construct a game object
			CGame game;

			// Add some minions
			auto minion1 = make_shared<CCharacterMinion>(MutantImageName, 5);
			auto minion2 = make_shared<CCharacterMinion>(StuartImageName, 1);
			auto minion3 = make_shared<CCharacterMinion>(JerryImageName, 1);

			game.AddMinion(minion1);
			game.AddMinion(minion2);
			game.AddMinion(minion3);

			// Begin points to the first item
			auto iter1 = game.begin();

			// End points after the last item
			auto iter2 = game.end();

			auto villain1 = *iter1;
			++iter1;
			auto villain2 = *iter1;
			++iter1;
			auto villain3 = *iter1;
			++iter1;
			auto gru = *iter1;
			++iter1;

			Assert::IsTrue(minion1 == *iter1, L"First item correct");
			++iter1;
			Assert::IsTrue(minion2 == *iter1, L"Second item correct");
			++iter1;
			Assert::IsTrue(minion3 == *iter1, L"Third item correct");
			++iter1;
			Assert::IsFalse(iter1 != iter2);
		}

	};
}