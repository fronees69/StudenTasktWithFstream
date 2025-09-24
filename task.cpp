#include <iostream>   // Подключение библиотеки для ввода/вывода
#include <string>     // Подключение библиотеки для работы со строками
#include <fstream>    // Подключение библиотеки для работы с файлами
#include <Windows.h>  // Подключение библиотеки Windows для настройки кодировки консоли

using namespace std; // Использование стандартного пространства имён

// Структура для хранения данных о студенте
struct Student
{
    string name;     // Имя студента
    string surname;  // Фамилия студента
    int age;         // Возраст студента
};

// Указатель на массив студентов
Student* students = nullptr;
// Количество студентов
int studentCount = 0;
const string FILE_OF_DATA = "MyFile.txt"; // Путь к файлу

// Функция сохранения студентов в файл
void saveToFile()
{
    ofstream fout(FILE_OF_DATA);
    if (!fout)
    {
        cout << "Ошибка открытия файла\n";
        return;
    }
    fout << studentCount << endl; // Сохраняем количество студентов
    for (int i = 0; i < studentCount; i++)
    {
        fout << students[i].name << " "
            << students[i].surname << " "
            << students[i].age << endl;
    }
    fout.close();
}

// Функция загрузки студентов из файла
void loadFile()
{
    ifstream fin(FILE_OF_DATA);
    if (!fin)
    {
        cout << "Файл не найден\n";
        return;
    }
    fin >> studentCount;
    students = new Student[studentCount];
    for (int i = 0; i < studentCount; i++)
    {
        fin >> students[i].name >> students[i].surname >> students[i].age;
    }
    fin.close();
}

// Функция отображения меню
void showMenu()
{
    cout << "\n       === Меню ===\n";
    cout << "1. Показать всех студентов\n";
    cout << "2. Добавить студента\n";
    cout << "3. Изменить студента\n";
    cout << "4. Удалить студента\n";
    cout << "0. Выход\n";
    cout << "Выберите пункт: ";
}

// Функция отображения списка студентов
void showStudents()
{
    if (studentCount == 0)
    {
        cout << "Список студентов пуст.\n";
        return;
    }
    for (int i = 0; i < studentCount; i++)
    {
        cout << i + 1 << ". " << students[i].name << " "
            << students[i].surname << ", возраст: "
            << students[i].age << endl;
    }
}

// Функция добавления студента
void addStudent()
{
    Student s;
    cout << "Введите имя: ";
    cin >> s.name;
    cout << "Введите фамилию: ";
    cin >> s.surname;
    cout << "Введите возраст: ";
    cin >> s.age;

    Student* temp = new Student[studentCount + 1];
    for (int i = 0; i < studentCount; i++)
        temp[i] = students[i];
    temp[studentCount] = s;
    delete[] students;
    students = temp;
    studentCount++;

    cout << "Студент добавлен.\n";
    saveToFile(); // Сохраняем изменения
}

// Функция изменения данных студента
void changeStudent()
{
    if (studentCount == 0)
    {
        cout << "Нет студентов для изменения.\n";
        return;
    }
    showStudents();
    cout << "Введите номер студента для изменения: ";
    int index;
    cin >> index;
    if (index <= 0 || index > studentCount)
    {
        cout << "Неправильный номер.\n";
        return;
    }
    index--;
    cout << "Введите новое имя: ";
    cin >> students[index].name;
    cout << "Введите новую фамилию: ";
    cin >> students[index].surname;
    cout << "Введите новый возраст: ";
    cin >> students[index].age;

    cout << "Данные студента обновлены.\n";
    saveToFile(); // Сохраняем изменения
}

// Функция удаления студента
void deleteStudent()
{
    if (studentCount == 0)
    {
        cout << "Нет студентов для удаления.\n";
        return;
    }
    showStudents();
    cout << "Введите номер студента для удаления: ";
    int index;
    cin >> index;
    if (index <= 0 || index > studentCount)
    {
        cout << "Неправильный номер.\n";
        return;
    }
    index--;

    Student* temp = new Student[studentCount - 1];
    for (int i = 0, j = 0; i < studentCount; i++)
    {
        if (i == index) continue;
        temp[j++] = students[i];
    }
    delete[] students;
    students = temp;
    studentCount--;

    cout << "Студент удалён.\n";
    saveToFile(); // Сохраняем изменения
}

// Главная функция программы
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    loadFile(); // Загружаем данные при старте

    while (true)
    {
        showMenu();
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            showStudents();
            break;
        case 2:
            addStudent();
            break;
        case 3:
            changeStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 0:
            delete[] students;
            cout << "Выход.\n";
            return 0;
        default:
            cout << "Неверный выбор, попробуйте ещё раз.\n";
        }
    }
}
