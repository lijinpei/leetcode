#include <string>
#include <map>

class Solution {
  std::map<int, std::string> storage;
  int counter = 0;
public:
  // Encodes a URL to a shortened URL.
  std::string encode(const std::string &longUrl) {
    storage[counter] = longUrl;
    return std::to_string(counter++);
  }
  // Decodes a shortened URL to its original URL.
  std::string decode(const std::string &shortUrl) {
    return storage[std::stoi(shortUrl)];
  }
};

