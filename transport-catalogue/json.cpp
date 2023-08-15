#include "json.h"

using namespace std;

namespace json {

    namespace {

        Node LoadNode(istream& input);

        Node LoadArray(istream& input) {
            Array result;
            char c;
            input >> c;
            input.putback(c);
            for (char c; input >> c && c != ']';) {
                if (c != ',') {
                    input.putback(c);
                }
                result.push_back(LoadNode(input));
            }
            if (result.empty() && c != ']') {
                input.putback(c);
                throw ParsingError(""s);
            }
            return Node(move(result));
        }

        Node LoadNumber(std::istream& input) {
            using namespace std::literals;

            std::string parsed_num;

            // Считывает в parsed_num очередной символ из input
            auto read_char = [&parsed_num, &input] {
                parsed_num += static_cast<char>(input.get());
                if (!input) {
                    throw ParsingError("Failed to read number from stream"s);
                }
            };

            // Считывает одну или более цифр в parsed_num из input
            auto read_digits = [&input, read_char] {
                if (!std::isdigit(input.peek())) {
                    throw ParsingError("A digit is expected"s);
                }
                while (std::isdigit(input.peek())) {
                    read_char();
                }
            };

            if (input.peek() == '-') {
                read_char();
            }
            // Парсим целую часть числа
            if (input.peek() == '0') {
                read_char();
                // После 0 в JSON не могут идти другие цифры
            }
            else {
                read_digits();
            }

            bool is_int = true;
            // Парсим дробную часть числа
            if (input.peek() == '.') {
                read_char();
                read_digits();
                is_int = false;
            }

            // Парсим экспоненциальную часть числа
            if (int ch = input.peek(); ch == 'e' || ch == 'E') {
                read_char();
                if (ch = input.peek(); ch == '+' || ch == '-') {
                    read_char();
                }
                read_digits();
                is_int = false;
            }

            try {
                if (is_int) {
                    // Сначала пробуем преобразовать строку в int
                    try {
                        int value = std::stoi(parsed_num);
                        return Node(value);
                    }
                    catch (...) {
                        // В случае неудачи, например, при переполнении,
                        // код ниже попробует преобразовать строку в double
                    }
                }
                double value = std::stod(parsed_num);
                return Node(value);
            }
            catch (...) {
                throw ParsingError("Failed to convert "s + parsed_num + " to number"s);
            }
        }

        Node LoadSimpleString(istream& input) {
            string line;
            char c;
            while (input >> c && c != ',') {
                
                if (c == ']' || c == '}') {
                    input.putback(c);
                    break;
                }
                line.push_back(c);
            }
           
            //getline(input, line, ',');
            try {
                string sub_line = line.substr(line.find_first_not_of(" \n\r\"\t\\"), line.find_last_not_of(" \n\r\"\t\\") + 1);
                if (sub_line == "null") {
                    return Node(move(nullptr));
                }
                else if (sub_line == "true") {
                    return Node(move(true));
                }
                else if (sub_line == "false") {
                    return Node(move(false));
                }
                throw ParsingError(""s);
            }
            catch (...) {
                throw ParsingError(""s);
            }
        }

        // Считывает содержимое строкового литерала JSON-документа
        // Функцию следует использовать после считывания открывающего символа ":
        Node LoadString(std::istream& input) {
            using namespace std::literals;

            auto it = std::istreambuf_iterator<char>(input);
            auto end = std::istreambuf_iterator<char>();
            std::string s;
            while (true) {
                if (it == end) {
                    // Поток закончился до того, как встретили закрывающую кавычку?
                    throw ParsingError("String parsing error");
                }
                const char ch = *it;
                if (ch == '"') {
                    // Встретили закрывающую кавычку
                    ++it;
                    break;
                }
                else if (ch == '\\') {
                    // Встретили начало escape-последовательности
                    ++it;
                    if (it == end) {
                        // Поток завершился сразу после символа обратной косой черты
                        throw ParsingError("String parsing error");
                    }
                    const char escaped_char = *(it);
                    // Обрабатываем одну из последовательностей: \\, \n, \t, \r, \"
                    switch (escaped_char) {
                    case 'n':
                        s.push_back('\n');
                        break;
                    case 't':
                        s.push_back('\t');
                        break;
                    case 'r':
                        s.push_back('\r');
                        break;
                    case '"':
                        s.push_back('"');
                        break;
                    case '\\':
                        s.push_back('\\');
                        break;
                    default:
                        // Встретили неизвестную escape-последовательность
                        throw ParsingError("Unrecognized escape sequence \\"s + escaped_char);
                    }
                }
                else if (ch == '\n' || ch == '\r') {
                    // Строковый литерал внутри- JSON не может прерываться символами \r или \n
                    throw ParsingError("Unexpected end of line"s);
                }
                else {
                    // Просто считываем очередной символ и помещаем его в результирующую строку
                    s.push_back(ch);
                }
                ++it;
            }

            return Node(move(s));
        }

        Node LoadDict(istream& input) {
            Dict result;
            char c;
            input >> c;
            input.putback(c);
            for (char c; input >> c && c != '}';) {
                if (c == ',') {
                    input >> c;
                }
                string key = LoadString(input).AsString();
                input >> c;
                result.insert({ move(key), LoadNode(input) });
            }            
            if (result.empty() && c != '}') {
                input.putback(c);
                throw ParsingError(""s);
            }            
            return Node(move(result));
        }
        Node LoadNode(istream& input) {
            char c;
            input >> c;

            if (c == '[') {
                return LoadArray(input);
            }
            else if (c == '{') {
                return LoadDict(input);
            }
            else if (c == '"') {
                return LoadString(input);
            }
            else if (!std::isdigit(c) && c != '-') {
                input.putback(c);
                return LoadSimpleString(input);
            }
            else{
                input.putback(c);
                return LoadNumber(input);
            }
        }
    }  // namespace

    Node::Node() :value_(nullptr){
    }
    
    Node::Node(Array val) :value_(std::move(val))
    {
    }
    Node::Node(Dict val) :value_(std::move(val))
    {
    }
    Node::Node(string val) :value_(std::move(val))
    {
    }
    
    bool Node::IsInt() const{
        return std::holds_alternative<int>(value_);
    }

    bool Node::IsDouble() const{
        return std::holds_alternative<int>(value_) || std::holds_alternative<double>(value_);
    }

    bool Node::IsPureDouble() const{
        return std::holds_alternative<double>(value_);
    }

    bool Node::IsBool() const{
        return std::holds_alternative<bool>(value_);
    }

    bool Node::IsString() const{
        return std::holds_alternative<string>(value_);
    }

    bool Node::IsNull() const{
        return std::holds_alternative<nullptr_t>(value_);
    }

    bool Node::IsArray() const{
        return std::holds_alternative<Array>(value_);
    }

    bool Node::IsMap() const{
        return std::holds_alternative<Dict>(value_);
    }

    const Array& Node::AsArray() const {
        if (IsArray()) {
            return get<Array>(GetValue());
        }throw std::logic_error("");
    }

    const Dict& Node::AsMap() const {
        if (IsMap()) {
            return get<Dict>(GetValue());
        }throw std::logic_error("");
    }

    int Node::AsInt() const {
        if (IsInt()) {
            return get<int>(GetValue());
        }throw std::logic_error("");
    }

    bool Node::AsBool() const{
        if (IsBool()) {
            return get<bool>(GetValue());
        }throw std::logic_error("");
    }

    double Node::AsDouble() const{
        if (IsPureDouble()) {
            return get<double>(GetValue());
        }
        else if (IsInt())
        {
            return get<int>(GetValue()) + 0.0;
        }throw std::logic_error("");
    }

    const string& Node::AsString() const {
        if (IsString()) {
            return get<string>(GetValue());
        }throw std::logic_error("");
    }

    const Value& Node::GetValue() const{
        return value_;
    }

    bool operator==(const Node& lhs, const Node& rhs){
        if (typeid(lhs) == typeid(rhs)) {
            if (lhs.GetValue() == rhs.GetValue()) {
                return true;
            }
        }
        return false;
    }

    bool operator!=(const Node& lhs, const Node& rhs){
        return !(lhs == rhs);
    }
    
    bool operator==(const Document& lhs, const Document& rhs) {
        return lhs.GetRoot() == rhs.GetRoot();
    }
    bool operator!=(const Document& lhs, const Document& rhs) {
        return lhs.GetRoot() != rhs.GetRoot();
    }

    ostream& operator<<(ostream& os, const Array& arr) {
        os << "[";
        bool flag = false;
        for (const auto& value : arr) {
            if (flag) {
                os << " ," << endl;
            }flag = true;
            PrintMapArray(value, os);
        }
        os << "]";
        return os;
    }
    
    std::ostream& operator<<(std::ostream& os, const Dict& dict) {
        os << "{";
        bool flag = false;
        for (const auto& [key, value] : dict) {
            if (flag) {
                os << " ," << endl;
            }flag = true;
            os << "\"" << key << "\": ";
            PrintMapArray(value, os);
        }
        os << "}";
        return os;
    }
    

    //---------------Document-----------------------
    Document::Document(Node root)
        : root_(move(root)) {
    }

    const Node& Document::GetRoot() const {
        return root_;
    }

    Document Load(istream& input) {
        return Document{ LoadNode(input) };
    }

    void Print(const Document& doc, std::ostream& output) {
        std::visit(PrintValue{ output }, doc.GetRoot().GetValue());
    }

    
    void PrintMapArray(const Node& value, std::ostream& os) {
        
        std::visit(PrintValue{os }, value.GetValue());
        
    }
}  // namespace json