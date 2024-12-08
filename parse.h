#include <iostream>

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

// 通用解析类模板
class MyParserBase {
public:
    virtual int parse(const std::string& str) = 0;
    virtual ~MyParserBase()=default;

};

template<typename  T>
class MyParser : public MyParserBase {
public:
    ~MyParser() override =default;

    virtual T& data() {
        return _data;
    }
    private:
    T _data{};
};

class IntParser final : public MyParser<int> {
public:
    int parse(const std::string& str) override {
        try {
            _data = std::stoi(str);
        } catch (std::exception& e) {
            return -1;
        }
        return 0;
    };
    IntParser() {
        _data = 0;
    };
    int& data() override {
        return _data;
    }
private:
    int _data;
};

class FloatParser final : public MyParser<float> {
public: int parse(const std::string& str) override {
    try {
        _data = std::stof(str);
    } catch (std::exception& e) {
        return -1;
    }
    return 0;
};
    FloatParser() {
        _data = 0.0;
    };
    float &data() override {
        return _data;
    };
private:
    float _data;
};

class StringParser final : public MyParser<std::string> {
public: int parse(const std::string& str) override {
    try {
        _data = str;
    } catch (std::exception& e) {
        return -1;
    }
    return 0;
};
    std::string &data() override {
        return _data;
    };
private:
   std::string _data;
};


class PersonParser final : public MyParser<Person> {
public: int parse(const std::string& str) override {
    try {
        std::string::size_type pos = str.find('-');
        if (pos == std::string::npos) {
            throw std::invalid_argument("can not find ',' for st");
        }
       _data.name =  str.substr(0, pos);
       _data.age = stoi(str.substr(pos+1, str.size()-pos-1));
    } catch (std::exception& e) {
        return -1;
    }
    return 0;
};
    Person &data() override {
        return _data;
    };
private:
    Person _data;
};




class IntArrayParser final : public MyParser<vector<int>> {
public: int parse(const std::string& str) override {
    try {
        vector<int> result;
        std::string::size_type pos = str.find(':');
        if (pos == std::string::npos) {
            throw std::invalid_argument("can not find ':' for vector");
        }
        int num = std::stoi(str.substr(0, pos));
        std::stringstream ss(str.substr(pos + 1, str.size() - pos - 1));
        std::string sub_str;
        for (int i=0;i<num;i++) {
            if (ss.eof()) {
                throw std::invalid_argument("parse vector");
            }
            getline(ss,sub_str,',');
            result.push_back(stoi(sub_str));
        }
        if (!ss.eof()) {
            throw std::invalid_argument("parse vector");
        }
        _data = result;
    } catch (std::exception& e) {
        return -1;
    }
    return 0;
};
    vector<int> &data() override {
        return _data;
    };
    IntArrayParser() {
        _data = vector<int>{};
    };
private:
    std::vector<int> _data;
};


class FloatArrayParser final : public MyParser<vector<float>> {
public: int parse(const std::string& str) override {
    try {
        vector<float> result;
        std::string::size_type pos = str.find(':');
        if (pos == std::string::npos) {
            throw std::invalid_argument("can not find ':' for vector");
        }
        int num = std::stoi(str.substr(0, pos));
        std::stringstream ss(str.substr(pos + 1, str.size() - pos - 1));
        std::string sub_str;
        for (int i=0;i<num;i++) {
            if (ss.eof()) {
                throw std::invalid_argument("parse vector");
            }
            getline(ss,sub_str,',');
            result.push_back(stof(sub_str));
        }
        if (!ss.eof()) {
            throw std::invalid_argument("parse vector");
        }
        _data = result;
    } catch (std::exception& e) {
        return -1;
    }
    return 0;
};
    vector<float> &data() override {
        return _data;
    };
    FloatArrayParser() {
        _data = vector<float>{};
    };
private:
    std::vector<float> _data;
};


class PersonArrayParser final : public MyParser<vector<Person>> {
public: int parse(const std::string& str) override {
    try {
        vector<Person> result;
        std::string::size_type pos = str.find(':');
        if (pos == std::string::npos) {
            throw std::invalid_argument("can not find ':' for vector");
        }
        int num = std::stoi(str.substr(0, pos));
        std::stringstream ss(str.substr(pos + 1, str.size() - pos - 1));
        std::string sub_str;

        for (int i=0;i<num;i++) {
            if (ss.eof()) {
                throw std::invalid_argument("parse vector");
            }
            getline(ss,sub_str,',');
            std::string::size_type pos = sub_str.find('-');
            if (pos == std::string::npos) {
                throw std::invalid_argument("can not find ',' for st");
            }

            Person temp;
            temp.name =  sub_str.substr(0, pos);
            temp.age = stoi(sub_str.substr(pos+1, str.size()-pos-1));
            result.push_back(temp);
        }
        if (!ss.eof()) {
            throw std::invalid_argument("parse vector");
        }
        _data = result;
    } catch (std::exception& e) {
        return -1;
    }
    return 0;
};
    vector<Person> &data() override {
        return _data;
    };
    PersonArrayParser() {
        _data = vector<Person>{};
    };
private:
    std::vector<Person> _data;
};





class LineParser {
public:
    void addParse(MyParserBase* p) {
        parserList.push_back(p);
    }
    int parse(const std::string& str) const {
        std::stringstream ss(str);
        std::string sub_str;
        unsigned int i = 0;
        while (getline(ss, sub_str, '\t') && i < parserList.size()) {
            if (const int res = parserList[i]->parse(sub_str); res < 0) {
                return -1;
            }
            i++;
        }
        if (ss.eof() && (i == parserList.size())) {
            return 0;
        }
        return -1;
    }

private:
    vector<MyParserBase*> parserList;
};


