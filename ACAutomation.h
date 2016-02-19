#pragma once
#include <queue>
#include <cstddef>
#include <cstdint>

class ACAutomation
{
    static const int NODE_KIND = 0x100;     //for contain uint8_t
    struct Node{
        uint32_t flag;     //not end => 0 , end => id+1
        uint32_t size;
        Node *fail;
        Node *next[NODE_KIND];

        Node(){
            flag   = 0;
            fail = NULL;
            memset(next, 0, sizeof(next));
        }
    };
    Node *root;
    std::queue<Node*> q;
    void freeNode(Node *node);

public :
    ACAutomation();
    ~ACAutomation();
    void insert(uint8_t *pattern,uint32_t size,uint32_t id);
    void build();
    void search(uint8_t *data,uint64_t size);
    virtual bool matched(uint8_t *data,uint64_t position,uint32_t id);
};
