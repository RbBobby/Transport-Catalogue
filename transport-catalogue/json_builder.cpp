#include "json_builder.h"



namespace json {
	DictItemContext::DictItemContext(BaseContext base_context) : BaseContext(base_context)
	{
	}

	KeyItemContext::KeyItemContext(BaseContext base_context) : BaseContext(base_context)
	{
	}
	
	DictItemContext KeyItemContext::Value(Node::Value&& value)
	{	
			return builder_.Value(std::move(value));
	}
	
	ArrayItemContext::ArrayItemContext(BaseContext base_context) : BaseContext(base_context)
	{
	}

	ArrayItemContext ArrayItemContext::Value(Node::Value&& value)
	{
		return builder_.Value(std::move(value));
	}

	//------------------------BaseContext-------------------------------------
	
	BaseContext::BaseContext(Builder& builder) :builder_(builder)
	{
	}

	KeyItemContext BaseContext::Key(std::string&& str)
	{
		return builder_.Key(std::move(str));
	}

	BaseContext BaseContext::Value(Node::Value&& value)
	{
		return builder_.Value(std::move(value));
	}

	DictItemContext BaseContext::StartDict()
	{
		return builder_.StartDict();
	}

	ArrayItemContext BaseContext::StartArray()
	{
		return builder_.StartArray();
	}

	BaseContext BaseContext::EndDict()
	{
		return builder_.EndDict();
	}

	BaseContext BaseContext::EndArray()
	{
		return builder_.EndArray();
	}
	Node BaseContext::Build()
	{
		return builder_.Build();
	}
	//------------------------Builder-------------------------------------
	KeyItemContext json::Builder::Key(std::string&& str)
	{
		if (flag) {
			throw std::logic_error("Node completed");
		}
		keys.push_back(std::move(str));

		last_command = LastCommand::Key;
		
		return  KeyItemContext(*this);;
	}

	BaseContext Builder::Value(Node::Value&& value)
	{		
		if (flag) {
			throw std::logic_error("Node completed");
		}		
		if (last_command == LastCommand::Start) {
			if (nodes_stack_.empty()) {
				node_ = Node(std::move(value));
				flag = true;
			}
			last_command = LastCommand::Value;
			return BaseContext(*this);
		}
		else if (last_command == LastCommand::Key && nodes_stack_.back()->IsDict()) {
			std::get<Dict>(nodes_stack_.back()->GetValueNotConst())[keys.back()] = std::move(value);
			keys.pop_back();
			last_command = LastCommand::Value;
			return DictItemContext(*this);
		}
		else if (nodes_stack_.back()->IsArray()) {
			std::get<Array>(nodes_stack_.back()->GetValueNotConst()).emplace_back(std::move(value));
			last_command = LastCommand::Value;
			return ArrayItemContext(*this);
		}
		else {
			throw std::logic_error("It isn't arr");
		}
		last_command = LastCommand::Value;
		return BaseContext(*this);
	}

	DictItemContext Builder::StartDict()
	{	
		if (flag) {
			throw std::logic_error("Node completed");
		}
		Node* node = new Node(Dict());
		nodes_stack_.emplace_back(node);
		last_command = LastCommand::StartDict;
		
		return DictItemContext(*this);
	}

	ArrayItemContext Builder::StartArray()
	{
		if (flag) {
			throw std::logic_error("Node completed");
		}
		Node* node = new Node(Array());
		nodes_stack_.emplace_back(node);
		last_command = LastCommand::StartArray;
		
		return  ArrayItemContext(*this);
	}

	BaseContext Builder::EndDict()
	{
		if (flag) {
			throw std::logic_error("Node completed");
		}
		if (nodes_stack_.back()->IsArray()) {
			throw std::logic_error("It isn't arr");
		}
		Dict dict = std::get<Dict>(nodes_stack_.back()->GetValueNotConst());
		if (nodes_stack_.size() == 1) {
			node_ = *(nodes_stack_.back());
			flag = true;
			
			return BaseContext(*this);
		}
		nodes_stack_.pop_back();
		if (nodes_stack_.back()->IsArray()) {			
			std::get<Array>(nodes_stack_.back()->GetValueNotConst()).emplace_back(dict);
		}else if (nodes_stack_.back()->IsDict()) {
			std::get<Dict>(nodes_stack_.back()->GetValueNotConst())[keys.back()] = std::move(dict);
			keys.pop_back();
		}
		last_command = LastCommand::EndDict;
		
		return BaseContext(*this);
	}

	BaseContext Builder::EndArray()
	{
		if (flag) {
			throw std::logic_error("Node completed");
		}
		if (nodes_stack_.back()->IsDict()) {
			throw std::logic_error("It isn't dict");
		}
		Array array = std::get<Array>(nodes_stack_.back()->GetValueNotConst());
		if (nodes_stack_.size() == 1) {
			node_ = *(nodes_stack_.back());
			flag = true;
			
			return BaseContext(*this);
		}
		nodes_stack_.pop_back();
		if (nodes_stack_.back()->IsArray()) {
			std::get<Array>(nodes_stack_.back()->GetValueNotConst()).emplace_back(std::move(array));
		} else if (nodes_stack_.back()->IsDict()) {
			std::get<Dict>(nodes_stack_.back()->GetValueNotConst())[keys.back()] = std::move(array);
			keys.pop_back();
		}
		last_command = LastCommand::EndArray;
		
		return BaseContext(*this);
	}

	Node Builder::Build()
	{	
		if (!flag) {
			throw std::logic_error("Node not completed");
		}
		last_command = LastCommand::Build;
		return node_;
	}
}