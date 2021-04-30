#include <set>
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
    std::set<T> m_values{};
    std::size_t m_size;
public:
    explicit BST(std::vector<T>& values);
    std::vector<T> inorder();
    std::vector<T> preorder();
    std::vector<T> postorder();
    std::vector<T> inorder_helper(std::shared_ptr<Node<T>> start);
    std::vector<T> preorder_helper(std::shared_ptr<Node<T>> start);
    std::vector<T> postorder_helper(std::shared_ptr<Node<T>> start);
    void insert(T value);
    void remove(T value);
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
        m_values.insert(values.at(0));
        for (int i = 1; i < values.size(); i++) {
            insert(values.at(i));
        }
    }
}

template<typename T>
std::vector<T> BST<T>::inorder() {
    std::vector<T> traversal = inorder_helper(m_root);
    return traversal;
}

template<typename T>
std::vector<T> BST<T>::preorder() {
    std::vector<T> traversal = preorder_helper(m_root);
    return traversal;
}

template<typename T>
std::vector<T> BST<T>::postorder() {
    std::vector<T> traversal = postorder_helper(m_root);
    return traversal;
}

template<typename T>
std::vector<T> BST<T>::inorder_helper(std::shared_ptr<Node<T>> start) {
    std::vector<T> toRet;
    if (start->left != nullptr) {
        std::vector<T> tmp = inorder_helper(start->left);
        toRet.insert(toRet.end(), tmp.begin(), tmp.end());
    }
    toRet.push_back(start->value);
    if (start->right != nullptr) {
        std::vector<T> tmp = inorder_helper(start->right);
        toRet.insert(toRet.end(), tmp.begin(), tmp.end());
    }
    return toRet;
}

template<typename T>
std::vector<T> BST<T>::preorder_helper(std::shared_ptr<Node<T>> start) {
    std::vector<T> toRet;
    if (start->left != nullptr) {
        std::vector<T> tmp = inorder_helper(start->left);
        toRet.insert(toRet.end(), tmp.begin(), tmp.end());
    }
    if (start->right != nullptr) {
        std::vector<T> tmp = inorder_helper(start->right);
        toRet.insert(toRet.end(), tmp.begin(), tmp.end());
    }
    toRet.push_back(start->value);
    return toRet;
}

template<typename T>
std::vector<T> BST<T>::postorder_helper(std::shared_ptr<Node<T>> start) {
    std::vector<T> toRet;
    toRet.push_back(start->value);
    if (start->left != nullptr) {
        std::vector<T> tmp = inorder_helper(start->left);
        toRet.insert(toRet.end(), tmp.begin(), tmp.end());
    }
    if (start->right != nullptr) {
        std::vector<T> tmp = inorder_helper(start->right);
        toRet.insert(toRet.end(), tmp.begin(), tmp.end());
    }
    return toRet;
}

template<typename T>
void BST<T>::insert(T value) {
    m_size++;
    if (m_values.count(value)) {
        return;
    }
    m_values.insert(value);
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
void BST<T>::remove(T value) {
    if (!m_values.count(value)) {
        return;
    }
    std::shared_ptr<Node<T>> curr = m_root;
    while (true) {
        if (value < curr->value && curr->left != nullptr) {
            curr = curr->left;
        } else if (value > curr->value && curr->right != nullptr) {
            curr = curr->right;
        } else {
            break;
        }
    }

    if (curr->left == nullptr && curr->right == nullptr) {
        if (curr == curr->parent->left) {
            curr->parent->left = nullptr;
        } else { curr->parent->right = nullptr; }
    } else if (curr->left != nullptr && curr->right == nullptr) {
        curr->value = curr->left->value;
        curr->left = nullptr;
    } else if (curr->left == nullptr && curr->right != nullptr) {
        curr->value = curr->right->value;
        curr->right = nullptr;
    } else {
        std::vector<T> inorder = this->inorder();
        std::shared_ptr<Node<T>> successor;
        for (int i = 0; i < inorder.size(); i++) {
            if (inorder.at(i) == curr->value) {
                successor = search(inorder.at(i + 1));
                break;
            }
        }
        if (successor == nullptr) { throw "Error in code, remove value not found in tree"; }
        curr->value = successor->value;
        if (successor == successor->parent->left) {
            successor->parent->left = nullptr;
        } else { successor->parent->right = nullptr; }
    }
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

template<typename T>
void printVector(std::vector<T> vec) {
    for (const auto& i : vec)
        std::cout << i << ' ';
    std::cout << std::endl;
}

int main ()
{
    std::vector<int> input{1, 4, 5, 6, 3, 9, 2, 8, 7, 0};
    BST<int> bst(input);
    printVector(bst.inorder());
    bst.insert(1337);
    bst.insert(-420);
    bst.remove(1);
    printVector(bst.inorder());
    std::cout << bst.min() << ", " << bst.max() << std::endl;
    return 0;
}
