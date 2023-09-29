#include <iostream>

int main()
{
    // начальное действие: объявить переменную num, равную 1
    // условие: пока num меньше или равно 100
    // после каждого шага (итерации) цикла добавляем к num 1
    for (int num = 1; num <=100; num += 1)
    {
        //  -если число кратно и 3, и 5, вывести FizzBuzz

        if ((num % 3 == 0) && (num % 5 == 0))
        {
            std::cout << "FizzBuzz" << std::endl;
        }
        else if (num % 3 == 0){
            std::cout << "Fizz" << std::endl;
        }
        else if (num % 5 == 0)
        {
            std::cout << "Buzz" << std::endl;
        }
        else
        {
            std::cout << num << std::endl;
        }
        //  -если число кратно 3, вывести Fizz
        //  -если число кратно 5, вывести Buzz
        //  -иначе вывести число

        // выводим num    
        //std::cout << num << std::endl;
    }
}