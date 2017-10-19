#include "stdafx.h"
#include "CppUnitTest.h"
#include "Game.h"
#include "CharacterGru.h"
#include "Game.h"
#include "Clock.h"
#include "RestartSide.h"
#include<memory>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(GruHitTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCCharacterGruHitTest)
		{
			//Create a game to test
			CGame game;
			CCharacterGru Gru(&game);

			// Give it a location
			// Always make the numbers different, in case they are mixed up
			Gru.SetLocation(100, 200);

			// Center of Gru should be a true
			Assert::IsTrue(Gru.HitTest(100, 200));

			// Left of Gru
			Assert::IsFalse(Gru.HitTest(10, 200));

			// Right of Gru
			Assert::IsFalse(Gru.HitTest(200, 200));

			// Above Gru
			Assert::IsFalse(Gru.HitTest(100, 0));

			// Below Gru
			Assert::IsFalse(Gru.HitTest(100, 300));
		}

		TEST_METHOD(TestCCharacterGruConstraints)
		{
			CGame game;
			shared_ptr<CCharacter>Gru = make_shared<CCharacterGru>(&game);
			const wstring GruImageName = L"images/gru.png";
			auto GruImage = unique_ptr<Bitmap>(Bitmap::FromFile(GruImageName.c_str()));
			const int height = GruImage->GetHeight() / 2;
			const int width = GruImage->GetWidth() / 2;

		
			Assert::IsTrue(Gru != nullptr);

			Gru->SetLocation(560, 0);

			Gru->Constraints();

			Assert::IsTrue(Gru->HitTest(500 - width, 0));

			Gru->SetLocation(-560, 0);

			Gru->Constraints();

			Assert::IsTrue(Gru->HitTest(-500 + width, 0));

			Gru->SetLocation(0, 600);

			Gru->Constraints();

			Assert::IsTrue(Gru->HitTest(0, 500 - height));

			Gru->SetLocation(0, -600);

			Gru->Constraints();

			Assert::IsTrue(Gru->HitTest(0, -500 + height));
		}

	};
}