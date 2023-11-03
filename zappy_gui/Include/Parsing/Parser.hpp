/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** Parser
*/

#pragma once

#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
 
namespace parsing {

    class Option {
        public :

            class OptionException : public std::exception {

                public:
                    OptionException(const std::string &comment) noexcept :
                        _error("Option exception : (" + comment + ")")
                    {};

                    const char *what(void) const noexcept {
                        return _error.c_str();
                    }

                private:
                    const std::string _error;
            };

            Option(const std::string &name,
                const std::vector<std::string> &paramNames = {},
                const std::string &description = "",
                const std::size_t &nbParams = 0,
                const bool &isMandatory = false);

            inline auto setData(const std::string &data) -> void { _datas.push_back(data); };

            inline auto getData() const -> const std::vector<std::string> & { return _datas; };

            std::string _name;
            std::vector<std::string> _paramNames;
            std::string _description;
            std::size_t _nbParams;
            bool _isMandatory;

        private :
            std::vector<std::string> _datas;
    };

    class Parser {
        public:

            class ParserException : public std::exception {

                public:
                    ParserException(const std::string &comment) noexcept :
                        _error("Parser exception : (" + comment + ")")
                    {};

                    const char *what(void) const noexcept {
                        return _error.c_str();
                    }

                private:
                    const std::string _error;
            };

            Parser(const int &argc, char *const *argv);

            inline auto getOptions(void) const -> const std::map<std::string, std::pair<bool, Option>> &
                { return _options; };

            auto addOption(const Option &option) -> void;

            auto optionIsSets(const std::string &name) const -> bool;

            auto removeOption(const std::string &name) -> void;

            inline auto clear(void) -> void { _options.clear(); _values.clear(); _nbMandatoryFlags = 0; };

            auto operator [](const std::string &name) -> const std::vector<std::string> &;

            inline auto getValues(void) const -> const std::vector<std::string> & { return _values; };

            auto parse(void) -> void;

            auto displayUsage(void) -> void;

        private:
            std::vector<std::string> _args;
            const std::string _programName;
            std::map<std::string, std::pair<bool, Option>> _options;
            std::vector<std::string> _values;
            std::size_t _nbMandatoryFlags;
    };
}

auto operator <<(std::ostream &out, const parsing::Parser &parser) -> std::ostream &;
