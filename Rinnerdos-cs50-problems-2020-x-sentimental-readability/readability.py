from cs50 import get_string


def main():
    text = get_string("Text: \n")

    wordcount = 0
    
    L = (100 * count_letters(text) / (count_words(text)))
    S = (100 * count_sentences(text) / (count_words(text)))
    index = 0.0588 * L - 0.296 * S - 15.8
    
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")
      
      
def is_punctuation(char):
    if char == '?' or char == '.' or char == '!':
        return True
    else:
        return False
        

def is_letter(char):
    if 64 < ord(char) < 91 or 96 < ord(char) < 123 or char == "'" or char == '-':
        return True
    else:
        return False
        

def count_letters(text):
    letterCount = 0
    
    for char in text:
        if is_letter(char):
            letterCount += 1
        if ord(char) == 45 or ord(char) == 39:
            letterCount -= 1
        
    return letterCount
    
    
def count_words(text):
    wordCount = 0
    
    for i in range(len(text)):
        if is_letter(text[i]) and not is_letter(text[i + 1]):
            wordCount += 1
            
    return wordCount
    
    
def count_sentences(text):
    sentenceCount = 0
    
    for i in range(len(text)):
        if is_letter(text[i]) and is_punctuation(text[i + 1]):
            sentenceCount += 1
            
    return sentenceCount
    
    
main()