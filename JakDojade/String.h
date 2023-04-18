#pragma once
#include <string.h>

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
        this->data = new char[this->length + 1];

        for (size_t i = 0; i < this->length + 1; ++i) {
            this->data[i] = other.data[i];
        }
    }

    String(const char* cString)
    {
        this->length = 0;
        this->data = nullptr;

        while (cString[this->length] != '\0') {
            this->length++;
        }
        this->data = new char[this->length + 1];
        for (size_t i = 0; i < this->length + 1; ++i) {
            this->data[i] = cString[i];
        }
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] this->data;
            this->length = other.length;
            this->data = new char[this->length + 1];
            for (size_t i = 0; i < this->length + 1; ++i) {
                this->data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~String() {
        delete[] this->data;
    }

    size_t size() const {
        return this->length;
    }

    const char* c_str() const {
        return this->data;
    }

    void append(char c) {
        char* newData = new char[this->length + 2];
        for (size_t i = 0; i < this->length; i++) {
            newData[i] = data[i];
        }

        newData[this->length] = c;
        newData[this->length + 1] = '\0';
        delete[] this->data;
        this->data = newData;
        this->length++;
    }

    void append(const String& other) {
        size_t newLength = this->length + other.length;
        char* newData = new char[newLength + 1];
        for (size_t i = 0; i < this->length; ++i) {
            newData[i] = this->data[i];
        }
        for (size_t i = 0; i < other.length + 1; ++i) {
            newData[this->length + i] = other.data[i];
        }

        delete[] this->data;

        this->data = newData;
        this->length = newLength;
    }

    int toNumber()
    {
        int number = 0;

        for (int i = 0; i < this->length; i++)
        {

        }
    }

    bool equal(char* str)
    {
        if (this->length == strlen(str))
        {
            for (int i = 0; i < this->length; i++)
            {
                if (this->data[i] != str[i])
                {
                    return false;
                }
            }

            return true;
        }

        return false;
    }

    bool equal(const char* str)
    {
        if (this->length == strlen(str))
        {
            for (int i = 0; i < this->length; i++)
            {
                if (this->data[i] != str[i])
                {
                    return false;
                }
            }

            return true;
        }

        return false;
    }

private:
    size_t length;
    char* data;
};
