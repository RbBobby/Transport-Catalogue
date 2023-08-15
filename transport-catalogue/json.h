#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <variant>


namespace json {
    using namespace std::literals;
    
    class Node;
    // Сохраните объявления Dict и Array без изменения
    using Number = std::variant<int, double>;
    using Dict = std::map<std::string, Node>;
    using Array = std::vector<Node>;
    using Value = std::variant<std::nullptr_t, Array, Dict, bool, int, double, std::string>;
    // Эта ошибка должна выбрасываться при ошибках парсинга JSON
    class ParsingError : public std::runtime_error {
    public:
        using runtime_error::runtime_error;
    };
    std::ostream& operator<<(std::ostream& os, const Dict& dict);
    std::ostream& operator<<(std::ostream& out, const Array& arr);

    

    class Node {
    public:
        /* Реализуйте Node, используя std::variant */
        Node();
        
        template <typename T>
        Node(T val);

        Node(Array val);
        Node(Dict val);
        Node(std::string val);

        bool IsInt() const;
        bool IsDouble() const;
        bool IsPureDouble() const;
        bool IsBool() const;
        bool IsString() const;
        bool IsNull() const;
        bool IsArray() const;
        bool IsMap() const;

        int AsInt() const;
        bool AsBool() const;
        double AsDouble() const;
        const std::string& AsString() const;
        const Array& AsArray() const;
        const Dict& AsMap() const;

        const Value& GetValue() const;
    private:
        Value value_;
    };

    struct PrintValue {
        PrintValue(std::ostream& out) : out_(out) {}
        std::ostream& out_;

        //---------------PrintValue-----------------------
        void operator()(std::nullptr_t) const
        {
            out_ << "null"sv;
        }
        void  operator()(const Array& value) const {
            out_ << value;
        }
        void operator()(const Dict& value) const
        {
            out_ << value;
        }
        void operator()(bool value) const {
            out_ << std::boolalpha << value;
        }
        void operator()(int value) const {
            out_ << value;
        }
        void operator()(double value) const {
            out_ << value;
        }
        void  operator()(std::string value) const {
            out_ << "\"";
            for (const auto& letter : value) {
                switch (letter) {
                case '\r':
                    out_ << "\\r";
                    break;
                case '\n':
                    out_ << "\\n";
                    break;
                case '\"':
                    out_ << "\\\"";
                    break;
                case '\\':
                    out_ << "\\\\";
                    break;
                default:
                    out_ << letter;
                }
            }
            out_ << "\"";
        }
    };

    template <typename T>
    Node::Node(T value) : value_(value) {}

    bool operator==(const Node& lhs, const Node& rhs);
    bool operator!=(const Node& lhs, const Node& rhs);
   
    class Document {
    public:
        explicit Document(Node root);
        Document() = default;
        const Node& GetRoot() const;

    private:
        Node root_;
    };
    

    bool operator==(const Document& lhs, const Document& rhs);
    bool operator!=(const Document& lhs, const Document& rhs);
    Document Load(std::istream& input);

    void Print(const Document& doc, std::ostream& output);    
    
    void PrintMapArray(const Node& value, std::ostream& os);
    
}  // namespace json