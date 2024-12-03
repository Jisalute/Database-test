#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <vector>

// 位图类，用于存储位序列
class Bitmap {
private:
    std::vector<bool> bits;

public:
    void addBit(bool bit) {
        bits.push_back(bit);
    }

    void removeLastBit() {
        if (!bits.empty()) {
            bits.pop_back();
        }
    }

    Bitmap copy() const {
        Bitmap new_bitmap;
        new_bitmap.bits = bits;
        return new_bitmap;
    }

    std::string toString() const {
        std::string s;
        for (bool bit : bits) {
            s += bit ? '1' : '0';
        }
        return s;
    }
};

// 二叉树节点类
class BinTreeNode {
public:
    char ch; // 节点代表的字符（对于叶子节点）
    int freq; // 节点的频率
    BinTreeNode *left; // 左子节点
    BinTreeNode *right; // 右子节点

    // 构造函数（叶子节点）
    BinTreeNode(char character, int frequency)
        : ch(character), freq(frequency), left(nullptr), right(nullptr) {}

    BinTreeNode(int frequency, BinTreeNode *l, BinTreeNode *r)
        : ch('\0'), freq(frequency), left(l), right(r) {}

    ~BinTreeNode() {
        delete left;
        delete right;
    }
};

struct Compare {
    bool operator()(BinTreeNode *l, BinTreeNode *r) {
        return l->freq > r->freq;
    }
};

class HuffmanTree {
private:
    BinTreeNode *root;
    std::map<char, Bitmap> huffmanCodes;

    void generateCodes(BinTreeNode *node, Bitmap &current_code) {
        if (!node) return;

        if (!node->left && !node->right) {
            huffmanCodes[node->ch] = current_code.copy();
            return;
        }

        current_code.addBit(0);
        generateCodes(node->left, current_code);
        current_code.removeLastBit();

        current_code.addBit(1);
        generateCodes(node->right, current_code);
        current_code.removeLastBit();
    }

public:

    HuffmanTree(const std::map<char, int> &freq_map) {
        // 创建初始的叶子节点列表
        std::priority_queue<BinTreeNode*, std::vector<BinTreeNode*>, Compare> heap;
        for (auto pair : freq_map) {
            heap.push(new BinTreeNode(pair.first, pair.second));
        }

        while (heap.size() > 1) {
            BinTreeNode *left = heap.top();
            heap.pop();
            BinTreeNode *right = heap.top();
            heap.pop();
            BinTreeNode *merged = new BinTreeNode(left->freq + right->freq, left, right);
            heap.push(merged);
        }

        root = heap.top();

        Bitmap current_code;
        generateCodes(root, current_code);
    }

    ~HuffmanTree() {
        delete root;
    }

    const std::map<char, Bitmap>& getCodes() const {
        return huffmanCodes;
    }
};

int main() {
    std::ifstream file("word.txt");

std::string speech((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
file.close();

    // 将文本转换为小写，并只保留字母
    std::string text;
    for (char c : speech) {
        if (isalpha(c)) {
            text += tolower(c);
        }
    }

    // 统计每个字母的频率
    std::map<char, int> freq_map;
    for (char c : text) {
        freq_map[c]++;
    }

    HuffmanTree huffmanTree(freq_map);

    const std::map<char, Bitmap>& huffman_codes = huffmanTree.getCodes();

    auto encodeWord = [&](const std::string &word) {
        std::string encoded;
        for (char c : word) {
            char lower_c = tolower(c);
            if (huffman_codes.find(lower_c) != huffman_codes.end()) {
                encoded += huffman_codes.at(lower_c).toString();
            } else {
                std::cout << "Character '" << c << "' not in Huffman tree.\n";
                return std::string();
            }
        }
        return encoded;
    };

    std::string word1 = "dream";
    std::string encoded_word1 = encodeWord(word1);
    std::cout << "Huffman encoding for '" << word1 << "': " << encoded_word1 << std::endl;

    std::string word2 = "me";
    std::string encoded_word2 = encodeWord(word2);
    std::cout << "Huffman encoding for '" << word2 << "': " << encoded_word2 << std::endl;

    return 0;
}

