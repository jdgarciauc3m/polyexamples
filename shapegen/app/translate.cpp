#include "rectangle.h"
#include "scene.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <tuple>
#include <random>

void print_error(std::string msg, int argc, const char ** argv) {
  using namespace std;
  cerr << msg << endl;
  cerr << "\t" << argv[0] << " infile outfile dx dy" << endl;
  copy_n(argv, argc, ostream_iterator<std::string>{cout, " "});
}

std::tuple<std::string, std::string, int, int>
parse_args(int argc, const char ** argv) {
  using namespace std;
  if (argc != 5) {
    print_error("Wrong format", argc, argv);
    exit(-1);
  }
  
  try {
    int dx = stoi(argv[3]);
    int dy = stoi(argv[4]);
    return make_tuple(argv[1], argv[2], dx, dy);
  }
  catch (...) {
    print_error("Wrong numeric argument",argc,argv);
    exit(-1);
  }
}

void translate_scene(const std::string & inname, const std::string & outname, 
                int dx, int dy) {
  using namespace std;
  using namespace dsl;

  cout << "Reading gfile " << inname << endl;

  scene<rectangle> s;
  ifstream in{inname};
  in >> s;
  if (!in) throw runtime_error{"Error reading scene file: " + inname};

  s.translate(dx,dy);

  ofstream out{outname};
  out << s;
  if (!out) throw runtime_error{"Error writing scene file" + outname};

  cout << s.size() << " shapes written to file " << outname << endl;
}

int main(int argc, const char ** argv) {
  using namespace std;

  auto arg = parse_args(argc,argv); 

  try { 
    translate_scene(get<0>(arg), get<1>(arg), get<2>(arg), get<3>(arg));
  }
  catch (const exception & e) {
    cerr << e.what() << endl;
    return -1;
  }

  return 0;
}
