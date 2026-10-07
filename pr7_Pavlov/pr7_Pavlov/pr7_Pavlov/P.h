#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>


class Zapiska
{
public:
    int codeTovar;
    std::string name;
    std::string category;
    double price;
    int col;
};

const int MAX_ITEMS = 100;

inline int loadFile(Zapiska items[])
{
    std::ifstream file("internet-shop.txt");
    if (!file.is_open())
    {
        std::cout << "Ошибка: не удалось открыть файл internet-shop.txt\n";
        return -1;   
    }

    int count = 0;
    std::string line;
    while (std::getline(file, line) && count < MAX_ITEMS)
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string seg1, seg2, seg3, seg4, seg5;
        if (std::getline(ss, seg1, ';') &&
            std::getline(ss, seg2, ';') &&
            std::getline(ss, seg3, ';') &&
            std::getline(ss, seg4, ';') &&
            std::getline(ss, seg5, ';'))
        {
            if (!seg1.empty() && !seg2.empty() && !seg3.empty() &&
                !seg4.empty() && !seg5.empty())
            {
                try {
                    Zapiska temp;
                    temp.codeTovar = std::stoi(seg1);
                    temp.name = seg2;
                    temp.category = seg3;
                    temp.price = std::stod(seg4);   
                    temp.col = std::stoi(seg5);
                    items[count++] = temp;
                }
                catch (const std::exception& e) {
                    std::cout << "Ошибка при чтении строки: " << line
                        << " (" << e.what() << ")\n";
                }
            }
        }
    }

    file.close();

#ifdef DEBUG_MODE
    std::cout << "[DEBUG] Загружено товаров: " << count << "\n";
#endif
    return count;
}

inline void saveFile(Zapiska items[], int count)
{
    std::ofstream file("internet-shop.txt");
    if (!file.is_open())
    {
        std::cout << "Ошибка записи в файл\n";
        return;
    }
    for (int i = 0; i < count; i++)
    {
        file << items[i].codeTovar << ";"
            << items[i].name << ";"
            << items[i].category << ";"
            << items[i].price << ";"
            << items[i].col << ";\n";
    }
    file.close();
#ifdef DEBUG_MODE
    std::cout << "[DEBUG] Записано товаров: " << count << "\n";
#endif
}

// 1. Поиск по названию
inline void searchByName(Zapiska items[], int count)
{
    std::string searchName;
    std::cout << "Введите название товара для поиска: ";
    std::getline(std::cin, searchName);

    bool found = false;
    for (int i = 0; i < count; i++)
    {
        if (items[i].name == searchName)
        {
            std::cout << items[i].codeTovar << " | "
                << items[i].name << " | "
                << items[i].category << " | "
                << items[i].price << " руб. | "
                << items[i].col << " шт.\n";
            found = true;
        }
    }
    if (!found)
        std::cout << "Товар с таким названием не найден.\n";
}

// 2. Фильтр по категории
inline void filterByCategory(Zapiska items[], int count)
{
    std::string category;
    std::cout << "Введите категорию для фильтрации: ";
    std::getline(std::cin, category);   

    bool found = false;
    for (int i = 0; i < count; i++)
    {
        if (items[i].category == category)
        {
            std::cout << items[i].codeTovar << " | "
                << items[i].name << " | "
                << items[i].category << " | "
                << items[i].price << " руб. | "
                << items[i].col << " шт.\n";
            found = true;
        }
    }
    if (!found)
        std::cout << "Товаров с такой категорией нет.\n";
}

// 3,4,5. Оформление покупки
inline void buyItem(Zapiska items[], int count)
{
    int code, quantity;
    std::cout << "Введите код товара для покупки: ";
    std::cin >> code;
    std::cout << "Введите количество: ";
    std::cin >> quantity;
    std::cin.ignore();   

    int index = -1;
    for (int i = 0; i < count; i++)
    {
        if (items[i].codeTovar == code) { index = i; break; }
    }
    if (index == -1)
    {
        std::cout << "Товар с таким кодом не найден!\n";
        return;
    }
    if (items[index].col < quantity)
        throw std::runtime_error("Недостаточно товара на складе!");

    double totCost = items[index].price * quantity;
    items[index].col -= quantity;
    std::cout << "Покупка успешно оформлена!\n";
    std::cout << "Стоимость заказа: " << totCost << " руб.\n";
    std::cout << "Остаток товара: " << items[index].col << "\n";
}