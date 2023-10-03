#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numbers>

constexpr double D_PI = std::numbers::pi;

namespace mylib {

inline double sqrt(double s) {
  double x = s / 2.0;  // Is there any better way to determine initial value?
  double last_x = 0.0; // the value one before the last step

  while (x != last_x) // until the difference is not significant
  {                   // apply Babylonian method step
    last_x = x;
    x = (x + s / x) / 2.0;
  }

  return x;
}
inline double newt_sqrt(double alpha) {

  double x0 = 0, x1 = 0.5 * (1 + alpha);
  int n;

  for (n = 0; x0 != x1; ++n) {
    x0 = x1;
    x1 = 0.5 * (x0 + alpha / x0);
  }

  // std::cout << n << std::endl;

  return (x1);
}

inline double Q_rsqrt(double number) {

  double y = std::bit_cast<double>(0x5fe6eb50c7b537a9 -
                                   (std::bit_cast<std::uint64_t>(number) >> 1));
  // y = y * (1.5 - (number * 0.5 * y * y));
  return y * (1.5 - (number * 0.5 * y * y));
}

inline double Q_sqrt(double num) { return num * Q_rsqrt(num); }
} // namespace mylib

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
      const double area = delta * mylib::Q_sqrt(1 - x * x);
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
