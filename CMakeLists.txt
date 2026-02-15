cmake_minimum_required(VERSION 3.30)
project(a10-VanesszaTar)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH /opt/homebrew/Cellar/qt@5/5.15.16_2)
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
add_executable(a10-VanesszaTar TrenchCoat.cpp Repository.cpp Service.cpp UI.cpp main.cpp validators.cpp exceptions.cpp CSVBasketExporter.cpp HTMLBasketExporter.cpp GUI.cpp AdminWindow.cpp UserWindow.cpp ViewAllAdmin.cpp AddCoatDialog.cpp RemoveCoatDialog.cpp UpdateCoatDialog.cpp UserViewDialog.cpp ShoppingDialog.cpp CheckoutDialog.cpp SaveBasketDialog.cpp ViewSavedBasketDialog.cpp BasketTableModel.cpp)
target_link_libraries(a10-VanesszaTar
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets)