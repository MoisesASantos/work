#!/bin/bash

# Script de testes individuais com valgrind
# Execute para testar um comando específico e verificar leaks

VALGRIND="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes"

echo "======================================"
echo "TESTES INDIVIDUAIS COM VALGRIND"
echo "======================================"

# Função para testar com valgrind
test_with_valgrind() {
    local description="$1"
    local command="$2"
    
    echo -e "\n=========================================="
    echo "TESTE: $description"
    echo "Comando: $command"
    echo "=========================================="
    
    echo "$command" | $VALGRIND ./minishell 2>&1 | tee /tmp/valgrind_output.txt
    
    # Verificar leaks na saída
    if grep -q "All heap blocks were freed" /tmp/valgrind_output.txt; then
        echo -e "\033[0;32m✓ SEM LEAKS\033[0m"
    elif grep -q "no leaks are possible" /tmp/valgrind_output.txt; then
        echo -e "\033[0;32m✓ SEM LEAKS\033[0m"
    else
        echo -e "\033[0;31m✗ POSSÍVEIS LEAKS DETECTADOS\033[0m"
        grep "definitely lost\|indirectly lost\|possibly lost" /tmp/valgrind_output.txt
    fi
    
    read -p "Pressione Enter para continuar..."
}

# Menu de testes
while true; do
    clear
    echo "======================================"
    echo "MENU DE TESTES COM VALGRIND"
    echo "======================================"
    echo "1.  Comando vazio"
    echo "2.  echo simples"
    echo "3.  echo com argumentos"
    echo "4.  exit"
    echo "5.  exit com número"
    echo "6.  exit com string vazia"
    echo "7.  exit com overflow"
    echo "8.  export"
    echo "9.  export com string vazia"
    echo "10. cd (sem args)"
    echo "11. cd .."
    echo "12. pwd"
    echo "13. env"
    echo "14. echo com variáveis"
    echo "15. echo \$\"USER\""
    echo "16. echo \$'USER'"
    echo "17. heredoc simples"
    echo "18. heredoc sem comando"
    echo "19. redirecionamento >"
    echo "20. redirecionamento <"
    echo "21. pipe simples"
    echo "22. unset"
    echo "23. Teste completo sequencial"
    echo "0.  Sair"
    echo "======================================"
    read -p "Escolha uma opção: " opcao
    
    case $opcao in
        1)
            test_with_valgrind "Comando vazio" $'exit'
            ;;
        2)
            test_with_valgrind "Echo simples" $'echo\nexit'
            ;;
        3)
            test_with_valgrind "Echo com argumentos" $'echo hello world\nexit'
            ;;
        4)
            test_with_valgrind "Exit sem argumentos" $'exit'
            ;;
        5)
            test_with_valgrind "Exit com número" $'exit 42'
            ;;
        6)
            test_with_valgrind "Exit com string vazia" $'exit ""\nexit'
            ;;
        7)
            test_with_valgrind "Exit com overflow" $'exit -9223372036854775809\nexit'
            ;;
        8)
            test_with_valgrind "Export" $'export\nexit'
            ;;
        9)
            test_with_valgrind "Export com string vazia" $'export \'\'\nexit'
            ;;
        10)
            test_with_valgrind "CD sem argumentos" $'cd\nexit'
            ;;
        11)
            test_with_valgrind "CD .." $'cd ..\nexit'
            ;;
        12)
            test_with_valgrind "PWD" $'pwd\nexit'
            ;;
        13)
            test_with_valgrind "ENV" $'env\nexit'
            ;;
        14)
            test_with_valgrind "Echo com variáveis" $'echo $USER\nexit'
            ;;
        15)
            test_with_valgrind "Echo \$\"USER\"" $'echo $"USER"\nexit'
            ;;
        16)
            test_with_valgrind "Echo \$'USER'" $'echo $\'USER\'\nexit'
            ;;
        17)
            test_with_valgrind "Heredoc simples" $'cat << EOF\ntest\nEOF\nexit'
            ;;
        18)
            test_with_valgrind "Heredoc sem comando" $'<< EOF\ntest\nEOF\nexit'
            ;;
        19)
            test_with_valgrind "Redirecionamento >" $'echo test > /tmp/test.txt\nexit'
            ;;
        20)
            test_with_valgrind "Redirecionamento <" $'cat < /etc/passwd\nexit'
            ;;
        21)
            test_with_valgrind "Pipe simples" $'echo test | cat\nexit'
            ;;
        22)
            test_with_valgrind "Unset" $'unset PATH\nexit'
            ;;
        23)
            echo "Executando teste sequencial..."
            echo "Teste 1/10: Comando vazio"
            test_with_valgrind "1. Comando vazio" $'exit'
            
            echo "Teste 2/10: Echo"
            test_with_valgrind "2. Echo" $'echo hello\nexit'
            
            echo "Teste 3/10: Echo com variáveis"
            test_with_valgrind "3. Echo com variáveis" $'echo $USER\nexit'
            
            echo "Teste 4/10: Export"
            test_with_valgrind "4. Export" $'export TEST=123\nexit'
            
            echo "Teste 5/10: CD"
            test_with_valgrind "5. CD" $'cd\nexit'
            
            echo "Teste 6/10: PWD"
            test_with_valgrind "6. PWD" $'pwd\nexit'
            
            echo "Teste 7/10: ENV"
            test_with_valgrind "7. ENV" $'env\nexit'
            
            echo "Teste 8/10: Unset"
            test_with_valgrind "8. Unset" $'unset TEST\nexit'
            
            echo "Teste 9/10: Redirecionamento"
            test_with_valgrind "9. Redirecionamento" $'echo test > /tmp/test.txt\nexit'
            
            echo "Teste 10/10: Pipe"
            test_with_valgrind "10. Pipe" $'echo test | cat\nexit'
            
            echo "======================================"
            echo "TESTE SEQUENCIAL COMPLETO"
            echo "======================================"
            read -p "Pressione Enter para continuar..."
            ;;
        0)
            echo "Saindo..."
            exit 0
            ;;
        *)
            echo "Opção inválida!"
            sleep 2
            ;;
    esac
done
