#!/bin/bash

bubble_sort() {
    local arr=("${!1}")
    local len=${#arr[@]}
    for ((i = 0; i < len - 1; i++)); do
        for ((j = 0; j < len - i - 1; j++)); do
            if [ ${arr[j]} -gt ${arr[j + 1]} ]; then
                temp=${arr[j]}
                arr[j]=${arr[j + 1]}
                arr[j + 1]=$temp
            fi
            echo "Iteration: $i"
            echo "${arr[@]}"
        done
    done
    echo "${arr[@]}"
}

echo "Enter elements of array separated by spaces:"
read -a array
echo "Original array: ${array[@]}"
sorted_array=$(bubble_sort array[@])
echo "Sorted array: $sorted_array"
