.name "moro"
.comment "I will moro you to death"

fork %50
sti r1, %:live, r2
#0b 64 01 1206 02
live:
	live %0
