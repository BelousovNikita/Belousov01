#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <fstream>

#define N 4

using namespace std;

ifstream fin ("input.txt");
ofstream fout ("output.txt");

enum Symbols
{
    Empty,
    Numbers,
    Operations,
    Right_parenthesis,
    Left_parenthesis
};

class Operation
{
    map <char, int> priority;
    map <char, char> associativity;

public:
    Operation() = default;

    ~Operation() = default;

    void add (char operation, int prior, char L_R)
    {
        priority[operation] = prior;
        associativity[operation] = L_R;
    }

    int get_priority (char operation)
    {
        return priority[operation];
    }

    bool get_associativity (char operation)
    {
        return associativity[operation] == 'L';
    }
};

Symbols get_type (char symbol)
{
    if (isdigit(symbol))
    {
        return Numbers;
    } else if (symbol == '+' or symbol == '-' or symbol == '*' or symbol == '/')
    {
        return Operations;
    } else if (symbol == '(')
    {
        return Left_parenthesis;
    } else if (symbol == ')')
    {
        return Right_parenthesis;
    } else
    {
        return Empty;
    }
}

bool sort (queue <char>& out, Operation& operation)
{
    stack <char> Stack;
    char symbol;
    char temp;
    string expression;
    fin >> expression;
    for (int i = 0; i < expression.length(); i++)
    {
        symbol = expression[i];

        switch (get_type(symbol))
        {
            case Numbers:
            {
                out.push(symbol);
                break;
            }
            case Operations:
            {
                while (!Stack.empty())
                {
                    temp = Stack.top();
                    if ((get_type(temp) == Operations) and ((operation.get_associativity(symbol)) and (operation.get_priority(temp) >= operation.get_priority(symbol))) or ((!operation.get_associativity(symbol)) and (operation.get_priority(temp) > operation.get_priority((symbol)))))
                    {
                        out.push (temp);
                        Stack.pop();
                    } else
                    {
                        break;
                    }
                }
                Stack.push(symbol);
                break;
            }
            case Left_parenthesis:
            {
                Stack.push(symbol);
                break;
            }
            case Right_parenthesis:
            {
                while (!Stack.empty())
                {
                    temp = Stack.top();
                    if (temp == '(')
                    {
                        break;
                    } else
                    {
                        out.push(temp);
                        Stack.pop();
                    }
                }
                Stack.pop();
                break;
            }
            case Empty:
            {
                return false;
            }
        }
    }
    while (!Stack.empty())
    {
        out.push(Stack.top());
        Stack.pop();
    }
    return true;
}

int calculate (queue<char>* out)
{
    stack <int> Stack;
    char symbol;
    int value;
    int now;

    while (!out -> empty())
    {
        symbol = out -> front();
        switch (get_type(symbol))
        {
            case Numbers:
            {
                Stack.push(symbol - '0');
                break;
            }
            case Operations:
            {
                value = Stack.top();
                Stack.pop();
                now = Stack.top();
                Stack.pop();

                switch (symbol)
                {
                    case '+':
                    {
                        value = value + now;
                        break;
                    }
                    case '-':
                    {
                        value = now - value;
                        break;
                    }
                    case '*':
                    {
                        value = value * now;
                        break;
                    }
                    case '/':
                    {
                        if (value == 0)
                            throw invalid_argument ("ERROR");
                        value = now / value;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                Stack.push(value);
                break;
            }
            default:
            {
                throw invalid_argument ("ERROR");
            }
        }
        out -> pop();
    }
    if (Stack.size() == 1)
    {
        return Stack.top();
    } else
    {
        throw invalid_argument ("ERROR");
    }
}


int main()
{
    char operation;
    int priority;
    char associativity;
    queue <char> output;
    Operation oper;

    for (int i = 0; i < N; i++)
    {
        fin >> operation;
        fin >> priority;
        fin >> associativity;
        oper.add(operation, priority, associativity);
    }

    if (sort(output, oper))
    {
        try
        {
            fout << calculate(&output);
        } catch (invalid_argument &ex)
        {
            fout << ex.what();
        }
    }
    return 0;
}
