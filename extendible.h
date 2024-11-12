#ifndef EXTENDIBLE_HASHING_H
#define EXTENDIBLE_HASHING_H

#include <iostream>
#include <vector>

class Bucket{
public:
    int profundidadLocal;
    int size;
    std::vector<int> data;
    Bucket(int depth, int size) : profundidadLocal(depth), size(size){}
    bool isFull() const{ return data.size() >= size; }
};

class ExtendibleHashing{
private:
    int tamBucket;
    int profundidadGlobal;
    std::vector<Bucket*> directorio;

    int hash(int key) const{ return key & ((1 << profundidadGlobal) - 1); }
    void doubleDirectory();
    void splitBucket(int index);

public:
    ExtendibleHashing(int tamBucket);
    ~ExtendibleHashing();
    void insert(int key);
    bool find(int key) const;
    void remove(int key);
    void print() const;
};

#endif
