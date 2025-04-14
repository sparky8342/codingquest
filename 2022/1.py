#!/usr/bin/python3

def check_avg(sum):
	avg = sum // 60
	if avg < 1500 or avg > 1600:
		return 1
	else:
		return 0

with open('inputs/1.txt') as f:
	numbers = [int(i) for i in f.readlines()]
	
sum = 0
for i in range(60):
	sum += numbers[i]

seconds = check_avg(sum)

for i in range(60, len(numbers)):
	sum = sum + numbers[i] - numbers[i - 60]	
	seconds += check_avg(sum)

print(seconds)