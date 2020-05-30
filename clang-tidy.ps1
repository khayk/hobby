Get-ChildItem -Path . -Filter *daily*.cpp -Recurse -ErrorAction SilentlyContinue -Force |
Foreach-Object {
    clang-tidy.exe -format-style=file $_.FullName -- -std=c++17 -Ic:\Code\Repo\Github\hobby\build\googletest-src\googletest\include
}

# set options=^
# -std=c++17 ^
# -fdelayed-template-parsing ^
# -fms-compatibility-version=19.10 ^
# -fms-extensions ^
# -Wall ^
# -Wmicrosoft ^
# -Wno-invalid-token-paste ^
# -Wno-unknown-pragmas ^
# -Wno-unused-value ^
# -D_ATL_NO_HOSTING -DUNICODE -D_UNICODE -DWIN32 -D_DEBUG -DDEBUG ^
# -IC:\Code\Repo\Github\vcpkg\installed\x64-windows\include