# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    asm_apu.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 22:44:04 by qnguyen           #+#    #+#              #
#    Updated: 2022/12/05 21:47:36 by qnguyen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OUR_ASM=./asm
TEST_ASM=./resources/vm_champs/asm
CURRENT_DIR=./scripts
ASM_DIR=./testchamp/valid_asm

RED='\e[31m'
GREEN='\e[32m'
BLUE='\e[94m'
YELLOW='\e[93m'
NORMAL='\e[0m'

RESULT_FILE=${CURRENT_DIR}/asm_result
TEST_RESULT=${CURRENT_DIR}/asm_test_result

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
		if [[ ${OSTYPE} == "darwin18" ]]
		then
			random_num="$(find "$ASM_DIR" -type f -name "*.s" | wc -l | xargs jot -r 1 1)"
			champ="$(find "$ASM_DIR" -type f -name "*.s" | head -${random_num} | tail -1)"
		else
			champ="$(find "$ASM_DIR" -type f -name "*.s" | shuf -n 1)"
		fi
		printf "\tI gib u\n$GREEN${champ} ( ಠ ‿ <) $NORMAL\n"
	else
		champ=$(echo ${file} | sed s/\'//g)
	fi
}

test_asm()
{
	cor_champ=$(echo ${champ} | sed 's/\.s/\.cor/g')
	${TEST_ASM} "${champ}"
	if [[ -f "${cor_champ}" ]]
	then
		hexdump -vC "${cor_champ}" > ${TEST_RESULT}
		rm ${cor_champ}
	fi
	${OUR_ASM} "${champ}"
	if [[ -f "${cor_champ}" ]]
	then
		hexdump -vC "${cor_champ}" > ${RESULT_FILE}
		rm ${cor_champ}
	fi
	differs=$(diff ${RESULT_FILE} ${TEST_RESULT})
	if [[ $differs == "" ]]
	then
		printf "${GREEN}Hihi me see no diff ( っ´ω｀c)${NORMAL}\n"
		rm ${RESULT_FILE} ${TEST_RESULT}
	else
		printf "${RED}Oh oh senpaii~ made a big boo boo (p≧w≦q) me go away nao \n${NORMAL}"
		printf "$differs\n"
		exit
	fi
}

check_rerun()
{
	printf "\nI still have energy senpai, shall we go for another round? ${GREEN}(⁄ ⁄•⁄ω⁄•⁄ ⁄)⁄${NORMAL}\n"
	printf "\t$YELLOW\"yes\"$NORMAL: We do it one more time hihi ${GREEN}(´,,•ω•,,)♡${NORMAL}\n"
	printf "\t$YELLOW\"no\"$NORMAL: No ${GREEN}(╯︵╰,)${NORMAL}\n"
	read flag
	if [[ ${flag} != 'yes' ]]
	then
		exit
	fi
}

check_exisiting_asm
get_program_type
test_asm
while [[ 1 == 1 ]]
do
	if [[ ${file} != "surprise" ]]
	then
		check_rerun
	fi
	get_program_type
	test_asm
done
