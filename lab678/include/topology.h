#ifndef LAB6_TOPOLOGY_H
#define LAB6_TOPOLOGY_H

#include <list>
#include <stdexcept>

class Topology { 
private:
    std::list<std::list<int>> container; 

public:
    void Insert(int id, int parent_id); 
    int Find(int id); 
    void Erase(int id); 
    int GetFirstId(int list_id); 
};

#endif // LAB6_TOPOLOGY_H