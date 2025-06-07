#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

int main() {
  auto screen = ftxui::Screen::Create(
      ftxui::Dimension::Full(),   // Use full terminal width
      ftxui::Dimension::Fixed(10) // Fixed height of 10 rows
  );

  // Access a specific pixel at (10, 5)
  auto &pixel1 = screen.PixelAt(10, 5);

  // Set properties of the pixel.
  pixel1.character = U'X';
  pixel1.foreground_color = ftxui::Color::Red;
  pixel1.background_color = ftxui::Color::RGB(0, 255, 0);
  pixel1.bold = true; // Set bold style

  auto &pixel2 = screen.PixelAt(0, 0);

  // Set properties of the pixel.
  pixel2.character = U'O';
  pixel2.foreground_color = ftxui::Color::Blue;
  pixel2.background_color = ftxui::Color::RGB(0, 255, 0);
  pixel2.bold = true; // Set bold style

  screen.Print(); // Print the screen to the terminal
}

