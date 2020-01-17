#include <cassert>
#include <iostream>
#include <time.h>

#include "sort.h"
#include "myChrono.h"

typedef unsigned int uint;
using namespace std;

template<class T>
uint Valid_Sort(Intuha<T>* obj, uint len)
{
	try {
		T test_val = obj[0].GetValue();
		for (uint i = 0; i < len; i++)
		{
			//cout << obj[i].GetValue() << endl;
			if (test_val > obj[i].GetValue())
			{
				std::cout << "SORT FALSE" << endl;
				break;
			}
			test_val = obj[i].GetValue();
			if (i == (len - 1)) { std::cout << "SORT TRUE" << endl; }
		}
	}
	catch (...)
	{
		cout << "Procces validation false" << endl;
		exit(1);
	}
	return 0;
}

template<class T>
uint copyArr(const Intuha<T>* obj, Intuha<T>* target, uint len)
{
	for (uint i = 0; i < len; i++)
	{
		target[i] = obj[i];
	}
	return 0;
}

int main()
{
	const uint len = 500;

	auto s1 = make_unique<Intuha<int>[]>(len);
	auto s2 = make_unique<Intuha<int>[]>(len);

	//int test[] = { 6, 0, 1, 1, 6, 5, 7, 2, 3, 8, 0, 17, 4, 6 };
	srand(unsigned(time(0)));

	std::cout << "Create array" << endl;
	for (uint i = 0; i < len; i++)
	{
		//s1[i] = test[i];
		s1[i] = static_cast<int>(rand() % 10000);// / MAX_SIGN;
	}

	copyArr(s1.get(), s2.get(), len);
	//copyArr(s1, s2, len);
	{
		HronoTimer hTimer1("Bubbles");
		//MySort::SortBubble(s2.get(), len);
	}
	Valid_Sort(s2.get(), len);
	//Valid_Sort(s2, len);

	//copyArr(s1.get(), s2.get(), len);
	//{
	//	HronoTimer hTimer1("Shake");
	//	//MySort::SortShake(s2.get(), len);
	//}
	//Valid_Sort(s2.get(), len);

	//copyArr(s1.get(), s2.get(), len);
	//{
	//	HronoTimer hTimer1("SortCalc");
	//	MySort::SortCalc(s2.get(), 0, len);
	//}
	//Valid_Sort(s2.get(), len);

	//copyArr(s1.get(), s2.get(), len);
	//{
	//	HronoTimer hTimer1("QuickSort");
	//	MySort::MyQuickSort(s2.get(), 0, len - 1);
	//}
	//Valid_Sort(s2.get(), len);

	//copyArr(s1.get(), s2.get(), len);
	//{
	//	HronoTimer hTimer1("MergeSort");
	//	MySort::MergeSort(s2.get(), 0, len - 1);
	//}
	//Valid_Sort(s2.get(), len);


}
