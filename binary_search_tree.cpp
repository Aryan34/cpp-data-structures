#include <memory>
#include <vector>
#include <iostream>

template <typename T>
struct Node {
    T value;
    std::shared_ptr<Node<T>> left;
    std::shared_ptr<Node<T>> right;
    std::shared_ptr<Node<T>> parent;
};

template <typename T>
class BST {
private:
    std::shared_ptr<Node<T>> m_root;
    std::size_t m_size;
public:
    explicit BST(std::vector<T>& values);
    void inorder();
    void preorder();
    void postorder();
    std::string inorder_helper(std::shared_ptr<Node<T>> root);
    std::string preorder_helper(std::shared_ptr<Node<T>> root);
    std::string postorder_helper(std::shared_ptr<Node<T>> root);
    void insert(T value);
    std::shared_ptr<Node<T>> remove(T value);
    std::shared_ptr<Node<T>> search(T value);
    std::size_t size();
    T max();
    T min();
};

template<typename T>
BST<T>::BST(std::vector<T> &values) {
    m_size = values.size();
    if (m_size != 0) {
        m_root = std::make_shared<Node<T>>(Node<T>{values.at(0), nullptr, nullptr, nullptr});
        for (int i = 1; i < m_size; i++) {
            insert(values.at(i));
        }
    }
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
std::string BST<T>::inorder_helper(std::shared_ptr<Node<T>> root) {
    return "";
}

template<typename T>
std::string BST<T>::preorder_helper(std::shared_ptr<Node<T>> root) {
    return "";
}

template<typename T>
std::string BST<T>::postorder_helper(std::shared_ptr<Node<T>> root) {
    return "";
}

template<typename T>
void BST<T>::insert(T value) {
    if (m_root == nullptr) {
        m_root = std::make_shared<Node<T>>(Node<T>{value, nullptr, nullptr, nullptr});
    } else {
        std::shared_ptr<Node<T>> curr = m_root;
        while (true) {
            if (value < curr->value) {
                if (curr->left == nullptr) {
                    curr->left = std::make_shared<Node<T>>(Node<T>{value, nullptr, nullptr, curr});
                    break;
                } else { curr = curr->left; }
            } else if (value > curr->value) {
                if (curr->right == nullptr) {
                    curr->right = std::make_shared<Node<T>>(Node<T>{value, nullptr, nullptr, curr});
                    break;
                } else { curr = curr->right; }
            }
        }
    }
}

template<typename T>
std::shared_ptr<Node<T>> BST<T>::remove(T value) {
    return Node<T>();
}

template<typename T>
std::shared_ptr<Node<T>> BST<T>::search(T value) {
    std::shared_ptr<Node<T>> curr = m_root;
    while (true) {
        if (value < curr->value) {
            if (curr->left == nullptr) {
                return curr->left;
            } else { curr = curr->left; }
        } else if (value > curr->value) {
            if (curr->right == nullptr) {
                return curr->right;
            } else { curr = curr->right; }
        } else { return curr; }
    }
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
    std::vector<int> input{1, 9, 4, 5, 6, 3, 2, 8, 7, 0};
    BST<int> bst(input);
    return 0;
}
