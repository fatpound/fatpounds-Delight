#pragma once

template <typename T>
class BinarySearchTree
{
private:
    class BinarySearchTree_node
    {
    private:


    protected:


    public:
        BinarySearchTree_node* left = NULL;
        BinarySearchTree_node* right = NULL;
        T item;

        BinarySearchTree_node();
        ~BinarySearchTree_node();
        BinarySearchTree_node(T new_item);
    };


    BinarySearchTree_node* add_private(BinarySearchTree_node* node, T new_item);

    void list_preorder_private(BinarySearchTree_node* node);
    void list_inorder_private(BinarySearchTree_node* node);
    void list_postorder_private(BinarySearchTree_node* node);
    void list_leaves_private(BinarySearchTree_node* node);

    void list_preorder_reverse_private(BinarySearchTree_node* node);
    void list_inorder_reverse_private(BinarySearchTree_node* node);
    void list_postorder_reverse_private(BinarySearchTree_node* node);
    void list_leaves_reverse_private(BinarySearchTree_node* node);


protected:


public:
    BinarySearchTree_node* root = NULL;
    int item_count = 0;

    BinarySearchTree();
    ~BinarySearchTree();

    void add(T new_item);

    void list_preorder();
    void list_inorder();
    void list_postorder();
    void list_leaves();

    void list_preorder_reverse();
    void list_inorder_reverse();
    void list_postorder_reverse();
    void list_leaves_reverse();
};

template <typename T> BinarySearchTree<T>::BinarySearchTree_node::BinarySearchTree_node()
{

}
template <typename T> BinarySearchTree<T>::BinarySearchTree_node::~BinarySearchTree_node()
{

}
template <typename T> BinarySearchTree<T>::BinarySearchTree_node::BinarySearchTree_node(T new_item)
{
    this->item = new_item;
}

template <typename T> BinarySearchTree<T>::BinarySearchTree_node* BinarySearchTree<T>::add_private(BinarySearchTree_node* node, T new_item)
{
    if (node == NULL)
    {
        node = new BinarySearchTree_node(new_item);
        return node;
    }

    if (new_item < node->item)
    {
        node->left = this->add_private(node->left, new_item);
    }

    if (new_item > node->item)
    {
        node->right = this->add_private(node->right, new_item);
    }
}

template <typename T> BinarySearchTree<T>::BinarySearchTree()
{

}
template <typename T> BinarySearchTree<T>::~BinarySearchTree()
{

}

template <typename T> void BinarySearchTree<T>::list_preorder_private(BinarySearchTree_node* node)
{
    if (node == NULL)
        return;

    cout << node->item << ' ';
    this->list_preorder_private(node->left);
    this->list_preorder_private(node->right);
}
template <typename T> void BinarySearchTree<T>::list_inorder_private(BinarySearchTree_node* node)
{
    if (node == NULL)
        return;

    this->list_preorder_private(node->left);
    cout << node->item << ' ';
    this->list_preorder_private(node->right);
}
template <typename T> void BinarySearchTree<T>::list_postorder_private(BinarySearchTree_node* node)
{
    if (node == NULL)
        return;

    this->list_preorder_private(node->left);
    this->list_preorder_private(node->right);
    cout << node->item << ' ';
}
template <typename T> void BinarySearchTree<T>::list_leaves_private(BinarySearchTree_node* node)
{
    if (node == NULL)
        return;

    if (node->left == NULL && node->right == NULL)
    {
        cout << node->item << ' ';
        return;
    }

    list_leaves_private(root->left);
    list_leaves_private(root->right);
}

template <typename T> void BinarySearchTree<T>::list_preorder_reverse_private(BinarySearchTree_node* node)
{
    if (node == NULL)
        return;

    cout << node->item << ' ';
    this->list_preorder_private(node->right);
    this->list_preorder_private(node->left);
}
template <typename T> void BinarySearchTree<T>::list_inorder_reverse_private(BinarySearchTree_node* node)
{
    if (node == NULL)
        return;

    this->list_preorder_private(node->right);
    cout << node->item << ' ';
    this->list_preorder_private(node->left);
}
template <typename T> void BinarySearchTree<T>::list_postorder_reverse_private(BinarySearchTree_node* node)
{
    if (node == NULL)
        return;

    this->list_preorder_private(node->right);
    this->list_preorder_private(node->left);
    cout << node->item << ' ';
}
template <typename T> void BinarySearchTree<T>::list_leaves_reverse_private(BinarySearchTree_node* node)
{
    if (node == NULL)
        return;

    if (node->left == NULL && node->right == NULL)
    {
        cout << node->item << ' ';
        return;
    }

    list_leaves_private(root->right);
    list_leaves_private(root->left);
}

template <typename T> void BinarySearchTree<T>::add(T new_item)
{
    this->add_private(this->root, new_item);
    this->item_count++;
}

template <typename T> void BinarySearchTree<T>::list_preorder()
{
    this->list_preorder_private(this->root);
}
template <typename T> void BinarySearchTree<T>::list_inorder()
{
    this->list_inorder_private(this->root);
}
template <typename T> void BinarySearchTree<T>::list_postorder()
{
    this->list_postorder_private(this->root);
}
template <typename T> void BinarySearchTree<T>::list_leaves()
{
    this->list_leaves_private(this->root);
}

template <typename T> void BinarySearchTree<T>::list_preorder_reverse()
{
    this->list_preorder_reverse_private(this->root);
}
template <typename T> void BinarySearchTree<T>::list_inorder_reverse()
{
    this->list_inorder_reverse_private(this->root);
}
template <typename T> void BinarySearchTree<T>::list_postorder_reverse()
{
    this->list_postorder_reverse_private(this->root);
}
template <typename T> void BinarySearchTree<T>::list_leaves_reverse()
{
    this->list_leaves_reverse_private(this->root);
}