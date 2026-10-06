// pr7_Pavlov.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Вариант 10. Интернет-магазин
Хранить:
код товара;
название;
категорию;
цену;
количество на складе.

Реализовать:
1. Поиск товара по названию.
2. Фильтрацию по категории.
3. Оформление покупки.
4. Уменьшение остатка.
5. Расчёт стоимости заказа.
6. Сохранение изменений.

При недостаточном количестве товара выбрасывать исключение.


*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#define DEBUG_MODE
#include "P.h"

int main()
{
    setlocale(LC_ALL, "Ru");
    Zapiska items[MAX_ITEMS];
    int count = loadFile(items);
    if (count < 0) return 0;

    while (true)
    {
        std::cout << "Выбор задания\n " << "1. Показать всё\n" << "2. Поиск по названию\n" << "3. Фильтр по категории\n" << "4. Оформление покупки\n" << "5. Сохранить и выйти\n";

        int vibor;
        std::cin >> vibor;
        std::cin.ignore();
        switch (vibor)
        {
        case 1:
            if (count == 0) {
                std::cout << "Список товаров пуст.";
            }
            else {

                for (int i = 0; i < count; i++)
                {
                    std::cout << items[i].codeTovar << " | " <<
                        items[i].name << " | " <<
                        items[i].category << " | " <<
                        items[i].price << "руб." << " | " <<
                        items[i].col << std::endl;
                }
            }
            break;
        case 2:
            searchByName(items, count);
            break;
        case 3:
            filterByCategory(items, count);
            break;
        case 4:
            try {
                buyItem(items, count);
            }
            catch (const std::exception e) {
                std::cerr << "Ошибка покупки: " << e.what() << "\n";
            }
            break;
        case 5:
            saveFile(items, count);
            return 0;

        default:
            std::cout << "Неверный  пункт выбора. Попробуйте снова!.\n";


        }
    }
    return 0;
       

    }

    


