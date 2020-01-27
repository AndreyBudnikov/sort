#include "pch.h"
#include "CppUnitTest.h"
#include "../sort/sort.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSort
{
	TEST_CLASS(UnitTestSort)
	{
	private:

		template<class T>
		struct testVal
		{
			const uint len = 517;
			bool copy_test = false;
			Intuha<T>* ptr;
			testVal()
			{
				ptr = new Intuha<T>[len];
			}
			~testVal()
			{
				delete[] ptr;
			}
		};
		testVal<float> s;

	public:

		template<class T>
		uint init(uint len)
		{
			for (uint i = 0; i < s.len; i++) 
			{ 
				s.ptr[i] = static_cast<T>(((rand() % 9000) - 6000) / 100); 
			}
			s.copy_test = true;
			return 0;
		}

		template<class T>
		bool Valid_Sort(Intuha<T>* obj, uint len)
		{
			bool test = false;
			try 
			{
				T test_val = obj[0].GetValue();
				for (uint i = 0; i < s.len; i++)
				{
					if (test_val > obj[i].GetValue())
					{
						std::cout << "SORT FALSE" << endl;
						break;
					}
					test_val = obj[i].GetValue();
					if (i == (s.len - 1)) { test = true; }
				}
			}
			catch (...)
			{
				cout << "Procces validation false" << endl;
				exit(1);
			}
			return test;
		}

		// --- SortBubble
		TEST_METHOD_INITIALIZE(TestSortBubbleInit)
		{
			init<float>(s.len);
		}

		TEST_METHOD(TestSortBubble)
		{
			Assert::AreEqual(s.copy_test, true);
			MySort::SortBubble(s.ptr, s.len);
			Assert::AreEqual(Valid_Sort(s.ptr, s.len), true);
			s.copy_test = false;
		}

		// --- SortShake
		TEST_METHOD(TestSortShake)
		{
			Assert::AreEqual(s.copy_test, true);
			MySort::SortShake(s.ptr, s.len);
			Assert::AreEqual(Valid_Sort(s.ptr, s.len), true);
			s.copy_test = false;
		}

		// --- MyQuickSort
		TEST_METHOD(TestMyQuickSort)
		{
			Assert::AreEqual(s.copy_test, true);
			MySort::MyQuickSort(s.ptr, 0, s.len - 1);
			Assert::AreEqual(Valid_Sort(s.ptr, s.len), true);
			s.copy_test = false;
		}

		// --- SortCalc
		TEST_METHOD(TestSortCalc)
		{
			Assert::AreEqual(s.copy_test, true);
			MySort::SortCalc(s.ptr, 0, s.len);
			Assert::AreEqual(Valid_Sort(s.ptr, s.len), true);
			s.copy_test = false;
		}

		TEST_METHOD(TestHeapSort)
		{
			Assert::AreEqual(s.copy_test, true);
			MySort::myHeapSort(s.ptr, s.len);
			Assert::AreEqual(Valid_Sort(s.ptr, s.len), true);
			s.copy_test = false;
		}
	};
}
