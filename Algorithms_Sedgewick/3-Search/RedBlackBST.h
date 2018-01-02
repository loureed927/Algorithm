//**************************************************************
//              Red Black Binary Search Tree
//**************************************************************

#ifndef REDBLACKBST_H
#define REDBLACKBST_H

#include "Item.h"
#include <memory>
#include <vector>

// red black BST
// we use standard BST plus color information to represent 2-3 tree.
// red link bind two nodes can encode 3-nodes.
// Rules:
// a). red links lean left, don't allow right red links because it will become 4-node if one node
//     both has red left and right link.
// b). one node can only have one red link, also because it will become 4-node if allowed.
// c). every path from root to null link has same number of black link(perfect black balance).
//                  M                                             M
//                /   \                                         /   \
//              J       R                                    [E J]    R
//           &/  \     /  \     rbtree   2-3tree            /  |  \  /  \
//          E     L   P    X          ==                [A C]  H   L P  [S X]
//        /  \           &/
//       C    H         S
//     &/
//    A
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
        bool color; // color of link from parent to this node
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
        root->color = BLACK;
    }

    Item& Get(Key& key)
    {
        return Get(key, root);
    }

    void Delete(Key& key)
    {
        if (key == nullKey)
            throw(key);

        if (!Contains(key))
            return;

        if (!isRed(root->left) && !isRed(root->right))
            root->color = RED;

        root = Delete(key, root);

        if (!IsEmpty())
            root->color = BLACK;
    }

    void DeleteMin()
    {
        // the key is we can only delete key from 3-node, otherwise delete from 2-node will leave
        // a null link which break tree balance. so need to ensure do not end up with a 2-node by
        // ensure current node is not 2-node.
        // at root:
        // a) if root is 2-node, both children are 2-node, then combine them to 4-node;
        // b) otherwise borrow node from right child to ensure left child is not 2-node.
        // down the tree:
        // a). if left child of current node is not 2-node, it is perfect.
        // b). if left child is 2-node,
        //     b.1. right child is 2-node, then combine them with smallest key in parent to make
        //          left child 4-node;
        //     b.2  right child is not 2-node, then move smallest key in right child to parent,
        //          move smallest key in parent to left child, make left child 3-node;
        // traverse left links to bottom, will end up with a 3-node or 4-node, delete the smallest key,
        // will convert this node to 2-node or 3-node, then up the tree to split any 4-node.

        if (IsEmpty())
            return;

        //?
        if (!isRed(root->left) && !isRed(root->right))
            root->color = RED;

        root = DeleteMin(root);

        if (!IsEmpty())
            root->color = BLACK;
    }

    void DeleteMax()
    {
        if (IsEmpty())
            return;

        if (!isRed(root->left) && !isRed(root->right))
            root->color = RED;

        root = DeleteMax(root);

        if (!IsEmpty())
            root->color = BLACK;
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

    // this method takes one node from BST which its right link is red,
    // returns a node as root of BST of same keys which left link is red.
    //                    node                                          x
    //                  /     &\                                     &/   \
    //             keys<node    x                   ----->         node    keys>x
    //                        /   \                               /    \
    //               keys(node,x)  keys>x                   keys<node keys(node,x)
    SPNode rotateLeft(SPNode node)
    {
        SPNode x = node->right;
        node->right = x->left;
        x->left = node;
        x->color = node->color; // preserve node's color
        node->color = RED; // node is new root x's left red link now.
        x->num = node->num;
        node->num = Size(node->left) + Size(node->right) + 1;

        return x;
    }

    // similar to rotateLeft
    SPNode rotateRight(SPNode node)
    {
        SPNode x = node->left;
        node->left = x->right;
        x->right = node;
        x->color = node->color; // preserve node's color
        node->color = RED; // node is new root x's right red link now.
        x->num = node->num;
        node->num = Size(node->left) + Size(node->right) + 1;

        return x;
    }

    void flipColors(SPNode node)
    {
        node->color = RED;
        node->left->color = BLACK;
        node->right->color = BLACK;
    }

    SPNode moveRedLeft(SPNode node)
    {
        // why flip color here?
        flipColors(node);

        // move red link of right node to left node
        if (isRed(node->right->left))
        {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
            flipColors(node);
        }

        return node;
    }

    SPNode moveRedRight(SPNode node)
    {
        // why flip color here?
        flipColors(node);

        // 
        if (isRed(node->left->left))
        {
            node = rotateRight(node);
            flipColors(node);
        }

        return node;
    }

    // restore red black tree invariant
    SPNode balance(SPNode node)
    {
        if (isRed(node->right) && !isRed(node->left))
        {
            node = rotateLeft(node);
        }
        if (isRed(node->left) && isRed(node->left->left))
        {
            node = rotateRight(node);
        }
        if (isRed(node->left) && isRed(node->right))
        {
            flipColors(node);
        }

        node->num = Size(node->left) + Size(node->right) + 1;
        return node;
    }

    SPNode Put(Item& item, SPNode node)
    {
        if (item.IsNull())
            throw(item);

        // if node is null, create one.
        if (node == nullptr)
        {
            // add with red link to parent.
            return std::make_shared<Node>(item, 1, RED);
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

        if (isRed(node->right) && !isRed(node->left))
        {
            node = rotateLeft(node);
        }
        if (isRed(node->left) && isRed(node->left->left))
        {
            node = rotateRight(node);
        }
        if (isRed(node->left) && isRed(node->right))
        {
            flipColors(node);
        }

        node->num = Size(node->left) + Size(node->right) + 1;
        return node;
    }

    SPNode DeleteMin(SPNode node)
    {
        if (node->left == nullptr)
            return nullptr;

        if (!isRed(node->left) && !isRed(node->left->left))
        {
            node = moveRedLeft(node);
        }

        node->left = DeleteMin(node->left);
        return balance(node);
    }

    SPNode DeleteMax(SPNode node)
    {
        if (isRed(node->left))
            node = rotateRight(node);

        if (node->right == nullptr)
            return nullptr;

        if (!isRed(node->right) && !isRed(node->right->left))
        {
            node = moveRedRight(node);
        }

        node->right = DeleteMin(node->right);
        return balance(node);
    }

    SPNode Delete(Key& key, SPNode node)
    {
        if (key < node->item.GetKey())
        {
            if (!isRed(node->left) && !isRed(node->left->left))
            {
                node = moveRedLeft(node);
            }
            node->left = Delete(key, node->left);
        }
        else
        {
            if (isRed(node->left))
            {
                node = rotateRight(node);
            }
            if (key == node->item.GetKey() && node->right == nullptr)
            {
                return nullptr;
            }
            if (!isRed(node->right) && !isRed(node->right->left))
            {
                node = moveRedRight(node);
            }
            if (key == node->item.GetKey())
            {
                // if find the key, set its node with its min item of right subtree,
                // and then delete the min node of subtree(its item is already moved to found node).
                // also every node in the right subtree is smaller than min node.
                SPNode x = Min(node->right);
                node->item.SetKey(x->item.GetKey());
                node->item.SetValue(x->item.GetValue());
                node->right = DeleteMin(node->right);
            }
            else
            {
                node->right = Delete(key, node->right);
            }

            return balance(node);
        }
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

