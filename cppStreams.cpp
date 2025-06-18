/* String Streams 106L Fall 2019 */
#include <sstream> // stringstream
#include <iostream> // cout, cin
#include <fstream> // file input / output streams
#include <iomanip> // streams manipulations 

using namespace std; 


int stringToInteger(const string& str) {
    istringstream iss(str);
    
    int result;
    char remain;/* -- Ensure no characters after the -- recall example from book: "password  y" */
    // iss >> result;
    // iss >> remain; 
    // if (iss.fail()) throw domain_error("");
    if (!(iss >> result) || iss >> remain) throw domain_error("");

    return result;
}

/* standard iostreams: 
    cin, 
    cout (buffered), 
    cerr (un-buffered),
    clog (buffered)
*/

void standardStreams(){
    int num;

    /* --flushing options-- */
    cout << "CS";
    cout << 106; 
    cout << flush; //1: CS106 only shows up at this point
    cout << 'L'; 
    cout << endl;  //2: endl includes flush. Console: "CS160L\n"
    cout << "some more content"; 
    cin >> num;    //3: cout is flushed when cin is waiting for user input
}

/* 
    endl    insert new line *and flush stream*
    ws      skips all whitespaces until it finds another char
    boolalpha prints "true" and "false" for bools (instead of 1 and 0). 
    noboolalpha negate prev

    hex     prints numbers in hexa
    sepercision adjusts the precision of printed numbers
*/
void someOutputManipulations(){
    cout << "[" << setw(10) << "Ito" << "]"; // Output: [ Ito]
    cout << "[" << left << setw(10) << "Ito" << "]"; //Output: [Ito ]
    cout << "[" << left << setfill('-') << setw(10) << "Ito" << "]";

}

int main() {
    /* stringstream */
    //ostringstream oss("Initial");
    ostringstream oss("Initial", stringstream::ate); // mode flag: ate: start at end
    //istringstream iss("Initial");
    istringstream iss("Initial", stringstream::binary); // mode flag: read as binary

    /*  get possition: oss.tellp(), iss.tellg() 
        set possition: oss.seekp(pos), iss.seekg(pos)
        create offset:          streamoff(n)
    */

    cout << oss.str() << endl; 

    oss << 18.6 << " Ounce "; 
    cout << oss.str() << endl;  

    /* as flushing cout in expensive, this makes \n differ from endl and disable default flushes cout. 
       pottential for performance boost */
    std::ios::sync_with_stdio(false); /* !! */                                      
    for (int i = 1; i <=5; ++i) {
        std::cout << i << '\n'; 
    }


    /*  Output file streams: << (send to file)
        is_open(), open(), close(), fail()

        https://cplusplus.com/reference/fstream/ofstream/#google_vignette
    */
    std::ofstream ofs("hello.txt");
    if (ofs.is_open()) {
        ofs << "Hello CS106L!" << '\n';
    } 
    ofs.close();
    ofs << "this will not get written"; // will silently fail

    //ofs.open("hello.txt");
    ofs.open("hello.txt", std::ios::app); // Flag, specifies to append content, not truncate
    ofs << "this will though, its open again"; 

    /* Input stream */
    std::ifstream ifs("input.txt");
    if (ifs.is_open()) {
        std::string line; 
        std::getline(ifs, line); 
        std::cout << "Read from the file: " << line << '\n'; 
    }
    
    if (ifs.is_open()) {
        std::string lineTwo;
        std::getline(ifs, lineTwo);
        std::cout << "Read from the file: " << lineTwo << '\n';
    }

    /*  std::cin - buffered, think of it as a place where a user stores some data and then read form it.
        It stop reading at a whitespace (" ", \n, \t). leaves the new line (and other white spaces?!) in the buffer
        -- should not use getline and std::cin together because of the difference in how they parse data--
    */

    /*  stream state bits: 
        G: good bit: ready for read/write.
        F: Fail bit: prev operation failed, all future operations frozen.
           on when: type mismatch, file cant be opened, seekg failed
        E: EOF bit: prev operation reached the end of buffer content.
           
        B: Bad bit: extrenal error, likely irrecoverable.
           on when: could not move char-s to buffer from external src (probably src was unexpectedaly deleted)
    */

    return 0;
}

