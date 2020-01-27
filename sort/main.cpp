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

uint cout_m(Intuha<int>& obj)
{
	cout << "Result = [ " << obj.data << " ][ " << obj.loc_count << " ] = " << *obj.data << endl << endl;
	return 0;
}

int main()
{
	//Intuha<int> tmp0 { static_cast<Intuha<int>>(7) };
	//cout_m(tmp0);

	//Intuha<int> tmp1;
	//cout_m(tmp1);

	//Intuha<int> tmp2(1);
	//cout_m(tmp2);

	//Intuha<int> tmp3{ tmp2 };
	//cout_m(tmp3);

	//Intuha<int> tmp4;
	//tmp4 = tmp2;
	//cout_m(tmp4);

	//Intuha<int> tmp5(5);
	//tmp5 = std::move(tmp0);
	//cout_m(tmp5);

	//Intuha<int> tmp6(Intuha<int>(6));
	//cout_m(tmp6);

	//return 0;


	const uint len = 1000; // int len(10)

	auto s1 = make_unique<Intuha<float>[]>(len);
	auto s2 = make_unique<Intuha<float>[]>(len);

	//Intuha<int>* s1 = new Intuha<int>[len];
	//Intuha<int>* s2 = new Intuha<int>[len];

	//int test[] = { 6, 0, 1, 1, 6, 5, 7, 2, 3, 8, 0, 17, 4, 6 };
	srand(unsigned(time(0)));

	std::cout << "Create array" << endl;
	for (uint i = 0; i < len; i++)
	{
		//s1[i] = test[i];
		s1[i] = static_cast<float>((rand() % 10000) - 4000) / 100;
	}

	//copyArr(s1.get(), s2.get(), len);
	//{
	//	HronoTimer hTimer1("Bubbles");
		//MySort::SortBubble(s2.get(), len);
	//}
	//Valid_Sort(s2.get(), len);
	
	//copyArr(s1.get(), s2.get(), len);
	//{
	//	HronoTimer hTimer1("Shake");
	//	//MySort::SortShake(s2.get(), len);
	//}
	//Valid_Sort(s2.get(), len);

	copyArr(s1.get(), s2.get(), len);
	{
		HronoTimer hTimer1("Heap");
		MySort::myHeapSort(s2.get(), len);
	}
	Valid_Sort(s2.get(), len);

	copyArr(s1.get(), s2.get(), len);
	{
		HronoTimer hTimer1("SortCalc");	
		MySort::SortCalc(s2.get(), 0, len);
	}
	Valid_Sort(s2.get(), len);

	copyArr(s1.get(), s2.get(), len);
	{
		HronoTimer hTimer1("QuickSort");
		MySort::MyQuickSort(s2.get(), 0, len - 1);
	}
	Valid_Sort(s2.get(), len);

	copyArr(s1.get(), s2.get(), len);
	{
		HronoTimer hTimer1("MergeSort");
		MySort::MergeSort(s2.get(), 0, len - 1);
	}
	Valid_Sort(s2.get(), len);


}
