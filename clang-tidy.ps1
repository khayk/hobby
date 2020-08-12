# Simple usage examples
#
# 1. Run clang-tidy on the given files and:
#       a) Display issues in the standart output using checks from $allChecks list
#           - .\clang-tidy.ps1 -files "File1.cpp;File2.cpp"
#
#       b) Applys fixes that are defined in the $allChecks list
#           - .\clang-tidy.ps1 -files "File1.cpp;File2.cpp" -fix
#
#       c) Applys fixes that are defined in the $safeChecks list
#           - .\clang-tidy.ps1 -files "File1.cpp;File2.cpp" -fix -safeOnly
#
# 2. Run clang-tidy on the given folders and redirect output to 'issues.txt` file
#       a) Check for issues only
#           - .\clang-tidy.ps1 -folders "folder1;folder2;folder3" -redirectTo "issues.txt"
#
#       b) Apply fixes defined in the $allChecks list
#           - .\clang-tidy.ps1 -folders "folder1;folder2;folder3" -redirectTo "issues.txt" -fix

param (
    # List of files to check, saperated by `;`
    [String]$files = '',

    # List of folders to check, saperaated by `;`
    [String]$folders = '',

    # Instruct to fix all checks defined in the script
    [Switch]$fix = $false,

    # Narrow down check list to the those, that are 100% safe to apply automatically
    [Switch]$safeOnly = $false,

    # File that will be used to hold the execution results, otherwise result
    # displayed in the standard output
    [String]$redirectTo = ''
)

function dumpCommandLine() {
    Write-Output "=============================="
    Write-Output "*** Script input options ***"
    Write-Output "------------------------------"
    Write-Output "files      : $files"
    Write-Output "folders    : $folders"
    Write-Output "fix        : $fix"
    Write-Output "safeOnly   : $safeOnly"
    Write-Output "redirectTo : $redirectTo"
    Write-Output ""
    Write-Output "------------------------------"
}

# Dump command line
dumpCommandLine

if (Test-Path $env:VCPKG_ROOT) {
    $vcpkgRoot=$env:VCPKG_ROOT
    Write-Output "vcpkg detected at this location '$vcpkgRoot'"
}
else {
    Write-Output "Please define environment varialbe VCPKG_ROOT"
    Exit
}

$vcpkgInclude = Join-Path -Path $vcpkgRoot -ChildPath "installed\x64-windows\include"
Write-Output "vcpkg include dir is '$vcpkgInclude'"


# List of checks that are safe to be fixed automatically
$safeChecks = @(
    "-checks=-*",
    "llvm-namespace-comment",
    "modernize-use-nullptr",
    "modernize-use-override",
    "readability-braces-around-statements",
    "readability-uppercase-literal-suffix"
)


# List of checks to analyze manually
#   - Recheck if we need to enable these: -modernize-use-nodiscard
#   - Configure check for this: -readability-identifier-naming
$allChecks = @(
    "-checks=-*",
    "modernize-*",
    "readability-*",
    "cppcoreguidelines-*",
    "performance-*",
    "misc-*",
    "llvm-*",
    "cert-*",
    "google-*",
    "-llvm-include-order",
    "-cert-err58-cpp",
    "-cppcoreguidelines-avoid-c-arrays",
    "-cppcoreguidelines-avoid-magic-numbers",
    "-cppcoreguidelines-owning-memory",
    "-cppcoreguidelines-pro-bounds-array-to-pointer-decay",
    "-cppcoreguidelines-pro-bounds-constant-array-index",
    "-cppcoreguidelines-pro-bounds-pointer-arithmetic",
    "-cppcoreguidelines-pro-type-reinterpret-cast",
    "-cppcoreguidelines-pro-type-union-access",
    "-cppcoreguidelines-special-member-functions",
    "-google-build-using-namespace",
    "-google-runtime-references",
    "-modernize-avoid-c-arrays",
    "-modernize-use-nodiscard",
    "-modernize-use-trailing-return-type",
    "-readability-implicit-bool-conversion",
    "-readability-magic-numbers"
)

# Define preprocessor settings
$preprocessor = @(
    "-D_ATL_NO_HOSTING",
    "-DUNICODE",
    "-D_UNICODE",
    "-DWIN32",
    "-D_DEBUG",
    "-DDEBUG",
    "-D_WIN32_WINNT=_WIN32_WINNT_WIN10",
    "-D_WINSOCK_DEPRECATED_NO_WARNINGS",
    "-DBOOST_BIND_GLOBAL_PLACEHOLDERS",
    "-DBOOST_ASIO_NO_DEPRECATED"
)

# Define project include directories
$includes = @(
    "-I`"$vcpkgInclude/`"",
    "-I`"./`"",
    "-I`"./daily/src/`"",
    "-I`"./deitel/src/`""
)


# Define clang-tidy options
$options = @("-std=c++17",
             "-fdelayed-template-parsing",
             "-fms-compatibility-version=19.10",
             "-fms-extensions",
             "-Wall",
             "-Wmicrosoft",
             "-Wno-invalid-token-paste",
             "-Wno-unknown-pragmas",
             "-Wno-unused-value"
)


# ==============================================================================
# Determine clang tidy configuration
# ------------------------------------------------------------------------------

# Content of clang-tidy when no args are specified
$excludeList = @(".vs", ".vscode", "bin", "build", "docs")
$includeList = @("*.cpp")
$projectFolders = @("daily\\",
                    "deitel\\")

# Create the list of files that we want to check
$fileList = @()
$folderList = @()

# Configure script as the user commended
if ($files.Length -ne 0) {
    $fileList = $files.Split(';') | Where-Object { $_Length -ne 0 }
    Write-Output "User defined file list: $fileList"
}
elseif ($folders.Length -ne 0) {
    $folderList = $folders.Split(';') | Where-Object { $_Length -ne 0 }
    Write-Output "User defined folder list: $folderList"
}
else {
    $folderList += $projectFolders
    Write-Output "Default folder list: $folderList"
}

if ($folderList.Count -gt 0) {
    Write-Output "Constructing the list of files to be processed..."

    $filter = $folderList -join '|'
    $excludeFilter = $excludeList -join '|'

    $fileList = Get-ChildItem -Path '.' -Recurse -File -Force -Include $includeList `
        | Where-Object { $_.FullName -Match $filter } `
        | Where-Object { $_.FullName -NotMatch $excludeFilter } `
        | Select-Object -ExpandProperty FullName

    Write-Output $fileList
    Write-Output "Construction completed. Discovered $($fileList.Count) files"
}

$checkList = $allChecks
$fixCommand = "--"

if ($fix)
{
    # Activate safe checks only, these are checks that 100% are safe to apply
    if ($safeOnly)
    {
        $checkList = $safeChecks
    }

    $fixCommand = "-format-style=file -fix" + $fixCommand
}

$checks = $checkList -join ','

# ==============================================================================
# Run clang tidy application
# ------------------------------------------------------------------------------

$counter = 1

if ($redirectTo.Length -gt 0) {
    # Clean the content of the file
    '' > $redirectTo
}

foreach ($file in $fileList) {
    # Boilerplate staff, see nice progress
    $percent = [Math]::Round($counter * 100 / $fileList.Count)
    $relativeName = $file

    if ($file.IndexOf($PSScriptRoot) -ne -1)
    {
        $pos = $PSScriptRoot.length
        $relativeName = $file.Remove(0, $pos)
    }

    if ($redirectTo.Length -gt 0) {
        Write-Output "Redirecting"
        clang-tidy.exe $file $checks $fixCommand $options $preprocessor $includes >>$redirectTo
    }
    else {
        clang-tidy.exe $file $checks $fixCommand $options $preprocessor $includes
    }

    Write-Output "Completed: $percent%, File: $relativeName"
    $counter++
}
