# Correções Aplicadas ao Minishell

## Resumo das Correções

### 1. **exit "" (string vazia)**
**Arquivo:** `src/build-ins/ft_exit.c`

**Problema:** A função `ft_is_number()` não verificava se a string estava vazia, retornando 1 (true) para strings vazias.

**Solução:** Adicionada verificação no início da função:
```c
if (!str || !str[0])
    return (0);
```
Também adicionado verificação após o sinal de +/- para garantir que há pelo menos um dígito:
```c
if (!str[i])
    return (0);
```

---

### 2. **exit -9223372036854775809 (overflow)**
**Arquivo:** `src/build-ins/ft_exit.c`

**Problema:** A função `ft_atol()` não detectava overflow corretamente ao multiplicar o resultado por 10.

**Solução:** 
- Adicionado include `<limits.h>` para usar LONG_MIN
- Modificada a detecção de overflow em `ft_atol()`:
```c
if (result < 0 || (sign == 1 && result < prev) || \
    (sign == -1 && result < 0 && prev >= 0))
    return (LONG_MIN);
```
- Modificada `ft_exit()` para verificar se o resultado é LONG_MIN (indicando overflow):
```c
exit_code = ft_atol(args[1]);
if (exit_code == LONG_MIN && \
    ft_strncmp(args[1], "-9223372036854775808", 21) != 0)
{
    print_error_msg(args[0], "numeric argument required");
    return (2);
}
```

---

### 3. **ctrl-C retorna status errado**
**Arquivos:** 
- `src/include/shell.h`
- `src/minishell/ft_signals.c`
- `src/read/ft_read_input.c`

**Problema:** Quando o usuário pressionava Ctrl-C no prompt, o exit_status não era atualizado para 130.

**Solução:**
1. Adicionada variável global em `shell.h`:
```c
extern int g_signal_received;
```

2. Definida e atualizada no handler de sinal em `ft_signals.c`:
```c
int g_signal_received = 0;

static void ft_handle_signals(int sig)
{
    (void)sig;
    g_signal_received = 130;
    // ... resto do código
}
```

3. Verificação e atualização do exit_status em `ft_read_input.c`:
```c
if (g_signal_received)
{
    shell->exit_status = g_signal_received;
    g_signal_received = 0;
}
```

---

### 4. **export '' (string vazia)**
**Arquivo:** `src/build-ins/ft_export.c`

**Problema:** A função `ft_is_invalid_identity()` não verificava se a string estava vazia.

**Solução:** Adicionada verificação no início:
```c
if (!str || !str[0])
    return (1);
```
E verificação adicional após o loop:
```c
if (i == 0)
    return (1);
```

---

### 5. **cd sem argumentos**
**Arquivo:** `src/build-ins/ft_cd.c`

**Problema:** O comando `cd` sem argumentos retornava erro em vez de ir para a pasta HOME.

**Solução:** Modificado para buscar a variável de ambiente HOME e fazer chdir para ela:
```c
if (args[1] == NULL)
{
    home = getenv("HOME");
    if (!home)
    {
        print_error_msg("cd", "HOME not set");
        return (1);
    }
    oldpwd = getcwd(NULL, 0);
    if (chdir(home) != 0)
    {
        print_perror_msg("cd", home);
        free(oldpwd);
        return (1);
    }
    pwd = getcwd(NULL, 0);
    ft_set_env(&env, ft_strdup("OLDPWD"), oldpwd);
    ft_set_env(&env, ft_strdup("PWD"), pwd);
    return (0);
}
```

---

### 6. **echo $"USER" e echo $'USER'**
**Arquivo:** `src/read/expand.c`

**Problema:** O `$` seguido de aspas estava sendo expandido incorretamente. No bash:
- `echo $"USER"` → imprime `$USER` (sem expansão)
- `echo $'USER'` → imprime `$USER` (sem expansão)

**Solução:** Adicionada verificação em `handle_dollar()` para retornar "$" literalmente quando seguido de aspas:
```c
if (line[*i] == '\'' || line[*i] == '\"')
    return (ft_strdup("$"));
```

---

### 7. **heredoc sem comando (status)**
**Status:** Este problema pode não existir mais após as correções, mas precisa ser testado.

O heredoc deve retornar status 0 quando executado com sucesso, mesmo sem comando após ele.

---

## Como Testar

### Compilar o projeto:
```bash
make re
```

### Executar o script de testes:
```bash
chmod +x test_minishell.sh
./test_minishell.sh
```

### Testes com valgrind:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./minishell
```

### Testes manuais importantes:

1. **exit "":**
```bash
echo 'exit ""' | ./minishell
echo $?  # Deve ser 2
```

2. **exit overflow:**
```bash
echo 'exit -9223372036854775809' | ./minishell
echo $?  # Deve ser 2
```

3. **ctrl-C:**
```bash
./minishell
# Pressione Ctrl-C
echo $?  # Deve ser 130
```

4. **export '':**
```bash
echo "export ''" | ./minishell
echo $?  # Deve ser 1
```

5. **cd sem argumentos:**
```bash
echo -e "cd\npwd" | ./minishell  # Deve mostrar $HOME
```

6. **echo $"USER":**
```bash
echo 'echo $"USER"' | ./minishell  # Compare com bash
```

7. **echo $'USER':**
```bash
echo "echo \$'USER'" | ./minishell  # Compare com bash
```

---

## Testes Completos Recomendados

Execute todos os testes listados no documento original, incluindo:

### Simple Command & global variables
- Comandos com caminho absoluto
- Comando vazio ("" ou '')
- Linhas com apenas espaços/tabs

### Arguments
- Comandos com opções e argumentos

### echo
- Todos os testes de echo com diferentes combinações de aspas

### exit
- Todos os valores de teste incluindo overflows

### Signals
- Ctrl-C deve retornar 130
- Ctrl-D deve funcionar corretamente

### export/unset
- Variáveis válidas e inválidas
- Strings vazias

### cd
- Com e sem argumentos
- Pastas existentes/inexistentes
- Verificação de PWD/OLDPWD

### Environment variables
- Todas as variações de expansão de variáveis

### Redirection & Pipes
- Redirecionamentos múltiplos
- Heredoc com e sem comando
- Pipes em várias posições

### Memory Leaks
- Testar cada funcionalidade com valgrind
- Sair do programa após cada teste

---

## Notas Adicionais

- As correções foram aplicadas seguindo o comportamento do bash
- Todas as funções mantêm compatibilidade com a norminette
- Os testes devem ser executados um de cada vez para facilitar a identificação de leaks
- Sempre compare o comportamento com o bash usando: `echo $?` após cada comando
