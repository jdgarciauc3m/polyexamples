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
  cerr << "\t" << argv[0] << " infile outfile k" << endl;
  copy_n(argv, argc, ostream_iterator<std::string>{cout, " "});
}

std::tuple<std::string, std::string, int>
parse_args(int argc, const char ** argv) {
  using namespace std;
  if (argc != 4) {
    print_error("Wrong format", argc, argv);
    exit(-1);
  }
  
  try {
    int k = stoi(argv[3]);
    return make_tuple(argv[1], argv[2], k);
  }
  catch (...) {
    print_error("Wrong numeric argument",argc,argv);
    exit(-1);
  }
}

void resize_scene(const std::string & inname, const std::string & outname,
                  int factor)
{
  using namespace std;
  using namespace dsl;

  cout << "Reading file " << inname << endl;

  scene<rectangle> s;
  ifstream in{inname};
  in >> s;
  if (!in) throw std::runtime_error{"Error reading scene file:" + inname};

  s.resize_shapes(factor);

  ofstream out{outname};
  out << s;
  if (!out) throw std::runtime_error{"Error writing scene file:" + outname};

  cout << s.size() << " shapes written to file " << outname << endl;
}

int main(int argc, const char ** argv) {
  using namespace std;

  auto arg = parse_args(argc,argv); 

  try {
    resize_scene(get<0>(arg), get<1>(arg), get<2>(arg));
  }
  catch (exception & e) {
    cerr << e.what() << endl;
    return -1;
  }

  return 0;
}
