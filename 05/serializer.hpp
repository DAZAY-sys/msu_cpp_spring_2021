#pragma once
#include <iostream>

enum class Error
{
    NoError,
    CorruptedArchive
};

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer);

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer);
};

class Serializer
{
    static constexpr char Separator = ' ';
    std::ostream out_;
public:
    std::string string_out;
    explicit Serializer(std::ostream& out) : out_(out.rdbuf()) {
        string_out.clear();
    }

    template <class T>
    Error save(T& object);

    template <class... ArgsT>
    Error operator()(ArgsT... args);

private:
    template <class T, class... ArgsT>
    Error process(T&& val, ArgsT&&... args);
    template <class T>
    Error process(T val);
    Error process(bool arg);
    Error process(uint64_t arg);
};

class Deserializer
{
    static constexpr char Separator = ' ';
    std::istream in_;

    public:
    std::string string_in;
    explicit Deserializer(std::istream& in): in_(in.rdbuf()) {
        string_in.clear();
    }

    template <class T>
    Error load(T& object);

    template <class... ArgsT>
    Error operator()(ArgsT&... args);

private:
    template <class T, class... ArgsT>
    Error process(T& val, ArgsT&... args);
    template<class T>
    Error process(T& val);
    Error process(bool& value);
    Error process(uint64_t& value);
};

#include "serializer.tpp"
