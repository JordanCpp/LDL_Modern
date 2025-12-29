// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module std;

import Win32;

extern "C" int main();

extern "C" void EntryPoint()
{
	int result = main();

	ExitProcess(0);
}

export namespace std
{
	/********************************************************************************************************************
												        	 stdint.h 
	********************************************************************************************************************/
	using uint8_t  = unsigned char;
	using int8_t   = signed char;
	using uint16_t = unsigned short;
	using int16_t  = signed short;
	using uint32_t = unsigned int;
	using int32_t  = signed int;

	/********************************************************************************************************************
															 stddef.h
	********************************************************************************************************************/
	using size_t = unsigned int;

	/********************************************************************************************************************
															 stdlib.h
	********************************************************************************************************************/
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

	/********************************************************************************************************************
															 string.h
	********************************************************************************************************************/
	size_t strlen(const char* src)
	{
		size_t i = 0;

		while (src[i] != 0)
		{
			i++;
		}

		return i;
	}

	/********************************************************************************************************************
															 <string>
	********************************************************************************************************************/
	template <typename T>
	class basic_string
	{
	private:
		size_t _capacity;
		size_t _position;
		T*     _content;

	public:
		~basic_string()
		{
			if (_content)
			{
				delete[] _content;
			}
		}

		basic_string() :
			_capacity(0),
			_position(0),
			_content(nullptr)
		{
		}

		basic_string(const T* source) :
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

		basic_string& operator=(const T& source)
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

		bool operator== (const basic_string<T>& source)
		{
			return (strcmp(_content, source.c_str()) == 0);
		}

		basic_string& operator=(const T* source)
		{
			size_t length = strlen(source);

			resize(length);

			for (size_t i = 0; i < length; i++)
			{
				_content[i] = source[i];
			}

			return *this;
		}

		basic_string<T>& operator+=(const basic_string<T>& source)
		{
			for (size_t i = 0; i < source.size(); i++)
			{
				push_back(source[i]);
			}

			return *this;
		}

		basic_string<T>& operator=(const basic_string<T>& source)
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

				_content  = p;
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

	typedef basic_string<char> string;

	/********************************************************************************************************************
															 <expected>
	********************************************************************************************************************/
	template<typename E>
	class unexpect_t 
	{
	public:
		explicit unexpect_t() = default;
	};

	inline constexpr unexpect_t<void> unexpect{};

	template<typename E>
	class unexpected 
	{
		E _value;
	public:
		explicit unexpected(E e) : 
			_value(e)
		{
		}

		E& value() 
		{ 
			return _value; 
		}

		const E& value() const 
		{ 
			return _value; 
		}
	};

	template<typename T, typename E>
	class expected 
	{
	private:
		union 
		{
			T _value;
			E _error;
		};

		bool _hasValue;

	public:
		expected(const T& val) :
			_value(val),
			_hasValue(true)
		{
		}

		expected(T&& val) : 
			_value(static_cast<T&&>(val)), 
			_hasValue(true) 
		{
		}

		expected(unexpected<E>&& e) : 
			_error(static_cast<E&&>(e.value())), 
			_hasValue(false) 
		{
		}

		~expected() 
		{
			if (_hasValue)
			{
				_value.~T();
			}
			else
			{
				_error.~E();
			}
		}

		constexpr bool has_value() const noexcept 
		{ 
			return _hasValue; 
		}

		constexpr explicit operator bool() const noexcept 
		{ 
			return _hasValue;
		}

		T& operator*() 
		{ 
			return _value; 
		}

		const T& operator*() const 
		{ 
			return _value;
		}

		T* operator->() 
		{ 
			return &_value;
		}

		E& error() 
		{ 
			return _error; 
		}

		const E& error() const
		{ 
			return _error; 
		}

		template<typename U>
		constexpr T value_or(U&& default_value) const& 
		{
			return _hasValue ? _value : static_cast<T>(default_value);
		}
	};

	/********************************************************************************************************************
															 <unique_ptr>
	********************************************************************************************************************/
	template<typename T>
	struct default_delete 
	{
		void operator()(T* ptr) const 
		{
			delete ptr;
		}
	};

	template<typename T>
	struct default_delete<T[]> 
	{
		void operator()(T* ptr) const 
		{
			delete[] ptr;
		}
	};

	template<typename T, typename Deleter = default_delete<T>>
	class unique_ptr 
	{
	private:
		T* _ptr = nullptr;

	public:
		constexpr unique_ptr() noexcept : 
			_ptr(nullptr) 
		{
		}

		constexpr unique_ptr(nullptr_t) noexcept : 
			_ptr(nullptr) 
		{
		}

		explicit unique_ptr(T* ptr) noexcept : 
			_ptr(ptr) 
		{
		}

		unique_ptr(const unique_ptr&) = delete;
		unique_ptr& operator=(const unique_ptr&) = delete;

		unique_ptr(unique_ptr&& other) noexcept : 
			_ptr(other.release()) 
		{
		}

		unique_ptr& operator=(unique_ptr&& other) noexcept 
		{
			reset(other.release());

			return *this;
		}

		~unique_ptr() 
		{
			reset();
		}

		T* release() noexcept 
		{
			T* temp = _ptr;
			_ptr    = nullptr;

			return temp;
		}

		void reset(T* ptr = nullptr) noexcept 
		{
			T* oldPtr = _ptr;
			_ptr       = ptr;

			if (oldPtr)
			{
				Deleter{}(oldPtr);
			}
		}

		T* get() const noexcept 
		{ 
			return _ptr; 
		}

		explicit operator bool() const noexcept 
		{ 
			return _ptr != nullptr; 
		}

		T& operator*() const 
		{ 
			return *_ptr; 
		}

		T* operator->() const noexcept 
		{
			return _ptr;
		}
	};

	template<typename T, typename... Args>
	unique_ptr<T> make_unique(Args&&... args) 
	{
		return unique_ptr<T>(new T(static_cast<Args&&>(args)...));
	}
}

export
{
	/********************************************************************************************************************
															 <new>
	********************************************************************************************************************/

    void* operator new(size_t bytes)
    {
        return std::malloc(bytes);
    }

	void operator delete(void* ptr)
	{
		return std::free(ptr);
	}

	void* operator new[](size_t bytes)
	{
		return std::malloc(bytes);
	}

	void operator delete[](void* ptr)
	{
		return std::free(ptr);
	}

	void* operator new(size_t bytes, void* ptr)
	{
		return ptr;
	}

	void* operator new[](size_t bytes, void* ptr)
	{
		return ptr;
	}

	void __cdecl operator delete(void* ptr, size_t size) noexcept
	{
		::operator delete(ptr);
	}

	void __cdecl operator delete[](void* ptr, size_t size) noexcept
	{
		::operator delete[](ptr);
	}
}