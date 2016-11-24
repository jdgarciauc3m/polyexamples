#include "rectangle.h"
#include "scene.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <tuple>
#include <random>
#include <experimental/optional>

template <typename T>
using optional = std::experimental::optional<T>;

void print_error(std::string msg, int argc, const char ** argv) {
  using namespace std;
  cerr << msg << endl;
  cerr << "\t" << argv[0] << " outfile nshapes" << endl;
  copy_n(argv, argc, ostream_iterator<std::string>{cout, " "});
}

optional<std::tuple<std::string, int>> parse_args(int argc, const char ** argv) {
  using namespace std;
  if (argc != 3) {
    print_error("Wrong format", argc, argv);
    return {};
  }

  try { 
    int nelem = stoi(argv[2]); 
    return tuple<string,int>(string{argv[1]}, nelem);
  }
  catch (...) { 
    print_error("Wrong nshapes format", argc, argv);
    return {};
  }
}

template <typename G>
dsl::rectangle random_rectangle(G && g) {
  std::uniform_int_distribution<int> 
    gx{0,100}, gy{0,100}, gw{1,10}, gh{1,10};
  
  return {gx(g), gy(g), gw(g), gh(g)};
}

void generate_scene(const std::string & name, int n) {
  using namespace std;
  using namespace dsl;

  cout << "Writing file " << name << endl;
  cout << "sizeof(rectangle)= " << sizeof(dsl::rectangle) << endl;
  cout << "Generating " << n << " elements\n";

  random_device rd;
  scene<rectangle> s;
  for (int i=0; i<n; i++) {
    auto r = random_rectangle(rd);
    s.add_shape(r);
  }

  ofstream of{name};
  of << s << endl;
  if (!of) throw runtime_error{"Cannot write to file: " + name};

  cout << "Generated file " << name << " with " << n << " elements\n";
}

int main(int argc, const char ** argv) {
  using namespace std;

  auto r = parse_args(argc,argv); 
  if (!r) return -1;

  try { generate_scene(get<string>(*r), get<int>(*r)); }
  catch (exception & e) {
    cerr << e.what() << endl;
    return -1;
  }

  return 0;
}
