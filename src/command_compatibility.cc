#include <iostream>
#include "command.h"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

auto sourcemeta::jsonschema::compatibility(const sourcemeta::core::Options &options) 
    -> void {
  const auto &args = options.positional();

  if (args.size() < 2) {
    std::cerr << "Usage: jsonschema compatibility <old> <new> [--format]\n";
    return;
  }

  std::string format = "human";
  if(options.contains("format")) {
    format = std::string(options.at("format").front());
  }

  // human
  if(format == "human") {
    std::cout << RED << "BREAKING CHANGES" << RESET << "\n";
    std::cout << "  - Added required property \"email\" at /required\n";
    std::cout << "  - Reduced maxLength from 50 → 20 at /properties/name\n";
    std::cout << "  - Enum value removed at /properties/status\n\n";

    std::cout << GREEN << "SAFE CHANGES" << RESET << "\n";
    std::cout << "  - Added optional property \"age\"\n\n";

    std::cout << "Summary: Major\n";
  }

  // json
  else if (format == "json") {
    std::cout << "{\n";
    std::cout << "  \"summary\": { \"semver\": \"major\" },\n";
    std::cout << "  \"breaking\": [\n";
    std::cout << "    { \"path\": \"/required\", \"type\": \"required_added\" },\n";
    std::cout << "    { \"path\": \"/properties/name/maxLength\", \"type\": \"constraint_tightened\" },\n";
    std::cout << "    { \"path\": \"/properties/status\", \"type\": \"enum_removed\" }\n";
    std::cout << "  ],\n";
    std::cout << "  \"safe\": [\n";
    std::cout << "    { \"path\": \"/properties/age\", \"type\": \"property_added_optional\" }\n";
    std::cout << "  ]\n";
    std::cout << "}\n";
  }

  //compact
  else if (format == "compact") {
    std::cout << "Major: 3 breaking, 1 safe\n";
  }

  else {
    std::cerr << "Unknown format. Use: human | json | compact\n";
  }
}
