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
        bool fill;
        Pair(K key, V value) : _key(key), _value(value), next(nullptr), fill(true) {}
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

    vector<Pair*> getData() const {
        return _data;
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
        _data[index]->fill = true;
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

unsigned long long int pearsonHash(const std::string& text) {
    unsigned long long int hash_value = 0;
    for (char c : text) {
        hash_value = c + (hash_value * 31);
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
