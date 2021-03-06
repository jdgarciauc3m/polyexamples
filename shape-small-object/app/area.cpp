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

int main(int argc, const char ** argv) {
  using namespace std;

  auto fname = parse_args(argc,argv); 

  cout << "Reading gfile " << fname << endl;

  dsl::scene s;
  ifstream in{fname};
  in >> s;
  if (!in) {
    cerr << "Error reading scene file" << endl;
    return -1;
  }

  using clk = chrono::high_resolution_clock;
  auto t1 = clk::now();
  auto a = s.area();
  auto t2 = clk::now();

  cout << a << endl;
  cout << "Time: " << chrono::duration_cast<chrono::microseconds>(t2-t1).count() << endl;

  return 0;
}
