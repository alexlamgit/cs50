# Computes the approximate grade level needed to comprehend some text
import cs50


def main():

    # Calculate with the results of stuff...
    text = cs50.get_string("Text: ")

    # Again...
    words = numwords(text)

    # Again...
    letters_per100 = (numletters(text) * 100) / words
    sentences_per100 = (numsentences(text) * 100) / words

    # Again...
    index = round(0.0588 * letters_per100 - 0.296 * sentences_per100 - 15.8)

    # Done!
    if (index > 16):
        print("Grade 16+")
    # Done... again?
    elif (index < 1):
        print("Before Grade 1")
    # Ok done forreal.
    else:
        print(f"Grade {index}")

# Do stuff...


def numletters(t):
    numl = 0
    for i in range(len(t)):
        if t[i].isalpha():
            numl += 1
    return numl

# Do more stuff...


def numwords(t):
    numw = 0
    space_seen = True
    for i in range(len(t)):
        if t[i] != ' ' and space_seen:
            if t[i].isalpha():
                numw += 1
                space_seen = False
        elif t[i] == ' ':
            space_seen = True
    return numw

# Do more more stuff...


def numsentences(t):
    nums = 0
    punc_seen = True
    for i in range(len(t)):
        punc_check = t[i] != '!' or t[i] != '.' or t[i] != '?'
        if punc_check and punc_seen:
            if t[i].isalpha():
                nums += 1
                punc_seen = False
        elif t[i] == '!' or t[i] == '.' or t[i] == '?':
            punc_seen = True
    return nums


if __name__ == "__main__":
    main()

