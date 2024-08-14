#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <charconv>
#include <map>
#include <ranges>
#include <sstream>

#include <libtaskutils/python_exceptions.h>
#include <libtaskutils/python_utils.h>

class Trie
{
 public:

    struct TrieNode
    {
        char symbol;
        TrieNode * firstchild;
        TrieNode * sibling;
        bool is_word;
        TrieNode():firstchild(nullptr),sibling(nullptr), symbol(0), is_word(false)
        {
        }

        TrieNode * find_child_symbol(char symbol)
        {
            TrieNode * candidate = firstchild;
            while (candidate)
            {
                if (candidate->symbol == symbol)
                {
                    return candidate;
                }
                candidate = candidate->sibling;
            }
            return nullptr;
        }

        TrieNode * append_child_symbol(char symbol)
        {
            TrieNode * new_symbol = new TrieNode();
            new_symbol->symbol = symbol;

            TrieNode * old_first = firstchild;
            firstchild = new_symbol;
            new_symbol->sibling = old_first;
            return new_symbol;
        }
    };

    TrieNode root;

    Trie()
    {
    }
    void insert(std::string word)
    {
        TrieNode * current = &root;
        for(char ch : word)
        {
            TrieNode * new_current = current->find_child_symbol(ch);
            if (new_current == nullptr)
            {
                new_current = current->append_child_symbol(ch);
            }
            current = new_current;
        }
        if (current != &root)
            current->is_word = true;
    }


    bool search(std::string word)
    {
        TrieNode * current = &root;
        for(char ch : word)
        {
            TrieNode * new_current = current->find_child_symbol(ch);
            if (new_current == nullptr)
            {
                return false;
            }
            current = new_current;
        }
        return current != &root && current->is_word;
    }


    bool startsWith(std::string prefix)
    {
        TrieNode * current = &root;
        for(char ch : prefix)
        {
            TrieNode * new_current = current->find_child_symbol(ch);
            if (new_current == nullptr)
            {
                return false;
            }
            current = new_current;
        }
        return current != &root;
    }

    ~Trie()
    {
        TrieNode * current = &root;
        TrieNode * child = current->firstchild;
        while (child)
        {
            TrieNode * next_child = child->sibling;
            delete_node_recursive(child);
            child = next_child;
        }

    }

 private:
    void delete_node_recursive(TrieNode * node)
    {
        TrieNode * child = node->firstchild;
        while (child)
        {
            TrieNode * next_child = child->sibling;
            delete_node_recursive(child);
            child = next_child;
        }

    }

};

int test(const std::string & operations_python, const std::string & args_python)
{
    int res = -1;
    try
    {
        PythonInterp interp;
        PyObject_wrapper operations_parsed = interp.execString(operations_python.c_str());
        PyObject_wrapper args_parsed = interp.execString(args_python.c_str());

        Trie trie;

        PyObject_wrapper::iterator operation_it = operations_parsed.begin();
        PyObject_wrapper::iterator args_it = args_parsed.begin();

        for (;operation_it != operations_parsed.end() && args_it != args_parsed.end(); ++operation_it, ++args_it)
        {
            std::string op = (*operation_it).str().asString();
            std::string arg;
            if ((*args_it).len())
            {
                arg = (*(*args_it).begin()).str().asString();
            }
            std::cout<<op<<" "<<arg<<" ";
            if (op == "Trie")
            {
                std::cout<<std::endl;
            }
            if (op == "insert")
            {
                trie.insert(arg);
                std::cout<<std::endl;
            }

            if (op == "search")
            {
                if (arg == "beer")
                {
                   // std::cout<<std::endl;
                }
                std::cout<<trie.search(arg)<<std::endl;
            }

            if (op == "startsWith")
            {
                std::cout<<trie.startsWith(arg)<<std::endl;
            }

        }


        //res = solution.eraseOverlapIntervals(intervals);

    } catch (PythonParserException & exc)
    {
        std::cerr<<exc.what()<<std::endl;
    }
    std::cout<<"res : "<<res<<std::endl;
    return res;
}

void test1()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    //const char * operations = R"[=](["Trie","insert","insert","insert","insert","insert","insert","search","search","search","search","search","search","search","search","search","startsWith","startsWith","startsWith","startsWith","startsWith","startsWith","startsWith","startsWith","startsWith"])[=]";
    //const char * args = R"[=]([[],["app"],["apple"],["beer"],["add"],["jam"],["rental"],["apps"],["app"],["ad"],["applepie"],["rest"],["jan"],["rent"],["beer"],["jam"],["apps"],["app"],["ad"],["applepie"],["rest"],["jan"],["rent"],["beer"],["jam"]])[=]";


    const char * operations = R"[=](["Trie","insert","insert","insert","insert","insert","insert","search","search","search","search","search","search","search","search","search","startsWith","startsWith","startsWith","startsWith","startsWith","startsWith","startsWith","startsWith","startsWith"])[=]";
    const char * args = R"[=]([[],["app"],["apple"],["beer"],["add"],["jam"],["rental"],["apps"],["app"],["ad"],["applepie"],["rest"],["jan"],["rent"],["beer"]])[=]";
    //const char * operations = R"[=](["Trie", "insert", "insert", "insert", "search", "search", "search"])[=]";
    //const char * args = R"[=]([[], ["app"], ["apple"], ["beer"], ["app"], ["apple"], ["beer"] ])[=]";

    test(std::string(operations), std::string(args));
    //answer should be 595352
}



int main(int argc, char** argv)
{
   test1();

}

