#include <set>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

struct Node {
    char value;
    std::size_t count;
    std::shared_ptr<Node> parent;
    std::unordered_map<char, std::shared_ptr<Node>> children;
};

class Trie {
private:
    std::shared_ptr<Node> m_root;
    std::size_t m_size;
public:
    Trie();
    void insert(std::string& str);
    std::size_t search(std::string& str);
    std::size_t search_prefix(std::string& prefix);
};

Trie::Trie() {
    m_root = std::make_shared<Node>(Node{'\0', 0, nullptr, std::unordered_map<char, std::shared_ptr<Node>>()});
    m_size = 0;
}

void Trie::insert(std::string& str) {
    std::shared_ptr<Node> curr = m_root;
    for (char& value : str) {
        curr->count++;
        auto children = curr->children;
        auto iter = children.find(value);
        if (iter != children.end()) {
            curr = iter->second;
        } else {
            auto next = std::make_shared<Node>(Node{value, 0, curr, std::unordered_map<char, std::shared_ptr<Node>>()});
            children.insert({ value, next });
            curr = next;
        }
    }
}

std::size_t Trie::search(std::string& str) {
    return 0;
}

std::size_t Trie::search_prefix(std::string& prefix) {
    return 0;
}
