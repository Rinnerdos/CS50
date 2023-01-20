from sys import argv
from cs50 import SQL
import csv

if len(argv) != 2:
    exit("Input incorrect. Correct form: python import.py characters.csv")
    
db = SQL("sqlite:///students.db")
    
with open(argv[1], 'r') as csv_file:
    csv_reader = csv.reader(csv_file)
    
    data = list(csv_reader)
    
    for i in range(1, len(data)):
        splitted = data[i][0].split()
        
        if len(splitted) == 2:
            splitted.insert(1, None)
       
        data[i][0] = splitted[0]
        
        for j in range(1, 3):
            data[i].insert(j, splitted[j])
        
        db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                   data[i][0], data[i][1], data[i][2], data[i][3], data[i][4])

