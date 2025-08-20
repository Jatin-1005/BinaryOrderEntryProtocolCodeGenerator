#include <iostream>
#include <string>
#include <vector>

//Regularly push changes to github.
using namespace std;

struct HERO {
    string name;
    int age;
    float weight;
    char symbol;
};

int main(){
    vector<HERO> heros(2);
    heros[0].name = "Spiderman";
    heros[0].age = 20;
    heros[0].weight = 84.2;
    heros[0].symbol = 'X';

    HERO* subhash = (HERO*)(malloc(sizeof(HERO)));
    try
    {
        subhash->name = "Subhash";
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
        std::cout << "malloc doesn't fully contruct the object" << endl;
        subhash = new(subhash) HERO;
        subhash->name = "Subhash";
    }
    std::cout << "Name of hero is " << subhash->name << endl;
    return 0;
}