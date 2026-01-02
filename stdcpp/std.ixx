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
import stdcpp.unique_ptr;
import stdcpp.expected;
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
	/********************************************************************************************************************
													    	cstring
	********************************************************************************************************************/
	using stdcpp::strlen;
	/********************************************************************************************************************
															string
	********************************************************************************************************************/
	using string = stdcpp::string;
	/********************************************************************************************************************
															vector
	********************************************************************************************************************/
	template <typename T>
	using vector = stdcpp::vector<T>;
	/********************************************************************************************************************
															unique_ptr
	********************************************************************************************************************/
	template<typename T, typename D = stdcpp::default_delete<T>>
	using unique_ptr = stdcpp::unique_ptr<T, D>;
	using stdcpp::make_unique;
	using stdcpp::default_delete;
	/********************************************************************************************************************
															expected
	********************************************************************************************************************/
	using stdcpp::unexpect_t;
	using stdcpp::unexpect;
	using stdcpp::unexpected;
	template<typename T, typename E> using expected = stdcpp::expected<T, E>;
}