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

  TData& operator[](
    unsigned int _index
  );

  TData* begin();
  TData* end();

protected:
  void realloc();
//Attributes
  TData* data_ = nullptr;
  unsigned size_ = 0u;
  unsigned capacity_ = 0u;
};

template <typename TData>
std::ostream& operator<<(std::ostream& out, const CArray<TData>& arr);

#endif //MY_ARRAY_HPP
