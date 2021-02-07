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

using FreqHolder = std::unordered_map<char, size_t>;
using BinWord = std::vector<short>;
using Translator = std::unordered_map<char, BinWord>;


struct HNode{
    HNode* left_ = nullptr;
    HNode* right_ = nullptr;
    size_t freq_ = 0;
    char symbol_ = '\0';
    BinWord code_ = {};

    HNode(const size_t gf, const char gc) : freq_(gf), symbol_(gc) {}
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

//int main(int argc, char** argv){
int main(){
    //std::cout <<argc << '\n';
    //std::cout << "THE FIRST ARGUMENT " << argv[1] << '\n';
    //std::cout << "THE SECOND ARGUMENT " << argv[2] << '\n' << '\n';

    //std::ifstream in_file(argv[1], std::ios_base::in);
    std::stringstream in_file;
    in_file << R"(asdnad ads pamda asd)";
    std::string content;
    std::copy(std::istreambuf_iterator<char>(in_file),
              std::istreambuf_iterator<char>(), std::back_inserter(content));
    FreqHolder frequencies = get_frequency(content);
    //PriorQueue symbol_queue = build_queue(frequencies); 	//TODO DELETE
    HNode* symbol_tree  = build_HTree(frequencies);
    add_binary_words(symbol_tree);
    Translator char_to_bin = get_translator_to_bin(symbol_tree);


    for(const auto el : char_to_bin){
        std::cout << el.first << " = ";
        for(const auto c : el.second){
            std::cout << c << ' ';
        }
        std::cout << '\n';
    }


    /*
    while(!symbol_queue.empty()){
        std::cout << symbol_queue.top()->symbol_ << ' ' << symbol_queue.top()->freq_ << '\n';
        symbol_queue.pop();
    }
    */
    /*
    for(const auto& el : frequencies){
        std::cout << el.first << " " << el.second << '\n';
    }
    */

    return 0;
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
    symbol_tree->left_->code_ = symbol_tree->code_;
    symbol_tree->left_->code_.push_back(0);
    symbol_tree->right_->code_ = symbol_tree->code_;
    symbol_tree->right_->code_.push_back(1);
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



