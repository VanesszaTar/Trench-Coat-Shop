# Trench Coat Shop Application (C++ / Qt)

A desktop application for managing a trench coat shop, developed using **C++ and the Qt framework**.  
This project was built as part of coursework and demonstrates layered architecture, GUI design, and software engineering principles.

## 🧥 Features

### 👨‍💼 Administrator Mode
- Add, remove, and update trench coats
- Undo/Redo functionality for modifications
- Persistent storage in CSV and HTML formats

### 🛍 User Mode
- Browse trench coats filtered by size
- Add coats to shopping basket
- View and manage basket contents
- Save basket to CSV or HTML

---

## 🏗 Architecture

The application follows a layered architecture:

- **Domain** – TrenchCoat entity
- **Repository** – Data storage mechanism
- **Service** – Business logic
- **UI** – Qt graphical interface

This separation allows modular design, easier testing, and maintainable code.

---

## 🛠 Technologies Used

- C++
- Qt Framework (Widgets)
- Object-Oriented Programming
- File I/O (CSV / HTML)
- Undo/Redo design using command pattern
