/******************************************************************
 * This file contains example for types and operators in C++
 * 
 * Presentation link:
 * https://docs.google.com/presentation/d/1VF3nosLAyei9z-1nGdl6BdLefjv89clD943RHEJxtqI/edit?usp=sharing
 * 
 * Copyright: Pavel Golovinskiy 2023
*******************************************************************/

// файл строковых операций из STL
#include <string> 

struct MyString
{
    std::string the_string;                             // поле структуры, тип - стандартная строка

    operator const char* () const                       // оператор приведения к типу const char* - указателю на строку
    {
        return the_string.c_str();
    }
};

struct real
{
    // поле структуры, тип - беззнаковое целое длиной 32 бита
    uint32_t field;

    // функция структуры, в даном случае auto заменится на std::string
    // std::string ConvertToString();
    auto ConvertToString()
    { 
        return std::to_string(field); 
    }

    // оператор приведения структуры real к целому числу
    // real number = 5;
    // int i = number; приведет number к числу и запишет в i значение 5
    operator int ()                                     
    { 
        return (int)field; 
    }

    // оператор присваивания, позволяет инициализировать структуру целым числом
    // real number = 5; 
    real& operator= (uint32_t num)                      
    {
        field = num;
    }
};

// оператор сложения 2-х структур типа real, возвращаемое значение - строка
MyString operator+ (real a, real b)
{
    return MyString{a.ConvertToString() + b.ConvertToString()};
};

// оператор литерала "r" для чисел. из-за этой функции все числа формата 100r 
// будут считаться типом real 
real operator ""r(unsigned long long a) 
{ 
    // инициализация структуры типа real. хоть оно здесь и не написано. но return автоматически 
    // приведет то что следует за ним к типу возвращаемого значения. 
    return {(uint32_t)a}; 
};

int main(int argc, char** argv)
{    
    auto result = 5r + 6r;
    printf("result of \"5r + 6r\" is %s\n", (const char*)result);
    
    return 0;
}