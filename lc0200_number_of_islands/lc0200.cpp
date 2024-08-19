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

class Solution {
 public:

    struct Cell
    {
        std::size_t row;
        std::size_t col;
        char * ch;
        Cell(std::size_t row, std::size_t col, char * ch): row(row), col(col), ch(ch)
        {

        }
    };

    using BFSQueue = std::queue<Cell>;

    void process_subgraph(std::vector<std::vector<char>>& grid, std::size_t rowCount, std::size_t colCount, BFSQueue & bfsQueue)
    {
        while(!bfsQueue.empty())
        {
            Cell top = bfsQueue.front();
            bfsQueue.pop();

            struct Movement {int drow; int dcol;};
            constexpr Movement movements[4] = {{-1,0}, {1,0}, {0,-1}, {0, 1}};
            for (std::size_t movement = 0; movement < std::size(movements); movement++)
            {
                int row = top.row;
                int col = top.col;
                row += movements[movement].drow;
                col += movements[movement].dcol;
                if (row >= 0 && row <rowCount && col >=0 && col <colCount)
                {
                    char* val = &grid[row][col];
                    if (*val == '1')
                    {
                        *val = '2';
                        bfsQueue.emplace(row, col, val);
                    }
                }
            }
        }
    }

    int numIslands(std::vector<std::vector<char>>& grid)
    {
        BFSQueue bfsQueue;
        std::size_t rowCount = grid.size();
        std::size_t colCount = rowCount > 0 ? grid.front().size() : 0;

        int res = 0;
        for (std::size_t j = 0; j < rowCount; j++)
        {
            std::vector<char> & row = grid[j];
            for(std::size_t i = 0; i < colCount; i++)
            {
                char & cell_value = row[i];
                if (cell_value == '1')
                {
                    cell_value = '2';
                    res++;
                    bfsQueue.emplace(j, i, &cell_value);
                    process_subgraph(grid, rowCount, colCount, bfsQueue);
                }
            }
        }

        return res;

    }
};


int test(const std::string & islands)
{
    int res = -1;
    try
    {
        PythonInterp interp;
        PyObject_wrapper parsed = interp.execString(islands.c_str());

        static_assert(std::input_iterator<PyObject_wrapper::PyObjectIterator>, "as");


        static_assert( std::ranges::range<PyObject_wrapper> , "as");

        std::vector<std::vector<char>> islands_vec;
        for (PyObject_wrapper islands_row:parsed)
        {
            std::cout<<islands_row.str().asString()<<std::endl;

            auto int_view = islands_row | std::views::transform( [] (const PyObject_wrapper & wrapper) {return '0' + wrapper.asInt();});

            std::vector<char> interval_parsed;

            std::ranges::copy(int_view, std::back_inserter(interval_parsed));
            islands_vec.emplace_back(interval_parsed);

        }

        Solution solution;
        res = solution.numIslands(islands_vec);

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
    const char * islands = R"ad([["1","1","1","1","0"],["1","1","0","1","0"],["1","1","0","0","0"],["0","0","0","0","0"]])ad";

    test(std::string(islands));

}

void test2()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * islands = R"ad([["1","1","0","0","0"],["1","1","0","0","0"],["0","0","1","0","0"],["0","0","0","1","1"]])ad";

    test(std::string(islands));
}

void test3()
{
    //const char * prices = R"ad([1036,2413,2776,825,2640,31,1560,2917,4282,783,3146,2600,1939,694,4284,3881,554,167,372,4620,3037,1175,1075,3845,4981,4495,2807,4774,4526,3914,2633,3762,1570,2334,616,1648,1914,2900,349,2428,4013,1964,4020,1882,629,240,2595,2902,3419,292,224,4437,4918,632,3701,3840,3996,2129,3345,3979,1954,781,1576,1084,3250,4517,3106,2133,309,4520,2225])ad";
    const char * islands = R"ad([["1","1","1"],["0","1","0"],["1","1","1"]])ad";

    test(std::string(islands));
}



int main(int argc, char** argv)
{
   test1();
   test2();
   test3();

}

