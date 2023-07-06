//good comments are mentioned in every function to know its functionality
//everything is on heap for memory optimization
//all variables have good names for clear understanding and a good practice.
//explaination for each logic will be done to you on pen and paper.
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct globalordersnode{
    int balancefactor;
    int height;
    int data;//data means agentid
    char order[100];
    int restid;
    struct globalordersnode*left;
    struct globalordersnode*right;
}globalordersnode;

globalordersnode* globalordershead=0;
int globalorderid=0;
void gprint(globalordersnode* root)
{
    if(root==0) return;
    gprint(root->left);
    printf("order=%s , agentid=%d\n",root->order,root->data);
    gprint(root->right);
}
void printliveorders()
{
    gprint(globalordershead);
}

globalordersnode* makeglobalordersnode(int id,char*order,int restid)
{
    globalordersnode* temp=(globalordersnode*)malloc(sizeof(globalordersnode));
    temp->data=id;
    strcpy(temp->order,order);
    temp->restid=restid;
    temp->left=0;
    temp->right=0;
    temp->balancefactor=0;
    temp->height=1;
    return temp;
}

typedef struct prevordersnode{
    int balancefactor;
    int height;
    int data;
    char order[100];
    int month;
    int count;
    struct prevordersnode* left;
    struct prevordersnode* right;
}prevordersnode;

prevordersnode* makeprevordersnode(char* order,int month)
{
    prevordersnode* temp=(prevordersnode*)malloc(sizeof(prevordersnode));
    strcpy(temp->order,order);
    temp->month=month;
    temp->count=1;
    temp->left=0;
    temp->right=0;
    temp->balancefactor=0;
    temp->height=1;
    temp->data=globalorderid;
    return temp;
}
typedef struct restordersnode{
    int balancefactor;
    int height;
    int data;
    char order[100];
    int month;
    int count;
    struct restordersnode* left;
    struct restordersnode* right;
}restordersnode;

restordersnode* makerestordersnode(char* order,int month)
{
    restordersnode* temp=(restordersnode*)malloc(sizeof(restordersnode));
    strcpy(temp->order,order);
    temp->month=month;
    temp->count=1;
    temp->left=0;
    temp->right=0;
    temp->balancefactor=0;
    temp->height=1;
    temp->data=globalorderid;
    return temp;
}
typedef struct restaurantnode{
    int balancefactor;
    int height;
    int data;//data matlab restid
    char address[100];
    int seats;
    char facility[100];
    char menu[100];
    int ordercount;
    restordersnode* ordershead;
    struct restaurantnode*left;
    struct restaurantnode*right;
}restaurantnode;
restaurantnode* makerestaurantnode(int id,char* address,int s,char*facility,char*menu)
{
    restaurantnode* temp=(restaurantnode*)malloc(sizeof(restaurantnode));
    strcpy(temp->address,address);
    temp->seats=s;
    strcpy(temp->facility,facility);
    strcpy(temp->menu,menu);
    temp->ordershead=NULL;
    temp->data=id;
    temp->left=0;
    temp->right=0;
    temp->balancefactor=0;
    temp->height=1;
    temp->ordercount=0;
    return temp;
}

typedef struct agentnode{
    int balancefactor;
    int height;
    int data;//data matlab agentid
    char name[100];
    char phoneno[15];
    int accucommision;
    int working;
    struct agentnode*left;
    struct agentnode*right;
}agentnode;
agentnode* makeagentnode(char* name,int id,char*phoneno)
{
    agentnode* temp=(agentnode*)malloc(sizeof(agentnode));
    strcpy(temp->name,name);
    temp->data=id;
    strcpy(temp->phoneno,phoneno);
    temp->accucommision=0;
    temp->working=0;
    temp->left=0;
    temp->right=0;
    temp->balancefactor=0;
    temp->height=1;
    return temp;
}
typedef struct usernode{
    int balancefactor;
    int height;
    int data;//data matlab userid
    char name[100];
    char address[100];
    char phoneno[15];
    prevordersnode* prevordershead;
    struct usernode*left;
    struct usernode*right;
}usernode;
usernode* makeusernode(char*name,int id,char*phoneno,char* address)
{
    usernode* temp=(usernode*)malloc(sizeof(usernode));
    strcpy(temp->address,address);
    temp->data=id;
    strcpy(temp->name,name);
    strcpy(temp->phoneno,phoneno);
    temp->prevordershead=NULL;
    temp->left=0;
    temp->right=0;
    temp->balancefactor=0;
    temp->height=1;
    return temp;
}
int max(int a,int b)
{
    if(a>b) return a;
    else return b;
}

int gheight(globalordersnode* root)
{
    if (root == 0) return 0;
    return root->height;
}
globalordersnode* gLL(globalordersnode* root)
{
    globalordersnode* temp=root->left;
    globalordersnode* tempright=temp->right;
    temp->right=root;
    root->left=tempright;
    
    //now first update height of A and then height of B because B is above A.
    
    root->height=max(gheight(root->left),gheight(root->right))+1;
    temp->height=max(gheight(temp->left),gheight(temp->right))+1;
    
    return temp;
}
globalordersnode* gRR(globalordersnode* root)
{
    globalordersnode* temp=root->right;
    globalordersnode* templeft=temp->left;
    temp->left=root;
    root->right=templeft;
    
    //now first update height of A and then height of B because B is above A.
    
    root->height=max(gheight(root->left),gheight(root->right))+1;
    temp->height=max(gheight(temp->left),gheight(temp->right))+1;
    
    return temp;
}
globalordersnode* gLR(globalordersnode* root)
{
    globalordersnode* tempb=root->left;
    globalordersnode* tempc=tempb->right;
    tempb->right=tempc->left;
    root->left=tempc->right;
    tempc->left=tempb;
    tempc->right=root;
    
    //now first update height of A and height of B then update height of C because C is above A and B
    
    tempb->height=max(gheight(tempb->left),gheight(tempb->right))+1;
    root->height=max(gheight(root->left),gheight(root->right))+1;
    tempc->height=max(gheight(tempc->left),gheight(tempc->right))+1;
    
    return tempc;
}
globalordersnode* gRL(globalordersnode* root)
{
    globalordersnode* tempb=root->right;
    globalordersnode* tempc=tempb->left;
    tempb->left=tempc->right;
    root->right=tempc->left;
    tempc->right=tempb;
    tempc->left=root;
    
    //now first update height of A and height of B then update height of C because C is above A and B
    
    tempb->height=max(gheight(tempb->left),gheight(tempb->right))+1;
    root->height=max(gheight(root->left),gheight(root->right))+1;
    tempc->height=max(gheight(tempc->left),gheight(tempc->right))+1;
    
    return tempc;
}

int pheight(prevordersnode* root)
{
    if (root == 0) return 0;
    return root->height;
}
prevordersnode* pLL(prevordersnode* root)
{
    prevordersnode* temp=root->left;
    prevordersnode* tempright=temp->right;
    temp->right=root;
    root->left=tempright;
    
    //now first update height of A and then height of B because B is above A.
    
    root->height=max(pheight(root->left),pheight(root->right))+1;
    temp->height=max(pheight(temp->left),pheight(temp->right))+1;
    
    return temp;
}
prevordersnode* pRR(prevordersnode* root)
{
    prevordersnode* temp=root->right;
    prevordersnode* templeft=temp->left;
    temp->left=root;
    root->right=templeft;
    
    //now first update height of A and then height of B because B is above A.
    
    root->height=max(pheight(root->left),pheight(root->right))+1;
    temp->height=max(pheight(temp->left),pheight(temp->right))+1;
    
    return temp;
}
prevordersnode* pLR(prevordersnode* root)
{
    prevordersnode* tempb=root->left;
    prevordersnode* tempc=tempb->right;
    tempb->right=tempc->left;
    root->left=tempc->right;
    tempc->left=tempb;
    tempc->right=root;
    
    //now first update height of A and height of B then update height of C because C is above A and B
    
    tempb->height=max(pheight(tempb->left),pheight(tempb->right))+1;
    root->height=max(pheight(root->left),pheight(root->right))+1;
    tempc->height=max(pheight(tempc->left),pheight(tempc->right))+1;
    
    return tempc;
}
prevordersnode* pRL(prevordersnode* root)
{
    prevordersnode* tempb=root->right;
    prevordersnode* tempc=tempb->left;
    tempb->left=tempc->right;
    root->right=tempc->left;
    tempc->right=tempb;
    tempc->left=root;
    
    //now first update height of A and height of B then update height of C because C is above A and B
    
    tempb->height=max(pheight(tempb->left),pheight(tempb->right))+1;
    root->height=max(pheight(root->left),pheight(root->right))+1;
    tempc->height=max(pheight(tempc->left),pheight(tempc->right))+1;
    
    return tempc;
}

int roheight(restordersnode* root)
{
    if (root == 0) return 0;
    return root->height;
}
restordersnode* roLL(restordersnode* root)
{
    restordersnode* temp=root->left;
    restordersnode* tempright=temp->right;
    temp->right=root;
    root->left=tempright;
    
    //now first update height of A and then height of B because B is above A.
    
    root->height=max(roheight(root->left),roheight(root->right))+1;
    temp->height=max(roheight(temp->left),roheight(temp->right))+1;
    
    return temp;
}
restordersnode* roRR(restordersnode* root)
{
    restordersnode* temp=root->right;
    restordersnode* templeft=temp->left;
    temp->left=root;
    root->right=templeft;
    
    //now first update height of A and then height of B because B is above A.
    
    root->height=max(roheight(root->left),roheight(root->right))+1;
    temp->height=max(roheight(temp->left),roheight(temp->right))+1;
    
    return temp;
}
restordersnode* roLR(restordersnode* root)
{
    restordersnode* tempb=root->left;
    restordersnode* tempc=tempb->right;
    tempb->right=tempc->left;
    root->left=tempc->right;
    tempc->left=tempb;
    tempc->right=root;
    
    //now first update height of A and height of B then update height of C because C is above A and B
    
    tempb->height=max(roheight(tempb->left),roheight(tempb->right))+1;
    root->height=max(roheight(root->left),roheight(root->right))+1;
    tempc->height=max(roheight(tempc->left),roheight(tempc->right))+1;
    
    return tempc;
}
restordersnode* roRL(restordersnode* root)
{
    restordersnode* tempb=root->right;
    restordersnode* tempc=tempb->left;
    tempb->left=tempc->right;
    root->right=tempc->left;
    tempc->right=tempb;
    tempc->left=root;
    
    //now first update height of A and height of B then update height of C because C is above A and B
    
    tempb->height=max(roheight(tempb->left),roheight(tempb->right))+1;
    root->height=max(roheight(root->left),roheight(root->right))+1;
    tempc->height=max(roheight(tempc->left),roheight(tempc->right))+1;
    
    return tempc;
}

int rheight(restaurantnode* root)
{
    if (root == 0) return 0;
    return root->height;
}
restaurantnode* rLL(restaurantnode* root)
{
    restaurantnode* temp=root->left;
    restaurantnode* tempright=temp->right;
    temp->right=root;
    root->left=tempright;
    
    //now first update height of A and then height of B because B is above A.
    
    root->height=max(rheight(root->left),rheight(root->right))+1;
    temp->height=max(rheight(temp->left),rheight(temp->right))+1;
    
    return temp;
}
restaurantnode* rRR(restaurantnode* root)
{
    restaurantnode* temp=root->right;
    restaurantnode* templeft=temp->left;
    temp->left=root;
    root->right=templeft;
    
    //now first update height of A and then height of B because B is above A.
    
    root->height=max(rheight(root->left),rheight(root->right))+1;
    temp->height=max(rheight(temp->left),rheight(temp->right))+1;
    
    return temp;
}
restaurantnode* rLR(restaurantnode* root)
{
    restaurantnode* tempb=root->left;
    restaurantnode* tempc=tempb->right;
    tempb->right=tempc->left;
    root->left=tempc->right;
    tempc->left=tempb;
    tempc->right=root;
    
    //now first update height of A and height of B then update height of C because C is above A and B
    
    tempb->height=max(rheight(tempb->left),rheight(tempb->right))+1;
    root->height=max(rheight(root->left),rheight(root->right))+1;
    tempc->height=max(rheight(tempc->left),rheight(tempc->right))+1;

    return tempc;
}
restaurantnode* rRL(restaurantnode* root)
{
    restaurantnode* tempb=root->right;
    restaurantnode* tempc=tempb->left;
    tempb->left=tempc->right;
    root->right=tempc->left;
    tempc->right=tempb;
    tempc->left=root;
    
    //now first update height of A and height of B then update height of C because C is above A and B
    
    tempb->height=max(rheight(tempb->left),rheight(tempb->right))+1;
    root->height=max(rheight(root->left),rheight(root->right))+1;
    tempc->height=max(rheight(tempc->left),rheight(tempc->right))+1;
    
    return tempc;
}

int aheight(agentnode* root)
{
    if (root == 0) return 0;
    return root->height;
}
agentnode* aLL(agentnode* root)
{
    agentnode* temp=root->left;
    agentnode* tempright=temp->right;
    temp->right=root;
    root->left=tempright;
    
    //now first update height of A and then height of B because B is above A.
    
    root->height=max(aheight(root->left),aheight(root->right))+1;
    temp->height=max(aheight(temp->left),aheight(temp->right))+1;
    
    return temp;
}
agentnode* aRR(agentnode* root)
{
    agentnode* temp=root->right;
    agentnode* templeft=temp->left;
    temp->left=root;
    root->right=templeft;
    
    //now first update height of A and then height of B because B is above A.
    
    root->height=max(aheight(root->left),aheight(root->right))+1;
    temp->height=max(aheight(temp->left),aheight(temp->right))+1;
    
    return temp;
}
agentnode* aLR(agentnode* root)
{
    agentnode* tempb=root->left;
    agentnode* tempc=tempb->right;
    tempb->right=tempc->left;
    root->left=tempc->right;
    tempc->left=tempb;
    tempc->right=root;
    
    //now first update height of A and height of B then update height of C because C is above A and B
    
    tempb->height=max(aheight(tempb->left),aheight(tempb->right))+1;
    root->height=max(aheight(root->left),aheight(root->right))+1;
    tempc->height=max(aheight(tempc->left),aheight(tempc->right))+1;
    
    return tempc;
}
agentnode* aRL(agentnode* root)
{
    agentnode* tempb=root->right;
    agentnode* tempc=tempb->left;
    tempb->left=tempc->right;
    root->right=tempc->left;
    tempc->right=tempb;
    tempc->left=root;
    
    //now first update height of A and height of B then update height of C because C is above A and B
    
    tempb->height=max(aheight(tempb->left),aheight(tempb->right))+1;
    root->height=max(aheight(root->left),aheight(root->right))+1;
    tempc->height=max(aheight(tempc->left),aheight(tempc->right))+1;
    
    return tempc;
}

int uheight(usernode* root)
{
    if (root == 0) return 0;
    return root->height;
}
usernode* uLL(usernode* root)
{
    usernode* temp=root->left;
    usernode* tempright=temp->right;
    temp->right=root;
    root->left=tempright;
    
    //now first update height of A and then height of B because B is above A.
    
    root->height=max(uheight(root->left),uheight(root->right))+1;
    temp->height=max(uheight(temp->left),uheight(temp->right))+1;
    
    return temp;
}
usernode* uRR(usernode* root)
{
    usernode* temp=root->right;
    usernode* templeft=temp->left;
    temp->left=root;
    root->right=templeft;
    
    //now first update height of A and then height of B because B is above A.
    
    root->height=max(uheight(root->left),uheight(root->right))+1;
    temp->height=max(uheight(temp->left),uheight(temp->right))+1;
    
    return temp;
}
usernode* uLR(usernode* root)
{
    usernode* tempb=root->left;
    usernode* tempc=tempb->right;
    tempb->right=tempc->left;
    root->left=tempc->right;
    tempc->left=tempb;
    tempc->right=root;
    
    //now first update height of A and height of B then update height of C because C is above A and B
    
    tempb->height=max(uheight(tempb->left),uheight(tempb->right))+1;
    root->height=max(uheight(root->left),uheight(root->right))+1;
    tempc->height=max(uheight(tempc->left),uheight(tempc->right))+1;
    
    return tempc;
}
usernode* uRL(usernode* root)
{
    usernode* tempb=root->right;
    usernode* tempc=tempb->left;
    tempb->left=tempc->right;
    root->right=tempc->left;
    tempc->right=tempb;
    tempc->left=root;
    
    //now first update height of A and height of B then update height of C because C is above A and B
    
    tempb->height=max(uheight(tempb->left),uheight(tempb->right))+1;
    root->height=max(uheight(root->left),uheight(root->right))+1;
    tempc->height=max(uheight(tempc->left),uheight(tempc->right))+1;
    
    return tempc;
}


// globalordersnode* gconstruct(globalordersnode* root,int* arr,int st,int end)
// {
//     if(st>end) return 0;
//     int mid=(st+end)/2;
//     root=makenode(arr[mid]);
//     root->left=construct(root->left,arr,st,mid-1);
//     root->right=construct(root->right,arr,mid+1,end);
//     return root;
// }

//this is insertion in AVL tree function which does insertion in O(log n) time

//step1 normal BST insertion
//step2 in return phase first update height and then identify the first violating node and perform rotation on it

//this flag is to identify the first violation in return phase and when we get that we will turn flag to 0 
globalordersnode* ginsert(globalordersnode* root,int* flag,int agentid,char* menu,int restid)
{
    if(root==0)
    {
        globalordersnode* temp=makeglobalordersnode(agentid,menu,restid);
        return temp;
    }
    if(root->data<agentid)
    {
        root->right=ginsert(root->right,flag,agentid,menu,restid);
        
        //now in return phase step1 is to update height and step2 is to update balance factor.
        
        root->height=max(gheight(root->left),gheight(root->right))+1;
        root->balancefactor=gheight(root->left)-gheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=gLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=gRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=gLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=gRL(root);
            }
        }
        return root;
    }
    else if(root->data>agentid)
    {
        root->left=ginsert(root->left,flag,agentid,menu,restid);
        
        root->height=max(gheight(root->left),gheight(root->right))+1;
        root->balancefactor=gheight(root->left)-gheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=gLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=gRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=gLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=gRL(root);
            }
        }
        return root;
    }
}
globalordersnode* gfindsuccessor(globalordersnode* root)
{
    globalordersnode* rootright=root->right;
    if(!rootright) return 0;
    globalordersnode* mov=rootright;
    while(mov->left!=0) mov=mov->left;
    return mov;
}

//this is deletion in AVL tree function which does deletion in O(log n) time

//step1 normal BST delete as traveldelete funtion.
//step2 in return phase first update height and then identify the first violating node and perform rotation on it

//this flag is to identify the first violation in return phase and when we get that we will turn flag to 0 

globalordersnode* gsearchdelete(globalordersnode* root,int agentid,int* flag)
{
    if(agentid<root->data)
    {
        root->left=gsearchdelete(root->left,agentid,flag);
        
        root->height=max(gheight(root->left),gheight(root->right))+1;
        root->balancefactor=gheight(root->left)-gheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=gLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=gRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=gLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=gRL(root);
            }
        }
        return root;
    }
    else if(agentid>root->data)
    {
        root->right=gsearchdelete(root->right,agentid,flag);
        
        root->height=max(gheight(root->left),gheight(root->right))+1;
        root->balancefactor=gheight(root->left)-gheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=gLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=gRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=gLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=gRL(root);
            }
        }
        return root;
    }
    else
    {
        if(root->left==0&&root->right==0) return 0;
        else if(root->left!=0&&root->right==0) return root->left;
        else if(root->left==0&&root->right!=0) return root->right;
        else
        {
            globalordersnode* successor=gfindsuccessor(root);
            //swap(root->data,successor->data);
            int temp=root->data;
            root->data=successor->data;
            successor->data=temp;
            
            root->right=gsearchdelete(root->right,agentid,flag);
            
            root->height=max(gheight(root->left),gheight(root->right))+1;
            root->balancefactor=gheight(root->left)-gheight(root->right);
            
            if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
            {
                *flag=0;
                if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
                {
                    root=gLL(root);
                }
                else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
                {
                    root=gRR(root);
                }
                else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
                {
                    root=gLR(root);
                }
                else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
                {
                    root=gRL(root);
                }
            }
            return root;
        }
    }
}

// prevordersnode* pconstruct(prevordersnode* root,int* arr,int st,int end)
// {
//     if(st>end) return 0;
//     int mid=(st+end)/2;
//     root=makenode(arr[mid]);
//     root->left=construct(root->left,arr,st,mid-1);
//     root->right=construct(root->right,arr,mid+1,end);
//     return root;
// }

prevordersnode* pinsert(prevordersnode* root,int x,int* flag,char*menu,int month)
{
    if(root==0)
    {
        prevordersnode* temp=makeprevordersnode(menu,month);
        return temp;
    }
    if(root->data<x)
    {
        root->right=pinsert(root->right,x,flag,menu,month);
        
        root->height=max(pheight(root->left),pheight(root->right))+1;
        root->balancefactor=pheight(root->left)-pheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=pLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=pRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=pLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=pRL(root);
            }
        }
        return root;
    }
    else if(root->data>x)
    {
        root->left=pinsert(root->left,x,flag,menu,month);
        
        root->height=max(pheight(root->left),pheight(root->right))+1;
        root->balancefactor=pheight(root->left)-pheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=pLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=pRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=pLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=pRL(root);
            }
        }
        return root;
    }
}
prevordersnode* pfindsuccessor(prevordersnode* root)
{
    prevordersnode* rootright=root->right;
    if(!rootright) return 0;
    prevordersnode* mov=rootright;
    while(mov->left!=0) mov=mov->left;
    return mov;
}
prevordersnode* psearchdelete(prevordersnode* root,int x,int* flag)
{
    if(x<root->data)
    {
        root->left=psearchdelete(root->left,x,flag);
        
        root->height=max(pheight(root->left),pheight(root->right))+1;
        root->balancefactor=pheight(root->left)-pheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=pLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=pRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=pLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=pRL(root);
            }
        }
        return root;
    }
    else if(x>root->data)
    {
        root->right=psearchdelete(root->right,x,flag);
        
        root->height=max(pheight(root->left),pheight(root->right))+1;
        root->balancefactor=pheight(root->left)-pheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=pLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=pRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=pLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=pRL(root);
            }
        }
        return root;
    }
    else
    {
        if(root->left==0&&root->right==0) return 0;
        else if(root->left!=0&&root->right==0) return root->left;
        else if(root->left==0&&root->right!=0) return root->right;
        else
        {
            prevordersnode* successor=pfindsuccessor(root);
            //swap(root->data,successor->data);
            int temp=root->data;
            root->data=successor->data;
            successor->data=temp;
            
            root->right=psearchdelete(root->right,x,flag);
            
            root->height=max(pheight(root->left),pheight(root->right))+1;
            root->balancefactor=pheight(root->left)-pheight(root->right);
            
            if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
            {
                *flag=0;
                if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
                {
                    root=pLL(root);
                }
                else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
                {
                    root=pRR(root);
                }
                else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
                {
                    root=pLR(root);
                }
                else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
                {
                    root=pRL(root);
                }
            }
            return root;
        }
    }
}


// restordersnode* roconstruct(restordersnode* root,int* arr,int st,int end)
// {
//     if(st>end) return 0;
//     int mid=(st+end)/2;
//     root=makenode(arr[mid]);
//     root->left=construct(root->left,arr,st,mid-1);
//     root->right=construct(root->right,arr,mid+1,end);
//     return root;
// }

restordersnode* roinsert(restordersnode* root,int x,int* flag,char*menu,int month)
{
    if(root==0)
    {
        restordersnode* temp=makerestordersnode(menu,month);
        return temp;
    }
    if(root->data<x)
    {
        root->right=roinsert(root->right,x,flag,menu,month);
        
        root->height=max(roheight(root->left),roheight(root->right))+1;
        root->balancefactor=roheight(root->left)-roheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=roLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=roRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=roLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=roRL(root);
            }
        }
        return root;
    }
    else if(root->data>x)
    {
        root->left=roinsert(root->left,x,flag,menu,month);
        
        root->height=max(roheight(root->left),roheight(root->right))+1;
        root->balancefactor=roheight(root->left)-roheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=roLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=roRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=roLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=roRL(root);
            }
        }
        return root;
    }
}
restordersnode* rofindsuccessor(restordersnode* root)
{
    restordersnode* rootright=root->right;
    if(!rootright) return 0;
    restordersnode* mov=rootright;
    while(mov->left!=0) mov=mov->left;
    return mov;
}
restordersnode* rosearchdelete(restordersnode* root,int x,int* flag)
{
    if(x<root->data)
    {
        root->left=rosearchdelete(root->left,x,flag);
        
        root->height=max(roheight(root->left),roheight(root->right))+1;
        root->balancefactor=roheight(root->left)-roheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=roLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=roRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=roLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=roRL(root);
            }
        }
        return root;
    }
    else if(x>root->data)
    {
        root->right=rosearchdelete(root->right,x,flag);
        
        root->height=max(roheight(root->left),roheight(root->right))+1;
        root->balancefactor=roheight(root->left)-roheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=roLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=roRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=roLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=roRL(root);
            }
        }
        return root;
    }
    else
    {
        if(root->left==0&&root->right==0) return 0;
        else if(root->left!=0&&root->right==0) return root->left;
        else if(root->left==0&&root->right!=0) return root->right;
        else
        {
            restordersnode* successor=rofindsuccessor(root);
            //swap(root->data,successor->data);
            int temp=root->data;
            root->data=successor->data;
            successor->data=temp;
            
            root->right=rosearchdelete(root->right,x,flag);
            
            root->height=max(roheight(root->left),roheight(root->right))+1;
            root->balancefactor=roheight(root->left)-roheight(root->right);
            
            if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
            {
                *flag=0;
                if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
                {
                    root=roLL(root);
                }
                else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
                {
                    root=roRR(root);
                }
                else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
                {
                    root=roLR(root);
                }
                else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
                {
                    root=roRL(root);
                }
            }
            return root;
        }
    }
}

// restaurantnode* rconstruct(restaurantnode* root,int* arr,int st,int end)
// {
//     if(st>end) return 0;
//     int mid=(st+end)/2;
//     root=makenode(arr[mid]);
//     root->left=construct(root->left,arr,st,mid-1);
//     root->right=construct(root->right,arr,mid+1,end);
//     return root;
// }

restaurantnode* rinsert(restaurantnode* root,int restid,int* flag,char* address,int seats,char* category,char* menu)
{
    if(root==0)
    {
        restaurantnode* temp=makerestaurantnode(restid,address,seats,category,menu);
        return temp;
    }
    if(root->data<restid)
    {
        root->right=rinsert(root->right,restid,flag,address,seats,category,menu);
        
        root->height=max(rheight(root->left),rheight(root->right))+1;
        root->balancefactor=rheight(root->left)-rheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=rLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=rRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=rLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=rRL(root);
            }
        }
        return root;
    }
    else if(root->data>restid)
    {
        root->left=rinsert(root->left,restid,flag,address,seats,category,menu);
        
        root->height=max(rheight(root->left),rheight(root->right))+1;
        root->balancefactor=rheight(root->left)-rheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=rLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=rRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=rLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=rRL(root);
            }
        }
        return root;
    }
}
restaurantnode* rfindsuccessor(restaurantnode* root)
{
    restaurantnode* rootright=root->right;
    if(!rootright) return 0;
    restaurantnode* mov=rootright;
    while(mov->left!=0) mov=mov->left;
    return mov;
}
restaurantnode* rsearchdelete(restaurantnode* root,int x,int* flag)
{
    if(x<root->data)
    {
        root->left=rsearchdelete(root->left,x,flag);
        
        root->height=max(rheight(root->left),rheight(root->right))+1;
        root->balancefactor=rheight(root->left)-rheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=rLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=rRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=rLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=rRL(root);
            }
        }
        return root;
    }
    else if(x>root->data)
    {
        root->right=rsearchdelete(root->right,x,flag);
        
        root->height=max(rheight(root->left),rheight(root->right))+1;
        root->balancefactor=rheight(root->left)-rheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=rLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=rRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=rLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=rRL(root);
            }
        }
        return root;
    }
    else
    {
        if(root->left==0&&root->right==0) return 0;
        else if(root->left!=0&&root->right==0) return root->left;
        else if(root->left==0&&root->right!=0) return root->right;
        else
        {
            restaurantnode* successor=rfindsuccessor(root);
            //swap(root->data,successor->data);
            int temp=root->data;
            root->data=successor->data;
            successor->data=temp;
            
            root->right=rsearchdelete(root->right,x,flag);
            
            root->height=max(rheight(root->left),rheight(root->right))+1;
            root->balancefactor=rheight(root->left)-rheight(root->right);
            
            if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
            {
                *flag=0;
                if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
                {
                    root=rLL(root);
                }
                else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
                {
                    root=rRR(root);
                }
                else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
                {
                    root=rLR(root);
                }
                else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
                {
                    root=rRL(root);
                }
            }
            return root;
        }
    }
}


// agentnode* aconstruct(agentnode* root,int* arr,int st,int end)
// {
//     if(st>end) return 0;
//     int mid=(st+end)/2;
//     root=makenode(arr[mid]);
//     root->left=construct(root->left,arr,st,mid-1);
//     root->right=construct(root->right,arr,mid+1,end);
//     return root;
// }

agentnode* ainsert(agentnode* root,int agentid,int* flag,char* name,char* phoneno)
{
    if(root==0)
    {
        agentnode* temp=makeagentnode(name,agentid,phoneno);
        return temp;
    }
    if(root->data<agentid)
    {
        root->right=ainsert(root->right,agentid,flag,name,phoneno);
        
        root->height=max(aheight(root->left),aheight(root->right))+1;
        root->balancefactor=aheight(root->left)-aheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=aLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=aRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=aLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=aRL(root);
            }
        }
        return root;
    }
    else if(root->data>agentid)
    {
        root->left=ainsert(root->left,agentid,flag,name,phoneno);
        
        root->height=max(aheight(root->left),aheight(root->right))+1;
        root->balancefactor=aheight(root->left)-aheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=aLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=aRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=aLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=aRL(root);
            }
        }
        return root;
    }
}
agentnode* afindsuccessor(agentnode* root)
{
    agentnode* rootright=root->right;
    if(!rootright) return 0;
    agentnode* mov=rootright;
    while(mov->left!=0) mov=mov->left;
    return mov;
}
agentnode* asearchdelete(agentnode* root,int x,int* flag)
{
    if(x<root->data)
    {
        root->left=asearchdelete(root->left,x,flag);
        
        root->height=max(aheight(root->left),aheight(root->right))+1;
        root->balancefactor=aheight(root->left)-aheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=aLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=aRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=aLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=aRL(root);
            }
        }
        return root;
    }
    else if(x>root->data)
    {
        root->right=asearchdelete(root->right,x,flag);
        
        root->height=max(aheight(root->left),aheight(root->right))+1;
        root->balancefactor=aheight(root->left)-aheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=aLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=aRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=aLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=aRL(root);
            }
        }
        return root;
    }
    else
    {
        if(root->left==0&&root->right==0) return 0;
        else if(root->left!=0&&root->right==0) return root->left;
        else if(root->left==0&&root->right!=0) return root->right;
        else
        {
            agentnode* successor=afindsuccessor(root);
            //swap(root->data,successor->data);
            int temp=root->data;
            root->data=successor->data;
            successor->data=temp;
            
            root->right=asearchdelete(root->right,x,flag);
            
            root->height=max(aheight(root->left),aheight(root->right))+1;
            root->balancefactor=aheight(root->left)-aheight(root->right);
            
            if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
            {
                *flag=0;
                if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
                {
                    root=aLL(root);
                }
                else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
                {
                    root=aRR(root);
                }
                else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
                {
                    root=aLR(root);
                }
                else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
                {
                    root=aRL(root);
                }
            }
            return root;
        }
    }
}

// usernode* uconstruct(usernode* root,int* arr,int st,int end)
// {
//     if(st>end) return 0;
//     int mid=(st+end)/2;
//     root=makenode(arr[mid]);
//     root->left=construct(root->left,arr,st,mid-1);
//     root->right=construct(root->right,arr,mid+1,end);
//     return root;
// }

usernode* uinsert(usernode* root,int userid,int* flag,char* name,char* phoneno,char* address)
{
    if(root==0)
    {
        usernode* temp=makeusernode(name,userid,phoneno,address);
        return temp;
    }
    if(root->data<userid)
    {
        root->right=uinsert(root->right,userid,flag,name,phoneno,address);
        
        root->height=max(uheight(root->left),uheight(root->right))+1;
        root->balancefactor=uheight(root->left)-uheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=uLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=uRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=uLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=uRL(root);
            }
        }
        return root;
    }
    else if(root->data>userid)
    {
        root->left=uinsert(root->left,userid,flag,name,phoneno,address);
        
        root->height=max(uheight(root->left),uheight(root->right))+1;
        root->balancefactor=uheight(root->left)-uheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=uLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=uRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=uLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=uRL(root);
            }
        }
        return root;
    }
}
usernode* ufindsuccessor(usernode* root)
{
    usernode* rootright=root->right;
    if(!rootright) return 0;
    usernode* mov=rootright;
    while(mov->left!=0) mov=mov->left;
    return mov;
}
usernode* usearchdelete(usernode* root,int userid,int* flag)
{
    if(userid<root->data)
    {
        root->left=usearchdelete(root->left,userid,flag);
        
        root->height=max(uheight(root->left),uheight(root->right))+1;
        root->balancefactor=uheight(root->left)-uheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=uLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=uRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=uLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=uRL(root);
            }
        }
        return root;
    }
    else if(userid>root->data)
    {
        root->right=usearchdelete(root->right,userid,flag);
        
        root->height=max(uheight(root->left),uheight(root->right))+1;
        root->balancefactor=uheight(root->left)-uheight(root->right);
        
        if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
        {
            *flag=0;
            if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
            {
                root=uLL(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
            {
                root=uRR(root);
            }
            else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
            {
                root=uLR(root);
            }
            else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
            {
                root=uRL(root);
            }
        }
        return root;
    }
    else
    {
        if(root->left==0&&root->right==0) return 0;
        else if(root->left!=0&&root->right==0) return root->left;
        else if(root->left==0&&root->right!=0) return root->right;
        else
        {
            usernode* successor=ufindsuccessor(root);
            //swap(root->data,successor->data);
            int temp=root->data;
            root->data=successor->data;
            successor->data=temp;
            
            root->right=usearchdelete(root->right,userid,flag);
            
            root->height=max(uheight(root->left),uheight(root->right))+1;
            root->balancefactor=uheight(root->left)-uheight(root->right);
            
            if((root->balancefactor<-1||root->balancefactor>1)&&*flag)
            {
                *flag=0;
                if(root->balancefactor==2&&root->left&&root->left->balancefactor==1)
                {
                    root=uLL(root);
                }
                else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==-1)
                {
                    root=uRR(root);
                }
                else if(root->balancefactor==2&&root->left&&root->left->balancefactor==-1)
                {
                    root=uLR(root);
                }
                else if(root->balancefactor==-2&&root->right&&root->right->balancefactor==1)
                {
                    root=uRL(root);
                }
            }
            return root;
        }
    }
}




void search(char* category,char* food,char*area,restaurantnode* root)
{
    if(root==0) return;
    search(category,food,area,root->left);
    if(strcmp(root->address,area)==0) printf("%d\n",root->data);
    else if(strcmp(root->menu,food)==0) printf("%d\n",root->data);
    else if(strcmp(root->facility,category)==0) printf("%d\n",root->data);
    search(category,food,area,root->right);
}
void atravel(agentnode* root,agentnode** save,int *flag)
{
    if(root==0) return;
    
    if(!*flag) atravel(root->left,save,flag);
    
    if(!root->working&&!*flag)
    {
        *flag=1;
        *save=root;
    }
    if(!*flag) atravel(root->right,save,flag);
}
void utravel(usernode* root,usernode** save,int *flag,int userid)
{
    if(root==0) return;
    if(!*flag) utravel(root->left,save,flag,userid);
    if(root->data==userid)
    {
        *flag=1;
        *save=root;
    }
    if(!*flag) utravel(root->right,save,flag,userid);
}
void ptravel(prevordersnode* root,int *flag,char*menu,int month)
{
    if(root==0) return;
    if(!*flag) ptravel(root->left,flag,menu,month);
    if(strcmp(root->order,menu)==0)
    {
        *flag=1;
        root->count++;
        root->month=month;
    }
    if(!*flag) ptravel(root->right,flag,menu,month);
}
void rotravel(restordersnode* root,int *flag,char*menu,int month)
{
    if(root==0) return;
    if(!*flag) rotravel(root->left,flag,menu,month);
    if(strcmp(root->order,menu)==0)
    {
        *flag=1;
        root->count++;
        root->month=month;
    }
    if(!*flag) rotravel(root->right,flag,menu,month);
}
restaurantnode* rsearch(restaurantnode* root,int restid)
{
    
    restaurantnode* mov=root;
    while(mov!=0)
    {
        if(restid<mov->data) mov=mov->left;
        else if(restid>mov->data) mov=mov->right;
        else return mov;
    }
    return 0;
}
agentnode* asearch(agentnode* root,int agentid)
{
    agentnode* mov=root;
    while(mov!=0)
    {
        if(agentid<mov->data) mov=mov->left;
        else if(agentid>mov->data) mov=mov->right;
        else return mov;
    }
    return 0;
}
void order(char* name,char* address,char* phoneno,char* menu,agentnode* agentnodehead,int restid,usernode*usernodehead,int userid,int month,restaurantnode*restauranthead)
{
    //step1 travel the agenttree and see who is free and you got exit from loop and 
    //insert the order in gloalordertree with the agent and mark agent as busy.
    //if no agent available the say no agent available and we will not take that order(because to insert in global list we need the agent id).
    
    //step 2 userlist mai ek prevorders tree hai usee update karna hai by inserting(special way by incrementing count of that menu by searching and not creating copy of same menu )
    
    //step 3 restaurantlist mai ek orders tree hai usee update karna hai by inserting(special way by incrementing count of that menu by searching and not creating copy of same menu )
    
    globalorderid++;
    int flag=0;
    agentnode* agent=0;
    atravel(agentnodehead,&agent,&flag);
    //printf("saved is %d",agent->data);
    //printf("done till this");
    if(flag)
    {
        globalordershead=ginsert(globalordershead,&flag,agent->data,menu,restid);
        //printf("inserted\n");
        //printliveorders();
        agent->working=1;
    }
    else
    {
        printf("no agent available\n");
    }
    //printf("done first part");
    //uss user tak pohoch gaye fir uska prevordershead nikalo
   
    //fir uss menu ka count++ karo
    //side mai linked list wala code kholo if any problem for steps taken.
    
    int flag1=0;
    usernode*user=0;
    utravel(usernodehead,&user,&flag1,userid);
    //printf("user is%d\n",userid);
    int flag2=0;
    prevordersnode* prevorderhead=user->prevordershead;
    //printf("%d\n",prevorderhead);
    ptravel(prevorderhead,&flag2,menu,month);
    //yeh x ko ek globally increase karo as orderid.
    if(!flag2)
    {
        flag2=1;
        user->prevordershead=pinsert(prevorderhead,globalorderid,&flag2,menu,month);
        //printf("%s\n",user->prevordershead->order);
    }
    
   
    //similar logic for restaurant list.
    
    restaurantnode* restaurant=rsearch(restauranthead,restid);
    //printf("restuarnt is %d\n",restaurant->data);
    restordersnode* ordershead=restaurant->ordershead;
    restaurant->ordercount++;
    
    int flag3=0;
    rotravel(ordershead,&flag3,menu,month);
    //yeh x ko ek globally increase karo as orderid.
    if(!flag3)
    {
        flag3=1;
        restaurant->ordershead=roinsert(ordershead,globalorderid,&flag3,menu,month);
    }
    
}
void delivery(int agentid,agentnode*agentnodehead,int comm)
{
    
    //step1 agenttree ko travel karo and uss agent ko commission add karo and uss agent ko not working mark karo.
    //step2 globaltree ko travel karo and remove that order from globalorderlist.
    
    agentnode* agent=asearch(agentnodehead,agentid);
    //printf("I am %d",agent->data);
    agent->working=0;
    printf("I have deliverd my name is %s and my id is %d\n",agent->name,agentid);
    agent->accucommision=agent->accucommision+comm;
    
    int flag=1;
    globalordershead=gsearchdelete(globalordershead,agentid,&flag);
    
}
void cancelorder(int agentid,agentnode*agentnodehead)
{
    //step1 agenttree ko travel karo and uss agent ko not working mark karo.
    //step2 globaltree ko travel karo and remove that order from globalorderlist.
    
    
    agentnode* agent=asearch(agentnodehead,agentid);
    agent->working=0;
    printf("I have recieved cancel order, my agent id is %d\n",agent->data);
    
    int flag=1;
    globalordershead=gsearchdelete(globalordershead,agentid,&flag);
    
}

void findtop3ptravel(prevordersnode* root,int* max,int*secondmax,int*thirdmax,char*first,char*second,char*third)
{
    if(root==0) return;
    findtop3ptravel(root->left,max,secondmax,thirdmax,first,second,third);
    if(root->month<=3)
        {
            if(root->count>*max)
            {
                *thirdmax=*secondmax;
                *secondmax=*max;
                *max=root->count;
                strcpy(third,second);
                strcpy(second,first);
                strcpy(first,root->order);
            }
            else if(root->count>*secondmax)
            {
                *thirdmax=*secondmax;
                *secondmax=root->count;
                strcpy(third,second);
                strcpy(second,root->order);
            }
            else if(root->count>*thirdmax)
            {
                *thirdmax=root->count;
                strcpy(third,root->order);
            }
        }
    findtop3ptravel(root->right,max,secondmax,thirdmax,first,second,third);
}
void findfavoritefoodsofuser(int userid,usernode*usernodehead)
{
    //step1 first find that user in usertree
    //step2 travel the prevorder tree of that user and find top 3 elements.
    
    
    int flag1=0;
    usernode*user=0;
    utravel(usernodehead,&user,&flag1,userid);
    
    
    prevordersnode* prevorderhead=user->prevordershead;
    int max=0;
    int secondmax=0;
    int thirdmax=0;
    char first[100]="";
    char second[100]="";
    char third[100]="";
    findtop3ptravel(prevorderhead,&max,&secondmax,&thirdmax,first,second,third);
    printf("first=%s\n",first);
    printf("second=%s\n",second);
    printf("third=%s\n",third);
    
    
}
void findtop3rotravel(restordersnode* root,int* max,int*secondmax,int*thirdmax,char*first,char*second,char*third)
{
    if(root==0) return;
    findtop3rotravel(root->left,max,secondmax,thirdmax,first,second,third);
    if(root->month<=3)
        {
            if(root->count>*max)
            {
                *thirdmax=*secondmax;
                *secondmax=*max;
                *max=root->count;
                strcpy(third,second);
                strcpy(second,first);
                strcpy(first,root->order);
            }
            else if(root->count>*secondmax)
            {
                *thirdmax=*secondmax;
                *secondmax=root->count;
                strcpy(third,second);
                strcpy(second,root->order);
            }
            else if(root->count>*thirdmax)
            {
                *thirdmax=root->count;
                strcpy(third,root->order);
            }
        }
    findtop3rotravel(root->right,max,secondmax,thirdmax,first,second,third);
}
void findtop3restordertravel(restaurantnode* root,int* max,int*secondmax,int*thirdmax,char*first,char*second,char*third)
{
    if(root==0) return;
    findtop3restordertravel(root->left,max,secondmax,thirdmax,first,second,third);
    findtop3rotravel(root->ordershead,max,secondmax,thirdmax,first,second,third);
    findtop3restordertravel(root->right,max,secondmax,thirdmax,first,second,third);
}
void findfavoritefoodsacrossrestaurants(restaurantnode*restnodehead)
{
    //step1 for each of the restaurant travel its orderstree and find max,secondmax,thirdmax and keep these max, secondmax,thirdmax. 
    //so at last you will get max,secondmax, thirdmax accross all restarants.
    int max=0;
    int secondmax=0;
    int thirdmax=0;
    char first[100]="";
    char second[100]="";
    char third[100]="";
    
    findtop3restordertravel(restnodehead,&max,&secondmax,&thirdmax,first,second,third);
    
    printf("first=%s\n",first);
    printf("second=%s\n",second);
    printf("third=%s\n",third);
    
}
void findtop3rtravel(restaurantnode* root,int* max,int*secondmax,int*thirdmax,int*firstid,int*secondid,int*thirdid)
{
    if(root==0) return;
    findtop3rtravel(root->left,max,secondmax,thirdmax,firstid,secondid,thirdid);
    if(root->ordercount>*max)
    {
        *thirdmax=*secondmax;
        *secondmax=*max;
        *max=root->ordercount;
        *thirdid=*secondid;
        *secondid=*firstid;
        *firstid=root->data;
    }
    else if(root->ordercount>*secondmax)
    {
        *thirdmax=*secondmax;
        *secondmax=root->ordercount;
        *thirdid=*secondid;
        *secondid=root->data;
    }
    else if(root->ordercount>*thirdmax)
    {
        *thirdmax=root->ordercount;
        *thirdid=root->data;
    }
    findtop3rtravel(root->right,max,secondmax,thirdmax,firstid,secondid,thirdid);
}
void findfavoriterestuarants(restaurantnode*restnodehead)
{
    //travel the restaurant tree and see the counts and find max,secondmax,thirdmax.
    
    int max=0;
    int secondmax=0;
    int thirdmax=0;
    int firstid=0;
    int secondid=0;
    int thirdid=0;
    
    findtop3rtravel(restnodehead,&max,&secondmax,&thirdmax,&firstid,&secondid,&thirdid);
    
    printf("first=%d\n",firstid);
    printf("second=%d\n",secondid);
    printf("third=%d\n",thirdid);
    
}

void rangeptravel(prevordersnode* root)
{
    if(root==0) return;
    rangeptravel(root->left);
    printf("order=%s, count=%d  \n",root->order,root->count);
    rangeptravel(root->right);
}
void rangeutravel(usernode* root,int userid1,int userid2)
{
    //travel the usertree and if userid is between userid1 to userid2 , then print the prevorder tree of that user.
    if(root==0) return;
    rangeutravel(root->left,userid1,userid2);
    if(root->data>=userid1&&root->data<=userid2)
    {
        printf("my userid is %d\n",root->data);
        rangeptravel(root->prevordershead);
    }
    rangeutravel(root->right,userid1,userid2);
}
int main()
{
    
    restaurantnode*restaurantroot=0;
    agentnode*agentroot=0;
    usernode*userroot=0;
    
    int flag=1;
    restaurantroot=rinsert(restaurantroot,1,&flag,"bajajnagar",100,"restaurant","chinese");
    flag=1;
    restaurantroot=rinsert(restaurantroot,2,&flag,"vijaynagar",50,"pub","northindian");
    flag=1;
    restaurantroot=rinsert(restaurantroot,3,&flag,"shivajinagar",500,"cafe","southindian");
    flag=1;
    restaurantroot=rinsert(restaurantroot,4,&flag,"rajnagar",250,"restaurant","Italian");
    flag=1;
    restaurantroot=rinsert(restaurantroot,5,&flag,"palnagar",300,"cafe","german");
    
    flag=1;
    agentroot=ainsert(agentroot,1,&flag,"ramu","8686245374");
    flag=1;
    agentroot=ainsert(agentroot,2,&flag,"shamu","7842111628");
    flag=1;
    agentroot=ainsert(agentroot,3,&flag,"bablu","5865456280");
    flag=1;
    agentroot=ainsert(agentroot,4,&flag,"paul","6865456280");
    flag=1;
    agentroot=ainsert(agentroot,5,&flag,"bob","4865456280");
    
    flag=1;
    userroot=uinsert(userroot,1,&flag,"rock","4546247891","balramnagar");
    flag=1;
    userroot=uinsert(userroot,2,&flag,"aditya","7846247891","ramnagar");
    flag=1;
    userroot=uinsert(userroot,3,&flag,"ganesh","7966247891","ganeshnagar");
    flag=1;
    userroot=uinsert(userroot,4,&flag,"john","7966247891","kasnagar");
    flag=1;
    userroot=uinsert(userroot,5,&flag,"smith","7966247891","vijaynagar");
    
    // printf("%d\n",restaurantroot->data);
    // printf("%d\n",restaurantroot->left->data);
    // printf("%d\n",restaurantroot->right->data);
    
    
    //Q1
    //first
    
    //search("restaurant","chinese","bajajnagar",restaurantroot);
    
    //second
    
    //search("restaurant","northindian","shivajinagar",restaurantroot);
    
    //Q2,Q3
    // order("ganesh","ganeshnagar","7966247891","chinese",agentroot,1,userroot,3,1,restaurantroot);
    // order("ganesh","ganeshnagar","7966247891","chinese",agentroot,1,userroot,3,1,restaurantroot);
    // order("aditya","ramnagar","7846247891","northindian",agentroot,2,userroot,2,2,restaurantroot);
    // order("john","kasnagar","7846247891","southindian",agentroot,3,userroot,4,2,restaurantroot);
    // order("smit","vijaynagar","7846247891","Italian",agentroot,4,userroot,5,2,restaurantroot);
    
    // printliveorders();
    
    // // //delivery ka format hai ki first argument is agentid ki konsa agent deliver kar raha.
    // delivery(2,agentroot,100);
    // delivery(3,agentroot,60);
    
    // printliveorders();
    
    //Q4
    // order("ganesh","ganeshnagar","7966247891","chinese",agentroot,1,userroot,3,1,restaurantroot);
    // order("ganesh","ganeshnagar","7966247891","chinese",agentroot,1,userroot,3,1,restaurantroot);
    // order("aditya","ramnagar","7846247891","northindian",agentroot,2,userroot,2,2,restaurantroot);
    // order("john","kasnagar","7846247891","southindian",agentroot,3,userroot,4,2,restaurantroot);
    // order("smit","vijaynagar","7846247891","Italian",agentroot,4,userroot,5,2,restaurantroot);
    
    // printliveorders();
    // delivery(1,agentroot,100);
    // printliveorders();
    
    // cancelorder(2,agentroot);
    // printliveorders();
    
    //Q5
    // order("ganesh","ganeshnagar","7966247891","chinese",agentroot,1,userroot,3,1,restaurantroot);
    // order("ganesh","ganeshnagar","7966247891","chinese",agentroot,1,userroot,3,1,restaurantroot);
    // order("ganesh","ganeshnagar","7966247891","northindian",agentroot,2,userroot,3,1,restaurantroot);
    // order("ganesh","ganeshnagar","7966247891","southindian",agentroot,3,userroot,3,1,restaurantroot);
    // order("ganesh","ganeshnagar","7966247891","southindian",agentroot,3,userroot,3,1,restaurantroot);
    // // // ///dontuncommentjustfordebug///////order("ganesh","ganeshnagar","7966247891","chinese",agenthead,1,userhead,3,1,restauranthead);
    // // // ///dontuncommentjustfordebug///////order("ganesh","ganeshnagar","7966247891","chinese",agenthead,1,userhead,3,1,restauranthead);
    // // // ///dontuncommentjustfordebug/////order("aditya","ramnagar","7846247891","northindian",agenthead,2,userhead,2,2,restauranthead);
    // findfavoritefoodsofuser(3,userroot);
    
    //////printliveorders();
    //////delivery(1,agenthead,100);
    //////printprevorderlistofparticularuser(userhead,1);
    /////printliveorders();
    
    //Q6
    // order("ganesh","ganeshnagar","7966247891","chinese",agentroot,1,userroot,3,1,restaurantroot);
    // order("aditya","ramnagar","7846247891","northindian",agentroot,2,userroot,2,2,restaurantroot);
    // order("aditya","ramnagar","7846247891","northindian",agentroot,2,userroot,2,2,restaurantroot);
    // order("john","kasnagar","7846247891","southindian",agentroot,3,userroot,4,2,restaurantroot);
    // order("smit","vijaynagar","7846247891","Italian",agentroot,4,userroot,5,2,restaurantroot);
    // /////printf("%d",restauranthead->ordershead->count);
    // ///////printf("%d",restauranthead->next->ordershead->count);
    // findfavoriterestuarants(restaurantroot);
    
    //Q7
    // order("ganesh","ganeshnagar","7966247891","chinese",agentroot,1,userroot,3,1,restaurantroot);
    // order("aditya","ramnagar","7846247891","northindian",agentroot,2,userroot,2,2,restaurantroot);
    // order("aditya","ramnagar","7846247891","northindian",agentroot,2,userroot,2,2,restaurantroot);
    // order("john","kasnagar","7846247891","southindian",agentroot,3,userroot,4,2,restaurantroot);
    // order("smit","vijaynagar","7846247891","Italian",agentroot,4,userroot,5,2,restaurantroot);
    // ////// restaurantnode* root=restaurantroot;
    
    // //// // restordersnode* restorderhead=root->left->ordershead;
    // //// // printf("%s",restorderhead->order);
    // //// // printf("%d",restorderhead->count);
    
    // findfavoritefoodsacrossrestaurants(restaurantroot);
    
    
    //Q8
    // order("ganesh","ganeshnagar","7966247891","chinese",agentroot,1,userroot,3,1,restaurantroot);
    // order("aditya","ramnagar","7846247891","northindian",agentroot,2,userroot,2,2,restaurantroot);
    // order("aditya","ramnagar","7846247891","northindian",agentroot,2,userroot,2,2,restaurantroot);
    // order("john","kasnagar","7846247891","southindian",agentroot,3,userroot,4,2,restaurantroot);
    // order("smit","vijaynagar","7846247891","Italian",agentroot,4,userroot,5,2,restaurantroot);
    
    // rock didn't order anything.
    // rangeutravel(userroot,2,5);
    // rangeutravel(userroot,2,4);
    // rangeutravel(userroot,3,3);
    
    
    
    return 0;
}













