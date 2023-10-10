#include <iostream>
#include <string>
#include <algorithm>
// #include <cassert>
// #include <cctype>
#include <boost/algorithm/string.hpp>
#include <boost/range.hpp>
#include <boost/range/adaptors.hpp>

using namespace std;

struct MinLen{
    bool operator()(const string& s) const {
        return s.size() > 3;
    }
};
struct EqualsShift{
    EqualsShift(unsigned int n): shift(n) {}
    bool operator()(char input, char search) const{
        int disp = tolower(input) - 'a' - shift;
        return tolower(search) == (disp >= 0)?'a':'z' + disp;
    }
private:
    unsigned long shift;
};
void test_find(){
    string haystack = "How little is too little";
    string needle = "Little";

    auto ret = boost::find(haystack,
        boost::last_finder(needle,
            boost::is_equal()));
    
    string encoded = "Lsa pmxxpi mw xss pmxxpi";
    string realWord = "little";
    auto ret2 = boost::find(encoded,
        boost::first_finder(realWord,
                        EqualsShift(4)));

    
}

void test_conversion(){
    string str = "funny text";
    auto range = str | boost::adaptors::strided(2);
    boost::to_upper(range);
    cout << "conversion: " << str << endl;
}

int main()
{
    cout << "Test string" << endl;
    string song = "Green tinted sixties mind";
    transform(song.begin(), song.end(), song.begin(), ::toupper);

    cout << "song: " << song << endl;

    string song2 = "Arab Isaralei";
    boost::to_upper(song2);
    cout << "song2: " << song2 << endl;

    char songarr[17] = "Book of Taliesyn";
    boost::to_upper(songarr);
    cout << "songarr: " << songarr << endl;

    string song3 = "Blue tainted body tusk";
    typedef boost::iterator_range<string::iterator> RangeType;
    RangeType range = boost::make_iterator_range(
        song3.begin() + 13,
        song3.begin() + 20);
    boost::to_upper(range);
    cout << "song3: " << song3 << endl;

    char songarr2[17] = "Brai of Taliesym";
    typedef boost::iterator_range<char *> ArrRangeType;
    ArrRangeType rng = boost::make_iterator_range(
        songarr2 + 8,
        songarr2 + 16);
    boost::to_upper(rng);
    cout << "songarr2: " << songarr2 << endl;

    string input = "linearize";
    string test = "near";
    cout << "If contains: " << boost::contains(input, test) << endl;

    string str1 = "Find the Cost of Freedom";
    string str2 = boost::to_lower_copy(str1);
    cout << "str2: " << str2 << endl;
    cout << "str1: " << str1 << endl;

    const char *haystack = "Mary had a little lamb";
    const char *needles[] = {"little", "Little", 0};

    for (int i = 0; needles[i] != 0; i++)
    {
        auto ret = boost::find_first(haystack, needles[i]);
        if (ret.begin() == ret.end())
        {
            cout << "String [" << needles[i] << "] not found" << endl;
        }
        else
        {
            cout << "String [" << needles[i] << "] found at "
                 << "offset " << ret.begin() - haystack
                 << " in string [" << haystack << endl;
        }

        cout << "'" << ret << "'" << endl;
        
    }

    typedef boost::iterator_range<string::const_iterator> string_range;
    vector<string_range> matches;
    string str_find = "He deserted the unit while they trudged "
        "through the desert one night.";
    boost::find_all(matches, str_find, "desert");

    for(auto match: matches){
        cout << "Found [" << "desert" << "] at offset "
            << match.begin() - str_find.begin() << endl;
    }

    // token find
    string str_token = "The application tried to read from an "
        "invalid address at 0xbeeffed";
    auto token = boost::find_token(str_token, 
            boost::is_xdigit(),
            boost::token_compress_on);
    while(token.begin() != token.end()){
        if(boost::size(token) > 3){
            cout << token <<endl;
        }
        auto remnant = boost::make_iterator_range(token.end(),
            str_token.end());
        token = boost::find_token(remnant, boost::is_xdigit(),
            boost::token_compress_on);
    }

    vector<string> v;
    auto ret_2 = boost::iter_find(v, str_token,
        boost::token_finder(boost::is_xdigit(),
            boost::token_compress_on));
    ostream_iterator<string> osit(cout , ", ");
    copy_if(v.begin(), v.end(), osit, MinLen());

    test_find();
    test_conversion();

    return 0;
}