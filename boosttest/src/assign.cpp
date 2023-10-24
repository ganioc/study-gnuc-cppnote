#include <iostream>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/assign/ptr_list_inserter.hpp>
#include <boost/assign/ptr_map_inserter.hpp>
#include <boost/assign/ptr_list_of.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <numeric>


#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/function_output_iterator.hpp>


using namespace std;
using namespace boost::assign;

struct WorkShift{
    WorkShift(double start=9.30,double end=17.30):start_(start),end_(end){}

    double start_, end_;
};

std::ostream& operator<<(std::ostream& os, const WorkShift& ws){
    return os<<"[" << ws.start_ << " till " << ws.end_ << "]";
}

struct Person{
    string name;
    int age;
    string bank_ac_no;

    Person(const string& name, int years,
        const string& ac_no):
        name(name),age(years),bank_ac_no(ac_no){}

};
void payout(double sum, const string& ac_no){
    cout << "Credited a sum of " << sum 
        << " to bank account number "
        << ac_no << endl;
}

template<typename Itertype>
void creditSum(Itertype first, Itertype last, double sum){
    cout << "creditSum" << endl;
    while(first != last){
        payout(sum, first->bank_ac_no);
        first++;
    }
}
bool seventyOrOlder(const Person& person){
    return person.age >= 70;
}

typedef std::map<string, int> scoremap;

struct GetScore: std::unary_function<const scoremap::value_type& , int>
{
    result_type operator()(argument_type entry) const{
        return entry.second;
    }
};

struct StringCat{
    StringCat(string &str):result_(str){}

    void operator()(const string& arg){
        if(arg.find_first_of(" \t") != string::npos){
            result_ += " \"" + arg + "\"";
        }else{
            result_ += " " +arg;
        }
    }

    string& result_;
};

int main(){
    cout << "assign test: " << endl;

    boost::ptr_vector<WorkShift> shifts = ptr_list_of<WorkShift>(6.00, 14.00);
    ptr_push_back(shifts)(14.00,22.00)(22.00,6.00);

    cout << "ptr_vector size: " << shifts.size() << endl;
    for(boost::ptr_vector<WorkShift>::iterator itr = shifts.begin(); itr != shifts.end(); itr++){
        // cout << itr->start_ << "," << itr->end_ << endl;
        cout << *itr << endl;
    }

    boost::ptr_map<string, WorkShift> shiftMap;
    ptr_map_insert(shiftMap)("morning", 6.00, 14.00)("day")
        ("afternoot", 14.00,22.00)
        ("night", 22.00, 6.00);

    for(const auto& entry: shiftMap){
        cout << entry.first << " " << shiftMap.at(entry.first) << endl;
    }

    std::vector<Person> people {{"A Smith", 71, "5702760"},
        {"L Townshead", 56, "39203234"},
        {"P Pitt", 90, "11110000"}};

    auto first = boost::make_filter_iterator(seventyOrOlder,
        people.begin(), people.end());
    auto last = boost::make_filter_iterator(seventyOrOlder,
        people.end(), people.end());

    creditSum(first, last, 100);

    scoremap subjectScores {{"Physics",80},{"Chemistry", 78},
        {"Statistics", 88},{"mathematics", 92
    }};

    boost::transform_iterator<GetScore,scoremap::iterator>
        first2(subjectScores.begin(), GetScore()),
        last2(subjectScores.end(), GetScore());
    
    cout << std::accumulate(first2, last2, 0) << endl;

    vector<string> dirs{"photos", "videos", "books", "personal docs"};
    string dirString ="";
    copy(dirs.begin(), dirs.end(),
        boost::make_function_output_iterator(
            StringCat(dirString)
        ));
    cout << "dirString: " << dirString << endl;
    return 0;
}