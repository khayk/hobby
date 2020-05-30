find . -regex '.*\.\(cpp\|hpp\|h\|cc\|cxx\)' -not -path "./build/*" | xargs clang-format -i -style=file
