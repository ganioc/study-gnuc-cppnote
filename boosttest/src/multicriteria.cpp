#include <iostream>
#include <set>
#include <string>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

using namespace std;
using namespace boost::multi_index;

struct PersonEntry
{
    /* data */
    string name;
    string phoneNumber;
    string city;
};
bool operator<(const PersonEntry &left, const PersonEntry &right)
{
    return left.name < right.name;
}
typedef ordered_non_unique<identity<PersonEntry>> by_person;
// typedef multi_index_container<PersonEntry,indexed_by<by_person>> directory_t;
typedef ordered_non_unique<member<PersonEntry, string, &PersonEntry::name>> by_name;
typedef ordered_unique<member<PersonEntry, string, &PersonEntry::phoneNumber>> by_phone;
typedef multi_index_container<PersonEntry, indexed_by<by_name, by_phone>> directory_t;

void test_multi()
{
    directory_t phonedir;
    PersonEntry p1{"Arindam Mukherjee", "550 888 9999", "Pune"};
    PersonEntry p2{"Arindam Mukherjee", "990 770 2458", "Calcutta"};
    PersonEntry p3{"Ace Ventura", "457 330 1288", "Tampa"};

    phonedir.insert(p1);
    phonedir.insert(p2);
    phonedir.insert(p3);

    auto iter = phonedir.find("Ace Ventura");
    if (iter != phonedir.end())
    {
        cout << iter->city << endl;
    }

    auto &ph_indx = phonedir.get<1>();
    auto iter2 = ph_indx.find("990 770 2458");
    if (iter2 != ph_indx.end())
    {
        cout << iter2->city << endl;
    }

    for(auto& elem: ph_indx){
        cout << elem.name << " live in " << elem.city 
            << " and can be reached at " << elem.phoneNumber
            << endl;
    }
}

int main()
{
    cout << "multi-criteria test: " << endl;
    multiset<PersonEntry> directory;
    PersonEntry p1{"Arindam Mukherjee", "550 888 9999", "Pune"};
    PersonEntry p2{"Arindam Mukherjee", "990 770 2458", "Calcutta"};
    directory.insert(p1);
    directory.insert(p2);

    auto it1 = directory.lower_bound(
        PersonEntry{"Arindam Mukherjee", "", ""});
    auto it2 = directory.upper_bound(
        PersonEntry{"Arindam Mukherjee", "", ""});

    while (it1 != it2)
    {
        cout << "Found: [" << it1->name << ", "
             << it1->phoneNumber << ", " << it1->city << "["
             << endl;
        it1++;
    }

    test_multi();
    return 0;
}