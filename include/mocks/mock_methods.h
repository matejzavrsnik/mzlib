//
// Copyright (c) 2019 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//
// Contains gmocks for testing functional stuff

#include "gmock/gmock.h"

#include <functional>

#ifndef MZLIB_MOCK_METHODS_H
#define	MZLIB_MOCK_METHODS_H

// will be assigned mocked functions when the mock is instantiated
static std::function<void()> _void_void;
static std::function<void(int)> _void_int;
static std::function<void(int,int)> _void_int_int;
static std::function<void(int,int,int)> _void_int_int_int;

// free functions
void free_void_void() { _void_void(); }
void free_void_int(int i) { _void_int(i); }
void free_void_int_int(int i, int j) { _void_int_int(i, j); }
void free_void_int_int_int(int i, int j, int k) { _void_int_int_int(i, j, k); }

// member functions & mock
class mock_methods
{

public:
   
   mock_methods()
   {
      _void_void = [this](){ void_void(); };
      _void_int = [this](int i){ void_int(i); };
      _void_int_int = [this](int i, int j){ void_int_int(i, j); };
      _void_int_int_int = [this](int i, int j, int k){ void_int_int_int(i, j, k); };
   }
   
   MOCK_METHOD0(void_void, void());
   MOCK_METHOD1(void_int, void(int));
   MOCK_METHOD2(void_int_int, void(int, int));
   MOCK_METHOD3(void_int_int_int, void(int, int, int));
};


#endif // MZLIB_MOCK_METHODS_H