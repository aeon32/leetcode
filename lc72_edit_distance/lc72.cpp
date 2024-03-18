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
    int minDistance(std::string word1, std::string word2)
    {
        std::vector<int> operations0(word2.size() + 1);

        for (int i = 0; i < operations0.size(); i++)
        {
            operations0[i] = i;
        }

        std::vector<int> operations1(word2.size() + 1);

        for (int j = 1; j <= word1.size(); j++)
        {
            operations1[0] = j;
            for (int i = 1; i <=word2.size(); i++)
            {
                int val1 = operations0[i] + 1;
                int val2 = operations1[i-1] + 1;
                int val3 = word1[j - 1] == word2[i - 1] ? operations0[i-1] : operations0[i-1] + 1;

                int val = std::min(val1, val2);
                val = std::min(val, val3);
                operations1[i] = val;
            }
            std::swap(operations0, operations1);

        }
        return operations0.back();
    }

    enum class OperationType
    {
        INSERT,
        DELETE,
        CHANGE
    };

    struct Operation
    {
        std::string before;
        std::string after;
        int op_index;
        OperationType operationType;
    };


    enum class MovementType
    {
        MOVE_UP,
        MOVE_RIGHT,
        MOVE_DIAGONAL,
        MOVE_DIAGONAL_SWAP
    };
    struct DPInfo
    {
        int distance;
        MovementType movement;
        DPInfo():distance(0), movement(MovementType::MOVE_UP)
        {

        }
    };

    using OperationSequence = std::vector<Operation>;

    using DPInfoRow = std::vector<DPInfo>;
    using DPInfoMatrix = std::vector<DPInfoRow>;

    OperationSequence minDistanceBackTrace(std::string & word1, std::string & word2)
    {

        DPInfoMatrix dpInfoMatrix(word1.size() + 1);
        for (int j = 0; j <= word1.size(); j++)
        {
            DPInfoRow  & row = dpInfoMatrix[j];
            row.resize(word2.size() + 1);
            row[0].distance = j;
            row[0].movement = MovementType::MOVE_UP;
        }

        for (int i = 0; i <= word2.size(); i++)
        {
            dpInfoMatrix.front()[i].distance = i;
            dpInfoMatrix.front()[i].movement = MovementType::MOVE_RIGHT;
        }


        for (int j = 1; j <= word1.size(); j++)
        {
            DPInfoRow  & row = dpInfoMatrix[j];
            DPInfoRow  & prev_row = dpInfoMatrix[j-1];
            for (int i = 1; i <=word2.size(); i++)
            {

                int val1 = prev_row[i].distance + 1;
                int val2 = row[i-1].distance + 1;
                int val3 = word1[j - 1] == word2[i - 1] ? prev_row[i-1].distance : prev_row[i-1].distance + 1;

                int val = std::min(val1, val2);
                val = std::min(val, val3);

                row[i].distance = val;
                if (val == val1)
                {
                    row[i].movement = MovementType::MOVE_UP;
                } else if (val == val2)
                {
                    row[i].movement = MovementType::MOVE_RIGHT;
                } else if ( word1[j - 1] == word2[i - 1] )
                    row[i].movement = MovementType::MOVE_DIAGONAL;
                else
                    row[i].movement = MovementType::MOVE_DIAGONAL_SWAP;

            }

        }
        OperationSequence  res;
        int j = word1.size();
        int i = word2.size();
        std::string word = word1;

        while (j > 0 || i>0)
        {
            std::cout<<"word : "<<word<<" i: "<<i<<" j: "<<j<<std::endl;
            std::string newWord = word;
            DPInfo & info = dpInfoMatrix[j][i];
            switch (info.movement)
            {
                case MovementType::MOVE_UP:
                j--;
                newWord.erase(j,1 );
                break;
                case MovementType::MOVE_RIGHT:
                i--;
                newWord.insert(j, 1, word2[i])     ;
                break;
                case MovementType::MOVE_DIAGONAL_SWAP:
                j--;
                i--;
                newWord[j] = word2[j];
                break;
                case MovementType::MOVE_DIAGONAL:
                j--;
                i--;
                break;

            }
            if (info.movement != MovementType::MOVE_DIAGONAL)
                res.push_back(Operation{word, newWord});
            word = newWord;
        }
        res.push_back(Operation{word2});
        return res;
    }


};


void test1()
{
   Solution solution;
   //std::cout<<solution.minDistance("horse", "ros")<<std::endl;
   std::string word1("horse");
   std::string word2("ros");
   Solution::OperationSequence  res = solution.minDistanceBackTrace(word1, word2);

   for(Solution::Operation & op : res)
   {
       std::cout<<op.before<<" "<<op.after<<std::endl;
   }


}



int main(int argc, char** argv)
{
   test1();

}

