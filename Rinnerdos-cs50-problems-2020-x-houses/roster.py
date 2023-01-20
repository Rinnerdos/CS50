from sys import argv
from cs50 import SQL

if len(argv) != 2:
    exit("Input incorrect. Correct form: python roster.py House")
    
db = SQL("sqlite:///students.db")

students = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", argv[1])

for i in range(len(students)):
    for key in students[i]:
        if students[i][key] == None:
            continue

        if students[i][key] == students[i]["last"]:
            print(f"{students[i][key]}, born ", end="")
        elif students[i][key] == students[i]["birth"]: 
            print(f"{students[i][key]}", end="")
        else:
            print(f"{students[i][key]} ", end="")
            
    print()