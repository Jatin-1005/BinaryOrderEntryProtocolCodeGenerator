// https://medium.com/@sidbhasin82/c-templates-what-is-std-enable-if-and-how-to-use-it-fd76d3abbabe
// https://github.com/sid842/cpp-tutorials/blob/main/templates-mp/main.cpp

#include <iostream>
#include <vector>
#include <set>

template<bool B, class T>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

class Person {
    public:
        std::string toString() const {
            return "Person";
        }
};

class Animal {
    public:
        std::string toString() const {
            return "Animal";
        }
};

class House {
    public:
        std::string toString() const {
            return "House";
        }
};

struct true_type {
    static const bool value = true;
};

struct false_type {
    static const bool value = false;
};

template<typename T>
struct is_type_container: false_type {};

template<typename T>
struct is_type_container<std::vector<T>>: true_type {};

template<typename T>
struct is_type_container<std::set<T>>: true_type {};

template<typename T>
struct has_to_string: false_type {};
template<>
struct has_to_string<House>: true_type {};
template<>
struct has_to_string<Person>: true_type {};
template<>
struct has_to_string<Animal>: true_type {};

template<typename T>
struct is_built_in_type: false_type {};

template<>
struct is_built_in_type<int>: true_type {};
template<>
struct is_built_in_type<float>: true_type {};

template<typename T>
std::string ToString(const T& x,
    typename enable_if<is_built_in_type<T>::value, T>::type* = 0) {
        return std::to_string(x);
}

template<typename T>
std::string ToString(const T& x,
    typename enable_if<has_to_string<T>::value, T>::type* = 0) {
        return x.toString();
}

template<typename T>
std::string ToString(const T& x,
    typename enable_if<is_type_container<T>::value, T>::type* = 0) {
        if(x.empty()) return "[]";
        std::string result = "[";
        for(auto& ele: x) {
            result += ToString(ele) + ",";
        }
        result.back() = ']';
        return result;
}

template<typename T>
void LOG(const T& t) {
    std::cout << ToString(t) << std::endl;
}

int main(int argc, const char* argv[]) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    Person p;
    Animal a;
    float pi = 3.14f;

    LOG(nums);
    LOG(p);
    LOG(a);
    LOG(pi);

    return 0;
}







