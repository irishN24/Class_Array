#include <iostream>
#include <time.h>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

class Array {
    int* a;
    int n;

public:
    Array(size_t len = 1, int t = 1, int min_d = 0, int max_d = 10); // конструктор 1
    Array(int* arr, size_t l); // конструктор 2
    Array(Array& arr);
    ~Array() { //деструктор
        if (a) {
            delete[] a;
            a = NULL;
        }
    }
    Array& operator =(Array& arr); //оператор присвоения
    int& operator [](int i);// оператор взятия индекса
    bool Test(); // проверка на упорядоченность
    bool operator == (Array arr); // оператор равенства 
    void Shell_sort(); //сортировка Шелла
    void Sift(int* arr, int n, int i);
    void HeapSort(); //Пирамидальная сортировка
    void quick_S(int l, int r);
    void Hoar_Sort(); // Сортировка Хоара
    //void Bit_sort(); //Побитовая сортировка
    friend istream& operator >> (istream& is, Array& a); //оператор ввод
    friend ostream& operator << (ostream& os, Array& a); //оператор вывод
};
//конструктор 1
Array::Array(size_t len, int t, int min_d, int max_d) {
    if (len > 0) { // проверка длины массива
        if (max_d >= min_d) { //проверка правильного диапазона
            a = new int[len]; //выделяем память
            if (a != nullptr) {
                this->n = len; // Инициализируем длину
                for (int i = 0; i < len; i++) {
                    a[i] = min_d + rand() % (max_d - min_d + 1);
                }
                if (t == 2) {
                    sort(a, a + n);
                }
                if (t == 3) {
                    sort(a, a + n, greater<int>());
                }
                else if (t > 3 || t < 1) {
                    cout << "Incorrect order!!!\n";
                    exit(-1);
                }
            }
        }
        else {
            cout << "Incorrect diapozon!!!\n";
        }
    }
}
//конструктор 2
Array::Array(int* arr, size_t l) {
    if (arr != nullptr) {
        a = new int[l];
        if (a != nullptr) {
            this->n = l;
            for (int i = 0; i < l; i++) {
                a[i] = arr[i];
            }
        }
    }
}
//конструктор копирования
Array::Array(Array& arr) : n(arr.n) {
    a = new int[n];
    copy(arr.a, arr.a + n, a);
}
//оператор присвоения
Array& Array::operator =(Array& arr) {
    if (this != &arr) {
        delete[] a;
        n = arr.n;
        a = new int[n];
        if (a) {
            for (int i = 0; i < n; i++) {
                a[i] = arr[i];
            }
        }
    }
    return *this;
}
//взятие индекса
int& Array::operator[](int i) {
    if (i < 0 || i >= n) {
        std::cout << "Index outside the array!!!" << "\n";
        return a[0];
    }
    return a[i];
}
//проверка на неупорядоченность
bool Array::Test() {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            return false;
        }
    }
    return true;
}
//оператор равенства
bool Array::operator == (Array arr) {
    if (n != arr.n) {
        return false;
    }
    Array arrr(*this);
    sort(arrr.a, arrr.a + arrr.n);
    sort(arr.a, arr.a + arr.n);
    for (int i = 0; i < n; i++) {
        if (arrr[i] == arr.a[i]) {
            return true;
        }
    }
    return false;
}
// Сортировка Шелла
void Array::Shell_sort() {
    int len = n;
    for (int step = n / 2; step > 0; step = step / 2) {
        for (int i = step; i < len; i++) {
            int tmp = a[i];
            int j;
            for (j = i; j >= step; j -= step) {
                if (tmp < a[j - step])
                {
                    a[j] = a[j - step];
                }
                else {
                    break;
                }
            }
            a[j] = tmp;
        }
    }
}
//Функция для просеивания
void Array::Sift(int *arr, int n, int i) {
    int j = i; //корень
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[j]) {
        j = l;
    }
    if (r < n && arr[r] > arr[j]) {
        j = r;
    }
    if (j != i) {
        swap(arr[i], arr[j]);
        Sift(arr, n, j);
    }
}
//Пирамидальная сортировка
void Array::HeapSort() {
    for (int i = (n / 2) - 1; i >= 0; i--) {
        Sift(a, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        Sift(a, i, 0);
    }
}
// Сортировка Хоара
void Array::Hoar_Sort() {
    quick_S(0, n - 1);
}
//быстрая сортировка
void Array::quick_S(int l, int r) {
    if (l <= r) {
        int i = l;
        int j = r;
        int x = a[(l + r) / 2];
        while (i <= j) {
            while (a[i] < x) {
                i++;
            }
            while (a[j] > x) {
                j--;
            }
            if (i <= j) {
                swap(a[i], a[j]);
                i++;
                j--;
            }
        }
        if (l < j) {
            quick_S(l, j);
        }
        if (r > i) {
            quick_S(i, r);
        }
    }
    else return;
}

istream& operator>>(istream& is, Array& a) { //дружественный ввод
    int len;
    cout << "Enter size of array: ";
    cin >> len;
    if (len > 0) {
        if (a.a != nullptr) {
            delete[] a.a;
            a.a = nullptr;
        }
        a.n = len;
        a.a = new int[len];
        cout << "Enter the array elements:\n";
        for (int i = 0; i < len; ++i) {
            is >> a.a[i];
        }
        return is;
    }
    else {
        cout << "Incorrect size!!!";
    }
}
ostream& operator<<(ostream& os, Array& a) { //дружественный вывод
    for (int i = 0; i < a.n; i++) {
        os << a.a[i] << " ";
    }
    os << "\n";
    return os;
}

int main()
{
    srand(time(NULL));
    Array Array1(500, 1, -100, 600);
    cout << "Array 1: " << Array1;
    cout << "==========================" << "\n";

    int arrr[5] = { 2,4,7,90,45 };
    Array Array2(arrr, 5);
    cout << "Array 2: " << Array2;
    cout << "==========================" << "\n";

    Array Array3(Array1);
    cout << "Array 3: " << Array3;
    cout << "==========================" << "\n";

    Array Array4;
    Array4 = Array2;
    cout << "Array 4: " << Array4;
    cout << "==========================" << "\n";

    if (Array1.Test()) {
        cout << "Array 1 is ordered\n";
    }
    else {
        cout << "Array 1 is not ordered\n";
    }
    cout << "==========================" << "\n";
    if (Array1 == Array2) {
        cout << "Arrays are equal\n";
    }
    else {
        cout << "Arrays are not equal\n";
    }
    cout << "==========================" << "\n";
    Array Array5;
    cin >> Array5;
    cout << "Array 5: " << Array5;
    cout << Array5[4] << "\n";
    Array Array6(Array1);
    cout << "Array 6: " << Array6;
    Array Array7(Array1);
    cout << "Array 7: " << Array7;
        auto start = steady_clock::now();
        Array1.Hoar_Sort();
        auto end = steady_clock::now();
        cout << "Array 1 in Hoar sort: " << Array1 << "Time: " << duration_cast<nanoseconds>(end - start).count() << " nanoseconds\n";

        
        start = steady_clock::now();
        Array6.Shell_sort();
        end = steady_clock::now();
        cout << "Array 6 in Shell Sort: " << Array6 << "Time: " << duration_cast<nanoseconds>(end - start).count() << " nanoseconds\n";

        
        start = steady_clock::now();
        Array7.HeapSort();
        end = steady_clock::now();
        cout << "Array 7 in Heap Sort: " << Array7 << "Time: " << duration_cast<nanoseconds>(end - start).count() << " nanoseconds\n";
    
}
