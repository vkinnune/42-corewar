#!/bin/zsh

RED='\033[0;31m'
NC='\033[0m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'

READ_CONT () {
	read -s -k "?Press any key to continue"
	echo ""
	tput cuu1
	tput el
}

RET_YN () {
	while true
	do
		read -s -k "REPLY"
		if [ ${REPLY} = "y" ]
		then
			return 0
		elif [ ${REPLY} = "n" ]
		then
			return 1
		fi
	done
}

READ_YN () {
	if RET_YN
	then
		tput rc && tput cd
		echo "${GREEN}YES${NC}"
	else
		tput rc && tput cd
		echo "${RED}NO${NC}"
	fi
}

RUN_CMD () {
	PROMPT=$1
	CMD=$2
	tput sc
	echo ${PROMPT}
	eval ${CMD}
	READ_YN
}

NORM_MANUAL () {
	tput sc
	echo "${YELLOW}Would you like to see the norminette for yourself? [y/n]${NC}"
	if RET_YN
	then
		norminette ../
			echo "${YELLOW}Are you satisfied? [y/n]${NC}"
			if RET_YN
			then
				tput clear
				echo "- Evaluator is satisfied with the norme: ${GREEN}YES${NC}"
			else
				tput clear
				echo "- Evaluator is satisfied with the norme: ${RED}NO, BOOHOO${NC}"
			fi
	else
		tput rc && tput cd
	fi
}

NORMINETTE () {
	tput sc
	echo "${YELLOW}Auto-testing 'norminette ../'${NC}"
	res=$(norminette ../)
	tput rc && tput cd
	if echo ${res} | grep -q 'Error'
	then
		echo "${RED}NO${NC}"
	else
		echo "${GREEN}OK${NC}"
	fi
	NORM_MANUAL
}

tput clear
echo "\n${YELLOW}Let's stop these mother@#$%in snakes on this mother@#$%in helltrain!\n${NC}"

echo "Welcome to the Corewar test, let's begin with the basics (make sure you have run make already...):"
READ_CONT

echo -n "- Something was submitted: "
RUN_CMD "\n${YELLOW}Running 'ls' from root, can you see stuff? [y/n]${NC}" "ls -al ../"
echo -n "- Author file repository: "
RUN_CMD "\n${YELLOW}Running 'ls' from root, can you see the author file? [y/n]${NC}" "ls -al ../"
echo -n "- Correct author file contents: "
RUN_CMD "\n${YELLOW}Printing author file with 'cat -e', is if formatted correctly? [y/n]${NC}" "cat -e ../author"
echo -n "- Norm is OK: "
NORMINETTE
echo -n "- The whole group is present: "
RUN_CMD "\n${YELLOW}Check, is everyone there? [y/n]${NC}"
echo "\nOKAY! Basics are done!\n"
READ_CONT

echo "TLDR: Take your time, don't be a dick, do the whole defence, you should both leave this grown."
echo "**********************************************************************************************"
echo "THE ASM"
echo "**********************************************************************************************"
echo "${YELLOW}We are about to test against valid '.s' files. We will check for:"
echo "- the .cor file is created"
echo "- bytecode correctness against the given school's asm"
echo "If you see any red, then there's something wrong"
echo "Otherwise, our asm might ocassionally print 'warning' for some .s files, that's a bonus feature of ours"
echo "Are you ready? [y/n]${NC}"
if RET_YN
then
	./asm/valid/test_valid.sh hive_asm
else
	echo "okay..."
fi

echo "${YELLOW}\nHow was it? did everything pass? [y/n]${NC}"
if RET_YN
then
	tput clear
	echo "- Generated .cor and bytecode is OK: ${GREEN}YES${NC}"
else
	tput clear
	echo "- Generated .cor and bytecode is OK: ${RED}NO${NC}"
fi

echo "${YELLOW}Time for error management tests, we have many."
echo "Are you ready? [y/n]${NC}"
if RET_YN
then
	./asm/invalid/test_invalid.sh
else
	echo "okay..."
fi

echo "${YELLOW}Here is how we deal with the following errors mentioned in the eval:"
READ_CONT
echo "- Unknown instruction:"
./../asm asm/invalid/bad_statement/unknown_instr.s
echo "${YELLOW}- Wrong argument number for an instruction:"
echo "${YELLOW}-   Too few arguments:"
./../asm asm/invalid/bad_statement/insufficient_args.s
echo "${YELLOW}-   Too many arguments:"
./../asm asm/invalid/bad_statement/too_many_args.s
echo "${YELLOW}- Wrong type of argument for an instruction:"
./../asm asm/invalid/bad_statement/incorrect_args.s
echo "${YELLOW}- Wrong character in a label:"
./../asm asm/invalid/bad_labels/illegal_label_char.s
echo "${YELLOW}- Reference to an unexisting label from a direct or indirect:"
echo "${YELLOW}-   One unexiisting label:"
./../asm asm/invalid/bad_labels/one_outstanding_refs.s
echo "${YELLOW}-   Multiple unexiisting labels:"
./../asm asm/invalid/bad_labels/multiple_outstanding_refs.s

echo "${YELLOW}\nHow was it? did everything pass? [y/n]${NC}"
if RET_YN
then
	tput clear
	echo "- Error management is OK: ${GREEN}YES${NC}"
else
	tput clear
	echo "- Error management is OK: ${RED}NO${NC}"
fi

echo "**********************************************************************************************"
echo "THE VM"
echo "**********************************************************************************************"
echo "${YELLOW}Lets enter the ARENAAA!!!"
echo "Are you ready to test the Virtual Machine? This will be lot's of fun."
echo "Kick back, relax, and have a chat. It'll take about an hour...[y/n]${NC}"
if RET_YN
then
	cd corewar
	./run_tests.sh
else
	echo "okay..."
fi
