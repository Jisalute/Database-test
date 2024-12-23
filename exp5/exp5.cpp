#include <iostream>
#include <ctime>
#include <algorithm>

// 起泡排序
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 插入排序
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 选择排序
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

// 归并排序
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// 快速排序
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 堆排序
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest!= i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// 打印数组
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

// 测试排序算法性能
void testSortingAlgorithms() {
    // 顺序数组
    int sortedArr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int sortedSize = sizeof(sortedArr) / sizeof(sortedArr[0]);

    std::cout << "顺序数组为: ";
    printArray(sortedArr, sortedSize);

    int sortedArr1[sortedSize];
    std::copy(sortedArr, sortedArr + sortedSize, sortedArr1);
    int sortedArr2[sortedSize];
    std::copy(sortedArr, sortedArr + sortedSize, sortedArr2);
    int sortedArr3[sortedSize];
    std::copy(sortedArr, sortedArr + sortedSize, sortedArr3);
    int sortedArr4[sortedSize];
    std::copy(sortedArr, sortedArr + sortedSize, sortedArr4);
    int sortedArr5[sortedSize];
    std::copy(sortedArr, sortedArr + sortedSize, sortedArr5);
    int sortedArr6[sortedSize];
    std::copy(sortedArr, sortedArr + sortedSize, sortedArr6);

    clock_t start, end;

    start = clock();
    bubbleSort(sortedArr1, sortedSize);
    end = clock();
    std::cout << "顺序数组 - 起泡排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "顺序数组 - 起泡排序后数组: ";
    printArray(sortedArr1, sortedSize);

    start = clock();
    insertionSort(sortedArr2, sortedSize);
    end = clock();
    std::cout << "顺序数组 - 插入排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "顺序数组 - 插入排序后数组: ";
    printArray(sortedArr2, sortedSize);

    start = clock();
    selectionSort(sortedArr3, sortedSize);
    end = clock();
    std::cout << "顺序数组 - 选择排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "顺序数组 - 选择排序后数组: ";
    printArray(sortedArr3, sortedSize);

    start = clock();
    mergeSort(sortedArr4, 0, sortedSize - 1);
    end = clock();
    std::cout << "顺序数组 - 归并排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "顺序数组 - 归并排序后数组: ";
    printArray(sortedArr4, sortedSize);

    start = clock();
    quickSort(sortedArr5, 0, sortedSize - 1);
    end = clock();
    std::cout << "顺序数组 - 快速排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "顺序数组 - 快速排序后数组: ";
    printArray(sortedArr5, sortedSize);

    start = clock();
    heapSort(sortedArr6, sortedSize);
    end = clock();
    std::cout << "顺序数组 - 堆排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "顺序数组 - 堆排序后数组: ";
    printArray(sortedArr6, sortedSize);

    // 逆序数组
    int reversedArr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int reversedSize = sizeof(reversedArr) / sizeof(reversedArr[0]);

    std::cout << "逆序数组为: ";
    printArray(reversedArr, reversedSize);

    int reversedArr1[reversedSize];
    std::copy(reversedArr, reversedArr + reversedSize, reversedArr1);
    int reversedArr2[reversedSize];
    std::copy(reversedArr, reversedArr + reversedSize, reversedArr2);
    int reversedArr3[reversedSize];
    std::copy(reversedArr, reversedArr + reversedSize, reversedArr3);
    int reversedArr4[reversedSize];
    std::copy(reversedArr, reversedArr + reversedSize, reversedArr4);
    int reversedArr5[reversedSize];
    std::copy(reversedArr, reversedArr + reversedSize, reversedArr5);
    int reversedArr6[reversedSize];
    std::copy(reversedArr, reversedArr + reversedSize, reversedArr6);

    start = clock();
    bubbleSort(reversedArr1, reversedSize);
    end = clock();
    std::cout << "逆序数组 - 起泡排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "逆序数组 - 起泡排序后数组: ";
    printArray(reversedArr1, reversedSize);

    start = clock();
    insertionSort(reversedArr2, reversedSize);
    end = clock();
    std::cout << "逆序数组 - 插入排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "逆序数组 - 插入排序后数组: ";
    printArray(reversedArr2, reversedSize);

    start = clock();
    selectionSort(reversedArr3, reversedSize);
    end = clock();
    std::cout << "逆序数组 - 选择排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "逆序数组 - 选择排序后数组: ";
    printArray(reversedArr3, reversedSize);

    start = clock();
    mergeSort(reversedArr4, 0, reversedSize - 1);
    end = clock();
    std::cout << "逆序数组 - 归并排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "逆序数组 - 归并排序后数组: ";
    printArray(reversedArr4, reversedSize);

    start = clock();
    quickSort(reversedArr5, 0, reversedSize - 1);
    end = clock();
    std::cout << "逆序数组 - 快速排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "逆序数组 - 快速排序后数组: ";
    printArray(reversedArr5, reversedSize);

    start = clock();
    heapSort(reversedArr6, reversedSize);
    end = clock();
    std::cout << "逆序数组 - 堆排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "逆序数组 - 堆排序后数组: ";
    printArray(reversedArr6, reversedSize);

    // 乱序数组
    int randomArr[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    int randomSize = sizeof(randomArr) / sizeof(randomArr[0]);

    std::cout << "乱序数组为: ";
    printArray(randomArr, randomSize);

    int randomArr1[randomSize];
    std::copy(randomArr, randomArr + randomSize, randomArr1);
    int randomArr2[randomSize];
    std::copy(randomArr, randomArr + randomSize, randomArr2);
    int randomArr3[randomSize];
    std::copy(randomArr, randomArr + randomSize, randomArr3);
    int randomArr4[randomSize];
    std::copy(randomArr, randomArr + randomSize, randomArr4);
    int randomArr5[randomSize];
    std::copy(randomArr, randomArr + randomSize, randomArr5);
    int randomArr6[randomSize];
    std::copy(randomArr, randomArr + randomSize, randomArr6);

    start = clock();
    bubbleSort(randomArr1, randomSize);
    end = clock();
    std::cout << "乱序数组 - 起泡排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "乱序数组 - 起泡排序后数组: ";
    printArray(randomArr1, randomSize);

    start = clock();
    insertionSort(randomArr2, randomSize);
    end = clock();
    std::cout << "乱序数组 - 插入排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "乱序数组 - 插入排序后数组: ";
    printArray(randomArr2, randomSize);

    start = clock();
    selectionSort(randomArr3, randomSize);
    end = clock();
    std::cout << "乱序数组 - 选择排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "乱序数组 - 选择排序后数组: ";
    printArray(randomArr3, randomSize);

    start = clock();
    mergeSort(randomArr4, 0, randomSize - 1);
    end = clock();
    std::cout << "乱序数组 - 归并排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "乱序数组 - 归并排序后数组: ";
    printArray(randomArr4, randomSize);

    start = clock();
    quickSort(randomArr5, 0, randomSize - 1);
    end = clock();
    std::cout << "乱序数组 - 快速排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "乱序数组 - 快速排序后数组: ";
    printArray(randomArr5, randomSize);

    start = clock();
    heapSort(randomArr6, randomSize);
    end = clock();
    std::cout << "乱序数组 - 堆排序时间: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
    std::cout << "乱序数组 - 堆排序后数组: ";
    printArray(randomArr6, randomSize);
}

int main() {
    testSortingAlgorithms();
    return 0;
}