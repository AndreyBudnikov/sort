#include <iostream>
#include <cassert>
#include <vector>
#include <set>
#include <iterator>
#include <chrono>
#include <cstring>

typedef unsigned int uint;
using namespace std;

class HronoTimer
{
private:
	chrono::steady_clock::time_point start;
public:
	HronoTimer(string str)
	{
		start = chrono::high_resolution_clock::now();
		std::cout << endl << "Start timer " << str << endl;
	}
	~HronoTimer()
	{
		std::cout << "Time Elapsed " << chrono::duration<double>(chrono::high_resolution_clock::now() - start).count() << endl;
	}
};


template <class T>
class Intuha
{
private:
	T* data;
	uint len = 0, loc_count;
	static uint count;

	//Intuha(Intuha& T);
public:
	explicit Intuha(const T& data = 0)
	{
		loc_count = count;
		count++;
		
		init(data);
		//cout << "Create Data " << loc_count << " [" << this->data << "] " << " = ";
		printData(data);
	}

	explicit Intuha(Intuha<T>&& obj) noexcept
	{
		this->loc_count = obj.count;
		this->data = move(obj.data);
		obj.data = nullptr;
		//cout << "Create Data & " << loc_count << " [" << this->data << "] " << " = ";
		printData(*(this->data));
	}

	~Intuha()
	{
		//cout << "Delete Data " << loc_count << " [" << this->data << "] " << endl;
		delete data;
	}

	typename enable_if<is_same<T, uint>::value || is_same<T, int>::value, T>::type
	init(T data)
	{
		this->data = new T(data);
		this->len = 1;
		return 0;
	}

	Intuha<T>& operator= (const Intuha<T>& obj)
	{
		*(this->data) = *(obj.data);
		//cout << "Change Data & " << loc_count << " = " << *(this->data) << endl;
		return *this;
	}

	Intuha<T>& operator= (Intuha<T>* obj)
	{
		*(this->data) = *(obj.data);
		//cout << "Change Data & " << loc_count << " = " << *(this->data) << endl;
		return *this;
	}

	Intuha<T>& operator= (T data)
	{
		*(this->data) = data;
		//cout << "Change Data = " << loc_count << " = " << data << endl;
		return *this;
	}

	bool operator< (const Intuha& obj) const
	{
		if (*(this->data) < (*obj.data)) { return true; }
		return false;
	}

	bool operator> (const Intuha& obj) const
	{
		return !(operator<(*obj.data));
	}

	bool operator<= (const Intuha& obj) const
	{
		if (*(this->data) <= (*obj.data)) { return true; }
		return false;
	}

	uint printData(const T& data)
	{
		//cout << data << endl;
		return 0;
	}

	inline uint GetCount() { return count; }
	inline T GetValue() const { return *(this->data); }

	friend uint MyQuickSort(Intuha<uint>* obj, int start, int len);
 };
template<class T>
uint Intuha<T>::count = 0;

uint SortBubble(Intuha<uint>* obj, uint len)
{
	uint count_step = 0;
	Intuha<uint> tmp(0);
	for (uint i = 0; i < (len - 1); i++)
	{
		for (uint j = 0; j < (len - i - 1); j++)
		{
			count_step++;
			if (obj[j + 1] < obj[j])
			{
				tmp = std::move(obj[j]);
				obj[j] = std::move(obj[j + 1]);
				obj[j + 1] = std::move(tmp);
			}
		}
	}
	std::cout << "Step = " << count_step << endl;
	return 0;
}

uint SortShake(Intuha<uint>* obj, uint len)
{
	uint count_step = 0;
	Intuha<uint> tmp(0);

	int start, pos, step;
	for (uint i = 0; i < (len - 1); i++)
	{

		pos = static_cast<uint>((i + 1) / 2);
		step = 1;
		
		if(!((i + 1)%2)) 
		{
			pos = (len - pos - 2);
			step = -1;
		}

		for (uint j = 0; j < (len - i - 1); j++)
		{
			count_step++;
			if (obj[pos + 1] < obj[pos])
			{
				tmp = std::move(obj[pos]);
				obj[pos] = std::move(obj[pos + 1]);
				obj[pos + 1] = std::move(tmp);
			}
			pos += step;
		}
	}
	std::cout << "Step = " << count_step << endl;
	return 0;
}

uint MyQuickSort(Intuha<uint>* obj, int start, int stop)
{
	assert(stop >= start);
	uint shift = start;// (start + stop + 1) / 2;// (rand() % (stop - start) + start);
	Intuha<uint> val (obj[shift].GetValue()), tmp (0);

	int count_arr_left = start + 1;
	int count_arr_right = stop;
	bool was_change = false;

	do
	{
		while (obj[count_arr_left] <= val)
		{
			if (count_arr_left < stop) { count_arr_left++; }
			else { break; }
		}
		while (val < obj[count_arr_right])
		{
			if (count_arr_right > start) { count_arr_right--; }
			else { break; }
		}

		if (count_arr_left < count_arr_right)
		{
			was_change = true;
			tmp = obj[count_arr_left];
			obj[count_arr_left] = obj[count_arr_right];
			obj[count_arr_right] = tmp;
		}
	} while (count_arr_left < count_arr_right);

	tmp = obj[count_arr_right];
	obj[count_arr_right] = obj[start];
	obj[start] = tmp;

	//if (!was_change) { return 0; }

	if (start < (count_arr_right - 1)) { MyQuickSort(obj, start, count_arr_right - 1); }
	if ((count_arr_right + 1) < stop) { MyQuickSort(obj, count_arr_right + 1, stop); }

	return 0;
}


uint Binary(multiset<Intuha<uint>>& obj, uint start, uint stop)
{
	cout << "Enter Bin" << endl;
	decltype(auto) iter = obj.cbegin();
	Intuha<uint> tmp;
	tmp = *iter;

	cout << "Enter cycle" << endl;
	//while (tmp != obj.cend())
	//{
	//	iter = obj.upper_bound(tmp);
	//	cout << "val" << (*iter).GetValue() << endl;
	//	
	//}

	 return (*iter).GetValue();
}

uint Valid_Sort(Intuha<uint>* obj, uint len)
{
		uint test_val = obj[0].GetValue();
	for (uint i = 0; i < len; i++)
	{
		if (test_val > obj[i].GetValue())
		{
			std::cout << "SORT FALSE" << endl;
			break;
		}
		test_val = obj[i].GetValue();
		if (i == (len - 1)) { std::cout << "SORT TRUE" << endl; }
	}
	return 0;
}

uint copyArr(const Intuha<uint>* obj, Intuha<uint>* target, uint len)
{
	for (uint i = 0; i < len; i++)
	{
		target[i] = obj[i];
	}
	return 0;
}


void main()
{
	const uint len = 100000;
	auto s1 = make_unique<Intuha<uint>[]>(len);
	auto s2 = make_unique<Intuha<uint>[]>(len);

	//int test[] = { 6, 0, 1, 1, 6, 5, 7, 2, 3, 8, 0, 17, 4, 6 };
	//srand(unsigned(time(0)));

	std::cout << "Create array" << endl;
	for (uint i = 0; i < len; i++)
	{
		//s1[i] = test[i];
		s1[i] = (rand() % 1000);
	}

	copyArr(s1.get(), s2.get(), len);
	{
		HronoTimer hTimer1("Bubbles");
	 	//SortBubble(s1.get(), len);
	}
	Valid_Sort(s2.get(), len);

	copyArr(s1.get(), s2.get(), len);
	{
		HronoTimer hTimer1("Shake");
		//SortShake(s2.get(), len);
	}
	Valid_Sort(s2.get(), len);

	copyArr(s1.get(), s2.get(), len);
	multiset<Intuha<uint>> tree;
	//for (uint i = 0; i < len; i++)
	{
	//	tree.insert(Intuha<uint>(s1[i].GetValue()));
	}

	{
		//HronoTimer hTimer1("Binary");
		//cout << Binary(tree, 0, len - 1) << endl;
	}

	copyArr(s1.get(), s2.get(), len);
	{

		for (uint i = 0; i < 1; i++)
		{
			HronoTimer hTimer1("QuickSort");
			uint br = MyQuickSort(s2.get(), 0, len - 1);
		}
	}
	Valid_Sort(s2.get(), len);
		
}