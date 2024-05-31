#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab		"\t"

int** Allocate(const int rows, const int cols);
void Clear(int** arr, const int rows);

void FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(double arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(char arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(int** arr, const int rows, const int cols);

template<typename T>void Print(T arr[], const int n);
void Print(int** arr, const int rows, const int cols);

template<typename T>T* push_back(T arr[], int& n, const T value);
template<typename T>T* push_front(T arr[], int& n, const T value);
template<typename T>T* insert(T arr[], int& n, const T value, const int index);

template<typename T>T* pop_back(T arr[], int& n);
template<typename T>T* pop_front(T arr[], int& n);
template<typename T>T* erase(T arr[], int& n, const int index);

int** push_row_back(int** arr, int& rows, const int cols);
int** push_row_front(int** arr, int& rows, const int cols);
int** insert_row(int** arr, int& rows, const int cols, int position);

int** pop_row_back(int** arr, int& rows, const int cols);

void push_col_back(int** arr, const int rows, int& cols);

#define DYNAMIC_MEMORY_1
//#define DYNAMIC_MEMORY_2
//#define PERFORMANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef DYNAMIC_MEMORY_1
	//			new
	int n = 5;
	cout << "Введите размер массива: "; cin >> n;

	typedef double DataType; //директива создает псевдоним для существуещего типа данных

	DataType* arr = new DataType[n];

	FillRand(arr, n);
	Print(arr, n);

	DataType value;
	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_back(arr, n, value);
	Print(arr, n);

	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	int index;
	cout << "Введите индекс добовляемого значения: "; cin >> index;
	cout << "Введите добавляемое значение: "; cin >> value;
	arr = insert(arr, n, value, index);
	Print(arr, n);

	arr = pop_back(arr, n);
	Print(arr, n);

	arr = pop_front(arr, n);
	Print(arr, n);

	cout << "Введите индекс удоляемого значения: "; cin >> index;
	arr = erase(arr, n, index);
	Print(arr, n);

	delete[] arr;
	// Memory leaks  
#endif // DYNAMIC_MEMORY_1

#ifdef DYNAMIC_MEMORY_2
	int rows;
	int cols;
	cout << "Введите колво строк: "; cin >> rows;
	cout << "Введите колво элементов строки: "; cin >> cols;

	int** arr = Allocate(rows, cols);

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	arr = push_row_back(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 100, 1000);
	Print(arr, rows, cols);

	arr = push_row_front(arr, rows, cols);
	FillRand(arr[0], cols, 100, 1000);
	Print(arr, rows, cols);

	int index;
	cout << "Введите позицию добовляемой строки: "; cin >> index;
	arr = insert_row(arr, rows, cols, index);
	if (index < rows)FillRand(arr[index], cols, 100, 1000);
	Print(arr, rows, cols);

	arr = pop_row_back(arr, rows, cols);
	Print(arr, rows, cols);

	push_col_back(arr, rows, cols);
	Print(arr, rows, cols);

	Clear(arr, rows);
#endif // DYNAMIC_MEMORY_2

#ifdef PERFORMANCE_CHECK

	int rows;
	int cols;
	cout << "Введите колво строк: "; cin >> rows;
	cout << "Введите колво элементов строки: "; cin >> cols;

	int** arr = Allocate(rows, cols);
	cout << "emoty allocated" << endl;
	FillRand(arr, rows, cols);
	cout << " data loa"
		arr = push_row_back(arr, rows, cols);
	Print(arr, rows, cols);


	Clear(arr, rows, cols);
#endif // PERFORMANCE_CHECK

#ifdef SYNTAX
	int rows = 3;
	int cols = 4;

	///////////////////////////////////////////////////
	///объявление двумерного динамического массива////
	/////////////////////////////////////////////////

	//1)создаем массив указателей
	int** arr = new int* [rows];

	//2)выделяем память под строки
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[cols];
	}

	//////////////////////////////////////////////////
	///обращение к элементам двумерного массива//////
	////////////////////////////////////////////////

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	///////////////////////////////////////////////////
	///удаление двумерного динамического массива////
	/////////////////////////////////////////////////

	//1)удаляем строки
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	//2)удаляем массив указателей
	delete[] arr;
#endif // SYNTAX

}

int** Allocate(const int rows, const int cols)
{
	int** arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[cols];
	}
	return arr;
}

void Clear(int** arr, const int rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}

void FillRand(int arr[], const int n, int minRand, int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
		//Обращение к элементам массива через арифметику указателейи оператор разименования
	}
}
void FillRand(double arr[], const int n, int minRand, int maxRand)
{
	minRand *= 100;
	maxRand *= 100;
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
		//Обращение к элементам массива через арифметику указателейи оператор разименования
		*(arr + i) /= 100;
	}
}
void FillRand(char arr[], const int n, int minRand, int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand();
		//Обращение к элементам массива через арифметику указателейи оператор разименования
	}
}
void FillRand(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 100;
		}
	}
}

template<typename T>void Print(T arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << tab;
		//Обращение к элементам массива через оператор индексирования []
	}
	cout << endl;
}
void Print(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << tab;
		}
		cout << endl;
	}
	cout << endl;
}

template<typename T>T* push_back(T arr[], int& n, const T value)
{
	//1)создаем буферный массив нужного размера
	T* buffer = new T[n + 1];
	//2)копируем значения исходного массива в буферный
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	//3)удаляем исходный массив
	delete[] arr;
	//4)подменяем адрес в указателе arr адресом нового массива
	int a = 2;
	int b = 3;
	a = b;
	arr = buffer;
	//5)только после всего этого можно добавить значение в конец массива
	arr[n] = value;
	//6)после добаавления элимента в конеуц массива колво его элементов увеличивается на 1
	n++;
	return arr;
}

template<typename T>T* push_front(T arr[], int& n, const T value)
{
	T* buffer = new T[n + 1];
	for (int i = 0; i < n; i++)buffer[i + 1] = arr[i];
	delete[] arr;
	buffer[0] = value;
	n++;
	return buffer;
}

template<typename T>T* insert(T arr[], int& n, const T value, const int index)
{
	T* buffer = new T[n + 1];
	//for (int i = 0; i < index; i++)buffer[i] = arr[i];
	//for (int i = index; i < n; i++)buffer[i + 1] = arr[i];
	for (int i = 0; i < n; i++)
	{
		//if (i < index)buffer[i] = arr[i];
		//else buffer[i + 1] = arr[i];
		//i < index ? buffer[i] = arr[i] : buffer[i + 1] = arr[i];
		buffer[i < index ? i : i + 1] = arr[i];
	}
	delete[] arr;
	buffer[index] = value;
	n++;
	return buffer;
}

template<typename T>T* pop_back(T arr[], int& n)
{
	T* buffer = new T[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}
template<typename T>T* pop_front(T arr[], int& n)
{
	T* buffer = new T[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}
template<typename T>T* erase(T arr[], int& n, const int index)
{
	T* buffer = new T[--n];
	//for (int i = 0; i < index; i++)buffer[i] = arr[i];
	//for (int i = index; i < n; i++)buffer[i] = arr[i + 1];
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i < index ? i : i + 1];
	}
	delete[] arr;
	return buffer;
}

int** push_row_back(int** arr, int& rows, const int cols)
{
	//1)создаем буферный массив указателей нужного размера
	int** buffer = new int* [rows + 1];
	//2)копируем адресса строк из исходного массива указателей в буферный
	for (int i = 0; i < rows; i++)buffer[i] = arr[i];
	//3)удаляем исходный массив
	delete[] arr;
	//4)создаем новую строку и помещаем ее в конец массива
	buffer[rows] = new int[cols] {};
	//5)после добавлния строки колво строк увеличивается на 1
	rows++;
	//6)возвращаем новы массив указателей на место вызова
	return buffer;
}
int** push_row_front(int** arr, int& rows, const int cols)
{
	int** buffer = new int* [rows + 1];
	for (int i = 0; i < rows; i++)buffer[i + 1] = arr[i];
	delete[] arr;
	buffer[0] = new int[cols] {};
	rows++;
	return buffer;
}

int** insert_row(int** arr, int& rows, const int cols, int position)
{
	if (position >= rows)return arr;
	int** buffer = new int* [rows + 1];
	for (int i = 0; i < position; i++)buffer[i] = arr[i];
	for (int i = position; i < rows; i++)buffer[i + 1] = arr[i];
	delete[] arr;
	buffer[position] = new int[cols];
	rows++;
	return buffer;
}

int** pop_row_back(int** arr, int& rows, const int cols)
{
	int** buffer = new int* [--rows];
	for (int i = 0; i < rows; i++)buffer[i] = arr[i];
	delete[] arr[rows];
	delete[] arr;
	return buffer;
}

void push_col_back(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols + 1] {};
		for (int j = 0; j < cols; j++)buffer[j] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols++;
}