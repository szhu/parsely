#include <iostream>
#include <cctype>
#import "parsely.hpp"

namespace parsely {
FileParser::FileParser(const char* filename)
: lineno(0), colno(-1), filename(filename), line_string(""), token_length(0), line_length(0) {
  file.open(filename);
  if (!file.is_open()) {
    std::cerr << "error: cannot open file " << filename << std::endl;
    std::exit(1);
  }
}


// Getting info

int FileParser::get_colno() {
  int colno = (int)line.tellg();
  return ((colno < 0) ? line_string.length() : colno) + 1;
}
int FileParser::get_line_length() {
  // if (line_string.find_last_of('\r') != std::string::npos)
  //   return line_string.length() - 1;
  // else
    return line_string.length();
}
bool FileParser::line_empty() {
  return (int)line.tellg() == -1;
}


// Getting the next thing

// advance_line
bool FileParser::advance_line() {
  if (!std::getline(file, line_string)) {
    colno = 1;
    lineno++;
    return false;
  }
  line_string.erase(line_string.find_last_not_of('\r') + 1);  // Ignore CR in CRLF
  line_length = get_line_length();
  line.clear();
  line.str(line_string);
  char dummy_char;
  line >> dummy_char; line.unget();
  lineno++;
  return true;
}
bool FileParser::advance_lines() {
  while (true) {
    if (!advance_line()) return false;
    if (!line_empty()) return true;
  }
}

// next_token
#define next_token_body { \
  colno = get_colno(); \
  bool status = (bool)(line >> token); \
  token_length = get_colno() - colno; \
  if (token_length > line_length) token_length = line_length; \
  if (!status) return false; \
  char dummy_char; \
  line >> dummy_char; line.unget(); \
  return true; \
}
bool FileParser::next_token() next_token_body;
bool FileParser::next_token(float& token) next_token_body;
bool FileParser::next_token(float& token, float min, float max) {
  if (!next_token(token)) return false;
  if (token < min || token > max) return false;
  return true;
}
bool FileParser::next_token(int& token) next_token_body;
bool FileParser::next_token(int& token, int min, int max) {
  if (!next_token(token)) return false;
  if (token < min || token > max) return false;
  return true;
}
bool FileParser::next_token(std::string& token) next_token_body;


// require_advance_line/require_next_token
#define require_error { \
  std::cerr << "error: expected " << what << " " << here(); \
  std::exit(1); \
}
void FileParser::require_advance_line(char what[]) {
  if (!advance_line()) require_error;
}
void FileParser::require_advance_line() {
  char what[] = "new line";
  if (!advance_line()) require_error;
}
std::string FileParser::require_next_token(char what[]) {
  std::string token;
  if (!next_token(token)) require_error;
  return token;
}
void FileParser::require_next_token(std::string& token, char what[]) {
  if (!next_token(token)) require_error;
}
void FileParser::require_next_token(int& token, char what[]) {
  if (!next_token(token)) require_error;
}
void FileParser::require_next_token(float& token, char what[]) {
  if (!next_token(token)) require_error;
}
void FileParser::require_next_token(int& token, int min, int max, char what[]) {
  if (!next_token(token, min, max)) require_error;
}
void FileParser::require_next_token(float& token, float min, float max, char what[]) {
  if (!next_token(token, min, max)) require_error;
}


// Displaying info

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
  char zfill[colno];
  char* zfill_cursor = zfill;
  std::string::iterator iter = line_string.begin();
  for (int i = 0; i < colno - 1; ++i, ++iter, ++zfill_cursor) {
    *zfill_cursor = (isspace(*iter)) ? *iter : ' ';
  }
  *zfill_cursor = '\0';
  return std::string(zfill);
}
std::string FileParser::underline_token() {
  int underlined_token_length;
  if (token_length <= 0)
    underlined_token_length = 0;
  else
    underlined_token_length = token_length - 1;
  return std::string(underlined_token_length, '~');
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
