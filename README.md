# Eset-Unload 💉

This project is a C++ application designed to help unload or manually load and unload the `ebehmoni.dll` module, a part of the ESET security software. It uses Visual Studio 143 toolset (v143) and ISO C++14.

---

## 📜 Project Overview

The main goal of this tool is to:
- Enumerate and find the `ebehmoni.dll` module loaded in the current process.
- If found, unload it.
- If not found, load it manually from a specific path and then unload it.

This tool works by using Windows API calls to manage DLLs within the process.

---

## 🔧 How to Build and Run

### ⚙️ Prerequisites:
- Visual Studio 143 toolset (v143) or later.
- C++14 or later.
- Windows SDK (for necessary APIs such as `Psapi.h`, `Windows.h`).

### 🏗️ Steps to Build:
1. Clone the repository.
2. Open the project in Visual Studio.
3. Build the solution.
4. The executable will be generated in the output directory.
5. Run the application to perform the DLL unloading tasks.

---

## ⚙️ Usage

1. **Running the Application:**
    - Compile the application.
    - When you run it, the following will happen:
      - The current process ID is displayed.
      - The tool attempts to find and unload the `ebehmoni.dll`.
      - If it is not found, it tries to load the DLL from `C:\Program Files\ESET\ESET Security\` and then unloads it.

2. **Example Output**:
    ```
    [before start] press any key to begin module inspection...
    Press any key to continue . . .
    enumerating loaded modules in process 9100
    old base address of ebehmoni.dll: 0x7ffcfc570000
    found ebehmoni.dll at: C:\Program Files\ESET\ESET Security\ebehmoni.dll
    successfully unloaded module.
    attempting to unload ebehmoni.dll...
    [after completion] press any key to exit...
    Press any key to continue . . .
    ```

---

## ⚙️ Requirements

- **Windows OS**: This application is built to run on Windows.
- **Visual Studio 143 (v143)**: Required for compilation.
- **C++14 Standard**: The code is written using ISO C++14.

---

## 🚀 Contributing

Feel free to fork the repository and create pull requests! Please ensure that your code is compatible with C++14 and follows the general coding standards.

---

## 📄 License

This project is open-source under the MIT License. Check the `LICENSE` file for more details.

---

## ⚠️ Important Notes

- **Warning**: This tool is intended for educational purposes. Please use it responsibly and ensure you have permission before interacting with system modules.
- **Disclaimer**: I, Evilbytecode, do not take any responsibility for the misuse of this tool. By using it, you acknowledge that you have proper authorization and are solely responsible for any consequences of its usage. Ensure you are using this tool in a legal and ethical manner.

## How to verify that it worked
- Open the process (Do not press anything yet)
- Open sysinformer/prochacker and open your process and press on modules tab
- you will see the .dll and go back to your process and press enter. after that go back and .dll wont be there.
