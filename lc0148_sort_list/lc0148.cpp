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


struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

 void dump_list(const std::string & prefix, ListNode * out)
 {
     std::cout<<prefix<<"[";
     while (out)
     {
         std::cout<<out->val<< (out->next ? "," : "") ;
         out = out->next;
     }
     std::cout<<"]"<<std::endl;

 }

class Solution
{
 public:
    std::size_t listLen(ListNode* head, ListNode * tail)
    {
        std::size_t res = 0;
        while (head != tail)
        {
            res++;
            head = head->next;
        }
        return res;
    }

    struct ListDivision
    {
        ListNode * head1;
        ListNode * head2;
        std::size_t list1len;
        std::size_t list2len;
    };

    ListDivision divideList(ListNode * head, ListNode * tail)
    {
        ListDivision res {
            nullptr, nullptr, 0, 0};

        ListNode * tail1 = nullptr;
        ListNode * tail2= nullptr;
        bool first = true;
        while (head != tail)
        {
            ListNode * nextHead = head->next;
            if (first)
            {
                if (res.head1 == nullptr)
                {
                    res.head1 = head;
                    tail1 = head;
                } else
                {
                    tail1->next = head;
                    tail1 = head;
                }
                res.list1len++;

            }

            if (!first)
            {
                if (res.head2 == nullptr)
                {
                    res.head2 = head;
                    tail2 = head;
                } else
                {
                    tail2->next = head;
                    tail2 = head;
                }
                res.list2len++;
            }

            first = !first;
            head = nextHead;

        }

        if (tail1)
        {
            tail1->next = nullptr;
        }

        if (tail2)
        {
            tail2->next = nullptr;
        }

        return res;
    }



    ListNode* sortList(ListNode* head)
    {

        ListDivision division = divideList(head, nullptr);
        if (division.list1len + division.list2len < 2)
        {
            if (head)
                head->next = nullptr;
            return head;
        }
        if (division.list1len + division.list2len == 2)
        {
            if (division.head1->val > division.head2->val)
                std::swap(division.head1, division.head2);
            division.head1->next = division.head2;
            return division.head1;

        }
        ListNode * left = sortList(division.head1);
        ListNode * right = sortList(division.head2);

        ListNode * res = nullptr;
        ListNode * res_tail = nullptr;
        while (left || right)
        {
            if (left && (!right || left->val <= right->val ) )
            {
                if (res)
                {
                    res_tail->next = left;
                    res_tail = left;
                } else
                {
                    res = left;
                    res_tail = left;
                }
                left = left->next;
            } else if (right && (!left || right->val < left->val))
            {
                if (res)
                {
                    res_tail->next = right;
                    res_tail = right;
                } else
                {
                    res = right;
                    res_tail = right;
                }
                right = right->next;
            }
        }

        if (res_tail)
            res_tail->next = nullptr;

        return res;

    }
};


int test(const std::string & prices)
{
    int res = -1;
    try
    {
        PythonInterp interp;
        PyObject_wrapper parsed = interp.execString(prices.c_str());

        static_assert(std::input_iterator<PyObject_wrapper::PyObjectIterator>, "as");


        static_assert( std::ranges::range<PyObject_wrapper> , "as");
        //static_assert( std::ranges::forward_range<PyObject_wrapper> , "as");

        auto int_view = parsed | std::views::transform( [] (const PyObject_wrapper & wrapper) {return wrapper.asInt();});

        ListNode * head = nullptr;
        ListNode * tail = nullptr;

        for(int val : int_view)
        {
            ListNode * newNode = new ListNode(val);
            if (tail)
            {
                tail->next = newNode;
                tail = newNode;
            } else
            {
                head = newNode;
                tail = newNode;
            }
        }

        std::cout<<"=======Result========="<<std::endl;


        Solution solution;
        ListNode * out = solution.sortList(head);
        dump_list("out ",out);


        res = 0;

    } catch (PythonParserException & exc)
    {
        std::cerr<<exc.what()<<std::endl;
    }
    std::cout<<"res : "<<res<<std::endl;
    return res;
}

void test1()
{
    const char * prices = R"ad([3,2,5,1])ad";

    test(std::string(prices));
    //answer should be 595352
}



int main(int argc, char** argv)
{
   test1();

}

