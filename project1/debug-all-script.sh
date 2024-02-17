while IFS= read -r i; do  
	./testCompare.sh "$i"
done < list_files

