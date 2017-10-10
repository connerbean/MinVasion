#include "stdafx.h"
#include "CppUnitTest.h"

#include "Game.h"
#include "Villain.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CVillainTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestConstructor)
		{
			CGame game;
			CVillain arya(&game, CVillain::Types::Arya);
			CVillain juicer(&game, CVillain::Types::Juicer);
			CVillain pokeball(&game, CVillain::Types::Pokeball);
		}

		TEST_METHOD(TestHitTest)
		{
			CGame game;
			CVillain arya(&game, CVillain::Types::Arya);
			CVillain juicer(&game, CVillain::Types::Juicer);
			CVillain pokeball(&game, CVillain::Types::Pokeball);

			arya.SetLocation(0, -250);
			Assert::IsTrue(arya.HitTest(0, -250), L"Arya center image Hit Test");
			// Just off chin (about 5 pixels to the right would be a hit)
			Assert::IsFalse(arya.HitTest(-32, -197), L"Arya near chin Hit Test");

			juicer.SetLocation(-250, -250);
			Assert::IsTrue(juicer.HitTest(-250, -250), L"Juicer center image Hit Test");
			// Just off handle (about 5 pixels above would be a hit)
			Assert::IsFalse(juicer.HitTest(-270, -250), L"Juicer near handle Hit Test");

			pokeball.SetLocation(250, -250);
			Assert::IsTrue(pokeball.HitTest(250, -250), L"Pokeball center image Hit Test");
			// Just off bottom left of ball (about 2 pixels above or to the right would be a hit)
			Assert::IsFalse(pokeball.HitTest(231, -231), L"Pokeball near bottom left Hit Test");
		}

	};
}