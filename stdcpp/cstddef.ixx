// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module stdcpp.cstddef;

export namespace std
{
    using size_t      = decltype(sizeof(0));
    using ptrdiff_t   = decltype((char*)0 - (char*)0);
    using nullptr_t   = decltype(nullptr);
    using max_align_t = long double;

    enum class byte : 
        unsigned char 
    {
    };

    template <typename IntType>
    constexpr byte operator<<(byte b, IntType shift) noexcept 
    { 
        return byte(static_cast<unsigned char>(b) << shift); 
    }

    template <typename IntType>
    constexpr byte operator>>(byte b, IntType shift) noexcept 
    {
        return byte(static_cast<unsigned char>(b) >> shift);
    }

    constexpr byte operator|(byte l, byte r) noexcept 
    {
        return byte(static_cast<unsigned char>(l) | static_cast<unsigned char>(r)); 
    }

    constexpr byte operator&(byte l, byte r) noexcept
    { 
        return byte(static_cast<unsigned char>(l) & static_cast<unsigned char>(r)); 
    }

    constexpr byte operator^(byte l, byte r) noexcept 
    {
        return byte(static_cast<unsigned char>(l) ^ static_cast<unsigned char>(r)); 
    }

    constexpr byte operator~(byte b) noexcept 
    { 
        return byte(~static_cast<unsigned char>(b)); 
    }

    constexpr byte& operator|=(byte& l, byte r) noexcept 
    { 
        return l = l | r;
    }

    constexpr byte& operator&=(byte& l, byte r) noexcept
    { 
        return l = l & r;
    }

    constexpr byte& operator^=(byte& l, byte r) noexcept 
    { 
        return l = l ^ r;
    }

    template <typename IntType>
    constexpr byte& operator<<=(byte& b, IntType shift) noexcept 
    { 
        return b = b << shift;
    }

    template <typename IntType>
    constexpr byte& operator>>=(byte& b, IntType shift) noexcept 
    { 
        return b = b >> shift; 
    }

    template <typename IntType>
    [[nodiscard]] constexpr IntType to_integer(byte b) noexcept
    {
        return static_cast<IntType>(b);
    }
}