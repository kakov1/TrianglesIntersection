#include <iostream>

int main() {
    int number = 5;       // Обычная переменная
    int &refNumber = number; // Ссылка на переменную number

    int newNumber = refNumber; // Создаем новую переменную и присваиваем ей значение ссылки

    refNumber = 10; // Изменяем значение через ссылку

    std::cout << "Original number: " << number << std::endl; // Выводит 10
    std::cout << "New number: " << newNumber << std::endl;   // Выводит 5

    return 0;
}