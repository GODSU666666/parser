#include <iostream>

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <fstream>
using namespace std;

// 通用解析类模板
template <typename T>
class MyParse {
    static T parse(std::string str) {
        T t;
        return t;
    };
};

// 特化版本，处理 int 类型
template <>
class MyParse<int> {
public:
    static int parse(std::string str) {
        return std::stoi(str);
    };
};

// 特化版本，处理 float 类型
template <>
class MyParse<float> {
public:
    static float parse(const std::string& str) {
        return std::stof(str);
    }
};

// 特化版本，处理 string 类型
template <>
class MyParse<string> {
public:
    static string parse(const std::string& str) {
        return str;
    }
};

// 特化版本，处理 vector 类型
template <typename T>
class MyParse<vector<T> > {
public:
    static vector<T> parse(const std::string& str) {
        vector<T> result;
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
            result.push_back(MyParse<T>::parse(sub_str));
        }
        if (!ss.eof()) {
            throw std::invalid_argument("parse vector");
        }

        return result;
    }
};


class ParserBase {
public:
    virtual int parse(const std::string& str) = 0;
    virtual ~ParserBase() {};
};

template <typename T>
class Parser : public ParserBase  {
public:
    Parser() {};
    int parse(const std::string& str) override {
        try {
           _data =  MyParse<T>::parse(str);
        } catch (std::exception& e) {
            return -1;
        }
        return 0;
    }

    T& data() {
        return _data;
    }
private:
    T _data;
};


class LineParser {
public:
    void addParse(ParserBase* p) {
        parseList.push_back(p);
    }
    int parse(std::string str) const {
        std::stringstream ss(str);
        std::string sub_str;
        unsigned int i = 0;
        while (getline(ss, sub_str, '\t') && i < parseList.size()) {
            int res = parseList[i]->parse(sub_str);
            if (res < 0) {
                return -1;
            }
            i++;
        }
        if (ss.eof() && (i == parseList.size())) {
            return 0;
        }
        return -1;
    }

private:
    vector<ParserBase*> parseList;
};


