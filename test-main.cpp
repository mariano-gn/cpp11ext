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

#include <iostream>
#include <string>
#include "cpp11ext.h"

enum class ecshort {
    first_short,
    second_short
};

enum old_enum {
    first_old = 10,
    second_old
};

template<typename K, typename M>
void print(M&& map, K&& key) {
    std::cout << "Value of " << key << ": " << map[key] << std::endl;
}
template<typename M>
void print(M&& map, ecshort&& key) {
    std::cout << "Value of " << static_cast<std::underlying_type<ecshort>::type>(key) << ": " << map[key] << std::endl;
}

int main() {
    ext11::unordered_map<size_t, std::string> first_map{ {1, "one"}, {2, "two"} };
    print(first_map, 1);
    print(first_map, 2);

    ext11::unordered_map<old_enum, std::string> second_map{ {first_old, "The first old"}, {second_old, "The second old"} };
    print(second_map, first_old);
    print(second_map, second_old);

    ext11::unordered_map<ecshort, std::string> failing_map{ { ecshort::first_short, "The first ecshort" }, { ecshort::second_short, "The second ecshort" } };
    print(failing_map, ecshort::first_short);
    print(failing_map, ecshort::second_short);
}
