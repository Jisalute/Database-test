#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    double modulus() const {
        return std::sqrt(real * real + imag * imag);
    }
};

// 随机生成复数向量
std::vector<Complex> generateRandomComplexVector(int size) {
    std::vector<Complex> v;
    for (int i = 0; i < size; ++i) {
        double realPart = static_cast<double>(rand()) / RAND_MAX * 10;
        double imagPart = static_cast<double>(rand()) / RAND_MAX * 10;
        v.push_back(Complex(realPart, imagPart));
    }
    return v;
}

// 置乱向量
void shuffleComplexVector(std::vector<Complex>& v) {
    for (int i = v.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(v[i], v[j]);
    }
}

// 查找复数
bool findComplex(const std::vector<Complex>& v, const Complex& c) {
    for (const Complex& complex : v) {
        if (complex.real == c.real && complex.imag == c.imag) {
            return true;
        }
    }
    return false;
}

// 插入复数
void insertComplex(std::vector<Complex>& v, const Complex& c) {
    v.push_back(c);
}

// 删除复数
void deleteComplex(std::vector<Complex>& v, const Complex& c) {
    std::vector<Complex>::iterator it = v.begin();
    while (it!= v.end()) {
        if (*it == c) {
            it = v.erase(it);
        } else {
            ++it;
        }
    }
}

// 唯一化向量
void uniqueComplexVector(std::vector<Complex>& v) {
    std::sort(v.begin(), v.end(), [](const Complex& a, const Complex& b) {
        if (a.real!= b.real) return a.real < b.real;
        return a.imag < b.imag;
    });
    v.erase(std::unique(v.begin(), v.end()), v.end());
}

// 比较函数用于排序
bool compareComplex(const Complex& a, const Complex& b) {
    double modA = a.modulus();
    double modB = b.modulus();
    if (modA!= modB) return modA < modB;
    return a.real < b.real;
}

// 起泡排序
void bubbleSort(std::vector<Complex>& v) {
    int n = v.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (!compareComplex(v[j], v[j + 1])) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}

// 归并函数
void merge(std::vector<Complex>& v, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<Complex> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = v[left + i];
    for (int j = 0; j < n2; ++j) R[j] = v[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compareComplex(L[i], R[j])) {
            v[k] = L[i];
            ++i;
        } else {
            v[k] = R[j];
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        v[k] = L[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        v[k] = R[j];
        ++j;
        ++k;
    }
}

// 归并排序
void mergeSort(std::vector<Complex>& v, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(v, left, mid);
        mergeSort(v, mid + 1, right);
        merge(v, left, mid, right);
    }
}

// 区间查找
std::vector<Complex> rangeSearch(const std::vector<Complex>& v, double m1, double m2) {
    std::vector<Complex> result;
    for (const Complex& c : v) {
        double mod = c.modulus();
        if (mod >= m1 && mod < m2) {
            result.push_back(c);
        }
    }
    return result;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int vectorSize = 10;
    std::vector<Complex> complexVector = generateRandomComplexVector(vectorSize);

    // 置乱向量
    shuffleComplexVector(complexVector);
    std::cout << "After shuffling:\n";
    for (const Complex& c : complexVector) {
        std::cout << c.real << " + " << c.imag << "i\n";
    }

    // 查找复数
    Complex toFind(3.5, 2.2);
    bool found = findComplex(complexVector, toFind);
    std::cout << "Is " << toFind.real << " + " << toFind.imag << "i found? " << (found? "Yes" : "No") << "\n";

    // 插入复数
    Complex toInsert(4.4, 3.3);
    insertComplex(complexVector, toInsert);
    std::cout << "After insertion:\n";
    for (const Complex& c : complexVector) {
        std::cout << c.real << " + " << c.imag << "i\n";
    }

    // 删除复数
    Complex toDelete(4.4, 3.3);
    deleteComplex(complexVector, toDelete);
    std::cout << "After deletion:\n";
    for (const Complex& c : complexVector) {
        std::cout << c.real << " + " << c.imag << "i\n";
    }

    // 唯一化向量
    uniqueComplexVector(complexVector);
    std::cout << "After unique:\n";
    for (const Complex& c : complexVector) {
        std::cout << c.real << " + " << c.imag << "i\n";
    }

    // 排序效率比较
    std::vector<Complex> sortedVector = complexVector;
    std::vector<Complex> reversedVector = complexVector;
    std::reverse(reversedVector.begin(), reversedVector.end());
    std::vector<Complex> randomVector = complexVector;
    shuffleComplexVector(randomVector);

    clock_t startBubbleSorted = clock();
    bubbleSort(sortedVector);
    clock_t endBubbleSorted = clock();

    clock_t startBubbleReversed = clock();
    bubbleSort(reversedVector);
    clock_t endBubbleReversed = clock();

    clock_t startBubbleRandom = clock();
    bubbleSort(randomVector);
    clock_t endBubbleRandom = clock();

    clock_t startMergeSorted = clock();
    mergeSort(sortedVector, 0, sortedVector.size() - 1);
    clock_t endMergeSorted = clock();

    clock_t startMergeReversed = clock();
    mergeSort(reversedVector, 0, reversedVector.size() - 1);
    clock_t endMergeReversed = clock();

    clock_t startMergeRandom = clock();
    mergeSort(randomVector, 0, randomVector.size() - 1);
    clock_t endMergeRandom = clock();

    double bubbleSortedTime = static_cast<double>(endBubbleSorted - startBubbleSorted) / CLOCKS_PER_SEC;
    double bubbleReversedTime = static_cast<double>(endBubbleReversed - startBubbleReversed) / CLOCKS_PER_SEC;
    double bubbleRandomTime = static_cast<double>(endBubbleRandom - startBubbleRandom) / CLOCKS_PER_SEC;
    double mergeSortedTime = static_cast<double>(endMergeSorted - startMergeSorted) / CLOCKS_PER_SEC;
    double mergeReversedTime = static_cast<double>(endMergeReversed - startMergeReversed) / CLOCKS_PER_SEC;
    double mergeRandomTime = static_cast<double>(endMergeRandom - startMergeRandom) / CLOCKS_PER_SEC;

    std::cout << "Bubble sort time for sorted vector: " << bubbleSortedTime << " seconds.\n";
    std::cout << "Bubble sort time for reversed vector: " << bubbleReversedTime << " seconds.\n";
    std::cout << "Bubble sort time for random vector: " << bubbleRandomTime << " seconds.\n";
    std::cout << "Merge sort time for sorted vector: " << mergeSortedTime << " seconds.\n";
    std::cout << "Merge sort time for reversed vector: " << mergeReversedTime << " seconds.\n";
    std::cout << "Merge sort time for random vector: " << mergeRandomTime << " seconds.\n";

    // 区间查找
    double m1 = 2.0, m2 = 5.0;
    std::vector<Complex> subVector = rangeSearch(complexVector, m1, m2);
    std::cout << "Complex numbers with modulus between " << m1 << " and " << m2 << ":\n";
    for (const Complex& c : subVector) {
        std::cout << c.real << " + " << c.imag << "i\n";
    }

    return 0;
}