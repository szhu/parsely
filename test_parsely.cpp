#import "parsely.cpp"

void test_pos_identifiers(const char* filename) {
  parsely::FileParser parser(filename);
  std::cout << "Here's how I would indicate where an parsing error occurred, for each token:" << std::endl;
  while (parser.advance_line()) {
    while (parser.next_token()) {
      std::cout << std::endl << "an error occurred "<< parser.here("(additional info)");
    }
    std::cout << std::endl << "an error occurred "<< parser.here("(additional info)");
  }
  std::cout << std::endl;
}

void test_split_token(const char* filename) {
  parsely::FileParser parser(filename);
  std::cout << "Here are all the tokens at their original locations, one per line:" << std::endl << std::endl;
  while (parser.advance_line()) {
    while (parser.next_token()) {
      std::cout << parser.lineno << ": " << parser.zfill_to_colno() << parser.token << std::endl;
    }
  }
  std::cout << std::endl;
}

int main(int argc, const char *argv[]) {
  if (argc <= 1) {
    std::cerr << "usage: " << argv[0] << " filename" << std::endl;
    return 1;
  }
  test_split_token(argv[1]);
  std::cout << std::endl << std::endl;
  test_pos_identifiers(argv[1]);
  return 0;
}
