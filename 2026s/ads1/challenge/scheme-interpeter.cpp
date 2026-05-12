//§ Requisites
    //§ Includes
        #include <iostream>
        #include <string>
        #include <vector>
        #include <memory>
        #include <cstddef>
        #include <cstdlib>
        #include <exception>
        #include <stdexcept>
        #include <cctype>
        #include <format>
        #include <ranges>
    //.
    //§ Aliases
        using namespace std;
        using st = size_t;
        #define INTERACTIVE_MODE   n == 1
        #define EVALUATE_ONCE_MODE n == 2
        #define START_STRING       "("
        #define START_CHAR         '('
        #define END_STRING         ")"
        #define END_CHAR           ')'
        #define SPACE              ' '
        #define IF                 '?'
        #define BEGINNING           0
    //.
    //§ Helpers
      struct PositionTracker {
        st value;
        st& operator++() {
          // log contents (like debug lamda) on each increment
          return value;
        }
      };
    //.
//.

//* --- Abstract Syntax Tree ---
  // TODO refactor the construction functions into 1 thing
  // TODO add variables $ x 10
  struct ExpressionNode {
      enum Type : unsigned char { NUMBER, OPERATOR, FUNCTION_APPLICATION, CONDITIONAL }
                                      nodeType;
      int                                 number;
      char                                 name;
      shared_ptr<ExpressionNode>         functions, 
                                      test, thenBranch, elseBranch;
      vector<shared_ptr<ExpressionNode>> arguments;
  };
  // struct NumberNode : public ExpressionNode {
  //     int number;
  // };
  // struct OperationNode : public ExpressionNode {
  //     char name;
  // };
//.
//* --- Pointer Constructors ---
  // TODO refactor the construction functions into 1 thing
  //   auto constructExpression(const ExpressionNode::Type type) {
  //     auto ptr = make_shared<ExpressionNode>();
  //     switch (type) {

  //     }
  //     return ptr;
  //   }
  auto constructNumber(const int &number) {
      auto ptr = make_shared<ExpressionNode>();
      ptr->nodeType = ExpressionNode::NUMBER;
      ptr->number   = number;
      return ptr;
  }
  auto constructOperation(const char &operatorToSave) {
      auto ptr = make_shared<ExpressionNode>();
      ptr->nodeType = ExpressionNode::OPERATOR;
      ptr->name     = operatorToSave;
      return ptr;
  }
  auto constructFunction(const shared_ptr<ExpressionNode> &function, const vector<shared_ptr<ExpressionNode>> &arguments) {
      auto ptr = make_shared<ExpressionNode>();
      ptr->nodeType  = ExpressionNode::FUNCTION_APPLICATION;
      ptr->arguments = arguments;
      ptr->functions = function;
      return ptr;
  }
  auto constructIfStatement(const shared_ptr<ExpressionNode> &conditions, const shared_ptr<ExpressionNode> &ifTrue, const shared_ptr<ExpressionNode> &ifFalse) {
    auto ptr = make_shared<ExpressionNode>();
    ptr->nodeType   = ExpressionNode::CONDITIONAL;
    ptr->test       = conditions;
    ptr->thenBranch = ifTrue;
    ptr->elseBranch = ifFalse;
    return ptr;
  }
//.

//* --- Tokenizer ---
auto tokenizeString(const string &input) {
    vector<string> tokens; string current;
    const auto addToken = [&](){
      if (!current.empty()) {
        tokens.push_back(current);
        current.clear();
      }
    };

    for (const auto &character : input) {
      const bool isDelimeter = ((character == START_CHAR) or (character == END_CHAR)), isSpace = isspace(character);

      if (isDelimeter or isSpace) addToken();
      if (isDelimeter) tokens.emplace_back(1, character);
      else if (!isSpace) current += character;
    } return addToken(), tokens;
}

//* --- Parser ---
shared_ptr<ExpressionNode> parseExpression(const vector<string> &tokens, st &position) {
    const auto print = [&](const vector<string> vec) {
        string list = "{ ";
        for (const auto& str : vec)
            list += format("\"{}\" ", str);
        return list += "}";
    }; const auto debug = [&](){
        const auto msg = format("Parsing Element #{}: ", position),
                   padding = string(7 + msg.size() + (4 * (((position - ((position == 1) ? 0 : 1))))), SPACE);
        clog << msg << print(tokens) << endl << padding << "∧" << endl << padding << "|" << endl;
      }; debug();
    if (position >= tokens.size()) throw runtime_error("Unexpected end of input");
    const auto &currentToken = tokens.at(position++);
    

    if (currentToken == START_STRING) {
        vector<shared_ptr<ExpressionNode>> arguments;
        if (position >= tokens.size()) throw runtime_error("Expected operator after '('");
        if (tokens.at(position).size() != 1) throw runtime_error(format("Unsupported Operator Detected: {}", tokens.at(position)));
        const auto &operation = tokens.at(position++).front();

        if (operation == IF) {
            const auto conditions = parseExpression(tokens, position),
                       thenBranch = parseExpression(tokens, position),
                       elseBranch = parseExpression(tokens, position);
            if (tokens.at(position++) != END_STRING) throw runtime_error("Expected Closing Brace After If");
            return constructIfStatement(conditions, thenBranch, elseBranch);
        }
        while (position < tokens.size() and tokens.at(position) != END_STRING) {
            arguments.push_back(parseExpression(tokens, position));
        } if (position >= tokens.size()) throw runtime_error("Expected closing ')'"); position++;
        return constructFunction(constructOperation(operation), arguments);
    }

    return constructNumber(stoi(currentToken));
}

//* --- Evaluation ---
auto evaluateExpression(const shared_ptr<ExpressionNode> &expression) {
    switch (expression->nodeType) {
      case ExpressionNode::NUMBER:
          return expression->number;
      case ExpressionNode::CONDITIONAL: {
        // TODO add recrusive evaluation of & | ^ logic operators
        return evaluateExpression((evaluateExpression(expression->test) ? expression->thenBranch : expression->elseBranch));
      }
      case ExpressionNode::FUNCTION_APPLICATION: {  if (expression->arguments.empty()) throw runtime_error("Expected at least 1 argument");
        const auto &operationName = expression->functions->name; int result = 0;

        switch (operationName) { // Handle Unary Operations
          break; case '!': return static_cast<int>(!static_cast<bool>(evaluateExpression(expression->arguments.at(BEGINNING))));
          break; case '-': if (expression->arguments.size() == 1) return (-(evaluateExpression(expression->arguments.at(BEGINNING))));
          break; case '#': return (abs(evaluateExpression(expression->arguments.at(BEGINNING))));
          // break; default : throw runtime_error(format("Unsupported Operator Detected: {}", operationName));
        } result = evaluateExpression(expression->arguments.at(BEGINNING));
        for (const auto &subExpression : expression->arguments | views::drop(1)) {
            const auto value = evaluateExpression(subExpression);

            switch (operationName) { // Handle n-ary (n ≥ 2) Operations
                break; case '>':            result = static_cast<int>(result > value);
                break; case '<':            result = static_cast<int>(result < value);
                break; case '&':            result = static_cast<int>(static_cast<bool>(result) and static_cast<bool>(value));
                break; case '|':            result = static_cast<int>(static_cast<bool>(result) or  static_cast<bool>(value));
                break; case '^':            result = static_cast<int>(static_cast<bool>(result) xor static_cast<bool>(value));
                break; case '%':            result %= value;
                break; case '+':            result += value;
                break; case '-':            result -= value;
                break; case '*':            result *= value;
                break; case '/': if (value) result /= value;
                                 else       throw runtime_error("Division by zero");
                break; default :            throw runtime_error(format("Unsupported Operator Detected: {}", operationName));
            }
        }
        return result;
      }
      default: throw runtime_error("An Operator Without Arguments Is An Invalid Expression");
    }
}

//* --- Loop ---
    int main(int n, char** args) {
        st position = BEGINNING; string input;
        
        if (INTERACTIVE_MODE) {
            const auto explain = [&](){ 
                cout << "Micro Lisp. Type 'q' to quit." << endl;
            }; explain();

            while (cout << ">> " and getline(cin, input)) {
                if (input == "exit" or input == "q")   return EXIT_SUCCESS;
                if (input == "?" or input == "help")   explain(), input.clear();
                if (input.empty())                     continue;

                try {
                    position = BEGINNING;
                    cout << evaluateExpression(parseExpression(tokenizeString(input), position)) << endl;
                } catch (exception& error) {
                    cout << "Error: " << error.what() << "\n";
                }
            }
        }
        if (EVALUATE_ONCE_MODE) {
            try {
                    input = args[1];
                    cout << evaluateExpression(parseExpression(tokenizeString(input), position)) << endl;
                    return EXIT_SUCCESS;
                } catch (exception& error) {
                    cout << "Error: " << error.what() << "\n";
                }
        }
        return EXIT_FAILURE;
    }
//.