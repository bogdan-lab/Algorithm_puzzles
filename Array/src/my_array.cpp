#include "my_array.hpp"
#include <iostream>

template <typename TData>
CArray<TData>::~CArray(){
    delete[] data_;
}

template <typename TData>
void CArray<TData>::realloc(){
    capacity_ = 2*(capacity_+1);
    TData* new_data = new TData[capacity_];
    for(unsigned i=0; i<size_; i++){
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
}


template <typename TData>
void CArray<TData>::push_back(const TData& _value){
    if(size_>=capacity_){
        realloc();
    }
    data_[size_] = _value;
    size_++;
}

template <typename TData>
void CArray<TData>::clear(){
    size_ = 0;
}

template <typename TData>
unsigned CArray<TData>::size() const {
    return size_;
}

template <typename TData>
TData& CArray<TData>::operator[](unsigned int _index){
    return data_[_index];
}


template <typename TData>
void CArray<TData>::erase(unsigned int _index){
    while(_index+1!=size_){
        std::swap(data_[_index], data_[_index+1]);
        _index++;
    }
    size_--;
}

template <typename TData>
void CArray<TData>::insert(unsigned int _index, const TData &_value){
    push_back(_value);
    unsigned cur_pos = size_-1;
    while(cur_pos!=_index){
        std::swap(data_[cur_pos], data_[cur_pos-1]);
        cur_pos--;
    }
}

template <typename TData>
TData* CArray<TData>::begin(){
    return data_;
}

template <typename TData>
TData* CArray<TData>::end(){
    return data_+size_;
}

template <typename TData>
const TData* CArray<TData>::begin() const {
    return data_;
}

template <typename TData>
const TData* CArray<TData>::end() const {
    return data_+size_;
}


template <typename TData>
CArray<TData>::CArray(const CArray<TData> &_array){
    size_ = _array.size_;
    capacity_ = _array.capacity_;
    if(capacity_){
        data_ = new TData[capacity_];
        std::copy(_array.begin(), _array.end(), begin());
    }
}


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

