from sys import argv
import csv

if len(argv) != 3:
    print("Input incorrect: python dna.py data.csv sequence.txt")

sequences = []

with open(argv[1], 'r') as csv_file:
    csv_reader = csv.reader(csv_file)
    
    data = list(csv_reader)
    
    sequences = data[0][1:len(data[0])]
    

# seqsFound is holds the values for amount of successive appearances of the to be found subsequence in the subsequence. This can hold multiple values.
# If a sequence is first found 5 times back to back, then 2 times, then once, etc. List will then be [5, 2, 1]. Take highest number and append to seqsFoundTotal

seqsFoundTotal = []    

file = open(argv[2], 'r')
txt = file.read()

for i in range(len(sequences)):
    seqCountTotal = 0
    seqCount = 0
    seqsFound = []
    index = txt.find(sequences[i])
    txtCopy = txt
    
    # While the to be found sequence is not found in the text, check if sequence next to sequence = sequence. If so, continue to count until not.
    # If not, append the count for that successive amount of sequences and reset count.
    # Splice the text each loop so that the found sequence is removed. Repeat until no more sequences.
    while index != -1:
        seqCount += 1
        
        # This checks whether two succesive sequence are the same or not. 
        if txtCopy[index:(index + len(sequences[i]))] != txtCopy[(index + len(sequences[i])):(index + 2 * len(sequences[i]))]:
            seqsFound.append(seqCount)
            seqCount = 0
        
        txtCopy = txtCopy[index+len(sequences[i]):len(txtCopy)]
        index = txtCopy.find(sequences[i])
         
    if seqsFound == []:
        seqsFoundTotal.append('0')
    else:
        seqCountTotal = str(max(seqsFound))    
        seqsFoundTotal.append(seqCountTotal)    


    
found = False
    
for i in range(1, len(data)):
    if data[i][1:len(data[i])] == seqsFoundTotal:
        print(data[i][0])
        found = True
        
if found == False:
    print("No match")