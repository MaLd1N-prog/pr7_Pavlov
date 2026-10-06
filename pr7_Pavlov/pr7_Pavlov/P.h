#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#define DEBUG_MODE


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

int loadFile(Zapiska items[])
{
    std::ifstream file("internet-shop.txt");
    if (!file.is_open())
    {
        std::cout << "Ошибка: нe удалось открыть данный файл";
        return 1;

    }

    int count = 0;
    std::string line;

    while (std::getline(file, line))
    {
        if (line == "") continue;



    }
    std::stringstream ss(line);
    std::string segment;
    try
    {
        std::getline(ss, segment, ';');
        items[count].codeTovar = std::stoi(segment);

        std::getline(ss, items[count].name, ';');
        std::getline(ss, items[count].category, ';');

        std::getline(ss, segment, ';');
        items[count].price = std::stoi(segment);

        std::getline(ss, segment);
        items[count].col = std::stoi(segment);
        count++;
    }
    catch (const std::exception e) {
        std::cout << "Ошибка при чтении строки: " << line << " " << e.what() << "\n";
    }

    file.close();

#ifdef DEBUG_MODE
    std::cout << "[DEBUG] Загружено товаров: " << count << "\n";
#endif
    return count;
}
void saveFile(Zapiska items[], int count)
{
    std::ofstream file("internet-shop.txt");
    if (!file.is_open())
    {
        std::cout << "Ошибка записи в файл";
        return;

    }


    for (int i = 0; i < count; i++)
    {
        file << items[i].codeTovar << ";" << items[i].name << ";" << items[i].category << ";" << items[i].price << ";" << items[i].col << ";" << "\n";

    }
    file.close();
#ifdef DEBUG_MODE
    std::cout << "[DEBUG] Записано товаров: " << count << "\n";
#endif

   
}

//1
void searchByName(Zapiska items[], int count) {
    std::string searchName;
    std::cout << "Введите название товара для поиска: ";
    std::cin.ignore();
    std::getline(std::cin, searchName);
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (items[i].name == searchName) {
            std::cout << "Найден: "<< items[i].codeTovar << " | " << items[i].name << " | " << items[i].category << " | " << items[i].price << "руб. | " << items[i].col << "шт. | " << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Товар с таким названием не найден ";
    }
}

//2
void filterByCategory(Zapiska items[], int count) {
    std::string category;
    std::cout << "Введите категорию для фильтрации: ";
    std::cin.ignore();
    std::getline(std::cin, category);

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (items[i].category == category) {
            std::cout << "Найден: " << items[i].codeTovar << " | " << items[i].name << " | " << items[i].category << " | " << items[i].price << "руб. | " << items[i].col << "шт. | " << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Товаров с такой категорией нету! ";
    }
}
//3,4,5

void buyItem(Zapiska items[], int count) {
    int code;
    int quantity;
    std::cout << "Введите код товара для покупки: ";
    std::cin >> code;
    std::cout << "Введите количество: ";
    std::cin >> quantity;

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (items[i].codeTovar == code) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        std::cout << "Товар с таким кодом не найден!\n";
        return;
    }
    if (items[index].col < quantity)
    {
        throw std::runtime_error("Недостаточно товара!");
    }

    double totCost = items[index].price * quantity;
    items[index].col -= quantity;
    std::cout << "Покупка успешно оформлена!\n";
    std::cout << "Стоимость заказа: "<< totCost << " руб. \n";
    std::cout << "Остаток на складе: " << items[index].col << "\n";
}


