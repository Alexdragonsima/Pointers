#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab		"\t"

int** Allocate(const int rows, const int cols);
void Clear(int** arr, const int rows);

void FillRand(int arr[], const int n,int minRand=0,int maxRand=100);
void FillRand(int** arr, const int rows, const int cols);

void Print(int arr[], const int n);
void Print(int** arr, const int rows, const int cols);

int* push_back(int arr[],int& n,const int value);
int* push_front(int arr[], int& n, const int value);
int* insert(int arr[], int& n, const int value, const int index);

int* pop_back(int arr[], int& n);
int* pop_front(int arr[], int& n);
int* erase(int arr[], int& n, const int index);

int** push_row_back(int** arr, int& rows, const int cols);
int** push_row_front(int** arr, int& rows, const int cols);
int** insert_row(int** arr, int& rows, const int cols,int position);

int** pop_row_back(int** arr, int& rows, const int cols);

void push_col_back(int** arr, const int rows, int& cols);

//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2
//#define PERFORMANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef DYNAMIC_MEMORY_1
	//			new
	int n = 5;
	cout << "¬ведите размер массива: "; cin >> n;
	int* arr = new int[n];

	FillRand(arr, n);
	Print(arr, n);

	int value;
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
	cout << "¬ведите колво строк: "; cin >> rows;
	cout << "¬ведите колво элементов строки: "; cin >> cols;
	
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
	cout << "¬ведите позицию добовл€емой строки: "; cin >> index;
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
	cout << "¬ведите колво строк: "; cin >> rows;
	cout << "¬ведите колво элементов строки: "; cin >> cols;

	int** arr = Allocate(rows, cols);
	cout << "emoty allocated" << endl;
	FillRand(arr, rows, cols);
	cout<<" data loa"
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

void FillRand(int arr[], const int n,int minRand,int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand;
		//ќбращение к элементам массива через арифметику указателейи оператор разименовани€
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

void Print(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << tab;
		//ќбращение к элементам массива через оператор индексировани€ []
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

int* push_back(int arr[],int& n, const int value)
{
	//1)создаем буферный массив нужного размера
	int* buffer = new int[n + 1];
	//2)копируем значени€ исходного массива в буферный
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	//3)удал€ем исходный массив
	delete[] arr;
	//4)подмен€ем адрес в указателе arr адресом нового массива
	int a = 2;
	int b = 3;
	a = b;
	arr = buffer;
	//5)только после всего этого можно добавить значение в конец массива
	arr[n] = value;
	//6)после добаавлени€ элимента в конеуц массива колво его элементов увеличиваетс€ на 1
	n++;
	return arr;
}

int* push_front(int arr[], int& n, const int value)
{
	int* buffer = new int[n + 1];
	for (int i = 0; i < n; i++)buffer[i + 1] = arr[i];
	delete[] arr;
	buffer[0] = value;
	n++;
	return buffer;
}

int* insert(int arr[], int& n, const int value, const int index)
{
	int* buffer = new int[n + 1];
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

int* pop_back(int arr[], int& n)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}

int* pop_front(int arr[], int& n)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}

int* erase(int arr[], int& n, const int index)
{
	int* buffer = new int[--n];
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
	//3)удал€ем исходный массив
	delete[] arr;
	//4)создаем новую строку и помещаем ее в конец массива
	buffer[rows] = new int[cols] {};
	//5)после добавлни€ строки колво строк увеличиваетс€ на 1
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