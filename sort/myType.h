#pragma once

#include <iostream>

typedef unsigned int uint;
using namespace std;

template <class T>
class Intuha
{
public:
	T* data;
	uint len = 0, loc_count;
	static uint static_count;
public:
	explicit Intuha(const T& data = 0) noexcept
	{
		init(data);
		//cout << "Create Data T& " << " [" << this->data << "][ " << loc_count << " ] = " << data << endl;
	}

	Intuha(Intuha<T>&& obj) noexcept
	{
		//cout << "Create Intuha<T>&& " << " from [" << obj.data << "][ " << obj.loc_count << " ] = " << *(obj.data) << endl;
		this->loc_count = obj.loc_count;
		this->data = obj.data;
		obj.data = nullptr;
	}

	explicit Intuha(const Intuha<T>& obj) noexcept
	{
		//cout << "Create Intuha<T>& " << " from [" << obj.data << "][ " << obj.loc_count << " ] = " << *(obj.data) << endl;
		init(*(obj.data));
		*(this->data) = *(obj.data);
	}

	~Intuha()
	{
		//cout << "Delete Data " << " [" << this->data << "][ " << loc_count << " ]" << endl;
		delete data;
	}

	typename enable_if<is_same<T, uint>::value || is_same<T, int>::value || is_same<T, float>::value, T>::type init(T data)
	{
		static_count++;
		this->data = new T(data);
		this->loc_count = static_count;
		this->len = 1;
		return 0;
	}

	Intuha<T>& operator= (const Intuha<T>& obj)
	{
		//cout << "Assigment Intuha<T>& from [" << obj.data << "][ " << obj.loc_count << "] to [" << this->data << "][ " << this->loc_count << " ] = " << *(obj.data) << " >> " << *data << endl;
		*(this->data) = *(obj.data);
		
		return *this;
	}

	Intuha<T>& operator= (Intuha<T>&& obj) noexcept
	{
		T* tmp_data = this->data;
		uint tmp_count = this->loc_count;

		this->data = obj.data;
		this->loc_count = obj.loc_count;

		obj.data = tmp_data;
		obj.loc_count = tmp_count;
		
		//cout << "Assigment Intuha<T>&& from [" << tmp_data  << "] to [" << this->data << "] " << " >> " << *(this->data) << endl;
		return *this;
	}

	Intuha<T>& operator= (Intuha<T>* obj)
	{
		//cout << "Assigment Intuha<T>* c = " << loc_count << ", " << obj->loc_count << " from [" << obj.data << "] to [" << data << "] " << *(obj.data) << " >> " << *data << endl;
		*(this->data) = *(obj.data);
		return *this;
	}

	Intuha<T>& operator= (T data)
	{
		//cout << "Equal data T count = " << loc_count << " in [" << this->data << "] = " << data << endl;
		*(this->data) = data;
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
		cout << data << endl;
		return 0;
	}

	inline uint GetCount() { return count; }
	inline T GetValue() const { return *(this->data); }

	friend uint MyQuickSort(Intuha<uint>* obj, int start, int len);
};
template<class T>
uint Intuha<T>::static_count = 0;