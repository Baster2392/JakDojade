#pragma once

template <typename T>
class Vector
{
private:

	T* tab;
	int avalibleSize;
	int currentSize;

public:

	Vector()
	{
		this->tab = new T[1];
		this->avalibleSize = 1;
		this->currentSize = 0;
	}
	
	~Vector()
	{
		if (this->tab != nullptr)
		{
			delete[] this->tab;
		}
	}

	void pushBack(T value)
	{
		if (this->currentSize == this->avalibleSize)
		{
			T* newTab = new T[this->avalibleSize * 2];
			for (unsigned int i = 0; i < this->avalibleSize; i++)
			{
				newTab[i] = this->tab[i];
			}

			if (this->tab != nullptr)
			{
				delete[] this->tab;
			}

			this->avalibleSize *= 2;
			this->tab = newTab;
		}

		this->currentSize++;
		this->tab[this->currentSize - 1] = value;
	}

	T popBack()
	{
		if (this->currentSize > 0)
		{
			this->currentSize--;
		}

		return this->tab[this->currentSize];
	}

	void erase(int index)
	{
		if (index >= this->currentSize)
		{
			return;
		}

		for (int i = index; i < this->currentSize - 1; i++)
		{
			this->tab[i] = this->tab[i + 1];
		}

		this->currentSize--;
	}

	int getSize()
	{
		return this->currentSize;
	}

	T& operator[](int index)
	{
		return this->tab[index];
	}

	void clear()
	{
		this->currentSize = 0;
	}

};
