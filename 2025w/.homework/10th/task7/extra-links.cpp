#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <optional>

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
    Link& setNext(Link& l) {
      nextValue = &l;
      return l; // return *this;
    }
    optional<Link*> isALoop() const {
      if (!nextValue) return nullopt;
      Link *slow = nextValue, 
           *fast = nextValue;
      while (fast && fast->getPointer()) {
        slow = slow->getPointer();
        fast = fast->getPointer()->getPointer();
        if (slow == fast) return slow;
      }
      return nullopt;
    }
};
ostream& operator<<(ostream& o, const Link& l) {
  o << l.getValue(); Link* current = l.getPointer(); optional<Link*> loop = l.isALoop(); bool first = true;
  while (current) { 
    bool               condition = (!first && loop && current == *loop);

    if (!condition)    o << " --> " << current->getValue();
    if (condition)     return o << "\n❌ Last Entry Created A Loop, Exiting Output";
    else               current = current->getPointer();
                       first = false;
  }
  return o;
}

int main (int argc, char** args) { if (argc > 2) return 1;
  unsigned amountOfLinks = 5; vector<Link> nodes;
  if (argc == 2) try {
    amountOfLinks = stoi(string(args[1]));
  } catch (...) { cerr << "Using Default Value: " << amountOfLinks << endl; }

                                                    nodes.reserve(amountOfLinks + 1);
  for (size_t i = 0; i < amountOfLinks; ++i)        nodes.emplace_back(getRandom());
  for (size_t i = 0; i < (amountOfLinks - 1); ++i)  nodes.at(i).setNext(nodes.at(i + 1));
  auto& start = nodes.at(0);

  cout << nodes.at(amountOfLinks - 1).setNext(start) << endl;
	return 0;
}