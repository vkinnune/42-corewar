# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    error_testing.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 21:49:05 by qnguyen           #+#    #+#              #
#    Updated: 2022/12/05 22:53:21 by qnguyen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

RED='\e[31m'
GREEN='\e[32m'
BLUE='\e[94m'
YELLOW='\e[93m'
NORMAL='\e[0m'

OUR_CORE=./corewar
TEST_CORE=./resources/vm_champs/corewar

OUR_ASM=./asm
TEST_ASM=./resources/vm_champs/asm

OUR_ERR=./scripts/our_err
TEST_ERR=./scripts/test_err

OUR_RESULT=./scripts/our_res
TEST_RESULT=./scripts/test_res

printf "What would you like?\n"
printf "\t$YELLOW[asm]$NORMAL?\n"
printf "\t$YELLOW[core]$NORMAL?\n"
printf "\tor me (⁄ ⁄•⁄ω⁄•⁄ ⁄)? $YELLOW[you]$NORMAL \n"

read -r test_type

2>${OUR_ERR}
2>${TEST_ERR}
2>${OUR_RESULT}
2>${TEST_RESULT}

if [[ ${test_type} == 'asm' ]]
then
	ERROR_DIR=./testchamp/error_asm/
elif [[ ${test_type} == 'core' ]]
then
	ERROR_DIR=./testchamp/error_core/
elif [[ ${test_type} == 'you' ]]
then
	printf "Hihi u naughty (ง ื▿ ื)ว\n"
	printf "\t$YELLOW[asm]$NORMAL?\n"
	printf "\t$YELLOW[core]$NORMAL?\n"
	read -r ERROR_DIR
else
	exit
fi

for FILE in ${ERROR_DIR}*
do
	if [[ ${test_type} == 'asm' ]]
	then
		${OUR_ASM} ${FILE} >> ${OUR_RESULT} 2>>${OUR_ERR}
		${TEST_ASM} ${FILE} >> ${TEST_RESULT} 2>${TEST_ERR}
	else
		${OUR_CORE} ${FILE} > ${OUR_RESULT} 2>>${OUR_ERR}
		${TEST_CORE} ${FILE} > ${TEST_RESULT} 2>>${TEST_ERR}
	fi
	echo ${FILE}
done

content=$(cat ${OUR_RESULT})
our_line_count=$(cat ${OUR_ERR} | wc -l)
if [[ ${test_type} == 'asm' ]]
then
	test_line_count=$(cat ${TEST_RESULT} | wc -l)
else
	test_line_count=$(cat ${TEST_ERR} | wc -l)
fi

if [[ ${content} != "" || ${our_line_count} != ${test_line_count} ]]
then
	printf "\n${RED}haha RIP (≧∇≦)ﾉ\n${NORMAL}"
	exit
else
	printf "${GREEN}Congratz (´• ω •\`) ♡ Errors are errors${NORMAL}\n"
	rm ${OUR_RESULT} ${TEST_RESULT}
fi
