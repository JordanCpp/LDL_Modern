module;

export module std;

import Win32;

extern "C" int main();

extern "C" void EntryPoint()
{
	int result = main();
}

export namespace std
{
    void* malloc(size_t size)
    {
        return HeapAlloc(GetProcessHeap(), 0, size);
    }

    void free(void* ptr)
    {
        if (ptr)
        {
            HeapFree(GetProcessHeap(), 0, ptr);
        }
    }

	size_t strlen(const char* src)
	{
		size_t i = 0;

		while (src[i] != 0)
		{
			i++;
		}

		return i;
	}

	template <typename T>
	class base_string
	{
	private:
		size_t _capacity;
		size_t _position;
		T*     _content;

	public:
		base_string() :
			_capacity(0),
			_position(0),
			_content(nullptr)
		{
		}

		base_string(const T* source) :
			_capacity(0),
			_position(0),
			_content(nullptr)
		{
			size_t length = strlen(source);

			resize(length);

			for (size_t i = 0; i < length; i++)
			{
				_content[i] = source[i];
			}
		}

		base_string& operator=(const T& source)
		{
			if (&source != this)
			{
				size_t length = strlen(source);

				resize(length);

				for (size_t i = 0; i < length; i++)
				{
					_content[i] = source[i];
				}
			}

			return *this;
		}

		bool operator== (const base_string<T>& source)
		{
			return (strcmp(_content, source.c_str()) == 0);
		}

		base_string& operator=(const T* source)
		{
			size_t length = strlen(source);

			resize(length);

			for (size_t i = 0; i < length; i++)
			{
				_content[i] = source[i];
			}

			return *this;
		}

		base_string<T>& operator+=(const base_string<T>& source)
		{
			for (size_t i = 0; i < source.size(); i++)
			{
				push_back(source[i]);
			}

			return *this;
		}

		base_string<T>& operator=(const base_string<T>& source)
		{
			if (&source != this)
			{
				size_t length = source.size();

				resize(length);

				for (size_t i = 0; i < length; i++)
				{
					_content[i] = source[i];
				}
			}

			return *this;
		}

		size_t capacity() const
		{
			return _capacity;
		}

		size_t size() const
		{
			return _position;
		}

		const T* c_str() const
		{
			return _content;
		}

		T* allocate(size_t count)
		{
			return new T[count];
		}

		void reserve(size_t count)
		{
			size_t total = count + 1;

			if (total > _capacity)
			{
				T* p = allocate(total);

				for (size_t i = 0; i < _position; i++)
				{
					p[i] = _content[i];
				}

				_content = p;
				_capacity = total;
			}
		}

		void resize(size_t count)
		{
			if (_capacity < count)
			{
				reserve(count);
			}

			_position = count;
			_content[_position] = '\0';
		}

		void push_back(const T& element)
		{
			if (_capacity == 0)
			{
				reserve(2);
			}
			else if (_position + 1 >= _capacity)
			{
				reserve(_capacity * 2);
			}

			_content[_position] = element;
			_position++;
			_content[_position] = '\0';
		}

		const T& at(size_t index) const
		{
			return _content[index];
		}

		T& at(size_t index)
		{
			return _content[index];
		}

		const T& operator[] (size_t index) const
		{
			return _content[index];
		}

		T& operator[] (size_t index)
		{
			return _content[index];
		}
	};

	typedef base_string<char> string;
}

export
{
    void* operator new(size_t bytes)
    {
        return std::malloc(bytes);
    }

	void* operator new[](size_t bytes)
	{
		return std::malloc(bytes);
	}

	void* operator new(size_t bytes, void* ptr)
	{
		return ptr;
	}

	void* operator new[](size_t bytes, void* ptr)
	{
		return ptr;
	}
}