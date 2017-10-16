#include "stdafx.h"
#include "CppUnitTest.h"
#include "Game.h"
#include "CharacterMinion.h"
#include "CharacterVillain.h"
#include<memory>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(MinionHitTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestCCharacterMinionHitTest)
		{
			//Create a game to test
			CGame game;
			const wstring name = L"images/stuart.png";
			CCharacterMinion Minion(&game,name, 1);

			// Give it a location
			// Always make the numbers different, in case they are mixed up
			Minion.SetLocation(300, 300);

			// Center of Minion should be a true
			Assert::IsTrue(Minion.HitTest(300, 300));

			// Left of Minion
			Assert::IsFalse(Minion.HitTest(100, 300));

			// Right of Minion
			Assert::IsFalse(Minion.HitTest(500, 200));

			// Above Minion
			Assert::IsFalse(Minion.HitTest(300, 100));

			// Below Minion
			Assert::IsFalse(Minion.HitTest(300, 500));
		}

		TEST_METHOD(TestCCharacterMinionConstraints)
		{
			CGame game;
			const wstring name = L"images/stuart.png";
			//CCharacterMinion Minion(&game, name, 1);
			shared_ptr<CCharacter>Minion = make_shared<CCharacterMinion>(&game, name, 1);

			Minion->SetLocation(550, 0);

			Minion->Constraints(Minion);

			Assert::IsTrue(Minion->HitTest(500, 0));

			Minion->SetLocation(-550, 0);

			Minion->Constraints(Minion);

			Assert::IsTrue(Minion->HitTest(-500, 0));

			Minion->SetLocation(0, 600);

			Minion->Constraints(Minion);

			Assert::IsTrue(Minion->HitTest(0, 500));

			Minion->SetLocation(0, -600);

			Minion->Constraints(Minion);

			Assert::IsTrue(Minion->HitTest(0, -500));
		}

	};
}