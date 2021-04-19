#include <vector>
#include <iostream>

template <typename T>
struct Node {
    T value;
    Node* next;
};

template <typename T>
class SLL {
private:
    Node<T>* m_head;
    Node<T>* m_tail;
    std::size_t m_size;
public:
    explicit SLL(std::vector<T>& values);
    Node<T>* get(int index);
    void insert(int index, T value);
    void print();
    void set(int index, T value);
};

template<typename T>
SLL<T>::SLL(std::vector<T> &values) {
    m_size = values.size();
    for (int i = 0; i < values.size(); i++) {
        switch (i) {
            case 0: {
                auto tmp0 = new Node<T>{values[0], nullptr};
                m_head = tmp0;
                m_tail = tmp0;
                break;
            }
            case 1: {
                auto tmp1 = new Node<T>{values[1], nullptr};
                m_head->next = tmp1;
                m_tail = tmp1;
                break;
            }
            default: {
                auto tmpDefault = new Node<T>{values[i], nullptr};
                m_tail->next = tmpDefault;
                m_tail = tmpDefault;
            }
        }
    }
}

template<typename T>
Node<T>* SLL<T>::get(int index) {
    if (0 <= index < m_size) {
        int i = 0;
        Node<T>* tmp = m_head;
        while (i != index) {
            tmp = tmp->next;
            i++;
        }
        return tmp;
    } else throw "Index out of bounds";
}

template<typename T>
void SLL<T>::insert(int index, T value) {
    Node<T>* prev = get(index - 1);
    Node<T>* next = prev->next;
    auto toInsert = new Node<T>{value, nullptr};
    toInsert->next = next;
    prev->next = toInsert;
}

template<typename T>
void SLL<T>::print() {
    Node<T>* tmp = m_head;
    while (tmp->next != nullptr) {
        std::cout << tmp->value << " ";
        tmp = tmp->next;
    }
    std::cout << tmp->value << std::endl;
}

template<typename T>
void SLL<T>::set(int index, T value) {
    if (0 <= index < m_size) {
        int i = 0;
        Node<T>* tmp = m_head;
        while (i != index) {
            tmp = tmp->next;
            i++;
        }
        tmp->value = value;
    } else throw "Index out of bounds";
}

int main ()
{
    std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    SLL<int> sll(vec);
    sll.print();
    sll.insert(4, 1337);
    sll.print();
    Node<int>* node = sll.get(4);
    std::cout << node->value << std::endl;
    sll.set(6, 600);
    sll.print();
    return 0;
}
