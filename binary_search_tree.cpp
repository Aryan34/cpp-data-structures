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
    m_size = 0;
    if (!values.empty()) {
        m_root = std::make_shared<Node<T>>(Node<T>{values.at(0), nullptr, nullptr, nullptr});
        for (int i = 1; i < values.size(); i++) {
            insert(values.at(i));
        }
    }
}

template<typename T>
void BST<T>::inorder() {
    std::string traversal = inorder_helper(m_root);
    std::cout << "Inorder: " + traversal << std::endl;
}

template<typename T>
void BST<T>::preorder() {
    std::string traversal = preorder_helper(m_root);
    std::cout << "Preorder: " + traversal << std::endl;
}

template<typename T>
void BST<T>::postorder() {
    std::string traversal = postorder_helper(m_root);
    std::cout << "Postorder: " + traversal << std::endl;
}

template<typename T>
std::string BST<T>::inorder_helper(std::shared_ptr<Node<T>> root) {
    std::string toRet;
    if (root->left != nullptr) { toRet.append(inorder_helper(root->left)); }
    toRet.append(std::to_string(root->value) + " ");
    if (root->right != nullptr) { toRet.append(inorder_helper(root->right)); }
    return toRet;
}

template<typename T>
std::string BST<T>::preorder_helper(std::shared_ptr<Node<T>> root) {
    std::string toRet;
    if (root->left != nullptr) { toRet.append(inorder_helper(root->left)); }
    if (root->right != nullptr) { toRet.append(inorder_helper(root->right)); }
    toRet.append(std::to_string(root->value) + " ");
    return toRet;
}

template<typename T>
std::string BST<T>::postorder_helper(std::shared_ptr<Node<T>> root) {
    std::string toRet;
    toRet.append(std::to_string(root->value) + " ");
    if (root->left != nullptr) { toRet.append(inorder_helper(root->left)); }
    if (root->right != nullptr) { toRet.append(inorder_helper(root->right)); }
    return toRet;
}

template<typename T>
void BST<T>::insert(T value) {
    m_size++;
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
    return m_size;
}

template<typename T>
T BST<T>::max() {
    std::shared_ptr<Node<T>> curr = m_root;
    while (curr->right != nullptr) {
        curr = curr->right;
    }
    return curr->value;
}

template<typename T>
T BST<T>::min() {
    std::shared_ptr<Node<T>> curr = m_root;
    while (curr->left != nullptr) {
        curr = curr->left;
    }
    return curr->value;
}

int main ()
{
    std::vector<int> input{1, 9, 4, 5, 6, 3, 2, 8, 7, 0};
    BST<int> bst(input);
    bst.inorder();
    bst.preorder();
    bst.postorder();
    std::cout << bst.min() << ", " << bst.max() << std::endl;
    return 0;
}
