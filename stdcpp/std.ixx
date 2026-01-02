// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module std;

import stdcpp.cstddef;
import stdcpp.cstdint;
import stdcpp.cstdlib;
import stdcpp.cpp_new;
import stdcpp.cpp_string;
import stdcpp.cstring;
import stdcpp.vector;
import Win32;

extern "C" int main();

extern "C" void EntryPoint()
{
	int result = main();

	ExitProcess(result);
}

export namespace std
{
	/********************************************************************************************************************
												        	 cstdint
	********************************************************************************************************************/
	using uint8_t  = stdcpp::uint8_t;
	using int8_t   = stdcpp::int8_t;
	using uint16_t = stdcpp::uint16_t;
	using int16_t  = stdcpp::int16_t;
	using uint32_t = stdcpp::uint32_t;
	using int32_t  = stdcpp::int32_t;

	/********************************************************************************************************************
															 stddef.h
	********************************************************************************************************************/
	using size_t = stdcpp::size_t;

	/********************************************************************************************************************
															 stdlib.h
	********************************************************************************************************************/
	using stdcpp::malloc;
	using stdcpp::free;
	using stdcpp::strlen;

	using string = stdcpp::string;

	template <typename T>
	using vector = stdcpp::vector<T>;
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