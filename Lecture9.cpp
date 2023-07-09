#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isWord;

    TrieNode() : isWord(false) {}
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* curr = root;
        for (char ch : word) {
            if (curr->children.find(ch) == curr->children.end()) {
                curr->children[ch] = new TrieNode();
            }
            curr = curr->children[ch];
        }
        curr->isWord = true;
    }

    bool search(const string& word) {
        TrieNode* node = findWordNode(word);
        return (node != nullptr && node->isWord);
    }

    bool startsWith(const string& prefix) {
        return (findWordNode(prefix) != nullptr);
    }

    void deleteWord(const string& word) {
        deleteWordHelper(root, word, 0);
    }

private:
    TrieNode* findWordNode(const string& word) {
        TrieNode* curr = root;
        for (char ch : word) {
            if (curr->children.find(ch) == curr->children.end()) {
                return nullptr;
            }
            curr = curr->children[ch];
        }
        return curr;
    }

    bool deleteWordHelper(TrieNode* node, const string& word, int depth) {
        if (node == nullptr) {
            return false;
        }
        if (depth == word.length()) {
            if (!node->isWord) {
                return false;
            }
            node->isWord = false;
            return node->children.empty();
        }

        char ch = word[depth];
        if (deleteWordHelper(node->children[ch], word, depth + 1)) {
            node->children.erase(ch);
            return node->children.empty();
        }
        return false;
    }
};

int main() {
    Trie trie;

    // Insert words into the trie
    trie.insert("apple");
    trie.insert("banana");
    trie.insert("orange");

    // Search for words in the trie
    cout << trie.search("apple") << endl;    // Output: 1 (true)
    cout << trie.search("banana") << endl;   // Output: 1 (true)
    cout << trie.search("orange") << endl;   // Output: 1 (true)
    cout << trie.search("grape") << endl;    // Output: 0 (false)

    // Check if prefixes exist in the trie
    cout << trie.startsWith("app") << endl;  // Output: 1 (true)
    cout << trie.startsWith("ban") << endl;  // Output: 1 (true)
    cout << trie.startsWith("ora") << endl;  // Output: 1 (true)
    cout << trie.startsWith("gr") << endl;   // Output: 0 (false)

    // Delete a word from the trie
    trie.deleteWord("apple");
    cout << trie.search("apple") << endl;    // Output: 0 (false)

    return 0;
}
