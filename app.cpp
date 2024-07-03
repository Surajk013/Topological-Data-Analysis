#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

// Function to trim whitespace from both ends of a string
std::string trim(const std::string& str) {
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) {
        start++;
    }

    auto end = str.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

// Function to remove surrounding quotes from a string
std::string remove_quotes(const std::string& str) {
    if (str.size() >= 2 && str.front() == '"' && str.back() == '"') {
        return str.substr(1, str.size() - 2);
    }
    return str;
}

// Function to split a string by a delimiter
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(remove_quotes(trim(token)));
    }
    return tokens;
}

int main() {
    std::string file_path = "/run/media/suraj/KSS/Studies/RVCE/4th_sem/DAA/weather/weather.csv";
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return 1;
    }

    // Read the header line
    std::string headerLine;
    std::getline(file, headerLine);
    std::vector<std::string> columns = split(headerLine, ',');

    // Store the data
    std::vector<std::map<std::string, std::string>> data;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> values = split(line, ',');
        std::map<std::string, std::string> row;
        for (size_t i = 0; i < columns.size(); ++i) {
            row[columns[i]] = values[i];
        }
        data.push_back(row);
    }

    file.close();

    // Define the columns to filter by and the columns to display
    std::vector<std::string> filter_columns = {"Station.City", "Date.Full"};
    std::vector<std::string> display_columns = {
        "Data.Temperature.Max Temp", "Data.Temperature.Avg Temp",
        "Data.Temperature.Min Temp", "Data.Wind.Direction",
        "Data.Wind.Speed", "Data.Precipitation"};

    // Prompt user for filtering criteria
    std::map<std::string, std::string> filters;
    std::string value;
    for (const auto& column : filter_columns) {
        std::cout << "Enter the value for '" << column << "': ";
        std::getline(std::cin, value);
        filters[column] = value;
    }

    // Apply filters to the data
    std::vector<std::map<std::string, std::string>> filtered_data;
    for (const auto& row : data) {
        bool match = true;
        for (const auto& filter : filters) {
            if (row.at(filter.first) != filter.second) {
                match = false;
                break;
            }
        }
        if (match) {
            filtered_data.push_back(row);
        }
    }

    // Display filtered data with labels
    for (const auto& row : filtered_data) {
        for (const auto& col : display_columns) {
            std::cout << col << ": " << row.at(col) << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}