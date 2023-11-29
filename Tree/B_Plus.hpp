#pragma once

#include <iostream>
#include <vector>
#include <queue>

namespace fatpound::tree
{
    template <typename T, size_t I, size_t S>
    class B_Plus
    {
    public:
        B_Plus() = default;
        ~B_Plus() noexcept
        {
            if (root_ == nullptr)
            {
                return;
            }

            class B_Plus<T, I, S>::node;

            std::queue<node*> Q;
            Q.push(root_);

            while (Q.size() > 0)
            {
                node* u = Q.front();
                Q.pop();

                if (u->lesser != nullptr)
                {
                    Q.push(u->lesser);
                }

                for (size_t i = 0; i < u->items.size(); i++)
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
        B_Plus(const B_Plus<T, I, S>& src) = delete;
        B_Plus(B_Plus<T, I, S>&& src) = delete;
        B_Plus<T, I, S>& operator = (const B_Plus<T, I, S>& src) = delete;
        B_Plus<T, I, S>& operator = (B_Plus<T, I, S>&& src) = delete;


    public:
        void Insert(const T& new_item);
        void ListLevelorder() const;


    protected:


    private:
        class node
        {
        public:
            node() = default;

            node(std::vector<std::pair<T, node*>*>& new_items, node* new_lesser, node* new_parent)
                :
                lesser(new_lesser),
                parent(new_parent),
                items( std::move(new_items) )
            {
                
            }
            node(std::pair<T, node*>* new_pair, node* new_lesser, node* new_parent)
                :
                lesser(new_lesser),
                parent(new_parent)
            {
                items.push_back(new_pair);
            }
            node(const T& new_item, node* new_lesser, node* new_parent)
                :
                lesser(new_lesser),
                parent(new_parent)
            {
                items.push_back(new std::pair<T, B_Plus<T, I, S>::node*>(new_item, nullptr));
            }

        public:
            std::vector<std::pair<T, node*>*> items;

            node* lesser = nullptr;
            node* parent = nullptr;

        protected:

        private:
        };


    private:
        int64_t GetDepth(B_Plus<T, I, S>::node* node, int64_t depth = 0) const;

        void Insert(B_Plus<T, I, S>::node* node, T new_item)
        {
            Insert(node, new std::pair<T, B_Plus<T, I, S>::node*>(new_item, nullptr), nullptr, false);
        }
        void Insert(B_Plus<T, I, S>::node* node, std::pair<T, B_Plus<T, I, S>::node*>* new_pair, B_Plus<T, I, S>::node* extend_node, bool extend, bool create = true);
        void Overflow(B_Plus<T, I, S>::node* node, std::pair<T, B_Plus<T, I, S>::node*>* new_pair, B_Plus<T, I, S>::node* extend_node, bool extend);
        void ListLevelorder(const B_Plus<T, I, S>::node* node, int64_t level) const;


    private:
        node* root_ = nullptr;

        size_t itemCount_ = 0ui64;
    };


    template <typename T, size_t I, size_t S> int64_t B_Plus<T, I, S>::GetDepth(B_Plus<T, I, S>::node* node, int64_t depth) const
    {
        if (node == nullptr)
        {
            return depth;
        }

        return GetDepth(node->lesser, depth + 1LL);
    }

    template <typename T, size_t I, size_t S> void B_Plus<T, I, S>::ListLevelorder() const
    {
        const int64_t height = GetDepth(root_);

        for (int64_t i = 1; i <= height; i++)
        {
            std::cout << "Level " << i << " : ";

            ListLevelorder(root_, i);

            std::cout << '\n';
        }

        std::cout << '\n';
    }
    template <typename T, size_t I, size_t S> void B_Plus<T, I, S>::ListLevelorder(const B_Plus<T, I, S>::node* node, int64_t level) const
    {
        if (node != nullptr)
        {
            if (level == 1)
            {
                for (size_t i = 0; i < node->items.size(); i++)
                {
                    std::cout << node->items[i]->first << ' ';
                }
            }
            else if (level > 1)
            {
                ListLevelorder(node->lesser, level - 1);

                for (size_t i = 0; i < node->items.size(); i++)
                {
                    ListLevelorder(node->items[i]->second, level - 1);
                    std::cout << '\t';
                }
            }
        }
        else if (level == 1)
        {
            std::cout << "x ";
        }
    }

    template <typename T, size_t I, size_t S> void B_Plus<T, I, S>::Insert(const T& new_item)
    {
        if (root_ == nullptr)
        {
            root_         = new B_Plus<T, I, S>::node(new_item, nullptr, nullptr);
            root_->lesser = new B_Plus<T, I, S>::node(new_item, nullptr, root_);

            return;
        }

        Insert(root_, new_item);

        itemCount_++;
    }
    template <typename T, size_t I, size_t S> void B_Plus<T, I, S>::Insert(B_Plus<T, I, S>::node* node, std::pair<T, B_Plus<T, I, S>::node*>* new_pair, B_Plus<T, I, S>::node* extend_node, bool extend, bool create)
    {
        if (node == nullptr)
        {
            return;
        }

        if (extend)
        {
            goto extension;
        }

        size_t index;


    control:


        if (node->lesser == nullptr)
        {
            goto sequence;
        }

        if (new_pair->first <= node->items[0]->first)
        {
            node = node->lesser;
            goto control;
        }

        index = 0;

        for (size_t i = 0; i < node->items.size(); i++)
        {
            if (new_pair->first > node->items[i]->first)
            {
                index = i;
            }
        }

        if (node->items[index]->second == nullptr)
        {
            node->items[index]->second = new B_Plus<T, I, S>::node(new_pair, nullptr, node);
            return;
        }
        else
        {
            node = node->items[index]->second;
            goto control;
        }


    sequence:


        if (node->items.size() == S * 2)
        {
            Overflow(node, new_pair, nullptr, false);
        }
        else
        {
            node->items.push_back(new_pair);

            if (node->items.size() > 1)
            {
                std::sort(
                    node->items.begin(),
                    node->items.end(),
                    [](std::pair<T, B_Plus<T, I, S>::node*>* p1, std::pair<T, B_Plus<T, I, S>::node*>* p2)
                    {
                        return p1->first < p2->first;
                    }
                );
            }
        }

        return;


    extension:


        if (node->items.size() == I * 2)
        {
            if (create)
            {
                Overflow(node, new std::pair<T, B_Plus<T, I, S>::node*>(new_pair->first, nullptr), extend_node, true);
            }
            else
            {
                Overflow(node, new_pair, extend_node, true);
            }
        }
        else
        {
            if (create)
            {
                node->items.push_back(new std::pair<T, B_Plus<T, I, S>::node*>(new_pair->first, extend_node));
            }
            else
            {
                node->items.push_back(new_pair);
                extend_node->lesser = new_pair->second;
                new_pair->second = extend_node;
            }

            if (node->items.size() > 1)
            {
                std::sort(
                    node->items.begin(),
                    node->items.end(),
                    [](std::pair<T, B_Plus<T, I, S>::node*>* p1, std::pair<T, B_Plus<T, I, S>::node*>* p2)
                    {
                        return p1->first < p2->first;
                    }
                );
            }
        }
    }
    template <typename T, size_t I, size_t S> void B_Plus<T, I, S>::Overflow(B_Plus<T, I, S>::node* node, std::pair<T, B_Plus<T, I, S>::node*>* new_pair, B_Plus<T, I, S>::node* extend_node, bool extend)
    {
        const size_t a = (node->lesser == nullptr ? S : I);

        node->items.push_back(new_pair);
        new_pair->second = extend_node;

        std::sort(
            node->items.begin(),
            node->items.end(),
            [](std::pair<T, B_Plus<T, I, S>::node*>* p1, std::pair<T, B_Plus<T, I, S>::node*>* p2)
            {
                return p1->first < p2->first;
            }
        );

        size_t center = (a * 2 + 1) / 2;

        B_Plus<T, I, S>::node* new_node = new B_Plus<T, I, S>::node();

        for (size_t i = center + 1; i <= a * 2; i++)
        {
            new_node->items.push_back(node->items[i]);
        }

        if (extend)
        {
            if (node == root_)
            {
                B_Plus<T, I, S>::node* new_parent = new B_Plus<T, I, S>::node();

                new_parent->lesser = root_;
                root_->parent = new_parent;
                root_ = new_parent;

                root_->items.push_back(node->items[center]);
                new_node->lesser = node->items[center]->second;
                node->items[center]->second = new_node;
            }
            else
            {
                new_pair->second = extend_node;
                new_node->lesser = node->items[center]->second;
                node->items[center]->second->parent = new_node;

                Insert(node->parent, node->items[center], new_node, true, false);
            }

            extend_node->parent = new_node;
            //new_pair->second = extend_node;
            new_node->parent = node->parent;

            for (size_t i = 0; i < new_node->items.size(); i++)
            {
                if (new_node->items[i]->second != nullptr)
                {
                    new_node->items[i]->second->parent = new_node;
                }
            }

            node->items.resize(center);
        }
        else
        {
            new_node->parent = node->parent;
            node->items.resize(center + 1);
            Insert(node->parent, node->items[center], new_node, true);
        }
    }
}