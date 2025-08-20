#include <iostream>
#include <vector>

using namespace std;

class Group
{
    pair<int, int> bitfield;
    // no setter for bitfield only getter.
    friend class Message;
    int x;
    int y;
};

class Message
{
    pair<int, int> bitfield;
    // the setter will set all the Groups bitfields too.
    vector<Group> groups;
    // groups which are optional cannot be passed into constructor ani, i'm thinking, but there is alternative way.

public:
    void setGroup(Group g)
    {
        groups.push_back(g);
        g.bitfield = bitfield;
    }
};

int main()
{
    return 0;
}