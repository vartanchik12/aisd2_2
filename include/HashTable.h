#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;

template<typename K, typename T>
class HashTable {
private:
    struct Pair {
        K _key;
        T _value;
        Pair* _next;
        Pair(K key, T value) : _key(key), _value(value), _next(nullptr) {}
    };
    vector<Pair*> _data;
    size_t _size;
    size_t HashFunction(K key) const {
        const double W = 0.6180339887;
        return static_cast<size_t>(_size * (key * W - static_cast<int>(key * W)));
    }
public:
    HashTable(size_t size) {
        if (size == 0) {
            throw invalid_argument("Size is zero");
        }
        _size = size;
        _data.resize(size, nullptr);
    }

    HashTable(const HashTable& other) {
        _size = other._size;
        _data.resize(_size, nullptr);
        for (size_t i = 0; i < _size; i++) {
            Pair* current = other._data[i];
            while (current) {
                insert(current->_key, current->_value);
                current = current->_next;
            }
        }
    }

    ~HashTable() {
        for (size_t i = 0; i < _size; i++) {
            Pair* current = _data[i];
            while (current) {
                Pair* tmp = current;
                current = current->_next;
                delete tmp;
            }
        }
    }

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            for (size_t i = 0; i < _size; i++) {
                Pair* current = _data[i];
                while (current) {
                    Pair* tmp = current;
                    current = current->_next;
                    delete tmp;
                }
            }
            _size = other._size;
            _data.resize(_size, nullptr);
            for (size_t i = 0; i < _size; i++) {
                Pair* current = other._data[i];
                while (current) {
                    insert(current->_key, current->_value);
                    current = current->_next;
                }
            }
        }
        return *this;
    }

    size_t GetSize() const {
        return _size;
    }

    void print() const {
        for (size_t i = 0; i < _size; i++) {
            Pair* current = _data[i];
            if (current) {
                cout << current->_key << ":";
            }
            else {
                continue;
            }
            while (current) {
                cout << " " << current->_value;
                current = current->_next;
            }
            cout << endl;
        }
    }

    void insert(K key, T value) {
        size_t index = HashFunction(key);
        Pair* NewPair = new Pair(key, value);
        NewPair->_next = _data[index];
        _data[index] = NewPair;
    }

    void insert_or_assign(K key, T value) {
        size_t index = HashFunction(key);
        Pair* current = _data[index];
        while (current) {
            if (current->_key == key) {
                current->_value = value;
                return;
            }
            current = current->_next;
        }
        insert(key, value);
    }

    bool contains(T value) const {
        for (size_t i = 0; i < _size; i++) {
            Pair* current = _data[i];
            while (current) {
                if (current->_value == value) {
                    return true;
                }
                current = current->_next;
            }
        }
        return false;
    }

    T* search(K key) const {
        size_t index = HashFunction(key);
        Pair* current = _data[index];
        while (current) {
            if (current->_key == key) {
                return &(current->_value);
            }
            current = current->_next;
        }
        return nullptr;
    }

    bool erase(K key) {
        size_t index = HashFunction(key);
        Pair* current = _data[index];
        Pair* prev = nullptr;
        while (current) {
            if (current->_key == key) {
                if (prev) {
                    prev->_next = current->_next;
                }
                else {
                    _data[index] = current->_next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->_next;
        }
        return false;
    }

    int count(K key) const {
        int count = 0;
        size_t index = HashFunction(key);
        Pair* current = _data[index];
        while (current) {
            if (current->_key == key) {
                count++;
            }
            current = current->_next;
        }
        return count;
    }
};


HashTable<int, int> countDuplicates(const vector<int>& arr) {
    size_t size = arr.size();
    HashTable<int, int> ht(size);

    for (const auto& num : arr) {
        int* count = ht.search(num);
        if (count) {
            ht.insert_or_assign(num, *count + 1);
        }
        else {
            ht.insert(num, 1);
        }
    }

    return ht;
}
