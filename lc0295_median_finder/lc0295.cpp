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




class MedianFinder {
 public:
    MedianFinder() {

    }

    void addNum(int num)
    {
        std::size_t initial_index = my_heap.size();
        my_heap.push_back(num);
        if (initial_index == 0)
            return;


        while (initial_index > 0)
        {
            bool is_even = initial_index % 2 == 0;
            std::size_t parent_index = is_even ? (initial_index - 2) / 2 : (initial_index - 1) / 2;
            if (my_heap[initial_index] > my_heap[parent_index])
            {
                std::swap(my_heap[initial_index], my_heap[parent_index]);
                initial_index = parent_index;
            } else
            {

                if (initial_index == my_heap.size() -1 && is_even && my_heap[initial_index - 1] > my_heap[initial_index])
                {
                    std::swap( my_heap[initial_index - 1] , my_heap[initial_index]);
                }
               
                break;
            }
        }
    }

    void testHeap(std::size_t root_index, std::vector<int> & out)
    {
        out.push_back(my_heap[root_index]);
        int child = 2*root_index;
        if ((child + 2) < my_heap.size())
        {
            testHeap(child + 2, out);
        }
        if ((child + 1) < my_heap.size())
        {
            testHeap(child + 1, out);
        }

    }

    double findMedian()
    {

    }
    private:
       std::vector<int> my_heap;
       int median_index = 0;

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


        MedianFinder medianFinder;
        std::cout<<"Median finder ()"<<std::endl;

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
            if (op == "MedianFinder")
            {
                std::cout<<"null"<<std::endl;
            }
            if (op == "addNum")
            {
                //bool res = randomizedCollection.insert((*(*args_it).begin()).asInt());
                //std::cout<<(res ? "true" : "false")<<std::endl;
                std::cout<<"    addNum("<<arg_vec[0]<<")"<<std::endl;
                medianFinder.addNum(arg_vec[0]);
            }

            if (op == "findMedian")
            {
                //bool res = randomizedCollection.remove((*(*args_it).begin()).asInt());
                std::cout<<"    findMedian() => ";
                double median =  medianFinder.findMedian();
                std::cout<<median<<std::endl;
            }

            if (op == "testHeap")
            {
                std::cout<<"    testHeap() => ";
                std::vector<int> heap;
                medianFinder.testHeap(0, heap);
                for(auto val : heap)
                {
                    std::cout<<val<<" ";
                }
                std::cout<<std::endl;
            }


        }

    } catch (PythonParserException & exc)
    {
        std::cerr<<exc.what()<<std::endl;
    }
    std::cout<<"res : "<<res<<std::endl;
    return res;
}


void test0()
{
    const char* operations = R"[=](["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"])[=]";
    const char* args = R"[=]([[], [1], [2], [], [3], []])[=]";

    test(std::string(operations), std::string(args));
}


void test1()
{
    const char* operations = R"[=](["MedianFinder","addNum","testHeap","addNum","testHeap","addNum","testHeap","addNum","testHeap","addNum","testHeap","addNum","testHeap","addNum","testHeap","addNum","testHeap","addNum","testHeap","addNum","testHeap","addNum","testHeap"])[=]";
    const char* args = R"[=]([[],[6],[],[10],[],[2],[],[6],[],[5],[],[0],[],[6],[],[3],[],[1],[],[0],[],[0],[]])[=]";

    test(std::string(operations), std::string(args));
}

void test2()
{
    const char* operations = R"[=](["MedianFinder","addNum","findMedian","addNum","findMedian","addNum","findMedian","addNum","findMedian","addNum","findMedian","addNum","findMedian","addNum","findMedian","addNum","findMedian","addNum","findMedian","addNum","findMedian","addNum","findMedian"])[=]";
    const char* args = R"[=]([[],[6],[],[10],[],[2],[],[6],[],[5],[],[0],[],[6],[],[3],[],[1],[],[0],[],[0],[]])[=]";

    test(std::string(operations), std::string(args));
}

int main(int argc, char** argv)
{
   test1();

}

