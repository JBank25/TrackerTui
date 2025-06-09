#include <memory> // for allocator, __shared_ptr_access
#include <string> // for string, basic_string
#include <vector> // for vector

#include "ftxui/component/captured_mouse.hpp" // for ftxui
#include "ftxui/component/component.hpp"      // for Toggle, Renderer, Vertical
#include "ftxui/component/component_base.hpp" // for ComponentBase
#include "ftxui/component/screen_interactive.hpp" // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp" // for text, hbox, vbox, Element
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
    std::ostringstream oss;
    oss << std::setfill(' ') << std::setw(3) << "";
    curResult.push_back(oss.str());
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
  int week1Selected = 0;
  int week2Selected = 0;
  int week3Selected = 0;
  int week4Selected = 0;

  Component toggleWeek1 = Toggle(&dayNums.at(0), &week1Selected);
  Component toggleWeek2 = Toggle(&dayNums.at(1), &week2Selected);
  Component toggleWeek3 = Toggle(&dayNums.at(2), &week3Selected);
  Component toggleWeek4 = Toggle(&dayNums.at(3), &week4Selected);

  auto container = Container::Vertical({
      toggleWeek1,
      toggleWeek2,
      toggleWeek3,
      toggleWeek4,
  });

  auto renderer = Renderer(container, [&] {
    return vbox({
        filler(),
        hbox(toggleWeek1->Render()),
        hbox(toggleWeek2->Render()),
        hbox(toggleWeek3->Render()),
        hbox(toggleWeek4->Render()),
    });
  });
  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(renderer);
}
