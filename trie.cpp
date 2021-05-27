#include <set>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

struct Node {
    std::size_t count;
    std::string value;
    std::shared_ptr<Node> parent;
    std::vector<std::shared_ptr<Node>> children;
};

class trie {
private:
    std::shared_ptr<Node> m_root;
    std::size_t m_size;
public:
    trie();
    void insert(std::string& str);
    std::size_t search(std::string& str);
    std::size_t search_prefix(std::string& prefix);
};

trie::trie() {
    m_root = std::make_shared<Node>(Node{0, "", nullptr, std::vector<std::shared_ptr<Node>>()});
    m_size = 0;
}

void trie::insert(std::string& str) {

}

std::size_t trie::search(std::string& str) {
    return 0;
}

std::size_t trie::search_prefix(std::string& prefix) {
    return 0;
}
