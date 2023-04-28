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

        for (int i = 0; i < this->length + 1; i++) {
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
        for (int i = 0; i < this->length + 1; i++)
        {
            this->data[i] = cString[i];
        }
    }

    String& operator=(const String& other)
    {
        if (this != &other) {
            
            if (this->data != nullptr)
            {
                delete[] this->data;
            }

            this->length = other.length;
            this->data = new char[this->length + 1];

            for (int i = 0; i < this->length + 1; i++)
            {
                this->data[i] = other.data[i];
            }
        }
        return *this;
    }

    char operator[](int index)
    {
        return this->data[index];
    }

    ~String()
    {
        if (this->data != nullptr)
        {
            delete[] this->data;
        }
    }

    int size()
    {
        return this->length;
    }

    const char* c_str()
    {
        return this->data;
    }

    void append(char c) {
        char* newData = new char[this->length + 2];
        for (int i = 0; i < this->length; i++)
        {
            newData[i] = data[i];
        }

        newData[this->length] = c;
        newData[this->length + 1] = '\0';

        if (this->data != nullptr)
        {
            delete[] this->data;
        }

        this->data = newData;
        this->length++;
    }

    void append(String& other) {
        int newLength = this->length + other.length;
        char* newData = new char[newLength + 1];
        for (int i = 0; i < this->length; i++)
        {
            newData[i] = this->data[i];
        }

        for (int i = 0; i < other.length + 1; i++)
        {
            newData[this->length + i] = other.data[i];
        }

        if (this->data != nullptr)
        {
            delete[] this->data;
        }

        this->data = newData;
        this->length = newLength;
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
    int length;
    char* data;
};
