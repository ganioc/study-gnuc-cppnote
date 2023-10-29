#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/rank.hpp>
#include <boost/type_traits/extent.hpp>
#include <boost/type_traits/is_pod.hpp>

using namespace std;

typedef vector<string> NameVec;

NameVec getNameShorterThan(const NameVec& names,
    size_t maxSize){
    NameVec shortNames;
    copy_if(names.begin(), names.end(),
        back_inserter(shortNames),
        [maxSize](const string& name){
            return name.size() <= maxSize;
        });
    return shortNames;
}

struct Book{
    Book(const string& id,
        const string& name,
        const string& auth)
            :isbn(id), title(name), author(auth)
        {}
    
    string isbn;
    string title;
    string author;
};

bool operator <(const Book& lhs, const Book& rhs){
    return lhs.isbn < rhs.isbn;
}
bool byDescendingISBN(const Book& lhs, const Book& rhs){
    return lhs.isbn > rhs.isbn;
}

template<unsigned int N>
struct Factorial
{
    enum{ value = N*Factorial<N-1>::value};
};
template<>
struct Factorial<0>
{
    enum{value=1};
};
template<typename T>
struct IsPointer{
    enum {value =0};
};

template<typename T>
struct IsPointer <T*>{
    enum {value = 1};
};
struct MyStruct{
    int n;
    float f;
    const char*s;
};

template<typename T, size_t N>
T* fastCopy(T(&arr)[N], boost::true_type podType){
    cerr << "fastCopy for POD" << endl;
    T *cpyarr = new T[N];
    memcpy(cpyarr, arr, N*sizeof(T));

    return cpyarr;
}
template<typename T, size_t N>
T* fastCopy(T(&arr)[N], boost::false_type nonPodType){
    cerr << "fastCopy for non-POD" << endl;
    T *cpyarr = new T[N];
    copy(&arr[0], &arr[N], &cpyarr[0]);

    return cpyarr;
}
template<typename T, size_t N>
T* fastCopy(T(&arr)[N]){
    return fastCopy(arr, typename boost::is_pod<T>::type());
}

void testTemplates(){
    cout << "Factorial: " << Factorial<4>::value << endl;

    cout << IsPointer<int>::value << endl;
    cout << IsPointer<int*>::value << endl;

    typedef int* intptr;
    cout << "intptr is "
        << (boost::is_pointer<intptr>::value?" ":"not ")
        << "pointer type"
        << endl;
    // introspect arrays

    int arr[10], arr2[10][15];
    cout << "arry type: " << boost::is_array<decltype(arr)>::value << endl;
    cout << "rank: "<< boost::rank<decltype(arr2)>::value <<endl;
    cout <<"arr extent:" << boost::extent<decltype(arr)>::value<<endl;
    cout <<"arr2 extent:"<<boost::extent<decltype(arr2)>::value <<endl;
    cout <<"arr2 extent 2:"<<boost::extent<decltype(arr2),0>::value <<endl;
    cout <<"arr2 extent 2:"<<boost::extent<decltype(arr2),1>::value <<endl;

    MyStruct podarr[10] = {};
    string strarr[10];
    auto *cpyarr = fastCopy(podarr);
    auto *cpyarr2 = fastCopy(strarr);

    delete[] cpyarr;
    delete[] cpyarr2;

}

template<typename T, size_t N>
void copy(T (&lhs)[N], T(&rhs)[N]){
    for(size_t i=0; i< N; i++){
        lhs[i] = rhs[i];
    }
}


int main(){
    cout << "Higher order functions:" << endl;

    vector<Book> books;
    books.emplace_back("908..511..123", "Little Prince",
        "Antoine St. Exupery");
    books.emplace_back("392..301..109", "Nineteen Eighty Four",
        "George Orwell");
    books.emplace_back("872..610..176", "to kill a mocking bird",
        "Harper Lee");
    books.emplace_back("392..301..109", "Animal Farm",
        "George Orwell");

    sort(books.begin(), books.end());

    cout << "Print out the books:" << endl;
    for(auto& book: books){
        cout << book.title << ": " 
        << book.isbn
        << endl;
    }

    sort(books.begin(), books.end(), byDescendingISBN);
    cout << endl
    << "Print out the books, again:" << endl;
    for(auto& book: books){
        cout << book.title << ": " 
        << book.isbn
        << endl;
    }

    vector<int> vec{2,4,6,8,9,1};
    auto it = find_if(vec.begin(), vec.end(),
        [](const int& num)-> bool{
            return num%2 !=0;
        });

    cout << "lambda find_if: " << *it << endl;

    vector<string> names{"Groucho", "Chico", "Harpo"};
    vector<string::size_type> lengths;

    transform(names.begin(), names.end(),
        back_inserter(lengths),
        bind(&string::size, placeholders::_1));
    
    // cout << "transform： " << lengths << endl;
    for( auto & len: lengths){
        cout << "len: " << len << endl;
    }

    string strPi = "3.1415926";
    double pi = boost::lexical_cast<double>(strPi);
    cout << "pi: " << pi << endl;

    testTemplates();
    return 0;
}