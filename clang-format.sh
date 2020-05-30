find . -regex '.*\.\(cpp\|hpp\|h\|cc\|cxx\)' | xargs clang-format -i -style=file
