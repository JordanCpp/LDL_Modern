// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module LDL.Color;

import std;

export namespace LDL
{
	class Color
	{
	public:
		Color() :
			r(0),
			g(0),
			b(0),
			a(255)
		{
		}

		Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha) :
			r(red),
			g(green),
			b(blue),
			a(alpha)
		{
		}

		std::uint32_t toInt() const
		{
			return (std::uint32_t)((r << 24) | (g << 16) | (b << 8) | a);
		}

		std::uint8_t r;
		std::uint8_t g;
		std::uint8_t b;
		std::uint8_t a;
	};
}
