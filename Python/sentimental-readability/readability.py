from cs50 import get_string


def Main():
    # Gets input from user
    text = get_string("Text: ")

    # Calls functions to count letters, words, sentences and do the math, respectively
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    index = check_index(letters, words, sentences)

    result(index)


# Counts letters by iterating through text incrementing count every time it finds a letter
def count_letters(text):
    count = 0
    for c in text:
        if c.isalpha():
            count += 1
    return count


# Counts words by iterating through text incrementing count every time it finds a space
def count_words(text):
    count = 0
    for c in text:
        if c == " ":
            count += 1
    # There's no space after the last word, so we add one after the text is finished
    count += 1
    return count


# Counts sentences by iterating through text incrementing count every time it finds a dot, question or exclamation mark
def count_sentences(text):
    count = 0
    for c in text:
        if c == "!" or c == "." or c == "?":
            count += 1
    return count


# Does the math and returns index
def check_index(letters, words, sentences):
    avg_letters = (letters / words) * 100
    avg_sentences = (sentences / words) * 100

    result = ((0.0588 * avg_letters) - (0.296 * avg_sentences) - 15.8)

    index = round(result)

    return index


# Prints results
def result(index):
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


Main()