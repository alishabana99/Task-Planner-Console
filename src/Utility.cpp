#include"Utility.h"


std::string Utility::TrimRecordIndentation(const std::string& str) {
    size_t first = str.find_first_not_of('\t'); // Find the first non-space character
    if (std::string::npos == first) // If no non-space character found, return an empty string
        return "";

    size_t last = str.find_last_not_of('\t'); // Find the last non-space character
    return str.substr(first, (last - first + 1)); // Return the trimmed string
}
