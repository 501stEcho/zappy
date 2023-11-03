/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** Parser
*/

#include "Parsing/Parser.hpp"
#include <iostream>

parsing::Option::Option(const std::string &name,
    const std::vector<std::string> &paramNames,
    const std::string &description,
    const std::size_t &nbParams,
    const bool &isMandatory) :
    _name(name),
    _paramNames(paramNames),
    _description(description),
    _nbParams(nbParams),
    _isMandatory(isMandatory),
    _datas{}
{
    if (paramNames.size() != nbParams)
        throw OptionException("Invalid number of param names");
}

parsing::Parser::Parser(const int &argc, char *const *argv) :
    _args{},
    _programName(argv[0]),
    _options{},
    _values{},
    _nbMandatoryFlags(0)
{
    for (int index = 0; (index < argc) && argv[index]; ++index)
        _args.push_back(argv[index]);
}

auto parsing::Parser::addOption(const Option &option) -> void
{
    auto emplacde = _options.emplace(std::make_pair(option._name, std::make_pair(false, option)));

    if (!emplacde.second)
        throw ParserException("Option : " + option._name + "already exists");
    if (option._isMandatory)
        ++_nbMandatoryFlags;
}

auto parsing::Parser::optionIsSets(const std::string &name) const -> bool
{
    auto finded = _options.find(name);

    if (finded == _options.end() || !finded->second.first)
        return false;
    return true;
}

auto parsing::Parser::removeOption(const std::string &name) -> void
{
    _options.erase(name);
}

auto parsing::Parser::operator [](const std::string &name) -> const std::vector<std::string> &
{
    auto finded = _options.find(name);

    if (finded == _options.end())
        throw ParserException("Invalid option :" + name);
    return finded->second.second.getData();
}

auto parsing::Parser::parse(void) -> void
{
    std::size_t encounteredMandatory = 0;
    auto entry = _args.begin();

    ++entry;
    _values.clear();
    while (entry != _args.end()) {
        if (!entry->starts_with("-")) {
            _values.push_back(*entry);
            ++entry;
            continue;
        }
        auto finded = _options.find(*entry);

        if (finded == _options.end())
            throw ParserException("Invalid option : " + *entry);
        auto &findedOption = finded->second.second;

        if (findedOption._nbParams)
            ++entry;

        for (std::size_t nbArgs = 0; (nbArgs < findedOption._nbParams) &&
            (entry != _args.end()) && !entry->starts_with("-") ; ++entry) {
            findedOption.setData(*entry);
        }

        if (findedOption.getData().size() != findedOption._nbParams)
            throw ParserException("Invalid number of args : " + findedOption._name);

        if (findedOption._isMandatory)
            ++encounteredMandatory;
        finded->second.first = true;

        if ((entry != _args.end()) && (!entry->starts_with("-") || findedOption._nbParams == 0))
            ++entry;
    }
    if (encounteredMandatory != _nbMandatoryFlags)
        throw ParserException("All mandatoryFlags are not present");
}

auto parsing::Parser::displayUsage(void) -> void
{
    std::cout << "USAGE: " << _programName << std::endl;
    for (auto &entry : _options) {
        std::cout << "\t" << entry.second.second._name << " ";
        for (auto &paramName : entry.second.second._paramNames)
            std::cout << "<" << paramName << "> ";
        std::cout << entry.second.second._description
            << " nbParams[" << entry.second.second._nbParams << "]"
            << " isMandatory : " << entry.second.second._isMandatory << std::endl;
    }
}

auto operator <<(std::ostream &out, const parsing::Parser &parser) -> std::ostream &
{
    const auto &options = parser.getOptions();
    const auto &values = parser.getValues();

    for (const auto &entry : options) {
        out << entry.second.second._name << " ";
        out << (parser.optionIsSets(entry.second.second._name) ? "OK" : "KO") << " ";
        for (const auto &data : entry.second.second.getData())
            out << data;
        out << std::endl;
    }
    out << "Values [" << values.size() << "] : " << std::endl;
    for (const auto &value : values)
        out << value << " ";
    return out;
}
