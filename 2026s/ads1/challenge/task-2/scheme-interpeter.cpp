//§ Requisites
  #include <cstddef>
  #include <exception>
  #include <iostream>
  #include <memory>
  #include <cctype>
  #include <string>
  #include <vector>
  #include <stdexcept>
  #include <format>
  #include <cassert>
  using namespace std;
//.

//* --- Abstract Syntax Tree ---
struct ExpressionNode {
    enum Type : unsigned char { NUMBER, OPERATOR, FUNCTION_APPLICATION }
                                       nodeType;
    int                                 number;
    char                                 name;
    shared_ptr<ExpressionNode>         functions;
    vector<shared_ptr<ExpressionNode>> arguments;
};

//* --- Pointer Constructors ---
  auto createNumber(const int &number) {
      auto ptr = make_shared<ExpressionNode>();
      ptr->nodeType = ExpressionNode::NUMBER;
      ptr->number   = number;
      return ptr;
  }
  auto createOperation(const char &operatorToSave) {
      auto ptr = make_shared<ExpressionNode>();
      ptr->nodeType = ExpressionNode::OPERATOR;
      ptr->name     = operatorToSave;
      return ptr;
  }
  auto applyOperation(const shared_ptr<ExpressionNode> &node, const vector<shared_ptr<ExpressionNode>> &arguments) {
      auto ptr = make_shared<ExpressionNode>();
      ptr->nodeType  = ExpressionNode::FUNCTION_APPLICATION;
      ptr->arguments = arguments;
      ptr->functions = node;
      return ptr;
  }
//.

//* --- Tokenizer ---
auto tokenizeString(const string &input) {
    vector<string> tokens;
    string         current;

    for (const auto &character : input) {
        if (isspace(character)) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        } else if (character == '(' || character == ')') {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
            tokens.emplace_back(1, character);
        } else {
            current += character;
        }
    } if (!current.empty()) tokens.push_back(current);

    return tokens;
}

//* --- Parser ---
shared_ptr<ExpressionNode> parseExpression(const vector<string> &tokens, size_t &position) { 
    if (position >= tokens.size()) throw runtime_error("Unexpected end of input");
    const string currentToken = tokens.at(position++);

    if (currentToken == "(") {
        vector<shared_ptr<ExpressionNode>> arguments;
        const auto operation = tokens.at(position++);

        while (position < tokens.size() && tokens.at(position) != ")") {
            arguments.push_back(parseExpression(tokens, position));
        }
        position++; //? why is this necesary

        assert(operation.size() == 1);
        return applyOperation(createOperation(operation.at(0)), arguments);
    }

    return createNumber(stoi(currentToken));
}

//* --- Evaluation ---
auto evaluateExpression(const shared_ptr<ExpressionNode> &node) {
    switch (node->nodeType) {
      case ExpressionNode::NUMBER:
          return node->number;
      case ExpressionNode::FUNCTION_APPLICATION: {  if (node->arguments.empty()) throw runtime_error("Expected at least 1 argument");
        const auto operationName = node->functions->name;
        int result = evaluateExpression(node->arguments.at(0));

        for (size_t i = 1, size = node->arguments.size(); i < size; ++i) {
            const auto value = evaluateExpression(node->arguments.at(i));
            switch (operationName) {
                break; case '+': result += value;
                break; case '-': result -= value;
                break; case '*': result *= value;
                break; case '/': if (value) result /= value;
                                 else throw runtime_error("Division by zero");
                break; default: throw runtime_error(format("Unsupported Operator Detected: {}", operationName));
            }
        }
        return result;
      }
      default: throw runtime_error("An Operator Without Arguments Is An Invalid Expression");
    }
}

//* --- Loop ---
int main() {
    string line;

    cout << "Micro Lisp. Type 'q' to quit.\n";
    while (true) {
        cout << ">> ";
        if (!getline(cin, line)) break;
        if ((line == "exit" || line == "q")) break;
        if (line.empty()) continue;

        try {
            size_t position = 0;
            // auto parsedTokens = tokenizeString(line);
            // auto currentNode = parseExpression(parsedTokens, position);
            // auto result = evaluateExpression(currentNode);

            // cout << result << "\n";
            cout << evaluateExpression(parseExpression(tokenizeString(line), position)) << endl;
        } catch (exception& error) {
            cout << "Error: " << error.what() << "\n";
        }
    }
}