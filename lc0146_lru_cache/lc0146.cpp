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
#include <unordered_set>
#include <unordered_map>
#include <random>

class LRUCache {
 private:
    struct LRUNode
    {
        int value;
        int prev_key;
        int next_key;
    };

    using Map = std::unordered_map<int, LRUNode >;

    int m_capacity;

    Map m_map;
    int m_head_key;
    int m_tail_key;


 public:
    LRUCache(int capacity):
        m_capacity(capacity)
    {

    }

    void adjust_value_pos(Map::iterator & it, int key)
    {
        if (m_map.size() != 1 && key != m_tail_key)
        {
            Map::iterator tail_node = m_map.find(m_tail_key);
            //Map::
            int node_before_key = it->second.prev_key;
            int node_after_key = it->second.next_key;


            Map::iterator node_after =  m_map.find(node_after_key);
            if (key != m_head_key)
            {
                Map::iterator node_before = m_map.find(node_before_key);
                node_before->second.next_key = node_after_key;
                node_after->second.prev_key = node_before_key;
            } else
            {
                node_after->second.prev_key = -1;
                m_head_key = node_after_key;
            }
            tail_node->second.next_key = key;
            it->second.prev_key = m_tail_key;
            it->second.next_key = -1;
            m_tail_key = key;
        }

    }

    int get(int key)
    {
        auto it = m_map.find(key);
        if (it == m_map.end())
            return -1;

        adjust_value_pos(it, key);
        return it->second.value;
    }

    void dump_list()
    {
        std::cout<<"list : [(";
        if (m_map.size())
        {
            int index = m_head_key;
            while (index != m_tail_key)
            {
                Map::iterator curr = m_map.find(index);
                std::cout << curr->second.value << ",";
                index = curr->second.next_key;
            };
            std::cout<<m_map[index].value;
        }

        std::cout<<"),(";
        if (m_map.size())
        {
            int index = m_tail_key;
            while (index != m_head_key)
            {
                Map::iterator curr = m_map.find(index);
                std::cout<<curr->second.value<<",";
                index = curr->second.prev_key;
            };
            std::cout<<m_map[index].value;
        }
        std::cout<<")]";

    }

    void put(int key, int value)
    {
        std::size_t init_size = m_map.size();
        auto it = m_map.find(key);
        if (it == m_map.end())
        {
            auto reset_res = m_map.insert(std::make_pair(key, LRUNode{value, -1 , -1} ));
            it = reset_res.first;

            if (init_size == 0)
            {
                m_head_key = key;
                m_tail_key = key;
            } else
            {
                //append to the end of list
                Map::iterator tail = m_map.find(m_tail_key);
                tail->second.next_key = key;
                it->second.prev_key = m_tail_key;

                m_tail_key = key;
            }

            if (init_size == m_capacity)
            {
                //we should evict lru node (head of the list)
                Map::iterator head = m_map.find(m_head_key);

                int next_after_head = head->second.next_key;
                Map::iterator next_after_head_node = m_map.find(next_after_head);
                next_after_head_node->second.prev_key = -1;
                m_head_key = next_after_head;

                m_map.erase(head);
            }

        } else
        {
            it->second.value = value;
            adjust_value_pos(it, key);

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


        PyObject_wrapper::iterator operation_it = operations_parsed.begin();
        PyObject_wrapper::iterator args_it = args_parsed.begin();


        LRUCache lruCache(args_it->begin()->asInt());
        std::cout<<"LRUCache ("<<args_it->begin()->asInt()<<")"<<std::endl;

        ++operation_it;
        ++args_it;



        std::vector<int> arg_vec;

        for (;operation_it != operations_parsed.end() && args_it != args_parsed.end(); ++operation_it, ++args_it)
        {
            std::string op = (*operation_it).str().asString();
            std::string arg;
            arg_vec.resize(0);

            PyObject_wrapper arg_object = *args_it;
            auto arg_int_view = arg_object | std::views::transform( [] (const PyObject_wrapper & wrapper) {return wrapper.asInt();});
            std::ranges::copy(arg_int_view, std::back_inserter(arg_vec));

            if ((*args_it).len())
            {
                arg = (*(*args_it).begin()).str().asString();
            }
            if (op == "LRUCache")
            {
                std::cout<<"null"<<std::endl;
            }
            if (op == "put")
            {
                //bool res = randomizedCollection.insert((*(*args_it).begin()).asInt());
                //std::cout<<(res ? "true" : "false")<<std::endl;
                std::cout<<"    put("<<arg_vec[0]<<", "<<arg_vec[1]<<")"<<std::endl;
                lruCache.put(arg_vec[0], arg_vec[1]);
            }

            if (op == "get")
            {
                //bool res = randomizedCollection.remove((*(*args_it).begin()).asInt());
                std::cout<<"    get("<<arg_vec[0]<<") => ";
                int get = lruCache.get(arg_vec[0]);
                std::cout<<get<<std::endl;
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


void test0_1()
{
    const char* operations = R"[=](["LRUCache","put","put","get", "put", "get"])[=]";
    const char* args = R"[=]([[2],[1,1],[2,2],[1],[3,3],[2] ])[=]";

    test(std::string(operations), std::string(args));
}


void test0_2()
{
    const char* operations = R"[=](["LRUCache","put","put","put", "get", "get", "get", "put",  "get", "get"])[=]";
    const char* args = R"[=]([[3],[1,1],[2,2],[3,3],[1],[2],[3],[4,4], [1], [2] ])[=]";

    test(std::string(operations), std::string(args));
}


void test1()
{

    //const char * operations = R"[=](["RandomizedCollection", "insert", "insert", "insert", "getRandom", "remove", "getRandom"])[=]";
    //const char * args = R"[=]([[], [1], [1], [2], [], [1], []])[=]";
    const char * operations = R"[=](["LRUCache","put","put","get","put","get","put","get","get","get"])[=]";
    const char * args = R"[=]([[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]])[=]";

    test(std::string(operations), std::string(args));
    //answer should be 595352
}


void test2()
{
    const char * operations = R"[=](["LRUCache","put","put","put","put","get","get"])[=]";
    const char * args = R"[=]([[2],[2,1],[1,1],[2,3],[4,1],[1],[2]])[=]";

    test(std::string(operations), std::string(args));
    //answer should be 595352

}


int main(int argc, char** argv)
{
   test2();

}

