$excludeList = @("*build*", "*out*", "*.vs*", "*.vscode*", "bin")
$includeList = @("*.cpp")

# Create the list of files that we want to check
$fileList = New-Object Collections.Generic.List[String]

Get-ChildItem -Path . -Directory -Exclude $excludeList | Foreach-Object {
    Get-ChildItem -Path $_.FullName -Include $includeList -Recurse | Foreach-Object {
        $fileList.Add($_.FullName)
    }
}

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

# Run tidy with auto fix checks
foreach ($file in $fileList) {
    clang-tidy.exe -format-style=file $file $fixCheckList -fix -- `
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
        -I"./build/googletest-src/googletest/include/" `
        -I"./daily/src/"
}

# Run tidy with all generic check, for manual fixing
foreach ($file in $fileList) {
    clang-tidy.exe $file $checkList -- `
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
        -I"./build/googletest-src/googletest/include/" `
        -I"./daily/src/"
}
