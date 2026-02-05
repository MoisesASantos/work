#!/bin/bash

# Script de testes para minishell
# Execute com: ./test_minishell.sh

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

echo "======================================"
echo "INICIANDO TESTES DO MINISHELL"
echo "======================================"

# Compilar o projeto
echo -e "\n${YELLOW}[COMPILANDO]${NC}"
make re
if [ $? -ne 0 ]; then
    echo -e "${RED}Erro na compilação!${NC}"
    exit 1
fi
echo -e "${GREEN}Compilação bem-sucedida!${NC}"

# Função para testar comando
test_command() {
    local description="$1"
    local command="$2"
    echo -e "\n${YELLOW}[TESTE]${NC} $description"
    echo "Comando: $command"
    echo "$command" | ./minishell
    echo "Exit status minishell: $?"
    echo "$command" | bash
    echo "Exit status bash: $?"
}

echo -e "\n======================================"
echo "TESTES ESPECÍFICOS DE BUGS"
echo "======================================"

echo -e "\n${YELLOW}1. TESTE: heredoc sem comando (deve retornar 0)${NC}"
cat << 'EOF' > /tmp/test_heredoc.txt
<< EOF
test
EOF
echo $?
exit
EOF
echo "Execute manualmente: cat /tmp/test_heredoc.txt | ./minishell"

echo -e "\n${YELLOW}2. TESTE: exit \"\" (deve dar erro)${NC}"
echo 'exit ""' > /tmp/test_exit_empty.txt
echo "Execute manualmente: cat /tmp/test_exit_empty.txt | ./minishell; echo $?"

echo -e "\n${YELLOW}3. TESTE: exit -9223372036854775809 (overflow)${NC}"
echo 'exit -9223372036854775809' > /tmp/test_exit_overflow.txt
echo "Execute manualmente: cat /tmp/test_exit_overflow.txt | ./minishell; echo $?"

echo -e "\n${YELLOW}4. TESTE: ctrl-C deve retornar status 130${NC}"
echo "Execute manualmente: ./minishell, pressione Ctrl-C, depois 'echo \$?'"

echo -e "\n${YELLOW}5. TESTE: export '' deve retornar erro${NC}"
echo "export ''" > /tmp/test_export_empty.txt
echo "Execute manualmente: cat /tmp/test_export_empty.txt | ./minishell; echo $?"

echo -e "\n${YELLOW}6. TESTE: cd sem argumentos deve ir para HOME${NC}"
echo 'cd' > /tmp/test_cd_home.txt
echo 'pwd' >> /tmp/test_cd_home.txt
echo "Execute manualmente: cat /tmp/test_cd_home.txt | ./minishell"

echo -e "\n${YELLOW}7. TESTE: echo \$\"USER\"${NC}"
echo 'echo $"USER"' > /tmp/test_echo_dquote.txt
echo "Execute manualmente: cat /tmp/test_echo_dquote.txt | ./minishell"
echo "Bash: "
echo 'echo $"USER"' | bash

echo -e "\n${YELLOW}8. TESTE: echo \$'USER'${NC}"
echo "echo \$'USER'" > /tmp/test_echo_squote.txt
echo "Execute manualmente: cat /tmp/test_echo_squote.txt | ./minishell"
echo "Bash: "
echo "echo \$'USER'" | bash

echo -e "\n======================================"
echo "TESTES COMPLETOS - ECHO"
echo "======================================"

# Testes de echo
declare -a echo_tests=(
    "echo"
    "'echo'"
    "\"echo\""
    "\"'echo'\""
    "'\"echo\"'"
    "'echo '"
    "\" echo\""
    "echo edson finda"
    "echo 'edson              \"           ' finda"
    "echo \"                 edson   '                      \" finda"
    "echo '       edson             ' finda \""
    "echo \"       edson             \" finda '"
    "echo edson'finda'"
    "echo edson'finda'\"efinda\"luanda"
    "echo edson\"finda\"\"efinda\"42''"
    "echo edson'finda'\"efinda\"'                   '42"
    "echo -n"
    "echo -"
    "echo -nnnnnnnn -n -n -nnnn edsonn"
    "echo -nnnnnnnn -n -n - -nnnn edsonn"
    "echo -nnnnnnnn -n \"-n\" -nnnn edsonn"
    "echo -nnnnnnnn -n \"-n \" -nnnn edsonn"
    "echo -nnnnnnnn -n -nm -nnnn edsonn"
)

for cmd in "${echo_tests[@]}"; do
    echo -e "\n${YELLOW}Testando:${NC} $cmd"
    echo "$cmd" | ./minishell > /tmp/mini_out.txt 2>&1
    echo "$cmd" | bash > /tmp/bash_out.txt 2>&1
    if diff -q /tmp/mini_out.txt /tmp/bash_out.txt > /dev/null; then
        echo -e "${GREEN}✓ PASSOU${NC}"
    else
        echo -e "${RED}✗ FALHOU${NC}"
        echo "Minishell:"
        cat /tmp/mini_out.txt
        echo "Bash:"
        cat /tmp/bash_out.txt
    fi
done

echo -e "\n======================================"
echo "TESTES COMPLETOS - EXIT"
echo "======================================"

declare -a exit_tests=(
    "exit"
    "exit \"\""
    "exit -9223372036854775809"
    "exit -9223372036854775808"
    "exit -1"
    "exit 0"
    "exit 1"
    "exit 9223372036854775807"
    "exit 9223372036854775808"
    "exit a"
    "exit a a"
    "exit 1 1"
    "exit 1 a"
    "exit a 1"
    "exit 123a"
    "exit 123a a"
    "exit '                        +1'"
    "exit '                        -1'"
    "exit '                        +1 '"
    "exit '                        -1 '"
    "exit '                        +-1'"
)

for cmd in "${exit_tests[@]}"; do
    echo -e "\n${YELLOW}Testando:${NC} $cmd"
    echo "$cmd" | ./minishell > /tmp/mini_out.txt 2>&1
    mini_status=$?
    echo "$cmd" | bash > /tmp/bash_out.txt 2>&1
    bash_status=$?
    
    echo "Minishell exit status: $mini_status"
    echo "Bash exit status: $bash_status"
    
    if [ $mini_status -eq $bash_status ]; then
        echo -e "${GREEN}✓ STATUS CORRETO${NC}"
    else
        echo -e "${RED}✗ STATUS DIFERENTE${NC}"
    fi
done

echo -e "\n======================================"
echo "TESTES COMPLETOS - EXPORT"
echo "======================================"

declare -a export_tests=(
    "export"
    "export ''"
    "export a"
    "export a b c"
    "export a="
    "export a====="
    "export a=edso"
    "export a='edson finda'"
    "export a='edson \"          \" finda'"
    "export a -oi 9mm _obs"
)

for cmd in "${export_tests[@]}"; do
    echo -e "\n${YELLOW}Testando:${NC} $cmd"
    echo -e "$cmd\necho \$?\nexit" | ./minishell > /tmp/mini_out.txt 2>&1
    echo -e "$cmd\necho \$?\nexit" | bash > /tmp/bash_out.txt 2>&1
    echo "Comparando saídas..."
    diff /tmp/mini_out.txt /tmp/bash_out.txt
done

echo -e "\n======================================"
echo "TESTES COMPLETOS - CD"
echo "======================================"

echo -e "${YELLOW}Testando: cd (sem argumentos)${NC}"
echo -e "cd\npwd\nexit" | ./minishell
echo "Deve ir para $HOME"

echo -e "\n${YELLOW}Testando: cd .. .${NC}"
echo -e "cd .. .\necho \$?\nexit" | ./minishell

echo -e "\n======================================"
echo "TESTES COMPLETOS - VARIÁVEIS DE AMBIENTE"
echo "======================================"

declare -a env_tests=(
    "echo \"\$USER\""
    "echo \"\$USER\$USER\""
    "echo \"\$USER \""
    "echo \$\"USER\""
    "echo \"\$\"USER"
    "echo \$'USER'"
    "echo '\$USER'"
    "echo '\$'USER"
    "echo \$@"
    "echo \$@@"
    "echo \$@@@@"
    "echo \$"
    "echo \$fdasfwed32r43wr2rferfrefewe"
)

for cmd in "${env_tests[@]}"; do
    echo -e "\n${YELLOW}Testando:${NC} $cmd"
    echo "$cmd" | ./minishell > /tmp/mini_out.txt 2>&1
    echo "$cmd" | bash > /tmp/bash_out.txt 2>&1
    
    echo "Minishell:"
    cat /tmp/mini_out.txt
    echo "Bash:"
    cat /tmp/bash_out.txt
    
    if diff -q /tmp/mini_out.txt /tmp/bash_out.txt > /dev/null; then
        echo -e "${GREEN}✓ PASSOU${NC}"
    else
        echo -e "${RED}✗ FALHOU${NC}"
    fi
done

echo -e "\n======================================"
echo "TESTES DE MEMORY LEAKS"
echo "======================================"
echo -e "${YELLOW}Execute manualmente com valgrind:${NC}"
echo "valgrind --leak-check=full --show-leak-kinds=all ./minishell"

echo -e "\n======================================"
echo "TESTES FINALIZADOS"
echo "======================================"
