#include "rectangle.h"
#include "scene.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <tuple>
#include <random>
#include <chrono>

void print_error(std::string msg, int argc, const char ** argv) {
  using namespace std;
  cerr << msg << endl;
  cerr << "\t" << argv[0] << " infile" << endl;
  copy_n(argv, argc, ostream_iterator<std::string>{cout, " "});
}

std::string
parse_args(int argc, const char ** argv) {
  using namespace std;
  if (argc != 2) {
    print_error("Wrong format", argc, argv);
    exit(-1);
  }

  return argv[1];
}

void print_area(const std::string & inname) {
  using namespace std;
  using namespace dsl;

  scene s;
  ifstream in{inname};
  in >> s;
  if (!in) throw runtime_error{"Error reading scene file"};

  using clk = chrono::high_resolution_clock;
  auto t1 = clk::now();
  auto a = s.area();
  auto t2 = clk::now();

  cout << a << endl;
  cout << "Time: " << chrono::duration_cast<chrono::microseconds>(t2-t1).count() << endl;
}

int main(int argc, const char ** argv) {
  using namespace std;

  auto fname = parse_args(argc,argv); 

  cout << "Reading gfile " << fname << endl;

  try { print_area(fname); }
  catch (exception & e) {
    cerr << e.what() << endl;
    return -1;
  }

  return 0;
}
