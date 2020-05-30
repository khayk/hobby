# List of checks to analyze manually
$checkList="-checks=-*,
modernize-*,
readability-*,
cppcoreguidelines-*,
performance-*,
misc-*,
llvm-*,
cert-*,
google-*,
-llvm-include-order,
-cert-err58-cpp,
-cppcoreguidelines-avoid-c-arrays,
-cppcoreguidelines-avoid-magic-numbers,
-cppcoreguidelines-owning-memory,
-cppcoreguidelines-pro-bounds-array-to-pointer-decay,
-cppcoreguidelines-pro-bounds-constant-array-index,
-cppcoreguidelines-pro-bounds-pointer-arithmetic,
-cppcoreguidelines-pro-type-reinterpret-cast,
-cppcoreguidelines-pro-type-union-access,
-cppcoreguidelines-special-member-functions,
-google-build-using-namespace,
-google-runtime-references,
-modernize-avoid-c-arrays,
-modernize-use-trailing-return-type,
-readability-implicit-bool-conversion,
-readability-magic-numbers
"

# List of checks to be fixed automatically
$fixCheckList="-checks=-*,
llvm-namespace-comment,
modernize-use-nullptr,
modernize-use-override,
readability-braces-around-statements,
readability-uppercase-literal-suffix
"

# -cert-err58-cpp check actually is a good thing, but gaves false positive error on gtest files

# $options=

Get-ChildItem -Path . -Filter *daily*.cpp -Recurse -ErrorAction SilentlyContinue -Force |
Foreach-Object {
    clang-tidy.exe -format-style=file $_.FullName $fixCheckList -fix -- `
        -std=c++17 `
        -fdelayed-template-parsing `
        -fms-compatibility-version=19.10 `
        -fms-extensions `
        -Wall `
        -Wmicrosoft `
        -Wno-invalid-token-paste `
        -Wno-unknown-pragmas `
        -Wno-unused-value `
        -D_ATL_NO_HOSTING -DUNICODE -D_UNICODE -DWIN32 -D_DEBUG -DDEBUG `
        -I"c:/Code/Repo/Github/hobby/build/googletest-src/googletest/include/" `
        -I"./daily/src/"
}


Get-ChildItem -Path . -Filter *daily*.cpp -Recurse -ErrorAction SilentlyContinue -Force |
Foreach-Object {
    clang-tidy.exe $_.FullName $checkList -- `
        -std=c++17 `
        -fdelayed-template-parsing `
        -fms-compatibility-version=19.10 `
        -fms-extensions `
        -Wall `
        -Wmicrosoft `
        -Wno-invalid-token-paste `
        -Wno-unknown-pragmas `
        -Wno-unused-value `
        -D_ATL_NO_HOSTING -DUNICODE -D_UNICODE -DWIN32 -D_DEBUG -DDEBUG `
        -I"c:/Code/Repo/Github/hobby/build/googletest-src/googletest/include/" `
        -I"./daily/src/"
}

