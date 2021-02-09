#include<iostream>
#include<unordered_map>
#include<vector>
#include<iterator>
#include<string>
#include<fstream>
#include<iterator>
#include<queue>
#include<utility>
#include<sstream>
#include<bitset>

using FreqHolder = std::unordered_map<char, uint64_t>;
using Translator = std::unordered_map<char, std::string>;
using Byte = std::bitset<8>;

struct HNode{
    HNode* left_ = nullptr;
    HNode* right_ = nullptr;
    uint64_t freq_ = 0;
    char symbol_ = '\0';
    std::string code_ = {};

    HNode(const uint64_t gf, const char gc) : freq_(gf), symbol_(gc) {}
    HNode(HNode* lhs, HNode* rhs) : left_(lhs), right_(rhs) {
        freq_ = lhs->freq_ + rhs->freq_;
    }
};

struct HNodeCompare{
   bool operator()( const HNode* lhs,
                    const HNode* rhs ) const {
       return lhs->freq_>rhs->freq_;
   }
};


using PriorQueue = std::priority_queue<HNode*,
                                       std::vector<HNode*>,
                                       HNodeCompare>;


FreqHolder get_frequency(const std::string& content);
PriorQueue build_queue(const FreqHolder& freq);
HNode* build_HTree(const FreqHolder& freq);
void add_binary_words(HNode* symbol_tree);
Translator get_translator_to_bin(const HNode* symbol_tree);
void fill_tree_vector(const HNode* symbol_tree, std::vector<const HNode*>& tree_elements);

std::string get_bin_repr_text(const std::string& content, const Translator& char_to_bin);
std::vector<Byte> split_to_bytes(const std::string& bin_text);

void write_encoded_text(std::ostream& out_file, const std::vector<Byte>& bin_content,
                        const Translator& char_to_bin, const uint64_t symbol_num);


int main(int argc, char** argv){
    //TODO Entire text is one symbol - does not work!

    std::ifstream in_file(argv[1], std::ios_base::in);
    //std::ifstream in_file("test_file", std::ios_base::in);
    std::string content{std::istreambuf_iterator<char>(in_file),
                        std::istreambuf_iterator<char>()};
    FreqHolder frequencies = get_frequency(content);
    HNode* symbol_tree  = build_HTree(frequencies);
    add_binary_words(symbol_tree);
    Translator char_to_bin = get_translator_to_bin(symbol_tree);
    std::string bin_text = get_bin_repr_text(content, char_to_bin);
    std::vector<Byte> bin_content = split_to_bytes(bin_text);
    uint64_t symbol_num = content.size();

    std::ofstream out_file(argv[2], std::ios_base::binary);
    write_encoded_text(out_file, bin_content, char_to_bin, symbol_num);

    return 0;
}

void write_binary_word(std::ostream& out_file, const std::vector<Byte>& bin_content){
    for(const auto& el : bin_content){
        out_file.write(reinterpret_cast<const char*>(&el),1);
    }
}

void write_encoded_text(std::ostream& out_file, const std::vector<Byte>& bin_content,
                        const Translator& char_to_bin, const uint64_t symbol_num){
    uint32_t char_num = static_cast<uint32_t>(char_to_bin.size());
    out_file.write(reinterpret_cast<char*>(&char_num), sizeof(char_num));
    //std::cout << "CHAR NUM = " << char_num << '\n';
    std::vector<Byte> current_word;
    for(const auto& el : char_to_bin){
        uint32_t word_legth = static_cast<uint32_t>(el.second.size());
        current_word = split_to_bytes(el.second);
        out_file.write(&el.first, sizeof(el.first));
        //std::cout << el.first << ' ' << word_legth << ' ';
        //for(const auto tst : current_word){
        //    std::cout << tst;
        //}
        //std::cout << '\n';
        out_file.write(reinterpret_cast<char*>(&word_legth), sizeof(word_legth));
        write_binary_word(out_file, current_word);
    }
    out_file.write(reinterpret_cast<const char*>(&symbol_num), sizeof(symbol_num));
    //std::cout << "Symbol num = " << symbol_num << '\n';
    uint64_t bin_word_num = bin_content.size();
    out_file.write(reinterpret_cast<char*>(&bin_word_num), sizeof(uint64_t));
    //std::cout << "Bin word num = " << bin_word_num << '\n';
    write_binary_word(out_file, bin_content);
    //for(const auto tst : bin_content){
    //    std::cout << tst;
    //}
}


std::vector<Byte> split_to_bytes(const std::string& bin_text){
    std::vector<Byte> bin_content;
    uint64_t size = bin_text.size()/8;
    uint64_t leftover = bin_text.size() % 8;
    bin_content.reserve(size+1);
    for(uint64_t i=0; i<size; i++){
        bin_content.push_back({bin_text, 8*i, 8});
    }
    bin_content.push_back({bin_text, 8*size, leftover});
    bin_content.back() <<= 8 - leftover;
    return bin_content;
}


std::string get_bin_repr_text(const std::string& content, const Translator& char_to_bin){
    std::string bin_text;
    for(const auto& el : content){
        bin_text.insert(bin_text.end(), char_to_bin.at(el).begin(), char_to_bin.at(el).end());
    }
    return bin_text;
}


Translator get_translator_to_bin(const HNode* symbol_tree){
    std::vector<const HNode*> tree_elements{symbol_tree};
    fill_tree_vector(symbol_tree, tree_elements);
    Translator char_to_bin;
    for(const auto el : tree_elements){
        if(el->symbol_!='\0') char_to_bin[el->symbol_] = el->code_;
    }
    return char_to_bin;
}


void fill_tree_vector(const HNode* symbol_tree, std::vector<const HNode*>& tree_elements){
    if(!symbol_tree->left_ || !symbol_tree->right_) return;
    tree_elements.push_back(symbol_tree->left_);
    tree_elements.push_back(symbol_tree->right_);
    fill_tree_vector(symbol_tree->left_, tree_elements);
    fill_tree_vector(symbol_tree->right_, tree_elements);
}


void add_binary_words(HNode* symbol_tree){
    if(!symbol_tree->left_ || !symbol_tree->right_) return;
    symbol_tree->left_->code_.reserve(symbol_tree->code_.size()+1);
    symbol_tree->left_->code_ = symbol_tree->code_;
    symbol_tree->left_->code_.push_back('0');
    symbol_tree->right_->code_.reserve(symbol_tree->code_.size()+1);
    symbol_tree->right_->code_ = symbol_tree->code_;
    symbol_tree->right_->code_.push_back('1');
    add_binary_words(symbol_tree->left_);
    add_binary_words(symbol_tree->right_);
}

HNode* build_HTree(const FreqHolder& freq){
    PriorQueue HNode_queue = build_queue(freq);
    while (HNode_queue.size()>1) {
        HNode* lhs = HNode_queue.top();
        HNode_queue.pop();
        HNode* rhs = HNode_queue.top();
        HNode_queue.pop();
        HNode_queue.push(new HNode(lhs, rhs));
    }
    HNode* tmp = HNode_queue.top();
    HNode_queue.pop();
    return tmp;
}


PriorQueue build_queue(const FreqHolder& freq){
    PriorQueue HNode_queue;
    for(const auto el : freq){
        HNode_queue.push( new HNode(el.second, el.first));
    }
    return HNode_queue;
}


FreqHolder get_frequency(const std::string& content){
    FreqHolder frequencies;
    for(const auto& el : content){
        frequencies[el]++;
    }
    return frequencies;
}



