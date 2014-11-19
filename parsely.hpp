#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>


#define INF std::numeric_limits<float>::infinity()

namespace parsely {
class FileParser {
  private:
    std::ifstream file;
    std::istringstream line;
    int get_colno();
    int get_line_length();

  public:
    const char* filename;
    int lineno;
    int colno;
    int line_length;
    std::string line_string;
    std::string token;
    int token_length;
    bool line_empty();

    explicit FileParser(const char* filename);

    bool advance_line();
    bool advance_lines();
    void require_advance_line(char description[]);
    void require_advance_line();

    bool next_token();
    bool next_token(float& token);
    bool next_token(float& token, float min, float max);
    bool next_token(int& token);
    bool next_token(int& token, int min, int max);
    bool next_token(std::string& token);
    std::string require_next_token(char description[]);
    void require_next_token(std::string& token, char description[]);
    void require_next_token(int& token, char description[]);
    void require_next_token(float& token, char description[]);
    void require_next_token(int& token, int min, int max, char description[]);
    void require_next_token(float& token, float min, float max, char description[]);

    std::string pos_identifier();
    std::string pos_indicator();
    std::string zfill_to_colno();
    std::string underline_token();
    std::string here();
    std::string here(std::string);
};
}
