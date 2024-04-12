#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename K, typename V>
class HashTable {
private:
    struct Pair {
        K _key;
        V _value;
        Pair* next;
        Pair(K key, V value) : _key(key), _value(value), next(nullptr) {}
    };
    vector<Pair*> _data;
    size_t _size;
    size_t hashFunction(K key) {
        return key % _size;
    };
public:
    HashTable(size_t size) {
        if (size == 0)
            throw invalid_argument("Size zero");
        _size = size;
        _data.resize(size);
    };

    HashTable(size_t size, const V& max, const V& min) {
        if (size == 0)
            throw invalid_argument("Size zero");
        _size = size;
        _data.resize(size);
        for (int i = 0; i < size; ++i) {
            V value = rand() % (max - min + 1) + min;
            _data[i] = new Pair(i, value);
        }
    };

    HashTable(const HashTable& other) {
        _size = other.get_size();
        _data.resize(_size);
        for (size_t i = 0; i < _size; ++i) {
            Pair* current = other._data[i];
            while (current != nullptr) {
                insert(current->_key, current->_value);
                current = current->next;
            }
        }
    }

    ~HashTable() {
        for (size_t i = 0; i < _size; i++) {
            Pair* current = _data[i];
            while (current) {
                Pair* tmp = current;
                current = current->next;
                delete tmp;
            }
        }
        _size = 0;
    }

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            for (size_t i = 0; i < _size; i++) {
                Pair* current = _data[i];
                while (current != nullptr) {
                    Pair* tmp = current;
                    current = current->next;
                    delete tmp;
                }
            }
            _size = other._size;
            _data.resize(size);
            for (size_t i = 0; i < _size; ++i) {
                Pair* current = other._data[i];
                while (current != nullptr) {
                    insert(current->key, current->value);
                    current = current->next;
                }
                ++_size;
            }

        }
        return *this;
    };

    size_t getSize() const {
        return _size;
    }

    void print() {
        for (int i = 0; i < _size; ++i) {
            Pair* current = _data[i];
            if (current)
                cout << current->_key << ":";
            while (current) {
                cout << current->_value << " ";
                current = current->next;
            }
            cout << endl;
        }
    };

    void insert(K key, V value) {
        size_t index = hashFunction(key);
        Pair* newPair = new Pair(key, value);
        newPair->next = _data[index];
        _data[index] = newPair;
    }

    void insertOrAssign(K key, V value) {
        size_t index = hashFunction(key);
        Pair* current = _data[index];
        while (current) {
            if (current->_key == key) {
                current->_value = value;
                return;
            }
            current = current->next;
        }
        insert(key, value);
    };

    bool erase(K key) {
        size_t index = hashFunction(key);
        Pair* current = _data[index];
        Pair* prev = nullptr;
        if (current) {
            if (prev) {
                prev->next = current->next;
            }
            else {
                _data[index] = current->next;
            }
            delete current;
            return true;
            prev = current;
            current = current->next;
        }
        return false;
    }

    bool contains(V value) const {
        for (int i = 0; i < _size; ++i) {
            Pair* current = _data[i];
            while (current) {
                if (current->_value == value)
                    return true;
                current = current->next;
            }
        }
        return false;
    };

    V* search(K key) {
        size_t index = hash(key);
        Pair* tmp = _data[index];
        while (tmp) {
            if (tmp->_key != key)
                tmp = tmp->next;
            return &(tmp->_value);
        }
    };

    int count(K key) {
        size_t index = hash(key);
        int count = 0;
        Pair* tmp = _data[index];
        while (tmp) {
            ++count;
            tmp = tmp->next;
        }
        return count;
    };
};

unsigned long long int pearsonHash(const string& text){
    unsigned long long int hash_value = 0;
    const unsigned char T[256] = {
       98,  6, 85,150, 36, 23,112,164,135,207,169,  5, 26, 64,165,219,
       61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115,
       90,168,156,203,177,120,  2,190,188,  7,100,185,174,243,162, 10,
      237, 18,253,225,  8,208,172,244,255,126,101, 79,145,235,228,121,
      123,251, 67,250,161,  0,107, 97,241,111,181, 82,249, 33, 69, 55,
       59,153, 29,  9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222,
      197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186,
       39,158,178,187,131,136,  1, 49, 50, 17,141, 91, 47,129, 60, 99,
      154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254,
      133,232,196,144,198,124, 53,  4,108, 74,223,234,134,230,157,139,
      189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44,
      183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12,
      221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166,
        3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117,
      238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110,
       43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239
    };
    for (char c : text){
        hash_value = T[hash_value ^ c];
    }
    return hash_value;
}

bool compareHashes(unsigned long long int saved_hash, const std::string& input_text) {
    unsigned long long int input_hash = pearsonHash(input_text);
    if (saved_hash == input_hash) {
        return true;
    }
    return false;
}

void ioLine() {
    string first_string;
    cout << "Write your first string: ";
    cin >> first_string;
    unsigned long long saved_hash = pearsonHash(first_string);

    string second_string;
    cout << "Write your second string: ";
    cin >> second_string;

    if (compareHashes(saved_hash, second_string)) {
        cout << "==" << endl;
    }
    else {
        cout << "!=" << endl;
    }
}
