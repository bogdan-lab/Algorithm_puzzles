#ifndef MY_ARRAY_HPP
#define MY_ARRAY_HPP

#include <iostream>

template <typename TData>
class CArray
{
public:
  CArray();

  CArray(
    const CArray& _array
  );

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

protected:
//Attributes
};

template <typename TData>
std::ostream& operator<<(std::ostream& out, const CArray<TData>& arr);

#endif //MY_ARRAY_HPP
