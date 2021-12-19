#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <list>
#include <fstream>
#include <chrono>

#define base "test_data\\"

using namespace std;

mutex arr;
mutex link_stack;

string download_repository = "<a href=\"file://";

list <string> links_stack;
vector <string> links;

std::chrono::milliseconds interval(500);

void copy (string name)
{
    ifstream in;
    in.open(base + name);
    if (!in.is_open())
    {
        throw runtime_error("ERROR");
    }
    ofstream out;
    out.open(name);
    if (!out.is_open())
    {
        throw runtime_error("ERROR");
    }
    out << in.rdbuf();
    in.close();
    out.close();
}

void finder()
{
    string a;
    link_stack.lock();
    if (!links_stack.empty())
    {
        a = links_stack.front();
        links_stack.pop_front();
    } else
    {
        link_stack.unlock();
        return;
    }
    link_stack.unlock();
    arr.lock();
    copy(a);
    bool flagger = false;
    for (auto it = links.begin(); it != links.end(); it++)
    {
        if (*it == a)
        {
            flagger = true;
            break;
        }
    }
    if (!flagger) links.push_back(a);
    arr.unlock();
    string str;
    ifstream in(base + a);
    if (!in.is_open())
    {
        cout << "File open error: ";
        cout << a << endl;
        return;
    }
    size_t pos = 0;
    string link;
    link.resize(10);
    bool flag;
    while (!in.eof())
    {
        getline(in, str);
        while (pos != string::npos)
        {
            flag = false;
            pos = str.find (download_repository, pos);
            if (pos != string::npos)
            {
                link.clear();
                link.resize(10);
                pos += 16;
                int i = 0;
                while (str[pos]!= '"')
                {
                    link[i] = str[pos];
                    i++; pos++;
                }
                link_stack.lock();
                for (auto it = links_stack.begin(); it!= links_stack.end(); it++)
                {
                    if (*it == link)
                    {
                        flag = true;
                        break;
                    }
                }
                arr.lock();
                for (auto it = links.begin(); it != links.end(); it++)
                {
                    if (*it == link)
                    {
                        flag = true;
                        break;
                    }
                }
                arr.unlock();
                if (!flag)
                {
                    cout << link << endl;
                    links_stack.push_front(link);
                }
                link_stack.unlock();
            }
        }
    }
    finder();
}

void start (int n)
{
    vector<thread> threads;
    for (int i = 0; i < n; i++)
    {
        thread thr(finder);
        this_thread::sleep_for(interval);
        threads.emplace_back(move(thr));
    }
    for (int i = 0; i < n; i++)
        threads[i].join();
    cout << "Links found: " << links.size() - 1 << endl;
}

int main()
{
    string first_link;
    int thread_num;
    cin >> first_link >> thread_num;
    fstream in(base + first_link);
    try
    {
        if (!in.is_open())
        {
            throw runtime_error ("First link is invalid");
        }
        links_stack.push_front(first_link);
        auto started = std::chrono::high_resolution_clock::now();
        start(thread_num);
        auto finish = std::chrono::high_resolution_clock::now();
        cout << "Search time: " << std::chrono::duration_cast<chrono::microseconds>(finish - started).count() << " microseconds";
    } catch (runtime_error &ex) {
        cout << ex.what();
    }
    return 0;
}
