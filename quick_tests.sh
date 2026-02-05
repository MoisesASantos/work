#!/bin/bash

# Testes rápidos - copie e cole no terminal para testar bugs específicos

echo "======================================"
echo "TESTES RÁPIDOS DOS BUGS"
echo "======================================"

echo -e "\n1. HEREDOC SEM COMANDO (deve retornar status 0)"
echo "Teste:"
cat << 'EOF' | ./minishell
<< END
test line 1
test line 2
END
echo $?
exit
EOF
echo "Status esperado: 0"

echo -e "\n2. EXIT COM STRING VAZIA (deve retornar erro)"
echo "Teste:"
echo 'exit ""' | ./minishell
echo "Status: $?"
echo "Status esperado: 2"

echo -e "\n3. EXIT COM UNDERFLOW (deve retornar erro)"
echo "Teste:"
echo 'exit -9223372036854775809' | ./minishell
echo "Status: $?"
echo "Status esperado: 2"

echo -e "\n4. EXIT COM LIMITE MÍNIMO VÁLIDO (deve funcionar)"
echo "Teste:"
echo 'exit -9223372036854775808' | ./minishell
echo "Status: $?"
echo "Status esperado: 0"

echo -e "\n5. EXIT COM LIMITE MÁXIMO VÁLIDO (deve funcionar)"
echo "Teste:"
echo 'exit 9223372036854775807' | ./minishell
echo "Status: $?"
echo "Status esperado: 255"

echo -e "\n6. EXIT COM OVERFLOW (deve retornar erro)"
echo "Teste:"
echo 'exit 9223372036854775808' | ./minishell
echo "Status: $?"
echo "Status esperado: 2"

echo -e "\n7. EXPORT COM STRING VAZIA (deve retornar erro)"
echo "Teste:"
cat << 'EOF' | ./minishell
export ''
echo $?
exit
EOF
echo "Status esperado: 1"

echo -e "\n8. CD SEM ARGUMENTOS (deve ir para HOME)"
echo "Teste:"
cat << 'EOF' | ./minishell
cd
pwd
exit
EOF
echo "Deve mostrar: $HOME"
echo "HOME atual: $HOME"

echo -e "\n9. ECHO \$\"USER\" (deve imprimir literal \$USER)"
echo "Teste Bash:"
bash -c 'echo $"USER"'
echo "Teste Minishell:"
echo 'echo $"USER"' | ./minishell | grep -v "minishell"
echo "Devem ser iguais"

echo -e "\n10. ECHO \$'USER' (deve imprimir literal \$USER)"
echo "Teste Bash:"
bash -c "echo \$'USER'"
echo "Teste Minishell:"
echo "echo \$'USER'" | ./minishell | grep -v "minishell"
echo "Devem ser iguais"

echo -e "\n11. CTRL-C STATUS"
echo "Teste manual:"
echo "./minishell"
echo "Pressione Ctrl-C"
echo "echo \$?"
echo "Status esperado: 130"

echo -e "\n======================================"
echo "TESTES COMPLETOS DE EXIT"
echo "======================================"

declare -a exit_tests=(
    "exit"
    'exit ""'
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
)

for cmd in "${exit_tests[@]}"; do
    echo -e "\nTestando: $cmd"
    echo "$cmd" | ./minishell > /dev/null 2>&1
    mini_status=$?
    echo "$cmd" | bash > /dev/null 2>&1
    bash_status=$?
    
    if [ $mini_status -eq $bash_status ]; then
        echo "✓ Status correto: $mini_status"
    else
        echo "✗ Status diferente - Minishell: $mini_status, Bash: $bash_status"
    fi
done

echo -e "\n======================================"
echo "TESTES DE VARIÁVEIS DE AMBIENTE"
echo "======================================"

declare -a env_tests=(
    'echo "$USER"'
    'echo "$USER$USER"'
    'echo "$USER "'
    'echo $"USER"'
    'echo "$"USER'
    "echo \$'USER'"
    "echo '\$USER'"
    "echo '\$'USER"
    'echo $@'
    'echo $@@'
    'echo $'
)

for cmd in "${env_tests[@]}"; do
    echo -e "\nTestando: $cmd"
    echo "Bash:"
    eval "echo \"$cmd\"" | bash 2>/dev/null || echo "(erro no bash)"
    echo "Minishell:"
    echo "$cmd" | ./minishell 2>/dev/null | grep -v "minishell" || echo "(erro no minishell)"
done

echo -e "\n======================================"
echo "COMPARAÇÃO COMPLETA ECHO"
echo "======================================"

declare -a echo_commands=(
    "echo"
    "echo -n"
    "echo -n hello"
    "echo -nnn hello"
    "echo -n -n -n hello"
    'echo "hello world"'
    "echo 'hello world'"
    'echo "hello" world'
    "echo 'hello' world"
    'echo hello"world"'
    "echo hello'world'"
    'echo "$USER"'
    "echo '\$USER'"
    'echo -nnnnnnnn -n -n -nnnn edsonn'
)

for cmd in "${echo_commands[@]}"; do
    echo -e "\n----------------------------------------"
    echo "Comando: $cmd"
    echo "Bash:"
    eval "$cmd"
    echo "Minishell:"
    echo "$cmd" | ./minishell | grep -v "minishell"
done

echo -e "\n======================================"
echo "FIM DOS TESTES"
echo "======================================"
