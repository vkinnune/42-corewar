./corewar $1 $2 $3 $4 $5 > result
./resources/vm_champs/corewar $1 $2 $3 $4 $5> test_result
diff result test_result
