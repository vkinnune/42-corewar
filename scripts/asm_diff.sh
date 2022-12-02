# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    asm_diff.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 22:44:04 by qnguyen           #+#    #+#              #
#    Updated: 2022/12/02 19:49:52 by qnguyen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OUR_ASM=./asm
TEST_ASM=/Users/qnguyen/Workspace/Corewar/resources/vm_champs/asm
CURRENT_DIR=./scripts
ASM_DIR=./testchamp/valid_asm

RED='\e[31m'
GREEN='\e[32m'
BLUE='\e[94m'
YELLOW='\e[93m'
NORMAL='\e[0m'

check_exisiting_asm()
{
	if [[ ! -f "$OUR_ASM"  ]]
	then
		printf "${RED}Sir, u gotta have an assembler to use our service (◠ ‿ ◠ ✿)${NORMAL}\n"
		exit
	elif [[ ! -f "$TEST_ASM" ]]
	then
		printf "${RED}Gib file for comparison nao （＞д＜）${NORMAL}\n"
		exit
	fi
}

get_program_type()
{
	if [[ $file != "surprise" ]]
	then
		printf "Do you have something in mind or you want me to surprise you Senpai (◕////◕)\n"
		printf "\t$YELLOW[asm_file]$NORMAL: You get to decide the asm file (¬_¬)\n"
		printf "\t$YELLOW\"surprise\"$NORMAL: Hihi I won't stop until you force me to Senpai ( •̀ ω •́ )\n"
		read -r file
	fi

	if [[ $file == "surprise" ]]
	then
		random_num=$(find "$ASM_DIR" -type f -name "*.s"  | wc -l | cut -d ' ' -f 8 | xargs jot -r 1 1)
		champ=$(find "$ASM_DIR" -type f -name "*.s" | head -$((random_num)) | tail -1)
		printf "\tI gib u\n$GREEN${champ} ( ಠ ‿ <) $NORMAL\n"
	else
		champ=$(echo ${file} | sed s/\'//g)
	fi
	test_asm
}

test_asm()
{
	cor_champ=$(echo ${champ} | sed 's/\.s/\.cor/g')
	${TEST_ASM} "${champ}"
	if [[ -f "${cor_champ}" ]]
	then
		hexdump -vC "${cor_champ}" > ${CURRENT_DIR}/test_result
		rm ${cor_champ}
	fi
	${OUR_ASM} "${champ}"
	if [[ -f "${cor_champ}" ]]
	then
		hexdump -vC "${cor_champ}" > ${CURRENT_DIR}/result
		rm ${cor_champ}
	fi
	differs=$(diff ${CURRENT_DIR}/result ${CURRENT_DIR}/test_result)
	if [[ $differs == "" ]]
	then
		printf "${GREEN}Hihi me see no diff ( っ´ω｀c)${NORMAL}\n"
		rm ${CURRENT_DIR}/result
		rm ${CURRENT_DIR}/test_result
	else
		printf "${RED}Oh oh senpaii~ made a big boo boo (p≧w≦q) me go away nao \n${NORMAL}"
		printf "$differs\n"
		exit
	fi
	check_run_type
}

check_run_type()
{
	if [[ ${file} == "surprise" ]]
	then
		sleep 1
		get_program_type
	else
		check_rerun
	fi
}

check_rerun()
{
	printf "\nI still have energy senpai, shall we go for another round? ${GREEN}(⁄ ⁄•⁄ω⁄•⁄ ⁄)⁄${NORMAL}\n"
	printf "\t$YELLOW\"yes\"$NORMAL: We do it one more time hihi ${GREEN}(´,,•ω•,,)♡${NORMAL}\n"
	printf "\t$YELLOW\"no\"$NORMAL: No ${GREEN}(╯︵╰,)${NORMAL}\n"
	read flag
	if [[ ${flag} == 'yes' ]]
	then
		get_program_type
	else
		exit
	fi
}

check_exisiting_asm
get_program_type
test_asm
