#include"miniatur.h"

using std::ostream;
using std::istream;
using std::string;
using std::vector;

string to_s(Fraktion f){
  if(f==Fraktion::Tyraniden)
    return "Tyraniden";
  else if(f==Fraktion::SM)
    return "Space_Marines";
  else if(f==Fraktion::CSM)
    return "Chaos_Space_Marines";
  else if(f==Fraktion::Orks)
    return "Orks";
  else if(f==Fraktion::AstraMilitarum)
    return "Astra_Militarum";
  else if(f==Fraktion::GreyKnights)
    return "Grey_Knights";
  else if(f==Fraktion::Demons)
    return "Chaos_Demons";
  else if(f==Fraktion::Harlequins)
    return "Harlequins";
  else if(f==Fraktion::ThousandSons)
    return "Thousand_Sons";
  else if(f==Fraktion::AdeptusMechanicus)
    return "Adeptus_Mechanicus";
  else if(f==Fraktion::Craftworlds)
    return "Craftworlds";
  else if(f==Fraktion::Drukhari)
    return "Drukhari";
  else
    return "unbekannt";
}

Miniatur::Miniatur(string name,Fraktion f,int points):name{name},f{f},points{points}{
  if(name.empty() || points <= 0)
    throw std::runtime_error("Name leer oder weniger als einen Punkt");
}
bool Miniatur::change_points(int n) {
  if(points-n<=0)
    return false;
  points-=n;
  return true;
}
string Miniatur::get_name() const{
  return name;
}
Fraktion Miniatur::get_fraktion() const{
  return f;
}
int Miniatur::get_points() const{
  return points;
}

ostream& Miniatur::print(ostream& o) const{
  return o << "[Name: " << name << ", Fraktion: " << to_s(f) << ", Punkte: " << points << "]";
}

int Spezial_Miniatur::counter{0};

Spezial_Miniatur::Spezial_Miniatur(string name,Fraktion f,int points):Miniatur(name,f,points),nr{++counter} {}

ostream& Spezial_Miniatur::print(ostream& o) const {
  Miniatur::print(o);
  return o << ", *Nr: " << nr << '*';
}

std::ostream& operator<<(std::ostream& o,const Miniatur& s){
  return s.print(o);
}
std::ostream& operator<<(std::ostream& o,const Spezial_Miniatur& s){
  return s.print(o);
}
