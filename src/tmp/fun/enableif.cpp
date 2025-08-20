#include <iostream>
#include <vector>
#include <set>

template<bool B, typename T>
struct enable_if {};

template<typename T>
struct enable_if<true, T> { typedef T type; };
 
template<typename T>
struct is_type_container {
    static const bool value = false;
};

template<typename T>
struct is_type_container<std::vector<T>> {
    static const bool value = true;
};

template<typename T>
struct is_type_container<std::set<T>> {
    static const bool value = true;
};

template<typename T>
struct is_built_in_type { static const bool value = false; };

template<>
struct is_built_in_type<int> { static const bool value = true; };



template<typename T>
std::string ToString(const T& x,
    typename enable_if<is_type_container<T>::value, T>::type* = 0) {
    return "container";
}

template<typename T>
std::string ToString(const T& x, typename enable_if<is_built_in_type<T>::value, T>::type* = 0) {
    return std::to_string(x);
}

int main()
{
    std::vector<int> v = {2, 5};
    std::cout << ToString(24) << std::endl;
    std::cout << ToString(v) << std::endl;
    return 0;
}