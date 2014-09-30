#!/bin/sh
# mp3test.sh
# Harlan Russell
# ECE 223, Fall 2014
#
# A simple shell script for MP3 to generate data for performance analysis
#
# either use chmod to make this file executable
#     prompt> chmod +x mp3test.sh
# or call the program sh
#     prompt> sh mp3test.sh
#
# There are five tests for:
#    Insertion Sort, Recursive Selection Sort, Iterative Selection Sort,
#    Merge Sort, and Quick Sort
#
# Each sort is run with random, ascending, and decending lists.
# 
# "sizes" is used to hold the size for each trial
#
# TEST 1 Insertion sort
echo "The date today is `date`"
echo "insertion sort with random list"
sizes="1000 5000 10000 15000 20000"
for listsize in $sizes ; do
   ./geninput $listsize 1 | ./lab3 1
done
echo "insertion sort with ascending list"
for listsize in $sizes ; do
   ./geninput $listsize 2 | ./lab3 1
done
echo "insertion sort with descending list"
for listsize in $sizes ; do
   ./geninput $listsize 3 | ./lab3 1
done
#
# TEST 2 Recursive selection sort
echo "recursive selection sort with random list"
for listsize in $sizes ; do
   ./geninput $listsize 1 | ./lab3 2
done
echo "iterative selection sort with ascending list"
for listsize in $sizes ; do
   ./geninput $listsize 2 | ./lab3 2
done
echo "iterative selection sort with descending list"
for listsize in $sizes ; do
   ./geninput $listsize 3 | ./lab3 2
done
#
# TEST 3 Iterative selection sort
echo "iterative selection sort with random list"
for listsize in $sizes ; do
   ./geninput $listsize 1 | ./lab3 3
done
echo "recursive selection sort with ascending list"
for listsize in $sizes ; do
   ./geninput $listsize 2 | ./lab3 3
done
echo "recursive selection sort with descending list"
for listsize in $sizes ; do
   ./geninput $listsize 3 | ./lab3 3
done
#
# TEST 4 Merge sort
echo "merge sort with random list"
sizes="20000 100000 200000 300000 400000"
for listsize in $sizes ; do
   ./geninput $listsize 1 | ./lab3 4
done
echo "merge sort with ascending list"
for listsize in $sizes ; do
   ./geninput $listsize 2 | ./lab3 4
done
echo "merge sort with descending list"
for listsize in $sizes ; do
   ./geninput $listsize 3 | ./lab3 4
done
#
# TEST 5 Merge sort
echo "quick sort with random list"
sizes="20000 100000 200000 300000 400000"
for listsize in $sizes ; do
   ./geninput $listsize 1 | ./lab3 5
done
echo "quick sort with ascending list"
for listsize in $sizes ; do
   ./geninput $listsize 2 | ./lab3 5
done
echo "quick sort with descending list"
for listsize in $sizes ; do
   ./geninput $listsize 3 | ./lab3 5
done
#
echo "end"

