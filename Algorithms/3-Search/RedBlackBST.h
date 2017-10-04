//**************************************************************
//              Red Black Binary Search Tree
//**************************************************************

#ifndef REDBLACKBST_H
#define REDBLACKBST_H

#include "Item.h"
#include <memory>
#include <vector>

// red black BST
template<typename Key, typename Item>
class RedBlackBST
{
private:
    Item nullItem;

    // forward declare class Node.
    class Node;
    typedef std::shared_ptr<Node> SPNode;

    class Node
    {
    public:
        Node(Item& it, int n, bool color) :item(it), num(n), color(color)
        {
        }

        // make data public member.
        Item item; // item contains key and value
        SPNode left; // link to left subtree
        SPNode right; // link to right subtree
        int num; // nodes number under this node as root
        bool color;
    };

    static bool RED = true;
    static bool BLACK = false;

    SPNode root; // root of BST

public:
    RedBlackBST()
    {
    }

    ~RedBlackBST()
    {
    }

    void Put(Item& item)
    {
        root = Put(item, root);
    }

    Item& Get(Key& key)
    {
        return Get(key, root);
    }

    void Delete(Key& key)
    {
    }

    void DeleteMin()
    {
    }

    void DeleteMax()
    {
    }

    // Rank will return the number of keys smaller than given key.
    int Rank(Key& key)
    {
        return Rank(key, root);
    }

    bool Contains(Key& key)
    {
        return !Get(key).IsNull();
    }

    bool IsEmpty()
    {
        return Size() == 0;
    }

    int Size()
    {
        return Size(root);
    }

    Key& Min()
    {
        return Min(root)->item.GetKey();
    }

    Key& Max()
    {
        return Max(root)->item.GetKey();
    }

    Item& Select(int k)
    {
        return Select(k, root)->item;
    }

    // Returns the smallest key in this symbol table greater than or equal to given key.
    Key& Ceiling(Key& key)
    {
        SPNode ceilingNode = Ceiling(key, root);
        if (ceilingNode == nullptr)
            return nullKey;
        else
            return ceilingNode->item.GetKey();
    }

    // Returns the largest key in this symbol table less than or equal to given key.
    Key& Floor(Key& key)
    {
        SPNode floorNode = Floor(key, root);
        if (floorNode == nullptr)
            return nullKey;
        else
            return floorNode->item.GetKey();
    }

    // access vector contains all keys in ST.
    void Keys(std::vector<Key>& keyContainer)
    {
        return Keys(keyContainer, Min(), Max());
    }

    void Keys(std::vector<Key>& keyContainer, Key& lo, Key& hi)
    {
        return Keys(keyContainer, root, lo, hi);
    }

private:

    bool isRed(SPNode node)
    {
        if (node == nullptr)
            return false;

        return node->color == RED;
    }

    SPNode Put(Item& item, SPNode node)
    {
        if (item.IsNull())
            throw(item);

        // if node is null, create one.
        if (node == nullptr)
        {
            return std::make_shared<Node>(item, 1);
        }

        // if exist, update its value
        if (item.GetKey() < node->item.GetKey()) // search in left subtree
        {
            node->left = Put(item, node->left);
        }
        else if (item.GetKey() > node->item.GetKey()) // search in right subtree
        {
            node->right = Put(item, node->right);
        }
        else // hit
        {
            node->item.SetValue(item.GetValue());
        }
        node->num = Size(node->left) + Size(node->right) + 1;
        return node;
    }

    /*****************************************************************************************/
    /*          all operations except put and delete remains the same as standard BST        */
    /*****************************************************************************************/
    int Size(SPNode node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        else
        {
            return node->num;
        }
    }

    Item& Get(Key& key, SPNode node)
    {
        if (key == nullKey)
            throw(key);

        if (node == nullptr)
            return nullItem;

        if (key < node->item.GetKey()) // key is less than key of node, search in the left subtree.
        {
            return Get(key, node->left);
        }
        else if (key > node->item.GetKey()) // search in right.
        {
            return Get(key, node->right);
        }
        else // hit
        {
            return node->item;
        }
    }

    SPNode Min(SPNode node)
    {
        if (node->left == nullptr)
        {
            return node;
        }
        else
        {
            return Min(node->left);
        }
    }

    SPNode Max(SPNode node)
    {
        if (node->right == nullptr)
        {
            return node;
        }
        else
        {
            return Max(node->right);
        }
    }

    SPNode Ceiling(Key& key, SPNode node)
    {
        if (key == nullKey)
            throw(key);

        if (node == nullptr)
            return nullptr;

        // considering BST
        //                   s
        //                  / \
                        //                 e   x
        //                / \
                        //               a    r
        //                \  /
        //                c  h
        //                   \
                        //                    m
        // looking for g's ceiling.
        // g is less than root s, the ceiling may be in left subtree or root itself.
        // g is greater than e, then ceiling must in the right subtree of e.
        // e's left subtree is always smaller than g, will not have keys greater than g.
        // so look into subtree r, g is less than r, so it may be in left subtree r.
        // g is less than h, so must be in left subtree of h which is null, then h is the ceiling.

        if (key > node->item.GetKey()) // if key is greater than node's key, then ceiling is in the right subtree.
        {
            return Ceiling(key, node->right);
        }
        else if (key < node->item.GetKey()) // if key is smaller than node's key, then ceiling may in the left subtree.
        {
            SPNode ceilingNode = Ceiling(key, node->left);
            if (ceilingNode == nullptr)
            {
                return node;
            }
            else
            {
                return ceilingNode;
            }
        }
        else
        {
            return node;
        }
    }

    SPNode Floor(Key& key, SPNode node)
    {
        if (key == nullKey)
            throw(key);

        if (node == nullptr)
            return nullptr;

        // considering BST
        //                   s
        //                  / \
                        //                 e   x
        //                / \
                        //               a    r
        //                \  /
        //                c  h
        //                   \
                        //                    m
        // looking for g's floor
        // g is less than root s, it must be left subtree.
        // g is greater than e, then e's right subtree may contain the floor if it has key less than(equal to) g.
        // if not found, than e is the floor.

        if (key < node->item.GetKey()) // if key is less than node's key, then floor is in the left subtree.
        {
            return Floor(key, node->left);
        }
        else if (key > node->item.GetKey()) // if key is greater than node's key, then floor may in the right subtree.
        {
            SPNode floorNode = Floor(key, node->right);
            if (floorNode == nullptr)
            {
                return node;
            }
            else
            {
                return floorNode;
            }
        }
        else
        {
            return node;
        }
    }

    SPNode Select(int k, SPNode node)
    {
        if (k < 0 || k > Size())
            return nullptr;

        if (node == nullptr)
            return nullptr;

        int leftSize = Size(node->left);

        // if rank k is less than node left subtree num, then the key must in the left subtree.
        if (k < leftSize)
        {
            return Select(k, node->left);
        }
        else if (k > leftSize)
        {
            return Select(k - leftSize - 1, node->right);
        }
        else
        {
            return node;
        }
    }

    int Rank(Key& key, SPNode node)
    {
        if (key == nullKey)
            throw(key);

        // encounter null node, so the key is not in the tree.
        if (node == nullptr)
        {
            return 0;
        }

        if (key < node->item.GetKey())
        {
            return Rank(key, node->left);
        }
        else if (key > node->item.GetKey())
        {
            return Size(node->left) + 1 + Rank(key, node->right);
        }
        else
        {
            return Size(node->left);
        }
    }

    void Keys(std::vector<Key>& keyContainer, SPNode node, Key& lo, Key& hi)
    {
        if (node == nullptr)
            return;

        if (lo < node->item.GetKey())
        {
            Keys(keyContainer, node->left, lo, hi);
        }

        if (lo <= node->item.GetKey() && hi >= node->item.GetKey())
        {
            keyContainer.push_back(node->item.GetKey());
        }

        if (hi > node->item.GetKey())
        {
            Keys(keyContainer, node->right, lo, hi);
        }
    }
};

#endif

