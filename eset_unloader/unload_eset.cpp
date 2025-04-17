#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <string>
#include <algorithm>

#pragma comment(lib, "psapi.lib")

class unload_eset {
public:
    void run() {
        print_intro();
        system("pause");
        DWORD pid = get_current_pid();
        set_color(11);
        std::wcout << L"enumerating loaded modules in process " << pid << std::endl;
        process_target_module(L"ebehmoni.dll");
        set_color(14);
        std::wcout << L"attempting to unload ebehmoni.dll..." << std::endl;
        set_color(14);
        std::wcout << L"[after completion] press any key to exit..." << std::endl;
        system("pause");
    }

private:
    void set_color(WORD color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }
    std::wstring to_lower(const std::wstring& input) {
        std::wstring out = input;
        std::transform(out.begin(), out.end(), out.begin(), ::towlower);
        return out;
    }
    void unload_module(HMODULE module) {
        if (FreeLibrary(module)) {
            set_color(10);
            std::wcout << L"successfully unloaded module." << std::endl;
        }
        else {
            set_color(12);
            std::wcerr << L"failed to unload module." << std::endl;
        }
        set_color(7);
    }
    void handle_module(const std::wstring& name, HMODULE module, const std::wstring& full_path) {
        MODULEINFO mod_info;
        if (GetModuleInformation(GetCurrentProcess(), module, &mod_info, sizeof(mod_info))) {
            set_color(9);
            std::wcout << L"old base address of " << name << L": 0x"
                << std::hex << reinterpret_cast<uintptr_t>(mod_info.lpBaseOfDll) << std::endl;
        }
        set_color(13);
        std::wcout << L"found " << name << L" at: " << full_path << std::endl;
        unload_module(module);
    }

    bool try_find_module(HMODULE& module, const std::wstring& target_name, std::wstring& path) {
        HMODULE h_mods[1024];
        DWORD cb_needed;
        if (EnumProcessModules(GetCurrentProcess(), h_mods, sizeof(h_mods), &cb_needed)) {
            for (unsigned int i = 0; i < cb_needed / sizeof(HMODULE); i++) {
                WCHAR sz_mod_name[MAX_PATH];
                if (GetModuleFileNameExW(GetCurrentProcess(), h_mods[i], sz_mod_name, MAX_PATH)) {
                    std::wstring current_path = sz_mod_name;
                    if (to_lower(current_path).find(to_lower(target_name)) != std::wstring::npos) {
                        module = h_mods[i];
                        path = current_path;
                        return true;
                    }
                }
            }
        }
        return false;
    }
    void process_target_module(const std::wstring& name) {
        HMODULE module = nullptr;
        std::wstring path;
        if (try_find_module(module, name, path)) {
            handle_module(name, module, path);
        }
        else {
            set_color(6);
            std::wcout << name << L" not found in process. loading manually..." << std::endl;
            std::wstring full_load_path = L"C:\\Program Files\\ESET\\ESET Security\\" + name;
            HMODULE forced = LoadLibraryW(full_load_path.c_str());
            if (forced) {
                MODULEINFO mod_info;
                if (GetModuleInformation(GetCurrentProcess(), forced, &mod_info, sizeof(mod_info))) {
                    set_color(9);
                    std::wcout << L"forced old base address of " << name << L": 0x"
                        << std::hex << reinterpret_cast<uintptr_t>(mod_info.lpBaseOfDll) << std::endl;
                }
                set_color(13);
                std::wcout << L"manually loaded " << name << L" at: " << full_load_path << std::endl;
                unload_module(forced);
            }
            else {
                set_color(12);
                std::wcerr << L"failed to manually load " << name << std::endl;
            }
        }
    }
    void print_intro() {
        set_color(14);
        std::wcout << L"[before start] press any key to begin module inspection..." << std::endl;
    }
    DWORD get_current_pid() {
        return GetCurrentProcessId();
    }
};

int wmain() {
    unload_eset u;
    u.run();
    return 0;
}
