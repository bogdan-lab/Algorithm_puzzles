#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>
#include<bitset>
#include<fstream>


using Byte = std::bitset<8>;


struct HNode{
    //0 - left; 1 - right
    HNode* left_ = nullptr;
    HNode* right_ = nullptr;
    char symbol_ = '\0';
};


HNode* build_decipher_tree(std::ifstream& bin_input);
void add_char_to_tree(HNode* root, const char symbol, const uint32_t word_len,
                      const std::vector<Byte> code);
std::string decipher_content(std::ifstream& in_file, const HNode* dec_tree);
std::vector<Byte> read_string_into_bytes(std::ifstream& bin_input, const size_t char_num);






int main(int argc, char** argv){

    std::ifstream in_file(argv[1], std::ios_base::binary);
    HNode* dec_tree = build_decipher_tree(in_file);
    std::string dec_content =  decipher_content(in_file, dec_tree);

    std::ofstream out_file(argv[2], std::ios_base::out);
    out_file << dec_content;

    return 0;
}






std::string decipher_content(std::ifstream& bin_file, const HNode* dec_tree){
    uint64_t symbol_num = 0;
    bin_file.read(reinterpret_cast<char*>(&symbol_num), sizeof(symbol_num));
    uint64_t bin_word_num = 0;
    bin_file.read(reinterpret_cast<char*>(&bin_word_num), sizeof(bin_word_num));
    std::vector<Byte> bin_content = read_string_into_bytes(bin_file, bin_word_num);
    //for(const auto& el : bin_content){
    //    std::cout << el;
    //}
    std::string content;
    content.reserve(symbol_num);
    const HNode* root = dec_tree;
    uint64_t idx = 0;
    while(symbol_num){
        root =bin_content[idx/8][7-idx%8] ? root->right_ : root->left_;
        idx++;
        if(!root->right_ && !root->left_){
            symbol_num--;
            content.push_back(root->symbol_);
            root = dec_tree;
        }
    }
    return content;
}


void add_char_to_tree(HNode* root, const char symbol, const uint32_t word_len,
                      const std::vector<Byte> code){
    for(uint32_t i=0; i<word_len; i++){
        if(code[i/8][7-i%8]){
            if(!root->right_) root->right_ = new HNode();
            root = root->right_;
        }
        else{
            if(!root->left_) root->left_ = new HNode();
            root = root->left_;
        }
    }
    root->symbol_ = symbol;
}

std::vector<Byte> read_string_into_bytes(std::ifstream& bin_input, const size_t char_num){
    char buffer[char_num];
    bin_input.read(buffer, static_cast<std::streamsize>(char_num));
    //std::cout << "BUFFER\n";
    //for(size_t i=0; i<char_num; i++){
    //    std::cout << buffer[i];
    //}
    std::vector<Byte> code;
    code.reserve(char_num);
    for(size_t i=0; i<char_num; i++){
        code.push_back(Byte(buffer[i]));
    }
    return code;
}


HNode* build_decipher_tree(std::ifstream& bin_input){
    HNode* root = new HNode();
    uint32_t char_num = 0;
    bin_input.read(reinterpret_cast<char*>(&char_num), sizeof(char_num));
    char cur_symbol='\0';
    uint32_t cur_word_len = 0;
    while(char_num--){
        bin_input.read(&cur_symbol, sizeof(cur_symbol));
        bin_input.read(reinterpret_cast<char*>(&cur_word_len), sizeof(cur_word_len));
        size_t bin_repr_size = cur_word_len/8+1;
        std::vector<Byte> code = read_string_into_bytes(bin_input, bin_repr_size);
        //std::string str = "";
        //for(const auto& el : code){
        //    str += el.to_string();
        //}
        //std::cerr << str << '\n';
        add_char_to_tree(root, cur_symbol, cur_word_len, code);
    }
    return root;
}


