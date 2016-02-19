#include "ACAutomation.h"
#include <iostream>
#include <cstring>

//fork from https://github.com/kelvict/ACAutomation
//I modified it to uint8_t index

ACAutomation::ACAutomation()
{
    this->root = new Node();
}

void ACAutomation::freeNode(Node *node)
{
    for(int i=0; i<NODE_KIND; ++i)
    {
        if(node->next[i] != NULL)
        {
            freeNode(node->next[i]);
        }
    }
    delete node;
}

ACAutomation::~ACAutomation()
{
    freeNode(this->root);
}

void ACAutomation::insert(uint8_t *pattern,uint32_t size,uint32_t id)
{
    Node *p = this->root;
    for(uint32_t i=0;i<size;i++){
        uint32_t index=pattern[i];
        if (p->next[index] == NULL)
            p->next[index] = new Node();
        p = p->next[index];
    }
    p->flag = id + 1;     //modify zero based id to 1 base id, because 0 is use as end flag
    p->size = size;
}

void ACAutomation::build(){
    this->root->fail = NULL;
    this->q.push(this->root);
    while(!this->q.empty())
    {
        Node *parent = this->q.front();
        this->q.pop();
        for(int i=0; i<NODE_KIND; ++i)
        {
            Node *child =parent->next[i];
            if (child == NULL) continue;
            if (parent == this->root){
                child->fail = this->root;
            }
            else{
                Node *failp = parent->fail;
                while(failp != NULL)
                {
                    if(failp->next[i] != NULL)
                    {
                        child->fail = failp->next[i];
                        break;
                    }
                    failp = failp->fail;
                }
                if(failp == NULL) child->fail=this->root;
            }
            this->q.push(child);
        }
    }

}


void ACAutomation::search(uint8_t *data,uint64_t size)
{
    Node *p = this->root;
    for(uint64_t i=0;i<size;i++){
        uint8_t index=data[i];
        while(p->next[index] == NULL && p != this->root){
            p = p->fail;
        }
        if(p->next[index] == NULL){
            p=this->root;
        }else{
            p=p->next[index];
            if(p->flag>0){
                bool continu=matched(data, i- p->size+1, p->flag-1);
                if(continu==false){
                    return;
                }
            }
        }
    }
}
bool ACAutomation::matched(uint8_t *data, uint64_t position,uint32_t id){
    std::cout<<"ACAutomation::matched():pos="<<position<<" data[pos]="<<data[position]<<" id="<<id<<"\r\n";
    return true;
}





static const char *pattern[5]={
    "show",
    "bl",
    "a",
    "d",
    "ef",
};

static uint8_t data[]="show me the money power overwhelming food for thought black sheep wall";

int __attribute__((weak)) main()
{
    std::cout<<"\r\n--------start of ACAutomation demo--------\r\n";
    ACAutomation ac;
    for(int i=0;i<5;i++){
        ac.insert((uint8_t*)pattern[i],strlen(pattern[i]),i);
    }
    ac.build();
    ac.search(data,sizeof(data));
    std::cout<<"\r\n--------end of program---------\r\n";
}

