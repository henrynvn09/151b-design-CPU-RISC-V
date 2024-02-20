while IFS= read -r i; do  
	./timeCompare.sh "$i"
done < list_files

