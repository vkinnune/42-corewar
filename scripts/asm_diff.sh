# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    asm_diff.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 22:44:04 by qnguyen           #+#    #+#              #
#    Updated: 2022/11/30 22:44:33 by qnguyen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OUR_ASM=./asm
TEST_ASM=./c_asm
CURRENT_DIR=./scripts

RED='\e[31m'
GREEN='\e[32m'
BLUE='\e[94m'
YELLOW='\e[93m'
NORMAL='\e[0m'

# if [[ ! -f "$OUR_ASM"  ]]
# then
# 	echo "Where file?"
# 	exit
# elif [[ ! -f "$TEST_ASM" ]]
# then
# 	echo "Gotta have something to compare yours with, chief"
# 	exit
# fi

$OUR_ASM "$1.s"
hexdump "$1.cor" -vC > $CURRENT_DIR/result
$TEST_ASM "$1.s"
hexdump "$1.cor" -vC > $CURRENT_DIR/test_result
differs=$(diff $CURRENT_DIR/result $CURRENT_DIR/test_result)
if [[ $differs == "" ]];
then
	printf "${GREEN}hihi me see no diff ( っ´ω｀c) me go away nao ${NORMAL}\n"
	rm $CURRENT_DIR/result
	rm $CURRENT_DIR/test_result
else
	printf "${RED}oh oh soomeone made a big boo boo (p≧w≦q)\n${NORMAL}"
	printf "$differs\n"
fi
