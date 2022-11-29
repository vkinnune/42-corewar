./asm "$1.s"
hexdump "$1.cor" -vC > result
./casm "$1.s"
hexdump "$1.cor" -vC > c_result
diff result c_result
