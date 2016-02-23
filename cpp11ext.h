/**
Copyright (c) 2016 Mariano Gonzalez

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _CPP11EXT_H_
#define _CPP11EXT_H_
#include <type_traits>
#include <unordered_map>

namespace ext11 {
    // hash function for scoped enums.
    // What it does is simply forwarding the job to the hash function of the underlying type of the enum.
    struct echash {
        template <typename enumclass_t>
        std::size_t operator()(enumclass_t&& ec) const {
            using under_type = typename std::underlying_type<typename std::decay<enumclass_t>::type>::type;
            return std::hash<under_type>()(static_cast<under_type>(ec));
        }
    };

    // Hash function for ext11::unordered_map
    // If said parameter is a scoped enum it uses echash, otherwise it just uses std::hash
    template <typename key_t>
    using hash_t = typename std::conditional<std::is_enum<key_t>::value, echash, std::hash<key_t>>::type;

    template <typename key_t, 
        typename T,
        typename _hasher = hash_t<key_t>,
        typename _eqt = std::equal_to<key_t>,
        typename _alloc = std::allocator<std::pair<const key_t, T>>>
    using unordered_map = std::unordered_map<key_t, T, _hasher, _eqt, _alloc>;
}

#endif // _CPP11EXT_H_
