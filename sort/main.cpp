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
		std::cout << endl << "START - " << str << endl;
	}
	~HronoTimer()
	{
		std::cout << "STOP - Time Elapsed " << chrono::duration<double>(chrono::high_resolution_clock::now() - start).count() << endl;
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

	typename enable_if<is_same<T, uint>::value || is_same<T, int>::value || is_same<T, float>::value, T>::type
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

template<class T>
uint SortBubble(Intuha<T>* obj, uint len)
{
	uint count_step = 0;
	Intuha<T> tmp(0);
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

template<class T>
uint SortShake(Intuha<T>* obj, uint len)
{
	uint count_step = 0;
	Intuha<T> tmp(0);

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

template<class T>
uint MyQuickSort(Intuha<T>* obj, int start, int stop)
{
	assert(stop >= start);
	uint shift = static_cast<uint>((start + stop) / 2);
	Intuha<T> val (obj[shift].GetValue()), tmp (0);

	tmp = obj[start];
	obj[start] = obj[shift];
	obj[shift] = tmp;

	int count_arr_left = start + 1;
	int count_arr_right = stop;
	do
	{
		while ((obj[count_arr_left] <= val) && (count_arr_left++ < stop));
		while ((val < obj[count_arr_right]) && (count_arr_right-- > start));

		if (count_arr_left < count_arr_right)
		{
			tmp = obj[count_arr_left];
			obj[count_arr_left] = obj[count_arr_right];
			obj[count_arr_right] = tmp;
		}
	} while (count_arr_left < count_arr_right);

	tmp = obj[count_arr_right];
	obj[count_arr_right] = obj[start];
	obj[start] = tmp;

	if (start < (count_arr_right - 1)) { MyQuickSort(obj, start, count_arr_right - 1); }
	if ((count_arr_right + 1) < stop) { MyQuickSort(obj, count_arr_right + 1, stop); }

	return 0;
}

const uint MAX_SIGN = 10000;
inline uint Prepare(float data) { return MAX_SIGN; }
inline uint Prepare(int data)   { return 1; }

template<class T>
uint SortCalc(Intuha<T>* obj, int start, int len)
{
	assert(len > 0);
	const uint factor = Prepare(static_cast<T>(0));

	int tmp;
	int max = static_cast<T>(obj[start].GetValue() * factor);
	int min = max;
	for (uint i = 1; i < len; i++)
	{
		tmp = obj[start + i].GetValue() * factor;
		if (max < tmp) { max = tmp; }
		if (tmp < min) { min = tmp; }
	}
	max += abs(min);
	auto ptr = make_unique<uint[]>(++max);
	for (int i = 0; i < max; i++) { ptr[i] = static_cast<uint>(0); }
	for (int i = 0; i < len; i++) { ptr[static_cast<uint>(obj[start + i].GetValue() * factor) + abs(min)]++; }

	uint count = start;
	for (int i = 0; i < max; i++)
	{
		for (uint j = 0; j < ptr[i]; j++)
		{
			obj[count++] = static_cast<T>(i - min) / factor;
		}
	}
	return 0;
}


uint Binary(multiset<Intuha<uint>>& obj, uint start, uint stop)
{
	return 0;
}

template<class T>
uint Merge(Intuha<T>* obj, uint start, uint stop)
{
	assert(stop >= start);
	auto ptr = make_unique<Intuha<T>[]>(stop - start + 1);
	uint med = (stop + start) / 2;
	uint first = start , last = med + 1;
	uint count = 0;

	for (uint i = 0; i <= (stop - start); i++)
	{
		if ((last > stop) || ((first <= med) && (obj[first] < obj[last]))) { ptr[i] = obj[first++]; }
		else { ptr[i] = obj[last++]; }
	}
	for (uint i = 0; i <= (stop - start); i++) { obj[start + i] = ptr[i]; }
	return 0;
}

template<class T>
uint MergeSort(Intuha<T>* obj, int start, int stop)
{
	assert(stop >= start);
	if (stop == start) { return 0; }
	uint med = (stop + start) / 2;
	//cout << "Enter start " << start << " stop " << stop << " med " << med << endl;
	//for (uint i = start; i <= stop; i++)
	//{
	//	cout << "Data " << obj[i].GetValue() << endl;
	//}
	
	MergeSort(obj, start, med);
	MergeSort(obj, med + 1, stop);
	Merge(obj, start, stop);
	return 0;
}

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
		exit (1);
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
		s1[i] = static_cast<float>(rand() % 100000) - 50000;// / MAX_SIGN;
	}

	copyArr(s1.get(), s2.get(), len);
	{
		HronoTimer hTimer1("Bubbles");
	 	//SortBubble(s2.get(), len);
	}
	Valid_Sort(s2.get(), len);

	copyArr(s1.get(), s2.get(), len);
	{
		HronoTimer hTimer1("Shake");
		//SortShake(s2.get(), len);
	}
	Valid_Sort(s2.get(), len);

	copyArr(s1.get(), s2.get(), len);
	{
		HronoTimer hTimer1("SortCalc");
		SortCalc(s2.get(), 0, len);
	}
	Valid_Sort(s2.get(), len);

	copyArr(s1.get(), s2.get(), len);
	{
		HronoTimer hTimer1("QuickSort");
		MyQuickSort(s2.get(), 0, len - 1);
	}
	Valid_Sort(s2.get(), len);

	copyArr(s1.get(), s2.get(), len);
	{
		HronoTimer hTimer1("MergeSort");
		MergeSort(s2.get(), 0, len - 1);
	}
	Valid_Sort(s2.get(), len);

		
}