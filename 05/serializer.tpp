#include "serializer.hpp"

template <class Serializer>
Error Data::serialize(Serializer& serializer)
{
    return serializer(a, b, c);
}

template <class T>
Error Serializer::save(T& object)
{
    string_out.clear();
    return object.serialize(*this);
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT... args)
{
    Error err = process(args...);
    if (err == Error::NoError)
        out_ << string_out;
    return err;
}

template <class T, class... ArgsT>
Error Serializer::process(T&& val, ArgsT&&... args)
{
    if(process(val) == Error::NoError)
        return process(std::forward<ArgsT>(args)...);
    else return Error::CorruptedArchive;
}

Error Serializer::process(bool arg)
{
    if (string_out.length() != 0)
        string_out += Separator;
    if (arg == true)
        string_out += "true";
    else if (arg == false)
        string_out += "false";
    return Error::NoError;
}

template <class T>
Error Serializer::process(T arg)
{
    return Error::CorruptedArchive;
}

Error Serializer::process(uint64_t arg)
{
    if (string_out.length() != 0)
        string_out += Separator;
    string_out += std::to_string(arg);
    return Error::NoError;
}

template <class T>
Error Deserializer::load(T& object)
{
    Error err;
    if (in_.peek() == EOF)
        return Error::CorruptedArchive;

    string_in.clear();
    err = object.deserialize(*this);
    if (in_.peek() != EOF)
        return Error::CorruptedArchive;
    else
        return err;
}

template <class Deserializer>
Error Data::deserialize(Deserializer& deserializer)
{
    return deserializer(a, b, c);
}

template <class... ArgsT>
Error Deserializer::operator()(ArgsT&... args)
{
    return process(args...);
}

template <class T, class... ArgsT>
Error Deserializer::process(T& val, ArgsT&... args)
{
    if(process(val) == Error::NoError)
        return process(args...);
    else return Error::CorruptedArchive;
}

template<class T>
Error Deserializer::process(T& val)
{
    val = -1; // чтобы не выводилось предупреждение об неиспольз переменной
    return Error::CorruptedArchive;
}

Error Deserializer::process(bool& value)
{
    std::string text;

    in_ >> text;

    if (text == "")
        return Error::CorruptedArchive;

    if (text == "true")
    {
        value = true;
        if (string_in.length() != 0)
        {
            string_in += Separator;
            string_in += text;
        }
    }
    else if (text == "false")
    {
        value = false;
        if (string_in.length() != 0)
        {
            string_in += Separator;
            string_in += text;
        }
    }
    else
        return Error::CorruptedArchive;

    return Error::NoError;
}

Error Deserializer::process(uint64_t& value)
{
    std::string text;
    in_ >> text;

    if (text == "")
        return Error::CorruptedArchive;

    if (string_in.length() != 0)
        string_in += Separator;
    string_in += text;

    value = std::stoull(text);
    return Error::NoError;
}
