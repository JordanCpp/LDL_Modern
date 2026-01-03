// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module stdcpp.allocator;

import stdcpp.cstddef;
import stdcpp.cpp_new;

export namespace std
{
    template <typename T>
    class allocator
    {
    public:
        using value_type = T;
        using size_type  = size_t;

        constexpr allocator() noexcept = default;

        template <typename U>
        constexpr allocator(const allocator<U>&) noexcept {}

        [[nodiscard]] T* allocate(size_t n)
        {
            if (n == 0)
            {
                return nullptr;
            }

            return static_cast<T*>(::operator new(n * sizeof(T)));
        }

        void deallocate(T* p, size_t n) noexcept
        {
            if (p)
            {
                ::operator delete(p);
            }
        }
    };

    template <typename T, typename U>
    bool operator==(const allocator<T>&, const allocator<U>&) noexcept 
    { 
        return true; 
    }

    template <typename T, typename U>
    bool operator!=(const allocator<T>&, const allocator<U>&) noexcept 
    { 
        return false; 
    }
}