#include <iostream>
#include "parse.h"
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <fstream>
using namespace std;

// struct Person {
//     std::string name;
//     int age;
// };

// class MyParse<Person> {
// public:
//     static Person parse(std::string str) {
//         Person p;
//         std::string::size_type pos = str.find(',');
//         if (pos == std::string::npos) {
//             throw std::invalid_argument("can not find ',' for st");
//         }
//         p.name =  str.substr(0, pos);
//         p.age = stoi(str.substr(pos+1, str.size()-pos-1));
//         return p;
//     }
// };



int main() {
    LineParser lp;
    MyParser<int> *intParser = new IntParser();
    MyParser<float> *floatParser = new FloatParser();
    MyParser<string> *stringParser = new StringParser();
    MyParser<vector<int>> *intArrayParser = new IntArrayParser();
    MyParser<vector<float>> *floatArrayParser = new FloatArrayParser();
    MyParser<Person> *personParser = new PersonParser();
    MyParser<vector<Person>> *personArrayParser = new PersonArrayParser();
    lp.addParse(intParser);
    lp.addParse(floatParser);
    lp.addParse(stringParser);
    lp.addParse(intArrayParser);
    lp.addParse(floatArrayParser);
    lp.addParse(personParser);\
    lp.addParse(personArrayParser);
    lp.parse("4\t3.14\ttest\t3:1,2,3\t2:1.3,1.1\tnihao-23\t2:sxm-1,sxm1-2\t2:4.12,2.34");
    cout << intParser->data();
    cout << floatParser->data();
    cout << stringParser->data();
    cout << intArrayParser->data().at(0);
    cout << floatArrayParser->data().at(0);
    cout << personParser->data().name;
    cout << personArrayParser->data().at(1).name;
    cout << personArrayParser->data().at(0).age;
    // cout << intParser->data()<<" "<<parser->data().at(1)<<" "<<parser->data().at(2)<<"\n";
    // cout << parserPerson->data().age<<" "<<parserPerson->data().name<<"\n";
    // cout << parserString->data()<<"\n";
    // cout << parserFloat->data()<<"\n";
    // cout << parserFloatVector->data().at(0)<<" "<<parserFloatVector->data().at(1)<<"\n";

    return 0;
}
