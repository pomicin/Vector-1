#ifndef _VECT_HPP
#define _VECT_HPP

#include <initializer_list>
#include <iostream>
#include <optional>
#include <iterator>
#include <memory>
#include <cstring>

// N dimensional Vector of element type T
// Heavily inspired by GNU implementation of std::array
template <typename T, std::size_t N>
struct Vector {

  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  pointer m_Data;
  const size_type m_Size = N;

// Capacity
  size_type size() const {
    return m_Size;
  }

// Iterators
  iterator begin() {
    return iterator(std::addressof(m_Data[0]));
  }

  iterator end() {
    return iterator(std::addressof(m_Data[N]));
  }

  const_iterator cbegin() const {
    return const_iterator(std::addressof(m_Data[0]));
  }

  const_iterator cend() const {
    return const_iterator(std::addressof(m_Data[N]));
  }

  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

  reverse_iterator rend() {
    return reverse_iterator(begin());
  }

  const_reverse_iterator crbegin() {
    return reverse_iterator(cend());
  }

  const_reverse_iterator crend() {
    return reverse_iterator(cbegin());
  }

// Construction
  Vector():
    m_Data(new value_type[N]) {

    return;
  }

  Vector(const_reference value):
    m_Data(new value_type[N]) {
    fill(value);

    return;
  }

  Vector(Vector<value_type, N>&& other) noexcept:
    m_Data(other.m_Data) {
    other.m_Data = nullptr;

    return;
  }

  Vector(const Vector<value_type, N>& other):
    m_Data(new value_type[N]) {
    std::copy(other.begin(), other.end(), begin());

    return;
  }

  Vector(const std::initializer_list<value_type>& init_list):
    m_Data(new value_type[N]) {
    std::copy(init_list.begin(), init_list.end(), begin());

    return;
  }

//Destruction
  ~Vector() {
    delete[] m_Data;
  }

// Assignment
  const_reference operator=(Vector<value_type, N>&& other) {
    m_Data = other.m_Data;
    other.m_Data = nullptr;

    return *this;
  }

  const_reference operator=(const Vector<value_type, N>& other) {
    std::copy(other.begin(), other.end(), begin());

    return *this;
  }

  const_reference operator=(const std::initializer_list<value_type> init_list) {
    std::copy(init_list.begin(), init_list.end(), begin());

    return *this;
  }

// Data access
  reference operator[](const std::size_t n) {
    return m_Data[n];
  }

  pointer data() {
    return m_Data;
  }

// Modify
  void fill(const_reference value) {
    std::fill(begin(), end(), value);

    return;
  }

  void swap(const Vector<value_type, N>& other) {
    std::swap_ranges(other.begin(), other.end(), begin());

    return;
  }

// Arithmetic modify
  Vector<value_type, N>& operator+=(Vector<value_type, N>& other) {
    #pragma omp simd
    for(unsigned int i = 0; i < size(); i++)
      m_Data[i] += other.m_Data[i];

    return *this;
  }

  Vector<value_type, N>& operator-=(const Vector<value_type, N>& other) {
    #pragma omp simd
    for(unsigned int i = 0; i < size(); i++)
      m_Data[i] -= other.m_Data[i];

    return *this;
  }

  Vector<value_type, N>& operator*=(const_reference scalar) {
    #pragma omp simd
    for(unsigned int i = 0; i < size(); i++)
      m_Data[i] *= scalar;

    return *this;
  }

  Vector<value_type, N>& operator/=(const_reference scalar) {
    #pragma omp simd
    for(unsigned int i = 0; i < size(); i++)
      m_Data[i] /= scalar;

    return *this;
  }

};

#endif // _VECT_HPP
