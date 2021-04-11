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
    explicit Vector(T fillValue, int s=10);
    Vector(const Vector& vector);
    ~Vector();

    unsigned int size();
    T get(int index);
    void set(int index, T value);
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
Vector<T>::Vector(T fillValue, int s) : m_size(s > 0 ? s : throw ("Size cannot be less than one.")), m_capacity(s),
                                        m_arr(new T[s]) {
    fill(fillValue);
    std::cout << "Constructor called." << std::endl;
}

template<typename T>
Vector<T>::Vector(const Vector &vector) : m_size(vector.m_size), m_capacity(vector.m_capacity),
                                          m_arr(new T[m_capacity]) {
    for (int i = 0; i < m_capacity; i++) {
        m_arr[i] = vector.m_arr[i];
    }
}

template<typename T>
Vector<T>::~Vector() {
    delete[] m_arr;
    std::cout << "Destructor called." << std::endl;
}

template<typename T>
unsigned int Vector<T>::size() {
    return m_size;
}

template<typename T>
T Vector<T>::get(int index) {
    if (0 <= index < m_size) {
        return m_arr[index];
    } else throw "Index out of bounds.";
}

template<typename T>
void Vector<T>::set(int index, T value) {
    if (0 <= index < m_size) {
        m_arr[index] = value;
    } else throw "Index out of bounds.";
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
