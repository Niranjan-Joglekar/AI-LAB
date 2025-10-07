#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;
map<string, vector<string>> ParentToChild;
map<string, string> ChildToParent;

void addRelation(string Parent, string children){
    ParentToChild[Parent].push_back(children);
    ChildToParent[children] = Parent;
}

void GetChildren(string Person){
    if (ParentToChild.find(Person) != ParentToChild.end())
    {
        cout<<"Children of "<< Person <<":";
        for (auto &child : ParentToChild[Person])
        {
            cout<<child<<" ";
        }
        cout<<endl;
    }else{
        cout<<"Person has no children";
    }
    
}

void getSiblings(string Person){
    if (ChildToParent.find(Person) != ChildToParent.end()){
        string parent = ChildToParent[Person];
        cout<<"Siblings of "<< Person <<": ";
        for (auto &sib : ParentToChild[parent])
        {
           if (sib != Person) cout << sib << " ";
        }
        cout<<endl;
    }else{
        cout<<"Person has no children";
    }
    
}

int main()
{
    addRelation("John", "Alice");
    addRelation("John", "Bob");
    addRelation("Alice", "Charlie");
    addRelation("Alice", "Diana");

    GetChildren("Alice");
    getSiblings("Bob");
}