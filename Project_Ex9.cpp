#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

//1.O(n)
int GetEscaoeTime(std::string blocks, int pos)
{
    std::string::iterator position = blocks.begin()+(pos -1);
    int time{};
    while(1)
    {
        time++;
        if (*position == '<')
        {
            if (position == blocks.begin())
            {
                break;
            }
            *position = '>';
            position--;
        }
        else
        {
            if (position == blocks.end()-1)
            {
                break;
            }
            *position = '<';
            position++;
        }
    }
    return time;
}
//2.O(n)
int NoviceRobber(std::vector<int>& nums)
{
    if (nums.size() == 1)
    {
        return nums[0];
    }
    std::vector<int> v(nums.size()+1, 0);
    v[0] = 0;
    v[1] = nums[0];
    for (int i = 2; i < nums.size(); i++)
    {
        v[i] = std::max(v[i - 2] + nums[i], v[i - 1]);
    }
    return v[nums.size()-1];
}

//3.O(n log n)
bool CanAttenMeetings(std::vector<std::vector<int>>& invervals)
{
    std::sort(invervals.begin(), invervals.end());
    for (int i = 0; i < invervals.size()-1; i++)
    {
        if (invervals[i][1] > invervals[i + 1][0])
        {
            return false;
        }
    }
    return true;
}


//4.O(n log n)
int MinMeetingRooms(std::vector<std::vector<int>>& intervals)
{
    int n = intervals.size();
    std::vector<int> start(n,0);
    std::vector<int> end(n,0);
    for (int i = 0; i < n; i++)
    {
        start[i] = intervals[i][0];
        end[i] = intervals[i][1];
    }

    sort(start.begin(), start.end()); 
    sort(end.begin(), end.end());

    int count{}, max_count{}, i{}, j{}, k{};
    while (j < n)
    {
        if (i < n &&start[i] == k)
        {
            count++;
            i++;
        }
        if (end[j] == k)
        {
            count--;
            j++;
        }
        k++;
        max_count = std::max(max_count, count); 
    }
    return max_count;
}


struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
//5.O(n)
void ReorderList(ListNode* head)
{
    std::vector<ListNode*> v;
    auto p = head;
    while (p != nullptr)
    {
        v.push_back(p);
        p = p->next;
    }

    auto front = v.begin() + 1;
    auto back = v.end() - 1;
    p = head;
    if (p == nullptr)
    {
        return;
    }
    int index{ 1 };
    while (index < v.size())
    {
        if (index & 1)
        {
            p->next = *back;
            back--;
        }
        else
        {
            p->next = *front;
            front++;
        }
        index++;
        p = p->next;
    }
    p->next = nullptr;
}

void PrintList(ListNode* head) {
    while (head) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main()
{
    //std::string blocks{ ">><>>" };
    //std::cout << GetEscaoeTime(blocks, 2);

    //std::vector<int> nums{ 9};
    //std::cout << NoviceRobber(nums);

    //std::vector<int> values1 = { 1, 2, 3, 4 };
    //std::vector<int> values2 = { 1, 2, 3, 4, 5 };

    //ListNode* head1 = new ListNode(values1[0]);
    //ListNode* current = head1;
    //for (int i = 1; i < values1.size(); ++i) {
    //    current->next = new ListNode(values1[i]);
    //    current = current->next;
    //}

    //ListNode* head2 = new ListNode(values2[0]);
    //current = head2;
    //for (int i = 1; i < values2.size(); ++i) {
    //    current->next = new ListNode(values2[i]);
    //    current = current->next;
    //}

    //std::cout << "Original List 1: ";
    //PrintList(head1);
    //ReorderList(head1);
    //std::cout << "Reordered List 1: ";
    //PrintList(head1);

    //std::cout << "Original List 2: ";
    //PrintList(head2);
    //ReorderList(head2);
    //std::cout << "Reordered List 2: ";
    //PrintList(head2);

    //std::vector<std::vector<int>> intervals = {
    //  {1, 5}, {2, 6}, {3, 8}, {10, 15}
    //};
    //std::cout << "최소 회의실 개수: " << MinMeetingRooms(intervals)<< std::endl;
}
