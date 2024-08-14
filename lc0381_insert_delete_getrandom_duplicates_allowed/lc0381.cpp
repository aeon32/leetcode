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

class RandomizedCollection1 {
    public:

    using IndexesSet = std::unordered_set<int>;
    using Map = std::unordered_map<int, IndexesSet>;


    using RandomAccessVector = std::vector<int>;

    Map map;
    RandomAccessVector random_vector;

    static constexpr std::size_t INITIAL_SIZE = 30000;
    std::size_t free_block_index;

    std::default_random_engine random_engine;
    std::uniform_int_distribution<std::size_t> distribution;

    RandomizedCollection1()
    :free_block_index(0),
    distribution(0)
    {
        map.reserve(INITIAL_SIZE);
        random_vector.reserve(INITIAL_SIZE);
    }

    bool insert(int val) {
        Map::iterator it = map.find(val);
        bool res = (it == map.end() || it->second.empty());
        if (it == map.end())
        {
            it = map.insert(std::make_pair(val, IndexesSet())).first;
        }
        it->second.insert(random_vector.size());
        random_vector.push_back(val);
        return res;
    }

    bool remove(int val) {
        Map::iterator it = map.find(val);
        bool res = (it != map.end() && !it->second.empty());
        if (!res)
            return false;

        if (it != map.end())
        {
            IndexesSet::iterator it_to_delete = it->second.begin();

            int vector_index_to_delete = (*it_to_delete);
            int back_value = random_vector.back();
            random_vector[vector_index_to_delete] = back_value;

            it->second.erase(it_to_delete);
            random_vector.pop_back();

            IndexesSet & back_value_set = map[back_value];
            IndexesSet::iterator back_value_it = back_value_set.find(random_vector.size());
            if (back_value_it != back_value_set.end())
            {
                back_value_set.erase(back_value_it);
                back_value_set.insert(vector_index_to_delete);
            }

        }
        return res;
    }

    int getRandom()
    {
        std::size_t random_index = distribution(random_engine) % random_vector.size();
        //std::cout<<random_vector.size()<<" "<<random_index<<std::endl;
        return random_vector[random_index ];

    }
};


class RandomizedCollection
{

 public:
    struct ValWithIndex
    {
        int val;
        std::size_t index;
    };

    struct ValWithIndexHasher
    {
        using is_transparent = void;
        std::size_t operator()(int val) const
        {
            return std::hash<int>() (val);
        }

        std::size_t operator()(const ValWithIndex & val) const
        {
            return std::hash<int>() (val.val);
        }
    };

    struct ValWithIndexComparator
    {
        using is_transparent = void;
        bool operator()(int val, const ValWithIndex & other) const
        {
            return val == other.val;
        }

        bool operator()(const ValWithIndex & one, const ValWithIndex & other ) const
        {
            return one.val == other.val && one.index == other.index ;
        }
    };

    using TrickySet = std::unordered_set<ValWithIndex, ValWithIndexHasher, ValWithIndexComparator>;
    using RandomAccessVector = std::vector<int>;

    static const std::size_t INITIAL_SIZE = 30000;

    TrickySet values_set;
    RandomAccessVector  random_vector;

    std::default_random_engine random_engine;
    std::uniform_int_distribution<std::size_t> distribution;

    RandomizedCollection()
    {
        values_set.reserve(INITIAL_SIZE);
        random_vector.reserve(INITIAL_SIZE);

    }

    void dump() const
    {
        std::cout<<" set ";
        for(const ValWithIndex & val : values_set)
        {
            std::cout<<" "<<val.val<<":"<<val.index<<" ";
        }


    }

    bool insert(int val) {
        bool res  = values_set.find(val) == values_set.end();
        values_set.insert(ValWithIndex{val , random_vector.size()});
        random_vector.push_back(val);
        return res;
    }

    bool remove(int val) {
        TrickySet::iterator it = values_set.find(val);
        if (it != values_set.end())
        {

            std::size_t vector_index = it->index;
            int back_value = random_vector.back();
            random_vector[vector_index] = back_value;

            values_set.erase(it);
            random_vector.pop_back();


            if (vector_index != random_vector.size())
            {
                ValWithIndex val_to_update{back_value, random_vector.size()};
                TrickySet::iterator it_to_update = values_set.find(val_to_update);
                values_set.erase(it_to_update);
                values_set.insert(ValWithIndex{back_value, vector_index});
            }

            return true;
        }

        return false;
    }

    int getRandom()
    {

        std::size_t random_index = distribution(random_engine) % random_vector.size();
        //std::cout<<random_vector.size()<<" "<<random_index<<std::endl;
        return random_vector[random_index ];

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

        RandomizedCollection1 randomizedCollection;

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
            if (op == "RandomizedCollection")
            {
                std::cout<<"null"<<std::endl;
            }
            if (op == "insert")
            {
                bool res = randomizedCollection.insert((*(*args_it).begin()).asInt());
                std::cout<<(res ? "true" : "false")<<std::endl;
            }

            if (op == "remove")
            {
                bool res = randomizedCollection.remove((*(*args_it).begin()).asInt());
                std::cout<<(res ? "true" : "false")<<std::endl;
            }

            if (op == "getRandom")
            {
                std::cout<<randomizedCollection.getRandom()<<std::endl;
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

    //const char * operations = R"[=](["RandomizedCollection", "insert", "insert", "insert", "getRandom", "remove", "getRandom"])[=]";
    //const char * args = R"[=]([[], [1], [1], [2], [], [1], []])[=]";
    const char * operations = R"[=](["RandomizedCollection", "insert", "insert", "remove", "getRandom"])[=]";
    const char * args = R"[=]([[],[1],[1],[1],[]])[=]";

    test(std::string(operations), std::string(args));
    //answer should be 595352
}




void test2()
{

}


int main(int argc, char** argv)
{
   test1();

}

