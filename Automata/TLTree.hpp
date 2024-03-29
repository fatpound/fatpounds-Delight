#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <memory>
#include <algorithm>
#include <stdexcept>

namespace rn = std::ranges;

namespace fatpound::automata
{
    class TLTree
    {
    public:
        TLTree() = delete;

        TLTree(const std::vector<std::pair<std::string, std::vector<std::string>>>& cfgs);

        TLTree(const TLTree& src) = delete;
        TLTree(TLTree&& src) = delete;
        TLTree& operator = (const TLTree& src) = delete;
        TLTree& operator = (TLTree&& src) = delete;
        ~TLTree() noexcept;


    public:
        const std::vector<std::string>& GetWords() const;


    protected:


    private:
        struct Node
        {
            std::vector<Node*> leaves_;

            std::string item_;

            Node(const std::string& item);
        };


    private:
        bool IsTerminal_(const std::string& word) const;

        void CreateTree_(Node* node);
        void CreateInnerTree_(Node* node);


    private:
        const std::vector<std::pair<std::string, std::vector<std::string>>>& cfgs_;
        std::vector<std::string> results_;
        std::vector<size_t> recurse_;

        Node* tree_ = nullptr;

        static constexpr const size_t recurse_limit_ = 1u;
    };
}