#include "extendible.h"

ExtendibleHashing::ExtendibleHashing(int tamBucket)
    : tamBucket(tamBucket), profundidadGlobal(1) {
    directorio.resize(2);
    directorio[0] = new Bucket(profundidadGlobal, tamBucket);
    directorio[1] = new Bucket(profundidadGlobal, tamBucket);
}

ExtendibleHashing::~ExtendibleHashing() {
    for (auto bucket : directorio) {
        delete bucket;
    }
}

void ExtendibleHashing::doubleDirectory() {
    int size = directorio.size();
    directorio.resize(size * 2);
    for (int i = 0; i < size; ++i) {
        directorio[i + size] = directorio[i];
    }
    ++profundidadGlobal;
}

void ExtendibleHashing::splitBucket(int index) {
    Bucket* oldBucket = directorio[index];
    int profundidadLocal = oldBucket->profundidadLocal;

    
    if (profundidadLocal == profundidadGlobal) {
        doubleDirectory();
    }

    Bucket* newBucket = new Bucket(profundidadLocal + 1, tamBucket);
    oldBucket->profundidadLocal++;

    
    int dirSize = directorio.size();
    for (int i = 0; i < dirSize; ++i) {
        if (directorio[i] == oldBucket && (i & (1<<profundidadLocal)) != 0) {
            directorio[i] = newBucket;
        }
    }

    std::vector<int> tempData = oldBucket->data;
    oldBucket->data.clear();
    for (int key : tempData) {
        int newIndex = hash(key);
        directorio[newIndex]->data.push_back(key);
    }
}

void ExtendibleHashing::insert(int key) {
    int index = hash(key);
    Bucket* bucket = directorio[index];

    if (bucket->isFull()) {
        splitBucket(index);
        index = hash(key);
        bucket = directorio[index];
    }
    bucket->data.push_back(key);
}

bool ExtendibleHashing::find(int key) const {
    int index = hash(key);
    for (int value : directorio[index]->data) {
        if (value == key) {
            return true;
        }
    }
    return false;
}

void ExtendibleHashing::remove(int key) {
    int index = hash(key);
    auto& data = directorio[index]->data;
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (*it == key) {
            data.erase(it);
            return;
        }
    }
}

void ExtendibleHashing::print() const {
    std::cout<<"Profundidad global: "<<profundidadGlobal<<std::endl;
    for (size_t i = 0; i < directorio.size(); ++i) {
        std::cout<<"Bucket "<<i<<" (Profundidad local: "<<directorio[i]->profundidadLocal<<"): ";
        for (int value : directorio[i]->data) {
            std::cout<<value<<" ";
        }
        std::cout<<std::endl;
    }
}
