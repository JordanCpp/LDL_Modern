// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module stdcpp.cpp_string;

import stdcpp.cpp_new;
import stdcpp.cstring;
import stdcpp.allocator;

export namespace stdcpp
{
	template <typename T, typename Allocator = stdcpp::allocator<T>>
	class basic_string
	{
	private:
		Allocator _alloc;
		size_t    _capacity;
		size_t    _position;
		T*        _content;

		void freeContent()
		{
			if (_content)
			{
				_alloc.deallocate(_content, _capacity);
			}
		}
	public:
		~basic_string()
		{
			freeContent();
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
				T* p = _alloc.allocate(total);

				if (_content)
				{
					for (size_t i = 0; i < _position; i++)
					{
						p[i] = _content[i];
					}

					freeContent();
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
}