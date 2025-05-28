#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

typedef void(__stdcall* t_InjectedFunction)();

int main() {
	std::cout << "Starting Injection...\n";

	HMODULE hModule = LoadLibraryW(L"injector-dll.dll");
	if (!hModule || hModule == INVALID_HANDLE_VALUE) {
		std::cerr << "Failed to load injector-dll.dll\n";
		return EXIT_FAILURE;
	}

	std::cout << "Successfully loaded injector-dll.dll\n";

	t_InjectedFunction InjectedFunction = (t_InjectedFunction)GetProcAddress(hModule, "InjectedFunction");
	if (!InjectedFunction) {
		std::cerr << "Failed to get address of InjectedFunction\n";
		FreeLibrary(hModule);
		return EXIT_FAILURE;
	}

	InjectedFunction();
}