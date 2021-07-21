#include <iostream>
#include <cassert>
#include <vector>
#include <locale>

using namespace std;

class ArrayInt {
protected:
    int m_lenght;
    int* m_data;
public:
    ArrayInt() : m_lenght(0), m_data(nullptr)
    {
    }
    ArrayInt(int lenght) : m_lenght(lenght), m_data(nullptr)
    {
        assert(lenght >= 0);
        if (lenght > 0)
        {
            m_data = new int[lenght];
        }
    }
    ~ArrayInt()
    {
        delete[] m_data;
    }
    void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_lenght = 0;
    }
    int getLenght() const
    {
        return m_lenght;
    }
    void printArray() const
    {
        cout << "Массив: ";
        for (int i = 0; i < m_lenght; i++)
        {
            cout << m_data[i] << ' ';
        }
        cout << endl;
    }
    int& operator[] (int index)
    {
        assert(index >= 0 && index < m_lenght);
        return m_data[index];
    }
    void resize(int newLenght)
    {
        if (newLenght == m_lenght)
        {
            return;
        }
        else if (newLenght <= 0)
        {
            erase();
            return;
        }
        int* data = new int[newLenght];
        if (m_lenght > 0)
        {
            int elementsToCopy = newLenght > m_lenght ? m_lenght : newLenght;
            for (int index = 0; index < elementsToCopy; index++)
            {
                data[index] = m_data[index];
            }
        }
        delete[] m_data;
        m_data = data;
        m_lenght = newLenght;
    }
    void insertBefore(int value, int index)
    {
        assert(index >= 0 && index <= m_lenght);
        int* data = new int[m_lenght + 1];
        for (int i = 0; i < index; ++i)
        {
            data[i] = m_data[i];
        }
        data[index] = value;
        for (int i = index; i < m_lenght; ++i)
        {
            data[i + 1] = m_data[i];
        }
        delete[] m_data;
        m_data = data;
        ++m_lenght;
    }
    void push_back(int value)
    {
        insertBefore(value, m_lenght);
    }
    void pop_back()
    {
        assert(m_lenght > 0);
        resize(m_lenght - 1);
    }
    void pop_front()
    {
        assert(m_lenght > 0);
        int* data = new int[m_lenght - 1];
        for (int i = 0; i < m_lenght; i++)
        {
            data[i] = m_data[i + 1];
        }
        delete[] m_data;
        m_data = data;
        --m_lenght;
    }
    void sortArray()
    {
        bool f = true;
        while (f)
        {
            f = false;
            for (int i = 0; i < m_lenght - 1; i++)
            {
                if (m_data[i] > m_data[i + 1])
                {
                    f = true;
                    swap(m_data[i + 1], m_data[i]);
                }
            }
        }
    }
    int getUniqCount()
    {
        if (m_lenght > 0)
        {
            int counter = 1;
            ArrayInt b(m_lenght);
            for (int i = 0; i < m_lenght; i++)
            {
                b[i] = m_data[i];
            }
            b.sortArray();
            int current = b[0];
            for (int i = 0; i < m_lenght; i++)
            {
                if (b[i] != current)
                {
                    current = b[i];
                    counter++;
                }
            }
            return counter;
        }
        else
        {
            return 0;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "RUS");

    // #1
    ArrayInt a;
    a.push_back(3);
    a.push_back(1);
    a.push_back(5);
    a.push_back(2);
    a.push_back(3);
    a.push_back(1);
    a.push_back(2);

    a.pop_back();
    a.printArray();
    a.pop_front();
    a.printArray();

    cout << endl << endl;

    // #2
    cout << "Количество уникальных элементов числового массива: " << a.getUniqCount() << endl;

    cout << endl << endl;

    // #1
    a.printArray();
    a.sortArray();
    a.printArray();

    cout << endl << endl;
    return 0;
}