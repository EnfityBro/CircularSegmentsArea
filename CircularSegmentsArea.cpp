#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <limits>
#include <clocale>
using namespace std;

// Константа Пи с высокой точностью
const double PI = 3.14159265358979323846;

/*Форматирует число с двумя знаками после запятой.*/
string FormatNumber(double value)
{
    ostringstream oss;
    oss << fixed << setprecision(2) << value;

    return oss.str();
}

/*
Вычисляет параметры круга по радиусу и типу расчета.
@param radius - радиус круга (должен быть в диапазоне [0.01, 1e6]).
@param type - строка, определяющая тип расчета:
            "площадь_круга" - только площадь,
            "длина_окружности" - только длина окружности,
            "все_параметры" - площадь, длина и диаметр.
@return Вектор строк с результатами или сообщением об ошибке.
*/
vector<string> CalculateCircleParams(double radius, const string& type)
{
    vector<string> result;

    // Проверка допустимого диапазона радиуса
    if ((radius < 0.01) || (radius > 1e6))
    {
        result.push_back("Ошибка: радиус вне допустимого диапазона (0.01 – 1e6)");
        return result;
    }

    // Расчет основных величин
    double area = PI * radius * radius;
    double circumference = 2.0 * PI * radius;
    double diameter = 2.0 * radius;

    // Формирование выходных данных в зависимости от типа расчета
    if (type == "площадь_круга")
    {
        result.push_back("Площадь: " + FormatNumber(area));
    }
    else if (type == "длина_окружности")
    {
        result.push_back("Длина окружности: " + FormatNumber(circumference));
    }
    else if (type == "все_параметры")
    {
        result.push_back("Площадь: " + FormatNumber(area));
        result.push_back("Длина окружности: " + FormatNumber(circumference));
        result.push_back("Диаметр: " + FormatNumber(diameter));
    }
    else
    {
        result.push_back("Ошибка: неизвестный тип расчета");
    }

    return result;
}

/*Отображает главное меню программы.*/
void ShowMenu()
{
    cout << "\n========================================\n";
    cout << "  Вычислительная система определения\n";
    cout << "  площадей круговых сегментов\n";
    cout << "========================================\n";
    cout << "1. Выполнение\n";
    cout << "2. Тестирование\n";
    cout << "3. Выход\n";
    cout << "========================================\n";
    cout << "Выберите пункт меню: ";
}

/*Осуществляет режим выполнения: ввод данных пользователем и расчет.*/
void RunExecution()
{
    double radius;
    string type;

    cout << "\n--- Режим выполнения ---\n";
    cout << "Введите радиус (от 0.01 до 1e6): ";

    // Обработка некорректного ввода радиуса
    while (!(cin >> radius))
    {
        cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        cout << "Ошибка исходных данных, повторите ввод\n";
        cout << "Введите радиус (от 0.01 до 1e6): ";
    }

    // Очистка буфера после чтения числа
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    cout << "Введите тип расчета (площадь_круга, длина_окружности, все_параметры): ";
    getline(cin, type);

    // Удаление возможных пробелов в начале и конце
    size_t start = type.find_first_not_of(" \t");
    size_t end = type.find_last_not_of(" \t");

    if ((start != string::npos) && (end != string::npos))
    {
        type = type.substr(start, end - start + 1);
    }
    else
    {
        type = "";
    }

    vector<string> output = CalculateCircleParams(radius, type);

    cout << "\nРезультат:\n";
    for (const auto& line : output)
    {
        cout << line << endl;
    }
}

#pragma region Testing

/*Структура для хранения тестового случая.*/
struct TestCase
{
    double radius;
    string type;
    vector<string> expected;
    string description;
};

/*Осуществляет режим автоматического тестирования.*/
void RunTesting()
{
    cout << "\n--- Режим автоматического тестирования ---\n\n";

    vector<TestCase> tests =
    {
        // Корректные тесты из примеров задания
        {5.0, "все_параметры",
        {"Площадь: 78.54", "Длина окружности: 31.42", "Диаметр: 10.00"},
        "Пример 1: радиус 5, все параметры"},

        {10.0, "все_параметры",
        {"Площадь: 314.16", "Длина окружности: 62.83", "Диаметр: 20.00"},
        "Пример 2: радиус 10, все параметры"},

        {5.0, "площадь_круга",
        {"Площадь: 78.54"},
        "Только площадь при радиусе 5"},

        {10.0, "длина_окружности",
        {"Длина окружности: 62.83"},
        "Только длина окружности при радиусе 10"},
        
        // Граничные значения
        {0.01, "все_параметры",
        {"Площадь: 0.00", "Длина окружности: 0.06", "Диаметр: 0.02"},
        "Минимальный допустимый радиус 0.01"},
        
        {1000000.0, "площадь_круга",
        {"Площадь: 3141592653589.79"},
        "Максимальный допустимый радиус 1e6"},
        
        // Некорректные данные
        {0.009, "все_параметры",
        {"Ошибка: радиус вне допустимого диапазона (0.01 – 1e6)"},
        "Радиус меньше минимума"},
        
        {1000001.0, "площадь_круга",
        {"Ошибка: радиус вне допустимого диапазона (0.01 – 1e6)"},
        "Радиус больше максимума"},
        
        {5.0, "неизвестный_тип",
        {"Ошибка: неизвестный тип расчета"},
        "Неизвестный тип расчета"},
        
        {-5.0, "все_параметры",
        {"Ошибка: радиус вне допустимого диапазона (0.01 – 1e6)"},
        "Отрицательный радиус"}
    };

    int passed = 0;
    int total = static_cast<int>(tests.size());

    for (size_t i = 0; i < tests.size(); ++i)
    {
        const TestCase& tc = tests[i];
        vector<string> actual = CalculateCircleParams(tc.radius, tc.type);

        bool isOk = (actual == tc.expected);

        cout << "Тест " << (i + 1) << ": " << tc.description << "\n";
        cout << "  Ввод: радиус=" << tc.radius << ", тип=\"" << tc.type << "\"\n";
        cout << "  Ожидаемый результат:\n";
        for (const auto& s : tc.expected)
        {
            cout << "    " << s << "\n";
        }
        cout << "  Фактический результат:\n";
        for (const auto& s : actual)
        {
            cout << "    " << s << "\n";
        }
        cout << "  Статус: " << (isOk ? "ПРОЙДЕН" : "НЕ ПРОЙДЕН") << "\n\n";

        if (isOk)
        {
            ++passed;
        }
    }

    cout << "========================================\n";
    cout << "Итог: пройдено " << passed << " из " << total << " тестов\n";

    if (passed == total)
    {
        cout << "Все тесты успешно пройдены.\n";
    }
    else
    {
        cout << "Обнаружены ошибки в работе программы.\n";
    }

    cout << "========================================\n";
}

#pragma endregion

/*Входная точка программы. Реализует цикл главного меню и управляет переходами между режимами.*/
int main()
{
    // Установка локали и кодировки для корректного отображения кириллицы
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice = 0;
    bool running = true;

    while (running)
    {
        ShowMenu();

        // Обработка ввода пункта меню
        if (!(cin >> choice))
        {
            cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            cout << "Ошибка исходных данных, повторите ввод\n";
            continue;
        }
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

        switch (choice)
        {
        case 1:
            RunExecution();
            break;
        case 2:
            RunTesting();
            break;
        case 3:
            cout << "\nЗавершение работы программы.\n";
            running = false;
            break;
        default:
            cout << "Ошибка исходных данных, повторите ввод\n";
            break;
        }
    }

    return 0;
}