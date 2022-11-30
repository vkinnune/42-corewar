# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    apustaja.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/20 21:11:39 by qnguyen           #+#    #+#              #
#    Updated: 2022/11/30 22:13:36 by qnguyen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

RED='\e[31m'
GREEN='\e[32m'
BLUE='\e[94m'
YELLOW='\e[93m'
NORMAL='\e[0m'
OUR_CORE=./corewar
TEST_CORE=/Users/qnguyen/Workspace/Corewar/resources/vm_champs/corewar
CHAMP_DIR=./testchamp/

check_file()
{
	if [[ ! -f "$OUR_CORE"  ]]
	then
		echo "Where file?"
		exit
	elif [[ ! -f "$TEST_CORE" ]]
	then
		echo "Gotta have something to compare yours with, chief"
		exit
	fi
}

apu()
{
	count=0
	if [[ $file != "chill" ]]
	then
		printf "You got some champs in mind or u wanna chill and let me handle the stuff for ya?\n"
		printf "\t$YELLOW[champ_name]$NORMAL: input each champ one by one (hit $YELLOW'enter'$NORMAL when you've had enough $RED( •̀ ω •́ )$NORMAL\n"
		printf "\t$YELLOW\"chill\"$NORMAL: automatically run -v 4 FOREVER ψ(｀∇´)ψ\n"
		read -r file
	fi
	#not an elif
	if [[ "$file" == "chill" ]]
	then
		echo "Okei u lazy bum"
		for i in {0..3}
		do
			champ_num=$(find "$CHAMP_DIR" -type f -name "*.cor" | wc -l)
			random_num=$(jot -r 1 1 $champ_num)
			champs[$i]=$(find "$CHAMP_DIR" -type f -name "*.cor" | head -$((random_num)) | tail -1)
		done
		count=4
	else
		for i in {0..3}
		do
			file=$(echo "$file" | sed s/\'\//g | sed 's/\\/\//g')
			if [[ $file == '' ]]
			then
				break
			elif [[ ! -f "$file" ]]
			then
				echo "What kind of champion is this (ﾒ・ん・)？???"
				exit
			else
				champs[$i]=$file
				((count++))
			fi
			if [[ $i -lt 3 ]]
			then
				read -r file
			fi
		done
	fi

	if [[ $count -eq 0 ]]
	then
		printf "Me no see champ, me no do work $GREEN( っ´ω｀c)$NORMAL \n"
		exit
	fi

	############# SHOW TEST CHAMPS

	printf "Testing with:$GREEN\n"
	string=
	for ((i=0; i<${count}; i++))
	do
		string+="${champs[$i]} "
		echo "$(echo ${champs[$i]})"
	done
	printf "\n$NORMAL"

	flag=4
	test_v_flag
	check_run_type
}

test_v_flag()
{
	(time $OUR_CORE -v $flag $string > result) 2>>time_result
	(time $TEST_CORE -v $flag $string > test_result) 2>>test_timeresult

	diff=$(cmp result test_result)
	if [[ $diff != "" ]]
	then
		printf "\n${RED}haha RIP (≧∇≦)ﾉ\n${NORMAL}"
		printf "$diff\n"
		line=$(echo $diff | rev | cut -d ' ' -f 1 | rev)
		printf "${RED}Yours:  $(sed -n ${line}p result)\n"
		printf "${GREEN}Test's: $(sed -n ${line}p test_result)\n${NORMAL}"
		exit
	fi

	if [[ $flag == "4" ]]
	then
		printf "${GREEN}All of your instructions executed perfectly (and the printing too), me proud very (￣︶￣;)\n$NORMAL"
	fi
	runtime=$(tail -n 3 time_result | head -n 1 | cut -d '	' -f 2)
	printf "It took you $BLUE$runtime$NORMAL to run\n"
	test_runtime=$(tail -n 3 test_timeresult | head -n 1 | cut -d '	' -f 2)
	printf "It took that other one $BLUE$test_runtime$NORMAL\n"
	if [[ $runtime < $test_runtime ]]
	then
		printf "You fast af ${BLUE}>─=≡Σ((( つ•̀ω•́)つ\n\n$NORMAL"
	fi
}

check_run_type()
{
	if [[ $file == "chill" ]]
	then
		apu
	fi
	more_test
}

more_test()
{
	printf "\nYa wanna keep going bud?\n"
	printf "\t$YELLOW\"yes\"$NORMAL: run the rest of the flags\n"
	printf "\t$YELLOW[num]$NORMAL: run a certain -v flag\n"
	printf "\t$YELLOW\"rerun\"$NORMAL: compare different champs\n"
	printf "\t$YELLOW\"no\"$NORMAL: No :(\n"
	read flag
	if [[ $flag == "rerun" ]]
	then
		apu
	elif [[ $flag == "no" ]]
	then
		rm -f result test_result time_result test_timeresult
		exit
	elif [[ $flag == "yes" ]]
	then
		flag_num=( "3" "7" "15" )
		for i in "${flag_num[@]}"
		do
			flag=$i
			printf "Now testing -v $i\n"
			test_v_flag
		done
	else
		test_v_flag
	fi
	more_test
}

check_file
printf "Moro moro $GREEN╰(⸝⸝⸝´꒳\`⸝⸝⸝)╯$NORMAL\n"
declare -A champs
declare string
declare file
apu
