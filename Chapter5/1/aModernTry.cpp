// #include<cstdlib>
#include<iostream>
#include<memory>
// using namespace std;
// typedef long data_t;
using data_t=long;
using vec_ptr=vec_rec*;
struct vec_rec{
    long len;
    // data_t *data;
    std::unique_ptr<data_t[]> data;
};

vec_ptr new_vec(long len)
{
    auto result=std::make_unique<vec_rec>();
    // data_t *data=nullptr;
    result->data=std::make_unique<data_t[]>(len);
    result->len=len;
    return result.get();
}

