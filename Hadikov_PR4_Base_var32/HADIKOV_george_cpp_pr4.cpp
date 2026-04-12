#include <iostream>
#include <cstdlib>   
#include <ctime>     
#include <map>       

using namespace std;

// Глобальные константы

const int MAX_SIZE = 100; // максимальный размер массива


// Функции проверки корректности ввода

// Функция для  ввода целого числа с проверкой
bool inputInt(int& value) {
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(32767, '\n');
        return false;
    }
    cin.ignore(32767, '\n');
    return true;
}

// Функция ввода размера массива с проверкой границ
int inputSize(const char* prompt) {
    int size;
    while (true) {
        cout << prompt;
        if (inputInt(size) && size > 0 && size <= MAX_SIZE) {
            return size;
        }
        cout << "Ошибка! Введите целое число от 1 до " << MAX_SIZE << ": ";
    }
}

// Задние 1. 

// Находит длину самой длинной последовательности, где элементы попеременно возрастают и убывают
int longestAlternatingSequence(const int arr[], int size) {
    if (size == 0) return 0;
    if (size == 1) return 1;

    int maxLen = 1;
    int currentLen = 1;
    int expected = -1; // -1: не определено, 1: ждем возрастания, 0: ждем убывания

    // Цикл for по коллекции (по значениям элементов через индекс)
    // Используем обычный for, но обращаемся arr[i] как к элементу коллекции
    for (int i = 1; i < size; ++i) {
        if (arr[i] > arr[i - 1]) {
            if (expected == -1 || expected == 1) {
                currentLen++;
                expected = 0; // теперь ждем убывания
            } else {
                if (currentLen > maxLen) maxLen = currentLen;
                currentLen = 2;
                expected = 0;
            }
        } else if (arr[i] < arr[i - 1]) {
            if (expected == -1 || expected == 0) {
                currentLen++;
                expected = 1; //  ждем возрастания
            } else {
                if (currentLen > maxLen) maxLen = currentLen;
                currentLen = 2;
                expected = 1;
            }
        } else {
            // элементы равны
            if (currentLen > maxLen) maxLen = currentLen;
            currentLen = 1;
            expected = -1;
        }
    }
    
    if (currentLen > maxLen) maxLen = currentLen;
    return maxLen;
}

//для задания 1 с инициализацией при описании
void task1() {
    cout << "\n=== ЗАДАНИЕ 1 ===\n";
    cout << "Поиск длины самой длинной попеременно возрастающей/убывающей последовательности\n";
    cout << "Инициализация массива при описании произвольными значениями.\n";
    
    // Инициализация при описании массива произвольными значениями
    int arr[] = {1, 7, 2, 5, 4, 4, 6, 4, 2, 6, 1, 8, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    cout << "Массив: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    int result = longestAlternatingSequence(arr, size);
    cout << "Результат: длина самой длинной последовательности = " << result << endl;
    cout << "=================\n\n";
}

// Задание 2.

// Функция ввода массива с клавиатуры с контролем
void inputArrayFromKeyboard(int arr[], int size) {
    cout << "Введите " << size << " целых чисел:\n";
    for (int i = 0; i < size; ++i) { // цикл for по индексам
        while (true) {
            cout << "arr[" << i << "] = ";
            if (inputInt(arr[i])) {
                break;
            }
            cout << "Ошибка! Введите целое число.\n";
        }
    }
}

// Функция вывода массива (обращение по индексам)
void printArrayByIndex(const int arr[], int size) {
    for (int i = 0; i < size; ++i) { // цикл for по индексам
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Находит элементы, равные среднему арифметическому двух соседних
void findAverageOfNeighbors(const int arr[], int size, int result[], int& resultSize) {
    resultSize = 0;
    
    if (size < 3) {
        return; // недостаточно элементов
    }
    
    // Цикл for по индексам
    for (int i = 1; i < size - 1; ++i) {
        // Проверка: 2 * arr[i] == arr[i-1] + arr[i+1] (целочисленно)
        if (2 * arr[i] == arr[i - 1] + arr[i + 1]) {
            result[resultSize] = arr[i];
            resultSize++;
        }
    }
}

//  для задания 2
void task2() {
    cout << "\n=== ЗАДАНИЕ 2 ===\n";
    cout << "Поиск элементов, равных среднему арифметическому двух соседних.\n";
    cout << "Ввод массива с клавиатуры с контролем.\n";
    
    int size = inputSize("Введите размер массива (1..100): ");
    
    int arr[MAX_SIZE];
    inputArrayFromKeyboard(arr, size);
    
    cout << "Введенный массив: ";
    printArrayByIndex(arr, size);
    
    int result[MAX_SIZE];
    int resultSize;
    findAverageOfNeighbors(arr, size, result, resultSize);
    
    cout << "Элементы, равные среднему соседей: ";
    if (resultSize == 0) {
        cout << "отсутствуют";
    } else {
        for (int i = 0; i < resultSize; ++i) {
            cout << result[i] << " ";
        }
    }
    cout << endl;
    cout << "=================\n\n";
}

// Задание 3.
void initArrayRandom(int* arr, int size, int minVal = 1, int maxVal = 10) {
    int* ptr = arr; // указатель на начало массива
    int* end = arr + size; // указатель на конец массива
    
    while (ptr < end) { // цикл while по указателям
        *ptr = minVal + rand() % (maxVal - minVal + 1);
        ptr++;
    }
}

// Функция вывода массива через указатели
void printArrayByPointer(const int* arr, int size) {
    const int* ptr = arr;
    const int* end = arr + size;
    
    while (ptr < end) {
        cout << *ptr << " ";
        ptr++;
    }
    cout << endl;
}

// Функция решения задачи 3
// Находит подмассив максимальной длины без повторяющихся элементов
// Используется алгоритм скользящего окна с двумя указателями
void longestUniqueSubarray(const int* arr, int size, int* result, int& resultSize) {
    resultSize = 0;
    if (size == 0) return;
    
    int maxStart = 0;
    int maxLen = 0;
    
    int left = 0;
    int right = 0;
    
    // Массив для отслеживания вхождений чисел 
    // Предполагаем, что числа в диапазоне 0..99 (при необходимости можно расширить)
    const int HASH_SIZE = 1000;
    int count[HASH_SIZE] = {0};
    
    // Цикл while по номеру элемента (right)
    while (right < size) {
        int val = *(arr + right); // обращение через указатель
        
        // Если элемент уже есть в окне, сдвигаем левую границу
        while (count[val] > 0) {
            int leftVal = *(arr + left);
            count[leftVal]--;
            left++;
        }
        
        count[val]++;
        
        // Обновляем максимум
        int currentLen = right - left + 1;
        if (currentLen > maxLen) {
            maxLen = currentLen;
            maxStart = left;
        }
        
        right++;
    }
    
    // Копируем результат через указатели
    resultSize = maxLen;
    const int* src = arr + maxStart;
    int* dst = result;
    int* dstEnd = result + maxLen;
    
    while (dst < dstEnd) {
        *dst = *src;
        dst++;
        src++;
    }
}

// для задания 3
void task3() {
    cout << "\n=== ЗАДАНИЕ 3 ===\n";
    cout << "Поиск подмассива максимальной длины без повторяющихся элементов.\n";
    cout << "Инициализация массива случайными значениями.\n";
    
    // Инициализация датчика случайных чисел
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
    
    int size = inputSize("Введите размер массива (1..100): ");
    
    int arr[MAX_SIZE];
    initArrayRandom(arr, size, 1, 10); // числа от 1 до 10
    
    cout << "Сгенерированный массив: ";
    printArrayByPointer(arr, size);
    
    int result[MAX_SIZE];
    int resultSize;
    longestUniqueSubarray(arr, size, result, resultSize);
    
    cout << "Подмассив без повторений максимальной длины: ";
    printArrayByPointer(result, resultSize);
    cout << "Длина: " << resultSize << endl;
}

// Тип указателя на функцию без параметров и возвращаемого значения
typedef void (*TaskFunction)();

void showMenu() {
    cout << "1. Задание 1 \n";
    cout << "2. Задание 2 \n";
    cout << "3. Задание 3 \n";
    cout << "0. Выход\n";
    cout << "Выберите номер задачи: ";
}

int main() {
    // Инициализация map для меню
    map<int, TaskFunction> menu;
    menu[1] = task1;
    menu[2] = task2;
    menu[3] = task3;
    
    int choice;
    
    do {
        showMenu();
        
        if (!inputInt(choice)) {
            cout << "Ошибка ввода! Попробуйте снова.\n";
            choice = -1;
            continue;
        }
        
        if (choice == 0) {
            cout << "Программа завершена.\n";
            break;
        }
        
        // Поиск в map и вызов соответствующей функции
        if (menu.find(choice) != menu.end()) {
            menu[choice](); // вызов функции задания
        } else {
            cout << "Неверный номер задачи! Выберите 1, 2, 3 или 0.\n";
        }
        
    } while (true);
    
    return 0;
}
