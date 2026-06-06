//§ Requisites
  //§ Includes
    #include <cstddef>
    #include <initializer_list>
    #include <memory>
    #include <type_traits>
    #include <utility>
    #include <iostream>
    #include <string>
    #include <vector>
    #include <array>
    #include <cassert>
    #include <dirent.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <cstdlib>
    #include <cerrno>
    #include <variant>
    #include <map>
    #include <functional>
  //.
  //§ Helpers
    //§ Aliases
      #define is ==
      using namespace std;
      const string PROC         = "/proc";
      using st                  = size_t;
      using sst                 = ssize_t;
      template <st size> struct EntryWrapper;
      using strs                = vector<string>;
      using List                = vector<st>;
      using Record              = map<st, List>;                                      template <st amount>
      using RecursiveCollection = vector<unique_ptr<EntryWrapper<amount>>>;           template <st amount>
      using ValueType           = variant<st, string, RecursiveCollection<amount>>;   template <st amount>
      using Keys                = array<string, amount>;                              template <st amount>
      using Entry               = array<ValueType<amount>, amount>;                   template <st amount>
      using Collection          = vector<Entry<amount>>;
      #define DECLARE_ALIASES \
        constexpr auto keyAmount = data.fieldNames.size(); \
        using Value    = ValueType<keyAmount>; \
        using Wrapper  = EntryWrapper<keyAmount>; \
        using EntryPtr = unique_ptr<Wrapper>; \
        using func     = function<vector<EntryPtr>(const st &, vector<EntryPtr>)>;
    //.
    //§ Structs
      template <st size>
      struct EntryWrapper {
        Entry<size> values;
      };
      template <st size>
      struct Data {
        Keys<size>       fieldNames;
        Collection<size> fieldValues;

        template <typename ...Keys> requires(is_convertible_v<Keys, string> and ...)
        explicit Data(Keys&& ...key) : fieldNames{std::forward<Keys>(key)...} {}
      };
    //.
    //§ Template Magic
      template <typename... Lambda>      struct ConstructCallable : Lambda... { using Lambda::operator()...;  };
      template <typename... Lambda>      ConstructCallable(Lambda...) -> ConstructCallable<Lambda...>;
      template <typename ...KeyAmount>   Data(KeyAmount&& ...) -> Data<sizeof...(KeyAmount)>;
      template <typename T>              struct UNHANDLED_TYPE;
      // template <typename ExistingSize>   Data<ExistingSize> -> ValueType<ExistingSize>;
    //.
    //§ Functions
      auto is_number(const string &str) {
        for (const auto &c : str) 
          if (!isdigit(c)) return false;
        return true;
      }
      auto escape(const string& str) {
        string final;
        for (const auto& c : str) {
          switch (c) {
            break; case '"' : final += "\\\"";
            break; case '\\': final += "\\\\";
            break; case '\b': final += "\\b";
            break; case '\f': final += "\\f";
            break; case '\n': final += "\\n";
            break; case '\r': final += "\\r";
            break; case '\t': final += "\\t";
            break; default  : final += c;
          }
        }
        return final;
      }
      auto read_from(const string &path, const int fileDescriptor = -1) {
        char data[4096]; sst amountWritten = ((fileDescriptor < 0) ? readlink(path.c_str(), data, (sizeof(data) - 1)) : read(fileDescriptor, data, (sizeof(data) - 1)));
        return ((amountWritten is -1) ? string() : ((data[amountWritten] = '\0'), string(data, static_cast<st>(amountWritten))));
      }
      auto name_of (const st &pid) {
        const auto path = PROC + "/" + to_string(pid) + "/stat";
        string content; int fileDescriptor = -1; st start = string::npos, end = start;

        fileDescriptor = open(path.c_str(), O_RDONLY);    if (fileDescriptor is -1)  return string();
        content        = read_from(path, fileDescriptor); if (content is string())   return string();
        start          = content.find('(');        if (start is string::npos) return string();
        end            = content.rfind(')');        if (end is string::npos)  return string();
        content        = content.substr(start + 1, end - start - 1);

        return close(fileDescriptor), content;
      }
      auto parent_of (const st &pid) {
        const auto path = PROC + "/" + to_string(pid) + "/stat";
        string content, buffer; int fileDescriptor = -1; st count = 0, answer = 0;

        fileDescriptor = open(path.c_str(), O_RDONLY);    if (fileDescriptor is -1)  return answer; 
        content        = read_from(path, fileDescriptor); if (content is string())   return answer; 
        for (const auto &token : content) {
          if      (token is ' ') ++count;
          else if (count == 3)   buffer += token;
          if      (count > 3)    break;
        }
        try { answer = stoul(buffer); }
        catch (...) { return answer; }
        return close(fileDescriptor), answer;
      }
      template <st amount>
      auto outputEntry(const Keys<amount> &fields, const Entry<amount> &entry, string &accumulateOutput, bool firstChild = true) -> remove_cvref_t<decltype(accumulateOutput)> {
        accumulateOutput += string((firstChild ? "" : ",")) + "{"; bool firstField = true;

        for (st index = 0; index < amount; ++index) {
          accumulateOutput += (firstField ? "" : ",")
                           + string("\"") + fields.at(index) + string("\"") + ":"
                           + visit(ConstructCallable {
                              [&](const st                            &number) { return to_string(number);            },
                              [&](const string                        &string) { return "\"" + escape(string) + "\""; },
                              [&](const RecursiveCollection<amount>   &array)  {
                                string buffer = "[";

                                for (const auto &entry : array) {
                                  string content;

                                  buffer += outputEntry(fields, entry->values, content, ((entry is (*array.begin())) ? true : false));
                                } 
                                return buffer + "]";
                               },
                              [&](const auto                          &ERROR)  {
                                [[maybe_unused]] UNHANDLED_TYPE<remove_cvref_t<decltype(ERROR)>> TRIGGER_OUTPUT;
                               }
                             }, entry.at(index));
          if (firstField) firstField = false;
        }
        return accumulateOutput += "}";
      }
      void output(const auto &data) {
        cout << "["; bool firstObject = true;

        for (const auto &entry : data.fieldValues) {
          string buffer;

          cout << (firstObject ? "" : ",") 
               << outputEntry(data.fieldNames, entry, buffer);
          if (firstObject) firstObject = false;
        } 
        cout << "]";
      }
    //.
  //.
//.

int main () {
  DIR *dir = opendir(PROC.c_str()); if (!dir) return 1;
  struct dirent *ent; Data data("pid", "name", "children"); Record family; DECLARE_ALIASES
  const func populateChildren = [&](const auto &parent_id, auto collected) {
  if (!family.contains(parent_id)) return collected;
  
  const auto &children_of_process = family.at(parent_id);

    for (const auto &child_id : children_of_process)
      collected.push_back(
        make_unique<Wrapper>(
          Entry<keyAmount> {
            Value { child_id },
            Value { name_of(child_id) },
            Value { populateChildren(child_id, {}) }
          }
        )
      );
     return collected;
  };

  while (!(errno = 0) and (ent = readdir(dir)) and !errno)
    if (const auto &process_id = ent->d_name; ent->d_type is DT_DIR and is_number(process_id)) {
      st child_id = 0; try { child_id = stoul(process_id); } catch (...) { return EXIT_FAILURE; }

      family[parent_of(child_id)].emplace_back(child_id);
    }

  for (const auto &[parent_id, collection_of_children_ids] : family)
    if (parent_id and !parent_of(parent_id))
      data.fieldValues.emplace_back(
          Entry<keyAmount> {
            Value{ parent_id },
            Value{ name_of(parent_id) },
            Value{ populateChildren(parent_id, {}) }
          }
      );
     
  return output(data), abs(closedir(dir));
}