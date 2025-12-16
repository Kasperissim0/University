#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

double getRandom(const double& min = -200, const double& max = 200) {
  random_device seed; mt19937 gen(seed()); uniform_real_distribution<double>distr(min, max);
  return distr(gen);
}
class Link {
    const double value;
    Link* nextValue;
  public:
    explicit Link(const double& value = getRandom()) : value{value}, nextValue{nullptr} {
    }
    const double& getValue() const {
      return this->value;
    }
    Link* getPointer() const {
      return this->nextValue;
    }
    Link& insert(Link& l) {
      nextValue = &l;
      return l; // return *this;
    }
};
ostream& operator<<(ostream& o, const Link& l) {
  o << l.getValue(); Link* current = l.getPointer();
  while (true) {
    if (current) {
      o << " --> " << current->getValue();
      current = current->getPointer();
    }
    else return o;
  }
}

int main (int argc, char** args) { if (argc > 2) return 1;
  unsigned amountOfLinks = 5; Link start; vector<Link> nodes;
  if (argc == 2) try {
    amountOfLinks = stoi(string(args[1]));
  } catch (...) { cerr << "Using Default Value: " << amountOfLinks << endl; }

                                                    nodes.reserve(amountOfLinks);
  for (size_t i = 0; i < amountOfLinks; ++i)        nodes.emplace_back(getRandom());
  for (size_t i = 0; i < (amountOfLinks - 1); ++i)  nodes.at(i).insert(nodes.at(i + 1));
  
  if (!nodes.empty())                               start.insert(nodes.at(0));
  else                                              throw runtime_error("Unable To Set Link Vector");
  
  cout << start << endl;

	return 0;
}