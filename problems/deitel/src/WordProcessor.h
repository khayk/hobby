#pragma once

#include <string>

namespace deitel {

std::string_view nextWord(size_t offset, const std::string& str);

class WordProcessor {
    uint32_t charsPerLine_{65};
    uint32_t charsPerMargin_{10};

public:
    WordProcessor(uint32_t lineLength, uint32_t marginLength);

    [[nodiscard]] uint32_t lineLength() const noexcept;
    [[nodiscard]] uint32_t marginLength() const noexcept;

    void align(const std::string& text, std::string& aligned) const;
};

} // namespace deitel
