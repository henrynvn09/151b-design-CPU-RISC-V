while IFS= read -r i; do  
	./gshare_test.sh "$i"
done < allfiles-benchmarks.md

