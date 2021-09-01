#include "../Include/LIFO.hpp"

List::List(const List &list)
{
    auto *root = list.head.get();

    std::unique_ptr<Node> new_head {nullptr};

    Node *pnew_head {nullptr};

    while(root)
    {
        auto tmp{std::make_unique<Node> (root->fdata)};

        if(!new_head)
        {
            new_head = std::move(tmp);
            pnew_head = new_head.get();
        }
        else
        {
            pnew_head -> next = std::move(tmp);
            pnew_head = pnew_head -> next.get();
        }
        root = root -> next.get();
    }

    head = std::move(new_head);
}

List::List(List &&list)
{
    head = std::move(list.head);
}

void List::pop(void)
{
    if(!head)
        return;

    std::unique_ptr<Node> tmp = std::move(head);
    head = std::move(tmp -> next);
}

void List::push(int data)
{
    auto tmp = std::make_unique<Node> (data);

    if(head)
    {
        tmp -> next = std::move(head);
        head = std::move(tmp);
    }
    else
    {
        head = std::move(tmp);
    }
}

void List::clean(void)
{
    while(head)
        head = std::move(head -> next);
}

int List::GetTopValue(void) const
{
    if(!head)
        return -1;
    else
        return head->fdata;
}

std::ostream &operator << (std::ostream &o, const List &list)
{
    auto * head = list.head.get();

    while(head)
    {
        o << head -> fdata << " ";
        head = head -> next.get();
    }

    return o;
}