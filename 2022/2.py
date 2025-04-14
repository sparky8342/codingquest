#!/usr/bin/python3

numbers = []
with open('inputs/2.txt') as f:
    for line in f:
        numbers.append([int(x) for x in line.split()])
        
winning_numbers = {12, 48, 30, 95, 15, 55, 97} 
winnings = 0

for nums in numbers:
    matching = 0
    for n in nums:
        if n in winning_numbers:
            matching += 1
    if matching == 3:
        winnings += 1
    elif matching == 4:
        winnings += 10
    elif matching == 5:
        winnings += 100
    elif matching == 6:
        winnings += 1000

print(winnings)