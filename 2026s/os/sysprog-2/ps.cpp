//§ Requisites
  //§ Includes
    #include <algorithm>
    #include <cstddef>
    #include <iostream>
    #include <string>
    #include <vector>
    #include <tuple>
    #include <cassert>
    #include <dirent.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <stdlib.h>
    #include <errno.h>
  //.
  //§ Helpers
    //§ Aliases
      #define is ==
      using namespace std;
      using st              = size_t;
      using sst             = ssize_t;
      using strs            = vector<string>;
      using entry           = tuple<string, strs, bool, bool>;
      using process         = vector<entry>;
      using entries         = vector<process>;
      const string PROC = "/proc";
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
      auto state_of(const string &pid) {
        const string path = PROC + "/" + pid + "/stat"; string content, output; int fileDescriptor; st position = 0;

        fileDescriptor = open(path.c_str(), O_RDONLY);      if (fileDescriptor is -1)     return  output;
        content        = read_from(path, fileDescriptor);   if (content.empty())          return  output;
        position       = content.find_last_of(')');         if (position is string::npos) return  output;

        return close(fileDescriptor), output = content.at(position + 2);
      }
      auto adress_of(const string &pid) {
        const string path = PROC + "/" + pid + "/maps"; string content; int fileDescriptor; uintptr_t position = 0, answer = 0;

        fileDescriptor = open(path.c_str(), O_RDONLY);       if (fileDescriptor is -1)     return string();
        content        = read_from(path, fileDescriptor);    if (content.empty())          return string();
        position       = content.find('-');               if (position is string::npos) return string();
        content        = content.substr(0, position); st digitPlace = 0;
        for_each(content.rbegin(), content.rend(), [&](const auto& value) {
          assert((value >= '0' and value <= '9') or (value >= 'a' and value <= 'f'));
          const st digit = static_cast<st>((value - ((value <= '9') ? '0' : 'W')));
          answer += digit << (4 * digitPlace++);
        });
        return close(fileDescriptor), to_string(answer);
      }
      auto args_of(const string &pid) {
        const string path = PROC + "/" + pid + "/cmdline"; string content, buffer; strs output; int fileDescriptor = -1;

        fileDescriptor = open(path.c_str(), O_RDONLY);      if (fileDescriptor is -1)     return  output;
        content        = read_from(path, fileDescriptor);   if (content.empty())          return  output;
        for (const auto& token : content) {
          if (token is '\0' and !buffer.empty()) output.push_back(buffer), buffer.clear();
          else buffer += token;
        }
        return close(fileDescriptor), output;
      }
      void output(const entries &data) { bool first = true; cout << "[";
        for (const auto& entry : data) {
          bool first1 = true; cout << (first ? "" : ",") << "{";
          for (const auto &[key, value, num, array] : entry) { bool first2 = true;
            cout << (first1 ? "" : ",")
                << "\"" << key << "\"" << ":"
                << (!array ? ((!num ? ("\"" + escape(value.at(0)) + "\"") : value.at(0))) : 
                [&] { string output2 = "[";
                  for (const auto &entry : value) {
                    output2 += string(first2 ? "" : ",") + "\"" + escape(entry) + "\"";
                    if (first2) first2 = false;;
                  } return output2 += "]";
                }());
            if (first1) first1 = false;
          } if (first) first = false; cout << "}";
        } cout << "]";
      }
    //.
  //.
//.

int main () {
  DIR *dir = opendir(PROC.c_str()); if (!dir) return 1;
  struct dirent *ent; entries data;

  while (!(errno = 0) and (ent = readdir(dir)) and !errno)
    if (const auto &pid = ent->d_name; ent->d_type is DT_DIR and is_number(pid)) {
      const auto exe   =  read_from(PROC + "/" + pid + "/exe"),
                 cwd   =  read_from(PROC + "/" + pid + "/cwd"),
                 state =  state_of(pid);
      if (exe.empty() or cwd.empty() or state.empty()) continue;
      else data.insert(data.end(), { // may be wasteful since each process separately stores the key names (pid/exe etc.)
        entry{ "pid",         strs{pid},        true,  false },
        entry{ "exe",         strs{exe},        false, false },
        entry{ "cwd",         strs{cwd},        false, false },
        entry{ "base_address", strs{adress_of(pid)}, true,  false },
        entry{ "state",       strs{state},      false, false },
        entry{ "cmdline",     strs{args_of(pid)},   false, true  }
      });
    }
     
  return output(data), abs(closedir(dir));
}