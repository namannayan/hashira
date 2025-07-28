#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <boost/multiprecision/cpp_int.hpp>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using BigInteger = boost::multiprecision::cpp_int;

// Share structure
struct Share {
    BigInteger x;
    BigInteger y;
};

// ProblemInput structure
struct ProblemInput {
    int k;
    std::vector<Share> shares;
};

// JsonInputParser class
class JsonInputParser {
public:
    static ProblemInput parse(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Error reading the file: " + filePath);
        }

        json data = json::parse(file);

        ProblemInput input;
        input.k = data["keys"]["k"];
        int n = data["keys"]["n"];

        for (int i = 1; i <= n; ++i) {
            std::string key = std::to_string(i);
            if (data.contains(key)) {
                BigInteger x(key);
                int base = std::stoi(data[key]["base"].get<std::string>());
                std::string value = data[key]["value"];
                BigInteger y = stringToBigInteger(value, base);
                input.shares.push_back({x, y});
            }
        }
        return input;
    }

private:
    static BigInteger stringToBigInteger(const std::string& str, int base) {
        BigInteger result = 0;
        BigInteger power(1);

        for (int i = str.length() - 1; i >= 0; i--) {
            int digit;
            if (str[i] >= '0' && str[i] <= '9') {
                digit = str[i] - '0';
            } else if (str[i] >= 'a' && str[i] <= 'z') {
                digit = str[i] - 'a' + 10;
            } else if (str[i] >= 'A' && str[i] <= 'Z') {
                digit = str[i] - 'A' + 10;
            } else {
                throw std::invalid_argument("Invalid character in number string");
            }
            result += digit * power;
            power *= base;
        }
        return result;
    }
};

// SecretFinder class
class SecretFinder {
public:
    static BigInteger findSecret(int k, const std::vector<Share>& allShares) {
        std::vector<Share> pointsToUse(allShares.begin(), allShares.begin() + k);
        BigInteger secretSum = 0;

        for (int j = 0; j < k; ++j) {
            const auto& currentPoint = pointsToUse[j];
            BigInteger xj = currentPoint.x;
            BigInteger yj = currentPoint.y;

            BigInteger numerator = 1;
            BigInteger denominator = 1;

            for (int m = 0; m < k; ++m) {
                if (m == j) continue;
                BigInteger xm = pointsToUse[m].x;
                numerator *= -xm;
                denominator *= (xj - xm);
            }

            BigInteger term = yj * numerator / denominator;
            secretSum += term;
        }

        return secretSum;
    }
};

// Main function
int main() {
    std::string testCase1Path = "testcase1.json";
    std::string testCase2Path = "testcase2.json";

    std::cout << "Processing Catalog Placements Assignment..." << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    try {
        ProblemInput input1 = JsonInputParser::parse(testCase1Path);
        std::cout << "Test Case 1: Parsed " << input1.shares.size() << " shares, k = " << input1.k << std::endl;
        std::cout << "Secret for Test Case 1: " << SecretFinder::findSecret(input1.k, input1.shares) << std::endl;

        std::cout << std::endl;

        ProblemInput input2 = JsonInputParser::parse(testCase2Path);
        std::cout << "Test Case 2: Parsed " << input2.shares.size() << " shares, k = " << input2.k << std::endl;
        std::cout << "Secret for Test Case 2: " << SecretFinder::findSecret(input2.k, input2.shares) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Processing complete." << std::endl;

    return 0;
}
