Get-ChildItem -Path . -Filter *daily*.cpp -Recurse -ErrorAction SilentlyContinue -Force |
Foreach-Object {
    clang-format.exe -i -style=file $_.FullName
}
