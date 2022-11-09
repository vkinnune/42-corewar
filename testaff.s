.name "testaff"
.comment "I will test aff you to death"
	
live:	ld %87, r2
		ld %73, r3
		ld %78, r4
		aff r2
		aff r3
		aff r4
		zjmp %:live
