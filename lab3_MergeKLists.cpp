/*
    实验名称：合并K个有序链表
    使用算法技术：分治
    问题描述：给你一个链表数组，每个链表都已经按升序排列。
            请你将所有链表合并到一个升序链表中，返回合并后的链表。
    例：输入：lists = [[1,4,5],[1,3,4],[2,6]]
        输出：[1,1,2,3,4,4,5,6]
        解释：链表数组如下：
            [
            1->4->5,
            1->3->4,
            2->6
            ]
            将它们合并到一个有序链表中得到。
            1->1->2->3->4->4->5->6
    使用说明：在主函数中先实例化一个Solution类的对象，再通过该对象调用mergeKLists函数，
             传入的参数为链表数组，得到的是合并后链表的头指针，打印验证即可。
    创建时间：2022.5.20
    最后修改时间:2022.5.20
    作者：********
*/

#include<iostream>
#include<vector>
using namespace std;
/*Definition for singly-linked list.*/
struct ListNode 
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//链表类
class LinkedList
{
    public:
    ListNode* head;
    friend class Solution;  //声明友元类，这样Solution类能访问LinkedList的私有成员
    LinkedList(vector<int>nums)      //构造函数
    {
        head=nullptr;   
        for(int i=nums.size()-1;i>=0;i--)
        {
            ListNode* temp=new ListNode(nums[i],head);
            head=temp;      //更新头指针
        }
    }
    LinkedList(ListNode* head)
    {
        this->head=head;
    }
    void destory()                    //释放内存空间
    {
        ListNode* temp=nullptr;
        while(head&&head->next)
        {
            temp=head;
            head=head->next;
            temp->next=nullptr;
            delete temp;
            temp=nullptr;   //delete后temp可能变成野指针
        }
        if(head)    delete head;
    }
    void show()                        //打印链表
    {
        ListNode* p=head;
        while(p)
        {
            cout<<p->val<<"->";
            p=p->next;
        }
        cout<<"NULL"<<endl;
    }

};

 
class Solution {
public:
    //合并两个有序链表的函数
    ListNode* mergeTwoLists(ListNode* list1,ListNode* list2)
    {
        if(!list1)  return list2;
        if(!list2)  return list1;

        ListNode* res=list1->val<=list2->val?list1:list2;
        ListNode* tail=res;
        ListNode* temp=nullptr;
        //两链表都没处理完
        while(list1&&list2)
        {
            if(list1->val<=list2->val)
            {
                temp=list1;
                list1=list1->next;               
            }
            else
            {
                temp=list2;
                list2=list2->next;
            }
            tail->next=temp;    //把较小的节点加在结果链表后面
            tail=tail->next;    //更新尾指针
            
        }
        //说明list2处理结束，将l1剩余元素跟在后面即可
        if(!list2)  tail->next=list1;
        //说明list1处理结束，将l1剩余元素跟在后面即可
        else        tail->next=list2;
        return res;
    }
    //合并K个有序链表
    ListNode* mergeKLists(vector<ListNode*>& lists) 
    {
        //分治的思想
        if(lists.size()==0)  return nullptr;
        if(lists.size()==1)  return lists[0];
        vector<ListNode*> left;
        vector<ListNode*> right;
        int mid=lists.size()/2;
        for(int i=0;i<mid;i++)
        {
            left.push_back(lists[i]);
        }
        for(int i=mid;i<lists.size();i++)
        {
            right.push_back(lists[i]);
        }
        return mergeTwoLists(mergeKLists(left),mergeKLists(right));
    }
};

int main()
{
    vector<int>nums1={1,4,5};   LinkedList l1(nums1);
    vector<int>nums2={1,3,4};   LinkedList l2(nums2);
    vector<int>nums3={2,6};     LinkedList l3(nums3);
    cout<<"原链表数组:"<<endl;
    l1.show();
    l2.show();
    l3.show();
    vector<ListNode*>lists={l1.head,l2.head,l3.head};
    Solution solution;
    ListNode* res=solution.mergeKLists(lists);
    LinkedList resl(res);
    cout<<"合并后的链表:"<<endl;
    resl.show();
    resl.destory();     //释放内存空间
    
    return 0;
}
