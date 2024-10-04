#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <charconv>
#include <map>
#include <ranges>
#include <sstream>
#include <unordered_map>

#include <libtaskutils/python_exceptions.h>
#include <libtaskutils/python_utils.h>


class Solution {
 public:
    bool checkInclusion(std::string word1, std::string word2)
    {
        if (word1.size() > word2.size())
            return false;

        using CharNumsMap = std::unordered_map<char, std::size_t>;
        CharNumsMap  charNumsMap;

        for (char symb : word1)
        {
            charNumsMap[symb]++;
        }

        std::size_t i = 0;
        std::size_t tail = i; //uncalculated taile
        std::size_t matched_count = 0;

        while ( i <= word2.size() - word1.size())
        {

            //std::cout<<word2[i]<<" "<<word2[tail]<<std::endl;

            bool tail_symbol_in_map = false;
            for (; tail < i + word1.size(); )
            {
                char symb = word2[tail];
                CharNumsMap::iterator tail_symbol_it = charNumsMap.find(symb);

                tail_symbol_in_map = tail_symbol_it != charNumsMap.end();

                if (tail_symbol_in_map && tail_symbol_it->second !=0)
                {
                    tail_symbol_it->second--;
                    matched_count++;
                    tail++;
                } else
                {
                    break;
                }
            }

            if (matched_count == word1.size() ) //whole word has been found
                return true;

            if (tail_symbol_in_map )
            {
                charNumsMap[word2[i]]++;
                matched_count--;
                i++;//

            } else
            {
                for (std::size_t k = i; k < tail; k++)
                {
                    char symb = word2[k];
                    CharNumsMap::iterator it = charNumsMap.find(symb);
                    if (it != charNumsMap.end())
                    {
                        it->second++;
                    }
                }
                matched_count = 0;
                tail++;
                i = tail;

            }

        }
        return false;
    }
};


void test0()
{
   Solution solution;
   //std::cout<<solution.minDistance("horse", "ros")<<std::endl;
   std::string word1("ab");
   std::string word2("eidbaooo");
   std::cout<<word1<<" "<<word2<<" "<<solution.checkInclusion(word1, word2)<<std::endl;

}

void test1()
{
    Solution solution;
    //std::cout<<solution.minDistance("horse", "ros")<<std::endl;
    std::string word1("adc");
    std::string word2("dcda");
    std::cout<<word1<<" "<<word2<<" "<<solution.checkInclusion(word1, word2)<<std::endl;

}

void test2()
{
    Solution solution;
    //std::cout<<solution.minDistance("horse", "ros")<<std::endl;
    std::string word1("abc");
    std::string word2("dcda");
    std::cout<<word1<<" "<<word2<<" "<<solution.checkInclusion(word1, word2)<<std::endl;

}

void test3()
{
    Solution solution;
    //std::cout<<solution.minDistance("horse", "ros")<<std::endl;
    std::string word1("abc");
    std::string word2("ccccbbbbaaaa");
    std::cout<<word1<<" "<<word2<<" "<<solution.checkInclusion(word1, word2)<<std::endl;

}

int main(int argc, char** argv)
{
   test0();
   test1();
   test2();
   test3();

}

