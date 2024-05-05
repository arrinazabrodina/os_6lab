#include "first.hpp"

using namespace std;

mutex sharedDataMutex;

int* generateMatrix(int width, int height) {
    cout << "Generating array with width " << width << " and height " << height << endl;
    int* matrix = new int[width * height];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i * width + j] = rand() % 20; // rand() % 20; i*width+j+1
        }
    }

    return matrix;
}

void outputMatrix(int* matrix, int width, int height) {
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << matrix[i * width + j] << "\t";
        }
        cout << endl;
    }
}

void multiplyAtIndex(int index, int n, int m, int k, int* firstArray, int* secondArray, int* resultArray) {
    int row = index / k;
    int col = index % k;

    int currentResult = 0;
    for (int j = 0; j < m; j++) {
        int firstItem = firstArray[j * n + row];
        int secondItem = secondArray[col * m + j];
        currentResult += firstItem * secondItem;
    }
    sharedDataMutex.lock();
    cout << "row: " << row << "; col: " << col << " = " << currentResult << endl;
    resultArray[index] = currentResult;
    sharedDataMutex.unlock();
}

int first() {
    int n, m, k;
#if true
    n = 5;
    m = 10;
    k = 7;
#else
    cout << "Enter n, m, k: " << endl;
    cin >> n >> m >> k;
#endif
    int* firstMatrix = generateMatrix(n, m);
    int* secondMatrix = generateMatrix(m, k);

    cout << "First matrix" << endl;
    outputMatrix(firstMatrix, n, m);
    cout << "Second matrix" << endl;
    outputMatrix(secondMatrix, m, k);

    int* resultMatrix = (int*)calloc(n * k, sizeof(int));

    thread* threads = new thread[n * k];
    double* arrr = new double[n * k];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int index = i * k + j;
            threads[index] = thread(multiplyAtIndex, index, n, m, k, firstMatrix, secondMatrix, resultMatrix);
        }
    }

    for (int i = 0; i < n * k; i++)
    {
        threads[i].join();
    }

    cout << "Result:" << endl;
    outputMatrix(resultMatrix, k, n);

    delete firstMatrix;
    delete secondMatrix;
    return 0;
}