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
    char dummy_char;

  public:
    const char* filename;
    int lineno;
    int colno;
    std::string line_string;
    std::string token;
    int token_length;

    explicit FileParser(const char* filename);
    bool advance_line();
    int get_colno();

    bool next_token();
    bool next_token(float& token);
    bool next_token(float& token, float min, float max);
    bool next_token(int& token);
    bool next_token_positive(int& token);
    bool next_token(std::string& token);
    std::string require_next_token();
    void require_next_token(std::string& token);
    void require_next_token(int& token);
    void require_next_token_positive(int& token);
    void require_next_token(float& token);
    void require_next_token_positive(float& token);
    void require_next_token_min(float& token, float min);
    void require_next_token_max(float& token, float max);
    void require_next_token_minmax(float& token, float min, float max);

    std::string pos_identifier();
    std::string pos_indicator();
    std::string zfill_to_colno();
    std::string underline_token();
    std::string here();
    std::string here(std::string);
};
}
