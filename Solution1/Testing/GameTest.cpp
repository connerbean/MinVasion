#include "stdafx.h"
#include "CppUnitTest.h"

#include "Game.h"
#include "CharacterMinion.h"

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

			// Begin points to the first item
			auto iter1 = game.begin();

			// End points after the last item
			auto iter2 = game.end();

			// There should be 4 items iterated by default - Gru and 3 villains
			Assert::IsTrue(iter1 != iter2);
			++iter1;
			Assert::IsTrue(iter1 != iter2);
			++iter1;
			Assert::IsTrue(iter1 != iter2);
			++iter1;
			Assert::IsTrue(iter1 != iter2);
			++iter1;
			Assert::IsFalse(iter1 != iter2);

			// Add some minions
			auto minion1 = make_shared<CCharacterMinion>(&game, MutantImageName, 5, 0);
			auto minion2 = make_shared<CCharacterMinion>(&game, StuartImageName, 1, 0);
			auto minion3 = make_shared<CCharacterMinion>(&game, JerryImageName, 1, 0);

			game.Add(minion1);
			game.Add(minion2);
			game.Add(minion3);

			iter1 = game.begin();
			iter2 = game.end();

			// Skip the 4 auto-added characters
			++iter1;
			++iter1;
			++iter1;
			++iter1;

			Assert::IsTrue(minion1 == *iter1, L"First minion correct");
			++iter1;
			Assert::IsTrue(minion2 == *iter1, L"Second minion correct");
			++iter1;
			Assert::IsTrue(minion3 == *iter1, L"Third minion correct");
			++iter1;
			Assert::IsFalse(iter1 != iter2);
		}

		TEST_METHOD(TestCGameMinionSpawn)
		{
			CGame game;

			// update the game one second
			game.Update(1);

			// check to see we have items now, 5 in total for 3 villains, gru, and one min
			Assert::IsTrue(game.GetItemsSize() == 5);

			game.Reset(); // nuke the game, check to make sure we got rid of minions
			Assert::IsTrue(game.GetItemsSize() == 4);
		}

	};
}