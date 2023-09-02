# pragma once
#include "json.h"

namespace json {
	class BaseContext;
	class DictItemContext;
	class ArrayItemContext;
	class KeyItemContext;
	class Builder;

	enum class LastCommand {
		Start,
		Key,
		Value,
		StartDict,
		StartArray,
		EndDict,
		EndArray,
		Build		
	};

	class BaseContext {
	public:
		BaseContext(Builder& builder);

		KeyItemContext Key(std::string&& str);

		BaseContext Value(Node::Value&& value);

		DictItemContext StartDict();

		ArrayItemContext StartArray();

		BaseContext EndDict();

		BaseContext EndArray();

		Node Build();
	
		Builder& builder_;
	};

	class DictItemContext :public BaseContext{
	public:
		DictItemContext(BaseContext base_context);

		BaseContext Value(Node::Value&& value) = delete;

		DictItemContext StartDict() = delete;

		ArrayItemContext StartArray() = delete;

		BaseContext EndArray() = delete;

		Node Build() = delete;
	};

	class KeyItemContext :public BaseContext {
	public:
		KeyItemContext(BaseContext base_context);

		DictItemContext Value(Node::Value&& value);

		KeyItemContext Key(std::string&& str) = delete;

		BaseContext EndDict() = delete;

		BaseContext EndArray() = delete;

		Node Build() = delete;
	};

	class ArrayItemContext :public BaseContext {
	public:
		ArrayItemContext(BaseContext base_context);

		KeyItemContext Key(std::string&& str) = delete;

		ArrayItemContext Value(Node::Value&& value);

		BaseContext EndDict() = delete;

		Node Build() = delete;

	};

	class Builder {

	public:
		KeyItemContext Key(std::string&& str);

		BaseContext Value(Node::Value&& value);

		DictItemContext StartDict();

		ArrayItemContext StartArray();

		Builder& EndDict();

		Builder& EndArray();

		Node Build();


	private:
		LastCommand last_command = LastCommand::Start;
		bool flag = false;
		Node node_;
		std::vector<Node*> nodes_stack_;
		std::vector<std::string> keys;
	};
}//namespace json