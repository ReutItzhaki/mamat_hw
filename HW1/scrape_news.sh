#!/bin/bash

site="https://www.ynetnews.com/category/3082"
data=$(wget --no-check-certificate -O - $site 2>/dev/null)

articles=$(echo "$data" | 
grep -oP "https://www.ynetnews.com/article/[0-9a-zA-Z]+" | sort | uniq )
echo "$articles" | wc -l > results.csv 

output=""
num=("" "" "" "")
(( counter=0 ))
for art in $articles; do
	info=$(wget --no-check-certificate -O - $art 2>/dev/null)
	for name in "Netanyahu" "Gantz" "Bennett" "Peretz"; do
		num[$counter]=$(echo "$info" | grep -oP $name | wc -w )
        (( counter++ ))	
	done
	if [[ "$num" -eq "0000" ]]; then
	  output="$art, -"
	else
      output="$art, Netanyahu, ${num[0]}, Gantz, \
      ${num[1]}, Bennett, ${num[2]}, Peretz, ${num[3]}"
	fi

	echo "$output" >> results.csv
	(( counter=0 ))
	num=("" "" "" "")  
done
