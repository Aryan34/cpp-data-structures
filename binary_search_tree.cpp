#include <memory>
#include <vector>
#include <iostream>

template <typename T>
struct Node {
    T value;
    std::unique_ptr<T> left;
    std::unique_ptr<T> right;
    std::unique_ptr<T> parent;
};

template <typename T>
class BST {
private:
    Node<T> m_root;
    std::size_t m_size;
public:
    explicit BST(std::vector<T>& values);
    void inorder();
    void preorder();
    void postorder();
    void insert(T value);
    Node<T> remove(T value);
    Node<T> search(T value);
    std::size_t size();
    T max();
    T min();
};

template<typename T>
BST<T>::BST(std::vector<T> &values) {

}

template<typename T>
void BST<T>::inorder() {

}

template<typename T>
void BST<T>::preorder() {

}

template<typename T>
void BST<T>::postorder() {

}

template<typename T>
void BST<T>::insert(T value) {

}

template<typename T>
Node<T> BST<T>::remove(T value) {
    return Node<T>();
}

template<typename T>
Node<T> BST<T>::search(T value) {
    return Node<T>();
}

template<typename T>
std::size_t BST<T>::size() {
    return 0;
}

template<typename T>
T BST<T>::max() {
    return nullptr;
}

template<typename T>
T BST<T>::min() {
    return nullptr;
}

int main ()
{
    std::cout << "BST";
    return 0;
}
