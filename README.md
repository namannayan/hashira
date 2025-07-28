
# hashira

---

## ⚙️ Requirements

### Compiler
- A C++ compiler that supports **C++17**
- Example: `g++`, `clang++`, or Visual Studio

### Libraries
- [Boost (Header-only)](https://www.boost.org/) – for `cpp_int` arbitrary precision integer
- [nlohmann/json](https://github.com/nlohmann/json) – for JSON parsing

---

## 📦 Setup

### 1. Install Boost (Header-only)
- Download Boost from https://www.boost.org/users/download/
- Extract it to a location like: `C:\Libraries\boost_1_88_0`

### 2. Install nlohmann/json
- Download single-header `json.hpp` from:  
  https://github.com/nlohmann/json/releases/latest
- Place it at: `C:\Libraries\nlohmann\json.hpp`

---

## 🧪 Compilation

### 💻 On Windows (PowerShell):

```powershell
g++ -std=c++17 -I"C:/Libraries/boost_1_88_0" -I"C:/Libraries/nlohmann" secret_reconstruction.cpp -o secret_reconstruction
.\secret_reconstruction
