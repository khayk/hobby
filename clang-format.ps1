$excludeList = @("*build*", "*out*", "*.vs*", "*.vscode*", "bin")
$includeList = @("*.cpp", "*.h")

# Create the list of files that we want to format
$fileList = New-Object Collections.Generic.List[String]

Get-ChildItem -Path . -Directory -Exclude $excludeList | Foreach-Object {
    Get-ChildItem -Path $_.FullName -Include $includeList -Recurse | Foreach-Object {
        $fileList.Add($_.FullName)
    }
}

foreach ($file in $fileList) {
    clang-format.exe -i -style=file $file
}
