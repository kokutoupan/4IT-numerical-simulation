#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numbers>

constexpr double D_PI = std::numbers::pi;

int main() {

  int DivNum = 1;
  for (auto loopCount = 1; loopCount < 10; ++loopCount) {
    DivNum *= 10;
    double delta = 1.0 / DivNum;
    std::cout << DivNum << ", ";

    const auto startTime = std::chrono::system_clock::now();
    double sum = 0;
    for (int i = 0; i < DivNum; ++i) {
      const double x = (delta * i);
      const double area = delta * (1 / (x * x + 1));
      sum += area;
    }
    const double pi = sum * 4.0;
    const auto endTime = std::chrono::system_clock::now();
    // std::cout << std::setprecision(15) << "PI ~= " << pi << std::endl;
    // std::cout << "Error [%] = " << (100.0 * std::fabs(D_PI - pi) / D_PI)
    //           << std::endl;
    // std::cout << "Elapsed time [ms] = "
    //           <<
    //           std::chrono::duration_cast<std::chrono::milliseconds>(endTime
    //           -
    //                                                                    startTime)
    //                  .count()
    //           << std::endl;
    std::cout << std::setprecision(15) << pi << ", ";
    std::cout << (100.0 * std::fabs(D_PI - pi) / D_PI) << ", ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime -
                                                                      startTime)
                     .count()
              << std::endl;
  }
  return 0;
}
