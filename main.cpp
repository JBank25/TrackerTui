#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/screen.hpp>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

int zellerDayOfWeek(int year, int month, const int day) {
  // Zeller's congruence adjustments
  if (month < 3) {
    month += 12;
    year--;
  }

  int k = year % 100; // year of century
  int j = year / 100; // century

  int h = (day + ((13 * (month + 1)) / 5) + k + (k / 4) + (j / 4) - 2 * j) % 7;

  // Convert Zeller's result (0=Saturday) to standard (0=Sunday)
  return (h + 5) % 7;
}

std::vector<std::vector<std::string>> generateStringWeekNums(int startNum) {
  std::vector<std::vector<std::string>> result;
  std::vector<std::string> curResult;

  int counter = 0;
  // Blank spaces for first few days if needed. For example
  // if July 1, 2025 is a Tuesday then we would want
  // Sunday Monday Tuesday Wednesday Thursday Friday Saturday
  //                  1         2       3       4       5
  for (; counter < startNum; counter++) {
    curResult.push_back("     ");
  }
  for (int i = counter; i <= 31; i++) {
    if (curResult.size() % 7 == 0 && !curResult.empty()) {
      result.push_back(curResult);
      curResult.clear();
    } else {
      std::ostringstream oss;
      oss << std::setfill(' ') << std::setw(3) << i;
      curResult.push_back(oss.str());
    }
  }
  return result;
}

int main() {
  using namespace ftxui;
  const std::vector<std::string> daysOfWeek = {
      {"Sunday ", " Monday ", " Tuesday ", " Wednesday ", " Thursday ",
       " Friday ", " Saturday"}};

  std::vector<std::vector<std::string>> dayNums =
      generateStringWeekNums(zellerDayOfWeek(2025, 7, 1));

  auto tableDays = Table({{daysOfWeek}});

  tableDays.SelectAll().Border(LIGHT);
  tableDays.SelectRow(1).Border(DOUBLE);
  tableDays.SelectRow(1).SeparatorHorizontal(LIGHT);

  auto tableNums = Table({{dayNums}});

  tableNums.SelectAll().Border(LIGHT);
  tableNums.SelectRow(1).Border(DOUBLE);
  tableNums.SelectRow(1).SeparatorHorizontal(LIGHT);

  auto documentDays = tableDays.Render();
  auto documentNums = tableNums.Render();
  auto screenDays =
      Screen::Create(Dimension::Full(), Dimension::Fit(documentDays));
  auto screenNums =
      Screen::Create(Dimension::Full(), Dimension::Fit(documentNums));
  Render(screenDays, documentDays);
  Render(screenNums, documentNums);
  screenDays.Print();
  screenNums.Print();
}
