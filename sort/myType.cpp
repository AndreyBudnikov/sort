template <class T>
class Intuha
{
private:
	T* data;
	uint len = 0, loc_count;
	static uint count;
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
