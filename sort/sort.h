#pragma once

#include <iostream>
#include <cassert>
#include <cstring>

#include "myType.h"

typedef unsigned int uint;
using namespace std;

namespace MySort
{
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

			if (!((i + 1) % 2))
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
		Intuha<T> val(obj[shift].GetValue()), tmp(0);

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
	inline uint Prepare(int data) { return 1; }

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
		assert(max < 10000);
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

	template<class T>
	uint Merge(Intuha<T>* obj, uint start, uint stop)
	{
		assert(stop >= start);
		auto ptr = make_unique<Intuha<T>[]>(stop - start + 1);
		uint med = (stop + start) / 2;
		uint first = start, last = med + 1;
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
		MergeSort(obj, start, med);
		MergeSort(obj, med + 1, stop);
		Merge(obj, start, stop);
		return 0;
	}
}

