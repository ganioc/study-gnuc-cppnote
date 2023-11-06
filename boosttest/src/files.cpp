#include <boost/filesystem.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/counter.hpp>
#include <boost/iostreams/filter/grep.hpp>
#include <iostream>
#include <ostream>

#include <vector>

using namespace std;
namespace fs = boost::filesystem;
namespace io = boost::iostreams;

void traverse(const fs::path &dirpath)
{
    if (!fs::exists(dirpath) || !fs::is_directory(dirpath))
    {
        return;
    }

    fs::directory_iterator dirit(dirpath), end;

    for_each(dirit, end,
             [](const fs::directory_entry &entry)
             {
                 cout << entry.path().string() << endl;
             });
}
void writeToMemory()
{
    cout << "Test write to memory" << endl;

    char out_array[256];
    io::array_sink osink(out_array, out_array + sizeof(out_array));
    io::stream<io::array_sink> out(osink);

    out << "Size of out_array is " << sizeof(out_array)
         << '\n'
         << ends << flush;
    
    vector<char> vchars(out_array, out_array + strlen(out_array));

    io::array_source src(vchars.data(), vchars.size());
    io::stream<io::array_source> in(src);

    io::copy(in, cout);

    typedef vector<char> charvec;
    charvec output;
    io::back_insert_device<charvec> sink(output);
    io::stream<io::back_insert_device<charvec>> iout(sink);

    iout << "Size of insert outputs " << output.size() << ends << flush;

    charvec ivchars(output.begin(), output.begin() + output.size());
    io::array_source isrc(ivchars.data(), ivchars.size());
    io::stream<io::array_source> iin(isrc);

    io::copy(iin, cout);
    cout << endl;
}
void writeThroughFilter(const char* filename){
    io::file_source infile(filename);
    io::counter counter;
    io::filtering_istream fis;
    fis.push(counter);
    cout << "fis is complete: " << fis.is_complete() <<endl;
    fis.push(infile);
    io::copy(fis, cout);

    io::counter *ctr = fis.component<io::counter>(0);
    cout << "Chars: " << ctr->characters() << endl  
        << "Lines: " << ctr->lines() << endl;
}
void testGrepFilter(const char* filename){
    io::file_source infile(filename);
    io::filtering_istream fis;
    io::grep_filter grep(boost::regex("^\\s*$"),
        boost::regex_constants::match_default, io::grep::invert);
    fis.push(grep);
    fis.push(infile);

    io::copy(fis,cout);

}
void testCompressionFilter(){
    cout << endl << "Test compression filter" << endl;
    
}
int main(void)
{
    cout << "===== Test files lib =====" << endl;

    // get the current working directory
    fs::path cwd = fs::current_path();

    cout << "cwd: " << cwd << endl;
    cout << "generic: " << cwd.generic_string() << endl;
    cout << "native: " << cwd.string() << endl;

    cout << "Components:" << endl;
    for (const auto &dir : cwd)
    {
        cout << '[' << dir.string() << ']';
    }
    cout << endl;

    fs::path pl1;
    pl1 = "/opt/boost";
    pl1.clear();
    cout << "Is pl1 empty? " << pl1.empty() << endl;

    fs::path pl2("..");
    pl2 /= "..";
    cout << "Relative path: " << pl2.string() << endl;
    cout << "Absolute path: " << fs::absolute(pl2, "E:\\DATA\\photos").string() << endl;
    cout << "Absolute path without CWD: " << fs::absolute(pl2).string() << endl;
    cout << "canonical string: " << fs::canonical(pl2).string() << endl;

    fs::path p3 = "E:\\DATA";
    auto p4 = p3 / "boost" / "boost_1_56";
    cout << p4.string() << endl;
    cout.put('\n');

    boost::system::error_code ec;
    auto p5 = p4 / ".." / "boost_1_100";
    auto p6 = fs::canonical(p5, ec);

    if (ec.value() == 0)
    {
        cout << "Normalized: " << p6.string() << endl;
    }
    else
    {
        cout << ec.message() << endl;
    }

    cout << "p6: " << p6 << endl;

    fs::path dirpath = fs::current_path();
    traverse(dirpath);

    writeToMemory();

    writeThroughFilter("test.tmp");

    testGrepFilter("test.tmp");

    testCompressionFilter();

    return 0;
}