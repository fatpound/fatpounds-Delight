#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <ranges>

namespace rn = std::ranges;

namespace fatpound::tree
{
    template <std::totally_ordered T, size_t C>
    class B
    {
    public:
        B() = default;
        ~B() noexcept
        {
            if (root_ == nullptr)
            {
                return;
            }

            class B<T, C>::Node;

            std::queue<Node*> Q;
            Q.push(root_);

            while (Q.size() > 0u)
            {
                Node* u = Q.front();
                Q.pop();

                if (u->lesser != nullptr)
                {
                    Q.push(u->lesser);
                }

                for (size_t i = 0u; i < u->items.size(); ++i)
                {
                    if (u->items[i]->second != nullptr)
                    {
                        Q.push(u->items[i]->second);
                    }

                    delete u->items[i];
                }

                delete u;
            }

            root_ = nullptr;
        }
        B(const B<T, C>& src) = delete;
        B(B<T, C>&& src) = delete;
        B<T, C>& operator = (const B<T, C>& src) = delete;
        B<T, C>& operator = (B<T, C>&& src) = delete;


    public:
        void Insert(const T& new_item)
        {
            std::pair<T, B<T, C>::Node*>* new_pair = new std::pair<T, B<T, C>::Node*>(new_item, nullptr);

            if (root_ == nullptr)
            {
                root_ = new B<T, C>::Node(new_pair);
                depth_++;

                return;
            }

            Insert(root_, new_pair, true);
        }
        void ListLevelorder() const
        {
            if (root_ == nullptr)
            {
                return;
            }

            std::queue<B<T, C>::Node*> Q;
            Q.push(root_);

            while (Q.size() > 0u)
            {
                B<T, C>::Node* u = Q.front();
                Q.pop();


                if (u->lesser != nullptr)
                {
                    Q.push(u->lesser);
                }

                for (size_t i = 0u; i < u->items.size(); ++i)
                {
                    std::cout << u->items[i]->first << ' ';

                    if (u->items[i]->second != nullptr)
                    {
                        Q.push(u->items[i]->second);
                    }
                }

                std::cout << "\n";
            }

            std::cout << "\n";
        }
        

    protected:


    private:
        struct Node
        {
            Node() = default;

            Node(B<T, C>::Node* new_lesser)
                :
                lesser(new_lesser)
            {

            }
            Node(std::pair<T, Node*>* new_item, Node* new_parent = nullptr)
                :
                parent(new_parent)
            {
                if (new_item != nullptr)
                {
                    items.push_back(new_item);
                }
            }

            std::vector<std::pair<T, Node*>*> items;

            Node* lesser = nullptr;
            Node* parent = nullptr;
        };


    private:
        void Insert(B<T, C>::Node* node, std::pair<T, B<T, C>::Node*>* pair, bool add_first_time)
        {
            if (node == nullptr)
            {
                return;
            }

        label:

            if (node->items.size() == C * 2u)
            {
                if (add_first_time)
                {
                    size_t idx = 0u;
                    bool flag = false;

                    for (size_t i = 0u; i < node->items.size(); ++i)
                    {
                        if (pair->first > node->items[i]->first && node->items[i]->second != nullptr)
                        {
                            if (flag == false)
                            {
                                flag = true;
                            }

                            idx = i;
                        }
                    }

                    if (flag)
                    {
                        Insert(node->items[idx]->second, pair, true);
                    }
                    else
                    {
                        Overflow(node, pair);
                    }
                }
                else
                {
                    Overflow(node, pair);
                }
            }
            else
            {
                if (node->items.size() != 0u && add_first_time)
                {
                    if (pair->first < node->items[0u]->first && node->lesser != nullptr)
                    {
                        node = node->lesser;
                        goto label;
                    }

                    size_t index = 0u;

                    for (size_t i = 0u; i < node->items.size(); ++i)
                    {
                        if (pair->first > node->items[i]->first)
                        {
                            index = i;
                        }
                    }

                    if (node->items[index]->second != nullptr)
                    {
                        node = node->items[index]->second;
                        goto label;
                    }
                }

                node->items.push_back(pair);

                if (node->items.size() > 1u)
                {
                    rn::sort(node->items, [](const auto& p1, const auto& p2) -> bool { return p1->first < p2->first; });
                }
            }
        }
        void Overflow(B<T, C>::Node* node, std::pair<T, B<T, C>::Node*>* pair)
        {
            std::vector<std::pair<T, B<T, C>::Node*>*> temp_vec;

            temp_vec.push_back(pair);

            for (size_t i = 0u; i < C * 2u; ++i)
            {
                temp_vec.push_back(node->items[i]);
            }

            rn::sort(temp_vec, [](const auto& p1, const auto& p2) -> bool { return p1->first < p2->first; });

            size_t center = (C * 2u + 1u) / 2u;

            std::vector<std::pair<T, B<T, C>::Node*>*> temp_vec_less;
            std::vector<std::pair<T, B<T, C>::Node*>*> temp_vec_more;

            for (size_t i = 0u; i < center; ++i)
            {
                temp_vec_less.push_back(temp_vec[i]);
            }

            for (size_t i = center + 1u; i <= C * 2u; ++i)
            {
                temp_vec_more.push_back(temp_vec[i]);
            }

            node->items.clear();

            for (size_t i = 0u; i < temp_vec_less.size(); ++i)
            {
                node->items.push_back(temp_vec_less[i]);
            }

            if (node == root_)
            {
                node->parent = new B<T, C>::Node(node);
                root_ = node->parent;
                depth_++;
            }

            Insert(node->parent, temp_vec[center], false);

            B<T, C>::Node* new_node = new B<T, C>::Node();
            new_node->parent = node->parent;

            for (size_t i = 0u; i < temp_vec_more.size(); ++i)
            {
                new_node->items.push_back(temp_vec_more[i]);
            }

            new_node->lesser = temp_vec[center]->second;
            temp_vec[center]->second = new_node;
        }


    private:
        Node* root_ = nullptr;

        size_t depth_ = 0;
    };
}