#include <cassert>
#include <iostream>

template<typename T>
class Vector {
private:
    unsigned int m_size;
    unsigned int m_capacity;
    T* m_arr;
    void addCapacity();
public:
    friend void swap(Vector<T>& first, Vector<T>& second);
    ~Vector(); // destructor
    explicit Vector(int s=10);  // constructor
    Vector(const Vector& vector);  // copy constructor
    Vector<T>& operator=(Vector<T> vector);  // copy/move assignment constructor
    Vector(Vector<T>&& vector) noexcept;  // move constructor

    const Vector<T>& operator[](int index) const;
    Vector<T>& operator[](int index);
    unsigned int size();
    void fill(T value);
    void add(T value);
    T pop();
    void insert(int index, T value);
    void remove(int index);
    void print();
};

template<typename T>
void Vector<T>::addCapacity() {
    assert(m_size == m_capacity);
    unsigned int tmp_capacity =
            m_capacity % 2 == 1 ? static_cast<unsigned int>(m_capacity * 1.5 + 1) : static_cast<unsigned int>(
                    m_capacity * 1.5);
    T* tmp_arr = new T[tmp_capacity];
    for (int i = 0; i < m_capacity; i++) {
        tmp_arr[i] = m_arr[i];
    }
    delete[] m_arr;
    m_arr = tmp_arr;
    m_capacity = tmp_capacity;
}

template<typename T>
void swap(Vector<T>& first, Vector<T>& second) {
    using std::swap;
    swap(first.m_size, second.m_size);
    swap(first.m_capacity, second.m_capacity);
    swap(first.m_arr, second.m_arr);
}

template<typename T>
Vector<T>::~Vector() {
    delete[] m_arr;
    std::cout << "Destructor called." << std::endl;
}

template<typename T>
Vector<T>::Vector(int s) : m_size(s > 0 ? s : throw ("Size cannot be less than one.")), m_capacity(s),
                                        m_arr(new T[s]) {
    std::cout << "Constructor called." << std::endl;
}

template<typename T>
Vector<T>::Vector(const Vector &vector) : m_size(vector.m_size), m_capacity(vector.m_capacity),
                                          m_arr(new T[vector.m_capacity]) {
    std::copy(std::begin(vector.m_arr), std::end(vector.m_arr), std::begin(m_arr));
    std::cout << "Copy constructor called." << std::endl;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> vector) {
    swap(*this, vector);
    std::cout << "Copy/Move assignment operator called." << std::endl;
    return *this;
}

template<typename T>
Vector<T>::Vector(Vector<T>&& vector) noexcept : Vector() {
    swap(*this, vector);
    std::cout << "Move constructor called." << std::endl;
}

template<typename T>
const Vector<T>& Vector<T>::operator[](int index) const {
    if (index >= 0) {
        return m_arr[index];
    } else throw "Index out of bounds.";
}

template<typename T>
Vector<T>& Vector<T>::operator[](int index) {
    if (index >= 0) {
        return m_arr[index];
    } else throw "Index out of bounds.";
}

template<typename T>
unsigned int Vector<T>::size() {
    return m_size;
}

template<typename T>
void Vector<T>::fill(T value) {
    for (int i = 0; i < m_size; i++) {
        m_arr[i] = value;
    }
}

template<typename T>
void Vector<T>::add(T value) {
    if (m_size == m_capacity) {
        addCapacity();
    }
    m_arr[m_size] = value;
    m_size++;
}

template<typename T>
T Vector<T>::pop() {
    if (m_size > 0) {
        T toRet = m_arr[m_size - 1];
        T* tmp_arr = new T[m_capacity];
        for (int i = 0; i < m_size; i++) {
            tmp_arr[i] = m_arr[i];
        }
        delete[] m_arr;
        m_arr = tmp_arr;
        m_size--;
        return toRet;
    } else throw "Cannot pop() from empty vector.";
}

template<typename T>
void Vector<T>::insert(int index, T value) {
    if (0 <= index <= m_size) {
        if (m_size == m_capacity) {
            addCapacity();
        }
        T* tmp_arr = new T[m_capacity];
        for (int i = 0; i < m_size + 1; i++) {
            if (i == index) {
                tmp_arr[i] = value;
                i++;
            }
            tmp_arr[i] = i < index ? m_arr[i] : m_arr[i - 1];
        }
        delete[] m_arr;
        m_arr = tmp_arr;
        m_size++;
    } else throw "Index out of bounds.";
}

template<typename T>
void Vector<T>::remove(int index) {
    if (0 <= index < m_size) {
        T* tmp_arr = new T[m_capacity];
        for (int i = 0; i < m_size - 1; i++) {
            if (i != index) {
                tmp_arr[i] = i < index ? m_arr[i] : m_arr[i + 1];
            }
        }
        delete[] m_arr;
        m_arr = tmp_arr;
        m_size--;
    } else throw "Index out of bounds.";
}

template<typename T>
void Vector<T>::print() {
    for (int i = 0; i < m_size - 1; i++) {
        std::cout << m_arr[i] << ", ";
    }
    std::cout << m_arr[m_size - 1] << std::endl;
}
