#include <iostream>
#include <iomanip>
#include <time.h>
#include <windows.h>

using namespace std;

// 1. Створення та заповнення динамічного масиву випадковими дійсними числами
void Create(double* a, const int n, const double Low, const double High)
{
    for (int i = 0; i < n; i++)
    {
        double r = (double)rand() / RAND_MAX;
        a[i] = Low + r * (High - Low);
    }
}

// 2. Форматне виведення масиву у рядок
void Print(double* a, const int n)
{
    for (int i = 0; i < n; i++)
        cout << setw(8) << setprecision(2) << fixed << a[i];
    cout << endl;
}

// 3. Обчислення суми від'ємних елементів
double SumNegative(double* a, const int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] < 0)
            sum += a[i];
    }
    return sum;
}

// 4. Пошук індексу мінімального елемента
int MinIndex(double* a, const int n)
{
    int min_i = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i] < a[min_i])
            min_i = i;
    }
    return min_i;
}

// 5. Пошук індексу максимального елемента
int MaxIndex(double* a, const int n)
{
    int max_i = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i] > a[max_i])
            max_i = i;
    }
    return max_i;
}

// 6. Обчислення добутку елементів між min та max
double ProductBetweenMinMax(double* a, const int n)
{
    int min_i = MinIndex(a, n);
    int max_i = MaxIndex(a, n);

    // Визначаємо ліву (start) та праву (end) межі
    int start, end;
    if (min_i < max_i)
    {
        start = min_i;
        end = max_i;
    }
    else
    {
        start = max_i;
        end = min_i;
    }

    // Якщо між ними немає елементів
    if (end - start <= 1)
        return 0;

    double p = 1.0;
    for (int i = start + 1; i < end; i++)
    {
        p *= a[i];
    }
    return p;
}

// 7. Сортування елементів на парних індексах за зростанням
void SortEvenIndices(double* a, const int n)
{
    for (int i = 0; i < n; i += 2)
    {
        for (int j = i + 2; j < n; j += 2)
        {
            if (a[i] > a[j])
            {
                double temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand((unsigned)time(NULL));

    int n;
    cout << "Введіть розмір масиву n: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Розмір масиву має бути більшим за 0!" << endl;
        return 1;
    }

    // Створення динамічного масиву в оперативній пам'яті
    double* a = new double[n];

    double Low = -10.0;
    double High = 10.0;

    // Створення та виведення початкового масиву
    Create(a, n, Low, High);
    cout << "\nПочатковий масив:" << endl;
    Print(a, n);

    // 1.1. Обчислення суми від'ємних елементів
    double sumNeg = SumNegative(a, n);
    cout << "\nСума від'ємних елементів = " << setprecision(2) << fixed << sumNeg << endl;

    // 1.2. Обчислення добутку елементів між min та max
    double prod = ProductBetweenMinMax(a, n);
    cout << "Добуток елементів між min та max = " << setprecision(2) << fixed << prod << endl;

    // 2. Модифікація: Впорядкування елементів на парних індексах
    SortEvenIndices(a, n);

    // Виведення модифікованого масиву
    cout << "\nМодифікований масив (парні індекси впорядковано):" << endl;
    Print(a, n);

    // Обов'язкове звільнення динамічної пам'яті
    delete[] a;

    return 0;
}