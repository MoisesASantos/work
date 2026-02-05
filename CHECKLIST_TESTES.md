# Checklist Completo de Testes do Minishell

## ✅ Compile
- [ ] Verificar compilador usado
- [ ] Verificar flags: `-Wall -Wextra -Werror`
- [ ] Verificar que não há relink desnecessário
- [ ] Verificar targets mandatórios: `all`, `clean`, `fclean`, `re`

## ✅ Simple Command & Global Variables
- [ ] `/bin/ls` - comando com caminho absoluto
- [ ] `/bin/clear` - outro comando com caminho absoluto
- [ ] Verificar variáveis globais (apenas número do sinal)
- [ ] `""` ou `''` - comando vazio
- [ ] Linha com apenas espaços ou tabs → não deve ser guardada no histórico
- [ ] **Sair e verificar leak com valgrind**

## ✅ Arguments
- [ ] `/bin/ls -l` - comando com opções
- [ ] `/bin/ls -la /tmp` - comando com opções e argumentos
- [ ] **Sair e verificar leak**

## ✅ echo
Comparar tudo com bash:
- [ ] `echo`
- [ ] `'echo'`
- [ ] `"echo"`
- [ ] `"'echo'"`
- [ ] `'"echo"'`
- [ ] `'echo '`
- [ ] `" echo"`
- [ ] `echo edson finda`
- [ ] `echo 'edson              "           ' finda`
- [ ] `echo "                 edson   '                      " finda`
- [ ] `echo '       edson             ' finda "`
- [ ] `echo "       edson             " finda '`
- [ ] `echo edson'finda'`
- [ ] `echo edson'finda'"efinda"luanda`
- [ ] `echo edson"finda""efinda"42''`
- [ ] `echo edson'finda'"efinda"'                   '42`
- [ ] `echo -n`
- [ ] `echo -`
- [ ] `echo -nnnnnnnn -n -n -nnnn edsonn`
- [ ] `echo -nnnnnnnn -n -n - -nnnn edsonn`
- [ ] `echo -nnnnnnnn -n "-n" -nnnn edsonn`
- [ ] `echo -nnnnnnnn -n "-n " -nnnn edsonn`
- [ ] `echo -nnnnnnnn -n -nm -nnnn edsonn`
- [ ] **Sair e verificar leak**

## ✅ exit
Comparar com bash e verificar exit code com `echo $?`:
- [ ] `exit` → deve sair com código 0
- [ ] `exit ""` → **ERRO - argumento numérico inválido, código 2**
- [ ] `exit -9223372036854775809` → **ERRO - overflow, código 2**
- [ ] `exit -9223372036854775808` → código 0 (LONG_MIN válido)
- [ ] `exit -1` → código 255
- [ ] `exit 0` → código 0
- [ ] `exit 1` → código 1
- [ ] `exit 9223372036854775807` → código 255 (LONG_MAX válido)
- [ ] `exit 9223372036854775808` → **ERRO - overflow, código 2**
- [ ] `exit a` → ERRO - argumento não numérico, código 2
- [ ] `exit a a` → ERRO - muitos argumentos, código 1
- [ ] `exit 1 1` → ERRO - muitos argumentos, código 1
- [ ] `exit 1 a` → ERRO - muitos argumentos, código 1
- [ ] `exit a 1` → ERRO - muitos argumentos, código 1
- [ ] `exit 123a` → ERRO - argumento não numérico, código 2
- [ ] `exit 123a a` → ERRO - muitos argumentos, código 1
- [ ] `exit '                        +1'` → código 1
- [ ] `exit '                        -1'` → código 255
- [ ] `exit '                        +1 '` → código 1
- [ ] `exit '                        -1 '` → código 255
- [ ] `exit '                        +-1'` → ERRO - argumento não numérico, código 2
- [ ] **Sair e verificar leak**

## ✅ Return Value of a Process
- [ ] Testar `echo $?` após cada comando executado
- [ ] Comparar com bash
- [ ] **Sair e verificar leak**

## ✅ Signals
- [ ] `Ctrl-C` → deve limpar linha, nova prompt, `echo $?` deve retornar **130**
- [ ] `Ctrl-D` → deve sair do minishell
- [ ] `Ctrl-\` → não deve fazer nada
- [ ] **Sair e verificar leak**

## ✅ Double Quotes
Comparar com bash (pipe ou redir dentro de aspas = argumento):
- [ ] `echo "cat lol.c | cat > lol.c"`
- [ ] `echo something '>' aaa`
- [ ] `echo something '|' cat`
- [ ] `cat ""`
- [ ] **Sair e verificar leak**

## ✅ Single Quotes
Comparar com bash (sem expansão dentro de aspas simples):
- [ ] `echo '$USER'` → deve imprimir `$USER`
- [ ] `echo '$'` → deve imprimir `$`
- [ ] `echo '$ '` → deve imprimir `$ `
- [ ] `echo ' $'` → deve imprimir ` $`
- [ ] `cat ''` → erro de arquivo não encontrado
- [ ] **Sair e verificar leak**

## ✅ env
- [ ] `env` → deve listar todas as variáveis
- [ ] `env 42` → erro: muitos argumentos
- [ ] **Sair e verificar leak**

## ✅ export
Comparar com bash:
- [ ] `export` → deve listar todas as variáveis exportadas
- [ ] `export ''` → **ERRO - identificador inválido, código 1**
- [ ] `export a` → depois `echo $a` (deve estar vazio)
- [ ] `export a b c` → criar 3 variáveis
- [ ] `export a=` → `a` com valor vazio
- [ ] `export a=====` → `a` com valor `====`
- [ ] `export a=edso` → depois `echo $a` (deve mostrar `edso`)
- [ ] `export a='edson finda'` → depois `echo $a`
- [ ] `export a='edson "          " finda'` → depois `echo $a`
- [ ] `export a -oi 9mm _obs` → erro no `-oi` e `9mm`, sucesso em `a` e `_obs`
- [ ] **Sair e verificar leak**

## ✅ unset
- [ ] `unset` → sem efeito
- [ ] `unset a b c` → remover variáveis existentes
- [ ] `unset a b c` → tentar remover variáveis inexistentes
- [ ] `unset a b c` → apenas `b` existe
- [ ] `unset a b c` → apenas `b` não existe
- [ ] `unset PWD OLDPWD` → depois `cd` e `env` (devem ser recriadas)
- [ ] **Sair e verificar leak**

## ✅ cd
- [ ] `cd` → **deve ir para $HOME**
- [ ] `cd pasta_existente pasta_existente` → erro: muitos argumentos
- [ ] `cd ..` → subir um nível
- [ ] `cd .` → ficar no mesmo diretório
- [ ] `cd pasta_existente` → depois `env` (verificar PWD e OLDPWD)
- [ ] `cd pasta_existente_sem_permissão` → erro de permissão
- [ ] `cd pasta_inexistente` → erro: diretório não existe
- [ ] **Sair e verificar leak**

## ✅ pwd
- [ ] `pwd` → mostrar diretório atual
- [ ] `pwd sss` → ignorar argumentos extras
- [ ] **Sair e verificar leak**

## ✅ Relative Path
- [ ] `ls` → listar diretório atual
- [ ] `ls -la` → com opções
- [ ] `touch /tmp/test.txt` → criar arquivo
- [ ] `cat /tmp/test.txt` → ler arquivo
- [ ] `wc -l arquivo.txt` → contar linhas
- [ ] **Sair e verificar leak**

## ✅ Environment Path
- [ ] Comandos sem caminho completo devem funcionar
- [ ] Testar com `ls`, `cat`, `echo`, etc.
- [ ] Testar após `unset PATH` → deve dar erro
- [ ] **Sair e verificar leak**

## ✅ Redirection
### Sem arquivo:
- [ ] `echo edson >` → erro: esperado arquivo
- [ ] `< file_existente` → erro ou executar sem comando
- [ ] `<<` → erro: esperado delimitador

### Linhas desorganizadas:
- [ ] `echo edson > file baptista finda` → `baptista finda` são argumentos
- [ ] `echo edson > a baptista > b finda > c` → múltiplos redirs

### Sem permissão/pastas:
- [ ] `echo test > /root/file` → erro de permissão
- [ ] `echo test > /tmp` → erro: é um diretório

### Heredoc (`<<`):
- [ ] `<< EOF` seguido de texto e `EOF` → **deve retornar status 0**
- [ ] Variáveis devem ser expandidas dentro do heredoc
- [ ] `<< 'EOF'` → variáveis NÃO devem ser expandidas
- [ ] `Ctrl-C` dentro do heredoc → deve cancelar
- [ ] `Ctrl-D` dentro do heredoc → deve finalizar
- [ ] `<< 'a '` → delimitador com espaços
- [ ] `<< 'a b'` → delimitador com múltiplas palavras
- [ ] `<<` sem delimitador → erro
- [ ] **Sair e verificar leak**

## ✅ Pipes
- [ ] `|` no início → erro de sintaxe
- [ ] `|` no final → deve abrir herepipe (novo prompt)
- [ ] `echo test | cat` → pipe simples
- [ ] `echo test | cat | wc -l` → pipe múltiplo
- [ ] `|<` → erro de sintaxe
- [ ] `<|` → erro de sintaxe
- [ ] **Sair e verificar leak**

## ✅ Go Crazy and History
- [ ] `cat | cat | ls` → deve executar corretamente
- [ ] Usar setas ↑↓ para navegar no histórico
- [ ] Linhas vazias não devem ser adicionadas ao histórico
- [ ] **Sair e verificar leak**

## ✅ Environment Variables
Comparar tudo com bash:
- [ ] `echo "$USER"` → expandir dentro de aspas duplas
- [ ] `echo "$USER$USER"` → múltiplas expansões
- [ ] `echo "$USER "` → com espaço
- [ ] `echo $"USER"` → **deve imprimir literal $USER**
- [ ] `echo "$"USER` → parcialmente expandido
- [ ] `echo $'USER'` → **deve imprimir literal $USER**
- [ ] `echo '$USER'` → literal (sem expansão)
- [ ] `echo '$'USER` → parcialmente literal
- [ ] `echo $@` → variável especial
- [ ] `echo $@@` → múltiplos `@`
- [ ] `echo $@@@@` → ainda mais `@`
- [ ] `echo $` → apenas `$`
- [ ] `echo $fdasfwed32r43wr2rferfrefewe` → variável inexistente (vazio)
- [ ] `echo $?` → exit status do último comando
- [ ] **Sair e verificar leak**

---

## 📝 Notas Importantes

### Sobre Memory Leaks:
- Testar POUCOS comandos de cada vez
- Sair do programa após cada teste
- Se houver leak, é mais fácil identificar qual comando causou

### Sobre Valgrind:
```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell
```

### Sobre Comparação com Bash:
Sempre usar `echo $?` após comandos para verificar exit status

### Bugs Específicos Corrigidos:
1. ✅ heredoc sem comando retorna status 0
2. ✅ exit "" retorna erro (código 2)
3. ✅ exit -9223372036854775809 retorna erro (código 2)
4. ✅ ctrl-C retorna status 130
5. ✅ export '' retorna erro (código 1)
6. ✅ cd sem argumentos vai para $HOME
7. ✅ echo $"USER" imprime literal $USER
8. ✅ echo $'USER' imprime literal $USER

---

## 🚀 Como Executar os Testes

### Compilar:
```bash
make re
```

### Teste manual individual:
```bash
./minishell
# executar comandos manualmente
exit
```

### Teste com script:
```bash
chmod +x test_minishell.sh
./test_minishell.sh
```

### Teste individual com valgrind:
```bash
chmod +x test_valgrind.sh
./test_valgrind.sh
```

### Testes rápidos de bugs:
```bash
chmod +x quick_tests.sh
./quick_tests.sh
```
