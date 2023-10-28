#include <iostream>
#include <set>
#include <string>

using namespace std;

struct  PersonEntry
{
    /* data */
    string name;
    string phoneNumber;
    string city;
};
bool operator <(const PersonEntry& left, const PersonEntry& right){
    return left.name < right.name;
}

int main(){
    cout << "multi-criteria test: " << endl;
    multiset<PersonEntry> directory;
    PersonEntry p1{"Arindam Mukherjee", "550 888 9999", "Pune"};
    PersonEntry p2{"Arindam Mukherjee", "990 770 2458", "Calcutta"};
    directory.insert(p1);
    directory.insert(p2);

    auto it1 = directory.lower_bound(
        PersonEntry{"Arindam Mukherjee","",""});
    auto it2 = directory.upper_bound(
        PersonEntry{"Arindam Mukherjee","",""});
    
    while(it1 != it2){
        cout << "Found: [" << it1->name << ", "
            << it1->phoneNumber << ", " << it1->city << "["
            << endl;
        it1++;
    }
    return 0;
}