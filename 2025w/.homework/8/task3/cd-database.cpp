#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <map>

using namespace std;
namespace fs = filesystem;

const string FILE_TITLE = "collection.txt";
const string ERROR_MESSAGE = "💥 ERROR: ";
const size_t SMALL_DISTANCE = 30;
const size_t MEDIUM_DISTANCE = 2 * SMALL_DISTANCE;

void wait() {
  cin.get(); cin.get();
}

enum class Options { ADD = 1, REMOVE, EDIT, SEARCH, EXIT };
map<Options, string> userOptions {
  { Options::ADD, "Add Entry" },
  { Options::REMOVE, "Remove Entry" },
  { Options::EDIT, "Edit Entries" },
  { Options::SEARCH, "Search Collection" }, 
  { Options::EXIT, "Exit" }
};

class Album {
  private:
    static unsigned nextID;
    const unsigned ID;
  public:
    string title, artist, style;
    Album(const string& title, const string& artist,const string& style) : ID(nextID++) {
      if      (title.empty())       throw runtime_error("Title Cannot Be Empty");
      else if (artist.empty())      throw runtime_error("Artist Cannot Be Empty");
      else if (style.empty())       throw runtime_error("Style Cannot Be Empty");
      else this->title = title, this->artist = artist, this->style = style;
    };
    unsigned getID() const { 
      return ID;
     }
}; unsigned Album::nextID = 1;
class Collection {
  private:
    const fs::path CONFIG = FILE_TITLE;
    bool saveConfig() {
      ofstream data(CONFIG.string(), ios::trunc); 
      if (!data.is_open()) { cerr << ERROR_MESSAGE << "Failed To Open File" << endl; return false; }
      data << "--START--" << endl;
      for (const auto& albums : library)
      data << albums.getID() << " | "
           << albums.title << " | "
           << albums.artist << " | "
           << albums.style << " |" << endl;
      data << "--END--" << endl;
      return true;
    }
    bool loadConfig() { if (!fs::exists(CONFIG)) return false;
      ifstream data(CONFIG.string()); string temp;
      if (!data.is_open()) { cerr << ERROR_MESSAGE << "Failed To Open File" << endl; return false; }
      while (getline(data, temp)) {
        if (temp == "--START--") continue;
        if (temp == "--END--") break;
        try { library.push_back([&]{
          string title, artist, style; size_t inputType = 0;
          // clog << "Current Line: \"" << temp << "\"" << endl;
          temp = temp.substr(temp.find("|") + 1);
          // clog << "Processing: \"" << temp << "\"" << endl;
          for (const auto& c : temp) {
            if (c == '|') {
              // clog << "Delimiter Encountered: '|' Skipping + Collecting Next Album Info" << endl;
              if (inputType % 3 == 0) { 
                // clog << "Cleaning Up String" << endl << "Original: \"" << title << "\"" << endl;
                // clog << "Removing Trailing Whitespace: ";
                title.pop_back();
                // clog << "\"" << title << "\"" << endl;
                // clog << "Removing Leading Whitespace: ";
                title.erase(title.begin(), title.begin() + 1);
                // clog << "Final Form: " << "\"" << title << "\"" << endl << endl;
              }
              if (inputType % 3 == 1) { 
                // clog << "Cleaning Up String" << endl << "Original: \"" << artist << "\"" << endl;
                // clog << "Removing Trailing Whitespace: ";
                artist.pop_back();
                // clog << "\"" << artist << "\"" << endl;
                // clog << "Removing Trailing Whitespace: ";
                artist.erase(artist.begin(), artist.begin() + 1);
                // clog << "Final Form: " << "\"" << artist << "\"" << endl << endl;
              }
              if (inputType % 3 == 2) { 
                // clog << "Cleaning Up String" << endl << "Original: \"" << style << "\"" << endl;
                // clog << "Removing Trailing Whitespace: ";
                style.pop_back();
                // clog << "\"" << style << "\"" << endl;
                // clog << "Removing Trailing Whitespace: ";
                style.erase(style.begin(), style.begin() + 1);
                // clog << "Final Form: " << "\"" << style << "\"" << endl << endl;
              }
              ++inputType; continue;
            }
            switch (inputType % 3) {
              case 0:
                title += c;
                // clog << "Adding '" << c << "'" << " | Current String: \"" << title << "\"" << endl;
              break;
              case 1:
                artist += c;
                // clog << "Adding '" << c << "'" << " | Current String: \"" << artist << "\"" << endl;
              break;
              case 2:
                style += c;
                // clog << "Adding '" << c << "'" << " | Current String: \"" << style << "\"" << endl;
              break;
              default:
                cerr << ERROR_MESSAGE << "Invalid Config File Layout" << endl;
                return Album{"", "", ""};
            }
          }
          // clog << "Pushing: " << endl
          //     << "- Title: \"" << title << "\"" << endl
          //     << "- Artist: \"" << artist << "\"" << endl
          //     << "- Style: \"" << style << "\"" << endl;
          return Album{title, artist, style};
        }()); }
        catch (const runtime_error& e) { cerr << ERROR_MESSAGE << e.what() << endl; wait(); }
      }
      for (const auto& album : library)
      if (album.title == ERROR_MESSAGE ||
        album.artist == ERROR_MESSAGE ||
        album.style == ERROR_MESSAGE) return false;
        return true;
      }
    public:
      vector<Album> library;
      Collection() {
                              cout << "👀 Looking For Database File At " << CONFIG << endl;
        if (!loadConfig())    cout << "❌ No Collection Found" << endl;
        else                  cout << "✅ Collection Found, Loading ..." << endl;
      }
      ~Collection() {
                           cout << "🌀 Attempting To Save Changes" << endl;
        if (!saveConfig()) cerr << ERROR_MESSAGE << "Failed Save Updates" << endl;
        else               cout << "✅ Changes Saved" << endl;
      }
    };
    
ostream& operator<< (ostream& o, const Album& a) {
  o << left << setw(SMALL_DISTANCE) << a.getID();
  o << left << setw(MEDIUM_DISTANCE) << a.title;
  o << left << setw(MEDIUM_DISTANCE) << a.artist;
  o << left << setw(MEDIUM_DISTANCE) << a.style;
  return o;
}
ostream& operator<< (ostream& o, const Collection& c) {
  o << endl << right << setw(1.5 * MEDIUM_DISTANCE) << "Displaying Collection" << endl << endl;
  o << left << setw(SMALL_DISTANCE) << "ID";
  o << left << setw(MEDIUM_DISTANCE) << "Title:";
  o << left << setw(MEDIUM_DISTANCE) << "Artist:";
  o << left << setw(MEDIUM_DISTANCE) << "Style:" << endl << endl;
  for (const auto& album : c.library) o << album << endl;
  return o;
}

int main() {
  Collection collection; auto& library = collection.library;
  string temp; bool exitLoop = false;
  do {
    if (!library.empty()) cout << collection << endl;
    else                             cout << endl << "∅ Collection Empty\n" << endl;
    cout << "Choose Option: \n" << endl;
    for (size_t i = static_cast<size_t>(Options::ADD); i <= static_cast<size_t>(Options::EXIT); ++i)
      cout << "[ " << i << " ] " << userOptions.at(static_cast<Options>(i)) << endl;
    cout << "\n ➡︎ Choice: "; cin >> temp;
    try { switch (static_cast<Options>(stoi(temp))) {
      case Options::ADD: {
        string title, artist, style;
        cout << "Insert New Entry: " << endl
             << "- Title: "; cin.ignore(); getline(cin, title);
        cout << "- Artist: "; getline(cin, artist);
        cout << "- Style: "; getline(cin, style);
        try { library.push_back({title, artist, style}); }
        catch (const runtime_error& e) { cerr << ERROR_MESSAGE << e.what() << endl; wait(); }
      break; }
      case Options::REMOVE: {
        string temp;
        if (library.empty()) { cerr << ERROR_MESSAGE << "Cannot Delete Since Collection Is Empty" << endl; wait(); break; }
        cout << collection << endl; cout << "Select ID of a CD to Remove: "; cin >> temp;
        try {
          unsigned index = stoul(temp); vector<Album> replacement; bool found = false;
          for (const auto& album : library) {
            if (album.getID() == index) { found = true; continue; }
            replacement.push_back(album);
          }
          if (found) { library.swap(replacement); cout << "✅ Album With ID " << index << " Removed Successfully" << endl; }
          else cerr << ERROR_MESSAGE << "Album With ID " << index << " Not Found" << endl;
          wait();
        }
        catch (const runtime_error& e) { cerr << ERROR_MESSAGE << e.what() << endl;                             }
        catch (const invalid_argument& e) { cerr << ERROR_MESSAGE << "Invalid Input, Not A Number" << endl;     }
        catch (const out_of_range& e)     { cerr << ERROR_MESSAGE << "Invalid Input, Number Too Large" << endl; }
        break; }
      case Options::EDIT: {
        string temp, title, artist, style;
        if (library.empty()) { cerr << ERROR_MESSAGE << "Cannot Edit Since Collection Is Empty" << endl; wait(); break; }
        cout << collection << endl; cout << "Select ID of a CD to Edit: "; cin >> temp;
        try {
          unsigned index = stoul(temp); vector<Album> replacement; bool found = false, changedEntry = false, invalid = false;
          for (const auto& album : library) {
            if (album.getID() == index) { found = changedEntry = true;
              cout << "Insert New Entry: (Skip If No Changes)" << endl
                   << "Old Title: " << album.title << endl << "- New Title: "; cin.ignore(); getline(cin, title);
              cout << "Old Artist: " << album.artist << endl << "- New Artist: "; getline(cin, artist);
              cout << "Old Style: " << album.style << endl << "- New Style: "; getline(cin, style);
            }
            if (title.empty()) title = album.title;
            if (artist.empty()) artist = album.artist;
            if (style.empty()) style = album.style;
            try { replacement.push_back(((changedEntry) ? Album{title, artist, style} : album)); changedEntry = false; }
            catch (const runtime_error& e) { cerr << ERROR_MESSAGE << e.what() << endl; wait(); invalid = true; break; }
          }
          if (found && !invalid) { library.swap(replacement); cout << "✅ Album With ID " << index << " Edited Successfully" << endl; }
          else if (!invalid) cerr << ERROR_MESSAGE << "Album With ID " << index << " Not Found" << endl;
          wait();
        }
        catch (const invalid_argument& e) { cerr << ERROR_MESSAGE << "Invalid Input, Not A Number" << endl;     }
        catch (const out_of_range& e)     { cerr << ERROR_MESSAGE << "Invalid Input, Number Too Large" << endl; }
      break; }
      case Options::SEARCH: {
        string target; bool found = false;
        cout << "Insert Search String: "; cin.ignore(); getline(cin, target);
        cout << endl << "Search Target: \"" << target << "\"" << endl;
        transform(target.begin(), target.end(), target.begin(), ::tolower);
        for (const auto& album : library) {
          string title = album.title,
                 artist = album.artist,
                 style = album.style;
          transform(title.begin(), title.end(), title.begin(), ::tolower);
          transform(artist.begin(), artist.end(), artist.begin(), ::tolower);
          transform(style.begin(), style.end(), style.begin(), ::tolower);
          if (title.find(target) != string::npos || 
              artist.find(target) != string::npos || 
              style.find(target) != string::npos) {
                cout << "✅ Entry Found" << endl << album << endl;
                found = true; 
              }
        }
        if (!found) cout << ERROR_MESSAGE << "Entry Not Found" << endl;
        wait();
      break; }
      case Options::EXIT: {
        exitLoop = true;
      break; }
      default: {
        cerr << ERROR_MESSAGE << "Invalid Input, Not In Choice Range";
        wait();
      break; }
    } }
    catch (const invalid_argument& e) { cerr << ERROR_MESSAGE << "Invalid Input, Not A Number"; wait();     }
    catch (const out_of_range& e)     { cerr << ERROR_MESSAGE << "Invalid Input, Number Too Large"; wait(); }
  } while (!exitLoop);
  return 0;
}

