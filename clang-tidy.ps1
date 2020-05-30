$checkList="-checks=-*,modernize-*,readability-*,cppcoreguidelines-*,performance-*,misc-*,llvm-*,cert-*,google-*,-llvm-include-order,-modernize-avoid-c-arrays,-modernize-use-trailing-return-type,-readability-implicit-bool-conversion,-readability-magic-numbers,-cppcoreguidelines-special-member-functions,-cppcoreguidelines-pro-bounds-array-to-pointer-decay,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-avoid-c-arrays,-cppcoreguidelines-pro-type-reinterpret-cast,-cppcoreguidelines-owning-memory,-cppcoreguidelines-pro-bounds-constant-array-index,-cppcoreguidelines-avoid-magic-numbers,-google-build-using-namespace,-google-runtime-references"

Get-ChildItem -Path . -Filter *daily*.cpp -Recurse -ErrorAction SilentlyContinue -Force |
Foreach-Object {
    clang-tidy.exe $_.FullName $checkList -- -std=c++17 -I"c:/Code/Repo/Github/hobby/build/googletest-src/googletest/include/" -I"./daily/src/"
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