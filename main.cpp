#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <windows.h>

using namespace std;

const int ARRAY_SIZE = 10;
const int MIN_RANDOM = 1;
const int MAX_RANDOM = 100;

// Функция для получения выбора пользователя с защитой от букв
int getUserChoice() {
    int choice;

    while (true) {
        cout << "Ваш выбор: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Ошибка! Введите целое число (1 или 2)." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    return choice;
}

// Функция для ручного заполнения массива
void fillManually(float arr[], int size) {
    cout << "Введите " << size << " чисел:" << endl;

    for (int i = 0; i < size; i++) {
        while (true) {
            cout << "Элемент [" << i << "]: ";
            cin >> arr[i];

            if (cin.fail()) {
                cout << "Ошибка! Введите число." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }
    }
}

// Функция для заполнения массива случайными числами
void fillRandomly(float arr[], int size) {
    for (int i = 0; i < size; i++) {
        int randomNumber = MIN_RANDOM + rand() % (MAX_RANDOM - MIN_RANDOM + 1);
        arr[i] = static_cast<float>(randomNumber);
    }
}

// Функция сортировки массива (метод "пузырька") с подсчетом итераций
void sortArray(float arr[], int size, int &iterations) {
    iterations = 0; // Обнуляем счетчик перед началом

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            iterations++; // Считаем каждое сравнение как итерацию

            if (arr[j] > arr[j + 1]) {
                // Обмен значений
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Функция вывода массива
void printArray(const float arr[], int size) {
    cout << "[";

    for (int i = 0; i < size; i++) {
        cout << arr[i];

        if (i < size - 1) {
            cout << ", ";
        }
    }

    cout << "]" << endl;
}

int main() {
    // Включаем поддержку русского языка в консоли Windows
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(0, "");

    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(0)));

    float arr[ARRAY_SIZE];

    cout << "=== Программа сортировки массива ===" << endl;
    cout << "Размер массива: " << ARRAY_SIZE << endl;
    cout << endl;

    cout << "Выберите способ заполнения массива:" << endl;
    cout << "1 - Ввести массив вручную" << endl;
    cout << "2 - Заполнить случайными числами (от " << MIN_RANDOM << " до " << MAX_RANDOM << ")" << endl;

    int choice = getUserChoice();
    cout << endl;

    if (choice == 1) {
        fillManually(arr, ARRAY_SIZE);
    } else if (choice == 2) {
        fillRandomly(arr, ARRAY_SIZE);
    } else {
        cout << "Ошибка: неверный пункт меню. Программа завершена." << endl;
        return 1;
    }

    cout << endl;
    cout << "Исходный массив:" << endl;
    printArray(arr, ARRAY_SIZE);

    int iterations = 0;
    // Сортировка (передаем iterations по ссылке, чтобы сохранить результат)
    sortArray(arr, ARRAY_SIZE, iterations);

    cout << endl;
    cout << "Отсортированный массив (по возрастанию):" << endl;
    printArray(arr, ARRAY_SIZE);

    // Выводим количество итераций
    cout << "Количество итераций, затраченных на сортировку: " << iterations << endl;

    return 0;
}
