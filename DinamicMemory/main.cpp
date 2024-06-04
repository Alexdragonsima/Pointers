#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab		"\t"
int index;

template<typename T>T** Allocate(const int rows, const int cols);
template<typename T>void Clear(T** arr, const int rows);

void FillRand(int    arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(double arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(char   arr[], const int n, int minRand = 0, int maxRand = 100);

void FillRand(int**    arr, const int rows, const int cols, int minRand = 0, int maxRand = 100);
void FillRand(double** arr, const int rows, const int cols, int minRand = 0, int maxRand = 100);

template<typename T>void Print(T   arr[], const int n);
template<typename T>void Print(T** arr,   const int rows, const int cols);

template<typename T>T* push_back (T arr[], int& n, const T value);
template<typename T>T* push_front(T arr[], int& n, const T value);
template<typename T>T* insert    (T arr[], int& n, const T value, const int index);

template<typename T>T* pop_back (T arr[], int& n);
template<typename T>T* pop_front(T arr[], int& n);
template<typename T>T* erase    (T arr[], int& n, const int index);

template<typename T>T** push_row_back (T** arr, int& rows, const int cols);
template<typename T>T** push_row_front(T** arr, int& rows, const int cols);
template<typename T>T** insert_row    (T** arr, int& rows, const int cols, int position);

template<typename T>T**  pop_row_back  (T** arr, int& rows,const int cols);

template<typename T>void push_col_back (T** arr, const int rows, int& cols);
template<typename T>void push_col_front (T** arr, const int rows, int& cols);
template<typename T>void insert_col (T** arr, const int rows, int& cols,int index);


//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2
//#define PERFORMANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");

	typedef double DataType; //директива создает псевдоним дл€ существуещего типа данных
#ifdef DYNAMIC_MEMORY_1
	//			new
	int n = 5;
	cout << "¬ведите размер массива: "; cin >> n;


	DataType* arr = new DataType[n];

	FillRand(arr, n);
	Print(arr, n);

	DataType value;
	cout << "¬ведите добавл€емое значение: "; cin >> value;
	arr = push_back(arr, n, value);
	Print(arr, n);

	cout << "¬ведите добавл€емое значение: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	int index;
	cout << "¬ведите индекс добовл€емого значени€: "; cin >> index;
	cout << "¬ведите добавл€емое значение: "; cin >> value;
	arr = insert(arr, n, value, index);
	Print(arr, n);

	arr = pop_back(arr, n);
	Print(arr, n);

	arr = pop_front(arr, n);
	Print(arr, n);

	cout << "¬ведите индекс удол€емого значени€: "; cin >> index;
	arr = erase(arr, n, index);
	Print(arr, n);

	delete[] arr;
	// Memory leaks  
#endif // DYNAMIC_MEMORY_1

#ifdef DYNAMIC_MEMORY_2
	int rows;
	int cols;
	cout << "¬ведите колво строк: ";            cin >> rows;
	cout << "¬ведите колво элементов строки: "; cin >> cols;

	DataType** arr = Allocate<DataType>(rows, cols);
	//double** arr = new double* [rows];
	//for (int i = 0; i < rows; i++)
	//{
	//	arr[i] = new double[cols];
	//}

	FillRand(arr, rows, cols);
	Print   (arr, rows, cols);
	
	arr = push_row_back(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 100, 1000);
	Print   (arr, rows, cols);
	
	arr = push_row_front(arr, rows, cols);
	FillRand(arr[0], cols, 100, 1000);
	Print   (arr, rows, cols);
	
	int index;
	cout << "¬ведите позицию добовл€емой строки: "; cin >> index;
	arr = insert_row(arr, rows, cols, index);
	if (index < rows)FillRand(arr[index], cols, 100, 1000);
	Print(arr, rows, cols);
	
	arr = pop_row_back(arr, rows, cols);
	Print(arr, rows, cols);
	
	push_col_back(arr, rows, cols);
	Print        (arr, rows, cols);

	push_col_front(arr, rows, cols);
	Print(arr, rows, cols);

	cout << "¬ведите позицию добавл€емого столбца :"; cin >> index;
	insert_col(arr, rows, cols, index);
	Print(arr, rows, cols);

	Clear(arr, rows);
#endif // DYNAMIC_MEMORY_2

#ifdef PERFORMANCE_CHECK

	int rows;
	int cols;
	cout << "¬ведите колво строк: "; cin >> rows;
	cout << "¬ведите колво элементов строки: "; cin >> cols;

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
	///объ€вление двумерного динамического массива////
	/////////////////////////////////////////////////

	//1)создаем массив указателей
	int** arr = new int* [rows];

	//2)выдел€ем пам€ть под строки
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

	//1)удал€ем строки
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	//2)удал€ем массив указателей
	delete[] arr;
#endif // SYNTAX

}

template<typename T>T** Allocate(const int rows, const int cols)
{
	T** arr = new T* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new T[cols];
	}
	return arr;
}

template<typename T>void Clear(T** arr, const int rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}

void FillRand(int    arr[], const int n, int minRand, int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
		//ќбращение к элементам массива через арифметику указателейи оператор разименовани€
	}
}
void FillRand(double arr[], const int n, int minRand, int maxRand)
{
	minRand *= 100;
	maxRand *= 100;
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
		//ќбращение к элементам массива через арифметику указателейи оператор разименовани€
		*(arr + i) /= 100;
	}
}
void FillRand(char   arr[], const int n, int minRand, int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand();
		//ќбращение к элементам массива через арифметику указателейи оператор разименовани€
	}
}
void FillRand(int**    arr, const int rows, const int cols, int minRand, int maxRand)
{
	for (int i = 0; i < rows; i++)
	{
		FillRand(arr[i], cols, minRand, maxRand);
	}
}
void FillRand(double** arr, const int rows, const int cols, int minRand, int maxRand)
{
	for (int i = 0; i < rows; i++)
	{
		FillRand(arr[i], cols, minRand, maxRand);
	}
}

template<typename T>void Print(T   arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << tab;
		//ќбращение к элементам массива через оператор индексировани€ []
	}
	cout << endl;
}
template<typename T>void Print(T** arr,   const int rows, const int cols)
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

template<typename T>T* push_back (T arr[], int& n, const T value)
{
	T* buffer = new T[n + 1];
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	arr = buffer;
	arr[n] = value;
	n++;
	return buffer;
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
template<typename T>T* insert    (T arr[], int& n, const T value, const int index)
{
	if (index >= n)return arr;
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

template<typename T>T* pop_back (T arr[], int& n)
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
template<typename T>T* erase    (T arr[], int& n, const int index)
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

template<typename T>T** push_row_back (T** arr, int& rows, const int cols)
{
	return push_back(arr, rows, new T[cols]{});
}
template<typename T>T** push_row_front(T** arr, int& rows, const int cols)
{
	return push_front(arr, rows, new T[cols]{});
}
template<typename T>T** insert_row    (T** arr, int& rows, const int cols, int position)
{
	return insert(arr, rows, new T[cols], index);
}

template<typename T>T** pop_row_back  (T** arr, int& rows, const int cols)
{
	delete[] arr[rows-1];
	return pop_back(arr, rows);
}

template<typename T>void push_col_back(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		arr[i] = push_back(arr[i], cols, T());
		cols--;
	}
	cols++;
}
template<typename T>void push_col_front(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		arr[i] = push_front(arr[i], cols, T());
		cols--;
	}
	cols++;
}

template<typename T>void insert_col(T** arr, const int rows, int& cols,int index)
{
	for (int i = 0; i < rows; i++)
	{
		arr[i] = insert(arr[i], cols, T(), index);
		cols--;
	}
	cols++;
}