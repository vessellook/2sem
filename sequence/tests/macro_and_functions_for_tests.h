#pragma once

// тест последовательностей TestSequence проверяет соответствие
// реализации потомков интерфейса ISequence<T>
// Нужно поменять параметры в файле с желаемым тестом
// В этом файле несколько функций, полезных во всех тестах,
// и макроопределения

// нужно добавить больше проверок, более точных и разнообразных,
// удачные проверки делать, потому что эти почти ничего не отлавливают

#include "../config.h"
#include <iostream>


#define ASSERT(condition) do{if(!(condition)){ abort(); }}while(false)

#define SHOW_TEST_PASSED


void print_test_separator() {
#ifdef SHOW_TEST_PASSED
    std::cout << std::endl;
#endif
}

template<class T>
bool check_value(T got_value, T expected_value, int test_num) {
    if (got_value != expected_value) {
        std::cout << "TEST " << test_num << ": "
                  << "FAILED: expected value " << expected_value
                  << " and got value " << got_value << std::endl;
        return false;
    }
#ifdef SHOW_TEST_PASSED
    std::cout << "TEST " << test_num << ": "
              << "PASSED: expected value and got value are equal" << std::endl;
#endif
    return true;
}
