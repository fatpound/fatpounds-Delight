#pragma once

#include <iostream>

using namespace std;

template <typename T>
class SinglyCircularLinkedList
{
private:
    class SinglyCircularLL_node
    {
    private:


    protected:


    public:
        SinglyCircularLL_node* next = NULL;
        T item;

        SinglyCircularLL_node();
        ~SinglyCircularLL_node();
        SinglyCircularLL_node(T new_item);
    };

    SinglyCircularLL_node* list = NULL;
    int item_count = 0;

    void connect(SinglyCircularLinkedList<T>& second);
    void connect_sorted(SinglyCircularLL_node* node);

    SinglyCircularLL_node* go_to_index(int index);


protected:


public:
    SinglyCircularLinkedList();
    ~SinglyCircularLinkedList();

    void add(T new_item);
    void add_sorted(T new_item);
    void combine(SinglyCircularLinkedList<T>& second);
    void combine_sorted(SinglyCircularLinkedList<T>& second);
    void reverse();
    void list_all();
};

template <typename T> SinglyCircularLinkedList<T>::SinglyCircularLL_node::SinglyCircularLL_node()
{

}
template <typename T> SinglyCircularLinkedList<T>::SinglyCircularLL_node::~SinglyCircularLL_node()
{

}
template <typename T> SinglyCircularLinkedList<T>::SinglyCircularLL_node::SinglyCircularLL_node(T new_item)
{
    this->item = new_item;
}

template <typename T> SinglyCircularLinkedList<T>::SinglyCircularLinkedList()
{

}
template <typename T> SinglyCircularLinkedList<T>::~SinglyCircularLinkedList()
{

}

template <typename T> void SinglyCircularLinkedList<T>::connect(SinglyCircularLinkedList<T>& second)
{
    SinglyCircularLL_node* end = this->go_to_index(this->item_count - 1);
    end->next = second.list;

    SinglyCircularLL_node* second_end = second.go_to_index(second.item_count - 1);
    second_end->next = this->list;
}
template <typename T> void SinglyCircularLinkedList<T>::connect_sorted(SinglyCircularLinkedList<T>::SinglyCircularLL_node* node)
{
    if (this->list == NULL)
    {
        this->list = node;
        return;
    }

    if (node->item < this->list->item)
    {
        node->next = this->list;
        this->list = node;

        SinglyCircularLinkedList<T>::SinglyCircularLL_node* end = this->go_to_index(this->item_count - 1);
        end->next = node;

        return;
    }

    SinglyCircularLinkedList<T>::SinglyCircularLL_node* temp = this->list;
    SinglyCircularLinkedList<T>::SinglyCircularLL_node* start = temp;

    while (temp->next != start)
    {
        if (temp->item <= node->item && node->item <= temp->next->item)
        {
            node->next = temp->next;
            temp->next = node;

            return;
        }

        temp = temp->next;
    }

    temp->next = node;
    node->next = start;
}
template <typename T> typename SinglyCircularLinkedList<T>::SinglyCircularLL_node* SinglyCircularLinkedList<T>::go_to_index(int index)
{
    if (index >= this->item_count)
        return NULL;

    SinglyCircularLinkedList<T>::SinglyCircularLL_node* temp = this->list;

    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }

    return temp;
}

template <typename T> void SinglyCircularLinkedList<T>::add(T new_item)
{
    SinglyCircularLinkedList<T>::SinglyCircularLL_node* new_part = new SinglyCircularLinkedList<T>::SinglyCircularLL_node(new_item);
    this->item_count++;

    if (this->list == NULL)
    {
        this->list = new_part;
        new_part->next = this->list;

        return;
    }

    SinglyCircularLinkedList<T>::SinglyCircularLL_node* end = this->go_to_index(this->item_count - 2);
    end->next = new_part;
    new_part->next = this->list;
}
template <typename T> void SinglyCircularLinkedList<T>::add_sorted(T new_item)
{
    SinglyCircularLinkedList<T>::SinglyCircularLL_node* new_part = new SinglyCircularLinkedList<T>::SinglyCircularLL_node(new_item);
    this->item_count++;

    if (this->list == NULL)
    {
        this->list = new_part;
        new_part->next = this->list;

        return;
    }

    if (new_item < this->list->item)
    {
        new_part->next = this->list;
        this->list = new_part;

        SinglyCircularLinkedList<T>::SinglyCircularLL_node* end = this->go_to_index(this->item_count - 1);
        end->next = new_part;

        return;
    }

    SinglyCircularLinkedList<T>::SinglyCircularLL_node* temp = this->list;
    SinglyCircularLinkedList<T>::SinglyCircularLL_node* start = temp;

    while (temp->next != start)
    {
        if (temp->item <= new_item && new_item <= temp->next->item)
        {
            new_part->next = temp->next;
            temp->next = new_part;

            return;
        }

        temp = temp->next;
    }

    temp->next = new_part;
    new_part->next = start;
}
template <typename T> void SinglyCircularLinkedList<T>::combine(SinglyCircularLinkedList<T>& second)
{
    if (this->list == NULL || second.list == NULL)
        return;

    this->connect(second);
    this->item_count += second.item_count;
}
template <typename T> void SinglyCircularLinkedList<T>::combine_sorted(SinglyCircularLinkedList<T>& second)
{
    if (this->list == NULL || second.list == NULL)
        return;

    SinglyCircularLinkedList<T>::SinglyCircularLL_node* temp = second.list;
    SinglyCircularLinkedList<T>::SinglyCircularLL_node* start = temp;

    do
    {
        SinglyCircularLinkedList<T>::SinglyCircularLL_node* temp2 = temp->next;

        this->connect_sorted(temp);
        temp = temp2;
    }
    while (temp != start);

    this->item_count += second.item_count;
}
template <typename T> void SinglyCircularLinkedList<T>::reverse()
{
    if (this->list == NULL)
        return;

    SinglyCircularLinkedList<T>::SinglyCircularLL_node* t;
    SinglyCircularLinkedList<T>::SinglyCircularLL_node* a = NULL;
    SinglyCircularLinkedList<T>::SinglyCircularLL_node* x;

    SinglyCircularLinkedList<T>::SinglyCircularLL_node* temp = this->list;
    SinglyCircularLinkedList<T>::SinglyCircularLL_node* start = temp;

    while (1)
    {
        t = temp->next;
        temp->next = a;
        a = t;
        x = temp;

        temp = t->next;
        t->next = x;

        if (temp == start)
        {
            start->next = t;

            this->list = t;

            return;
        }

        if (temp->next == start)
        {
            start->next = temp;

            temp->next = t;
            this->list = temp;

            return;
        }
    }

    start->next = temp;
}
template <typename T> void SinglyCircularLinkedList<T>::list_all()
{
    if (this->list == NULL)
        return;

    SinglyCircularLinkedList<T>::SinglyCircularLL_node* temp = this->list;
    SinglyCircularLinkedList<T>::SinglyCircularLL_node* start = temp;

    do
    {
        cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';
        temp = temp->next;
    }
    while (temp != start);

    cout << '\n';
}