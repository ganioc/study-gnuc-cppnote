#include <iostream>
#include <boost/container/vector.hpp>
#include <boost/container/slist.hpp>

using namespace std;

typedef boost::container::slist<string> list_type;
typedef list_type::iterator iter_type;

int main(){
    cout << "Test container move" <<endl;

    // boost::container::vector<S

    boost::container::slist<string> geologic_areas;

    geologic_areas.push_front("Neogene");
    geologic_areas.push_front("Paleogene");
    geologic_areas.push_front("Cretaceous");

    for(const auto& str: geologic_areas){
        cout << str << endl;
    }

    cout << "try iterator:" << endl;
    boost::container::slist<string> eras;
    boost::container::slist<string>::iterator last =
        eras.before_begin();
    
    const char* era_names[] = {
        "Cambrian",
        "Ordovician",
        "Silurian",
        "Devonian",
        "Carboniferous"
    };

    for(const char *period: era_names){
        eras.emplace_after(last, period);
        ++last;
    }

    int i = 0;
    for(const auto& str: eras){
        cout << "str: " << era_names[i++] << endl;
    }

    cout << "splicing: " << endl;
    list_type dinos;
    iter_type last_splicing = dinos.before_begin();

    const char* dinoarray[] = {"Elasmosaurus",
        "Fabrosaurus", "Galimimus", "Hadrosaurus",
        "Iguanodon", "Appatosaurus", "Brachiosaurus"};
    
    // fill the slist
    for(const char* dino: dinoarray){
        dinos.insert_after(last_splicing, dino);
        ++last_splicing;
    }

    // find the pivot
    last_splicing = dinos.begin();
    iter_type iter = last_splicing;

    while(++iter != dinos.end()){
        if(*last_splicing > *iter){
            break;
        }
        ++last_splicing;
    }

    return 0;
}