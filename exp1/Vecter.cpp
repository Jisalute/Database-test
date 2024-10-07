#ifndef VECTOR_CPP
#define VECTOR_CPP

#include "Vectors.h"
#include <stdexcept> 

template <typename T>
class Vectors {
protected:
    int _size;
    int _capacity;
    T* _elem;

    void copyFrom(const T* A, int lo, int hi) {
        _elem = new T[_capacity = 2 * (hi - lo)];
        _size = 0;
        while (lo < hi) {
            _elem[_size++] = A[lo++];
        }
    }

    void expand() {
        if (_size < _capacity) return;
        _capacity = std::max(_capacity, 1);
        T* oldElem = _elem;
        _elem = new T[_capacity <<= 1];
        for (int i = 0; i < _size; ++i) {
            _elem[i] = oldElem[i];
        }
        delete[] oldElem;
    }

    void shrink() {
        if (_capacity < _size << 2) return;
        T* oldElem = _elem;
        _elem = new T[_capacity >>= 1];
        for (int i = 0; i < _size; ++i) {
            _elem[i] = oldElem[i];
        }
        delete[] oldElem;
    }

    bool bubble(int lo, int hi) {
        bool sorted = true;
        for (int i = lo; i < hi - 1; ++i) {
            if (_elem[i] > _elem[i + 1]) {
                std::swap(_elem[i], _elem[i + 1]);
                sorted = false;
            }
        }
        return sorted;
    }

    void bubbleSort(int lo, int hi) {
        while (!bubble(lo, hi--));
    }

    int max(int lo, int hi) {
        int maxIndex = lo;
        for (int i = lo + 1; i < hi; ++i) {
            if (_elem[i] > _elem[maxIndex]) {
                maxIndex = i;
            }
        }
        return maxIndex;
    }

    void selectionSort(int lo, int hi) {
        for (int i = lo; i < hi - 1; ++i) {
            int j = max(i, hi);
            if (j!= i) {
                std::swap(_elem[i], _elem[j]);
            }
        }
    }

    void merge(int lo, int mi, int hi) {
        T* A = _elem + lo;
        int lb = mi - lo;
        T* B = new T[lb];
        for (int i = 0; i < lb; ++i) {
            B[i] = A[i];
        }
        int lc = hi - mi;
        T* C = _elem + mi;
        for (int i = 0, j = 0, k = 0; j < lb; ) {
            if ((k < lc) && (C[k] < B[j])) {
                A[i++] = C[k++];
            } else {
                A[i++] = B[j++];
            }
        }
        delete[] B;
    }

    void mergeSort(int lo, int hi) {
        if (hi - lo < 2) return;
        int mi = (lo + hi) / 2;
        mergeSort(lo, mi);
        mergeSort(mi, hi);
        merge(lo, mi, hi);
    }

    int partition(int lo, int hi) {
        std::swap(_elem[lo], _elem[lo + rand() % (hi - lo)]);
        T pivot = _elem[lo];
        int mi = lo;
        for (int k = lo + 1; k < hi; ++k) {
            if (_elem[k] < pivot) {
                std::swap(_elem[++mi], _elem[k]);
            }
        }
        std::swap(_elem[lo], _elem[mi]);
        return mi;
    }

    void quickSort(int lo, int hi) {
        if (hi - lo < 2) return;
        int mi = partition(lo, hi);
        quickSort(lo, mi);
        quickSort(mi + 1, hi);
    }



public:
    // 构造函数
    Vectors(int c = 3, int s = 0, T v = T()) {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    }



    Vectors(const Vectors<T>& V, int lo, int hi) {
        copyFrom(V._elem, lo, hi);
    }

    // 析构函数
    ~Vectors() {
        delete[] _elem;
    }

    // 只读访问接口
    int size() const {
        return _size;
    }

    bool empty() const {
        return!_size;
    }

    int disordered() const {
        for (int i = 1; i < _size; ++i) {
            if (_elem[i - 1] > _elem[i]) {
                return 1;
            }
        }
        return 0;
    }

    int find(const T& e) const {
        return find(e, 0, _size);
    }

    int find(const T& e, int lo, int hi) const {
        for (int i = lo; i < hi; ++i) {
            if (_elem[i] == e) {
                return i;
            }
        }
        return -1;
    }

    int search(const T& e) const {
        return (0 >= _size)? -1 : search(e, 0, _size);
    }



    // 可写访问接口
    T& operator[](int r) const {
        return _elem[r];
    }

    Vectors<T>& operator=(const Vectors<T>& V) {
        if (_elem) delete[] _elem;
        copyFrom(V._elem, 0, V._size);
        return *this;
    }

    T remove(int r) {
        T e = _elem[r];
        remove(r, r + 1);
        return e;
    }

    int remove(int lo, int hi) {
        if (lo == hi) return 0;
        while (hi < _size) {
            _elem[lo++] = _elem[hi++];
        }
        _size = lo;
        shrink();
        return hi - lo;
    }

    int insert(int r, const T& e) {
        expand();
        for (int i = _size; i > r; --i) {
            _elem[i] = _elem[i - 1];
        }
        _elem[r] = e;
        _size++;
        return r;
    }

    int insert(const T& e) {
        return insert(_size, e);
    }

    void sort(int lo, int hi) {
        mergeSort(lo, hi);
    }

    void sort() {
        sort(0, _size);
    }

    void unsort(int lo, int hi) {
        std::random_shuffle(_elem + lo, _elem + hi);
    }

    void unsort() {
        unsort(0, _size);
    }

    int deduplicate() {
        int oldSize = _size;
        int i = 1;
        while (i < _size) {
            (find(_elem[i], 0, i) < 0)? i++ : remove(i);
        }
        return oldSize - _size;
    }

    int uniquify() {
        int i = 0, j = 0;
        while (++j < _size) {
            if (_elem[i]!= _elem[j]) {
                _elem[++i] = _elem[j];
            }
        }
        _size = ++i;
        shrink();
        return j - i;
    }

    // 遍历
    void traverse(void (*visit)(T&)) {
        for (int i = 0; i < _size; ++i) {
            visit(_elem[i]);
        }
    }

    template <typename VST>
    void traverse(VST& visit) {
        for (int i = 0; i < _size; ++i) {
            visit(_elem[i]);
        }
    }
};
#endif 