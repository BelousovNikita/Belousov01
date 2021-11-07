#include<iostream>
#include<string>
#include <fstream>

using namespace std;

ifstream fin ("input.txt");
ofstream fout ("output.txt");

template <typename T>
class Vector {
    T* elements;
    int size;

public:
    Vector(): elements (nullptr), size (0) {}

    ~Vector()
    {
        delete[] elements;
    }

    void Add (T element)
    {
        ++size;
        T* arr = new T[size];

        for (int i = 0; i < size - 1; i++)
        {
            arr[i] = elements[i];
        }
        arr[size-1] = element;
        delete[] elements;
        elements = new T[size];

        for (int i = 0; i < size; i++)
        {
            elements[i] = arr[i];
        }
        delete[] arr;
    }

    void Remove (int index)
    {
        if (index >= size || index < 0)
        {
            fout << "ERROR";
            exit (0);
        }
        --this->size;
        T* arr = new T[this->size];
        for (int i = 0; i < this->size+1; i++)
        {
            if (i < index)
                arr[i] = this->elements[i];
            else if (i> index)
                arr[i-1] = this->elements[i];
        }
        delete[] elements;
        elements = new T[size];

        for (int i = 0; i < size; i++)
        {
            elements[i] = arr[i];
        }
        delete[] arr;
    }

    T& operator[] (int index)
    {
       if (index < 0 || index > this->size)
       {
           fout << "ERROR";
           exit(0);
       }
        return this->arr[index];
    }

    void RSH (int c)
    {
        if (c < 0)
            exit(0);
        if (c % size == 0)
            return;
        T temp;
        int count = 1;
        c = c % size;

        while (count <= c)
        {
            temp = elements [size-1];
            for (int i = size - 1; i > 0; i--)
            {
                elements[i] = elements[i-1];
            }
            elements[0] = temp;
            count++;
        }
    }

    void LSH (int c)
    {
        RSH (size - (c % size));
    }

    void print ()
    {
        for (int i = 0; i < size; i++)
            fout << elements[i] << endl;
    }

    void Update (T value, int index)
    {
        if (index < 0 || index >= size)
            exit(0);
        this->elements[index] = value;
    }

    void print_index (int index)
    {
        if (index < 0 || index >= size)
        {
            fout << "ERROR";
            exit(0);
        }
        fout << elements[index] << endl;
    }

};

template <typename T>
void command (int N)
{
    string command;
    Vector<T> vector;
    for (int i = 0; i < N; i++)
    {
        fin >> command;
        if (command == "ADD")
        {
            T value;
            fin >> value;
            vector.Add(value);
        }

        else if (command == "REMOVE")
        {
            int index;
            fin >> index;
            vector.Remove(index);
        }

        else if (command == "PRINT")
        {
            int index;
            fin >> index;
            vector.print_index(index);
        }

        else if (command == "UPDATE")
        {
            int index;
            T value;
            fin >> index;
            fin >> value;
            vector.Update(value, index);
        }

        else if (command == "LSH")
        {
            int c;
            fin >> c;
            vector.LSH(c);
        }

        else if (command == "RSH")
        {
            int c;
            fin >> c;
            vector.RSH(c);
        }
    }

    vector.print();
}

int main()
{
    char type_of_vector;
    fin >> type_of_vector;
    int N;
    fin >> N;

    if (type_of_vector == 'I') command<int>(N);
    else if (type_of_vector == 'D')  command<double>(N);
    else command <string>(N);

    return 0;
}
