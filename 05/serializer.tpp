#include "serializer.hpp"

template <class Serializer>
Error Data::serialize(Serializer& serializer)
{
    return serializer(a, b, c);
}

template <class T>
Error Serializer::save(T& object)
{
    return object.serialize(*this);
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT... args)
{
    return process(args...);
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
    out_ << Separator;
    if (arg == true)
        out_ << "true";
    else if (arg == false)
         out_ << "false";
    return Error::NoError;
}

template <class T>
Error Serializer::process(T arg)
{
    return Error::CorruptedArchive;
}

Error Serializer::process(uint64_t arg)
{
    out_ << Separator << arg;
    return Error::NoError;
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

template <class T>
Error Deserializer::load(T& object)
{
    Error err;
    if (in_.peek() == EOF)
        return Error::CorruptedArchive;
    err = object.deserialize(*this);
    if (in_.peek() != EOF)
        return Error::CorruptedArchive;
    else
        return err;
}

template <class T, class... ArgsT>
Error Deserializer::process(T& val, ArgsT&... args)
{
    Error a;
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

    if (text == "true")
        value = true;
    else if (text == "false")
        value = false;
    else
        return Error::CorruptedArchive;

    return Error::NoError;
}

Error Deserializer::process(uint64_t& value)
{
    std::string text;
    in_ >> text;
    value = std::stoull(text);
    return Error::NoError;
}
