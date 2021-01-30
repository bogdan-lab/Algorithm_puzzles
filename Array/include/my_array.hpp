#ifndef MY_ARRAY_HPP
#define MY_ARRAY_HPP

#include <iostream>

template <typename TData>
class CArray
{
public:
  CArray() = default;

  CArray(
    const CArray& _array
  );

  CArray& operator =(const CArray& _arr) = delete;
  CArray(CArray&& _arr) = delete;
  CArray& operator =(CArray&& _arr) = delete;

  ~CArray();

  void push_back(
    const TData& _value
  );

  void insert(
    unsigned int _index,
    const TData& _value
  );

  void erase(
    unsigned int _index
  );

  void clear();

  unsigned int size() const;

  TData& operator[](unsigned int _index);

  TData* begin();
  TData* end();
  const TData* begin() const;
  const TData* end() const;
protected:
  void realloc();
//Attributes
  TData* data_ = nullptr;
  unsigned size_ = 0u;
  unsigned capacity_ = 0u;
};

template <typename TData>
std::ostream& operator<<(std::ostream& out, const CArray<TData>& arr);




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
    for(auto it=_arr.begin(); it!=_arr.end()-1; it++){
        _out << *it << " ; ";
    }
    return _out << *(_arr.end()-1) << " }\n";
}







#endif //MY_ARRAY_HPP
