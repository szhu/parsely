#include <iostream>
#import "parsely.hpp"

namespace parsely {
FileParser::FileParser(const char* filename)
: lineno(0), colno(-1), filename(filename) {
  file.open(filename);
  if (!file.is_open()) {
    std::cerr << "error: cannot open file " << filename << std::endl;
    std::exit(1);
  }
}
bool FileParser::advance_line() {
  if (!std::getline(file, line_string)) return false;
  line.clear();
  line.str(line_string);
  line >> dummy_char; line.unget();
  lineno++;
  return true;
}

#define next_token_body { \
  colno = get_colno(); \
  bool status = bool(line >> token); \
  token_length = get_colno() - colno; \
  if (!status) return false; \
  line >> dummy_char; line.unget(); \
  return true; \
}
int FileParser::get_colno() {
  int colno = (int)line.tellg(); \
  return ((colno < 0) ? line_string.length() : colno) + 1; \
}

// next_token
bool FileParser::next_token() next_token_body;
bool FileParser::next_token(float& token) next_token_body;
bool FileParser::next_token(float& token, float min, float max) {
  if (!next_token(token)) return false;
  if (token < min || token > max) return false;
  return true;
}
bool FileParser::next_token(int& token) next_token_body;
bool FileParser::next_token_positive(int& token) {
  if (!next_token(token)) return false;
  if (token < 0) return false;
  return true;
}
bool FileParser::next_token(std::string& token) next_token_body;


// require_next_token
#define do_error(msg) { \
  std::cerr << "error: " << msg << " " << here(); \
  std::exit(1); \
}
std::string FileParser::require_next_token() {
  std::string token;
  if (next_token(token)) return token;
  do_error("expected a string");
}
void FileParser::require_next_token(std::string& token) {
  if (next_token(token)) return;
  do_error("expected a string");
}
void FileParser::require_next_token(int& token) {
  if (next_token(token)) return;
  do_error("expected a integer");
}
void FileParser::require_next_token_positive(int& token) {
  if (next_token_positive(token)) return;
  do_error("expected a positive integer");
}
void FileParser::require_next_token(float& token) {
  if (next_token(token)) return;
  do_error("expected a number");
}
void FileParser::require_next_token_positive(float& token) {
  if (next_token(token, 0, INF)) return;
  do_error("expected a positive number");
}
void FileParser::require_next_token_min(float& token, float min) {
  if (next_token(token, min, INF)) return;
  do_error("expected a number at least " << min);
}
void FileParser::require_next_token_max(float& token, float max) {
  if (next_token(token, -INF, max)) return;
  do_error("expected a number at most " << max);
}
void FileParser::require_next_token_minmax(float& token, float min, float max) {
  if (next_token(token, min, max)) return;
  do_error("expected a number between " << min << " and " << max);
}


std::string FileParser::pos_identifier() {
  std::ostringstream oss;
  oss << std::string(filename) << ':' << lineno << ':' << colno;
  return oss.str();
}
std::string FileParser::pos_indicator() {
  std::ostringstream oss;
  oss << line_string << std::endl << zfill_to_colno() << '^' << underline_token() << std::endl;
  return oss.str();
}
std::string FileParser::zfill_to_colno() {
  return std::string(colno-1, ' ');
}
std::string FileParser::underline_token() {
  if (token_length < 1)
    return std::string(" ");
  else
    return std::string(token_length-1, '~');
}
std::string FileParser::here() {
  std::ostringstream oss;
  oss << "at " << pos_identifier() << std::endl;
  oss << pos_indicator();
  return oss.str();
}
std::string FileParser::here(std::string msg) {
  std::ostringstream oss;
  oss << "at " << pos_identifier() << ": " << msg << std::endl;
  oss << pos_indicator();
  return oss.str();
}
}
