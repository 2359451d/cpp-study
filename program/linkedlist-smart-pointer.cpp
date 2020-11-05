#include<memory>
#include<string>
#include<iostream>

using namespace std;

typedef struct Node{
    char data;
    // Node* next; 这么写要注意内存泄漏（new）
    unique_ptr<Node> next;
}Node;

class Link{
    void front(const char& data){
        auto node= make_unique<Node>();//生成对象指针
        node->data=data;
        node->next=move(head.next);//head.next对象所有权转给当前node智能指针.next
        head.next=move(node);//node对象转给head.next
    };

    void print()
    {
        Node* node = head.next.get();//获得底层指针
        while(node)
        {
            cout<<node->data<<endl;
            node=node->next.get();
        }
    }
    private:
        Node head;
};