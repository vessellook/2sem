#pragma once
#include <string>


struct Animal {
    friend std::ostream& operator<<(std::ostream& os, const Animal& text_block);
public:
    std::string name;
    int age;
    Animal(): name(), age() {}
    Animal(std::string name, int age): name(name), age(age) {}
};

std::ostream& operator<<(std::ostream& os, const Animal& animal) {
    os << "(" << animal.name << ", " << animal.age << ")";
    return os;
}

Animal rise_age(Animal item) {
    item.age += 1;
    return item;
}

bool is_age_not_zero(Animal item) {
    return item.age != 0;
}