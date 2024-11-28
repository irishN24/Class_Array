#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Array {
    int *a, n;

public:
    Array(size_t len = 1, int t = 1, int min_d = 0, int max_d = 10); // конструктор 1 ++
    Array(int* arr, size_t l); // конструктор 2 ++
    Array(Array& arr); //конструктор копирования ++
    ~Array() { //деструктор ++
        if (a) {
            delete[] a;
            a = NULL;
        }
    }
    Array& operator =(Array& arr); //оператор присвоения ++
    int& operator [](int i);// оператор взятия индекса ++
    bool Test(); // проверка на упорядоченность++
    bool operator == (Array arr); // оператор равенства недоделана
    void Shell_sort(); //сортировка Шелла
    void HeapSort(); //Пирамидальная сортировка
    void Hoar_Sort(); // Сортировка Хоара
    void Bit_sort(); //Побитовая сортировка
    friend istream& operator >> (istream& is, Array& a); //оператор ввод ++
    friend ostream& operator << (ostream& os, Array& a); //оператор вывод ++
};
//конструктор 1
Array::Array(size_t len, int t, int min_d, int max_d) {
    if (len > 0) { // проверка длины массива
        if (max_d > min_d) { //проверка правильного диапазона
            a = new int[len]; //выделяем память
            if (a != nullptr) {
                this->n = len; // Инициализируем длину
                srand(time(NULL));
                if (t == 1) {
                    for (int i = 0; i < len; i++) {
                        a[i] = min_d + rand() % (max_d - min_d + 1);
                    }
                }
                else if (t == 2) {
                    a[0] = min_d + rand() % max_d; // первый элемент >= мин
                    for (int i = 1; i < len; i++) {
                        a[i] = a[i - 1] + rand() % max_d; // каждый следующий >= предыдущего
                    }
                }
                else if (t == 3) {
                    a[0] = max_d - rand() % min_d; // первый элемент <= max
                    for (int i = 1; i < len; i++) {
                        a[i] = a[i - 1] - rand() % min_d; // каждый следующий <= предыдущего
                    }
                }
                else {
                    cout << "Incorrect order!!!\n";
                }
            }
        }
        else {
            cout << "Incorrect diapozon!!!\n";
        }
    }
}
//конструктор 2
Array:: Array(int *arr, size_t l){
    if(arr != nullptr){
        a = new int[l];
        if(a != nullptr){
            this -> n = l;
            for(int i = 0; i < l; i++){
                a[i] = arr[i];
            }
        }
    }
}
//конструктор копированипя
Array::Array(Array &arr) {
    n = arr.n;
    a = new int[n];
    if (a != nullptr) {
        for (int i = 0; i < n; i++) {
            a[i] = arr[i];
        }
    }
}
//оператор присвоения
Array &Array::operator =(Array& arr){
    if(this != &arr){
        delete[] a;
        n = arr.n;
        a = new int[n];
        if(a){
            for(int i = 0; i < n; i++){
                a[i] = arr[i];
            }
        }
    }
    return *this;
}
//взятие индекса
int &Array::operator[](int i){
    if(i < 0 || i < n){
        std::cout << "\nIndex outside the array!!!" << "\n";
        return a[0];
    }
    return a[i];
}
//проверка на неупорядоченность
bool Array::Test(){
    for(int i = 0; i < n - 1;i++){
        if(a[i] > a[i+1]){
            return false;
        }
    }
    return true;
}
//оператор равенства
bool Array::operator == (Array arr){//массивы равны если у них одинаковые элементы
    if(n != arr.n){
        return false;
    }
    int i = 0;
    while(i < arr.n){
        bool flag = false;
        for (int j = 0; j < n; j++){
            if(arr.a[i] == a[j]){
                arr.a[i] = arr.a[arr.n - 1];
                arr.n--;
                flag = true;
                break;
            }
        }
        if(!flag){
            return false;
        }
        i++;
    }
    return true;
}


/*istream& operator>>(istream& is, Array &a) { //дружественный ввод
    int len;
    cout << "Enter the size of the array: ";
    cin >> len;

    while (is.fail()) {
        cerr << "Invalid input for array size!";
        is.clear();
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        is >> len;
    }
    delete[] a.a;
    a.n = len;
    a.a = new int[len];
    if (a.a) {
        for (int i = 0; i < len; i++) {
            cout << "Enter element " << i << ": ";
            is >> a[i];
            while (is.fail()) {
                cerr << "Invalid input for array element!";
                is.clear();
                is.ignore(numeric_limits<streamsize>::max(), '\n');
                is >> a[i];
            }
        }
    }
    return is;
}
*/
ostream &operator<<(ostream &os, Array& a) { //дружественный вывод
    for (int i = 0; i < a.n; i++) {
        os << a.a[i] << " ";
    }
    os << "\n";
    return os;
}

int main()
{
    Array Array1(200, 1, 0, 50);
    cout << "Array 1:{ " << Array1 << "\n";
    cout << "==========================" << "\n";
    int arrr[5] = {2,4,7,90,45};
    Array Array2(arrr, 5);
    cout << "Array 2: " << Array2 << "\n";
    cout << "==========================" << "\n";

}
