#include "WordProcessor.h"
#include <stdexcept>
#include <vector>

namespace {

} // namespace

namespace deitel {

std::string_view nextWord(size_t offset, const std::string& str)
{
    const auto beg = str.find_first_not_of(' ', offset);
    if (beg == std::string::npos)
    {
        return "";
    }

    const auto end = str.find_first_of(' ', beg);
    if (end == std::string::npos)
    {
        return std::string_view(str.c_str() + beg);
    }

    return std::string_view(str.c_str() + beg, end - beg);
}

WordProcessor::WordProcessor(uint32_t lineLength, uint32_t marginLength)
    : charsPerLine_(lineLength - 2 * marginLength)
    , charsPerMargin_(marginLength)
{
    if (lineLength == 0)
    {
        throw std::invalid_argument("Line length should be at least 1 character long");
    }

    if (2 * marginLength >= lineLength)
    {
        throw std::invalid_argument("Margin are too big to fit in a single line");
    }
}

[[nodiscard]] uint32_t WordProcessor::lineLength() const noexcept
{
    return charsPerLine_ + 2 * charsPerMargin_;
}

[[nodiscard]] uint32_t WordProcessor::marginLength() const noexcept
{
    return charsPerMargin_;
}

void WordProcessor::align(const std::string& text, std::string& aligned) const
{
    constexpr char lineBreak = '\n';
    size_t offset            = 0;
    std::vector<std::string_view> line;

    while (offset < text.size())
    {
        aligned.append(charsPerMargin_, ' ');

        // Select word candidates that will fit in a line
        size_t nonSpacesChars = 0;
        size_t currentLength  = 0;
        while (true)
        {
            const auto word = nextWord(offset, text);

            if (word.empty() || currentLength + word.length() > charsPerLine_)
            {
                break;
            }

            currentLength += word.length() + 1;
            nonSpacesChars += word.length();
            line.push_back(word);
            offset = word.data() - text.data() + word.length() + 1;
        }

        size_t remainingSpaces = charsPerLine_ - nonSpacesChars;
        size_t spaces = remainingSpaces / (line.size() < 2 ? 1 : (line.size() - 1));
        size_t idx    = 0;
        while (idx + 1 < line.size())
        {
            aligned.append(line[idx]);
            const auto spacesToPut = (idx + 2 < line.size() ? spaces : remainingSpaces);
            aligned.append(spacesToPut, ' ');
            remainingSpaces -= spaces;
            ++idx;
        }

        if (idx < line.size())
        {
            aligned.append(line[idx]);
            aligned.append(charsPerMargin_, ' ');
            aligned.push_back(lineBreak);
        }

        line.clear();
    }

    if (!aligned.empty() && aligned.back() == lineBreak)
    {
        aligned.pop_back();
    }
}

} // namespace deitel
