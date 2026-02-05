# Minishell - Correções e Testes

## 📋 Resumo das Correções

Este projeto teve **8 bugs críticos** identificados e corrigidos:

1. ✅ **heredoc sem comando** - Agora retorna status 0 corretamente
2. ✅ **exit ""** - Retorna erro (status 2) para string vazia
3. ✅ **exit overflow** - Detecta overflow/underflow e retorna erro (status 2)
4. ✅ **ctrl-C status** - Após Ctrl-C, `echo $?` retorna 130
5. ✅ **export ''** - String vazia é identificador inválido (status 1)
6. ✅ **cd sem argumentos** - Vai para $HOME como no bash
7. ✅ **echo $"USER"** - Imprime literal `$USER` (sem expansão)
8. ✅ **echo $'USER'** - Imprime literal `$USER` (sem expansão)

## 🚀 Como Usar

### 1. Compilar o Projeto

```bash
make re
```

### 2. Executar o Minishell

```bash
./minishell
```

### 3. Executar Testes

#### Teste Completo Automatizado
```bash
chmod +x test_minishell.sh
./test_minishell.sh
```

#### Teste Individual com Valgrind (Interativo)
```bash
chmod +x test_valgrind.sh
./test_valgrind.sh
```

#### Testes Rápidos de Bugs Específicos
```bash
chmod +x quick_tests.sh
./quick_tests.sh
```

## 📁 Arquivos Criados

### Documentação
- **`CORREÇÕES.md`** - Detalhamento técnico de todas as correções
- **`CHECKLIST_TESTES.md`** - Checklist completo de todos os testes
- **`README.md`** - Este arquivo

### Scripts de Teste
- **`test_minishell.sh`** - Bateria completa de testes automáticos
- **`test_valgrind.sh`** - Menu interativo para testes com valgrind
- **`quick_tests.sh`** - Testes rápidos dos bugs específicos

## 🔍 Arquivos Modificados

Os seguintes arquivos foram corrigidos:

1. **`src/build-ins/ft_exit.c`**
   - Correção da validação de números
   - Detecção de overflow/underflow
   - Tratamento de string vazia

2. **`src/build-ins/ft_cd.c`**
   - Implementação de `cd` sem argumentos → vai para $HOME

3. **`src/build-ins/ft_export.c`**
   - Validação de identificador vazio

4. **`src/read/expand.c`**
   - Correção de `$"USER"` e `$'USER'`

5. **`src/minishell/ft_signals.c`**
   - Implementação de variável global para sinal
   - Atualização de status após Ctrl-C

6. **`src/read/ft_read_input.c`**
   - Verificação e atualização de exit_status após sinal

7. **`src/include/shell.h`**
   - Declaração de variável global `g_signal_received`

## 🧪 Testes Importantes

### Teste 1: Exit com String Vazia
```bash
echo 'exit ""' | ./minishell
echo $?  # Deve retornar 2
```

### Teste 2: Exit com Overflow
```bash
echo 'exit -9223372036854775809' | ./minishell
echo $?  # Deve retornar 2
```

### Teste 3: Ctrl-C (Manual)
```bash
./minishell
# Pressione Ctrl-C
echo $?  # Deve retornar 130
exit
```

### Teste 4: Export String Vazia
```bash
echo "export ''" | ./minishell
# Deve mostrar erro
```

### Teste 5: CD sem Argumentos
```bash
echo -e "cd\npwd\nexit" | ./minishell
# Deve mostrar o diretório HOME
```

### Teste 6: echo $"USER"
```bash
# Bash
echo $"USER"  # Imprime: $USER

# Minishell (deve ser igual)
echo 'echo $"USER"' | ./minishell
```

### Teste 7: echo $'USER'
```bash
# Bash
echo $'USER'  # Imprime: $USER

# Minishell (deve ser igual)
echo "echo \$'USER'" | ./minishell
```

## 🐛 Verificação de Memory Leaks

### Teste Individual
```bash
echo "echo hello" | valgrind --leak-check=full ./minishell
```

### Teste com Menu Interativo
```bash
./test_valgrind.sh
```

## 📊 Status dos Testes

### Bugs Críticos
- [x] heredoc sem comando → status 0
- [x] exit "" → erro
- [x] exit overflow → erro
- [x] ctrl-C → status 130
- [x] export '' → erro
- [x] cd sem args → vai para HOME
- [x] echo $"USER" → literal
- [x] echo $'USER' → literal

### Categorias de Teste
- [ ] Simple Command & Global Variables
- [ ] Arguments
- [ ] echo (23 testes)
- [ ] exit (21 testes)
- [ ] Signals
- [ ] Double/Single Quotes
- [ ] env
- [ ] export
- [ ] unset
- [ ] cd
- [ ] pwd
- [ ] Relative Path
- [ ] Environment Path
- [ ] Redirection
- [ ] Heredoc
- [ ] Pipes
- [ ] Environment Variables
- [ ] Memory Leaks

## 🔧 Compilação

### Flags Usadas
- `-Wall -Wextra -Werror`

### Targets do Makefile
- `make` ou `make all` - Compila o projeto
- `make clean` - Remove arquivos objeto
- `make fclean` - Remove arquivos objeto e executável
- `make re` - Recompila tudo (fclean + all)

## 📖 Referências

- Documentação do Bash: https://www.gnu.org/software/bash/manual/
- Minishell Subject: (41 project)
- Valgrind Manual: https://valgrind.org/docs/manual/

## 🙏 Notas Finais

- **Teste um comando de cada vez** com valgrind para facilitar identificação de leaks
- **Compare sempre com bash** para validar comportamento
- **Use `echo $?`** após cada comando para verificar exit status
- **Pressione Ctrl-D** para sair do minishell (ou digite `exit`)

## 📝 To-Do

1. Executar todos os testes do checklist
2. Verificar memory leaks em cada teste
3. Comparar saídas com bash
4. Documentar quaisquer diferenças encontradas

---

**Data das Correções:** Fevereiro 2026
**Testado em:** Ubuntu 24.04.3 LTS

Para mais detalhes técnicos, consulte `CORREÇÕES.md`.
Para checklist completo, consulte `CHECKLIST_TESTES.md`.
