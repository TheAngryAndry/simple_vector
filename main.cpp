#include <algorithm>

template<typename T>
struct Vector {
private:
    int vector_size = 0;
    int actual_size = 0; // степень двойки
    T *data;

    void extend() {
        T *new_data = new T[actual_size * 2];
        actual_size *= 2;
        for (int i = 0; i < vector_size; ++i) {
            new_data[i] = data[i];
        }
        delete [] data;
        data = new_data;
    }

    void retract() {
        T *new_data = new T[actual_size / 2];
        actual_size /= 2;
        for (int i = 0; i < vector_size; ++i) {
            new_data[i] = data[i];
        }
        delete [] data;
        data = new_data;
    }


public:
    explicit Vector() {
        data = new T[1];
        vector_size = 0;
        actual_size = 1;
    }


    explicit Vector(int const size) {
        data = new T[size];
        vector_size = 0;
        actual_size = size;
    }

    explicit Vector(const T *data_, int const size) {
        if (size == 0) {
            data = new T[1];
            vector_size = 0;
            actual_size = 1;
            return;
        }
        vector_size = size;
        actual_size = 1;
        while (actual_size < vector_size) {
            actual_size <<= 1;
        }

        data = new T[actual_size];
        for (int i = 0; i < vector_size; ++i) {
            data[i] = data_[i];
        }
    }

    void push_back(const T val) {
        if (vector_size >= actual_size) {
            extend();
        }
        data[vector_size] = val;
        ++vector_size;
    }

    void pop_back() {
        if (vector_size == 0) {
            return;
        }
        --vector_size;
        if (vector_size * 2 < actual_size && actual_size > 1) {
            retract();
        }
    }

    Vector(const Vector& other) {
        vector_size = other.vector_size;
        actual_size = other.actual_size;
        data = new T[actual_size];
        for (int i = 0; i < vector_size; ++i) {
            data[i] = other.data[i];
        }
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;
        delete[] data;
        vector_size = other.vector_size;
        actual_size = other.actual_size;
        data = new T[actual_size];
        for (int i = 0; i < vector_size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    T& operator[](int ind) {
        if (ind >= vector_size) {
            throw std::out_of_range("List index out of range");
        }
        return data[ind];
    }

    int size() const {
        return vector_size;
    }

    ~Vector() {
        delete [] data;
    }
};

