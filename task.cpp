#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <cctype>

using namespace std;

struct Student 
{
    string name;
    string surname;
    string group;
    int age;
};

bool isValidName(const string& str) 
{
    if (str.empty()) return false;
    for (char ch : str) 
    {
        if (!isalpha(static_cast<unsigned char>(ch))) return false;
    }
    return true;
}

void saveToFile(const Student* students, int studentCount) 
{
    const string FILE_OF_DATA = "Database.txt";
    ofstream fout(FILE_OF_DATA);
    if (!fout) 
    {
        cout << "Ошибка открытия файла\n";
        return;
    }
    fout << studentCount << endl;
    for (int i = 0; i < studentCount; i++) 
    {
        fout << students[i].name << " "
            << students[i].surname << " "
            << students[i].age << " "
            << students[i].group << endl;
    }
    fout.close();
}

void loadFile(Student*& students, int& studentCount)
{
    const string FILE_OF_DATA = "Database.txt";
    ifstream fin(FILE_OF_DATA);
    if (!fin) 
    {
        cout << "Файл не найден\n";
        students = nullptr;
        studentCount = 0;
        return;
    }
    fin >> studentCount;
    students = new Student[studentCount];
    for (int i = 0; i < studentCount; i++) 
    {
        fin >> students[i].name >> students[i].surname >> students[i].age >> students[i].group;
    }
    fin.close();
}

void showMenu() 
{
    cout << "\n ========= Меню =========\n";
    cout << "1. Показать всех студентов\n";
    cout << "2. Добавить студента\n";
    cout << "3. Изменить студента\n";
    cout << "4. Удалить студента\n";
    cout << "5. Найти студента\n";
    cout << "0. Выход\n";
    cout << "Выберите пункт: ";
}

void showStudents(const Student* students, int studentCount) 
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
            << students[i].age << ", Класс: "
            << students[i].group << endl;
    }
}

void addStudent(Student*& students, int& studentCount) 
{
    Student s;
    cout << "Введите имя: ";
    cin >> s.name;
    while (!isValidName(s.name)) 
    {
        cout << "Имя должно содержать только буквы. Повторите ввод: ";
        cin >> s.name;
    }

    cout << "Введите фамилию: ";
    cin >> s.surname;
    while (!isValidName(s.surname)) 
    {
        cout << "Фамилия должна содержать только буквы. Повторите ввод: ";
        cin >> s.surname;
    }

    cout << "Введите возраст: ";
    while (!(cin >> s.age) || s.age < 10 || s.age > 100) 
    {
        cout << "Возраст должен быть числом от 10 до 100. Повторите ввод: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "Введите класс студента: ";
    cin >> s.group;
    while (s.group.empty()) 
    {
        cout << "Класс не может быть пустым. Повторите ввод: ";
        cin >> s.group;
    }

    Student* temp = new Student[studentCount + 1];
    for (int i = 0; i < studentCount; i++)
        temp[i] = students[i];
    temp[studentCount] = s;
    delete[] students;
    students = temp;
    studentCount++;

    cout << "Студент добавлен.\n";
    saveToFile(students, studentCount);
}

void changeStudent(Student* students, int studentCount) 
{
    if (studentCount == 0) {
        cout << "Нет студентов для изменения.\n";
        return;
    }

    showStudents(students, studentCount);
    cout << "Введите номер студента для изменения: ";
    int index;
    while (!(cin >> index) || index <= 0 || index > studentCount) 
    {
        cout << "Неправильный номер. Повторите ввод: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    index--;

    cout << "Введите новое имя: ";
    cin >> students[index].name;
    while (!isValidName(students[index].name)) 
    {
        cout << "Имя должно содержать только буквы. Повторите ввод: ";
        cin >> students[index].name;
    }

    cout << "Введите новую фамилию: ";
    cin >> students[index].surname;
    while (!isValidName(students[index].surname)) 
    {
        cout << "Фамилия должна содержать только буквы. Повторите ввод: ";
        cin >> students[index].surname;
    }

    cout << "Введите новый возраст: ";
    while (!(cin >> students[index].age) || students[index].age < 10 || students[index].age > 100)
    {
        cout << "Возраст должен быть числом от 10 до 100. Повторите ввод: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "Введите новый класс студента: ";
    cin >> students[index].group;
    while (students[index].group.empty()) 
    {
        cout << "Класс не может быть пустым. Повторите ввод: ";
        cin >> students[index].group;
    }

    cout << "Данные студента обновлены.\n";
    saveToFile(students, studentCount);
}

void deleteStudent(Student*& students, int& studentCount) 
{
    if (studentCount == 0) {
        cout << "Нет студентов для удаления.\n";
        return;
    }

    showStudents(students, studentCount);
    cout << "Введите номер студента для удаления: ";
    int index;
    while (!(cin >> index) || index <= 0 || index > studentCount) 
    {
        cout << "Неправильный номер. Повторите ввод: ";
        cin.clear();
        cin.ignore(1000, '\n');
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
    saveToFile(students, studentCount);
}

void searchStudent(Student*& students, int& studentCount)
{
    bool isFound = false;
    string studentSurname;
    if (studentCount == 0)
    {
        cout << "Список пуст.";
        return;
    }
    cout << "Введите фамилию для поиска: ";
    cin >> studentSurname;
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].surname == studentSurname)
        {
            cout << i + 1 << ". " << students[i].name << " " << students[i].surname << ", группа: " << students[i].group << ", возраст: " << students[i].age << endl;
            isFound = true;
        }
    }
    if (!isFound)
    {
        cout << "Студент не найден." << endl;
    }

}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Student* students = nullptr;
    int studentCount = 0;

    loadFile(students, studentCount);

    while (true) 
    {
        showMenu();
        int choice;
        if (!(cin >> choice))
        {
            cout << "Ошибка ввода. Введите число.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) 
        {
        case 1:
            showStudents(students, studentCount);
            break;
        case 2:
            addStudent(students, studentCount);
            break;
        case 3:
            changeStudent(students, studentCount);
            break;
        case 4:
            deleteStudent(students, studentCount);
            break;
        case 5: 
            searchStudent(students, studentCount);
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
