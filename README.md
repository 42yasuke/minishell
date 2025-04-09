# 🐚 minishell

**minishell** est un projet de l'école 42 qui consiste à recréer un shell UNIX basique. Il permet de comprendre en profondeur le fonctionnement des shells, la gestion des processus, la redirection des entrées/sorties, la manipulation de l’environnement, et bien plus.

## 🎯 Objectif

Développer un shell interactif capable d’interpréter des commandes simples ou composées, en respectant le comportement du shell Bash, tout en gérant :

- les redirections (`>`, `>>`, `<`, `<<`)
- les pipes (`|`)
- les variables d’environnement
- les signaux (`CTRL+C`, `CTRL+\`)
- la gestion des erreurs, quotes, expansions…

## ⚙️ Fonctionnalités implémentées

- 💬 Lecture et parsing de la ligne de commande
- 🧵 Exécution de commandes simples et chaînées avec pipes
- 📂 Support des redirections (in/out/append/heredoc)
- 🌱 Gestion de l’environnement (`env`, `export`, `unset`, etc.)
- 📜 Expansions (`$VAR`, `~`)
- 🧠 Gestion fine des quotes (`'` et `"`)
- ❌ Gestion des erreurs (commande introuvable, syntaxe, permissions…)
- 📶 Gestion des signaux (`SIGINT`, `SIGQUIT`)
- 🧼 Gestion mémoire sans fuites

## 📚 Built-ins supportés

* echo
* cd
* pwd
* export
* unset
* env
* exit

## 🧪 Compilation et Utilisation

### Compilation

Le projet utilise un `Makefile` pour faciliter la compilation.

```bash
make
```

Pour nettoyer les fichiers objets :

```bash
make clean
```

Pour supprimer tous les fichiers compilés (objets + exécutable) :

```bash
make fclean
```

Pour recompiler le projet :

```bash
make re
```

### 📄 Utilisation

```bash
./minishell
```
Tu entres alors dans un shell interactif :
```shell
minishell$ echo Hello World!
Hello World!
```
### 🎮 Exemples de commandes

```shell
minishell$ echo "Salut $USER"
minishell$ ls -l | grep minishell > out.txt
minishell$ cat << EOF
> Ceci est un heredoc
> EOF
```
