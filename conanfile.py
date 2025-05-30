from conan import ConanFile
from conan.tools.cmake import cmake_layout

class TrackerTui(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    requires = "ftxui/6.0.2"

    def layout(self):
        cmake_layout(self)

