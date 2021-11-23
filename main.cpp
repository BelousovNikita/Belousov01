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
    int allocated_mem;

public:
    Vector(): elements (nullptr), size (0), allocated_mem(0) {}

    ~Vector()
    {
        delete[] elements;
    }

    void Add (T element)
    {
        if (size + 1 > allocated_mem) {
            allocated_mem == 0 ? allocated_mem = 1 : allocated_mem *= 2;
            T *arr = new T[allocated_mem];
            for (int i = 0; i < size; i++) {
                arr[i] = elements[i];
            }
            delete[] elements;
            elements = arr;
        }
        elements[size] = element;
        size++;
    }

    void Remove (int index)
    {
        if (index >= size || index < 0)
        {
            throw runtime_error("ERROR");
        }
        --size;
        T* arr = new T[size];
        for (int i = 0; i < size+1; i++)
        {
            if (i < index)
                arr[i] = elements[i];
            else if (i> index)
                arr[i-1] = elements[i];
        }
        elements = arr;
    }

    T& operator[] (int index)
    {
        if (index < 0 || index > size)
        {
            throw runtime_error("ERROR");
        }
        return elements[index];
    }

    void RSH (int c)
    {
        if (c < 0)
            throw runtime_error("ERROR");
        int k = c % size;
        if (k == 0)
            return;
        T *temp = new T[size];
        for (int i = 0; i < size; i++)
            temp[(i + k) % size] = elements[i];
        delete[] elements;
        elements = temp;
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
    try {
        for (int i = 0; i < N; i++) {
            fin >> command;
            if (command == "ADD") {
                T value;
                fin >> value;
                vector.Add(value);
            } else if (command == "REMOVE") {
                int index;
                fin >> index;
                vector.Remove(index);
            } else if (command == "PRINT") {
                int index;
                fin >> index;
                vector.print_index(index);
            } else if (command == "UPDATE") {
                int index;
                T value;
                fin >> index;
                fin >> value;
                vector.Update(value, index);
            } else if (command == "LSH") {
                int c;
                fin >> c;
                vector.LSH(c);
            } else if (command == "RSH") {
                int c;
                fin >> c;
                vector.RSH(c);
            }
        }
    } catch (runtime_error &ex) {
        cout << ex.what();
        exit(0);
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