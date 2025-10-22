# 🎨 Digital Art Gallery & Auction System (C++)

A simple **console-based digital art auction system** built in **C++**.  
This project allows users to **add artworks, place bids, view all artworks, manage bids**, and save data locally using CSV files — no external database required.

---

## 🧰 Features

✅ Add new artworks with title, artist name, and base price  
✅ Show all artworks with their current bids  
✅ Place bids on artworks (only higher bids accepted)  
✅ View detailed info for each artwork and its bids  
✅ Delete artworks and related bids  
✅ View top (highest bid) artwork  
✅ Persistent storage using CSV files (`artworks.csv`, `bids.csv`)  

---

## 🧱 Technologies Used

- **Language:** C++ (Standard Library only)
- **File Handling:** CSV (text-based storage)
- **IDE Support:** Dev-C++, Code::Blocks, Visual Studio, or g++
- **No MySQL or Boost dependency!**

---

## 🖥️ How to Run

### 🔹 Option 1: Using Dev-C++
1. Open `Digital_Art_Gallery_Auction_New.dev` or create a new project.
2. Add `main.cpp` file to the project.
3. Go to **Tools → Compiler Options → Directories → C++ Includes** (if needed).
4. Make sure the output directory (e.g., `/bin/`) exists.
5. Compile and run the project (`Ctrl + F10`).

### 🔹 Option 2: Using Command Line
If you have **g++** installed (MinGW / MSYS64):

```bash
g++ main.cpp -o ArtGallery
ArtGallery.exe
