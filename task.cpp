#include <iostream>   // Подключение библиотеки для ввода/вывода через консоль
#include <string>     // Подключение библиотеки для работы со строками
#include <fstream>    // Подключение библиотеки для работы с файлами
#include <Windows.h>  // Подключение библиотеки Windows для настройки кодировки консоли

using namespace std; // Использование стандартного пространства имён std

// Структура для хранения информации о студенте
struct Student
{
    string name;     // Имя студента
    string surname;  // Фамилия студента
    string group;
    int age;         // Возраст студента
};

// Функция для сохранения массива студентов в файл
void saveToFile(const Student* students, int studentCount)
{
    const string FILE_OF_DATA = "Database.txt"; // Локальное имя файла
    ofstream fout(FILE_OF_DATA);    // Открытие файла для записи
    if (!fout)                      // Проверка успешности открытия
    {
        cout << "Ошибка открытия файла\n";
        return;
    }
    fout << studentCount << endl;   // Запись количества студентов
    for (int i = 0; i < studentCount; i++) // Цикл по всем студентам
    {
        fout << students[i].name << " "      // Запись имени
            << students[i].surname << " "   // Запись фамилии
            << students[i].age     // Запись возраста
            << students[i].group << " " << endl;
    }
    fout.close();                   // Закрытие файла
}

// Функция для загрузки массива студентов из файла
void loadFile(Student*& students, int& studentCount)
{
    const string FILE_OF_DATA = "Database.txt"; // Локальное имя файла
    ifstream fin(FILE_OF_DATA);     // Открытие файла для чтения
    if (!fin)                       // Проверка успешности открытия
    {
        cout << "Файл не найден\n";
        students = nullptr;
        studentCount = 0;
        return;
    }
    fin >> studentCount;            // Чтение количества студентов
    students = new Student[studentCount]; // Выделение памяти под массив
    for (int i = 0; i < studentCount; i++) // Цикл по всем студентам
    {
        fin >> students[i].name >> students[i].surname >> students[i].age >> students[i].group; // Чтение данных
    }
    fin.close();                    // Закрытие файла
}

// Функция отображения текстового меню
void showMenu()
{
    cout << "\n ========= Меню =========\n";
    cout << "1. Показать всех студентов\n";   // Пункт меню: показать студентов
    cout << "2. Добавить студента\n";         // Пункт меню: добавить студента
    cout << "3. Изменить студента\n";         // Пункт меню: изменить данные
    cout << "4. Удалить студента\n";          // Пункт меню: удалить студента
    cout << "0. Выход\n";                     // Пункт меню: выход из программы
    cout << "Выберите пункт: ";               // Приглашение к выбору
}

// Функция отображения списка студентов
void showStudents(const Student* students, int studentCount)
{
    if (studentCount == 0)                    // Проверка: есть ли студенты
    {
        cout << "Список студентов пуст.\n";
        return;
    }
    for (int i = 0; i < studentCount; i++)    // Цикл по всем студентам
    {
        cout << i + 1 << ". " << students[i].name << " "
            << students[i].surname << ", возраст: "
            << students[i].age << 
            ", Класс: " << students[i].group << endl;      // Вывод информации о студенте
    }
}

// Функция добавления нового студента
void addStudent(Student*& students, int& studentCount)
{
    Student s;                                // Новый студент
    cout << "Введите имя: ";
    cin >> s.name;                            // Ввод имени
    cout << "Введите фамилию: ";
    cin >> s.surname;                         // Ввод фамилии
    cout << "Введите возраст: ";
    cin >> s.age;              // Ввод возраста
    cout << "Введите класс студента: ";
    cin >> s.group;

    Student* temp = new Student[studentCount + 1]; // Новый массив на 1 больше
    for (int i = 0; i < studentCount; i++)         // Копирование старых данных
        temp[i] = students[i];
    temp[studentCount] = s;                        // Добавление нового студента
    delete[] students;                             // Освобождение старой памяти
    students = temp;                               // Переназначение указателя
    studentCount++;                                // Увеличение счётчика

    cout << "Студент добавлен.\n";
    saveToFile(students, studentCount);            // Сохранение изменений
}

// Функция изменения данных студента
void changeStudent(Student* students, int studentCount)
{
    if (studentCount == 0)                         // Проверка: есть ли студенты
    {
        cout << "Нет студентов для изменения.\n";
        return;
    }
    showStudents(students, studentCount);          // Показ списка
    cout << "Введите номер студента для изменения: ";
    int index;
    cin >> index;                                  // Ввод номера
    if (index <= 0 || index > studentCount)        // Проверка корректности
    {
        cout << "Неправильный номер.\n";
        return;
    }
    index--;                                       // Преобразование в индекс массива
    cout << "Введите новое имя: ";
    cin >> students[index].name;                   // Ввод нового имени
    cout << "Введите новую фамилию: ";
    cin >> students[index].surname;                // Ввод новой фамилии
    cout << "Введите новый возраст: ";
    cin >> students[index].age;                    // Ввод нового возраста
    cout << "Введите новый класс студента: ";
    cin >> students[index].group;

    cout << "Данные студента обновлены.\n";
    saveToFile(students, studentCount);            // Сохранение изменений
}

// Функция удаления студента
void deleteStudent(Student*& students, int& studentCount)
{
    if (studentCount == 0)                         // Проверка: есть ли студенты
    {
        cout << "Нет студентов для удаления.\n";
        return;
    }
    showStudents(students, studentCount);          // Показ списка
    cout << "Введите номер студента для удаления: ";
    int index;
    cin >> index;                                  // Ввод номера
    if (index <= 0 || index > studentCount)        // Проверка корректности
    {
        cout << "Неправильный номер.\n";
        return;
    }
    index--;                                       // Преобразование в индекс массива

    Student* temp = new Student[studentCount - 1]; // Новый массив на 1 меньше
    for (int i = 0, j = 0; i < studentCount; i++)  // Копирование всех кроме удаляемого
    {
        if (i == index) continue;
        temp[j++] = students[i];
    }
    delete[] students;                             // Освобождение памяти
    students = temp;                               // Переназначение указателя
    studentCount--;                                // Уменьшение счётчика

    cout << "Студент удалён.\n";
    saveToFile(students, studentCount);            // Сохранение изменений
}

// Главная функция программы
int main()
{
    SetConsoleCP(1251);                            // Установка кодировки ввода (кириллица)
    SetConsoleOutputCP(1251);                      // Установка кодировки вывода

    Student* students = nullptr;                   // Указатель на динамический массив студентов
    int studentCount = 0;                          // Количество студентов

    loadFile(students, studentCount);              // Загрузка данных из файла при старте

    while (true)                                   // Бесконечный цикл меню
    {
        showMenu();                                // Показ меню
        int choice;
        cin >> choice;                             // Ввод выбора пользователя
        switch (choice)                            // Обработка выбора
        {
        case 1:
            showStudents(students, studentCount);  // Показ студентов
            break;
        case 2:
            addStudent(students, studentCount);    // Добавление студента
            break;
        case 3:
            changeStudent(students, studentCount); // Изменение студента
            break;
        case 4:
            deleteStudent(students, studentCount); // Удаление студента
            break;
        case 0:
            delete[] students;                     // Освобождение памяти
            cout << "Выход.\n";
            return 0;                              // Завершение программы
        default:
            cout << "Неверный выбор, попробуйте ещё раз.\n"; // Обработка ошибки
        }
    }
}
