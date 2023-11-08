#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void CreateRow(int** a, const int N, const int Low, const int High, int rowNo, int colNo = 0)
{
    if (colNo < N) {
        a[rowNo][colNo] = Low + rand() % (High - Low + 1);
        CreateRow(a, N, Low, High, rowNo, colNo + 1);
    }
}

void CreateRows(int** a, const int N, const int Low, const int High, int rowNo = 0)
{
    if (rowNo < N) {
        CreateRow(a, N, Low, High, rowNo);
        CreateRows(a, N, Low, High, rowNo + 1);
    }
}

void PrintRow(int** a, const int N, int rowNo, int colNo = 0)
{
    if (colNo < N) {
        cout << setw(4) << a[rowNo][colNo];
        PrintRow(a, N, rowNo, colNo + 1);
    }
    else {
        cout << endl;
    }
}

void PrintRows(int** a, const int N, int rowNo = 0)
{
    if (rowNo < N) {
        PrintRow(a, N, rowNo);
        PrintRows(a, N, rowNo + 1);
    }
}

void SearchFirstEven(int** a, const int N, int i, int& minEven, int& k)
{
    if (i < N) {
        if (a[i][N - 1 - i] % 2 == 0) {
            k = i;
            minEven = a[i][N - 1 - i];
        }
        else if (k == -1) {
            SearchFirstEven(a, N, i + 1, minEven, k);
        }
        else {
            SearchMinEven(a, N, i + 1, minEven);
        }
    }
}

void SearchMinEven(int** a, const int N, int i, int& minEven)
{
    if (i < N) {
        if (a[i][N - 1 - i] % 2 == 0 && a[i][N - 1 - i] < minEven) {
            minEven = a[i][N - 1 - i];
        }
        SearchMinEven(a, N, i + 1, minEven);
    }
}

int SumMaxEvenOnEvenRows(int** a, const int N, int i = 0, int sum = 0)
{
    if (i < N) {
        int maxEven = INT_MIN;
        for (int j = 0; j < N; j++) {
            if (a[i][j] % 2 == 0 && a[i][j] > maxEven) {
                maxEven = a[i][j];
            }
        }
        sum += maxEven;
        return SumMaxEvenOnEvenRows(a, N, i + 2, sum);
    }
    return sum;
}

int main()
{
    srand((unsigned)time(NULL));
    int N;
    cout << "N = ";
    cin >> N;
    cout << endl;
    int** a = new int* [N];
    for (int i = 0; i < N; i++) {
        a[i] = new int[N];
    }
    int Low = -9, High = 9;

    CreateRows(a, N, Low, High);
    PrintRows(a, N);

    int k = -1;
    int minEven;

    SearchFirstEven(a, N, 0, minEven, k);

    if (k > -1) {
        SearchMinEven(a, N, k + 1, minEven);
        cout << "minEven = " << minEven << endl;
    }
    else {
        cout << "there are no even elements" << endl;
    }

    int sumMaxEvenOnEvenRowsValue = SumMaxEvenOnEvenRows(a, N);
    cout << "Sum of max even elements on even rows: " << sumMaxEvenOnEvenRowsValue << endl;

    for (int i = 0; i < N; i++) {
        delete[] a[i];
    }
    delete[] a;
    return 0;
}
