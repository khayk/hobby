#include <gtest/gtest.h>
#include "WordProcessor.h"

using namespace deitel;

TEST(WordProcessorTest, AdjustText)
{
    WordProcessor wordProc(65, 0);

    const std::string text =
        "Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots "
        "in a piece of classical Latin literature from 45 BC, making it over 2000 years "
        "old. Richard McClintock, a Latin professor at Hampden-Sydney College in "
        "Virginia, looked up one of the more obscure Latin words, consectetur, from a "
        "Lorem Ipsum passage, and going through the cites of the word in classical "
        "literature, discovered the undoubtable source.";

    std::string aligned;
    wordProc.align(text, aligned);
    std::cout << '\n' << aligned << '\n';

    EXPECT_GE(aligned.length(), text.length());

    size_t offsetU = 0;
    size_t offsetA = 0;

    while (offsetU < text.size())
    {
        const auto wordU = nextWord(offsetU, text);
        const auto wordA = nextWord(offsetA, aligned);

        ASSERT_TRUE(wordU.length() > 0);
        EXPECT_EQ(wordU, wordA);

        offsetU = text.data() - wordU.data() + wordU.length() + 1;
        offsetA = aligned.data() - wordA.data() + wordA.length() + 1;
    }

    size_t off     = 0;
    while (off < aligned.length())
    {
        auto pos = aligned.find('\n', off + 1);
        if (pos != std::string::npos)
        {
            EXPECT_LE(pos - off, wordProc.lineLength() + 1);
            off = pos;
        }
        else
        {
            off = aligned.length();
        }
    }
}