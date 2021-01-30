#include "my_array.hpp"
#include <iostream>




template <typename T>
std::ostream& operator<<(std::ostream& _out, const CArray<T>& _arr){
    if(_arr.size()==0){
        return _out << "{}\n";
    }
    _out << "{";
    for(unsigned i=0; i<_arr.size()-1; i++){
        _out << _arr[i] << " ; ";
    }
    return _out << _arr[_arr.size()-1] << " }\n";
}

