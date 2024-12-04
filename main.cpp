#include <iostream>
#include "parse.h"
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <fstream>
using namespace std;

struct Person {
    std::string name;
    int age;
};

template<>
class MyParse<Person> {
public:
    static Person parse(std::string str) {
        Person p;
        std::string::size_type pos = str.find(',');
        if (pos == std::string::npos) {
            throw std::invalid_argument("can not find ',' for st");
        }
        p.name =  str.substr(0, pos);
        p.age = stoi(str.substr(pos+1, str.size()-pos-1));
        return p;
    }
};



int main() {
    LineParser lp;
    Parser<vector<int> > *parser = new Parser<vector<int> >();
    Parser<Person > *parserPerson = new Parser<Person>();
    Parser<string > *parserString = new Parser<string >();
    Parser<float > *parserFloat = new Parser<float >();
    Parser<vector<float> > *parserFloatVector = new Parser<vector<float> >();
    lp.addParse(parser);
    lp.addParse(parserPerson);
    lp.addParse(parserString);
    lp.addParse(parserFloat);
    lp.addParse(parserFloatVector);
    lp.parse("3:1,2,3\txiaomin,13\tnihao\t3.1415\t2:4.12,2.34");
    cout << parser->data().at(0)<<" "<<parser->data().at(1)<<" "<<parser->data().at(2)<<"\n";
    cout << parserPerson->data().age<<" "<<parserPerson->data().name<<"\n";
    cout << parserString->data()<<"\n";
    cout << parserFloat->data()<<"\n";
    cout << parserFloatVector->data().at(0)<<" "<<parserFloatVector->data().at(1)<<"\n";
    delete(parser);
    return 0;
}
