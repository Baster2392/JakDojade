#pragma once

class String {
public:
    String()
    {
        this->length = 0;
        this->data = nullptr;
    }

    String(const String& other)
    {
        this->length = other.length;
        this->data = new char[length + 1];

        for (size_t i = 0; i < length + 1; ++i) {
            data[i] = other.data[i];
        }
    }

    String(const char* cString) : length(0), data(nullptr) {
        while (cString[length] != '\0') {
            ++length;
        }
        data = new char[length + 1];
        for (size_t i = 0; i < length + 1; ++i) {
            data[i] = cString[i];
        }
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            for (size_t i = 0; i < length + 1; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~String() {
        delete[] data;
    }

    size_t size() const {
        return length;
    }

    const char* c_str() const {
        return data;
    }

    void append(char c) {
        char* newData = new char[length + 2];
        for (size_t i = 0; i < length; ++i) {
            newData[i] = data[i];
        }
        newData[length] = c;
        newData[length + 1] = '\0';
        delete[] data;
        data = newData;
        ++length;
    }

    void append(const String& other) {
        size_t newLength = length + other.length;
        char* newData = new char[newLength + 1];
        for (size_t i = 0; i < length; ++i) {
            newData[i] = data[i];
        }
        for (size_t i = 0; i < other.length + 1; ++i) {
            newData[length + i] = other.data[i];
        }
        delete[] data;
        data = newData;
        length = newLength;
    }

private:
    size_t length;
    char* data;
};
