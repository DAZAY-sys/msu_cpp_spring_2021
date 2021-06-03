#pragma once
#include <iostream>
#include <vector>
#include <system_error>
#include <algorithm>
#include <typeinfo>
#include <sstream>

struct IndexError
{
    std::string message_;

    IndexError(const std::string& message)
        : message_(message)
    {}
};

struct ArgError
{
    std::string message_;
    ArgError(const std::string& message):
        message_(message)
        {}
};

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

template <class T>
void process(std::vector<std::string> &arguments, T&& val)
{
    std::stringstream stream;

//    std::string part = "";
    try
    {
        stream << val;
    }
    catch(...)
    {
        throw ArgError("Mistake in argument type!\n");
    }
    arguments.push_back(stream.str());
}

template <class T, class... ArgsT>
void process(std::vector<std::string> &arguments, T&& val, ArgsT&&... args)
{
//    std::string part = "";
    std::stringstream stream;

    try
    {
////        if (typeid(val) != typeid(std::string) or
////            typeid(val) != typeid(const char ))
//
//            part = std::to_string(val);
        stream << val;
    }
    catch(...)
    {
        throw ArgError("Mistake in argument type!\n");
    }
    arguments.push_back(stream.str());

    process(arguments, std::forward<ArgsT>(args)...);
}

template <class... ArgsT>
std::string format(std::string line, ArgsT... args)
{
    std::vector<int> indexes;
    std::vector<std::string> arguments;
    std::string answer = "";
    size_t max_index = 0;
    std::string word;
    size_t begin_pos = 0, end_pos = 0, last_pos = 0;

    while ((begin_pos = line.find_first_of("{", last_pos)) != std::string::npos)
    {
        end_pos = line.find_first_of("}", begin_pos);
        answer += line.substr(last_pos, begin_pos - last_pos + 1);
        if (end_pos == std::string::npos)
            throw IndexError("Wrong bracket order!");
        else
        {
            word = line.substr(begin_pos + 1, end_pos - begin_pos - 1);
            if (!is_number(word))
                throw IndexError("Wrong symbols brackets!\n");
            else if (std::stoi(word) > (int)max_index)
                max_index = std::stoi(word);

            indexes.push_back(std::stoi(word));
        }
        last_pos = end_pos + 1;
    }

    word = line.substr(last_pos);
    if (word.length() != 0)
        answer += word;

    process(arguments, std::forward<ArgsT>(args)...);
    if (arguments.size() < max_index + 1)
        throw ArgError("Incorrect argument index!\n");
    else
    {
        begin_pos = 0, end_pos = 0, last_pos = 0;
        size_t i = 0;
        while ((begin_pos = answer.find_first_of("{", last_pos)) != std::string::npos)
        {
            answer.replace(begin_pos, 1, arguments[indexes[i]]);
            last_pos = begin_pos + 1;
            i += 1;
        }
    }
    return answer;
}

