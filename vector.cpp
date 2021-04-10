#include <iostream>

template <typename T>
class Vector {
private:
    T *m_arr;
    unsigned int m_size;
    unsigned int m_capacity;
public:
    explicit Vector(int s=10);
    ~Vector();
    Vector(const Vector &vector);

    unsigned int size();
    T get(int index);
    void set(int index, T value);
    void add(T value);
    T pop();
    void print();
};

template <typename T>
Vector<T>::Vector(int s) {
    if (s > 0) {
        m_size = s;
        m_capacity = s;
        m_arr = new T[m_capacity];
        std::cout << "Constructor called." << std::endl;
    }
    else throw ("Size cannot be less than one.");
}

template <typename T>
Vector<T>::~Vector() {
    delete[] m_arr;
    std::cout << "Destructor called." << std::endl;
}

template <typename T>
Vector<T>::Vector(const Vector &vector) {
    m_size = vector.m_size;
    m_capacity = vector.m_capacity;
    m_arr = new T[m_capacity];
    for (int i = 0; i < m_capacity; i++) {
        m_arr[i] = vector.m_arr[i];
    }
}

template <typename T>
unsigned int Vector<T>::size() {
    return m_size;
}

template <typename T>
T Vector<T>::get(int index) {
    if (0 <= index < m_size) {
        return m_arr[index];
    }
    else throw "Index out of bounds.";
}

template <typename T>
void Vector<T>::set(int index, T value) {
    if (0 <= index < m_size) {
        m_arr[index] = value;
    }
    else throw "Index out of bounds.";
}

template <typename T>
void Vector<T>::add(T value) {
    if (m_size == m_capacity) {
        unsigned int tmp_capacity = m_capacity % 2 == 1 ? static_cast<unsigned int>(m_capacity * 1.5 + 1) : static_cast<unsigned int>(m_capacity * 1.5);
        T *tmp_arr = new T[tmp_capacity];
        for (int i = 0; i < m_capacity; i++) {
            tmp_arr[i] = m_arr[i];
        }
        delete[] m_arr;
        m_arr = tmp_arr;
        m_capacity = tmp_capacity;
    }
    m_arr[m_size] = value;
    m_size++;
}

template <typename T>
T Vector<T>::pop() {
    if (m_size > 0) {
        T toRet = m_arr[m_size - 1];
        T *tmp_arr = new T[m_capacity];
        for (int i = 0; i < m_size; i++) {
            tmp_arr[i] = m_arr[i];
        }
        delete[] m_arr;
        m_arr = tmp_arr;
        m_size--;
        return toRet;
    }
    else throw "Cannot pop() from empty vector.";
}

template <typename T>
void Vector<T>::print() {
    std::cout << "Vector start: " << std::endl;
    for (int i = 0; i < m_size; i++) {
        std::cout << m_arr[i] << std::endl;
    }
    std::cout << "Vector end. " << std::endl;
}
